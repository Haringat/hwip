cmake_minimum_required(VERSION 3.5)

project(hwip VERSION 0.1.1 LANGUAGES C CXX)

INCLUDE(CheckIncludeFiles)
INCLUDE(CheckCXXCompilerFlag)

CHECK_INCLUDE_FILES(list HAVE_LIST_H)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include_directories(${PROJECT_BINARY_DIR})

add_library(hwip
        src/libhwip/decapsulate.c
        src/libhwip/encapsulate.c
        src/libhwip/hwip.h)
add_library(clp
        src/libclp/Argument.cpp
        src/libclp/Argument.hpp
        src/libclp/Parser.cpp
        src/libclp/Parser.hpp
        src/libclp/Alias.cpp
        src/libclp/Alias.hpp
        src/libclp/clp.h
        src/libclp/clp.cpp)
add_executable(hwip_exec
        src/hwip/main.c)
set_target_properties(hwip_exec
        PROPERTIES
            OUTPUT_NAME "hwip")

#add_dependencies(hwip libhwip libclp)
target_link_libraries(hwip_exec hwip clp)

add_library(libhwip-java SHARED
            bindings/java/binding/com_github_haringat_hwip_clp_Argument.h
            bindings/java/binding/com_github_haringat_hwip_clp_Parser.h
            bindings/java/binding/Argument.cpp
            bindings/java/binding/Parser.cpp)

target_link_libraries(libhwip-java hwip clp)

#project(hwip C)

# map gnu build systems steps to cmake tasks. You might be better off with just entering the commands manually though...

#[[add_custom_target(
        build
        COMMAND make -f GNUMakefile
        DEPENDS configure
)

add_custom_target(
        configure
        COMMAND ${PROJECT_SOURCE_DIR}/configure
        DEPENDS automake autoconf libtoolize autoheader
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

add_custom_target(
        autoheader
        COMMAND autoheader
        DEPENDS aclocal
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)]]
