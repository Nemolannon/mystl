#include <vector>
#include <iostream>
#include "stash.h"
using namespace std;

class Obj{

    public:
    
    int n;
    static int counter;

    Obj(int nn) : n(nn)
    {
        ++counter;
        cout << "Obj " << n << " constructor called" << endl;
    }

    Obj() : n(counter++)
    {
        cout << "Obj " << n << " constructor called" << endl;
    }
    Obj(const Obj& obj) : n(obj.n)
    {
        cout << "Obj " << n << " copy constructor called" << endl;
    }
    ~Obj()
    {
        cout << "Obj " << n << " destructor called" << endl;
    }
};

int Obj::counter = -1;

int main()
{
    const int size = 1000;
    //Obj obj;
    Stash<Obj> stash;
    for(int f = 0; f < size; ++f)
    {
        cout << "create " << f << " exemplair" << endl;
        Obj obj;
        stash.push_back(obj);
        cout << "exemplair " << f << " has been pushed" << endl;
    }
    for(int f = 0; f < size; ++f)
    {
        cout << stash[f].n << endl;
    }
}