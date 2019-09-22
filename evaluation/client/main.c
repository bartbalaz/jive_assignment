#include <stdio.h>
#include <stdlib.h>


#include "common/log.h"
#include "client.h"

int main(int argc, char* argv[])
{
  int ret = 0;

  if(argc != 3) {
    LOG("Usage: %s <server_address> <port_number>\n", argv[0]);
    ret = 1;
  }
  else {
    int port = atoi(argv[2]);

    if(port < 1024 || port > 64000)
    {
      LOG("port_number (%s), must be a value between 1024 and 6400\n", argv[2]);
      ret = 1;
    }
    else {
      open_log_file("client.log");
      client(argv[1], port);
    }
  }
	
	return ret;
}
