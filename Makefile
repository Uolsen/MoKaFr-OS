CFILES = $(shell find . -name '*.c')
OFILES = $(CFILES:.c=.o)
# GCCFILESFLAGS = -ffreestanding -mgeneral-regs-only
INCLUDE = src/hal/
GCCFLAGS = -Wall -O2 -I$(INCLUDE) -ffreestanding -nostdinc -nostdlib -nostartfiles
ARMGNU ?= aarch64-none-elf

all: clean kernel8.img

boot.o: boot.S
	$(ARMGNU)-gcc $(GCCFLAGS) -c boot.S -o boot.o

src/os/lib.o: src/os/lib.s
	$(ARMGNU)-gcc $(GCCFLAGS) -c src/os/lib.S -o src/os/lib.o

%.o: %.c
	$(ARMGNU)-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: boot.o src/os/lib.o $(OFILES)
	$(ARMGNU)-ld -nostdlib boot.o src/os/lib.o $(OFILES) -T link.ld -o build/kernel8.elf
	$(ARMGNU)-objcopy -O binary build/kernel8.elf build/kernel8.img

clean:
	/bin/rm build/kernel8.elf *.o build/*.img > /dev/null 2> /dev/null || true
	find . -name '*.o' -type f -delete