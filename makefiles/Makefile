#
# Base makefile.
#
# This make file is symbolically linked from any directory involved
# in building 
#

PWD = $(shell pwd)
DIR_MAKEFILE = $(shell basename $(PWD)).mk

include $(DIR_MAKEFILE)

ifdef BLD_ROOT
   include $(BLD_ROOT)/project.mk
   include $(BLD_ROOT)/../makefiles/defs.mk
   include $(BLD_ROOT)/../makefiles/rules.mk
else
error:
	@echo "BLD_ROOT must be defined in \"$(DIR_MAKEFILE)\"."
endif

