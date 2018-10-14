#ifndef BX_APPLICATION_HPP
#define BX_APPLICATION_HPP

#include <string>

#include "parameters.hpp"

// This class provides the basic support for any application



namespace Bx {
  namespace Basic {

    class Application
    {
      public:
        virtual Appilcation(std::string& applicationName, std::string&
          executableName, std::string& version, std::string& buildTime)
          Parameters& parameters);
        
        

        int run(int argc, char* pArgv[]);

        // Parameters are managed by the application at a top level
        // Any class that needs to read the parameters may invoke
        //
        static Parameters& getParameters();

      protected:

        // This method has to be overriden by the targe application
        virtual doRun() = 0;

        // Parameter class
        
      private:
        static Application* _pApplicationInstance;
        
        std::string _applicationName;
        std::string _executableName;
        std::string _version;
        std::string _buildTime;

        Parameters _parameters;
    };
  }
}

#endif
