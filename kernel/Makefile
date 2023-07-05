TARGET?=i686-elf
BOOTARCH?=i386

# Not called by master Makefile?
ifndef CALLEDBYMASTER
CXX=$(TARGET)-g++ -Iinclude/
AS=$(TARGET)-as
else
# Called by master Makefile
# Load sysroot specific configuration.
include sysroot.config
endif

CPPFLAGS+= -ffreestanding -O2
CXXFLAGS+= -Wall -Wextra -fno-exceptions -fno-rtti

# List of folders where builds are stored and received from
BUILD_FOLDERS=build/ arch/$(BOOTARCH)/build/ kernel/build/ string/build/

# List of objects from the kernel
KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
string/build/strlen.o \
kernel/build/kernel.o \

# Phony targets
ifndef CALLEDBYMASTER
.PHONY: all launch clean
else
.PHONY: all launch clean install install-headers
endif

# Suffixes
.SUFFIXES: .o .cpp .s

# Main target
all: build/kernel.bin

# Load arch-specifc options
include arch/$(BOOTARCH)/make.config

# Create multiboot kernel (Development)
build/kernel.bin: arch/$(BOOTARCH)/linker.ld $(KERNEL_OBJS)
	$(CXX) -T arch/$(BOOTARCH)/linker.ld -o build/kernel.bin $(CPPFLAGS) -nostdlib $(KERNEL_OBJS) -lgcc

# Include auto generated dependencies (if they exist)
-include $(KERNEL_OBJS:.o=.d)

# The below automatically solves dependencies
# START GENERIC

# Define C++ template
define CXX-template
$1%.o: $1../%.cpp
	$$(CXX) -MD -c $$< -o $$@ $$(CPPFLAGS) $$(CXXFLAGS)
endef
$(foreach folder,$(BUILD_FOLDERS),$(eval $(call CXX-template,$(folder))))

# Define ASM template
define ASM-template
$1%.o: $1../%.s
	$$(AS) -MD $$(basename $$@).d $$< -o $$@
endef
$(foreach folder,$(BUILD_FOLDERS),$(eval $(call ASM-template,$(folder))))

# END GENERIC

# Launch Kernel
launch: all
	qemu-system-i386 -kernel build/kernel.bin

# Cleanup
clean:
	rm -rf build/*
	rm -rf arch/$(BOOTARCH)/build/*
	rm -rf kernel/build/*
	rm -rf string/build/*
