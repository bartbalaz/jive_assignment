#include <stdio.h>

#include "lib_c/libfile_c.h"
#include "exec_file_1.h"

int main(int argc, char* argv[])
{
	printf("Hello from executable!\n");

	function_1();
	
	printer(1);
	
	return 0;
}


