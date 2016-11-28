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
        target.dox
        )

if (TARGET_CONFIGURATION STREQUAL "arduino")
    add_definitions(-DF_CPU=16000000UL)
    add_definitions(-DVCC=5000U)

    add_subdirectory(avr)

    add_avr_executable(pov ${HEADERS} ${SOURCES} ${OTHERS})
    target_link_libraries(
            pov-${AVR_MCU}.elf
            libPOV-${AVR_MCU}
            libdevice-${AVR_MCU})
elseif (TARGET_CONFIGURATION STREQUAL "attiny85")
    add_definitions(-DF_CPU=8000000UL)
    add_definitions(-DVCC=5000U)

    add_subdirectory(avr)

    add_avr_executable(pov ${HEADERS} ${SOURCES} ${OTHERS})
    target_link_libraries(
            pov-${AVR_MCU}.elf
            libPOV-${AVR_MCU}
            libdevice-${AVR_MCU})
else ()
    add_subdirectory(mockavr)

    target_include_directories(DeviceHeaders INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mockavr/>
            )
endif ()
