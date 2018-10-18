
#include <sstream>
#include <iostream>
#include <libgen>

#include "boost/date_time/posix_time/posix_time.hpp" 
#include "exception.hpp"
#include "application.hpp"
#include "log.hpp"

namespace pt boost::posix_time;

using namespace Bx::Basic;

Log::_logInstance;

vector<string> Log::_levelVec = { "ftl", "err", "wrn", "inf", "dbg" };

Log::Log():
_logLevel(dbg),
{
}

Log::level(string& logLevel)
{
  int i(0);

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
      _logInstance._level = _levelTbl[i];
    }
  }
}

Log::level(logLevel_t logLevel)
{
  _logInstance._level = logLevel;
}

void
Log::file(std::string& name)
{
  if(name.size())
  {
    if(_logInstance._logFile.is_open())
    {
      _logInstance._logFile << "Log file: " << name << " closed at "
      << pt::to_simple_string (localTime) << std::endl;
      
      _logInstance._logFile.close();
    }

    _logInstance._logFile.open(name, ios::trunc);

    if(_logInstance._logFile.is_open())
    {
      pt::ptime localTime = pt::second_clock::local_time();

      _logInstance._logFile << "Log file: " << name << " opened at "
          << pt::to_simple_string (localTime) << std::endl
          << "Application info: " << Application::appInfo() << std::endl;
    }
  }
}

void
Log::log(logLevel_t logLevel, int errno, const char* pFileName,
  const int lineNum, const char* pFormat...)
{ 
  if(logLevel <= _logInstance._logLevel)
  {
    char msg[core_msg_size];
    
    va_list argptr;
    va_start(argptr, pFormat);
    vsnprintf(msg, core_msg_size, pFormat, argptr);
    va_end(argptr)
       
    // Get current time stamp
    pt::ptime localTime = pt::second_clock::local_time();
    
    // Prepare the buffer
    std::stringstream ss;

    ss << localTime.date().year() << "/" << timeLocal.date().month()
      << "/" << timeLocal.date().day()
      << "|" << timeLocal.time_of_day().hours()
      << ":" << timeLocal.time_of_day().minutes()
      << ":" << timeLocal.time_of_day().seconds()
      << "(" << _levelVec[logLevel] << "),"
      << ::basename(pFileName) << "(" << lineNum << "):"
      << msg;
      
    if(errno >= 0)
    {
      ss << " e:" << errno << "(" << strerror(errno) << ")";
    }
    ss << std::endl

    std::cout << ss;

    if(_logInstance._logFile.is_open())
    {
      _logInstance._logFile << ss;
    }
  }
}


