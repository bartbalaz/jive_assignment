#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


 

#include "json.h"
#include "log.h"

int file_handle = -1;

#define BUFFER_SIZE 128


void open_json_file(char* filename)
{
    ASSERT(file_handle == -1, "File already opened");

    file_handle = open(filename, O_RDONLY);


    ASSERT_E(file_handle > 0, "Could not open file");
}

json_object* read_json_file()
{
  ASSERT(file_handle > 0, "File not opened");
 
  int read_chars = 0;
  int total_read_chars = 0;
  int work_buffer_size = BUFFER_SIZE;
  char *work_buffer = (char*)malloc(work_buffer_size + 1);
  work_buffer[work_buffer_size] = 0;
  char *start;
  char *end;
  json_object *head = NULL;
  json_object *tail = NULL;


  while ( (read_chars = read(file_handle, work_buffer+total_read_chars,
                  work_buffer_size - total_read_chars)) ) {


    total_read_chars += read_chars;

    LOG("Read %d from file, work_buffer_size %d, total read_chars %d",
        read_chars, work_buffer_size, total_read_chars);

    
    /* Try to see if we have both start and end symbols */
    start = strchr(work_buffer, '{');
    end = strchr(work_buffer, '}');

    if(!start || !end) {
       
      /* The work_buffer does not have enough room for the record */
      work_buffer_size *= 2;
      work_buffer = (char*) realloc(work_buffer, work_buffer_size + 1);
      work_buffer[work_buffer_size] = 0;
      LOG("We coudn't read whole record, resising to %d", work_buffer_size);
    }
    
    while(start && end) {
            
      /* We have a complete record, create a content */
      unsigned long long content_size = ((unsigned long long) end - (unsigned long long) start) + 2;
      
      char* content = (char*) malloc (content_size + 1);
      memcpy(content, start, content_size);
      content[content_size] = 0;

      /* Shift the work buffer */

      memmove(work_buffer, work_buffer + content_size, work_buffer_size - content_size);
      memset(work_buffer + work_buffer_size - content_size, 0, content_size);

      /* Let's try to get start and end in the remaining buffer */
      start = strchr(work_buffer, '{');
      end = strchr(work_buffer, '}');

      /* Adjust the values */
      total_read_chars -= content_size;


      /* Let's search for the "addressOfRecord" key */
      char *cursor = strstr(content, "addressOfRecord");
      
      ASSERT(cursor != NULL, "Line read does not have address of record field");

      /* Let's search for the separator now i.e ":" */
      cursor = strchr(cursor, ':');

      ASSERT(cursor != NULL, "Could not find separator");

      /* Let's search for the begining of the value i.e. '"' */
      cursor = strchr(cursor, '"');

      ASSERT(cursor != NULL, "Could not find value");

      cursor++;

      /* Let's find the end of the value i.e. the '"' character */
      char *end_of_value = strchr(cursor, '"');

      ASSERT(end_of_value != NULL, "Could not find end of value");

      /* Create the key value */
      content_size = (unsigned long long)end_of_value - (unsigned long long)cursor;

      LOG("Key size is %lu", content_size);

      char* key = (char*) malloc (content_size + 1);

      memcpy(key, cursor, content_size);

      key[content_size] = 0;

      /* Create the output data strcutre */
      json_object *obj = (json_object*)malloc(sizeof(json_object));

      obj->key = key;

      obj->content = content;

      obj->next = NULL;

      LOG("Read addressOfRecord with key '%s' and content:", obj->key);

      DUMP(obj->content);

      if(!head){
        head = obj;
        tail = obj;
      }
      else {
        tail->next = obj;
        tail = obj;
      }
    }
  }

  return head;
}
  

void close_json_file()
{
  ASSERT(file_handle > 0, "File already closed");

  close(file_handle);

  file_handle = -1;
}
