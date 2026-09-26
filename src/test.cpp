


#include <iostream>



int getLength(int x)
{
    int length;
    bool finished{};

    if(finished)
    {
        return static_cast<int>(length);
    }
    else if(x < 1)
    {
        finished = true;
    }
    while(!x < 1)
    {
        x/=10;
        length ++;
        std::cout << "The length of Integer : " << length << std::endl;
    }

}


int main ()
{


    int x = 121;


    std::cout << "Length of x : " << getLength(x) << std::endl;

    return 0;
}