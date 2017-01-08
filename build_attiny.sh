#!/usr/bin/env bash

##### Configuration
#

UPLOAD_PORT=/dev/spidev0.0
AVR_PROGRAMMER=linuxspi
AVR_UPLOADTOOL_OPTIONS="-b 10000"

AVR_L_FUSE=0xE2
AVR_H_FUSE=0xDF

#
##### End of configuration

function src_root()
{
   SCRIPT_NAME="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)/$(basename "${BASH_SOURCE[0]}")"
   dirname "${SCRIPT_NAME}"
}

BUILD_DIR=$(mktemp -d "${TMPDIR:-/tmp/}$(basename $0).XXXXXXXXXXXX")
SRC_DIR="$(src_root)"

CMAKE_AVR_FILE="${SRC_DIR}/cmake/cmake-avr/generic-gcc-avr.cmake"

[ -d "${BUILD_DIR}" ] && rm -rf "${BUILD_DIR}"
mkdir "${BUILD_DIR}"
cd  "${BUILD_DIR}"

cmake -DCMAKE_TOOLCHAIN_FILE="${CMAKE_AVR_FILE}" \
    -DTARGET_CONFIGURATION=attiny85 -DAVR_MCU=attiny85 \
    -DAVR_PROGRAMMER=${AVR_PROGRAMMER} -DAVR_UPLOADTOOL_PORT=${UPLOAD_PORT} \
    -DAVR_UPLOADTOOL_OPTIONS="${AVR_UPLOADTOOL_OPTIONS}" \
    -DAVR_L_FUSE="${AVR_L_FUSE}" -DAVR_H_FUSE="${AVR_H_FUSE}" \
    "$SRC_DIR"

make && sudo make set_fuses upload_pov
