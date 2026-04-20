#include "ScalarConverter.hpp"

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
    else if (!str.compare("+inf") || !str.compare("+inff") || !str.compare("inf") || !str.compare("inff"))
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
