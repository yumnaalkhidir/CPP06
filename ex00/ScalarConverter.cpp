#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& copy) {(void)copy;}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other){(void)other; return (*this);}
ScalarConverter::~ScalarConverter() {}


void ScalarConverter::convert(const std::string str)
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
            std::cout << "NO TYPE" << std::endl;
            std::cout << "char: " << "Impossible" << std::endl;
            std::cout << "int: " << "Impossible" << std::endl;
            std::cout << "double: " << "Impossible" << std::endl;
            std::cout << "float: " << "Impossible" << std::endl;
            break ;
        }
    }
}
