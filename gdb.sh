#!/bin/bash
#gdb-multiarch -ex 'set architecture aarch64:armv8-a' -ex 'file build/kernel8.elf' -ex 'target remote tcp:localhost:1234' -ex 'layout regs'
gdb-multiarch -ex 'set architecture aarch64' -ex 'file build/kernel8.elf' -ex 'layout regs'