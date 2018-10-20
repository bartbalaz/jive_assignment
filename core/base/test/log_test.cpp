#include <exception>

#include "base/log.hpp"

#include "log_test.hpp"

int
log_test_1() {

  BX_LOG(LOG_INF, "log_test_1");
  
  int ret(1);

  try {
    BX_LOG(LOG_DBG, "This is a debug test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file %s at line", __FILE__, __LINE__);
  }
  catch (Bx::Base::Exception &e)
  {
    BX_LOG_E_EX(e);
    ret = 0;
  }
  catch (std::exception& e)
  {
    BX_LOG_E_EX(e);
    ret = 0;
  }

  BX_LOG(LOG_INF, "log_test_1 done");
  
  return ret;
}


int
log_test_2() {

  BX_LOG(LOG_INF, "log_test_2");
  
  int ret(1);

  try {
  
    BX_LOG(LOG_DBG, "Opening log file 'logfile.txt'");
    
    Bx::Base::Log::file("logfile.txt");
    
    BX_LOG(LOG_DBG, "This is a debug test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file %s at line", __FILE__, __LINE__);

    BX_LOG(LOG_DBG, "Closing log file");

    Bx::Base::Log::file("");
    
    BX_LOG(LOG_DBG, "This is a debug test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_INF, "This is a info test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_WRN, "This is a warning test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_ERR, "This is a error test in file %s at line", __FILE__, __LINE__);
    BX_LOG(LOG_FTL, "This is a error test in file %s at line", __FILE__, __LINE__);
  }
  catch (Bx::Base::Exception &e)
  {
    BX_LOG_E_EX(e);
    ret = 0;
  }
  catch (std::exception& e)
  {
    BX_LOG_E_EX(e);
    ret = 0;
  }
  
  BX_LOG(LOG_INF, "log_test_2 done");

  return ret;
}
