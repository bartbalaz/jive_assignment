/*
 * This is a very basic JSON parser it extracts the addressOfrecord field
 * that is set as the key and stores the entire structure in the content
 * field.
 */


typedef struct json_object_s {
  char *key;
  char *content;
  struct json_object_s *next; 
} json_object; 


void open_json_file(char* filename);

json_object* read_json_file();

void close_json_file();
