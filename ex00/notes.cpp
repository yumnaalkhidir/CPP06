#include "ScalarConverter.hpp"
#include <cctype>
#include <cstdlib>
#include <ctype.h>
#include <cstdlib>
#include <iostream>
#include<cmath>
#include <limits>
#include <string>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(ScalarConverter& copy) {(void)copy;}
ScalarConverter& ScalarConverter::operator=(ScalarConverter& other){(void)other; return (*this);}
ScalarConverter::~ScalarConverter() {}

int detect_specials(std::string str)
{
    if (!str.compare("-inf") || !str.compare("-inff"))
    {
        std::cout << "char: " << "Impossible" << std::endl;
        std::cout << "int: " << "Impossible" << std::endl;
        std::cout << "double: " << "-inf" << std::endl;
        std::cout << "float: " << "-inff" << std::endl;
        return(1);
    }
    else if (!str.compare("+inf") || !str.compare("+inff"))
    {
        std::cout << "char: " << "Impossible" << std::endl;
        std::cout << "int: " << "Impossible" << std::endl;
        std::cout << "double: " << "+inf" << std::endl;
        std::cout << "float: " << "+inff" << std::endl;
        return(1);
    }
    else if (!str.compare("nan") || !str.compare("nanf"))
    {
        std::cout << "char: " << "Impossible" << std::endl;
        std::cout << "int: " << "Impossible" << std::endl;
        std::cout << "double: " << "nan" << std::endl;
        std::cout << "float: " << "nanf" << std::endl;
        return(1);
    }
    return(0);
}

int detect_literal(std::string str)
{
    if (str.length() == 1 && !std::isdigit(str[0]))
    {
        std::cout << "char: " << str[0] << std::endl;
        std::cout << "int: " << static_cast<int>(str[0]) << std::endl;
        std::cout << "double: " << static_cast<double>(str[0]) << ".0" << std::endl;
        std::cout << "float: " << static_cast<float>(str[0]) << ".0f" << std::endl;
        return (1);
    }
    return(0);
}

void toChar(double value)
{
    if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max()
        || isnan(value) || isinf(value))
    {
        std::cout << "char: Impossible" << std::endl;
        return ;
    }
    char c = static_cast<char>(value);
    if (std::isprint(c))
        std::cout << "char: " << c << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    
}
void toInt(double value)
{
    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()
        || isnan(value) || isinf(value))
    {
        std::cout << "int: Impossible" << std::endl;
        return ;
    }
    else
    {
        int val = static_cast<int>(value);
        std::cout << "int: " << val << std::endl;
    }
}
void toDouble(double value)
{
    if (isnan(value))
    {
        std::cout << "double: nan" << std::endl;
        return ;
    }
    else if (value == std::numeric_limits<double>::infinity())
    {
        std::cout << "double: +inf" << std::endl;
        return ;
    }
    else if (value == -std::numeric_limits<double>::infinity())
    {
        std::cout << "double: -inf" << std::endl;
        return ;
    }
    if (value == static_cast<int>(value))
        std::cout << "double: " << value << ".0" << std::endl;
    else
        std::cout << "double: " << value << std::endl;
}
void toFloat(double value)
{
    if (isnan(value))
    {
        std::cout << "float: nanf" << std::endl;
        return ;
    }
    else if (value == std::numeric_limits<double>::infinity())
    {
        std::cout << "float: +inff" << std::endl;
        return ;
    }
    else if (value == -std::numeric_limits<double>::infinity())
    {
        std::cout << "float: -inff" << std::endl;
        return ;
    }
    if (value == static_cast<int>(value))
        std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl; 
    else
        std::cout << "float: " << static_cast<float>(value) << "f" << std::endl; 
}

void ScalarConverter::convert(std::string str)
{
    if (detect_specials(str))
        return ;
    if (detect_literal(str))
        return ;

    if (!str.empty() && str[str.length() - 1] == 'f')
    {
        std::cout << "str now is: " << str << std::endl;
        str.erase(str.length() - 1);
        std::cout << "str now is: " << str << std::endl;
    }
    char* endptr;
    double value = std::strtod(str.c_str(), &endptr);
    if (*endptr != '\0')
    {
        std::cout << "char: " << "Impossible" << std::endl;
        std::cout << "int: " << "Impossible" << std::endl;
        std::cout << "double: " << "Impossible" << std::endl;
        std::cout << "float: " << "Impossible" << std::endl;
        return ;
    }
    toChar(value);
    toInt(value);
    toDouble(value);
    toFloat(value);
}




enum Type
{
    CHAR,
    INT,
    DOUBLE,
    FLOAT,
    PSEUDO,
    INVALID
};
bool is_int(std::string str)
{
    if (str.find('.') == std::string::npos && str.find_first_not_of("-+0123456789") == std::string::npos)
        return (true);
    return (false);
}

bool is_double(std::string str)
{
    if (str.find('.') != std::string::npos && str.find_first_not_of("-+0123456789") == std::string::npos)
        return (true);
    return (false);
}

bool is_float(std::string str)
{
    if (str.find('.') != std::string::npos && str.find_first_not_of("-+0123456789f") == std::string::npos
            && str.find_last_of("f") == str.length() - 1)
        return (true);
    return (false);
}
Type detect_type(std::string str)
{
    if (!str.compare("-inf") || !str.compare("-inff")
        || !str.compare("+inf") || !str.compare("+inff")
        || !str.compare("nan") || !str.compare("nanf"))
        return (PSEUDO);
    else if (str.length() == 1 && !std::isdigit(str[0]))
        return (CHAR);
    else if (is_int(str))
        return (INT);
    else if (is_double(str))
        return (DOUBLE);
    else if (is_float(str))
        return (FLOAT);
    else
        return (INVALID);
}