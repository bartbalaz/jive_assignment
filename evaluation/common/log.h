/*
 * Trivial thread safe single level logging facility
 *
 */

#ifdef __cplusplus
extern "C" {
#endif


#include <errno.h>


void open_log_file(const char* log_file);

void close_log_file();

void trivial_log(int error, const char* file_name,
  const int line_num, const char* format,...);

/* All the macros that contain the "_E" suffix add the value
 * of errno to the log message.
 */

/* Log macros */

#define LOG(ARGS...) \
{ trivial_log(-1, __FILE__, __LINE__, ARGS); }

#define LOG_E(ARGS...) \
{ trivial_log(errno, __FILE__, __LINE__, ARGS); }


/* Abort macros, that abort the exectuion */

#define ABORT(ARGS...) \
{ \
  trivial_log(-1, __FILE__, __LINE__, ARGS); \
  exit(1); \
} 

#define ABORT_E(ARGS...) \
{ \
  trivial_log(errno, __FILE__, __LINE__, ARGS); \
  exit(1); \
} 

/* Assert macros, that will abort the exectuion in case of failure */

#define ASSERT(EXPRESSION, ARGS...) \
  if(!(EXPRESSION)) { ABORT(ARGS); }

#define ASSERT_E(EXPRESSION, ARGS...) \
  if(!(EXPRESSION)) { ABORT_E(ARGS); }



#ifdef __cplusplus
}
#endif


 
