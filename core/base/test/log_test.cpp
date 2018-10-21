#include <exception>
#include <error.h>

#include "base/log.hpp"
#include "base/exception.hpp"

#include "log_test.hpp"

bool
log_test_1()
{

  BX_LOG(LOG_INF, "log_test_1");
  
  bool ret(true);

  try
  {
    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
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

  BX_LOG(LOG_INF, "log_test_1 done");
  
  return ret;
}


bool
log_test_2()
{

  BX_LOG(LOG_INF, "log_test_2");
  
  bool ret(true);

  try
  {
  
    BX_LOG(LOG_DBG, "Opening log file 'logfile.txt'");
    
    Bx::Base::Log::file("logfile1.txt");
    
    BX_LOG(LOG_DBG, "1 This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "1 This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "1 This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "1 This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "1 This is a error test in file '%s' at line %d", __FILE__, __LINE__);

    BX_LOG(LOG_DBG, "Closing log file 'logfile1.txt'");

    Bx::Base::Log::file("");
    
    BX_LOG(LOG_DBG, "2 This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "2 This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "2 This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "2 This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "2 This is a error test in file '%s' at line %d", __FILE__, __LINE__);

    BX_LOG(LOG_DBG, "Opening log file");

    Bx::Base::Log::file("logfile2.txt");

    BX_LOG(LOG_DBG, "3 This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "3 This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "3 This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "3 This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "3 This is a error test in file '%s' at line %d", __FILE__, __LINE__);

    BX_LOG(LOG_DBG, "Closing log file 'logfile2.txt'");

    Bx::Base::Log::file("");

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
  
  BX_LOG(LOG_INF, "log_test_2 done");

  return ret;
}


bool
log_test_3()
{

  BX_LOG(LOG_INF, "log_test_3");
  
  bool ret(true);
  
  try
  {
  
    BX_LOG(LOG_DBG, "Setting log level to 'dbg'");

    Bx::Base::Log::level("dbg");
    
    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);

    BX_LOG(LOG_DBG, "Setting log level to 'inf'");

    Bx::Base::Log::level("inf");
    
    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);

    BX_LOG(LOG_INF, "Setting log level to 'wrn");

    Bx::Base::Log::level("wrn");

    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
   
    BX_LOG(LOG_WRN, "Setting log level to 'err");

    Bx::Base::Log::level("err");

    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);


    BX_LOG(LOG_ERR, "Setting log level to 'ftl");

    Bx::Base::Log::level("ftl");

    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);

    BX_LOG(LOG_FTL, "Setting log level to 'dbg");

    Bx::Base::Log::level("dbg");

    BX_LOG(LOG_INF, "log_test_3 done");

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
 
    
  return ret;
}

bool
log_test_4()
{

  BX_LOG(LOG_INF, "log_test_4");
  
  bool ret(true);
  
  try
  {

    BX_LOG(LOG_DBG, "Setting log level to 'dbg'");

    Bx::Base::Log::level(Bx::Base::Log::dbg);
    
    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);

    BX_LOG(LOG_DBG, "Setting log level to 'inf'");

    Bx::Base::Log::level(Bx::Base::Log::inf);
    
    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);

    BX_LOG(LOG_INF, "Setting log level to 'wrn");

    Bx::Base::Log::level(Bx::Base::Log::wrn);

    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
   
    BX_LOG(LOG_WRN, "Setting log level to 'err");

    Bx::Base::Log::level(Bx::Base::Log::err);

    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);


    BX_LOG(LOG_ERR, "Setting log level to 'ftl");

    Bx::Base::Log::level(Bx::Base::Log::ftl);

    BX_LOG(LOG_DBG, "This is a debug test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file '%s' at line %d", __FILE__, __LINE__);

    BX_LOG(LOG_FTL, "Setting log level to 'dbg");

    Bx::Base::Log::level(Bx::Base::Log::dbg);

    BX_LOG(LOG_INF, "log_test_4 done");

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
   
  return ret;
}

bool
log_test_5()
{

  BX_LOG(LOG_INF, "log_test_5");

  bool ret(true);

  try
  {
    BX_EXCEPTION("Test exception 1");
  }
  catch (Bx::Base::Exception &e)
  {
    BX_LOG_EX(e);
  }
  catch (std::exception& e)
  {
    BX_LOG_E_EX(e);
    ret = false;
  }

  try
  {
    errno = 11;
    BX_EXCEPTION("Test exception 2, with errno, should be 11");
  }
  catch (Bx::Base::Exception &e)
  {
    BX_LOG_E_EX(e);
    
  }
  catch (std::exception& e)
  {
    BX_LOG_E_EX(e);
    ret = false;
  }

  try
  {
    BX_ASSERT((false), "Test exception 3 through assert");
  }
  catch (Bx::Base::Exception &e)
  {
    BX_LOG_EX(e);
  }
  catch (std::exception& e)
  {
    BX_LOG_E_EX(e);
    ret = false;
  }

  try
  {
    errno = 12;
    BX_ASSERT_E((false), "Test exception 3 through assert, with errno, should be 12");
  }
  catch (Bx::Base::Exception &e)
  {
    BX_LOG_EX(e);
    
  }
  catch (std::exception& e)
  {
    BX_LOG_E_EX(e);
    ret = false;
  }

  BX_LOG(LOG_INF, "log_test_5 done");

  return ret;
  
}


    
