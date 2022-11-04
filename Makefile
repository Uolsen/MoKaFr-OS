CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles
ARMGNU ?= aarch64-none-elf

all: clean kernel8.img

boot.o: boot.S
	$(ARMGNU)-gcc $(GCCFLAGS) -c boot.S -o boot.o

%.o: %.c
	$(ARMGNU)-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: boot.o $(OFILES)
	$(ARMGNU)-ld -nostdlib boot.o $(OFILES) -T link.ld -o build/kernel8.elf
	$(ARMGNU)-objcopy -O binary build/kernel8.elf build/kernel8.img

clean:
	/bin/rm build/kernel8.elf *.o build/*.img > /dev/null 2> /dev/null || true