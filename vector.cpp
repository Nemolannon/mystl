#include "vector.h"
namespace my
{

template<class T>
vector::vector() : MAX_SIZE(MY_VECTOR_MAX_SIZE), TYPE_SIZE(sizeof(T)),
    nCounter(0), nSize(MY_VECTOR_INIT_SIZE),
    pStash(static_cast<T*>(::operator new(nSize*TYPE_SIZE)))
{}

template<class T>
void vector::inflate()
{
        nSize *= 2; // Увеличиваем размер
        // Если нарушен лимит, бросаем исключение
        if(nSize >= MAX_SIZE) throw std::length_error("Exceeded the maximum size of the vector. MAX_SIZE is " + std::to_string(MAX_SIZE) + ", " + std::to_string(nSize) + " requested");
        T* pOldStash = pStash;  // Сохраняем указатель
        pStash = static_cast<T*>(::operator new(nSize * TYPE_SIZE));// Выделяем память под контейнер нового размера
        for(int f = 0; f < nCounter; ++f)
        {
            new(&(pStash[f])) T(pOldStash[f]);  // Копируем элементы в новый контейнер
        }
        for(int f = 0; f < nCounter; ++f)
        {
            pOldStash[f].~T();  // Удаляем все элементы, которые были скопированы
        }
        ::operator delete(pOldStash);   // Освобождаем память, которая была занята только что скопированным контейнером
}

};