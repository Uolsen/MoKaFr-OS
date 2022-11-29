CFILES = $(shell find . -name '*.c')
OFILES = $(CFILES:.c=.o)
# GCCFILESFLAGS = -ffreestanding -mgeneral-regs-only
INCLUDE = src/hal/
GCCFLAGS = -Wall -O2 -I$(INCLUDE) -ffreestanding -nostdinc -nostdlib -nostartfiles -DDEBUG
ARMGNU ?= aarch64-none-elf

all: clean kernel8.img

src/os/boot.o: src/os/boot.S
	$(ARMGNU)-gcc $(GCCFLAGS) -c src/os/boot.S -o src/os/boot.o

firmware/BCM4345C0.o: firmware/BCM4345C0.hcd
	$(ARMGNU)-objcopy -I binary -O elf64-littleaarch64 -B aarch64 $< $@

src/os/interrupt/entry.o: src/os/interrupt/entry.S
	$(ARMGNU)-gcc $(GCCFLAGS) -c src/os/interrupt/entry.S -o src/os/interrupt/entry.o

src/os/sched/scheda.o: src/os/sched/scheda.S
	$(ARMGNU)-gcc $(GCCFLAGS) -c src/os/sched/scheda.S -o src/os/sched/scheda.o

src/os/mm/mma.o: src/os/mm/mma.S
	$(ARMGNU)-gcc $(GCCFLAGS) -c src/os/mm/mma.S -o src/os/mm/mma.o

src/os/liba.o: src/os/liba.s
	$(ARMGNU)-gcc $(GCCFLAGS) -c src/os/liba.S -o src/os/liba.o

%.o: %.c
	$(ARMGNU)-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: src/os/boot.o src/os/interrupt/entry.o src/os/liba.o src/os/sched/scheda.o src/os/mm/mma.o $(OFILES) firmware/BCM4345C0.o
	$(ARMGNU)-ld -nostdlib src/os/boot.o src/os/interrupt/entry.o src/os/liba.o src/os/sched/scheda.o src/os/mm/mma.o $(OFILES) firmware/BCM4345C0.o -T link.ld -o build/kernel8.elf
	$(ARMGNU)-objcopy --srec-forceS3 build/kernel8.elf -O srec build/kernel8.srec
	$(ARMGNU)-objcopy -O binary build/kernel8.elf build/kernel8.img
	$(ARMGNU)-objdump -l -S -D build/kernel8.elf > build/kernel8.dump

clean:
	/bin/rm build/kernel8.elf *.o build/*.img build/*.srec > /dev/null 2> /dev/null || true
	find . -name '*.o' -type f -delete