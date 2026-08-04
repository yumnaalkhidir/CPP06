#include <cstdlib>
#include <iostream>

int main()
{
    int num = 358732483;
    char *ch = reinterpret_cast<char *>(&num);

    std::cout << "Number: " << num << std::endl;
    std::cout << "Address: " << &num << std::endl;
    // std::cout << "Ch: " << int(*(ch + 1)) << std::endl;
    // std::cout << std::hex;
    std::cout << "Ch: " << int(ch[0] ) << std::endl;
    std::cout << "Ch: " << int(ch[1] ) << std::endl;
    std::cout << "Ch: " << int(ch[2] ) << std::endl;
    std::cout << "Ch: " << int(ch[3] ) << std::endl;

}