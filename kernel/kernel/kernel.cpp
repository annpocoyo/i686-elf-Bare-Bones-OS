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

/* Initialize terminal interface */
TTY tty;

extern "C" void kernel_main(void) 
{
	/* Newline and scrolling support has been achieved as shown below: */
	for (int i = 1; i != 11; i++) {
		tty.write_string("Hello World!\n");
		tty.write_string("This should be on the next line.\n");
		tty.write_string("THIS IS AMAZING! I built my own hello world kernel\n");
		tty.write_string("with newline support!\n");
		tty.write_string("and scrolling!\n");
	}
	
	/* Let's showcase the colours :) */
	tty.write_string("We even have some nice looking ");
	tty.write_string("C", vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK));
	tty.write_string("o", vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
	tty.write_string("l", vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK));
	tty.write_string("o", vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
	tty.write_string("u", vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK));
	tty.write_string("r", vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
	tty.write_string("s", vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
	tty.write_string("!\n");
}
