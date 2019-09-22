#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <poll.h>

#include "common/log.h"
#include "common/aor.h"

#define BUFFER_SIZE 1025
#define STACK_SIZE 8192
#define TIMEOUT 10000  /* in ms */

struct connection_info
{
  int client_fd;
  int connection_count;
  struct sockaddr_in client;
};

typedef struct req {
  const char *key;
  struct req *next;
} req_t;

/*
 *  Returns read offset
 */
unsigned long process_request(int client_fd, char* request)
{
  unsigned long read_offset = 0;

  LOG("Processing request '%s' (%d)", request, strlen(request));
  
  /* veryfy if we have received a well formed request */
  char* start = request;
  char* end = strstr(request, "\r\n");
  
  while(end) {
    
    /* end point at the '\r', let's make an end of string here */
    end[0] = 0;
    
    LOG("Looking up key '%s' (%d)", start, strlen(start))

    aor_t* aor = get_first_aor(start);

    if(aor) {
      while(aor) {
          LOG("Found aor key %s", aor->key);
          DUMP(aor->content);

          ASSERT_E( send(client_fd, aor->content, strlen(aor->content), 0) > 0,
             "Could not send response" );

          /* Verify if there are multiple aors for this key */
          aor = get_next_aor(aor);
      }
    }
    else {
     LOG("Did not find aor");

      /* There were no aors for this key, let's send a CRLF */
      ASSERT_E(send(client_fd, "\r\n", 2, 0)>0, "Could not send response"); 
    }
    

    /* skip the CRLF, after, end and start either point at EOS or
     * the beginning of the next request
     */
    end += 2; 
    start = end;
    
    /* Try to find a new termination symbol */
    end = strstr(start, "\r\n");
  }

  /* verify if there were not partial requests */
  if(strlen(start)) {
    /* The offset will be equivalent to the amount of incomplete request
     */
    read_offset = strlen(start);
    memmove(request, start, read_offset);

    LOG("Incomplete or partial request offset %d", read_offset);    
  }

  return read_offset;
}


void *connection (void *arg)
{
  char buf[BUFFER_SIZE + 1];
  struct connection_info *info = (struct connection_info *) arg;

  LOG("Starting connection %d from: %s", info->connection_count, inet_ntoa((info->client.sin_addr)));

  unsigned long read_offset = 0;
  
  while (1) {
    struct pollfd poll_record;

    poll_record.fd = info->client_fd;
    poll_record.events = POLLIN;

    poll(&poll_record, 1, TIMEOUT);
    
    if(poll_record.revents == POLLIN) {
      
      int read = recv(info->client_fd, buf + read_offset, BUFFER_SIZE - 1, 0);
      LOG("Client connection %d, received %d bytes",
          info->connection_count, read);

      if (!read) {
        LOG("Client requested to terminate connection %d from: %s",
            info->connection_count, inet_ntoa((info->client.sin_addr)));
        break; // done reading
      }
      ASSERT_E(read > 0, "Client read failed");

      /* Make the buffer safe for str functions */
      buf[read_offset+read] = 0;

      read_offset = process_request(info->client_fd, buf);
    }
    else {
      LOG("Client connection %d from: %s timed out", info->connection_count,
            inet_ntoa((info->client.sin_addr)));
      close(info->client_fd);
      break;
    }
  }

  free(info);

  return NULL;
}



void server(int port, const char* aor_file_name)
{
  LOG("Reading aor file '%s'", aor_file_name)

  open_aor_file(aor_file_name);

  read_aor_file();

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
