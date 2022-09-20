#include <iostream>
#include <vector>

void out(const std::vector<int> &vec)
{
    std::cout << "Content:" << std::endl;
    for(int i(0); i < vec.size(); ++i)
        std::cout << i << " " << vec[i] << std::endl;
    std::cout << "size = " << vec.size() << std::endl;
    std::cout << "capacity = " << vec.capacity() << std::endl;
}

int main()
{
    std::vector<int> vec;
    vec.reserve(12);
    out(vec);
    vec.insert(vec.begin(), 10, 10);
    out(vec);
    vec.resize(15, 10);
    out(vec);
    vec.push_back(10);
    out(vec);
}