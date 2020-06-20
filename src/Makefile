
ISO := os.iso
OBJS := kernel.o bootstrap.o string.o printf.o utils.o

INCLUDEDIRS := -Iinclude -Iinclude/libc++ -Iextern/printf

ifdef QEMU_GDB
	QEMU_DEBUG_FLAGS += -S -s
endif

vpath %.c extern/printf

$(ISO): kernel.bin
	mkdir -p isodir/boot/grub
	cp $< isodir/boot
	cp grub.cfg isodir/boot/grub
	grub-mkrescue -o $@ isodir

kernel.bin: $(OBJS)
	$(LD) -m elf_i386 -T linker.ld -o $@ $^
	grub-file --is-x86-multiboot kernel.bin

%.o: %.c++
	$(CXX) -std=c++17 $(INCLUDEDIRS) -m32 -c $< -o $@ -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

%.o: %.c
	$(CC) $(INCLUDEDIRS) -m32 -c $< -o $@ -ffreestanding -O2 -Wall -Wextra

%.o: %.s
	$(CC) -c -masm=intel -m32 $< -o $@

.PHONY: clean run

run: $(ISO)
	qemu-system-x86_64 $(QEMU_DEBUG_FLAGS) -cdrom os.iso

clean:
	rm -f $(OBJS) kernel.bin $(ISO)
	rm -rf isodir
