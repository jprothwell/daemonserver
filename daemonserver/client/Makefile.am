AUTOMAKE_OPTIONS=foreign

#SUBDIRS = ../src/threadpool/ ../src/communication ../src/tinyxml
INCLUDES = -I$(top_srcdir)/include/sockheader -I$(top_srcdir)/include/threadheader -I$(top_srcdir)/include/tinyxmlheader

noinst_PROGRAMS = client
client_SOURCES = main.cpp
client_LDADD =  -L$(top_srcdir)/src/threadpool -L$(top_srcdir)/src/communication -L$(top_srcdir)/src/tinyxml
client_LDFLAGS = -g -Wall
LIBS = -lpthread -lsocket -lthreadpool -lxmlcore
