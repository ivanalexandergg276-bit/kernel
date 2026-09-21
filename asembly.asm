.global isr_wrapper_0
.extern exception_handler

isr_wrapper_0:
    # 1. Guardar los registros de la CPU en la pila
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    pushq %rbp
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15

    # 2. Llamar a nuestra función de C para manejar el error
    call exception_handler

    # 3. Restaurar los registros en orden inverso
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rbp
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax

    # 4. Regresar de la interrupción
    iretq