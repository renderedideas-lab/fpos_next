PASFLAGS = -Aelf -n -O3 -Xd -CX -XXs -Tlinux -Fi../include
LDFLAGS = -nostdlib -n -T link.ld
STRIPFLAGS = -s -K mmio -K fb -K bootboot -K environment -K initstack

AMD64_PREFIX = x86_64-linux-gnu-
AARCH64_PREFIX = aarch64-linux-gnu-
RISVC64_PREFIX = riscv64-linux-gnu-

ifeq ($(PLATFORM),x86_64)
TARGET_PREFIX=$(AMD64_PREFIX)
else
ifeq ($(PLATFORM),aarch64)
TARGET_PREFIX=$(AARCH64_PREFIX)
else
ifeq ($(PLATFORM),riscv64)
TARGET_PREFIX=$(RISVC64_PREFIX)
endif
endif
endif

fpos.elf: main.pas ../include/main.inc
	fpc -P$(PLATFORM) $(PASFLAGS) main.pas
	$(TARGET_PREFIX)ld -r -b binary -o font.o font.psf
	$(TARGET_PREFIX)ld $(LDFLAGS) main.o font.o -o fpos.$(PLATFORM).elf
	$(TARGET_PREFIX)strip $(STRIPFLAGS) fpos.$(PLATFORM).elf
	$(TARGET_PREFIX)readelf -hls fpos.$(PLATFORM).elf >fpos.$(PLATFORM).txt

clean:
	rm *.o *.elf *.ppu *.txt || true
