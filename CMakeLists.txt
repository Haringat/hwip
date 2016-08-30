cmake_minimum_required(VERSION 3.5)
project(hwip C)

add_custom_target(
        make
        COMMAND "make"
        DEPENDS steps/configure
)

add_custom_target(
        configure
        COMMAND "${PROJECT_SOURCE_DIR}/configure"
        COMMAND "touch steps/configure"
        DEPENDS steps/automake steps/autoconf steps/libtoolize
)

add_custom_target(
        aclocal
        COMMAND "aclocal"
        COMMAND "touch ${PROJECT_BINARY_DIR}/steps/aclocal"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        BYPRODUCTS steps/aclocal
        DEPENDS steps
)

add_custom_target(
        autoconf
        COMMAND "autoconf"
        COMMAND "touch ${PROJECT_BINARY_DIR}/steps/aclocal"
        DEPENDS steps/aclocal
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        BYPRODUCTS steps/autoconf
)

add_custom_target(
        libtoolize
        COMMAND "libtoolize"
        COMMAND "touch ${PROJECT_BINARY_DIR}/steps/libtoolize"
        DEPENDS steps/aclocal
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        BYPRODUCTS steps/libtoolize
)

add_custom_target(
        automake
        COMMAND automake --foreign --add-missing
        COMMAND "touch ${PROJECT_BINARY_DIR}/steps/automake"
        depends steps/libtoolize steps/autoconf
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        BYPRODUCTS steps/automake
)

add_custom_target(
        steps
        COMMAND "mkdir steps"
        BYPRODUCTS steps
)

add_custom_target(
        clean-gnu-sourcedir
        COMMAND rm -fr ./**/Makefile ./**/Makefile.in autom4te.cache aclocal.m4 compile config.guess config.sub configure depcomp install-sh ltmain.sh missing
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)