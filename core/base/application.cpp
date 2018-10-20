
#include "exception.hpp"
#include "application.hpp"

using namespace Bx::Base;

Application* Application::_pApplicationInstance(nullptr);

std::string Application::_noAppInfo("No application");


Application::Application(std::string& applicationName, std::string&
          executableName, std::string& version, std::string& buildTime,
          Parameters& parameters):
_applicationName(applicationName), 
_executableName(executableName),
_version(version),
_buildTime(buildTime),
_parameters(parameters)
{
  
  _appInfo =_applicationName + " (" + _executableName + "): " +
    "version: " + _version + ", built time: " + buildTime;
  
  // The instance is overriden without checking
  _pApplicationInstance = this;
}

Parameters& 
Application::parameters()
{
  BX_ASSERT((_pApplicationInstance), "No application");

  return _pApplicationInstance->_parameters;
}

std::string&
Application::appInfo()
{
    if(!_pApplicationInstance)
    {
      _noAppInfo
    }
    
    return _pApplicationInstance->_appInfo;
}
 
int
Application::run(int argc, char* pArgv[])
{
  int retVal(0);
  
  try {
    BX_LOG(LOG_INF, "Application starting");

    BX_LOG(LOG_INF, "Application name: %s", _applicationName.c_str());

    BX_LOG(LOG_INF, "Executable name: %s", _executableName.c_str());

    BX_LOG(LOG_INF, "Version: %s", _version.c_str());

    BX_LOG(LOG_INF, "Build time: %s", _buildTime.c_str());

    //Parse the parameters
    if(!_parameters.getParams(argc, pArgv))
    {
      BX_LOG(LOG_INF, ("Parameters parsed"));

      // Configure the logger
      Log::level(_parameters.logLevel());

      Log::file(_parameters.logFile());

      // Run the application
      doRun();
    }
  }
  catch (std::exception& e)
  {
    BX_LOG_EX(e);
    
    retVal = 1;
  }
  catch (...)
  {
    BX_LOG(LOG_FTL, "Caught an unexpected exception");
    
    retVal = 2;
  }

  return retVal;
}
