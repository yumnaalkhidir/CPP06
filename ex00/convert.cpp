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
    double value = std::strtod(str.c_str(), &end);

    if (errno == ERANGE || std::isinf(value))
        throw std::overflow_error("float overflow");
    if (value > FLT_MAX || value < -FLT_MAX)
        throw std::overflow_error("float overflow");
    return static_cast<float>(value);
}

