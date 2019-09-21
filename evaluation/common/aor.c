#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#include "aor.h"
#include "log.h"

int file_handle = -1;

#define BUFFER_SIZE 128
#define HASH_TABLE_SIZE 997 /* Preferably use prime values */

aor_t *aor_hash_table[HASH_TABLE_SIZE];

unsigned int calc_hash(const char* key)
{
  /* Simple and stupid hash function, that adds all the chars of the
   * key
   */
  unsigned int hash = 0;
  
  for(int i = 0; i < strlen(key); i++) {
    hash += key[i];
  }

  return hash % HASH_TABLE_SIZE;
}

/* For testing purposes */
void dump_all_aors_to_file(const char* filename)
{
  int dump_file_handle = open("out.json", O_CREAT | O_TRUNC | O_RDWR,
                          S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH  );

  ASSERT_E(dump_file_handle > 0, "Could not open dump file");

  aor_t *aor = NULL;

  for(int i = 0; i < HASH_TABLE_SIZE; i++)
  {
    aor = aor_hash_table[i];
    while(aor)
    {
      write(dump_file_handle, aor->content, strlen(aor->content));
      aor = aor->next;
    }
  }

  close(dump_file_handle);
}

void open_aor_file(const char* filename)
{
  ASSERT(file_handle == -1, "File already opened");

  file_handle = open(filename, O_RDONLY);

  /* clear the hash table */
  for(int i = 0; i < HASH_TABLE_SIZE; i++) {
    
    aor_hash_table[i] = NULL;
  }

  ASSERT_E(file_handle > 0, "Could not open file");
}

aor_t*
get_first_aor(const char* key)
{
  unsigned int hash = calc_hash(key);

  aor_t* aor = aor_hash_table[hash];

  /* Does the hash entry contain a value? */
  while(aor) {
    /* Is the key we are looking for? */
    if(!strcmp(aor->key, key))
    {
      break;
    }
    aor = aor->next;
  }

  return aor;
}

aor_t*
get_next_aor(aor_t* aor)
{
  const char* key = aor->key;
  aor = aor->next;
  
  if( (aor!= NULL) && (strcmp(aor->key, key)) )
  {
    /* The next key is different, there are no more structs with
     * the same key
     */
    aor = NULL;
  }
  
  return aor;
}

void read_aor_file()
{
  ASSERT(file_handle > 0, "File not opened");
 
  int read_chars = 0;
  int total_read_chars = 0;
  int work_buffer_size = BUFFER_SIZE;
  char *work_buffer = (char*)malloc(work_buffer_size + 1);
  work_buffer[work_buffer_size] = 0;
  char *start;
  char *end;


  while ( (read_chars = read(file_handle, work_buffer+total_read_chars,
                  work_buffer_size - total_read_chars)) ) {

    total_read_chars += read_chars;
    
    /* Try to see if we have both start and end symbols */
    start = strchr(work_buffer, '{');
    end = strchr(work_buffer, '}');

    if(!start || !end) {
      /* The work_buffer does not have enough room for the record,
       * need to double the buffer size
       */
      work_buffer_size *= 2;
      work_buffer = (char*) realloc(work_buffer, work_buffer_size + 1);
      work_buffer[work_buffer_size] = 0;
    }
    
    while(start && end) {
      
      
      /* We have a complete record, create a content, need to add 2 to compensage for the line termination */
      unsigned long long content_size = ((unsigned long long) end - (unsigned long long) start) + 2;

      /* Allocating size +1 byte for null termination */
      char* content = (char*) malloc (content_size + 1);
      memcpy(content, start, content_size);
      content[content_size] = 0;

      /* Shift the work buffer by the size of the current structure */
      memmove(work_buffer, work_buffer + content_size, work_buffer_size - content_size);
      memset(work_buffer + work_buffer_size - content_size, 0, content_size);

      /* Let's try to get start and end in the remaining buffer */
      start = strchr(work_buffer, '{');
      end = strchr(work_buffer, '}');

      /* Adjust the values */
      total_read_chars -= content_size;

      /* Structure processing */

      /* Let's search for the "addressOfRecord" key */
      char *cursor = strstr(content, "addressOfRecord");
      
      ASSERT(cursor != NULL, "Line read does not have address of record field");

      /* Let's search for the separator now i.e ":" */
      cursor = strchr(cursor, ':');

      ASSERT(cursor != NULL, "Could not find separator");

      /* Let's search for the begining of the value i.e. '"' */
      cursor = strchr(cursor, '"');

      ASSERT(cursor != NULL, "Could not find value");

      /* Move to the first byte of the aor value */
      cursor++;

      /* Let's find the end of the value i.e. the '"' character */
      char *end_of_value = strchr(cursor, '"');

      ASSERT(end_of_value != NULL, "Could not find end of value");

      /* Create the key value */
      content_size = ((unsigned long long)end_of_value - (unsigned long long)cursor);

      char* key = (char*) malloc (content_size + 1);
      memcpy(key, cursor, content_size);
      key[content_size] = 0;

      /* Create the output data strcutre */
      aor_t *aor = (aor_t*)malloc(sizeof(aor_t));
        
      aor->key = key;

      aor->content = content;

      unsigned int hash = calc_hash(key) ;

      aor->next = NULL;

      /* Store the entry in the hash table */
      aor_t *head = aor_hash_table[hash];

      if(head == NULL) {
        /* Hash table entry is empty */
        aor_hash_table[hash] = aor;
      }
      else {
        while(head->next) {
          if(!strcmp(head->key, aor->key))
          {
            /* Duplicate entries are stored next to each others,
             * so in case of duplication we'll be able to return
             * muptiple structures */
            LOG("Duplicate entry, storing anyways key='%s'", aor->key);
            aor->next = head->next;
            break;
          }
          head = head->next;
        }
        head->next = aor;
      }
    }
  }
}
  

void close_aor_file()
{
  ASSERT(file_handle > 0, "File already closed");

  close(file_handle);

  file_handle = -1;
}
