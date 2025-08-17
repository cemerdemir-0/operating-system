.global isr0
.global isr1
.global isr32
.global idt_load

.extern keyboard_handler
.extern timer_callback
.extern idtp

isr0:
    cli
    hlt

isr1:                       # IRQ1 - klavye
    pusha
    call keyboard_handler
    popa
    iret

isr32:
    pusha
    # call timer_callback   # <- şimdilik kapat
    popa
    iret

idt_load:
    lidt idtp
    sti
    ret
