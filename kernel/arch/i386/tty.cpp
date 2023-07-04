#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <string.h>
#include <kernel/vga.h>
#include <kernel/tty.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor_default(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
// Scroll the terminal down one
void terminal_scroll(void)
{
	// Pull the buffer back by screen width (effectively scrolling down by one)
	for (size_t i = 0; i <= VGA_HEIGHT * VGA_WIDTH; i++) {
		size_t toMoveUp = i + VGA_WIDTH;
		terminal_buffer[i] = terminal_buffer[toMoveUp];
	}
	
	// Set terminal row back to insure text stays together
	terminal_row--;
}

void terminal_putchar(char c, uint8_t color /* = terminal_color */) 
{
	// Is newline?
	if (c != '\n'){
		// No, progress normally.
		terminal_putentryat(c, color, terminal_column, terminal_row);
		
		// Line wrapping
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			// Go to next line?
			if (++terminal_row == VGA_HEIGHT)
				terminal_scroll(); // Reached end of screen. Scroll down.
		}
	} else {
		// Yes, skip to next line.
		terminal_column = 0;

		// Screen full?
		if (++terminal_row == VGA_HEIGHT)
			terminal_scroll(); // Reached end of screen. Scroll down.
	}
}
 
void terminal_write(const char* data, size_t size, uint8_t color /* = terminal_color */) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i], color);
}
 
void terminal_writestring(const char* data, uint8_t color /* = terminal_color */) 
{
	terminal_write(data, strlen(data), color);
}
