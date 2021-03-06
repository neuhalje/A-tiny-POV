# Project setup ---------------------------------------------------------------
cmake_minimum_required(VERSION 3.0.2)
project(atPOV)

# Show additional project files in IDEs (e.g. QtCreator)
set(PROJECT_FILES README.md LICENSE)
add_custom_target(_dummy SOURCES ${PROJECT_FILES})

# Additional CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/cmake/modules)

# Options and configuration ---------------------------------------------------

# Target specific configuration for cross compiling with cmake-avr
# ( cmake-avr https://github.com/mkleemann/cmake-avr )
if (CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_PROCESSOR STREQUAL "avr")
    set(TARGET_CONFIGURATION arduino CACHE STRING "Target configuration")
    set(TARGET_CONFIGURATIONS arduino attiny85)
    list(FIND TARGET_CONFIGURATIONS ${TARGET_CONFIGURATION} _INDEX)
    if (_INDEX LESS 0)
        message(STATUS "Target configuration '${TARGET_CONFIGURATION}' "
                "does not exist. Valid target configurations: ")
        foreach (_target ${TARGET_CONFIGURATIONS})
            message(STATUS " - ${_target}")
        endforeach()
        message(FATAL_ERROR "Invalid target ${TARGET_CONFIGURATION}")
    endif ()

    set(AVR_UPLOADTOOL_OPTIONS "" CACHE STRING "Options for avrdude")
endif ()

# Options
include(CMakeDependentOption)
cmake_dependent_option(BUILD_TESTING "Build unit tests" ON
        "NOT CMAKE_CROSSCOMPILING" OFF)
option(BUILD_DOCUMENTATION "Build documentation" ON)

# Build targets ---------------------------------------------------------------

# Default compiler options
if ( ${CMAKE_VERSION} VERSION_LESS 3.1.0)
   add_compile_options(-std=c++11)
else ()
   set(CMAKE_CXX_STANDARD 11)
   set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Set target device compiler defines
if (TARGET_CONFIGURATION STREQUAL "arduino")
    add_definitions(-DF_CPU=16000000UL)
    add_definitions(-DVCC=5000U)
elseif (TARGET_CONFIGURATION STREQUAL "attiny85")
    add_definitions(-DF_CPU=8000000UL)
    add_definitions(-DVCC=5000U)
else ()
    # Nothing to add
endif ()

# Code coverage build type
set(CMAKE_CONFIGURATION_TYPES ${CMAKE_CONFIGURATION_TYPES} Coverage)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo" "Coverage")
set(_COVERAGE_FLAGS "-g -O0 --coverage")
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} ${_COVERAGE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# device specific implementation
add_subdirectory(device)

# libPOV: Hardware independent utilities and algorithms
add_subdirectory(libPOV)

# libPOV: Host based unit tests
if (BUILD_TESTING)

    # Configure valgrind
    find_program(MEMORYCHECK_COMMAND NAMES valgrind)
    set(_ARGS "--leak-check=full --track-origins=yes")
    set(_ARGS "${_ARGS} --xml=yes --xml-file=valgrind_%p.xml")
    set(MEMORYCHECK_COMMAND_OPTIONS ${_ARGS})

    include(CTest)
    add_subdirectory(tests)
endif ()

# Documentation
if (BUILD_DOCUMENTATION)
    find_package(Doxygen REQUIRED)
    configure_file(${CMAKE_SOURCE_DIR}/doc/Doxyfile.in
            ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(dox ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif ()


# Print configuration ---------------------------------------------------------
include(Utils)
message(STATUS)
message(STATUS "${CMAKE_PROJECT_NAME} - Configuration:")
if (CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_PROCESSOR STREQUAL "avr")
    status_message("Cross compiling" TARGET_CONFIGURATION)
    status_message("AVR processor" AVR_MCU)
    status_message("AVR H_FUSE" AVR_H_FUSE)
    status_message("AVR L_FUSE" AVR_L_FUSE)
    status_message("AVR upload tool" AVR_UPLOADTOOL)
    status_message("AVR upload tool port" AVR_UPLOADTOOL_PORT)
    status_message("AVR programmer" AVR_PROGRAMMER)
    status_message("AVR OPTIONS" AVR_UPLOADTOOL_OPTIONS)

else ()
    status_message("Compiling for local system")
endif ()
status_message("Build type" CMAKE_BUILD_TYPE)
status_message("Unit tests" BUILD_TESTING)
status_message("Documentation" BUILD_DOCUMENTATION)
message(STATUS)
