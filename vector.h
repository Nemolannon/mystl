#pragma once

#ifndef MY_VECTOR_MAX_SIZE
#define MY_VECTOR_MAX_SIZE 4294967296 // Максимально допустимое количество элементов
#endif
#ifndef MY_VECTOR_INIT_SIZE
#define MY_VECTOR_INIT_SIZE 1   // Количество элементов, под которые будет выделена память при создании вектора
#endif

namespase my{

template<class T>
class vector
{
    const std::size_t MAX_SIZE; // Максимально допустимое количество элементов
    const std::size_t TYPE_SIZE;// Размер типа данных, хранящихся в контейнере

    std::size_t nCounter;  // Количество элементов, хранящихся в контейнере
    std::size_t nSize;   // Размер области памяти, выделенной для хранения (исчисляется не в байтах, а в элементах).

    T* pStash; // Указатель на начало области памяти, выделенной под хранение элементов вектора

    // -------------------------------Рабочие процедуры---------------------
    void inflate();  // Удваивает количество выделенной памяти; throws std::length_error
    
    public:
    // -------------------------------Определения типов-----------------
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    // reverse_iterator?
    // const_reverce_iterator?

    // -----------------------------------Операторы---------------------------
    reference operator[](const size_type);
    vector<value_type>& operator=(const vector<value_type>&);
    // ==,!=, <=, >=... ?

    // -------------------------------------Методы------------------------------

    // Конструкторы, деструкторы..
    vector();
    vector(const vector&);
    ~vector();

    // Доступ к элементам
    reference at(const size_type);  // throws std::out_of_range
    reference front();  // Возвращает ссылку на первый элемент
    reference back();   // Возвращает ссылку на последний элемент

    // Объем, размер, вместимость
    bool empty() const;
    size_type size() const; // Количество элементов, которые хранятся в vector в данный момент
    size_type max_size() const; // Максимально допустимое количество элементов
    void reserve(size_type n) // Выделяет дополнительно память для n элементов(увеличивает capacity на n); throws std::length_error
    size_type capacity() const; // Количество элементов, которые можно поместить в vector без дополнительного выделения памяти

    // Модификация
    void clear();
    iterator insert(const_iterator pos, const T& value);    // Вставляет копию value перед pos
    iterator insert(const_iterator pos, size_type count, const T& value);   // Вставляет count копий value перед pos
    iterator insert(const_iterator pos, iterator first, const_iterator last); // Вставляет перед pos копии элементов исходного контейнера, находящихся в диапазоне [first, last) 
    iterator erase(iterator pos); // Удаляет элемент pos из контейнера
    iterator erase(iterator first, const_iterator last); // Удаляет из контейнера элементы, находящиеся в диапазоне [first, last)
    void push_back(const T& value);
    void pop_back();
    void resize(size_type new_size);   // Увеличивает/уменьшает размер выделенной памяти контейнера до new_size элементов;
        // если new_size < size(), все элементы с номерами от new_size и больше будут удалены;
        // если new_size > size(), в конец вектора будет добавлено new_size() - size неинициализированных элементов
    void resize(sizetype new_size, const_reference value);  // То же самое, но все добавленные(при необходимости) элементы будут инициализированы значением value
};

};