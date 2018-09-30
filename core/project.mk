#
# Project-specific definitions
#


# The variables prefixed with BB_ are usually set while invoking 
# make or set by a shell script prior to invoke make


# Software version
# Major version
ifndef
BB_VERSION_MAJ = 0
endif

# Minor version
ifndef
BB_VERSION_MIN = 0
endif

# Version variant
ifndef
BB_VERSION_VAR = a
endif

# Version string
BB_VERSION_STRING = $(BB_VERSION_MAJ)-$(BB_VERSION_MIN)-$(BB_VERSION_VAR)

# Build time
space :=
space += 
BB_BUILD_TIME=$(subst $(space),_,$(shell date))

#------------------------------------------------------------
#  The options are:
#  "debug"   for debug build
#  "release" for release build
#
ifndef BB_CONFIG
BB_CONFIG = debug
endif

#------------------------------------------------------------
# The options are:
# "ilinux" for intel based linux
# "alinux" for arm based linux
#  any other value uses the default platform gnu compier
#------------------------------------------------------------
ifndef BB_TARGET
BB_TARGET = ilinux
endif

PROJ_CFG_PATH = /$(BB_TARGET)/$(BB_CONFIG)

#------------------------------------------------------------
# Platform file suffix
# Currently the target and the suffix are set to the same value
#------------------------------------------------------------
BB_SUFFIX = BB_TARGET

#------------------------------------------------------------
# Tool setup
#------------------------------------------------------------

# Target Intel Linux
ifeq '$(BB_TARGET)' 'ilinux'
   TOOLS = gnuIntel
else
   # Target Arm Linux (cross-compilation)
   ifeq '$(BB_TARGET)' 'alinux'
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

ifeq "$(BB_CONFIG)" "debug"
   PROJ_C_FLAGS += -g
   PROJ_CPP_FLAGS += -g
else
   ifeq "$(BB_CONFIG)" "release"
      PROJ_C_FLAGS += -O2
      PROJ_CPP_FLAGS += -O2
   endif
endif

# Defines for C/C++ command line
PROJ_DEFINES += \
  -DBB_$(shell echo $(BB_CONFIG) | tr '[:lower:]' '[:upper:]' ) \
  -DBB_$(shell echo $(BB_TARGET) | tr '[:lower:]' '[:upper:]' ) \
  -DBB_VERSION=\"$(BB_VERSION_STRING)\" \
  -DBB_TIME=\"$(BB_BUILD_TIME)\"

#PROJ_DEFINES += \
#  $(shell echo $(_PROJ_DEFINES) | tr '[:lower:]' '[:upper:]' ) 

# Includes path
PROJ_INC_PATHS = 

# Lib path
PROJ_LIB_PATHS = 
