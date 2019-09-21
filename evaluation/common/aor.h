/*
 * This is a very basic JSON parser it extracts the addressOfrecord field
 * that is set as the key and stores the entire structure in the content
 * field.
 */


typedef struct aor_s {
  char *key;
  char *content;
  struct aor_s *next; 
} aor_t; 


void open_aor_file(char* filename);

void read_aor_file();

void close_aor_file();
