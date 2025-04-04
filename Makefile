# platform, either x86, rpi or icicle
export PLATFORM=x86_64

QEMU_FLAGS = -serial stdio -rtc base=localtime,clock=vm

all: clean compile initdir disk

compile:
	$(MAKE) -C src

# create an initial ram disk image with the kernel inside
initdir:
	-@mkdir initrd
	-@cd initrd
	-@mkdir sys
	-@cd ..
	cp src/fpos.$(PLATFORM).elf initrd/sys/core

# create hybrid disk / cdrom image or ROM image
disk: initdir mkbootimg.json
	mkbootimg mkbootimg.json disk-$(PLATFORM).img

rom: mkbootimg.json
	mkbootimg mkbootimg.json disk-$(PLATFORM).rom

# BEGIN TODO SECTION
# create a GRUB cdrom
grub.iso: compile mkbootimg.json
	@mkbootimg mkbootimg.json iso/bootboot/initrd.bin
	@cp src/fpos.$(PLATFORM).elf iso/bootboot/loader
	grub2-mkrescue -o grub.iso iso

boot: compile disk
	qemu-system-$(PLATFORM) -drive file=disk-$(PLATFORM).img,format=raw $(QEMU_FLAGS)

boot-grub: grub.iso
	qemu-system-$(PLATFORM) -cdrom grub.iso -boot order=d $(QEMU_FLAGS)
# END TODO SECTION

# clean up
clean:
	rm -rf initrd *.bin *.img *.rom *.iso
