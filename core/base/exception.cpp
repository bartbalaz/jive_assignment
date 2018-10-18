

#include <libgen.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "exception.hpp"

using namespace Bx::Base;

Exception::Exception(const char* pFileName, const int lineNum,
    const int error, const char* pFormat,...)
{
  char header[header_size];
  char body[body_size];
  char fileName[::strlen(pFileName)+1];
  strcpy(fileName, pFileName);

  
  va_list argptr;
  va_start(argptr, pFormat);
  
  snprintf(header, header_size, "%s(%d),e=%d(%s):", ::basename(fileName),
    lineNum, error, strerror(errno));
  vsnprintf(body, body_size, pFormat, argptr);
  va_end(argptr);

  snprintf(_pMsg, header_size + body_size, "E{%s%s}", header, body);
}
    

Exception::Exception(const char* pFileName, const int lineNum,
    const char* pFormat,...)
{
  char header[header_size];
  char body[body_size];
  char fileName[::strlen(pFileName)+1];
  strcpy(fileName, pFileName);

  va_list argptr;
  va_start(argptr, pFormat);
  
  snprintf(header, header_size, "%s(%d):", basename(fileName),
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

      
