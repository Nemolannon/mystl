#include <iostream>
#include <vector>
#include "vector.cpp"

const int QUANTITY = 100;

class Obj
{
    public:
    //static int copy_counter;
    static int counter;
    int n;
    int*pN;
    Obj() : n(counter++), pN(&n) {}
    Obj(const Obj& obj) : n(obj.n), pN(&n) {std::cout << n << " copy constructor called" << std::endl;}
    ~Obj(){
        //delete pN;
        std::cout << n << " destructor called" << std::endl;}
};

//int Obj::copy_counter = 0;
int Obj::counter = 0;

int main()
{
    my::vector<int>vec;
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(0);
    int *p = vec.begin();
    for(int i(0); i < vec.size(); ++i)
    {
        std::cout << p[i] << std::endl;
    }
}