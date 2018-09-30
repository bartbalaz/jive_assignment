# Cyclical dependencies tools rules


#-----------------------------------------------------------------------------
# ldep
#-----------------------------------------------------------------------------

STD_INCLUDES = \
  -I/usr/include/ \
  -I/usr/include/asm/ \
  -I/usr/include/bits/ \
  -I/usr/include/gnu/ \
  -I/usr/include/sys/ \
  -I/usr/include/linux/ \
  -I/usr/lib/bcc/include \
  -I/usr/include/g++-2/	\
  -I/local/gcc/lib/gcc-lib/i686-pc-linux-gnu/2.95.2/include/
#-I/usr/local/gcc/lib/gcc-lib/i686-pc-linux-gnu/2.95.2/include/ \

.PHONY: ldep
ldep: cdep
	/vobs/CDMA2000/code/tools/lakos/bin/Linux/internal/ldep -d$(DEPS_DIR)/test.cdep

#$(_CDEPS)

.PHONY: cdep
cdep: _cdep

_cdep: 
ifdef LIBRARY
ifneq ($(strip $(SOURCES)),)
	@if test ! -d $(DEPS_DIR); then mkdir -p $(DEPS_DIR); fi;
	/vobs/CDMA2000/code/tools/lakos/bin/Linux/internal/cdep -I. $(INCLUDES) $(STD_INCLUDES) $(SOURCES) >> $(DEPS_DIR)/test.cdep
endif
endif

clean_ldep:
	rm -rf $(BLD_ROOT)/deps


