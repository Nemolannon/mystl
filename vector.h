#pragma once
namespase my{

template<class T>
class vector
{
    public:
    // -------------------------------Определения типов-----------------
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = const T*;
    // iterator?
    // const_iterator?
    // reverse_iterator?
    // const_reverce_iterator?

    // -----------------------------------Операторы---------------------------
    reference operator[](const size_type);
    vector<value_type>& operator=(const vector<value_type>&);
    // ==,!=, <=, >=... ?

    // -------------------------------------Методы------------------------------

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
    

};

};