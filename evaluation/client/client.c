#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>

#include "common/log.h"
#include "client.h"

#define BUFFER_SIZE 1025

void client(const char* server_address_string, int port)
{
  int client_fd, received;  
  char buf[BUFFER_SIZE + 1];
  struct in_addr server_ip_address;
  struct sockaddr_in server_address; /* connector's address information */

  ASSERT_E(inet_aton(server_address_string, &server_ip_address) != 0,
      "Could not convert address '%s'", server_address)

  LOG("Creating client socket");
  client_fd = socket(AF_INET, SOCK_STREAM, 0);

  ASSERT_E(client_fd != -1, "Could not create client socket");
    
  server_address.sin_family = AF_INET;      
  server_address.sin_port = htons(port);    
  server_address.sin_addr = server_ip_address;
  bzero(&(server_address.sin_zero), 8);   

  LOG("Connecting to server %s on port %d", server_address_string, port)
  ASSERT_E(connect(client_fd, (struct sockaddr *)&server_address,
      sizeof(struct sockaddr)) != -1, "Could not connect to server");

  char *key = "0142e2fa3543cb32bf000100620002\r\n";

  LOG("Sending  to server %s on port %d", server_address_string, port)
  ASSERT_E(send(client_fd, key, strlen(key), 0) != -1,
    "Could not sent data");
 
  received = recv(client_fd, buf, BUFFER_SIZE, 0);

  ASSERT_E(received >= 0, "Could not receive any data from server");

  buf[received] = 0;

  LOG("Received data (%d) for key %s", strlen(buf), key);
  DUMP(buf);

  close(client_fd);
}
