BIN_DIR    = bin
SRC_DIR    = src
INC_DIR    = include
LNK_DIR    = linker

DEVICE     = atmega328p
CLOCK      = 16000000L
OBJECTS    = $(SRC_DIR)/main.o $(SRC_DIR)/uart.o $(SRC_DIR)/wdt_unsafe.o $(SRC_DIR)/io.o
AVR_GCC    = $(AVR_BIN)/avr-gcc
AVR_OBJCPY = $(AVR_BIN)/avr-objcopy
AVR_SIZE   = $(AVR_BIN)/avr-size
AVR_OBJDMP = $(AVR_BIN_14_1_0)/avr-objdump

COMPILE = $(AVR_GCC) -I$(INC_DIR) -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -mrelax -nostartfiles

all:	$(BIN_DIR)/main.hex

%.o: %.c
	$(COMPILE) -flto -c $< -o $@

clean:
	rm -f $(BIN_DIR)/main.hex $(BIN_DIR)/main.elf $(BIN_DIR)/main.hex.dump $(BIN_DIR)/main.elf.dump $(OBJECTS)

$(BIN_DIR)/main.elf: $(OBJECTS)
	$(COMPILE) -Wl,-T $(LNK_DIR)/linker.ld -Wl,--section-start=.text=0x7E00 -o $(BIN_DIR)/main.elf $(OBJECTS)

$(BIN_DIR)/main.hex: $(BIN_DIR)/main.elf
	rm -f bin/main.hex
	$(AVR_OBJCPY) -j .text -j .data -O ihex $(BIN_DIR)/main.elf $(BIN_DIR)/main.hex
	$(AVR_SIZE) bin/main.elf

disasm:	$(BIN_DIR)/main.hex.dump $(BIN_DIR)/main.elf.dump

$(BIN_DIR)/main.hex.dump: $(BIN_DIR)/main.hex
	$(AVR_OBJDMP) -D -s -m avr5 --no-addresses --no-show-raw-insn $(BIN_DIR)/main.hex > $(BIN_DIR)/main.hex.dump

$(BIN_DIR)/main.elf.dump: $(BIN_DIR)/main.elf
	$(AVR_OBJDMP) -D -j .text -m avr5 --no-addresses --no-show-raw-insn $(BIN_DIR)/main.elf > $(BIN_DIR)/main.elf.dump
