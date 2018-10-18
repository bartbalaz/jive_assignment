

#include <libgen>

#include "exception.hpp"

using namespace Bx::Basic;

Exception::Exception(const char* pFileName, const int lineNum,
    const int errno, const char* pFormat...)
{
  char header[header_size];
  char body[body_size];
  
  va_list argptr;
  va_start(argptr, pFormat);
  
  snprintf(header, header_size, "%s(%d),e=%d(%s):", ::basename(pFileName),
    lineNum, errno, strerror(errno))
  vsnprintf(body, body_size, pFormat, argptr);
  va_end(argptr)

  snprintf(_pMsg, header_size + body_size, "E{%s%s}", header, body);
}
    

Exception::Exception(const char* pFileName, const int lineNum,
    const char* pFormat...)
{
  char header[header_size];
  char body[body_size];

  va_list argptr;
  va_start(argptr, pFormat);
  
  snprintf(header, header_size, "%s(%d):", basename(pFileName),
    lineNum);
  vsnprintf(body, body_size, pFormat, argptr);
  va_end(argptr);
  
  snprintf(_pMsg, header_size + body_size, "E{%s%s}", header, body);
}


const char*
Exception::what()
{
  return _pMsg;
}

      
