#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>
#include <kernel/vga.h>

/* TTY class definition */
class TTY {
    public:
        TTY(void);
        uint8_t terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        void put_char(char c, uint8_t color = 255);
        void write(const char* data, size_t size, uint8_t color = 255);
        void write_string(const char* data, uint8_t color = 255);
        void scroll(void);
    private:
        size_t terminal_row = 0;
        size_t terminal_column = 0;
        uint16_t* terminal_buffer = VGA_MEMORY;
        static const size_t VGA_WIDTH = 80;
        static const size_t VGA_HEIGHT = 25;
        static uint16_t* const VGA_MEMORY;
        void put_entry_at(char c, uint8_t color, size_t x, size_t y);
};

#endif
