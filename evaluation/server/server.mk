BLD_ROOT = ..

SOURCES = main.c \
	server.c
  
EXECUTABLE = server

EXEC_LIBS=common

EXEC_LIBS_NO_DEPENDENCY=pthread
