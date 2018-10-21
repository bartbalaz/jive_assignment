#define BOOST_TEST_MODULE base_library_test
#include <boost/test/included/unit_test.hpp>

#include "log_test.hpp"
#include "parameters_test.hpp"

BOOST_AUTO_TEST_CASE(log_test)
{
  BOOST_CHECK(log_test_1());
  BOOST_CHECK(log_test_2());
  BOOST_CHECK(log_test_3());
  BOOST_CHECK(log_test_4());
  BOOST_CHECK(log_test_5());
}

BOOST_AUTO_TEST_CASE(parameters_test)
{
  BOOST_CHECK(parameters_test_1());
}

