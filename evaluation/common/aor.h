/*
 * This is a very basic JSON parser it extracts the addressOfrecord field
 * that is set as the key and stores the entire structure in the content
 * field.
 */

#ifdef __cplusplus
extern "C" {
#endif


typedef struct aor_s {
  char *key;
  char *content;
  struct aor_s *next; 
} aor_t; 


void open_aor_file(const char* filename);

void read_aor_file();

void dump_all_aors_to_file(const char* filename);

aor_t* get_first_aor(const char* key);

aor_t* get_next_aor(aor_t* aor);

void close_aor_file();

#ifdef __cplusplus
}
#endif
