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
#include "common/log.h"

const char *existing_aors[5] =
{
  "0142e2fa3543cb32bf000100620002",
  "015403d9ebdff17c55000100620007",
  "UlkLaWL9dICuwpewUOJjYqh6slA6m2",
  "73XbKT9NJJ0tiI4t04CLrEwGmTeQta",
  "01546f59a9033db700000100610001"
};

const char *inexistent_aors[5] =
{
  "dupazbitaasdfasdfasdfasdfasdfd",
  "015403d9ebdff17c5",
  "UlkLaWL9dICuwpewUOJjYqsadfasdfasdh6slA6m2",
  "73XbKT9NJ   I4t04CLrEwGmTeQta",
  "01546f59axhskrtlrtq kupka10001"
};

const char *duplicate_aors[3] =
{
  "01552608338f396a57000100610001",
  "014d911f8553f09461000100620002",
  "0153e75f78453cfc55000100620007"
};

int main(int argc, char *argv[])
{
  LOG("Starting aor test");
    
  open_aor_file("input.json");

  read_aor_file();

  close_aor_file();

  dump_all_aors_to_file("out.json");

  LOG("Trying existing aors");

  for(int i = 0; i < 5; i++)
  {
    const char *key = existing_aors[i];

    LOG("Looking for key '%s'", key);
    
    aor_t* aor = get_first_aor(key);

    if(aor)
    {
      LOG("Ok: Found aor for key '%s'", aor->key);
      
      if( (aor = get_next_aor(aor)) ) {
        LOG("Error: Found a duplicate aor for key '%s'", aor->key);
      }
      else {
        LOG("Ok: No duplicate aor found for key '%s'", key);
      }
    }
    else {
      LOG("Error: aor not found for key '%s'", key);
    }
  }

  LOG("Trying inexistent aors");

  for(int i = 0; i < 5; i++)
  {
    const char *key = inexistent_aors[i];

    LOG("Looking for key '%s'", key);
    
    aor_t* aor = get_first_aor(key);

    if(aor)
    {
      LOG("Error: Found aor for key '%s'", aor->key);
    }
    else {
      LOG("Ok: aor not found for key '%s'", key);
    }
  }

  LOG("Trying duplicate aors");

  for(int i = 0; i < 3; i++)
  {
    const char *key = duplicate_aors[i];

    LOG("Looking for key '%s'", key);
    
    aor_t* aor = get_first_aor(key);

    if(aor)
    {
      LOG("Ok: Found aor for key '%s'", aor->key);

      if( (aor = get_next_aor(aor)) ) {
        LOG("Ok: Found a duplicate aor for key '%s'", aor->key);
      }
      else {
        LOG("Error: No duplicate aor found for key '%s'", key);
      }
    }
    else {
      LOG("Error: aor not found for key '%s'", key);
    }
  }
  
  return 0;
}
