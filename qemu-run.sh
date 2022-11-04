#!/bin/bash
../qemu-patch-raspberry4/build/qemu-system-aarch64 -machine raspi4b2g -serial null -serial mon:stdio -kernel kernel8.img -nographic