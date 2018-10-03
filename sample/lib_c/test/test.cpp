#define BOOST_TEST_MODULE lib_c_test
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(first_test)
{
  int i = 1;
  BOOST_CHECK(i);
  BOOST_CHECK(i == 2);
}
