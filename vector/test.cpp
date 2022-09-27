#include <iostream>
#include <vector>
#include "vector.cpp"


struct F1
{

  static const int SIZE = 10;
  static const char CODE = 'a';

  int *prototypeN;
  char *prototypeToken;
  
  class Obj
  {
    public:
    int n;
    int *pN;  // Указатель на поле n делает объекты класса Obj нерелоцируемыми
    char *pcToken;  // Указывает на символ, под который выделена память из кучи
    static bool pbReleased[SIZE]; // Чтобы отследить вызов деструктора

    Obj(const int nn, const char tok) : n(nn), pN(&n), pcToken(new char(tok))
    {
      pbReleased[n] = false;
    }

    Obj(const Obj& obj) : n(obj.n), pN(&n), pcToken(new char(*(obj.pcToken))) {}
    
    ~Obj()
    {
      delete pcToken;
      pbReleased[n] = true;
    }
  };

  my::vector<Obj>vec;
  
  F1() : prototypeN(new int[SIZE]), prototypeToken(new char[SIZE])
  {
    for(int i(0); i < SIZE; ++i)
    {
      prototypeN[i] = i;
      prototypeToken[i] = CODE+i;
      vec.push_back(Obj(i,static_cast<char>(CODE+i)));
    }
  }
  
  ~F1()
  {
    delete[] prototypeN;
    delete[] prototypeToken;
  }
};


  bool F1::Obj::pbReleased[SIZE] = {0};


int main()
{
    F1 f1;
}