#include "vector.h"

namespace my
{


//----------------------------------------------Конструкторы----------------------------------------------
template<class T>
vector<T>::vector() : MAX_SIZE(MY_VECTOR_MAX_SIZE), TYPE_SIZE(sizeof(T)),
    nCounter(0), nSize(MY_VECTOR_INIT_SIZE),
    pStash(static_cast<T*>(::operator new(nSize*TYPE_SIZE)))
{}

template<class T>
vector<T>::vector(int n) : MAX_SIZE(MY_VECTOR_MAX_SIZE), TYPE_SIZE(sizeof(T)),
    nCounter(0), nSize(n)
{
    if(nSize > MAX_SIZE) throw std::length_error("Exceeded the maximum size of the vector. MAX_SIZE is " + std::to_string(MAX_SIZE) + ", " + std::to_string(nSize) + " requested");
    pStash = static_cast<T*>(::operator new(nSize*TYPE_SIZE));
    for(T *tmp(pStash); nCounter < n; ++nCounter, ++tmp)
        new(tmp) T(T());
}

template<class T>
vector<T>::vector(const vector<T> &vec) : MAX_SIZE(vec.MAX_SIZE), TYPE_SIZE(vec.TYPE_SIZE), nSize(vec.nSize), nCounter(vec.nCounter),
pStash(static_cast<T*>(::operator new(nSize*TYPE_SIZE)))
{
    for(T *targ(pStash), *source(vec.pStash), *bound(const_cast<T*>(vec.cend())); source < bound; ++targ, ++source)
    {
        new(targ) T(*source);
    }
}

template<class T>
vector<T>::~vector()
{
        for(T *temp(pStash), *bound(end()); temp < bound; ++temp)
        {
            temp->~T();
        }
        ::operator delete(pStash);
}


//------------------------------------Доступ к элементам----------------------------------

//at()
template<class T>
typename vector<T>::reference vector<T>::at(const size_t n)
{
    if(n < nSize) return pStash[n];
    throw std::out_of_range("Out of range in my::vector::at(), nSize = " + std::to_string(nSize) + "; n = " + std::to_string(n));
}

//operator[]
template<class T>
typename vector<T>::reference vector<T>::operator[](size_type n)
{
    return pStash[n];
}


//---------------------------------------Модификация------------------------

//clear()
template<class T>
void vector<T>::clear()
{
    for(T *temp(pStash), *bound(end()); temp < bound; ++temp)
    {
        temp->~T();
    }
    ::operator delete(pStash);
    nCounter = 0;
    nSize = MY_VECTOR_INIT_SIZE;
    pStash = static_cast<T*>(::operator new(nSize * TYPE_SIZE));
}

//insert(pos, value, count)
/* Метод insert(), как и в стандартном векторе, выполняет побитовое копирование тех элементов,
 которые требуется переместить внутри вектора, поэтому для успешного выполнения insert
 все элементы вектора должны быть РЕЛОЦИРУЕМЫ, то есть для вектора объектов типа
    struct Obj
    {
        int n;
        int* pN = &n;
    };
 операция insert может сделать некоторое количество указателей Obj::pN недействительными.

 Кроме того, при вставке в вектор диапазона элементов [first, last),
 если эти элементы берутся из того самого вектора, для которого вызван insert,
 и хотя бы один из них будет перемещен в процессе вставки, выйдет ошибка.
 Исключение составляет только тот случай, когда для вставки элементов потребуется
 дополнительно выделить память. В этом случае для всех перемещаемых объектов будут вызваны
 копирующие конструкторы
*/

template<class T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos, const_reference val)
{
    T *retv;
    if(nCounter < nSize)// если место в контейнере ещё есть
    {
        T *target(end()), *source(&back());
        for(; source >= pos; --target, --source)
        {
            *target = *source;  // Как и в стандартном векторе, все существующие в контейнере объекты перемещаются побитовым копированием, без вызова копирующего конструктора
        }

        new(target) T(val);
        retv = target;
    }
    else
    {
        nSize *= 2; // Увеличиваем размер
        // Если превышен лимит, бросаем исключение
        if(nSize > MAX_SIZE) throw std::length_error("Exceeded the maximum size of the vector. MAX_SIZE is " + std::to_string(MAX_SIZE) + ", " + std::to_string(nSize) + " requested");
        T* pOldStash = pStash;  // Сохраняем указатель
        pStash = static_cast<T*>(::operator new(nSize * TYPE_SIZE));// Выделяем память под контейнер нового размера
        T *target(pStash), *source(pOldStash);
        for( ; source < pos; ++target, ++source)
        {
            new(target) T(*source);
            source->~T();
        }

        retv = target;
        
        new(target++) T(val);

        for(T *bound(pOldStash + nCounter); source < bound; ++target, ++source)
        {
            new(target) T(*source);
            source->~T();
        }
        // Замечание: теперь итератор pos, как и вообще все сохраненные итераторы, становятся недействительными

        ::operator delete(pOldStash);   // Освобождаем память, которая была занята только что скопированным контейнером
    }
    ++nCounter;
    return retv;
}

template<class T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos, size_type count, const_reference val)
{
    if(count == 0) return end();
    T *retv;
    if(nCounter < nSize - count)// если место в контейнере ещё есть
    {
        T *target(&back()+count), *source(&back());
        for(; source >= pos; --target, --source)
        {
            *target = *source;  // Как и в стандартном векторе, все существующие в контейнере объекты перемещаются побитовым копированием, без вызова копирующего конструктора
        }

        for(size_t i(count); i; --i) new(target--) T(val);
        retv = target;
    }
    else
    {
        while(nCounter < nSize - count) nSize *= 2; // Увеличиваем размер
        // Если превышен лимит, бросаем исключение
        if(nSize > MAX_SIZE) throw std::length_error("Exceeded the maximum size of the vector. MAX_SIZE is " + std::to_string(MAX_SIZE) + ", " + std::to_string(nSize) + " requested");
        T* pOldStash = pStash;  // Сохраняем указатель
        pStash = static_cast<T*>(::operator new(nSize * TYPE_SIZE));// Выделяем память под контейнер нового размера
        T *target(pStash), *source(pOldStash);
        for( ; source < pos; ++target, ++source)
        {
            new(target) T(*source);
            source->~T();
        }

        retv = target;
        
        for(size_t i(count); i; --i) new(target++) T(val);

        for(T *bound(pOldStash + nCounter); source < bound; ++target, ++source)
        {
            new(target) T(*source);
            source->~T();
        }
        // Замечание: теперь итератор pos, как и вообще все сохраненные итераторы, становятся недействительными

        ::operator delete(pOldStash);   // Освобождаем память, которая была занята только что скопированным контейнером
    }
    nCounter += count;
    return retv;
}

//insert(pos, first, last)
template<class T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos, iterator first, const_iterator last)
{
    T *retv;
    size_t chunksize(last - first); // Сколько элементов копировать
    size_t needspace(nCounter + chunksize); // Сколько нужно будет памяти для вектора после вставки
    if(nSize < needspace)   // Если выделено меньше, чем нужно
    {
        while(nSize < needspace) nSize*= 2; // Увеличиваем размер
        // Если превышен лимит, бросаем исключение
        if(nSize > MAX_SIZE) throw std::length_error("Exceeded the maximum size of the vector. MAX_SIZE is " + std::to_string(MAX_SIZE) + ", " + std::to_string(nSize) + " requested");
        T* pOldStash = pStash;  // Сохраняем указатель
        pStash = static_cast<T*>(::operator new(nSize * TYPE_SIZE));// Выделяем память под контейнер нового размера
        T *newStashSlider(pStash), *oldStashSlider(pOldStash);
        for( ; oldStashSlider < pos; ++newStashSlider, ++oldStashSlider)// Копировать в новый контейнер все элементы от нуля до позиции вставки
        {
            new(newStashSlider) T(*oldStashSlider);
        }

        retv = newStashSlider;  // Сохранить указатель на начало вставки для возврата

        // Копируем из источника элементы в диапазоне [first, last)
        for(T *source(first); source < last; ++source, ++newStashSlider)
            new(newStashSlider) T(*source);

        // Переносим в конец вектора все оставшиеся элементы
        for(T *bound(pOldStash + nCounter); oldStashSlider < bound; ++newStashSlider, ++oldStashSlider)
        {
            new(newStashSlider) T(*oldStashSlider);
        }

        // Удалить все перемещенные элементы
        for(T *bound(pOldStash + nCounter), *tmp = pOldStash; tmp < bound; ++tmp)
        {
            tmp->~T();
        }
        // Освобождаем память, которая была занята только что скопированным контейнером
        ::operator delete(pOldStash);
    }
    else// если место в контейнере ещё есть
    {
        // Перемещаем "отрезок" [pos, back()] на chunksize элементов
        T *target(&back() + chunksize), *source(&back());
        for(; source >= pos; --target, --source)
        {
            *target = *source;
        }

        // Копируем [first, last) в образовавшееся пространство
        for(const T *chunkSlider(last - 1); chunkSlider >= first; --target, --chunkSlider)
            new(target) T(*chunkSlider);

        retv = target;  // Сохраняем указатель на вставку для возврата
    }

    nCounter += chunksize;  // Увеличиваем счетчик элементов
    return retv;    // Выход
}

//erase(first, last)
template<class T>
typename vector<T>::iterator vector<T>::erase(iterator first, const_iterator last)
{
    // Для вектора {0,1,2,3,4(first),5,6,7(last),8,9,10}

    // Удаляем элементы [first, last) (т.е. 4,5,6)
    for(T *tmp(first); tmp < last; ++tmp)
    {
        tmp->~T();
    }
    // Получаем {0,1,2,3,X,X,X,7(first),8,9,10(last)}

    // Присоединяем "хвост"( 7(first), 8, 9, 10(last), bound )
    for(T *recv(first), *source(const_cast<T*>(last)), *bound(end()); source < bound; ++recv, ++source)
    {
        *recv = *source;
    }
    // Получаем {0,1,2,3,7,8,9,10}

    // Вычисляем количество элементов
    nCounter -= last-first;

    // Выход
    return nullptr;
}

//erase(pos)
template<class T>
typename vector<T>::iterator vector<T>::erase(iterator pos)
{
    return erase(pos, pos+1);
}

//push_back()
template<class T>
void vector<T>::push_back(const T& val)
{
    if(nCounter == nSize) reserve(nSize*2);
    new(&(pStash[nCounter++])) T(val);
}

//pop_back()
template<class T>
void vector<T>::pop_back()
{
    if(nCounter == 0) return;
    pStash[--nCounter].~T();
}


//------------------------------------Объем, размер, вместимость------------------------

//reserve()
template<class T>
void vector<T>::reserve(size_t n)
{
    nSize = n; // Пробуем изменить размер
    // Если нарушен лимит, бросаем исключение
    if(nSize > MAX_SIZE) throw std::length_error("Exceeded the maximum size of the vector. MAX_SIZE is " + std::to_string(MAX_SIZE) + ", " + std::to_string(nSize) + " requested");
    size_t copyes = (n > nCounter) ? nCounter : n;  // Вычисляем, сколько элементов нужно перенести в новый контейнер
    T* pOldStash = pStash;  // Сохраняем указатель
    pStash = static_cast<T*>(::operator new(nSize * TYPE_SIZE));// Выделяем память под контейнер нового размера
    // Распространённое в интернете решение:
    // pStash = new T[nSize];
    // кажется ошибочным, так как в этом случае для каждого
    // созданного элемента T автоматически будет вызван не нужный(а иногда и недоступный) в данном случае конструктор по умолчанию;
    // более верным кажется выделение из кучи неотформатированной области нужного размера,
    // её принудительное "форматирование"(static_cast<>) и последующее размещение в эой облати
    // копий существующих объектов при помощи оператора placement new.
    for(T *target(pStash), *source(pOldStash), *bound(pOldStash + copyes); source < bound; ++target, ++source)
    {
        new(target) T(*source);
        source->~T();  // В данном случае также необходим принудительный вызов деструктора для каждого элемента, что тоже выглядит не очень изящно, но другого способа я не нашел
    }

    // Если нужно, удаляем остатки
    for(T *tmp(pOldStash + copyes), *bound(pOldStash + nCounter); tmp < bound; ++tmp)
    {
        tmp->~T();
    }
    
    ::operator delete(pOldStash);   // Освобождаем память, которая была занята только что скопированным контейнером
}

// resize(new_size)
template<class T>
void vector<T>::resize(size_type new_size)
{
    reserve(new_size);
    for(T *tmp(pStash + nCounter), *bound(pStash + nSize); tmp < bound; ++tmp, ++nCounter)
    {
        new(tmp) T();
    }
}

//resize(new_size, val)
template<class T>
void vector<T>::resize(size_type new_size, const_reference val)
{
    reserve(new_size);
    for(T *tmp(pStash + nCounter), *bound(pStash + nSize); tmp < bound; ++tmp, ++nCounter)
    {
        new(tmp) T(val);
    }
}

};