#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

extern uint8_t terminal_color;
void terminal_initialize(void);
void terminal_putchar(char c, uint8_t color = terminal_color);
void terminal_write(const char* data, size_t size, uint8_t color = terminal_color);
void terminal_writestring(const char* data, uint8_t color = terminal_color);
void terminal_setcolor_default(uint8_t color);
void terminal_scroll(void);

#endif
