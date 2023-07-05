# i686-elf-Bare-Bones-OS

A basic OS made from the bare bones osdev tutorial. :)

## How to build from source

### Requirements to build

* GNU Make (For using the built in build scripts)
* i686-elf toolchain (specifically the binaries `i686-elf-g++` and `i686-elf-as`)
* Grub 2 that can target i386 (specifically for the binaries `grub-mkrescue` which is used for building the ISO)

### Requirements to test

* QEMU (specifically the binary `qemu-system-i386`) if you wish to use the built-in launch scripts.
* Basically anything that can boot an iso.

### How to build

To build the whole project run `make` in the root directory. To build a sub project alone (such as the kernel) run `make` in the sub project's directory.

To build an ISO (You must build the whole project for this) run `make production` in the root. This will generate an iso at `build/os.iso`.

To clean up all builds, run `make clean` in the root directory. To clean up just a sub project's builds, run `make clean` in the sub project's directory.

### How to launch

If you have QEMU installed you can run `make launch` in the root to quickly launch the OS without an ISO. Run `make launch-production` instead to launch the OS from the ISO.

The kernel can be run by itself by running `make launch` in the kernel directory.

If you don't have QEMU installed you can run the ISO normally using any device or VM. Alternatively you can run the kernel directly through your bootloader (not recommended) or a compatible VM.
