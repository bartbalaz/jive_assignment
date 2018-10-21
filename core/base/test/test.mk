BLD_ROOT = ../..

SOURCES = log_test.cpp parameters_test.cpp test.cpp
  
TEST_EXECUTABLE = lib_base_test

EXEC_LIBS = base

EXEC_LIBS_NO_DEPENDENCY = boost_program_options boost_date_time
