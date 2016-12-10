A tiny POV - ATtiny85 based Persistence of Vision
================================================

To quote [Wikipedia](https://en.wikipedia.org/wiki/Persistence_of_vision):

> Persistence of vision refers to the optical illusion whereby multiple discrete images blend into a single image in the human mind and believed to be the explanation for motion perception in cinema and animated films. Like other illusions of visual perception, it is produced by certain characteristics of the visual system.


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

### Hardware

* [ATtiny85](http://www.atmel.com/devices/ATTINY85.aspx) as MCU
* shift register for driving 8 LEDs (e.g. [BU4094BC](http://rohmfs.rohm.com/en/products/databook/datasheet/ic/logic_switch/standard_logic/bu4094bc-e.pdf) )

Later:
* tilt sensor to detect waving direction (e.g. [SW-520D](http://www.beelee-switch.com/prodcuts/Multiway-Function-Switch/SW_520D_series_R/05162H012.html))
* Bluetooth module as serial interface (needs an MCU with more pins, e.g. [ATtiny84](https://en.wikipedia.org/wiki/Atmel_AVR_ATtiny_comparison_chart)

| MCU pin |   Target             |  pin@target  |                       |
|:-------:|:--------------------:|:------------:|:----------------------|
|   1     |   (RESET)            | N/A          | _not implemented yet_ |
|   2     |   not connected      | N/A          | _not implemented yet_ |
|   3     |   Tilt sensor        |              | PCINT4 - signals waving direction change |
|   4     |   GND                | N/A         |                       |
|   5     |   BU4094BC           | Strobe (1)   | Serial to parallel conversion |
|   6     |   BU4094BC           | Serial in (2)|         ''            |
|   7     |   BU4094BC           | Clock (3)    |         ''            |
|   8     |   VCC                | N/A          |                       |


### C++

C++ has been chosen a) to see whether C++ is suitable for such a small device, and 
b) because it makes testing much easier because it has more accessible _seams_.

#### C++ vs. C size comparison

Comparing a C and a C++ version shows that  C++ has a 2.3 times larger image.

Moving `delay_*` from the  header file into the .cpp  file (45037ff) decreases
file size from 4362 to 2752 bytes.

| Version                          | rel. size | text | data | bss |  dec |  hex |     filename     |
|----------------------------------|:---------:|:----:|:----:|:---:|:----:|:----:|:----------------:|
| Plain C (4f6b3d6)                |    100%   | 1882 |    6 |   0 | 1888 |  760 | pov-attiny85.elf |
| C++ (6cabc7f)                    |    231%   | 4350 |    6 |   0 | 4362 | 110a | pov-attiny85.elf |
| C++ w. delay_* in .cpp (45037ff) |    145%   | 2740 |    6 |   6 | 2752 |  ac0 | pov-attiny85.elf |

Thanks
--------

Thanks to the following projects

* Project template (CMake, etc): [atMETEO](https://github.com/fetzerch/atMETEO) by @fetzerch 
* CMake/AVR integration: [cmake-avr](https://github.com/mkleemann/cmake-avr) by @mkleemann
* Testing: [Google Test](https://github.com/google/googletest) by @google
* Testing2: [cmake DownloadProject](https://github.com/Crascit/DownloadProject) by @Crascit

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
