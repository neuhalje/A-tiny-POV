cmake_minimum_required(VERSION 3.0.2)

# Code coverage target for all tests
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    find_package(PythonInterp REQUIRED)
    find_program(GCOVR_EXECUTABLE NAMES gcovr)

    add_custom_target(gcovr_to_cobertura
            COMMAND ${GCOVR_EXECUTABLE}
            -r ${CMAKE_SOURCE_DIR}
            --object-directory ${CMAKE_BINARY_DIR}
            -e ${CMAKE_SOURCE_DIR}/tests
            -e ".*gmock.*"
            -x -o coverage.xml -v -s
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Converting gcov coverage data to cobertura format with gcovr")
endif ()

set(HEADERS
        utils.h
        )

set(OTHERS
        test.dox
        )

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else ()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif ()


include(DownloadProject)
download_project(PROJ googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/libPOV)

function(add_test_gmock _NAME)
    add_executable(${_NAME} ${ARGN} ${HEADERS} ${OTHERS})
    target_link_libraries(${_NAME} PRIVATE libPOV libdevice gtest gmock_main)
    add_test(
            NAME ${_NAME}
            COMMAND ${_NAME} --gtest_output=xml:${_NAME}.xml)
endfunction()

add_test_gmock(example_gtest test_example_gtest.cpp)
add_test_gmock(test_font test_font.cpp)
add_test_gmock(test_BU4094BC test_BU4094BC.cpp)
