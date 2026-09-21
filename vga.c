/*
 * openKRN - VGA Driver Implementation
 * Copyright (C) 2026 Reliable Kernel Corp.
 */

#include "vga.h"

// Dimensiones estándar de la pantalla en modo texto
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Dirección de memoria física donde la tarjeta gráfica de la PC guarda el texto en pantalla
#define VGA_MEMORY ((volatile uint16_t*) 0xB8000)

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static volatile uint16_t* terminal_buffer;

// Función para combinar el color del texto y el color del fondo en un solo byte
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

// Crea una entrada de video que incluye el carácter y su color
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

// Inicializa el controlador de video limpiando la pantalla y poniendo letras blancas sobre fondo negro
void vga_init(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;

    vga_clear();
}

// Limpia toda la pantalla rellenándola con espacios vacíos
void vga_clear(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

// Imprime un solo carácter en la posición actual del cursor
void vga_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0; // Por ahora, si llegamos al fondo, regresamos arriba
        }
        return;
    }

    const size_t index = terminal_row * VGA_WIDTH + terminal_column;
    terminal_buffer[index] = vga_entry(c, terminal_color);

    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
}

// Imprime una cadena completa de texto terminada en nulo ('\0')
void vga_print(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        vga_putchar(str[i]);
    }
}