// Contador global de tics del reloj
volatile uint32_t timer_ticks = 0;

// Manejador de la interrupción del temporizador (IRQ 0 -> IDT 32)
void timer_handler() {
    timer_ticks++;
    
    // Aquí podríamos cambiar de proceso o actualizar la pantalla en el futuro
    
    // Importante: siempre hay que avisarle al PIC que ya terminamos de atender la interrupción (IRQ 0)
    pic_send_eoi(0);
}