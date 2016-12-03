# Disable language features that cannot be easily fulfilled on AVR
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-threadsafe-statics")

set(LIBDEVICE_LIBRARY libdevice)

# Enable floating point format in printf
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -uvfprintf -lprintf_flt")

add_library(DeviceHeaders INTERFACE)
target_include_directories(DeviceHeaders INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )


set(HEADERS
        include/device.h
        )

set(SOURCES
        main.c
        )

set(OTHERS
 #       target.dox
        )

include_directories(${PROJECT_SOURCE_DIR}/libPOV)


if (CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_PROCESSOR STREQUAL "avr")
    add_subdirectory(avr)

    add_avr_executable(pov ${HEADERS} ${SOURCES} ${OTHERS})
    target_link_libraries(
            pov-${AVR_MCU}.elf
            libPOV-${AVR_MCU}
            libdevice-${AVR_MCU})

    target_include_directories(DeviceHeaders INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/avr/>
            )
else ()
    add_subdirectory(mockavr)

    target_include_directories(DeviceHeaders INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mockavr/>
            )
endif ()
