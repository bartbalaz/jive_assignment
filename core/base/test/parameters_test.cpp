#include <exception>
#include <string>
#include <error.h>

#include "base/log.hpp"
#include "base/parameters.hpp"


class ParametesTest1: public Bx::Base::Parameters
{
  public:
    ParametesTest1(std::string helpString)
    {
      _helpMessage = helpString;
    };
  

};


bool parameters_test_1()
{
  BX_LOG(LOG_INF, "parameters_test_1");
  
  bool ret(true);
  
  ParametesTest1 parameterTest1("This is a help message");

  const char* params[] = {"app_name", "help", "dupa"};
  
  parameterTest1.getParams(2, params );

  BX_LOG(LOG_INF, "parameters_test_1 done");
  
  return ret;
}
