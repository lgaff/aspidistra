#!/bin/bash
losetup /dev/loop0 ../bin/floppy.img
mount /dev/loop0 /mnt/flop 
rm -vf /mnt/flop/kernel
cp -v -f ../src/aspidistros /mnt/flop/kernel
umount /dev/loop0
losetup -d /dev/loop0
