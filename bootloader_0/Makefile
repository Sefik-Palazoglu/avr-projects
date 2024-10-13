DEVICE     = atmega328p
CLOCK      = 16000000L
OBJECTS    = main.o uart.o
AVR_GCC    = $(AVR_BIN)/avr-gcc
AVR_OBJCPY = $(AVR_BIN)/avr-objcopy
AVR_SIZE   = $(AVR_BIN)/avr-size
AVR_OBJDMP = $(AVR_BIN_14_1_0)/avr-objdump

COMPILE = $(AVR_GCC) -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -mrelax -nostartfiles

all:	main.hex

%.o: %.c
	$(COMPILE) -flto -c $< -o $@

clean:
	rm -f main.hex main.elf main.dump main.elf.dump $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -Wl,-T linker.ld -Wl,--section-start=.text=0x7E00 -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	$(AVR_OBJCPY) -j .text -j .data -O ihex main.elf main.hex
	$(AVR_SIZE) main.elf

disasm:	main.hex
	$(AVR_OBJDMP) -D -s -m avr5 --no-addresses --no-show-raw-insn main.hex > main.dump
	$(AVR_OBJDMP) -D -j .text -m avr5 --no-addresses --no-show-raw-insn main.elf > main.elf.dump

tags: *.c
	ctags -R --exclude=io?*.h --exclude-exception=iom328p.h . $(AVR_INCLUDE)/* $(AVR_INCLUDE_AVR)/
