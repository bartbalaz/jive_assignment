# Cyclical dependencies tools definitions


#-----------------------------------------------------------------------------
# ldep
#-----------------------------------------------------------------------------

RECURS_TARGETS += cdep

DEPS_DIR = $(BLD_ROOT)/deps$(PROJ_CFG_PATH)

_CDEPS = $(patsubst %.cdep, -d%.cdep, $(wildcard $(DEPS_DIR)/*.cdep ))
