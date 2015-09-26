INCLUDES = -I$(top_srcdir)

h_sources = array.h cmwc4096.h command_line.h crccalc.h \
		kissrng.h maze.h maze_recursive.h maze_renderer.h \
		mtwister.h mwc1038.h mwc256.h prng.h realutil.h sortutil.h \
		validator.h

cpp_sources = crccalc.cpp realutil.cpp command_line.cpp \
		maze.cpp maze_recursive.cpp maze_renderer.cpp \
		prng.cpp mtwister.cpp mwc1038.cpp kissrng.cpp mwc256.cpp cmwc4096.cpp

lib_LTLIBRARIES = libcoyotl.la

libcoyotl_la_SOURCES = $(h_sources) $(cpp_sources)
libcoyotl_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

DEFS = -I. -I$(srcdir)
