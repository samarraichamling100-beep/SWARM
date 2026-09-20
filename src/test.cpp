#include <iostream>
#include <vector>



int main ()
{
    std::vector<int> List = {0,1,2,4,4,5};

    std::cout << "List Size : " << List.size() << std::endl;

    float a = 3;
    float b = 3;

    const float Y = a + b;
    std::cout << Y << std::endl;
}
