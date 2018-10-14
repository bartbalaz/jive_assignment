#ifndef BX_LOG_HPP
#define BX_LOG_HPP

#include <string>
#include <vector>
#include <fstream>

#include "parameters.hpp"

namespace Bx {
  namespace Basic {
    class Log {
      public:
   

        enum {
          ftl = 0,
          err = 1,
          wrn = 2,
          inf = 3,
          dbg = 4
        } logLevel_t;

        static void level(std::string& logLevel);

        static void level(logLevel_t logLevel);

        inline static logLevel_t level() { _logInstance._logLevel; }

        static void file(std::string& name);

        static void log(logLevel_t, char* pLog);
        
      private:
        Log();
        ~Log();

        static Log _logInstance;

        static vector<string> _levelTbl;
      
        ofstream _logFile;
        
        logLevel_t _logLevel;
        
    };
  }
}

#define LOG_DBG Bx::Basic::Log::dbg
#define LOG_INF Bx::Basic::Log::inf
#define LOG_WRN Bx::Basic::Log::wrn
#define LOG_ERR Bx::Basic::Log::err
#define LOG_FLT Bx::Basic::Log::ftl






#endif
