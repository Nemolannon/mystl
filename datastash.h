template <class T>
class DataStash
{
    std::size_t nSize;   // Размер области памяти, выделенной для хранения (исчисляется не в байтах, а в элементах).
    const std::size_t type_size;
    std::size_t nCounter;   // Количество экземпляров, хранящихся в контейнере
    void* pMem; // Указатель на начало области памяти, выделенной под хранение данных(адрес первой ячейки в этой области)
    void* pSlider; // Указатель на начало свободной области памяти(адрес ячейки памяти, следующей за последним байтом последнего хранящегося в контейнере элемента)
    void* pMemUpperBound;   // Верхняя граница области памяти, выделенной под хранение элементов (адрес последней ячейки в этой области).
    

    void inflate()
    {
        nSize *= 2;
        void* pOldMem = pMem;
        pMem = pSlider = malloc(nSize*type_size);
        T* arr = static_cast<T*>(pOldMem);
        for(int f = 0; f < nCounter; ++f)
        {
            new T(arr[f]);
            delete arr[f];
        }
        free(pOldMem);
    }

    void* operator new(std::size_t size)
    {
        void* pOldSlider = this->pSlider;
        this->pSlider += size;
        return pOldSlider;
    }

    void operator delete(void* p) {}    // delete будет только вызывать деструктор
    public:
    DataStash() : type_size(sizeof(T)), nSize(1), pMem(malloc(type_size)), pSlider(pMem), pMemUpperBound(pMem + type_size * nSize) {}
};