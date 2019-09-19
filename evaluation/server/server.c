#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>


#define BUFFER_SIZE 1024
#define SPOOL_BUFFER 1024


#define on_error(...) { fprintf(stderr, __VA_ARGS__); if(log_file > 0) close(log_file); fflush(stderr); return 1; }

int server(int port, const char* spool_file_name)
{
	printf("Starting server on port %d\n", port);
  
  int server_fd, client_fd, err, char_count;
  struct sockaddr_in server, client;
  char buf[BUFFER_SIZE];
  char spool_buffer[SPOOL_BUFFER];

  /* Open the file log file */
  int log_file = open(spool_file_name, O_CREAT | O_TRUNC | O_RDWR,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH  );
  if (log_file <= 0 ) on_error("Could not open file %s\n", spool_file_name);

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) on_error("Could not create socket\n");

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  int opt_val = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

  err = bind(server_fd, (struct sockaddr *) &server, sizeof(server));
  if (err < 0) on_error("Could not bind socket\n");

  err = listen(server_fd, 128);
  if (err < 0) on_error("Could not listen on socket\n");

  printf("Server is listening on %d\n", port);

  while (1) {
    socklen_t client_len = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);

    if (client_fd < 0) on_error("Could not establish new connection\n");

    char_count = snprintf(spool_buffer, SPOOL_BUFFER, "Starting connection from: %s\n",
                  inet_ntoa((client.sin_addr)));
                  
    write(log_file, spool_buffer, char_count);

    while (1) {
      int read = recv(client_fd, buf, BUFFER_SIZE, 0);

      if (!read) {
        char_count = snprintf(spool_buffer, SPOOL_BUFFER, "Finished connection from: %s\n",
                  inet_ntoa((client.sin_addr)));
        write(log_file, spool_buffer, char_count);
        break; // done reading
      }
      if (read < 0) on_error("Client read failed\n");

      err = send(client_fd, buf, read, 0);
      if (err < 0) on_error("Client write failed\n");

      char_count = snprintf(spool_buffer, SPOOL_BUFFER, "Echoed (%d)\n\%s", err, buf);
      write(log_file, spool_buffer, char_count);
    }
  }
}
