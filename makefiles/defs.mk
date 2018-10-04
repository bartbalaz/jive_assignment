# Default variables
# 



#
# General definitions
# 

BLD_ROOT_PATH = $(shell cd $(BLD_ROOT);pwd)

REL_PATH = $(subst $(BLD_ROOT_PATH),,$(PWD))

TOOLS_ROOT_PATH = $(shell cd $(BLD_ROOT);cd ../tools;pwd)

OBJ_DIR = $(BLD_ROOT_PATH)/../target/obj$(PROJ_CFG_PATH)$(REL_PATH)


#-----------------------------------------------------------------------------
# Recursion
# Only if the NO_RECURSION is not set
# NO_RECURSION prevents to recurse when the 
#-----------------------------------------------------------------------------

ifndef NO_RECURSION
	RECURS_TARGETS = clean all
endif

#-----------------------------------------------------------------------------
# C, C++ compilation and assembly
#-----------------------------------------------------------------------------

DEFINES = $(PROJ_DEFINES) $(DIR_DEFINES)

INCLUDES += $(PROJ_INC_PATHS) -I$(BLD_ROOT) $(DIR_INC_PATHS)

AS_FLAGS = \
 $(DEFINES) $(INCLUDES) \
 $(DIR_AS_FLAGS) \
 $(AS_COMPILER_FLAGS) \
 $(PROJ_AS_FLAGS)

CPP_FLAGS = \
 $(DEFINES) $(INCLUDES) \
 $(CPP_COMPILER_FLAGS) \
 $(PROJ_CPP_FLAGS) \
 $(DIR_CPP_FLAGS) 

C_FLAGS = \
 $(DEFINES) $(INCLUDES) \
 $(C_COMPILER_FLAGS) \
 $(PROJ_C_FLAGS) \
 $(DIR_C_FLAGS)

#-----------------------------------------------------------------------------
# Static libraries
#-----------------------------------------------------------------------------

LIB_DIR := $(BLD_ROOT)/../target/lib$(PROJ_CFG_PATH)

# EXEC_LIBS lists all the libraries that are required by the executable
# based we build a list 
ifdef EXEC_LIBS
	REQ_LIBS = $(patsubst %, $(LIB_DIR)/lib%.a,$(EXEC_LIBS))
endif


#-----------------------------------------------------------------------------
# Static linking
#-----------------------------------------------------------------------------

BIN_DIR := $(BLD_ROOT)/../target/bin$(PROJ_CFG_PATH)

LIB_PATHS += $(LIB_DIR) $(PROJ_LIB_PATHS) 

LINK_FLAGS = $(patsubst %,-L%,$(LIB_PATHS))


#-----------------------------------------------------------------------------
# Dependencies
#-----------------------------------------------------------------------------

DEP_FLAGS = $(DEFINES) $(INCLUDES)

DEP_PREFIX = $(subst /,_,$(REL_PATH))

#-----------------------------------------------------------------------------
# Definition for additional tools
#-----------------------------------------------------------------------------

include $(patsubst %,$(BLD_ROOT)/../makefiles/tools/%Defs.mk,$(TOOLS))


