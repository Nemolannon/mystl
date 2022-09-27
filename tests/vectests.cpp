#define BOOST_TEST_MODULE my_vector
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include "../vector/vector.cpp"
namespace data = boost::unit_test::data;
namespace utf = boost::unit_test;

struct F {
  const int size;
  my::vector<int> vec;  // Тестируемый вектор
  int *prototype; // Идентичный тестируемому вектору массив

  F() : size(10), prototype(new int(size))
  {
    vec.reserve(size);
    for(int f=0; f < size; ++f)
    {
      prototype[f] = f;
      vec.push_back(f);
    }
  }
  ~F() { delete[] prototype; }
};

/* 1. Вектор хранит данные в виде массива, то есть в линейном порядке. Следовательно, имея указатель
  на первый элемент, можно получить доступ ко всем остальным точно так же, как это можно сделать с обычным массивом
*/

  BOOST_DATA_TEST_CASE_F(F, linearity_test, data::make({0,1,2,3,4,5,6,7,8,9}), val)
  {
    int* test_array = vec.begin();  // Получаем указатель на первый элемент
    BOOST_TEST(test_array[val] == prototype[val]);  // Проверяем, как работает "индексация"
  }

/* 2.1 Метод capacity() возвращает объём памяти, зарезервированной под хранение элементов(будет проверено далее);
  "пустой" вектор владеет объемом памяти, определенным константой MY_VECTOR_INIT_SIZE(1).
*/

BOOST_AUTO_TEST_CASE(init_size_test)
{
  my::vector<int> vec;
  BOOST_TEST(vec.capacity() == MY_VECTOR_INIT_SIZE);
}

/* 2.2 Когда память исчерпана, вектор резервирует новую область, вдвое больше той, что было.
*/

BOOST_DATA_TEST_CASE(auto_increase_capacity_test, data::make({1,2,4,8,16,32,64,128,256}), limit)
{
  my::vector<int> vec;  // Пустой вектор
  BOOST_TEST(vec.capacity() == 1);  // Проверить, действительно ли он владеет только 1 байтом памяти
  for(int i(0); i < limit; ++i)
  {
    vec.push_back(0); //  Заполнить всю выделенную память
  }
  BOOST_TEST(vec.capacity() == limit); // Проверить объем памяти до увеличения
  vec.push_back(0); // Вызвать "переполнение"
  BOOST_TEST(vec.capacity() == limit*2);  // В результате объем выделенной памяти должен увеличиться в два раза
}

// ----------------------------------------------3 reserve()-------------------------

/*  3.1 Метод reserve(size_t n) резервирует память под n элементов
*/

BOOST_DATA_TEST_CASE(test_3_1_reserve_base, data::make({0, 1, 200, 3}), mem_size)
{
  my::vector<int>vec;
  BOOST_TEST_MESSAGE("Empty vector size is 1");
  BOOST_TEST(vec.capacity() = MY_VECTOR_INIT_SIZE);
  BOOST_TEST_MESSAGE("Reserve mem_size blocks");
  vec.reserve(mem_size);
  BOOST_TEST_MESSAGE("Cheking reserved volume");
  BOOST_TEST(vec.capacity() == mem_size);
}

/* 3.2 Максимально допустимый объем памяти, которым может владеть вектор, определен константой MY_VECTOR_MAX_SIZE.
  Если n больше этого параметра, вырабатывается исключение std::length_error
*/

BOOST_AUTO_TEST_CASE(test_3_2_reserve_length_error)
{
  my::vector<char>vec;
  BOOST_CHECK_THROW(vec.reserve(MY_VECTOR_MAX_SIZE + 1), std::length_error);
}

/* 3.3 Увеличение объема зарезервированной памяти (увеличение capacity методом reserve) не должно повредить или сделать недоступными уже хранящиеся в векторе данные,
  включая нерелоцируемые объекты и данные, которыми объект владеет по ссылке
*/

struct F1
{

  static const int SIZE = 10;
  static const char CODE = 'a';

  int *prototypeN;
  char *prototypeToken;
  
  class Obj
  {
    public:
    int n;
    int *pN;  // Указатель на поле n делает объекты класса Obj нерелоцируемыми
    char *pcToken;  // Указывает на символ, под который выделена память из кучи
    static bool pbReleased[SIZE]; // Чтобы отследить вызов деструктора

    Obj(const int nn, const char tok) : n(nn), pN(&n), pcToken(new char(tok))
    {
      pbReleased[n] = false;
    }

    Obj(const Obj& obj) : n(obj.n), pN(&n), pcToken(new char(*(obj.pcToken))) {}
    
    ~Obj()
    {
      delete pcToken;
      pbReleased[n] = true;
    }
  };

  my::vector<Obj>vec;
  
  F1() : prototypeN(new int[SIZE]), prototypeToken(new char[SIZE])
  {
    for(int i(0); i < SIZE; ++i)
    {
      prototypeN[i] = i;
      prototypeToken[i] = CODE+i;
      vec.push_back(Obj(i,static_cast<char>(CODE+i),));
    }
  }
  ~F1()
  {
    delete[] prototypeN;
    delete[] prototypeToken;
  }
};

BOOST_DATA_TEST_CASE_F(F1, test_3_3_reserve_data_integrity, data::make({11, 16, 20, 200, 1200}), new_size)
{
  for(bool repeat(true);;repeat = false)
  {
    Obj* pObj = vec.begin();
    for(int i(0); i < vec.size(); ++i)
    {
      BOOST_TEST(prototypeN[i] == pObj[i].n);
      BOOST_TEST(prototypeN[i] == *(pObj[i].pN));
      BOOST_TEST(prototypeToken[i] == *(pObj[i].pcToken));
    }
    if(repeat) vec.reserve(new_size);
      else break;
  }
}

/* 3.4 При сокращении объема (убавление capacity методом reserve) все объекты, подлежащие удалению, а также все
  данные, которыми каждый объект владеет по ссылке, должны быть удалены(вызов деструктора).
*/

BOOST_DATA_TEST_CASE_F(F1, test_3_4_reserve_memory_freeing_up, data::make({9,8,7,6,5,4,3,2,1,0}), new_size)
{
  Obj* pObj = vec.begin();
  for(int i(0); i < vec.size(); ++i)
  {
    BOOST_TEST(prototypeN[i] == pObj[i].n);
    BOOST_TEST(prototypeN[i] == *(pObj[i].pN));
    BOOST_TEST(prototypeToken[i] == *(pObj[i].pcToken));
    BOOST_TEST(!pbReleased[i]);
  }

  vec.reserve(new_size);
  BOOST_TEST(vec.capacity() == new_size);

  for(int i(0); i < vec.size(); ++i)
  {
    BOOST_TEST(prototypeN[i] == pObj[i].n);
    BOOST_TEST(prototypeN[i] == *(pObj[i].pN));
    BOOST_TEST(prototypeToken[i] == *(pObj[i].pcToken));
  }

  for(int i(new_size); i < SIZE; ++i)
  {
    BOOST_TEST(pbReleased[i]);
  }
}