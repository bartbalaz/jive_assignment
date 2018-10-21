#ifndef BX_LOG_HPP
#define BX_LOG_HPP

#include <string>
#include <vector>
#include <fstream>
#include <error.h>

#include "parameters.hpp"
#include "exception.hpp"

namespace Bx {
  namespace Base {
    class Log {
      public:
   
        typedef enum {
          ftl = 0,
          err = 1,
          wrn = 2,
          inf = 3,
          dbg = 4
        } logLevel_t;

        static void level(const char* logLevel);

        static void level(std::string& logLevel);

        static void level(logLevel_t logLevel);

        inline static logLevel_t level() { return _logInstance._logLevel; };

        static void file(std::string& name);

        static void file(const char* name);

        static void log(logLevel_t logLevel, int error, const char* pFileName,
          const int lineNum, const char* pFormat, ...);

        static std::string& logLevelHelp();

        static std::string& defaultLogLevel();
        
      private:
      
        enum {
          core_msg_size = 100
        };

        Log();

        ~Log();

        static Log _logInstance;

        static std::vector<std::string> _levelVec;

        static std::string _logLevelHelp;

        static std::string _defaultLogLevel;
      
        std::ofstream _logFile;
        
        logLevel_t _logLevel;
        
    };
  }
}

#define LOG_DBG Bx::Base::Log::dbg
#define LOG_INF Bx::Base::Log::inf
#define LOG_WRN Bx::Base::Log::wrn
#define LOG_ERR Bx::Base::Log::err
#define LOG_FTL Bx::Base::Log::ftl

#define BX_LOG(LVL, ARGS...) \
if (LVL <= Bx::Base::Log::level()) { Bx::Base::Log::log(LVL, \
  -1, __FILE__, __LINE__, ARGS); }

#define BX_LOG_E(LVL, ARGS...) \
if (LVL <= Bx::Base::Log::level()) { Bx::Base::Log::log(LVL, \
  errno, __FILE__, __LINE__, ARGS); }

#define BX_LOG_EX(EXCEPTION) \
Bx::Base::Log::log(LOG_FTL, -1, __FILE__, __LINE__, \
   EXCEPTION.what());

#define BX_LOG_E_EX(EXCEPTION) \
Bx::Base::Log::log(LOG_FTL, errno, __FILE__, __LINE__, \
   EXCEPTION.what());


#endif /* BX_LOG_HPP */
