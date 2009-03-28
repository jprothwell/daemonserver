AUTOMAKE_OPTIONS=foreign

SUBDIRS = src/threadpool/ src/communication src/tinyxml client/
INCLUDES = -I$(top_srcdir)/include/sockheader -I$(top_srcdir)/include/threadheader -I$(top_srcdir)/include/tinyxmlheader -I$(top_srcdir)/include
#export INCLUDES

noinst_PROGRAMS= daemonserver
daemonserver_SOURCES = main.cpp
daemonserver_LDADD = -L$(top_srcdir)/src/threadpool -L$(top_srcdir)/src/communication -L$(top_srcdir)/src/tinyxml
daemonserver_LDFLAGS = -g -Wall 
LIBS = -lpthread -lsocket -lxmlcore -lthreadpool
