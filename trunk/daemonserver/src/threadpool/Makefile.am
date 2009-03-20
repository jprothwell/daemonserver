AUTOMAKE_OPTIONS=foreign

INCLUDES = -I$(top_srcdir)/include/sockheader -I$(top_srcdir)/include/threadheader -I$(top_srcdir)/include/tinyxmlheader -I$(top_srcdir)/src/threadpool/thread

noinst_PROGRAMS = libthreadpool.so
libthreadpool_so_SOURCES = CBuilder.cpp \
	CInvoker.cpp \
	CThreadPool.cpp \
	CThreadPoolIdle.h \
	CCommand.cpp \
	CJob.cpp \
	CThreadPool.h \
	CThreadPoolWork.cpp \
	MyThread.h \
	CCommandJob.cpp \
	CThreadManager.cpp \
	CThreadPoolIdle.cpp \
	CThreadPoolWork.h \
	thread/CCondPrivate.cpp \
	thread/CThread.cpp \
	thread/sysinclude.h \
	thread/CCondPrivate.h \
	thread/CThread.h \
	thread/threadtype.h \
	thread/CMutexPrivate.cpp \
	thread/CThreadPrivate.cpp \
	thread/CMutexPrivate.h \
	thread/CThreadPrivate.h
libthreadpool_so_LDFLAGS = -g -Wall -fpic -shared
LIBS = -lpthread
