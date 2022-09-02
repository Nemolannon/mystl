#include <vector>
#include <iostream>
using namespace std;

class Obj{

    public:
    
    int n;
    static int counter;

    Obj(int nn) : n(nn)
    {
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

int Obj::counter = 0;

int main()
{
    cout << "Create the vector(5)" << endl;
    vector<Obj> vo(5);
    cout << "Create the Obj" << endl;
    Obj obj(100);
    cout << "Insert Obj at begin()" << endl;
    vo.insert(vo.begin(), obj);
    cout << "insert Obj at begin() + 2" << endl;
    vo.insert(vo.begin(), obj);
    cout << "Exit the programm" << endl;
}