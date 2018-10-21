#include <exception>
#include <string>
#include <error.h>

#include "base/log.hpp"
#include "base/exception.hpp"
#include "base/parameters.hpp"


class ParametesTest1: public Bx::Base::Parameters
{
  public:
    ParametesTest1(std::string helpString)
    {
      _helpMessage = helpString;
    };
};

void
parameter_test_1_helper(const char* description, int argc, const char* argv[])
{
    BX_LOG(LOG_INF, description);

    ParametesTest1 parameterTest("This is a help message");

    parameterTest.getParams(argc, argv);
}


bool parameters_test_1()
{
  BX_LOG(LOG_INF, "parameters_test_1");
  
  bool ret(true);
  
  try
  {
    const char* pArgv[][2] = { {"app_name", "-h"},
                              {"app_name", "--help"},
                              {"app_name", "-v"},
                              {"app_name", "--version"} };
  
    parameter_test_1_helper("Getting a help message using -h", 2,
      pArgv[0]);


    parameter_test_1_helper("Getting a help message using --help", 2,
      pArgv[1]);
  
    parameter_test_1_helper("Getting the version information using -v", 2,
      pArgv[2]);

    parameter_test_1_helper("Getting the version information using --version",
      2, pArgv[3]);
     
  }
  catch (Bx::Base::Exception &e)
  {
    BX_LOG_EX(e);
    ret = false;
  }
  catch (std::exception& e)
  {
    BX_LOG_E_EX(e);
    ret = false;
  }
  

  BX_LOG(LOG_INF, "parameters_test_1 done");
  
  return ret;
}


bool parameters_test_2()
{
  BX_LOG(LOG_INF, "parameters_test_2");
  
  bool ret(true);
  
  try
  {
    BX_LOG(LOG_INF, "Setting log level to 'ftl' and log file"
    " to 'log_file.txt");

    const char* argv[] = { "app_name", "-l", "ftl", "-o", "log_file.txt" };

    ParametesTest1 parameterTest("This is a help message");

    parameterTest.getParams(5, argv);

    BX_ASSERT((parameterTest.logLevel() == "ftl"),
      "Log level not set prorietly");

    BX_ASSERT((parameterTest.logFile() == "log_file.txt"),
      "Log file not set prorietly");
  }
  catch (Bx::Base::Exception &e)
  {
    BX_LOG_EX(e);
    ret = false;
  }
  catch (std::exception& e)
  {
    BX_LOG_E_EX(e);
    ret = false;
  }


  BX_LOG(LOG_INF, "parameters_test_2 done");
  
  return ret;
}



