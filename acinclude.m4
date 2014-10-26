dnl Function to detect if libmdmp dependencies are available
AC_DEFUN([AX_LIBMDMP_CHECK_LOCAL],
 [dnl Check for internationalization functions in libmdmp/libmdmp_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

