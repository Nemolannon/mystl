#include <iostream>
template<class T>
class Stash
{
    size_t nCounter;
    size_t nSize;
    T* pStash;

    public:
    Stash() : nCounter(0), nSize(1), pStash(static_cast<T*>(::operator new (sizeof(T) * nSize))) {}

    ~Stash()
    {
        for(int f = 0; f < nCounter; ++f)
        {
            pStash[f].~T();
        }
        ::operator delete(pStash);
    }
    void inflate()
    {
        std::cout << "inflate" << std::endl;
        T* pOldStash = pStash;
        nSize *= 2;
        std::cout << "create a new stash" << std::endl;
        pStash = static_cast<T*>(::operator new(nSize * sizeof(T)));
        for(int f = 0; f < nCounter; ++f)
        {
            new(&(pStash[f])) T(pOldStash[f]);
        }
        std::cout << "delete the old stash" << std::endl;
        for(int f = 0; f < nCounter; ++f)
        {
            pOldStash[f].~T();
        }
        ::operator delete(pOldStash);
    }

    void push_back(const T& val)
    {
        std::cout << "push_back obj " << val.n << std::endl;
        if(nCounter == nSize)
        {
            inflate();
        }
        new(&(pStash[nCounter++])) T(val);
    }

    void pop_back()
    {
        if(nCounter == 0) return;
        pStash[--nCounter].~T();
    }

    T& operator[](size_t n)
    {
        return pStash[n];
    }
};