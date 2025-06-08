QEMU_FLAGS = -serial stdio -rtc base=localtime,clock=vm -S -s

fpos.elf: clean fpc_all
	$(MAKE) -C src fpos.elf

# create an initial ram disk image with the kernel inside
initdir: fpos.elf
	-@mkdir initrd
	-@mkdir initrd/sys
	cp src/fpos.$(PLATFORM).elf initrd/sys/core

# create hybrid disk / cdrom image or ROM image
disk: initdir mkbootimg.json
	mkbootimg mkbootimg.json disk-$(PLATFORM).img

rom: mkbootimg.json
	mkbootimg mkbootimg.json disk-$(PLATFORM).rom

# BEGIN TODO SECTION
# create a GRUB cdrom
grub.iso: fpos.elf mkbootimg.json
	@mkbootimg mkbootimg.json iso/bootboot/initrd.bin
	@cp src/fpos.$(PLATFORM).elf iso/bootboot/loader
	grub2-mkrescue -o grub.iso iso

boot: fpos.elf disk
	qemu-system-$(PLATFORM) -drive file=disk-$(PLATFORM).img,format=raw $(QEMU_FLAGS)

boot-grub: grub.iso
	qemu-system-$(PLATFORM) -cdrom grub.iso -boot order=d $(QEMU_FLAGS)
# END TODO SECTION
all: fpc_all fpos.elf initdir disk