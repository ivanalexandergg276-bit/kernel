; ==============================================================================
; openKRN - boot.asm
; Arranque Multiboot (32 bits) y transición a Modo Largo (64 bits)
; Copyright (C) 2026 Reliable Kernel Corp.
; ==============================================================================

MBI_MAGIC   equ 0x1BADB002
MBI_FLAGS   equ 0x00010003
MBI_CHECKSUM equ -(MBI_MAGIC + MBI_FLAGS)

section .multiboot
align 4
    dd MBI_MAGIC
    dd MBI_FLAGS
    dd MBI_CHECKSUM

section .bss
align 4096
; Estructuras de Paginación obligatorias para Modo Largo (64 bits)
pml4_table:
    resb 4096
pdpt_table:
    resb 4096
pd_table:
    resb 4096

; Pila del Kernel
stack_bottom:
    resb 16384 * 2   ; 32 KB de pila
stack_top:

section .text
bits 32
global start
extern kmain

start:
    cli                         ; 1. Desactivar interrupciones
    mov esp, stack_top          ; Configurar pila temporal en 32 bits

    ; Verificar soporte de Multiboot (opcional pero seguro)
    ; eax contiene la magia multiboot, la guardamos
    push 0
    popf

    ; 2. Configurar Paginación de Identidad para los primeros 2MB
    ; Apuntar PML4[0] a PDPT
    mov eax, pdpt_table
    or eax, 0b11                ; Presente + Escrito/Modificable
    mov [pml4_table], eax

    ; Apuntar PDPT[0] a PD
    mov eax, pd_table
    or eax, 0b11                ; Presente + Escrito/Modificable
    mov [pdpt_table], eax

    ; Mapear 2MB usando una página gigante (Huge Page de 2MB) en PD[0]
    mov eax, 0b10000011         ; Presente + Escrito/Modificable + Página Gigante (2MB)
    mov [pd_table], eax

    ; 3. Cargar la dirección de la tabla PML4 en el registro CR3
    mov eax, pml4_table
    mov cr3, eax

    ; 4. Activar PAE (Physical Address Extension) en el registro CR4
    mov eax, cr4
    or eax, 1 << 5              ; Bit PAE
    mov cr4, eax

    ; 5. Activar el Modo Largo (LME) en el registro MSR EFER (0xC0000080)
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8              ; Bit LME (Long Mode Enable)
    wrmsr

    ; 6. Activar la Paginación y el Modo Protegido simultáneamente en CR0
    mov eax, cr0
    or eax, (1 << 31) | (1 << 0) ; Bit PG (Paging) y Bit PE (Protection Enable)
    mov cr0, eax

    ; 7. Cargar la GDT de 64 bits y dar el salto lejano (Far Jump) a Long Mode
    lgdt [gdt64.pointer]
    jmp gdt64.code_segment:long_mode_start

section .data
align 8
gdt64:
    dq 0                        ; Descriptor nulo
.code_segment: equ $ - gdt64
    dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)  ; Descriptor de Código de 64 bits (L=1)
.pointer:
    dw $ - gdt64 - 1
    dq gdt64

section .text
bits 64
long_mode_start:
    ; Ya estamos oficialmente en Modo Largo (64 bits)
    
    ; Limpiar registros de segmento de datos para 64 bits
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Apuntar la pila definitiva en 64 bits
    mov rsp, stack_top

    ; Llamar al punto de entrada principal en C de tu kernel
    call kmain

.hang:
    cli
    hlt
    jmp .hang