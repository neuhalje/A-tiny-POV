# Listed headers for IDEs even though no code is generated for the static lib
set(HEADERS
        )

set(SOURCES
        mock_device.cpp
        )

set(OTHERS
        #    libtarget.dox
        )

add_library(${LIBDEVICE_LIBRARY} ${SOURCES})

if (CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_PROCESSOR STREQUAL "avr")
    message(FATAL_ERROR "No Crosscompiling possible for ${LIBDEVICE_LIBRARY}")
else ()
endif ()

#set_target_properties(${LIBDEVICE_LIBRARY} PROPERTIES PREFIX "")
#set_target_properties(${LIBDEVICE_LIBRARY} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${LIBDEVICE_LIBRARY}
        PUBLIC ${CMAKE_SOURCE_DIR}
        )

target_link_libraries(${LIBDEVICE_LIBRARY} DeviceHeaders)
