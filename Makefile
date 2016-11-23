#
# Makefile template for ATtiny85
# Derived from AVR Crosspack template
#

DEVICE     = attiny85           # See avr-help for all possible devices
CLOCK      = 8000000            # 8Mhz
PROGRAMMER = -c linuxspi -P /dev/spidev0.0 # For using SPI on raspberry
TARGET     = main
OBJECTS    = main.o font.o output.o

# Program DEFINES
PROGRAM_DEFINES   =  -D DELAY_CHAR_COLUMN_MS=20  -DDELAY_REVERSE_WAVING_MS=300

# fuse settings:
# use http://www.engbedded.com/fusecalc
FUSES      = -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m  # 1mhz
#FUSES      = -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m  # 8mhz

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -std=c11 $(PROGRAM_DEFINES)

# symbolic targets:
all: $(TARGET).hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash: all
	sudo gpio -g mode 22 out
	sudo gpio -g write 22 0
	#sudo $(AVRDUDE) -p $(DEVICE) -P /dev/spidev0.0 -c linuxspi -b 10000 -U flash:w:$(TARGET).hex
	sudo $(AVRDUDE) -p $(DEVICE) $(PROGRAMMER) -U flash:w:$(TARGET).hex
	sudo gpio -g write 22 1

fuse:
	$(AVRDUDE) $(FUSES)

install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID $(TARGET).hex

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(OBJECTS)

# file targets:
$(TARGET).elf: $(OBJECTS)
	$(COMPILE) -o $(TARGET).elf $(OBJECTS)

$(TARGET).hex: $(TARGET).elf
	rm -f $(TARGET).hex
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-size --format=avr --mcu=$(DEVICE) $(TARGET).elf
	# If you have an EEPROM section, you must also create a hex file for the
	# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm: $(TARGET).elf
	avr-objdump -d $(TARGET).elf

cpp:
	$(COMPILE) -E $(TARGET).c
