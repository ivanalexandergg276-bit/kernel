/*
 * openKRN - Kernel Main Entry Point
 * Copyright (C) 2026 Reliable Kernel Corp.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

// Declaraciones de funciones que vendrán de otros módulos (como el driver de video o puertos)
// extern void vga_init();
// extern void vga_print(const char* str);

void kernel_main(void) {
    // 1. Aquí es a donde salta el bootloader (Multiboot) en modo protegido de 32 bits.
    
    // 2. Inicializar los subsistemas más básicos del kernel
    // vga_init();

    // 3. Imprimir un mensaje de bienvenida provisional para probar que el kernel arrancó
    // vga_print("Bienvenido a openKRN - Sistema operativo en desarrollo\n");

    // 4. Bucle infinito para evitar que el procesador ejecute basura o se reinicie
    while (1) {
        __asm__ __volatile__("hlt"); // Instrucción en C para pausar la CPU hasta la siguiente interrupción
    }
}