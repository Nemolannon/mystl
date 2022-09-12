#include <iostream>
#include <vector>
//#include "vector.cpp"

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
    std::vector<Obj> vobj(128);
    vobj.push_back(Obj());
    std::cout << "Out content:" << std::endl;
    for(Obj &obj : vobj)
        std::cout << *(obj.pN) << std::endl;
    std::cout << "Inserting:" << std::endl;
    vobj.insert(vobj.begin()+100,vobj.begin()+90, vobj.begin()+110);
    std::cout << "Out content:" << std::endl;
    for(Obj &obj : vobj)
        std::cout << obj.n << " " << *(obj.pN) << std::endl;
    std::cout << "Size of vector " << vobj.size() << std::endl;
    std::cout << "Exit programm" << std::endl;
}