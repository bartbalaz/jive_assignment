#ifndef BX_PARAMETERS_HPP
#define BX_PARAMETERS_HPP


#include <string>

#include "boost/program_options.hpp" 


namespace Bx {
  namespace Basic {

    class Parameters {
      public:
        Parameters();
        
        getParams(int argc, char* pArgv[]);


      protected:
        std::string _helpMessage;
        
        po::options_description _parameterDesc;
        
        po::parameter_map _parameter_map;


      private:
        std::string _configFileName;

    };

  }
}



#endif 
