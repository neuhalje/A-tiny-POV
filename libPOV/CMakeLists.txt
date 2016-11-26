

# Listed headers for IDEs even though no code is generated for the static lib
set(HEADERS
        config.h
    font.h
    output.h
)

set(SOURCES
    font.c
    output.c
)

set(OTHERS
    libPOV.dox
)


set(LIBPOV_LIBRARY libPOV)
if(CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_PROCESSOR STREQUAL "avr")
    add_avr_library(libPOV ${HEADERS} ${SOURCES} ${OTHERS})
    set(LIBPOV_LIBRARY libPOV-${AVR_MCU})
else()
    add_library(libPOV STATIC ${HEADERS} ${SOURCES} ${OTHERS})
endif()


target_include_directories(${LIBPOV_LIBRARY} INTERFACE ${CMAKE_SOURCE_DIR})
set_target_properties(${LIBPOV_LIBRARY} PROPERTIES PREFIX "")
set_target_properties(${LIBPOV_LIBRARY} PROPERTIES LINKER_LANGUAGE C)

# Add AVR specific header files
target_link_libraries(${LIBPOV_LIBRARY} DeviceHeaders)

# include_directories ("${CMAKE_SOURCE_DIR}/device/include")
