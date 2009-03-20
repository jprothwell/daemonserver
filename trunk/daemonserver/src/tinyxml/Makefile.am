AUTOMAKE_OPTIONS=foreign

INCLUDES = -I$(top_srcdir)/include/sockheader -I$(top_srcdir)/include/threadheader -I$(top_srcdir)/include/tinyxmlheader

noinst_PROGRAMS = libxmlcore.so
libxmlcore_so_SOURCES = tinystr.cpp  tinyxml.cpp  tinyxmlerror.cpp  tinyxmlparser.cpp
libxmlcore_so_LDFLAGS = -g -Wall -fpic -shared
