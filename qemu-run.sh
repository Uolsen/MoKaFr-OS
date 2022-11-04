#!/bin/bash
../qemu-patch-raspberry4/build/qemu-system-aarch64 -machine raspi4b2g -serial mon:stdio -kernel build/kernel8.img -nographic