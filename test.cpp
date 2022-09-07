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
    Obj obj[10];
    Obj* pFront = &obj[0];
    Obj* pBack = &obj[9];
    Obj* pPos = &obj[5];
    Obj* pEnd = pBack+1;
    std::cout << pEnd+(pFront-pPos) << std::endl;
}