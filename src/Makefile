
ISO := os.iso
OBJS := kernel.o bootstrap.o

$(ISO): kernel.bin
	mkdir -p isodir/boot/grub
	cp $< isodir/boot
	cp grub.cfg isodir/boot/grub
	grub-mkrescue -o $@ isodir

kernel.bin: $(OBJS)
	$(LD) -m elf_i386 -T linker.ld -o $@ $^
	grub-file --is-x86-multiboot kernel.bin

%.o: %.c++
	$(CXX) -m32 -c $< -o $@ -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

%.o: %.s
	$(CC) -c -masm=intel -m32 $< -o $@


.PHONY: clean run

run: $(ISO)
	qemu-system-i386 -cdrom os.iso

clean:
	rm -f $(OBJS) kernel.bin $(ISO)
	rm -rf isodir
