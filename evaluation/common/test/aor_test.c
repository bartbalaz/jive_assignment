#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <libgen.h>
#include <string.h>


#include "common/aor.h"


int main(int argc, char *argv[])
{
  open_aor_file("input.json");

  aor_t *head = read_aor_file();

  close_aor_file();

  int log_file_handle = open("out.json", O_CREAT | O_TRUNC | O_RDWR,
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH  );

  while(head)
  {
    write(log_file_handle, head->content, strlen(head->content));
    head = head->next;
  }


  return 0;
}
