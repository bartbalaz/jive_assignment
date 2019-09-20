#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "common/log.h"

#define BUFFER_SIZE 1024
#define STACK_SIZE 8192

struct connection_info
{
  int client_fd;
  int connection_count;
  struct sockaddr_in client;
};


void *connection (void *arg)
{
  char buf[BUFFER_SIZE];
  int err;
  struct connection_info *info = (struct connection_info *) arg;

  LOG("Starting connection %d from: %s", info->connection_count, inet_ntoa((info->client.sin_addr)));
  
  while (1) {
    int read = recv(info->client_fd, buf, BUFFER_SIZE, 0);

    if (!read) {
      LOG("Finished connection %d from: %s", info->connection_count, inet_ntoa((info->client.sin_addr)));
      break; // done reading
    }
    ASSERT_E(read > 0, "Client read failed");

    err = send(info->client_fd, buf, read, 0);
    ASSERT_E(err >= 0, "Client write failed");

    LOG("Echoed (bytes %d), on connection %d", err, info->connection_count);
  }

  free(info);

  return NULL;
}



int server(int port)
{
	LOG("Starting server on port %d", port);
  
  int server_fd, client_fd, err, connection_count = 0;
  struct sockaddr_in server, client;
  pthread_attr_t attr;
  pthread_t thread;

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  ASSERT_E(server_fd > 0, "Could not create socket");

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  int opt_val = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

  err = bind(server_fd, (struct sockaddr *) &server, sizeof(server));
  ASSERT_E(err >= 0, "Could not bind socket");

  err = listen(server_fd, 128);
  ASSERT_E(err >= 0,"Could not listen on socket");

  LOG("Server is listening on %d", port);

  ASSERT_E(pthread_attr_init(&attr) == 0, "Could not innitialize pthread attributes");

  ASSERT_E(pthread_attr_setstacksize(&attr, STACK_SIZE) != 0,
          "Could not set pthread stack size");

  while (1) {
    socklen_t client_len = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);

    ASSERT_E(client_fd > 0,"Could not establish new connection");

    struct connection_info *info = malloc(sizeof(struct connection_info));
    info->client_fd = client_fd;
    info->connection_count = connection_count++;
    info->client = client;

    pthread_create( &thread, &attr, connection, (void*) info);
  }
}
