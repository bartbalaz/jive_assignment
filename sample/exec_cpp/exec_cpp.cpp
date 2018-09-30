#include <iostream>

#include "exec_cpp.hpp"
#include "lib_c/libfile_c.h"
#include "lib_cpp/libfile.hpp"


using namespace NameSpace;

Class_1::Class_1(int value): 
some_value(value)
{
}
		
void 
Class_1::object_printex(void)
{
	std::cout << "Some value is " << some_value << std::endl;			
} 


int main(int argc, char* argv[])
{
	Class_1 class_1(10);
    Class_2 class_2("Class too");
	
	class_1.object_printex();
	class_2.printName();
    
	::printer();
}
