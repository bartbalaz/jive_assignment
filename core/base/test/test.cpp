#define BOOST_TEST_MODULE base_library_test
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include "log_test.hpp"
#include "parameters_test.hpp"

void separator()
{ 
  std::cout << std::endl << "-----------------------------------------------"
  "------------------------------------" << std::endl << std::endl;
}


BOOST_AUTO_TEST_CASE(log_test)
{
  separator();
  BOOST_CHECK(log_test_1());
  separator();
  BOOST_CHECK(log_test_2());
  separator();
  BOOST_CHECK(log_test_3());
  separator();
  BOOST_CHECK(log_test_4());
  separator();
  BOOST_CHECK(log_test_5());
  separator();
}

BOOST_AUTO_TEST_CASE(parameters_test)
{
  BOOST_CHECK(parameters_test_1());
  separator();
  BOOST_CHECK(parameters_test_2());
  separator();
  BOOST_CHECK(parameters_test_3());
  separator();

}

