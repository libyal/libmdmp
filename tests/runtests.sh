#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libmdmp/.libs/libmdmp.1.dylib && test -f ./pymdmp/.libs/pymdmp.so;
then
	install_name_tool -change /usr/local/lib/libmdmp.1.dylib ${PWD}/libmdmp/.libs/libmdmp.1.dylib ./pymdmp/.libs/pymdmp.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

