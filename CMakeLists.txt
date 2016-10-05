cmake_minimum_required(VERSION 3.5)

project(hwip VERSION 0.1.1 LANGUAGES C CXX)

INCLUDE(CheckIncludeFiles)
INCLUDE(CheckCXXCompilerFlag)

CHECK_INCLUDE_FILES(list HAVE_LIST_H)
if(HAVE_LIST_H)
    message(FATAL_ERROR "C++ class list could not be found.")
endif()
if(WIN32)
    option(WIN32 ON)
    message(STATUS "running on windows")
elseif(UNIX)
    option(UNIX ON)
    message(STATUS "running on UNIX")
else()
    message(FATAL_ERROR "unsupported operation system. Only windows and UNIX are supported.")
endif()
CHECK_INCLUDE_FILES(string HAVE_LIST_H)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    message(STATUS "c++11 support detected")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    message(STATUS "c++0x support detected")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

CONFIGURE_FILE(config.h.in ${CMAKE_BINARY_DIR}/config.h)

include_directories(${PROJECT_BINARY_DIR})

add_library(hwip SHARED
        src/libhwip/decapsulate.c
        src/libhwip/encapsulate.c
        src/libhwip/hwip.h src/libhwip/util.c src/libhwip/hwip.spec.c src/utils/stubber.h src/utils/msg.h)
set_target_properties(hwip
        PROPERTIES
            COMPILE_FLAGS "-m32"
            LINK_FLAGS "-m32")
add_library(clp SHARED
        src/libclp/Argument.cpp
        src/libclp/Argument.hpp
        src/libclp/Parser.cpp
        src/libclp/Parser.hpp
        src/libclp/clp.h
        src/libclp/clp.cpp src/utils/stubber.h src/utils/utils.h src/utils/msg.h)
set_target_properties(clp
        PROPERTIES
            COMPILE_FLAGS "-m32"
            LINK_FLAGS "-m32")
add_executable(hwip_exec
        src/hwip/main.c src/utils/stubber.h src/utils/msg.h)
set_target_properties(hwip_exec
        PROPERTIES
            OUTPUT_NAME "hwip"
            COMPILE_FLAGS "-m32"
            LINK_FLAGS "-m32")
add_executable(libhwip_test
        src/libhwip/hwip.spec.c src/utils/stubber.h src/utils/msg.h)
set_target_properties(libhwip_test
        PROPERTIES
            COMPILE_FLAGS "-m32"
            LINK_FLAGS "-m32")

# we need libmath
target_link_libraries(hwip m)
target_link_libraries(libhwip_test hwip)
target_link_libraries(hwip_exec hwip clp)

#add_library(hwip-java SHARED
#            bindings/java/binding/com_github_haringat_hwip_clp_Argument.h
#            bindings/java/binding/com_github_haringat_hwip_clp_Parser.h
#            bindings/java/binding/Argument.cpp
#            bindings/java/binding/Parser.cpp src/utils/stubber.h src/utils/msg.h)

#target_link_libraries(hwip-java
#        hwip
#        clp)
