#
# Project-specific definitions
#


# The variables prefixed with BX_ are usually set while invoking 
# make or set by a shell script prior to invoke make


# Software version
# Major version
ifndef
BX_VERSION_MAJ = undef
endif

# Minor version
ifndef
BX_VERSION_MIN = undef
endif

# Version variant
ifndef
BX_VERSION_VAR = undef
endif

# Version string
BX_VERSION_STRING = $(BX_VERSION_MAJ)-$(BX_VERSION_MIN)-$(BX_VERSION_VAR)

# Build time
space :=
space += 
BX_BUILD_TIME=$(subst $(space),_,$(shell date))

#------------------------------------------------------------
#  The options are:
#  "debug"   for debug build
#  "release" for release build
#
ifndef BX_CONFIG
BX_CONFIG = debug
endif

#------------------------------------------------------------
# The options are:
# "ilinux" for intel based linux
# "alinux" for arm based linux
#  any other value uses the default platform gnu compier
#------------------------------------------------------------
ifndef BX_TARGET
BX_TARGET = ilinux
endif

PROJ_CFG_PATH = /$(BX_TARGET)/$(BX_CONFIG)

#------------------------------------------------------------
# Platform file suffix
# Currently the target and the suffix are set to the same value
#------------------------------------------------------------
BX_SUFFIX = BX_TARGET

#------------------------------------------------------------
# Tool setup
#------------------------------------------------------------

# Target Intel Linux
ifeq '$(BX_TARGET)' 'ilinux'
   TOOLS = gnuIntel
else
   # Target Arm Linux (cross-compilation)
   ifeq '$(BX_TARGET)' 'alinux'
      TOOLS = gnuArm
   else 
   # Target Default gnu
      TOOLS = gnuDefault
   endif
endif
 
#------------------------------------------------------------
# Project-specific definitions
#------------------------------------------------------------

# Global C flags
PROJ_C_FLAGS += -Wall -Wno-format -Wno-strict-aliasing -Werror -Wno-long-long 

# Global CPP flags
PROJ_CPP_FLAGS += -Wall -Wno-format -Wno-strict-aliasing -Werror -Wno-long-long 

ifeq "$(BX_CONFIG)" "debug"
   PROJ_C_FLAGS += -g
   PROJ_CPP_FLAGS += -g
else
   ifeq "$(BX_CONFIG)" "release"
      PROJ_C_FLAGS += -O2
      PROJ_CPP_FLAGS += -O2
   endif
endif

# Defines for C/C++ command line
PROJ_DEFINES += \
  -DBX_$(shell echo $(BX_CONFIG) | tr '[:lower:]' '[:upper:]' ) \
  -DBX_$(shell echo $(BX_TARGET) | tr '[:lower:]' '[:upper:]' ) \
  -DBX_VERSION=\"$(BX_VERSION_STRING)\" \
  -DBX_TIME=\"$(BX_BUILD_TIME)\"

#PROJ_DEFINES += \
#  $(shell echo $(_PROJ_DEFINES) | tr '[:lower:]' '[:upper:]' ) 

# Includes path
PROJ_INC_PATHS = 

# Lib path
PROJ_LIB_PATHS = 
