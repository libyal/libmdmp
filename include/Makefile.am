include_HEADERS = \
        libmdmp.h

pkginclude_HEADERS = \
        libmdmp/codepage.h \
        libmdmp/definitions.h \
        libmdmp/error.h \
        libmdmp/extern.h \
        libmdmp/features.h \
        libmdmp/types.h

EXTRA_DIST = \
	libmdmp.h.in \
	libmdmp/definitions.h.in \
	libmdmp/features.h.in \
	libmdmp/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libmdmp.h
	/bin/rm -f libmdmp/definitions.h
	/bin/rm -f libmdmp/features.h
	/bin/rm -f libmdmp/types.h
	/bin/rm -f Makefile

