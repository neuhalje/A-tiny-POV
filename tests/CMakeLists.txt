find_package(CMocka 1.1.0 REQUIRED)

# Code coverage target for all tests
if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    find_package(PythonInterp REQUIRED)
    find_program(GCOVR_EXECUTABLE NAMES gcovr)

    add_custom_target(gcovr_to_cobertura
        COMMAND ${GCOVR_EXECUTABLE}
            -r ${CMAKE_SOURCE_DIR}
            --object-directory ${CMAKE_BINARY_DIR}
            -e ${CMAKE_SOURCE_DIR}/tests
            -e ".*cmocka.*"
            -x -o coverage.xml -v -s
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Converting gcov coverage data to cobertura format with gcovr")
endif()

set(HEADERS
    utils.h
)

set(OTHERS
    test.dox
)

function(add_test_cmocka _NAME)
    add_executable(${_NAME} ${ARGN} ${HEADERS} ${OTHERS})
    target_link_libraries(${_NAME} PRIVATE libPOV ${CMOCKA_LIBRARY})
    target_include_directories(${_NAME} PRIVATE ${CMOCKA_INCLUDE_DIRS})
    add_test(
        NAME ${_NAME}
        COMMAND ${_NAME} --gtest_output=xml:${_NAME}.xml)
endfunction()

add_test_cmocka(test_example test_example.c)
