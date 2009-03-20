AUTOMAKE_OPTIONS=foreign

INCLUDES = -I$(top_srcdir)/include/sockheader -I$(top_srcdir)/include/threadheader -I$(top_srcdir)/include/tinyxmlheader

noinst_PROGRAMS = libsocket.so
libsocket_so_SOURCES = CShm.cpp  CSocketClient.cpp  CSocket.cpp  CSocketServer.cpp
libsocket_so_LDFLAGS = -g -Wall -fpic -shared
