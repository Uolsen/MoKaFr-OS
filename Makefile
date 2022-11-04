CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles
GCCPATH = ../../gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin
ARMGNU ?= aarch64-none-elf

all: clean kernel8.img

boot.o: boot.S
	$(ARMGNU)-gcc $(GCCFLAGS) -c boot.S -o boot.o

%.o: %.c
	$(ARMGNU)-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: boot.o $(OFILES)
	$(ARMGNU)-ld -nostdlib boot.o $(OFILES) -T link.ld -o kernel8.elf
	$(ARMGNU)-objcopy -O binary kernel8.elf kernel8.img

clean:
	/bin/rm kernel8.elf *.o *.img > /dev/null 2> /dev/null || true