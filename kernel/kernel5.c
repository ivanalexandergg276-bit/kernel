// Declaramos el wrapper en Assembly para que C lo reconozca
extern void isr_wrapper_0();

// Función de inicialización completa de la IDT
void init_idt() {
    idt_reg.limit = sizeof(struct idt_entry) * 256 - 1;
    idt_reg.base = (uint64_t)&idt;

    // Conectamos la interrupción 0 (por ejemplo, un fallo o división por cero) con nuestro wrapper
    set_idt_gate(0, (uint64_t)isr_wrapper_0);

    // Cargamos la IDT en la CPU con la instrucción 'lidt'
    __asm__ volatile ("lidt %0" : : "m"(idt_reg));
}