#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <cstdlib>
#include <cerrno>
#include <iostream>
#include <cmath>
#include <climits>
#include <limits>
#include <iomanip>
#include <cfloat>

class ScalarConverter
{
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter &copy);
    ScalarConverter &operator=(const ScalarConverter &other);
    ~ScalarConverter();

public:
    static void convert(const std::string str);
};

enum Type
{
    CHAR,
    INT,
    DOUBLE,
    FLOAT,
    SPECIAL,
    INVALID
};

bool is_int(const std::string &str);
bool is_double(const std::string &str);
bool is_float(const std::string &str);
Type detect_type(const std::string &str);
int convert_to_int(const std::string &str);
double convert_to_double(const std::string &str);
float convert_to_float(const std::string &str);

#endif