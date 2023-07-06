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
BUILD_FOLDERS=build arch/$(BOOTARCH)/build kernel/build string/build

# Define location of crti.o and crtn.o (used for calling global constructers)
# (This will be defined in the arch-specific options)
CRTI_OBJ=$(ARCH_CRTI_OBJ)
CRTN_OBJ=$(ARCH_CRTN_OBJ)

# Get the path to crtbegin.o and crtend.o
CRTBEGIN_OBJ:=$(shell $(CXX) $(CPPFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CXX) $(CPPFLAGS) -print-file-name=crtend.o)

# List of objects from the kernel
KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
string/build/strlen.o \
kernel/build/kernel.o \

# Objects to link
# (this is separated from the $(KERNEL_OBJS) because the crt*.o files
#  need to be linked in a specific order to work)
OBJS=\
$(CRTI_OBJ) \
$(CRTBEGIN_OBJ) \
$(KERNEL_OBJS) \
$(CRTEND_OBJ) \
$(CRTN_OBJ) \

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
build/kernel.bin: arch/$(BOOTARCH)/linker.ld $(OBJS)
	$(CXX) -T arch/$(BOOTARCH)/linker.ld -o build/kernel.bin $(CPPFLAGS) -nostdlib $(OBJS) -lgcc

# Include auto generated dependencies (if they exist)
-include $(KERNEL_OBJS:.o=.d)

# The below automatically solves dependencies
# START GENERIC

# Define C++ template
define CXX-template
$1/%.o: $$(dir $1)%.cpp
	$$(CXX) -MD -c $$< -o $$@ $$(CPPFLAGS) $$(CXXFLAGS)
endef
$(foreach folder,$(BUILD_FOLDERS),$(eval $(call CXX-template,$(folder))))

# Define ASM template
define ASM-template
$1/%.o: $$(dir $1)%.s
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
