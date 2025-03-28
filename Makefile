# platform, either x86, rpi or icicle
export PLATFORM=x86_64

# the path to OVMF.fd (for testing with EFI)
OVMF = /usr/share/qemu/bios-TianoCoreEFI.bin

all: clean compile initdir disk

compile:
	$(MAKE) -C src

# create an initial ram disk image with the kernel inside
initdir:
	@mkdir initrd initrd/sys 2>/dev/null || true
	cp src/fpos.$(PLATFORM).elf initrd/sys/core

# create hybrid disk / cdrom image or ROM image
disk: initdir mkbootimg.json
	mkbootimg mkbootimg.json disk-$(PLATFORM).img

initrd.rom: mkbootimg.json
	mkbootimg mkbootimg.json initrd.rom

# BEGIN TODO SECTION
# create a GRUB cdrom
grub.iso: compile mkbootimg.json
	@mkbootimg mkbootimg.json initrd.bin
	@mkdir iso iso/bootboot iso/boot iso/boot/grub 2>/dev/null || true
	@cp src/fpos.$(PLATFORM).elf iso/bootboot/loader || true
	@cp config iso/bootboot/config || true
	@cp initrd.bin iso/bootboot/initrd || true
	@cp boot/grub/grub.cfg iso/boot/grub/grub.cfg || true
	grub2-mkrescue -o grub.iso iso
	@rm -r iso 2>/dev/null || true

bios: compile disk
	qemu-system-x86_64 -drive file=disk-$(PLATFORM).img,format=raw -serial stdio

cdrom:
	qemu-system-x86_64 -cdrom disk-$(PLATFORM).img -serial stdio

grubcdrom: grub.iso
	qemu-system-x86_64 -cdrom grub.iso -serial stdio

grub2: grub.iso
	qemu-system-x86_64 -drive file=disk-$(PLATFORM).img,format=raw -cdrom grub.iso -boot order=d -serial stdio

efi:
	qemu-system-x86_64 -bios $(OVMF) -m 64 -drive file=disk-$(PLATFORM).img,format=raw -serial stdio
	@printf '\033[0m'

eficdrom:
	qemu-system-x86_64 -bios $(OVMF) -m 64 -cdrom disk-$(PLATFORM).img -serial stdio
	@printf '\033[0m'

linux:
	qemu-system-x86_64 -kernel ../dist/bootboot.bin -drive file=disk-$(PLATFORM).img,format=raw -serial stdio

sdcard:
	qemu-system-aarch64 -M raspi3 -kernel ../dist/bootboot.img -drive file=disk-rpi.img,if=sd,format=raw -serial stdio

riscv:
	qemu-system-riscv64 -M microchip-icicle-kit -kernel ../dist/bootboot.rv64 -drive file=disk-icicle.img,if=sd,format=raw -serial stdio

coreboot:
ifeq ($(PLATFORM),x86)
	qemu-system-x86_64 -bios coreboot-x86.rom -drive file=disk-$(PLATFORM).img,format=raw -serial stdio
else
	qemu-system-aarch64 -bios coreboot-arm.rom -M virt,secure=on,virtualization=on -cpu cortex-a53 -m 1024M -drive file=disk-rpi.img,format=raw -serial stdio
endif
# END TODO SECTION

# clean up
clean:
	rm -rf initrd *.bin *.img *.rom *.iso 2>/dev/null || true
