#include <stdio.h>
#include <stdlib.h>


#include "common/log.h"
#include "client.h"

int main(int argc, char* argv[])
{
  int ret = 0;

  if(argc != 4) {
    LOG("Usage: %s <server_address> <port_number> <test_cycle>\n", argv[0]);
    ret = 1;
  }
  else {
    int port = atoi(argv[2]);
    int test_cycle = atoi(argv[3]);

    if(port < 1024 || port > 64000)
    {
      LOG("port_number (%s), must be a value between 1024 and 6400\n", argv[2]);
      ret = 1;
    }
    else if(test_cycle != 1) {
      LOG("test_cycle must be 1, 2 or 3", argv[2]);
      ret = 1;      
    }
    else {
      open_log_file("client.log");
      client(argv[1], port);
    }
  }
	
	return ret;
}
