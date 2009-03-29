AUTOMAKE_OPTIONS=foreign

INCLUDES = -I$(top_srcdir)/include/sockheader -I$(top_srcdir)/include/threadheader -I$(top_srcdir)/include/tinyxmlheader

noinst_PROGRAMS = libxmlcore.so
libxmlcore_so_SOURCES = tinystr.cpp  tinyxml.cpp  tinyxmlerror.cpp  tinyxmlparser.cpp xml_op.cpp
libxmlcore_so_LDFLAGS = -g -Wall -fpic -shared

if DEBUG_XML
libxmlcore_so_CPPFLAGS = -DDEBUG_XML
else
libxmlcore_so_CPPFLAGS = 
endif
