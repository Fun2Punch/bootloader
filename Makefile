CC = gcc
LD = ld
OBJCOPY = objcopy
CFLAGS = -ffreestanding -fno-stack-protector -m64 -Wall -O2
LDFLAGS = -T linker.ld -nostdlib

SERIALPORT = 0
DEBUGOUTPUT =0 

TARGET = vac

SRC := $(shell find . -name '*.c' -o -name '*.S')
OBJS := $(SRC:.c=.o)
OBJS := $(OBJS:.S=.o)

all:$(TARGET).img

$(TARGET).img: $(TARGET).bin
	cp $< $@
	
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
	
$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -DSERIALPORT=$(SERIALPORT) -DDEBUGOUTPUT=$(DEBUGOUTPUT) -c $< -o $@
	
%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	del 