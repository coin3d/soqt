# NOTE: This Makefile.am relies on $(htmldir) being AC_SUBST'ed into place...

include ../src/Inventor/Qt/common/Makefile.common

KEYHTMLPAGE = index.html

if BUILD_HTMLPAGES

# **************************************************************************
# build trickery

$(KEYHTMLPAGE): $(SoGuiBuiltFiles)
	@sim_ac_doxygen_exe@ $(top_builddir)/sogui.doxygen

filelist.txt: $(KEYHTMLPAGE)
	@ls -1 | egrep '(\.html|\.gif|\.png|\.css)$$' >filelist.txt

all-local: filelist.txt

clean-local:
	@if test -f filelist.txt; then \
	  cat filelist.txt | xargs rm -f filelist.txt; \
	fi

# **************************************************************************
# install trickery
# - uninstall after "make clean" will regenerate docs - ought to be fixed

install-data-local: install-html

uninstall-local: uninstall-html

install-html: filelist.txt
	@$(NORMAL_INSTALL)
if MAC_FRAMEWORK
	$(mkinstalldirs) "$(DESTDIR)$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Documentation"
	@echo " ln -sf Versions/Current/Documentation $(DESTDIR)$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Documentation"; \
	ln -sf Versions/Current/Documentation "$(DESTDIR)$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Documentation"
	@destdir="$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Documentation"; \
else
	@destdir="$(htmldir)"
endif
	list="`cat filelist.txt`"; \
	for file in $$list; do \
	  echo " $(INSTALL_DATA) $$file $(DESTDIR)$$destdir/$$file"; \
	  $(INSTALL_DATA) $$file "$(DESTDIR)$$destdir/$$file"; \
	done


uninstall-html: filelist.txt
	@$(NORMAL_UNINSTALL)
if MAC_FRAMEWORK
	@destdir="$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Documentation"; \
else
	@destdir="$(htmldir)"
endif
	list="`cat filelist.txt`"; \
	for file in $$list; do \
	  echo " rm -f $(DESTDIR)$(destdir)/$$file"; \
	  rm -f "$(DESTDIR)$(destdir)/$$file"; \
	done
	@echo " rmdir $(DESTDIR)$(destdir)"; \
	rmdir $(DESTDIR)$(destdir) 2>/dev/null; \
	:

endif  # BUILD_HTMLPAGES
