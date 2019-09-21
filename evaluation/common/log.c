/*
 * Trivial thread safe single level logging facility
 *
 */

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
 
#include "log.h"

#define LOG_MESSAGE_SIZE 256


/* log global variables */
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

int log_file_handle = -1;

void open_log_file(const char* file_name) {
  log_file_handle = open(file_name, O_CREAT | O_TRUNC | O_RDWR,
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH  );
                    
  ASSERT_E(log_file_handle > 0, "Could not open log file %s", file_name);

  LOG("Log file %s opened!", file_name);

  void *void_ptr;
  ASSERT(sizeof(void_ptr) == 4, "Compilation in 64 bit mode is not supported!");
}

void close_log_file() {
  if(log_file_handle > 0) {
    LOG("Log file %s closed!");
    close(log_file_handle);
    log_file_handle = -1;
  } 
}

void dump(const char* file_name, const int line_num, const char* buffer)
{
  trivial_log(-1, file_name, line_num, "Beginning of dump");
  
  /* Ensure thread safe */
  pthread_mutex_lock(&log_mutex);

  /*
   * Dump on the console
   */
  printf("%s\n", buffer);

  if(log_file_handle > 0) {
    write(log_file_handle, buffer, strlen(buffer));
  }
  
  pthread_mutex_unlock(&log_mutex);

  trivial_log(-1, file_name, line_num, "End of dump");
}

void trivial_log(int error, const char* file_name,
  const int line_num, const char* format,...)
{

  
  char user_msg[LOG_MESSAGE_SIZE];
  char time_msg[LOG_MESSAGE_SIZE];
  char full_msg[LOG_MESSAGE_SIZE];
  char local_file_name[strlen(file_name)+1];
  strcpy(local_file_name, file_name);

  /*
   * Build the user message
   */
  va_list argptr;
  va_start(argptr, format);
  vsnprintf(user_msg, LOG_MESSAGE_SIZE, format, argptr);
  va_end(argptr);


  /*
   * Buld the time message
   */
  struct timeval now_val;
  time_t now_time;

  gettimeofday(&now_val, NULL);
  now_time = now_val.tv_sec;
  strftime(time_msg, LOG_MESSAGE_SIZE, "%Y/%m/%d,%H:%M:%S", localtime(&now_time));

  /*
   * Build the full message
   */
  if(error >= 0) {
    /* When errorno is present */
    snprintf(full_msg, LOG_MESSAGE_SIZE, "%s|F:%s|L:%d|M:%s|e:%d (%s)", time_msg,
          basename(local_file_name), line_num, user_msg, error, strerror(error));
  }
  else {
    /* Without errno */
    snprintf(full_msg, LOG_MESSAGE_SIZE, "T:%s|F:%s|L:%d|M:%s", time_msg,
          basename(local_file_name), line_num, user_msg);
  }

  /* Ensure thread safe */
  pthread_mutex_lock(&log_mutex);

  /*
   * Print the message on the console 
   */
  printf("%s\n", full_msg);

  if(log_file_handle > 0) {
    write(log_file_handle, full_msg, strlen(full_msg));
  }
  
  pthread_mutex_unlock(&log_mutex);
}
