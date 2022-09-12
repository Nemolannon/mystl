// --------------------------THE CLONE FACTORY-----------------------
// "Фабрика клонов". Высокоуровневый низкохудожественный триллер с предсказуемой развязкой.
// Написано в хорошем расположении духа. Читать рекомендуется в таком же расположении.

#pragma once    // (C) ANDREW_APPLICATIONS, 2022. All right reserved (Копирование материалов препроцессором категорически запрещено)

#ifndef MY_VECTOR_INIT_SIZE
#define MY_VECTOR_INIT_SIZE 1   // Даже самое великое зло всегда начинается с мелочи
#endif
#ifndef MY_VECTOR_MAX_SIZE
#define MY_VECTOR_MAX_SIZE 1048576 // Найди свой предел: определи максимальную высоту дома перед #include
#endif

namespace my{   // Очевидно, что такие опасные эксперименты лучше проводить на закрытой территории

template<class T>   // Вывеска: "Клонируем что угодно"
class vector    // Фабрика клонов... Вот оно, вместилище боли и ужаса..
{
    // Информация для сотрудников: корпоративные тайны
    const unsigned long long int MAX_SIZE; // Когда-нибудь это закончится
    const std::size_t TYPE_SIZE;// Что бы мы ни клонировали, оно всегда будет иметь определенный размер. Этот размер необходимо учитывать при строительстве жилых помещений, иначе ОНО не влезет

    std::size_t nCounter;  // Количество занятых квартир/этажей в доме
    std::size_t nSize;   // Высота дома

    T* pStash; // Адрес дома

    // -------------------------------Рабочие процедуры---------------------
    void inflate();  // Когда в этом доме не хватит места, мы построим другой, вдвое больше; throws std::length_error
    
    public: // Информация для клиентов
    
    // -------------------------------Традиционная конспирация-----------------
    // Чтобы никто не догадался
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
    // Чтобы запутать всех еще больше
    reference operator[](const size_type);
    vector<value_type>& operator=(const vector<value_type>&);
    // ==,!=, <=, >=... ?

    // -------------------------------------Методы------------------------------

    // Конструкторы, деструкторы..
    vector();   // Собственно, цех по производству the houses of clones
    vector(int);
    vector(const vector&);  // Если мы "клонируем все, что угодно", мы должны уметь клонировать также и наши дома
    ~vector();  // Отдел кадров

    // Доступ к элементам
    reference at(const size_type);  // throws std::out_of_range
    reference front();  // Возвращает ссылку на первый элемент
    reference back() { return nCounter == 0 ? *pStash : *(pStash+nCounter-1);}   // Возвращает ссылку на последний элемент

    // Итераторы
    iterator begin() { return pStash; };
    const_iterator cbegin() const { return const_cast<const_iterator>(pStash); };
    iterator end() { return pStash + nCounter; };
    const_iterator cend() const { return const_cast<const_iterator>(pStash + nCounter); };

    // Объем, размер, вместимость
    bool empty() const;
    size_type size() const; // Количество элементов, которые хранятся в vector в данный момент
    size_type max_size() const; // Максимально допустимое количество элементов
    void reserve(size_type n); // Выделяет дополнительно память для n элементов(увеличивает capacity на n); throws std::length_error
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
    void resize(size_type new_size, const_reference value);  // То же самое, но все добавленные(при необходимости) элементы будут инициализированы значением value
};

};