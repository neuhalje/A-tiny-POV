#!/bin/sh

function src_root()
{
   SCRIPT_NAME="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)/$(basename "${BASH_SOURCE[0]}")"
   dirname "${SCRIPT_NAME}"
}

BUILD_DIR=$(mktemp -d "${TMPDIR:-/tmp/}$(basename $0).XXXXXXXXXXXX")
SRC_DIR=$(src_root)

#[ -d "${BUILD_DIR}" ] && rm -rf "${BUILD_DIR}"
#mkdir "${BUILD_DIR}"

cd  "${BUILD_DIR}"
cmake "$SRC_DIR"
make && make test

