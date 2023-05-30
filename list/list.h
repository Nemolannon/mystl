#pragma once

namespace my{

template<class T>
class list
{
    struct Node
    {
        T value;
        Node *pNext;
        Node *pPrev;
    };
    
    public:

    using value_type        = T;
    using size_type         = std::size_t;
    using reference 	    = value_type&
    using const_reference   = const value_type&
    using pointer           = value_type*;
    using const_pointer 	= const T*;
    using iterator          = T*;
    using const_iterator    = const iterator;
    //using reverse_iterator;
    //using const_reverse_iterator;

    list();
    ~list();

    list operator=(list& other);
    assign(size_type count, const T& value);

    reference front();
    reference back();

    bool empty() const;
    size_type size() const;
    size_type maxsize() const;
    
    iterator begin();
    iterator end();

    void clear();
    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, size_type count, const T& value);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();
    void resize(size_type count);
    void resize(size_type count, const T& value);
    void swap(list& other);

    void merge(list& other);
    void splice(const_itrator pos, list& other);
    void splice(const_iterator pos, list& other, const_iterator it);
    void splice(const_iterator pos, list& other, const_iterator first, const_iterator last);
    size_type remove(const T& value);
    void reverse();
    void unique();
    void sort();

    bool operator==(const list<T>& left, const list<T>& right);
};

};