#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libmdmp/.libs/libmdmp.1.dylib && test -f ./pymdmp/.libs/pymdmp.so
then
	install_name_tool -change /usr/local/lib/libmdmp.1.dylib ${PWD}/libmdmp/.libs/libmdmp.1.dylib ./pymdmp/.libs/pymdmp.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

