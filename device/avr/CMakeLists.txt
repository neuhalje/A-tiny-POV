# Listed headers for IDEs even though no code is generated for the static lib
set(HEADERS
        ../include/device.h
        )

set(SOURCES
        device.c
        )

set(OTHERS
        #    libtarget.dox
        )

set(LIBDEVICE_LIBRARY libdevice)
if (CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_PROCESSOR STREQUAL "avr")
    add_avr_library(${LIBDEVICE_LIBRARY} ${HEADERS} ${SOURCES} ${OTHERS})
    set(LIBDEVICE_LIBRARY ${LIBDEVICE_LIBRARY}-${AVR_MCU})
else ()
    message(FATAL_ERROR "Crosscompiling required for ${LIBDEVICE_LIBRARY}")
endif ()

set_target_properties(${LIBDEVICE_LIBRARY} PROPERTIES PREFIX "")
set_target_properties(${LIBDEVICE_LIBRARY} PROPERTIES LINKER_LANGUAGE C)
target_include_directories(${LIBDEVICE_LIBRARY}
        PUBLIC ${CMAKE_SOURCE_DIR}
        )

target_link_libraries(${LIBDEVICE_LIBRARY} DeviceHeaders)
