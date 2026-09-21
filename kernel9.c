// Declaramos el wrapper de la IRQ 0 en Assembly
extern void irq_wrapper_0();

// Dentro de tu función de inicialización general (o al final de init_idt):
// 1. Registramos el temporizador en la posición 32 de la IDT
set_idt_gate(32, (uint64_t)irq_wrapper_0);

// 2. Habilitar interrupciones de hardware globalmente en la CPU
__asm__ volatile ("sti");