

#include <iostream>
#include <string>
#include <typeinfo>
#include <algorithm>
int main ()
{
    std::string haystack = "samarishandsome";
    std::string needle = "handsome"; 
    char needlepin = needle[0];
    int OccuringIndex;
    for(int index = 0;index < haystack.length();index++)
    {
        int RemainingRange;
        std::cout << "Index : " << index << std::endl;
        bool IsStartingLetter = haystack[index] == needlepin;
        std::cout << "IsStartingLetter : " << IsStartingLetter << std::endl;
        RemainingRange = haystack.length() - needle.length() - index;
        std::cout << haystack.length() << " - " << needle.length() << " - " << index << " - " << 2 << " = " << RemainingRange << std::endl;
        bool HasNeededRange = RemainingRange <= 0;
        std::cout << "HasNeededRange : " << HasNeededRange << std::endl;
        if(IsStartingLetter &&  HasNeededRange)
        {
            std::string letter;
            letter += haystack[index];

            if(letter == needle)
            {
                std::cout << "Occuring letter : "<< letter << std::endl;
            }
        }
    }
    return 0;
}