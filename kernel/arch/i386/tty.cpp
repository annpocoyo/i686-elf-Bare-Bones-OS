#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <string.h>
#include <kernel/vga.h>
#include <kernel/tty.h>

// Define VGA_MEMORY address
uint16_t* const TTY::VGA_MEMORY = (uint16_t*) 0xB8000;

TTY::TTY(void) 
{
	// Clear and setup terminal
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void TTY::put_entry_at(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
// Scroll the terminal down one
void TTY::scroll(void)
{
	// Pull the buffer back by screen width (effectively scrolling down by one)
	for (size_t i = 0; i <= VGA_HEIGHT * VGA_WIDTH; i++) {
		size_t toMoveUp = i + VGA_WIDTH;
		terminal_buffer[i] = terminal_buffer[toMoveUp];
	}
	
	// Set terminal row back to insure text stays together
	terminal_row--;
}

void TTY::put_char(char c, uint8_t color /* = 255 */) 
{
	// Is default parameter defined?
	if (color == 255) {
		// No, redefine to default
		color = terminal_color;
	}

	// Is newline?
	if (c != '\n'){
		// No, progress normally.
		put_entry_at(c, color, terminal_column, terminal_row);
		
		// Line wrapping
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			// Go to next line?
			if (++terminal_row == VGA_HEIGHT)
				scroll(); // Reached end of screen. Scroll down.
		}
	} else {
		// Yes, skip to next line.
		terminal_column = 0;

		// Screen full?
		if (++terminal_row == VGA_HEIGHT)
			scroll(); // Reached end of screen. Scroll down.
	}
}
 
void TTY::write(const char* data, size_t size, uint8_t color /* = 255 */) 
{
	// Is default parameter defined?
	if (color == 255) {
		// No, redefine to default
		color = terminal_color;
	}

	for (size_t i = 0; i < size; i++)
		put_char(data[i], color);
}
 
void TTY::write_string(const char* data, uint8_t color /* = 255 */) 
{
	// Is default parameter defined?
	if (color == 255) {
		// No, redefine to default
		color = terminal_color;
	}

	write(data, strlen(data), color);
}
