#!/bin/bash
qemu-system-aarch64 -M virt,highmem=off -cpu cortex-a72 -m 1G -smp 4 -dtb bcm2711-rpi-4-b.dtb -serial mon:stdio -kernel build/kernel8.img -nographic