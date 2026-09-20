// Función para configurar una entrada específica en la IDT
void set_idt_gate(int n, uint64_t handler) {
    idt[n].offset_1 = handler & 0xFFFF;
    idt[n].selector = 0x08;        // Selector del segmento de código del kernel en la GDT
    idt[n].ist = 0;
    idt[n].type_attr = 0x8E;       // 0x8E significa: Interrupt Gate de 64 bits, presente (privelegio 0)
    idt[n].offset_2 = (handler >> 16) & 0xFFFF;
    idt[n].offset_3 = (handler >> 32) & 0xFFFFFFFF;
    idt[n].zero = 0;
}