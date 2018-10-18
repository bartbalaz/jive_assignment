#ifndef BX_APPLICATION_HPP
#define BX_APPLICATION_HPP

#include <string>

#include "parameters.hpp"
#include "log.hpp"

// This class provides the basic support for any application



namespace Bx {
  namespace Base {

    class Application
    {
      public:
        Application(std::string& applicationName, std::string&
          executableName, std::string& version, std::string& buildTime,
          Parameters& parameters);
        

        int run(int argc, char* pArgv[]);

        // Parameters are managed by the application at a top level
        // Any class that needs to read the parameters may invoke
        //
        static Parameters& parameters();

        static std::string& appInfo();
        

      protected:

        // This method has to be overriden by the targe application
        virtual void doRun() = 0;

        // Parameter class
        
      private:
        static Application* _pApplicationInstance;
        
        std::string _applicationName;
        std::string _executableName;
        std::string _version;
        std::string _buildTime;
        std::string _appInfo;

        Parameters& _parameters;
    };
  }
}

#endif
