#ifndef BX_LOG_HPP
#define BX_LOG_HPP

#include <string>
#include <vector>
#include <fstream>

#include "parameters.hpp"
#include "exception.hpp"

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

        static void log(logLevel_t logLevel, int errno, const char* pFileName,
          const int lineNum, const char* pFormat...);
        
      private:
      
        enum {
          core_msg_size = 100
        };

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

#define BX_LOG(LVL, ARGS...) \
if (LVL <= Bx::Basic::Log::level() ) { Bx::Basic::Log::log(LVL, \
  -1, __FILE__, __LINE__, ARGS) }

#define BX_LOG_E(LVL, ARGS...) \
if (LVL <= Bx::Basic::Log::level() ) { Bx::Basic::Log::log(LVL, \
  ::errno, __FILE__, __LINE__, ARGS) }

#define BX_LOG_EX(EXCEPTION) \
Bx::Basic::Log::log_exception(LOG_FTL, -1, __FILE__, __LINE__, \
  "{%s}", EXCEPTION.what())



#endif /* BX_LOG_HPP */
