#include "Serialization.hpp"


uintptr_t Serialization::serialize(Data* ptr)
{
    uintptr_t int_ptr = reinterpret_cast<uintptr_t>(ptr);
    return (int_ptr);
}

Serialization::Data* Serialization::deserialize(uintptr_t raw)
{
    Data *ptr = reinterpret_cast<Data*>(raw);
    return (ptr);
}
