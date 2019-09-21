BLD_ROOT = ../..

SOURCES = aor_test.c
  
TEST_EXECUTABLE = common_lib_test

TEST_RESOURCES = input.json

EXEC_LIBS = common

EXEC_LIBS_NO_DEPENDENCY = pthread
