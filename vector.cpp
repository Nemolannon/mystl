#include "vector.h"
namespace my
{

template<class T>
vector<T>::vector() : MAX_SIZE(MY_VECTOR_MAX_SIZE), TYPE_SIZE(sizeof(T)),
    nCounter(0), nSize(MY_VECTOR_INIT_SIZE),
    pStash(static_cast<T*>(::operator new(nSize*TYPE_SIZE)))
{}

template<class T>
vector<T>::~vector()
{
        for(int f = 0; f < nCounter; ++f)
        {
            pStash[f].~T();
        }
        ::operator delete(pStash);
}

template<class T>
void vector<T>::inflate()
{
        nSize *= 2; // Увеличиваем размер
        // Если нарушен лимит, бросаем исключение
        if(nSize >= MAX_SIZE) throw std::length_error("Exceeded the maximum size of the vector. MAX_SIZE is " + std::to_string(MAX_SIZE) + ", " + std::to_string(nSize) + " requested");
        T* pOldStash = pStash;  // Сохраняем указатель
        pStash = static_cast<T*>(::operator new(nSize * TYPE_SIZE));// Выделяем память под контейнер нового размера
        // Типичное решение, которое часто встречается в интернете:
        // pStash = new T[nSize];
        // кажется ошибочным, во-первых потому что в этом случае для каждого
        // созданного элемента T автоматически будет вызван абсолютно не нужный(а иногда и недоступный) в данном случае конструктор по умолчанию;
        // во-вторых, копирование элементов в этот уже инициализированный массив будет возможно только побитово, например с помощью оператора "=":
        // pStash[i] = pOldStash[i];
        // соответственно, необходимый вызов копирующего конструктора для каждого копируемого элемента становится недоступным
        // Поэтому выделение из кучи неотформатированной области, её принудительное форматирование и последующее размещение в эой облати
        // копий существующих объектов при помощи оператора placement new кажется единственно верным решением.
        for(int f(0); f < nCounter; ++f)
        {
            new(&(pStash[f])) T(pOldStash[f]);
        }
        for(int f(0); f < nCounter; ++f)
        {
            pOldStash[f].~T();  // В данном случае также необходим принудительный вызов деструктора для каждого элемента, что тоже выглядит не очень изящно, но другого способа я не нашел
        }
        ::operator delete(pOldStash);   // Освобождаем память, которая была занята только что скопированным контейнером
}

template<class T>
void vector<T>::push_back(const T& val)
{
    if(nCounter == nSize) inflate();
    new(&(pStash[nCounter++])) T(val);
}

template<class T>
void vector<T>::pop_back()
{
    if(nCounter == 0) return;
    pStash[--nCounter].~T();
}

/*template<class T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos, const T& val)
{
    if(pos == end()) { push_back(val); return back(); }
    if(nCount == nSize) inflate();
    iterator temp = back();
    iterator dest = end();
}*/

template<class T>
T& vector<T>::operator[](size_type n)
{
    return pStash[n];
}

};