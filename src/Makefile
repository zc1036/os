
ISO := os.iso
OBJS := kernel.o bootstrap.o paging.o string.o printf.o utils.o serial.o a20.o

QEMU := qemu-system-x86_64
QEMU_FLAGS += -serial mon:stdio

INCLUDEDIRS := -Iinclude -Iinclude/libc++ -Iextern/printf

ifdef QEMU_GDB
	QEMU_FLAGS += -S -s
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
	$(CXX) -std=c++17 $(INCLUDEDIRS) -masm=intel -m32 -c $< -o $@ -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

%.o: %.c
	$(CC) $(INCLUDEDIRS) -masm=intel -m32 -c $< -o $@ -ffreestanding -O2 -Wall -Wextra

%.o: %.s
	$(CC) -c -masm=intel -m32 $< -o $@

.PHONY: clean run

run: $(ISO)
	$(QEMU) $(QEMU_FLAGS) -cdrom $(ISO)

run-kernel: kernel.bin
	$(QEMU) $(QEMU_FLAGS) -kernel kernel.bin

clean:
	rm -f $(OBJS) kernel.bin $(ISO)
	rm -rf isodir
