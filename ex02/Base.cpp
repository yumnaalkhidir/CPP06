#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <exception>
#include <iostream>
#include "Base.hpp"
#include <cstdlib>

Base::~Base(){}

Base* generate(void)
{
    int num = rand() % 3;
    std::cout << " num is: " << num << std::endl;
    if (num == 0)
        return (new A());
    else if (num == 1)
        return (new B());
    else
        return (new C());
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p) != NULL)
    {
        std::cout << "A" << std::endl;
        return ;
    }
    else if (dynamic_cast<B*>(p) != NULL)
    {
        std::cout << "B" << std::endl;
        return ;
    }
    else if (dynamic_cast<C*>(p) != NULL)
    {
        std::cout << "C" << std::endl;
        return ;
    }
    else 
        return ;
}

void identify(Base& p)
{
    try
    {
        dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return ;
    }
    catch (std::exception &e){}

    try
    {
        dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return ;
    }
    catch (std::exception &e){}

    try
    {
        dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return ;
    }
    catch (std::exception &e){}
}
