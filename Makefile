# Create multiboot kernel (Development)
build/os.bin: build/kernel.o build/boot.o linker.ld
	i686-elf-gcc -T linker.ld -o build/os.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o -lgcc

# Build an iso (Production)
production: build/os.iso

# Launch (Development)
launch: build/os.bin
	qemu-system-i386 -kernel build/os.bin

# Launch (Production)
launch-production: build/os.iso
	qemu-system-i386 -cdrom build/os.iso

# Kernel Build
build/kernel.o: kernel.c
	mkdir -p build
	i686-elf-gcc -c kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Assmble Bootstrap
build/boot.o: boot.s
	mkdir -p build
	i686-elf-as boot.s -o build/boot.o

# Build iso
build/os.iso: build/os.bin grub.cfg
	mkdir -p build/isodir/boot/grub
	cp build/os.bin build/isodir/boot/os.bin
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o build/os.iso build/isodir
	rm -r build/isodir/

# Cleanup
clean:
	rm -r build/