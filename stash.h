#include <iostream>
template<class T>
class Stash
{
    size_t nCounter;
    size_t nSize;
    T* pStash;

    void operator delete(void*) {std::cout << "delete called" << std::endl;};
    void operator delete[](void*) {std::cout << "delete[] called" << std::endl;}
    public:
    Stash() : nCounter(0), nSize(1), pStash(new T[nSize]) {}

    ~Stash()
    {
        for(int f = 0; f < nCounter; ++f)
        {
            pStash[f].~T();
        }
        free(pStash);
    }
    void inflate()
    {
        std::cout << "inflate" << std::endl;
        T* pOldStash = pStash;
        nSize *= 2;
        std::cout << "create a new stash" << std::endl;
        void* p = malloc(nSize * sizeof(T));
        pStash = static_cast<T*>(p);
        for(int f = 0; f < nCounter; ++f)
        {
            pStash[f] = pOldStash[f];
        }
        std::cout << "delete the old stash" << std::endl;
        for(int f = 0; f < nCounter; ++f)
        {
            pOldStash[f].~T();
        }
        free(pOldStash);
    }

    void push_back(const T& val)
    {
        std::cout << "push_back obj " << val.n << std::endl;
        if(nCounter == nSize)
        {
            inflate();
        }
        pStash[nCounter++] = val;
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