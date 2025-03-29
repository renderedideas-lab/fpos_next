# Free Pascal Operating System, version NEXT
The NEXT version of the Free Pascal Operating System.

Starting from scratch with Bootboot's example, FPOS now lives again!

## Requirements

* Free Pascal Compiler 3.2 (3.3 seems to have problems)
* ld, strip, readelf - for supported AND target platform (see below)
* Bootboot's mkbootimg
* Make
* grub2-mkrescue and xorriso (optional)
* QEMU/VirtualBox/VMWare (optional, to try out the image)

For the best results and time, build on UNIX.

## Build steps

Clone this repository.

There are multiple options to create a FPOS that you want.

Go read the [Environment variables](#environment-variables) section below.

To compile and create a bootable disk image:

```bash
$ make all
```

To compile:

```bash
$ make compile
```

To create disk/cdrom image:

```bash
$ make disk
```

To create an ISO (requires grub2-mkrescue and xorriso):

```bash
$ make grub.iso
```

## Environment variables

| Variable name  	| Job                                                            	| Acceptable values                                  	| Default value                         	|
|----------------	|----------------------------------------------------------------	|----------------------------------------------------	|---------------------------------------	|
| PLATFORM       	| Specify the platform that FPOS should target                   	| x86_64 aarch64 riscv64                             	| x86_64                                   	|
| OVMF           	| Path of OVMF.fd (for testing with EFI)                         	| Path to any valid OVMF.fd (accepts relative paths) 	| /usr/share/qemu/bios-TianoCoreEFI.bin 	|
| AMD64_PREFIX   	| Prefix of ld, strip etc. commands, for AMD64 (x86_64) platform 	| Any                                                	| x86_64-linux-gnu-                     	|
| AARCH64_PREFIX 	| Same as AMD64_PREFIX, but for aarch64 platform                 	| Any                                                	| aarch64-linux-gnu-                    	|
| RISCV64_PREFIX 	| Same as AMD64_PREFIX, but for riscv64 platform                 	| Any                                                	| riscv64-linux-gnu-                    	|