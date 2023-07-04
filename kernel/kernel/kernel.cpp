#include <kernel/tty.h>
#include <kernel/vga.h>
 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
extern "C" void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Newline and scrolling support has been achieved as shown below: */
	for (int i = 1; i != 11; i++) {
		terminal_writestring("Hello World!\n");
		terminal_writestring("This should be on the next line.\n");
		terminal_writestring("THIS IS AMAZING! I built my own hello world kernel\n");
		terminal_writestring("with newline support!\n");
		terminal_writestring("and scrolling!\n");
	}
	
	/* Let's showcase the colours :) */
	terminal_writestring("We even have some nice looking ");
	terminal_writestring("C", vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK));
	terminal_writestring("o", vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
	terminal_writestring("l", vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK));
	terminal_writestring("o", vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
	terminal_writestring("u", vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK));
	terminal_writestring("r", vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
	terminal_writestring("s", vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
	terminal_writestring("!\n");
}
