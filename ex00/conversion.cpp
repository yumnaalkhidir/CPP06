#include "ScalarConverter.hpp"

int convert_to_int(const std::string &str)
{
    errno = 0;
    char *end;
    long value = std::strtol(str.c_str(), &end, 10);
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN)
        throw std::overflow_error("int overflow");
    return static_cast<int>(value);
}

double convert_to_double(const std::string &str)
{
    errno = 0;
    char *end;
    double value = std::strtod(str.c_str(), &end);

    if (errno == ERANGE)
        throw std::overflow_error("double overflow");

    return value;
}

float convert_to_float(const std::string &str)
{
    errno = 0;
    char *end;
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

    std::cout << "double: " << std::fixed << std::setprecision(1)
              << static_cast<double>(value) << std::endl;

    std::cout << "float: " << std::fixed << std::setprecision(1)
              << static_cast<float>(value) << "f" << std::endl;
}

void type_double(double value)
{

    if (value < 0 || value > 127)
        std::cout << "char: Impossible" << std::endl;
    else if (!std::isprint(static_cast<char>(value)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: " << static_cast<char>(value) << std::endl;
    
    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
        std::cout << "int: Impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(value) << std::endl;

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

    if (value < 0 || value > 127)
        std::cout << "char: Impossible" << std::endl;
    else if (!std::isprint(static_cast<char>(value)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: " << static_cast<char>(value) << std::endl;

    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
        std::cout << "int: Impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(value) << std::endl;

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