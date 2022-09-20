#include <vector>
#include <iostream>
#include "vector.cpp"
//using namespace std;

class Obj{

    public:
    
    static int counter;
    int n;
    int* pN;

    Obj(int nn) : n(nn), pN(&n)
    {
        ++counter;
        std::cout << "Obj " << n << " constructor called" << std::endl;
    }

    Obj() : n(counter++), pN(&n)
    {
        std::cout << "Obj " << n << " constructor called" << std::endl;
    }
    Obj(const Obj& obj) : n(obj.n), pN(&n)
    {
        std::cout << "Obj " << n << " copy constructor called" << std::endl;
    }
    ~Obj()
    {
        //delete pN;
        std::cout << "Obj " << n << " destructor called" << std::endl;
    }
};

int Obj::counter = 0;

int main()
{
    const int size = 80;
    //Obj obj;
    my::vector<Obj> stash;
    my::vector<my::vector<Obj>> vstash;
    //stash.reserve(127);
    for(int f = 0; f < size; ++f)
    {
        std::cout << "create " << f << " exemplair" << std::endl;
        Obj obj;
        stash.push_back(obj);
        std::cout << "exemplair " << f << " has been pushed" << std::endl;
    }

    stash.insert(stash.begin() + 31, stash.begin()+10, stash.begin() + 30);

    for(int f = 0; f < stash.size(); ++f)
    {
        std::cout << stash[f].n << " " << *(stash[f].pN) << std::endl;
    }

    std::cout << "Insert stash into vstash: " << std::endl;

    vstash.push_back(stash);
    vstash.push_back(stash);
    vstash.push_back(stash);
    vstash.push_back(stash);
    vstash.push_back(stash);

    std::cout << "vstash[1][1] = ";
    std::cout << vstash[1][1].n << std::endl;

    std::cout << "trying to acces for vstash[10][0]:" << std::endl;
    try
    {
       std::cout << vstash.at(10)[0].n << std::endl;
    }
    catch(std::out_of_range msg)
    {
        std::cout << msg.what() << std::endl;
    }

    //std::cout << "insert 10 Obj to begin() + 10 in vstash[0]:" << std::endl;

    //vstash[0].insert(vstash[0].begin()+10, 10, Obj());

    std::cout << "vstash[0]:" << std::endl;
    for(int i = 0; i < vstash[0].size(); ++i)
    {
        std::cout << vstash[0][i].n << " " << *(vstash[0][i].pN) << std::endl;
    }

    std::cout << "vstash[0].erase(vstash[0].begin()+10, vstash[0].begin+20)" << std::endl;
    vstash[0].erase(vstash[0].begin()+10, vstash[0].begin()+20);

    std::cout << "vstash[0]:" << std::endl;
    for(int i = 0; i < vstash[0].size(); ++i)
    {
        std::cout << vstash[0][i].n << " " << *(vstash[0][i].pN) << std::endl;
    }

    std::cout << "exit programm" << std::endl;
}