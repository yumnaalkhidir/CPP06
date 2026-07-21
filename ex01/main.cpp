#include <iostream>
#include "Serialization.hpp"

int main(void)
{
    Serialization::Data *ptr = new Serialization::Data();
    std::cout << "Data address: " << ptr << std::endl;
    ptr->number = 4;
    std::cout << "Data->number: " << ptr->number << std::endl;

    uintptr_t data_int = Serialization::serialize(ptr);
    std::cout << data_int << std::endl;
    if (data_int == reinterpret_cast<uintptr_t>(ptr))
        std::cout << "same" << std::endl;
    Serialization::Data *value = Serialization::deserialize(data_int);
    std::cout << "Value address: " << value << std::endl;
    std::cout << "Value->number: " << value->number << std::endl;    
    delete ptr;

}
