A tiny POV - ATtiny85 based Persistence of View
================================================

TODO


Building
--------
The project uses CMake as configuration tool. Hence the very first in the build
chain is to execute CMake as shown below. Note that the default
configuration builds the project for execution on the build machine,
mainly for testing purposes.

    $ mkdir <build dir>
    $ cd <build dir>
    $ cmake <source dir>

Alternatively call `build_local.sh` to create and run an out of source build.

### Cross compilation & flashing
A different configuration is needed to setup cross compilation and flashing for
ATtiny based targets. For this purpose a copy of [cmake-avr] has been included.

Compile and flash for ATtiny85 `build_attiny.sh`

Please see the cmake-avr documentation for more configuration options.

[cmake-avr]: https://github.com/mkleemann/cmake-avr

### Source layout

Device dependent (e.g. `*avr*`) code is separated from program logic via libraries. 
This will allow builds for the build machine (for unit tests) to execute without 
mocking AVR specific code. On the donwside this makes the code less AVR idiomatic
because wrapper funciton are needed. 

```text
<root>/
 TODO
```


### Unit tests
The project ships with a number of unit tests to ensure that the platform
independent code functions properly. The unit tests are meant to be
executed on the build system with `make test`.

Testing is enabled by default and can be disabled with the CMake option
`BUILD_TESTING`. The tests log to standard out and generate JUnit XML output
for further processing.

Code coverage information generation can be configured with the CMake
option `BUILD_CODECOVERAGE`. After the compilation with `make`, the generated
code coverage data can be converted into XML using `make gcovr_to_cobertura`.

### API Documentation
The Doxygen based API documentation can be build with `make dox`.
If not needed, the documentation support can be disabled with the CMake
option `BUILD_DOCUMENTATION`.


License
-------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
[GNU General Public License](http://www.gnu.org/licenses/gpl-2.0.html)
for more details.
