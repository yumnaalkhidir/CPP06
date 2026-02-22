#include "Base.hpp"
#include <cstdlib>
#include <ctime>

int main(void)
{
    srand(time(0));
    Base* random = generate();
    identify(random);
    Base &refere = *random;
    identify(refere);
    delete random;
}