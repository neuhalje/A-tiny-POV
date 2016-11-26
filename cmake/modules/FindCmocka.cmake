# - Find cmocka
#
# This module includes and builds cmocka as external project.
# The ratio for building cmocka as dedicated project is the
# possibility to use an up to date version for building.
#
# The directory containing the cmocka sources can be specified with
# CMOCKA_SOURCE_DIR. If this variable is omitted or the specified directory
# does not include a version of Google Mock, the sources will download.
#
# The directory where cmocka is built can be specified with
# CMOCKA_BINARY_DIR.
#
# This module defines the following variables:
#  CMOCKA_FOUND          - If Google Mock is available
#  CMOCKA_INCLUDE_DIRS   - Include directories for <cmocka.h>
#  CMOCKA_LIBRARY        - cmocka Library
#
#  Adapted from <https://github.com/fetzerch/atMETEO/blob/master/cmake/modules/FindGMock.cmake>
#
cmake_minimum_required(VERSION 3.6)


include(ExternalProject)
include(CheckCXXCompilerFlag)
find_package(Threads REQUIRED)

# Set default directories.
if(NOT CMOCKA_SOURCE_DIR)
    set(CMOCKA_SOURCE_DIR ${CMAKE_BINARY_DIR}/cmocka-src)
endif()
if(NOT CMOCKA_BINARY_DIR)
    set(CMOCKA_BINARY_DIR ${CMAKE_BINARY_DIR}/cmocka-bin)
endif()

# Compiler settings have to be passed on to externalproject_add in order to
# support cross compilation.
# Disable 'unused-local-typedefs' warnings for CMocka < 1.7.0.
#if(CMOCKA_FIND_VERSION AND CMOCKA_FIND_VERSION VERSION_LESS "1.1.0")
#    check_cxx_compiler_flag(
#        -Wno-unused-local-typedefs HAS_NO_UNUSED_LOCAL_TYPEDEFS)
#    if(HAS_NO_UNUSED_LOCAL_TYPEDEFS)
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs")
#    endif()
#endif()
set(CMAKE_ARGS
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS})

# Determine if CMOCKA_SOURCE_DIR contains CMocka sources.
find_file(CMOCKA_LOCAL_SOURCE
    NAMES cmocka.h
    PATHS ${CMOCKA_SOURCE_DIR}/include
    NO_DEFAULT_PATH)

# Build CMocka from local sources.
if(CMOCKA_LOCAL_SOURCE)

    message(STATUS "Using local CMocka version")

    externalproject_add(CMocka
        PREFIX cmocka
        CMAKE_ARGS ${CMAKE_ARGS}
        SOURCE_DIR ${CMOCKA_SOURCE_DIR}
        BINARY_DIR ${CMOCKA_BINARY_DIR}
        INSTALL_COMMAND "")

# Download CMocka.
else()

    # Latest version available on the cmocka.org.
    if(NOT CMOCKA_FIND_VERSION)
        set(CMOCKA_FIND_VERSION 1.1.0)
    endif()

        # 1.2.3 --> 1.2
    string(REGEX REPLACE  "([0-9]+)[.]([0-9]+)[.]([0-9]+)" "\\1.\\2" CMOCKA_MAJOR_MINOR ${CMOCKA_FIND_VERSION} )

    message(STATUS "Downloading CMocka ${CMOCKA_FIND_VERSION}")
    set(CMOCKA_URL "https://cmocka.org/files/${CMOCKA_MAJOR_MINOR}/cmocka-${CMOCKA_FIND_VERSION}.tar.xz ")

    externalproject_add(CMocka
        PREFIX cmocka
        URL "${CMOCKA_URL}"
        CMAKE_ARGS ${CMAKE_ARGS}
        SOURCE_DIR ${CMOCKA_SOURCE_DIR}
        BINARY_DIR ${CMOCKA_BINARY_DIR}
        INSTALL_COMMAND ""
        UPDATE_COMMAND "")
endif()

# Set the result variables.
set(CMOCKA_INCLUDE_DIRS
    ${CMOCKA_SOURCE_DIR}/include
    ${CMOCKA_SOURCE_DIR}/gtest/include)

set(GTEST_INCLUDE_DIRS
    ${CMOCKA_SOURCE_DIR}/gtest/include)

# Add dependency to the external target so that CMake is able
# to resolve the dependencies to CMocka libs and builds CMocka first.
macro(add_CMOCKA_library _name _lib)
    string(TOUPPER "${_name}_LIBRARY" _LIB_VAR)
    set(${_LIB_VAR} ${_name} ${CMAKE_THREAD_LIBS_INIT})
    add_library(${_name} STATIC IMPORTED)
    set_target_properties(${_name} PROPERTIES IMPORTED_LOCATION ${_lib})
    add_dependencies(${_name} CMocka)
endmacro()

add_CMOCKA_library(cmocka ${CMOCKA_BINARY_DIR}/libcmocka.a)
add_CMOCKA_library(CMOCKA_main ${CMOCKA_BINARY_DIR}/libCMOCKA_main.a)
add_CMOCKA_library(gtest ${CMOCKA_BINARY_DIR}/gtest/libgtest.a)
add_CMOCKA_library(gtest_main ${CMOCKA_BINARY_DIR}/gtest/libgtest_main.a)

# For CMocka < 1.7.0 GTest symbols are not included in the library
# and have to be added separately.
#if(CMOCKA_FIND_VERSION AND CMOCKA_FIND_VERSION VERSION_LESS "1.7.0")
#    list(APPEND CMOCKA_LIBRARY ${GTEST_LIBRARY})
#endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CMocka DEFAULT_MSG CMOCKA_SOURCE_DIR)
