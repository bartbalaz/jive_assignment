#ifndef BX_APPLICATION_HPP
#define BX_APPLICATION_HPP

#include <string>

#include "parameters.hpp"

// This class provides the basic support for any application


namespace po = boost::program_options; 

namespace Bx {
  namespace Basic {

    class Application
    {
      public:
        Appilcation(Parameters& parameters);

    
        int run(int argc, char* pArgv[]);

      protected:

        // This method has to be overriden by the targe application
        virtual int do_run() = 0;

        // Parameter class
        Parameters _parameters;
    };
  }
}

#endif
