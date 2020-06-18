
OBJS := kernel.o bootstrap.o

kernel.bin: $(OBJS)
	$(LD) -m elf_i386 -T linker.ld -o $@ $^ 

%.o: %.c++
	$(CXX) -m32 -c $< -o $@ -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

%.o: %.s
	$(CC) -c -masm=intel -m32 $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS)
