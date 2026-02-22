#include "ScalarConverter.hpp"
#include <cctype>
#include <cstdlib>
#include <ctype.h>
#include <cstdlib>
#include <cerrno>
#include <cfloat>
#include <exception>
#include <iostream>
#include<cmath>
#include <climits>
#include <limits>
#include <string>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(ScalarConverter& copy) {(void)copy;}
ScalarConverter& ScalarConverter::operator=(ScalarConverter& other){(void)other; return (*this);}
ScalarConverter::~ScalarConverter() {}
enum Type
{
    CHAR, // 0
    INT, // 1
    DOUBLE, // 2
    FLOAT, // 3 
    PSEUDO, // 4
    INVALID // 5
};

bool is_int(const std::string& str)
{
    if (str.empty())
        return false;

    int i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (i == (int)str.length())
        return false;
    for (; i < (int)str.length(); i++)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}

bool is_double(const std::string& str)
{
    if (str.empty())
        return false;

    int i = 0;
    bool has_dot = false;
    bool has_digit = false;

    if (str[i] == '+' || str[i] == '-')
        i++;

    for (; i < (int)str.length(); i++)
    {
        if (std::isdigit(str[i]))
            has_digit = true;
        else if (str[i] == '.' && !has_dot)
            has_dot = true;
        else
            return false;
    }
    return has_dot && has_digit;
}

bool is_float(const std::string& str)
{
    if (str.empty() || str[str.length() - 1] != 'f')
        return false;

    // str.erase(str.length() - 1);
    return is_double(str.substr(0, str.length() - 1));
}
Type detect_type(const std::string& str)
{
    if (!str.compare("-inf") || !str.compare("-inff")
        || !str.compare("+inf") || !str.compare("+inff")
        || !str.compare("nan") || !str.compare("nanf"))
        return (PSEUDO);
    else if (str.length() == 1 && !std::isdigit(str[0]))
        return (CHAR);
    else if (is_int(str))
        return (INT);
    else if (is_float(str))
        return (FLOAT);
    else if (is_double(str))
        return (DOUBLE);
    else
        return (INVALID);
}
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


int convert_to_int(const std::string& str)
{
    errno = 0;
    char* end;
    long value = std::strtol(str.c_str(), &end, 10);
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN)
        throw std::overflow_error("int overflow");
    return static_cast<int>(value);
}

double convert_to_double(const std::string& str)
{
    errno = 0;
    char* end;
    double value = std::strtod(str.c_str(), &end);

    if (errno == ERANGE)
        throw std::overflow_error("double overflow");

    return value;
}

float convert_to_float(const std::string& str)
{
    errno = 0;
    char* end;
    double temp = std::strtod(str.c_str(), &end);

    if (errno == ERANGE || std::isinf(temp))
        throw std::overflow_error("float overflow");

    return static_cast<float>(temp);
}

void type_char(char c)
{
    if (!std::isprint(c))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: " << c << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
    std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
}
void type_int(int value)
{
    if (value < 0 || value > 127)
    std::cout << "char: Impossible" << std::endl;
    else if (!std::isprint(static_cast<char>(value)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: " << static_cast<char>(value) << std::endl;

    std::cout << "int: " << value << std::endl;
    std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
    std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
}
void type_double(double value)
{
    //CHAR
    if (value < 0 || value > 127)
    std::cout << "char: Impossible" << std::endl;
    else if (!std::isprint(static_cast<char>(value)))
        std::cout << "char: Non dispalyable" << std::endl;
    else
        std::cout << "char: " << static_cast<char>(value) << std::endl;
    //INT
    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()
        || isnan(value) || isinf(value))
        std::cout << "int: Impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(value) << std::endl;
    //DOUBLE
    if (isnan(value))
    {
        std::cout << "double: nan" << std::endl;
        std::cout << "float: nanf" << std::endl;
    }
    else if (value == std::numeric_limits<double>::infinity())
    {
        std::cout << "double: +inf" << std::endl;
        std::cout << "float: +inff" << std::endl;
    }
    else if (value == -std::numeric_limits<double>::infinity())
    {
        std::cout << "double: -inf" << std::endl;
        std::cout << "float: -inff" << std::endl;
    }
    if (value == static_cast<int>(value))
    {
        std::cout << "double: " << value << ".0" << std::endl;
        std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl; 
    }
    else
    {
        std::cout << "double: " << value << std::endl;
        std::cout << "float: " << static_cast<float>(value) << "f" << std::endl; 
    }
}
void type_float(float value)
{
    double d_val = static_cast<double>(value); 
    //CHAR
    if (value < 0 || value > 127)
    std::cout << "char: Impossible" << std::endl;
    else if (!std::isprint(static_cast<char>(value)))
        std::cout << "char: Non dispalyable" << std::endl;
    else
        std::cout << "char: " << static_cast<char>(value) << std::endl;
    //INT
    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()
            || isnan(d_val) || isinf(d_val))
        std::cout << "int: Impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(value) << std::endl;
    //DOUBLE
    if (isnan(d_val))
    {
        std::cout << "double: nan" << std::endl;
        std::cout << "float: nanf" << std::endl;
    }
    else if (d_val == std::numeric_limits<double>::infinity())
    {
        std::cout << "double: +inf" << std::endl;
        std::cout << "float: +inff" << std::endl;
    }
    else if (d_val == -std::numeric_limits<double>::infinity())
    {
        std::cout << "double: -inf" << std::endl;
        std::cout << "float: -inff" << std::endl;
    }
    if (value == static_cast<int>(value))
    {
        std::cout << "double: " << d_val << ".0" << std::endl;
        std::cout << "float: " << value << ".0f" << std::endl; 
    }
    else
    {
        std::cout << "double: " << d_val << std::endl;
        std::cout << "float: " << value << "f" << std::endl; 
    }
}

void ScalarConverter::convert(std::string str)
{
    Type str_type = detect_type(str);

    switch (str_type) {
        case PSEUDO:
        {
            detect_specials(str);
            break ;
        }
        case CHAR:
        {
            char c = str[0];
            type_char(c);
            break ;
        }
        case INT:
        {
            try {
                int value = convert_to_int(str);
                type_int(value);
            }
            catch (std::exception& e) {
            std::cout << "char: Impossible" << std::endl;
            std::cout << "int: Impossible" << std::endl;
            std::cout << "float: Impossible" << std::endl;
            std::cout << "double: Impossible" << std::endl;
        }
            break ;
        }
        case FLOAT:
        {
            try {
                float f_value = convert_to_float(str);
                type_float(f_value);
                
            } 
            catch (std::exception& e) {
            std::cout << "char: Impossible" << std::endl;
            std::cout << "int: Impossible" << std::endl;
            std::cout << "float: Impossible" << std::endl;
            std::cout << "double: Impossible" << std::endl;
        }
            break ;
        }
        case DOUBLE:
        {
            try {
                double d_value = convert_to_double(str);
                type_double(d_value);
            }
            catch (std::exception& e) {
            std::cout << "char: Impossible" << std::endl;
            std::cout << "int: Impossible" << std::endl;
            std::cout << "float: Impossible" << std::endl;
            std::cout << "double: Impossible" << std::endl;
        }
            break ;
        }
        case INVALID:
        {
            std::cout << "char: " << "Impossible" << std::endl;
            std::cout << "int: " << "Impossible" << std::endl;
            std::cout << "double: " << "Impossible" << std::endl;
            std::cout << "float: " << "Impossible" << std::endl;
            break ;
        }
    }
}
