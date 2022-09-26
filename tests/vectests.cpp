#define BOOST_TEST_MODULE fixture_03
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include "../vector/vector.cpp"
namespace data = boost::unit_test::data;
namespace utf = boost::unit_test;

/* 1. Вектор хранит данные в виде массива, то есть в линейном порядке. Следовательно, имея указатель
  на первый элемент, можно получить доступ ко всем остальным точно так же, как это можно сделать с обычным массивом
*/
struct F {
  const int size;
  my::vector<int> vec;
  int* arr;

  F() : size(10), arr(new int(size))
  {
    BOOST_TEST_MESSAGE("Ctor F");
    vec.reserve(10);
    for(int f=0; f < 10; ++f)
    {
      arr[f] = f;
      vec.push_back(f);
    }
  }
  ~F() { delete arr; }
};

BOOST_AUTO_TEST_SUITE(s, * utf::fixture<F>())

  BOOST_DATA_TEST_CASE(Linearity_test, data::make({0,1,2,3,4,5,6,7,8,9}), val)
  {
    //int* vecarray = vec.begin();
    BOOST_TEST(true);//vecarray[val] == arr[val]);
  }


  BOOST_AUTO_TEST_CASE(test_case2)
  {
    BOOST_TEST_MESSAGE("running test_case2");
    BOOST_TEST(true);
  }

BOOST_AUTO_TEST_SUITE_END()