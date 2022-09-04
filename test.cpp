#include <iostream>
#include <vector>

const int QUANTITY = 100;

class Obj
{
    public:
    static int copy_counter;
    int n;
    int*pN;
    Obj(int nn = 0) : n(nn), pN(new int(10)) {}
    Obj(const Obj& obj) : n(obj.n*QUANTITY + ++copy_counter), pN(new int(*(obj.pN))) {std::cout << "copy constructor called" << std::endl;}
    ~Obj(){
        delete pN;
        std::cout << "destructor called" << std::endl;}
};

int Obj::copy_counter = 0;

int main()
{
    Obj obj;
    Obj* p;
    {
        void* temp = ::operator new(sizeof(Obj));
        p = new(temp) Obj(obj);
    }
    std::cout << *(p->pN) << std::endl;
}