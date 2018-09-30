# Rule for doxygen


ifdef DOC

doc : doxy

docConfig : doxyConfig

all : doxy

clean : doxy_clean

endif


_DEFINES = $(patsubst -D%,%,$(PROJ_DEFINES))

doxy :
	@env DOC_DEFINES='$(_DEFINES)' $(TOOLS_ROOT_PATH)/doxygen/$(DOC_PLATFORM)/$(DOX) $(DOC)


doxyConfig :
ifeq "$(findstring $(DOC_PLATFORM), Linux SunOS )" ""
	@echo "Automatic generation of documentation is not supported for \
	$(DOC_PLATFORM)"	
else
	-@$(TOOLS_ROOT_PATH)/doxygen/$(DOC_PLATFORM)/$(DOX) -g $(DOC)
endif


doxy_clean:
	rm -rf html
	rm -rf latex
	rm -rf man
	rm -rf rtf
	rm -rf xml
