DEVICE     = atmega328p
CLOCK      = 16000000L
OBJECTS    = src/main.o src/uart.o
AVR_GCC    = $(AVR_BIN)/avr-gcc
AVR_OBJCPY = $(AVR_BIN)/avr-objcopy
AVR_SIZE   = $(AVR_BIN)/avr-size
AVR_OBJDMP = $(AVR_BIN_14_1_0)/avr-objdump

COMPILE = $(AVR_GCC) -I./include -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -mrelax -nostartfiles

all:	bin/main.hex

%.o: %.c
	$(COMPILE) -flto -c $< -o $@

clean:
	rm -f main.hex main.elf main.dump main.elf.dump $(OBJECTS)

# file targets:
bin/main.elf: $(OBJECTS)
	$(COMPILE) -Wl,-T linker/linker.ld -Wl,--section-start=.text=0x7E00 -o bin/main.elf $(OBJECTS)

bin/main.hex: bin/main.elf
	rm -f bin/main.hex
	$(AVR_OBJCPY) -j .text -j .data -O ihex bin/main.elf bin/main.hex
	$(AVR_SIZE) bin/main.elf

disasm:	bin/main.hex bin/main.elf
	$(AVR_OBJDMP) -D -s -m avr5 --no-addresses --no-show-raw-insn main.hex > main.dump
	$(AVR_OBJDMP) -D -j .text -m avr5 --no-addresses --no-show-raw-insn main.elf > main.elf.dump