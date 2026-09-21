#define PIC1_COMMAND 0x20
#define PIC2_COMMAND 0xA0

// Función para enviar la señal de fin de interrupción (EOI) al PIC
void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC2_COMMAND, 0x20); // Si la interrupción vino del PIC secundario
    }
    outb(PIC1_COMMAND, 0x20);     // Siempre se le avisa al PIC primario
}