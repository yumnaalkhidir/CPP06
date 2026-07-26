#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &copy) { (void)copy; }
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
    (void)other;
    return (*this);
}
ScalarConverter::~ScalarConverter() {}

void printImpossible()
{
    std::cout << "char: " << "impossible" << std::endl;
    std::cout << "int: " << "impossible" << std::endl;
    std::cout << "float: " << "impossible" << std::endl;
    std::cout << "double: " << "impossible" << std::endl;
}

void printAll(double value)
{
    // ---- char ----
    if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127)
        std::cout << "char: impossible" << std::endl;
    else
    {
        char c = static_cast<char>(value);
        if (!std::isprint(static_cast<char>(c)))
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: '" << c << "'" << std::endl;
    }

    // ---- int ----
    if (std::isnan(value) || std::isinf(value) || value < static_cast<double>(INT_MIN) || value > static_cast<double>(INT_MAX))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(value) << std::endl;

    // ---- float ----
    if (std::isnan(value))
        std::cout << "float: nanf" << std::endl;
    else if (std::isinf(value) || value > FLT_MAX || value < -FLT_MAX)
        std::cout << "float: " << (value < 0 ? "-inff" : "+inff") << std::endl;
    else
    {
        float f = static_cast<float>(value);
        if (f == std::floor(f))
            std::cout << std::fixed << std::setprecision(1) << "float: " << f << "f" << std::endl;
        else
            std::cout << std::setprecision(8) << "float: " << f << "f" << std::endl;
    }

    // ---- double ----
    if (std::isnan(value))
        std::cout << "double: nan" << std::endl;
    else if (std::isinf(value))
        std::cout << "double: " << (value < 0 ? "-inf" : "+inf") << std::endl;
    else
    {
        if (value == std::floor(value))
            std::cout << std::fixed << std::setprecision(1) << "double: " << value << std::endl;
        else
            std::cout << std::setprecision(8) << "double: " << value << std::endl;
    }
}

void ScalarConverter::convert(const std::string str)
{
    Type str_type = detect_type(str);

    switch (str_type)
    {
    case SPECIAL:
    {
        printAll(std::strtod(str.c_str(), 0)); // strtod parses "nan"/"-inf"/etc. directly
        break;
    }
    case CHAR:
    {
        char c = str[0];
        printAll(static_cast<double>(c));
        break;
    }
    case INT:
    {
        try
        {
            int value = convert_to_int(str);
            printAll(static_cast<double>(value));
        }
        catch (std::exception &e)
        {
            try
            {
                printAll(convert_to_double(str));
            }
            catch (std::exception &e2)
            {
                printImpossible();
            }
        }
        break;
    }
    case FLOAT:
    {
        try
        {
            float f_value = convert_to_float(str);
            printAll(static_cast<double>(f_value));
        }
        catch (std::exception &e)
        {
            try
            {
                printAll(convert_to_double(str));
            }
            catch (std::exception &e2)
            {
                printImpossible();
            }
        }
        break;
    }
    case DOUBLE:
    {
        try
        {
            double d_value = convert_to_double(str);
            printAll(d_value);
        }
        catch (std::exception &e)
        {
            printImpossible();
        }
        break;
    }
    case INVALID:
    {
        printImpossible();
        break;
    }
    }
}
