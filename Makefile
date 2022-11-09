CFILES = $(shell find . -name '*.c')
OFILES = $(CFILES:.c=.o)
# GCCFILESFLAGS = -ffreestanding -mgeneral-regs-only
INCLUDE = src/hal/
GCCFLAGS = -Wall -O2 -I$(INCLUDE) -ffreestanding -nostdinc -nostdlib -nostartfiles
ARMGNU ?= aarch64-none-elf

all: clean kernel8.img

boot.o: boot.S
	$(ARMGNU)-gcc $(GCCFLAGS) -c boot.S -o boot.o

src/os/liba.o: src/os/liba.s
	$(ARMGNU)-gcc $(GCCFLAGS) -c src/os/liba.S -o src/os/liba.o

%.o: %.c
	$(ARMGNU)-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: boot.o src/os/liba.o $(OFILES)
	$(ARMGNU)-ld -nostdlib boot.o src/os/liba.o $(OFILES) -T link.ld -o build/kernel8.elf
	$(ARMGNU)-objcopy --srec-forceS3 build/kernel8.elf -O srec build/kernel8.srec
	$(ARMGNU)-objcopy -O binary build/kernel8.elf build/kernel8.img

clean:
	/bin/rm build/kernel8.elf *.o build/*.img build/*.srec > /dev/null 2> /dev/null || true
	find . -name '*.o' -type f -delete