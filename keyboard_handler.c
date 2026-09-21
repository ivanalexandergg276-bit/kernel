// Declaramos la función externa del wrapper de ensamblador
extern void irq_wrapper_1();

// Función que procesa la pulsación
void keyboard_handler() {
    // Leemos el puerto de E/S del teclado (0x60)
    uint8_t scancode;
    __asm__ volatile ("inb $0x60, %0" : "=a"(scancode));

    // Si el bit más alto no está encendido, significa que la tecla fue presionada (no liberada)
    if (!(scancode & 0x80)) {
        // Aquí puedes mapear el scancode a caracteres o mostrarlo en pantalla con tu driver vga.c
    }

    // Importante: Enviar la señal EOI al PIC para la IRQ 1
    pic_send_eoi(1);
}