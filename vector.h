#pragma once

#ifndef MY_VECTOR_INIT_SIZE
#define MY_VECTOR_INIT_SIZE 1   // 
#endif
#ifndef MY_VECTOR_MAX_SIZE
#define MY_VECTOR_MAX_SIZE 1048576 //
#endif

namespace my{

template<class T> 
class vector
{
    
    const unsigned long long int MAX_SIZE; // Максимально допустимый размер вектора в элементах
    const std::size_t TYPE_SIZE;// Размер типа, только для того чтобы не вызывать каждый раз sizeof...

    std::size_t nCounter;  // Количество объектов в контейнере
    std::size_t nSize;   // Размер контейнера в элементах(объём памяти, выделенной под хранение элементов)

    T* pStash; // указатель на первый элемент контейнера
    
    public:
    
    // -------------------------------Традиционная конспирация-----------------

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    // reverse_iterator?
    // const_reverse_iterator?

    // -----------------------------------Операторы---------------------------

    reference operator[](const size_type);
    vector<value_type>& operator=(const vector<value_type>&);
    // ==,!=, <=, >=... ?

    // -------------------------------------Методы------------------------------

    // Конструкторы, деструкторы..
    vector(); 
    vector(int);
    vector(const vector<T>&);
    ~vector();

    // Доступ к элементам
    reference at(const size_type);  // throws std::out_of_range
    reference front() {return *pStash; }  // Возвращает ссылку на первый элемент
    reference back() { return nCounter == 0 ? *pStash : *(pStash+nCounter-1);}   // Возвращает ссылку на последний элемент

    // Итераторы
    iterator begin() { return pStash; };
    const_iterator cbegin() const { return const_cast<const_iterator>(pStash); };
    iterator end() { return pStash + nCounter; };
    const_iterator cend() const { return const_cast<const_iterator>(pStash + nCounter); };

    // Объем, размер, вместимость
    bool empty() const{ return nCounter == 0; }
    size_type size() const { return nCounter; } // Количество элементов, которые хранятся в vector в данный момент
    size_type max_size() const { return MAX_SIZE; } // Максимально допустимое количество элементов
    void reserve(size_type n); // Меняет объем памяти, выделенной под хранение; объем становится равным n, все что окажется за пределами - удаляется. throws std::length_error
    size_type capacity() const { return nSize; } // Объем памяти(в элементах), выделенной под хранение элементов

    // Модификация
    void clear();
    iterator insert(const_iterator pos, const_reference val);   // Вставляет val перед pos
    iterator insert(const_iterator pos, size_type count, const_reference value);   // Вставляет count копий value перед pos
    iterator insert(const_iterator pos, iterator first, const_iterator last); // Вставляет перед pos копии элементов исходного контейнера, находящихся в диапазоне [first, last) 
    iterator erase(iterator pos); // Удаляет элемент pos из контейнера
    iterator erase(iterator first, const_iterator last); // Удаляет из контейнера элементы, находящиеся в диапазоне [first, last)
    void push_back(const T& value);
    void pop_back();
    void resize(size_type new_size);   // Увеличивает/уменьшает размер выделенной памяти контейнера до new_size элементов;
        // если new_size < size(), все элементы с номерами от new_size и больше будут удалены;
        // если new_size > size(), в конец вектора будет добавлено new_size() - size элементов, инициализированных конструктором по умолчанию
    void resize(size_type new_size, const_reference value);  // То же самое, но все добавленные(при необходимости) элементы будут инициализированы значением value
};

};