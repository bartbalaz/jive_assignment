#define BOOST_TEST_MODULE lib_c_test
#include <boost/test/included/unit_test.hpp>


#include "lib_c/libfile_c.h"


BOOST_AUTO_TEST_CASE(first_test)
{
  BOOST_CHECK(printer(1) == 1);
  BOOST_CHECK(printer(1) == 2);
}
