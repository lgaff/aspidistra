#!/bin/bash

losetup /dev/loop0 ../bin/floppy.img
bochs -f bochsrc.bxrc
losetup -d /dev/loop0
