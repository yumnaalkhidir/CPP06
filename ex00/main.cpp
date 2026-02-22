#include <iostream>
#include "ScalarConverter.hpp"

int main(void)
{
    ScalarConverter::convert("d");
    std::cout << std::endl;
    ScalarConverter::convert("-43");
    std::cout << std::endl;
    ScalarConverter::convert("-43.34");
    std::cout << std::endl;
    ScalarConverter::convert("-34f");
    std::cout << std::endl;
    ScalarConverter::convert("-inf");
    std::cout << std::endl;
    ScalarConverter::convert("-43es"); 
    std::cout << std::endl;
    ScalarConverter::convert("-1e309f"); 
    
}