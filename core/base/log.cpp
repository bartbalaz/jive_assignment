
#include <sstream>
#include <iostream>
#include <libgen.h>
#include <string.h>
#include <stdarg.h>

#include "boost/date_time/posix_time/posix_time.hpp"

#include "exception.hpp"
#include "application.hpp"
#include "log.hpp"

namespace pt = boost::posix_time;

using namespace Bx::Base;

Log Log::_logInstance;

std::vector<std::string> Log::_levelVec = { "ftl", "err", "wrn", "inf", "dbg" };

std::string Log::_logLevelHelp;

std::string Log::_defaultLogLevel("dbg");

Log::Log():
_logLevel(dbg)
{
}

Log::~Log()
{
  file("");
}

void
Log::level(const char* logLevel)
{
  std::string logLevelString(logLevel);

  Log::level(logLevelString);
}

void
Log::level(std::string& logLevel)
{
  unsigned i(0);

  if(logLevel.size())
  {
    for(; i < _levelVec.size(); i++)
    {
      if(_levelVec[i] == logLevel)
      {
        break;
      }
    }
    if (_levelVec[i] == logLevel)
    {
      _logInstance._logLevel = (logLevel_t) i;
    }
  }
}

void
Log::level(logLevel_t logLevel)
{
  _logInstance._logLevel = logLevel;
}


void
Log::file(const char* name)
{
  std::string fileName(name);

  Log::file(fileName);
}

void
Log::file(std::string& name)
{
  pt::ptime localTime = pt::second_clock::local_time();
  
  if(_logInstance._logFile.is_open())
  {
    _logInstance._logFile << "Log file: " << name << " closed at "
      << pt::to_simple_string (localTime) << std::endl;
    
    _logInstance._logFile.close();
  }    

  if(name.size())
  {    
    _logInstance._logFile.open(name, std::ios::trunc | std::ios::out);

    if(_logInstance._logFile.is_open())
    {     
      _logInstance._logFile << "Log file: '" << name << "' opened at "
          << pt::to_simple_string (localTime) << std::endl 
          << "Application version information: " << std::endl
          << Application::appInfo() << std::endl;
    }
  }
}

void
Log::log(logLevel_t logLevel, int error, const char* pFileName,
  const int lineNum, const char* pFormat,...)
{ 
  if(logLevel <= _logInstance._logLevel)
  {
    char msg[core_msg_size];
    char fileName[::strlen(pFileName)+1];
    strcpy(fileName, pFileName);

    va_list argptr;
    va_start(argptr, pFormat);
    vsnprintf(msg, core_msg_size, pFormat, argptr);
    va_end(argptr);
       
    // Get current time stamp
    pt::ptime localTime = pt::second_clock::local_time();
    
    // Prepare the buffer
    std::stringstream ss;

    ss << _levelVec[logLevel] << "|"<< localTime.date().year() << "/"
      << localTime.date().month()
      << "/" << localTime.date().day()
      << "|" << localTime.time_of_day().hours()
      << ":" << localTime.time_of_day().minutes()
      << ":" << localTime.time_of_day().seconds() << "|"
      << ::basename(fileName) << "(" << lineNum << "):"
      << msg;
      
    if(error >= 0)
    {
      ss << " e:" << error << "(" << strerror(error) << ")";
    }
    ss << std::endl;

    std::cout << ss.str();

    if(_logInstance._logFile.is_open())
    {
      _logInstance._logFile << ss.str();
    }
  }
}

std::string&
Log::logLevelHelp()
{
  if (!_logLevelHelp.size())
  {
    for(std::vector<std::string>::const_iterator i = _levelVec.begin();
      i != _levelVec.end(); i++)
    {
      _logLevelHelp += (i == _levelVec.begin() ? "" : ", ") + (*i);
    }
       
    _logLevelHelp += "\ndefault: " + _defaultLogLevel;
  }
  return _logLevelHelp;
}

std::string&
Log::defaultLogLevel()
{
  return _defaultLogLevel;
}
