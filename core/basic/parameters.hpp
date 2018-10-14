#ifndef BX_PARAMETERS_HPP
#define BX_PARAMETERS_HPP


#include <string>

#include "boost/program_options.hpp" 

namespace po = boost::program_options; 

namespace Bx {
  namespace Basic {

    class Parameters {
      public:
        virtual Parameters();
        
        int getParams(int argc, char* pArgv[]);

        std::string& getLogLevel();

      protected:
        std::string _helpMessage;

        po::options_description _basicParams;

        po::options_description _specificParams;
        
        po::parameter_map _parameter_map;

      private:
        po::string _logLevel;
        
    };

  }
}



#endif 
