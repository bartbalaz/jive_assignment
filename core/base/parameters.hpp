#ifndef BX_PARAMETERS_HPP
#define BX_PARAMETERS_HPP


#include <string>

#include "boost/program_options.hpp" 

namespace po = boost::program_options; 

namespace Bx {
  namespace Base {

    class Parameters {
      public:
        Parameters();
        
        int getParams(int argc, const char* pArgv[]);

        inline std::string& logLevel() { return _logLevel; };

        inline std::string& logFile() { return _logFile; }; 

      protected:
        std::string _helpMessage;

        po::options_description _commonParams;

        po::options_description _comandLineParams;

        po::options_description _fileParams;
        
        po::variables_map _parameter_map;

      private:
        std::string _logLevel;
        
        std::string _logFile;
    };

  }
}



#endif 
