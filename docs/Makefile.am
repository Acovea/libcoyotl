EXTRA_DIST = libcoyotl.doxygen libcoyotl_foot.html libcoyotl_head.html

CLEANFILES = html/*

htmldir = $(datadir)/doc/$(GENERIC_LIBRARY_NAME)/api

html_DATA = html/index.html

html/index.html: libcoyotl.doxygen
	doxygen libcoyotl.doxygen

install-data-hook:
	cp -dR html/* $(DESTDIR)$(htmldir)
