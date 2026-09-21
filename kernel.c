#include <stdint.h>

// Estructura de un descriptor de interrupción en x86_64
struct idt_entry {
    uint16_t offset_1;    // Bits 0-15 de la dirección de la función
    uint16_t selector;    // Selector de segmento en la GDT
    uint8_t  ist;         // Interrupt Stack Table (generalmente 0)
    uint8_t  type_attr;   // Tipo y atributos (puerta de interrupción, privilegios)
    uint16_t offset_2;    // Bits 16-31 de la dirección
    uint32_t offset_3;    // Bits 32-63 de la dirección
    uint32_t zero;        // Reservado (debe ser 0)
} __attribute__((packed));

// Puntero para registrar la IDT con la instrucción 'lidt'
struct idt_ptr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

// Definimos una IDT con 256 entradas (el estándar para x86)
struct idt_entry idt[256];
struct idt_ptr idt_reg;

// Función para inicializar la tabla básica
void init_idt() {
    idt_reg.limit = sizeof(struct idt_entry) * 256 - 1;
    idt_reg.base = (uint64_t)&idt;

    // Aquí cargaríamos las interrupciones básicas...
    
    // Instrucción en ensamblador para cargar la IDT en la CPU
    __asm__ volatile ("lidt %0" : : "m"(idt_reg));
}