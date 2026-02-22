#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include <stdint.h>
class Serialization
{
    private:
        Serialization();
        Serialization(const Serialization& copy);
        Serialization& operator=(const Serialization& other);
        ~Serialization();
    public:
        struct Data{
            int number;
        };
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
};
#endif