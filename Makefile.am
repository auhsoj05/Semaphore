bin_PROGRAMS = semaphore
semaphore_SOURCES = main.cpp
semaphore_CPPFLAGS=$(libgtk_CFLAGS)
semaphore_LDADD=$(libgtk_LIBS)

clean-local:
	@rm config.status configure config.log
	@rm Makefile
	@rm -r autom4te.cache/
	@rm aclocal.m4
	@rm compile install-sh missing Makefile.in
