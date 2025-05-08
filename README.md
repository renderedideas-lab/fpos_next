# Free Pascal Operating System, version NEXT
The NEXT version of the Free Pascal Operating System.

Starting from scratch with Bootboot's example, FPOS now lives again!

## Requirements

* Free Pascal Compiler 3.2 (3.3 seems to have problems)
* ld, strip, readelf - for supported AND target platform (see below)
* Bootboot's mkbootimg
* Make
* grub2-mkrescue and xorriso (optional)
* QEMU/VirtualBox/VMWare (to try out the image)

If you want to test the image, better use QEMU. VirtualBox + VMWare on Windows are confirmed to not working (yet).

Real hardware is not tested yet.

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
$ make fpc_all
```

To create disk/cdrom image:

```bash
$ make disk
```

To create an ISO (requires grub2-mkrescue and xorriso):

```bash
$ make grub.iso
```

To boot in QEMU:

```bash
$ make boot
```

To boot in QEMU using generated GRUB iso:

```bash
$ make boot-grub
```

To regenerate Makefile (requires fpcmake):

```bash
$ make makefiles
```

Or:

```bash
$ fpcmake -w -Tall
```

## Environment variables

| Variable name  	| Job                                                            	| Acceptable values                                  	| Default value                         	|
|----------------	|----------------------------------------------------------------	|----------------------------------------------------	|---------------------------------------	|
| PLATFORM       	| Specify the platform that FPOS should target                   	| \*many or not?\*                             	| x86_64                                   	|
| AMD64_PREFIX   	| Prefix of ld, strip etc. commands, for AMD64 (x86_64) platform 	| Any                                                	| x86_64-linux-gnu-                     	|
| AARCH64_PREFIX 	| Same as AMD64_PREFIX, but for aarch64 platform                 	| Any                                                	| aarch64-linux-gnu-                    	|
| RISCV64_PREFIX 	| Same as AMD64_PREFIX, but for riscv64 platform                 	| Any                                                	| riscv64-linux-gnu-                    	|