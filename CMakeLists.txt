cmake_minimum_required(VERSION 3.5)
project(hwip C)

# map gnu build systems steps to cmake tasks. You might be better off with just entering the commands manually

add_custom_target(
        build
        COMMAND make -f GNUMakefile
        DEPENDS configure
)

add_custom_target(
        configure
        COMMAND ${PROJECT_SOURCE_DIR}/configure
        DEPENDS automake autoconf libtoolize
)

add_custom_target(
        aclocal
        COMMAND aclocal
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(
        autoconf
        COMMAND autoconf
        DEPENDS aclocal
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(
        libtoolize
        COMMAND libtoolize
        DEPENDS aclocal
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(
        automake
        COMMAND automake --foreign --add-missing
        DEPENDS libtoolize autoconf
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)