#include <iostream>
#include "libfile.hpp"



Class_2::Class_2(const std::string &nicName): _nicName(nicName)
{}
     
void
Class_2::printName()
{
    std::cout << _nicName << std::endl;
}
