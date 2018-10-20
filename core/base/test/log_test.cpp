#include "base/log.hpp"

#include "log_test.hpp"

int
log_test_1() {
  BX_LOG(LOG_DBG, "This is a debug test in file %s at line", __FILE__, __LINE__);
  BX_LOG(LOG_INF, "This is a info test in file %s at line", __FILE__, __LINE__);
  BX_LOG(LOG_WRN, "This is a warning test in file %s at line", __FILE__, __LINE__);
  BX_LOG(LOG_ERR, "This is a error test in file %s at line", __FILE__, __LINE__);
  BX_LOG(LOG_FTL, "This is a error test in file %s at line", __FILE__, __LINE__);

  return 1;
}
