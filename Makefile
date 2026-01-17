CC = gcc
LD = ld
OBJCOPY = objcopy
CFLAGS = -ffreestanding -fno-stack-protector -m64 -Wall -O2
SRCFLAGS += -I./mm
SRCFLAGS += -I./entry
LDFLAGS = -T linker.ld -nostdlib

SERIALPORT = 0
DEBUGOUTPUT =0 

TARGET = vector

SRC := $(shell find entry mm -name '*.c' -o -name '*.S')
OBJS := $(SRC:.c=.o)
OBJS := $(OBJS:.S=.o)

all:$(TARGET).bin
	
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
	
$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
	
%.o: %.c
	$(CC) $(SRCFLAGS) $(CFLAGS) -DSERIALPORT=$(SERIALPORT) -DDEBUGOUTPUT=$(DEBUGOUTPUT) -c $< -o $@
	
%.o: %.S
	$(CC) $(SRCFLAGS) $(CFLAGS) -c $< -o $@
	
clean:
	rm -rf entry/*.o arch/*.o mm/*.o
	rm -rf $(TARGET).elf $(TARGET).bin $(TARGET).img
