#include <stdio.h>
#include <stdlib.h>

#include "common/log.h"
#include "server.h"

int main(int argc, char* argv[])
{
  int ret = 0;

  if(argc != 3) {
    printf("Usage: %s <port_number> <aor_file>\n", argv[0]);
    ret = 1;
  }
  else {
    int port = atoi(argv[1]);

    if(port < 1024 || port > 64000)
    {
      printf("port_number (%s), must be a value between 1024 and 6400\n", argv[1]);
      ret = 1;
    }
    else {
      open_log_file("server.log");
      server(port, argv[2]);
    }
  }
	
	return ret;
}


