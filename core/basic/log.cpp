
#include <sstream>
#include "boost/date_time/posix_time/posix_time_types.hpp"

#include "exception.hpp"
#include "log.hpp"


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

Log::level(string& logLevel)
{
  _logInstance._level = logLevel;
}

void
Log::file(std::string& name)
{
  if(_logInstance._logFile.is_open())
  {
    _logInstance._logFile.close();
  }

  _logInstance._logFile.open(name, ios::trunc);

  if(_logInstance._logFile.is_open())
  {
    boost::posix_time::ptime timeLocal =
      boost::posix_time::second_clock::local_time();

     std::stringstream ss;

     ss << "Log file: " << name << " opened at " << timeLocal.date().year()
      << "-" << timeLocal.date().month() << "-" << timeLocal.date().day()
      << ", " << timeLocal.date().hours() << ":" << timeLocal.date().minutes()
      << ":" << timeLocal.date().seconds() << std::endl;

    
  }
  
}

void
Log::log(logLevel_t logLevel, char* pLog)
{
  if(logLevel <= _logInstance._logLevel)
  {
    // Prepare the buffer
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
  }
}

