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
#include "common/aor.h"
#include "client.h"

#define BUFFER_SIZE 2048



char *simple_requests[12] = {
   // simple aors 
  "0142e2fa3543cb32bf000100620002\r\n",
  "015403d9ebdff17c55000100620007\r\n",
  "UlkLaWL9dICuwpewUOJjYqh6slA6m2\r\n",
  "73XbKT9NJJ0tiI4t04CLrEwGmTeQta\r\n",
  "01546f59a9033db700000100610001\r\n",

   // missing aors
  "dupazbitaasdfasdfasdfasdfasdfd\r\n",
  "015403d9ebdff17c5\r\n",
  "UlkLaWL9dICuwpewUOJjYqsadfasdfasdh6slA6m2\r\n",
  "73XbKT9NJ   I4t04CLrEwGmTeQta\r\n",

   // multiple aors
  "01552608338f396a57000100610001\r\n",
  "014d911f8553f09461000100620002\r\n",
  "0153e75f78453cfc55000100620007\r\n"
};

char *broken_request[4] = {
  "014",
  "2e2fa3543cb3",
  "2bf0001",
  "00620002\r\n",
};

char *simultaneous_request =
  "0142e2fa3543cb32bf000100620002\r\n015403d9ebdff17c55000100620007\r\n";

  


void client(const char* server_address_string, int port)
{
  char *key = NULL;
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

  LOG("---- Simple requests");
  for(int i = 0; i < 12; i++) {
    key = simple_requests[i];

    LOG("Sending  to server %s on port %d", server_address_string, port)
    ASSERT_E(send(client_fd, key, strlen(key), 0) != -1,
      "Could not sent data");
    sleep(1);
    
    received = recv(client_fd, buf, BUFFER_SIZE, 0);
    ASSERT_E(received >= 0, "Could not receive any data from server");

    buf[received] = 0;
    LOG("Received data (%d) for key %s", strlen(buf), key);
    DUMP(buf);
    sleep(1);
  }

  LOG("----- Broken requests");
  for(int i = 0; i < 4; i++) {
    key = broken_request[i];

    LOG("Sending  to server %s on port %d", server_address_string, port)
    ASSERT_E(send(client_fd, key, strlen(key), 0) != -1,
      "Could not sent data");
    sleep(1);
  }

  received = recv(client_fd, buf, BUFFER_SIZE, 0);
  ASSERT_E(received >= 0, "Could not receive any data from server");

  buf[received] = 0;
  LOG("Received data (%d) for key %s", strlen(buf), key);
  DUMP(buf);
  sleep(1);

  LOG("----- Simultaneous requests");
  key = simultaneous_request;
  LOG("Sending  to server %s on port %d", server_address_string, port)
  ASSERT_E(send(client_fd, key, strlen(key), 0) != -1,
    "Could not sent data");
  sleep(1);

  received = recv(client_fd, buf, BUFFER_SIZE, 0);
  ASSERT_E(received >= 0, "Could not receive any data from server");

  buf[received] = 0;
  LOG("Received data (%d) for key %s", strlen(buf), key);
  DUMP(buf);

  received = recv(client_fd, buf, BUFFER_SIZE, 0);
  ASSERT_E(received >= 0, "Could not receive any data from server");

  if(received == 0) {
    LOG("Server has closed the connection");
  }
  else{
    buf[received] = 0;
    LOG("Received data (%d) for key %s", strlen(buf), key);
    DUMP(buf);
  }
}



