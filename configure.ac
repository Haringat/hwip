AC_INIT([HWIP], [0.0.1])

AC_CONFIG_MACRO_DIRS([m4])

AC_ARG_ENABLE([node-binding], [
    BUILD_NODE_BINDING=bindings/node
], [
    BUILD_NODE_BINDING=
])

AM_INIT_AUTOMAKE

AC_PROG_CC

LT_INIT

AC_OUTPUT([GNUMakefile
           src/hwip/Makefile
           src/hwip/commandlineparser/Makefile
           src/libhwip/Makefile
           src/config.h])