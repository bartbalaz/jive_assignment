
#include "exception.hpp"
#include "application.hpp"

using namespace Bx::Basic;

Application* Application::_pApplication(null);




Application::Appilcation(std::string& applicationName, std::string&
          executableName, std::string& version, std::string& buildTime
          Parameters& parameters, Log& log):
_applicationName(applicationName), 
_executableName(executableName),
_version(version),
_buildTime(buildTime),
_parameters(parameters),
_log(log)
{
  
  _appInfo =_applicationName + " (" + _executableName + "): " +
    "version: " + _version + ", built time: " + buildTime;
  
  // The instance is overriden without checking
  _pApplication = this;
}

Parameters& 
Application::parameters()
{
  BX_ASSERT((_pApplication), "No application");

  return _pApplication->_parameters;
}

std::string&
Application::appInfo()
{
    BX_ASSERT((_pApplication), "No application");
    
    return _pApplication->_appInfo;
}
 
int
Application::run(int argc, char* pArgv[])
{
  int retVal(0);
  
  try {
    BX_LOG(LOG_INF, ("Application starting"));

    BX_LOG(LOG_INF, ("Application name: %s", _applicationName.c_str()));

    BX_LOG(LOG_INF, ("Executable name: %s", _executableName.c_str()));

    BX_LOG(LOG_INF, ("Version: %s", _version.c_str()));

    BX_LOG(LOG_INF, ("Build time: %s", _buildTime.c_str()));

    //Parse the parameters
    if(!_parameters.getParams(argc, pArgv))
    {
      BX_LOG(LOG_INF, ("Parameters parsed"));

      // Configure the logger
      Log::log(_parameters.logLevel());

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
    BX_LOG(LOG_FLT, "Caught an unexpected exception");
    
    retVal = 2;
  }

  return retVal;
}
