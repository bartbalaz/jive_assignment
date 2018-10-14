
#include "exception.hpp"
#include "application.hpp"

using namespace Bx::Basic;

Application* Application::_pApplication(null);




Application::Appilcation(std::string& applicationName, std::string&
          executableName, std::string& version, std::string& buildTime
          Parameters& parameters):
_parameters(parameters)
{
  if(_pApplication) throw BX_EXCEPTION("Application already created");
  
  _pApplication = this;
}

Parameters& 
Application::getParameters()
{
  if(!_pApplication) throw BX_EXCEPTION("No application");

  return _pApplication->_parameters;
}

int
Appilcation::run(int argc, char* pArgv[])
{
  int retVal(0);
  
  try {
    //Parse the parameters
    if(!_parameters.getParams(argc, pArgv))
    {
      // Configure the logger

      // Run the application
      doRun();      
    }
  } catch (Exception& e)
  {
    retVal = 1;
  } catch (...)
  {
    retVal = 2;
  }

  return retVal;
}
