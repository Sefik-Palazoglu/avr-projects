DEVICE     = atmega328p
CLOCK      = 16000000L
OBJECTS    = main.o

COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -mshort-calls -mrelax -nostartfiles

all:	main.hex

%.o: %.c
	$(COMPILE) -flto -c $< -o $@

clean:
	rm -f main.hex main.elf main.dump main.elf.dump $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -Wl,-T linker.ld -Wl,--section-start=.text=0x7E00 -flto -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -j .bootloader -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

disasm:	main.hex
	avr-objdump -D -s -m avr5 main.hex > main.dump
	avr-objdump -D -j .text -m avr5 main.elf > main.elf.dump

tags: *.c
	ctags -R --exclude=io?*.h --exclude-exception=iom328p.h . $(AVR_INCLUDE)* $(AVR_INCLUDE_AVR)
