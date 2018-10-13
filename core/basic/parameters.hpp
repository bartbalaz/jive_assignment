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

        enum {
          cont = 0,
          stop = 1
        } Cont;
        
        Cont getParams(int argc, char* pArgv[]);

        std::string& 

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
