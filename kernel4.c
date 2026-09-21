// Función en C que recibe el aviso del manejador de interrupciones
void exception_handler() {
    // Imprimimos un aviso visual en la pantalla (búfer de video)
    volatile char* video_memory = (volatile char*) 0xB8000;
    const char* err_message = "¡EXCEPCION CAPTURADA!";
    
    int i = 0;
    while (err_message[i] != '\0') {
        video_memory[i * 2] = err_message[i];
        video_memory[i * 2 + 1] = 0x4F; // Fondo rojo (4) con texto blanco (F)
        i++;
    }

    // Congelar el sistema de forma segura
    while (1) {
        __asm__ volatile ("cli; hlt");
    }
}