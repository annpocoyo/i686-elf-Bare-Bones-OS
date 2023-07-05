TARGET?=i686-elf
BOOTARCH?=i386
CXX=$(TARGET)-g++
AS=$(TARGET)-as

PREFIX=/usr
EXEC_PREFIX=$(PREFIX)
BOOTDIR=/boot
LIBDIR=$(EXEC_PREFIX)/lib
INCLUDEDIR=$(PREFIX)/include

# We need to tell the child make files that they are called by the master makefile
CALLEDBYMASTER=true

# List of INSTALL targets
INSTALL_TARGETS=

# List of HEADER targets
HEADER_TARGETS=

# List of CLEAN targets
CLEAN_TARGETS=

SYSROOT:=$(PWD)/sysroot
CXX+= --sysroot=$(SYSROOT) -isystem=$(INCLUDEDIR)

# Export all variables to make them available to child Makefiles
export

# Include all project specific targets
-include ./*/master.config

# Build full (Main Target)
all: install-headers install | sysroot/

# Phony targets
.PHONY: all install $(INSTALL_TARGETS) \
install-headers $(HEADER_TARGETS) \
production launch launch-production \
clean clean-builds clean-sysroot $(CLEAN_TARGETS) \

# Install all parts into sysroot
install: $(INSTALL_TARGETS) install-headers | sysroot/

# Install all headers into sysroot
install-headers: $(HEADER_TARGETS) | sysroot/

# Create directory structure
sysroot/:
	@mkdir -p $(SYSROOT)$(LIBDIR)
	@mkdir -p $(SYSROOT)$(INCLUDEDIR)
	@mkdir -p $(SYSROOT)$(BOOTDIR)

# Build an iso (Production)
production: build/os.iso

# Launch (Development)
launch: all
	qemu-system-i386 -kernel $(SYSROOT)$(BOOTDIR)/kernel.bin

# Launch (Production)
launch-production: build/os.iso
	qemu-system-i386 -cdrom build/os.iso

# Build iso
build/os.iso: all grub.cfg
	@mkdir -p $(SYSROOT)$(BOOTDIR)/grub/
	cp grub.cfg $(SYSROOT)$(BOOTDIR)/grub/grub.cfg
	grub-mkrescue -o build/os.iso $(SYSROOT)

# Cleanup
clean: clean-builds clean-sysroot $(CLEAN_TARGETS)

# Clean builds
clean-builds:
	rm -rf build/*

# Clean sysroot
clean-sysroot:
	rm -rf sysroot/
