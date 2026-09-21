#include <stdint.h>

// Puertos del PIC
#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

// Función para enviar un byte a un puerto de E/S
static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Función para remapear el PIC
void remap_pic() {
    // 1. Inicializar el PIC en modo cascada
    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);

    // 2. Definir los nuevos offsets (PIC1 empieza en 32, PIC2 en 40)
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    // 3. Configurar la cascada entre PIC1 y PIC2
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);

    // 4. Modo de operación normal (8086)
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    // 5. Limpiar las máscaras (permitir interrupciones)
    outb(PIC1_DATA, 0x0);
    outb(PIC2_DATA, 0x0);
}