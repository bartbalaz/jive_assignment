
#include "exception.hpp"
#include "application.hpp"

using namespace Bx::Basic;

static Application* Application::_pApplication(null);

Application::Appilcation(Parameters& parameters):
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
    _parameters.getParams(argc, pArgv);

    // Run the application
    doRun();
    
  } catch (Exception& e)
  {
    retVal = 1;
  } catch (...)
  {
    retVal = 2;
  }

  return retVal;
}
