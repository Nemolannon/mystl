#include <vector>
#include <iostream>
#include "vector.cpp"
//using namespace std;

class Obj{

    public:
    
    static int counter;
    int n;
    int* pN;

    Obj(int nn) : n(nn), pN(new int(nn))
    {
        ++counter;
        std::cout << "Obj " << n << " constructor called" << std::endl;
    }

    Obj() : n(counter++), pN(new int(n))
    {
        std::cout << "Obj " << n << " constructor called" << std::endl;
    }
    Obj(const Obj& obj) : n(obj.n), pN(new int(*(obj.pN)))
    {
        std::cout << "Obj " << n << " copy constructor called" << std::endl;
    }
    ~Obj()
    {
        delete pN;
        std::cout << "Obj " << n << " destructor called" << std::endl;
    }
};

int Obj::counter = 0;

int main()
{
    const int size = 80;
    //Obj obj;
    std::vector<Obj> stash;
    //stash.resize(128);
    for(int f = 0; f < size; ++f)
    {
        std::cout << "create " << f << " exemplair" << std::endl;
        Obj obj;
        stash.push_back(obj);
        std::cout << "exemplair " << f << " has been pushed" << std::endl;
    }

    stash.insert(stash.cbegin() + 31, stash.cbegin() + 60, stash.cbegin() + 65);

    for(int f = 0; f < size; ++f)
    {
        std::cout << *(stash[f].pN) << std::endl;
    }
}