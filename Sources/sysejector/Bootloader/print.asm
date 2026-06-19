[BITS 16]
[ORG 0x7C00]

start:
        mov ax, 0x13
        int 0x10
        mov ax, 0xA000
        mov es, ax

mainLoop:
        xor di, di
        mov cx, 320 * 200

nextPixel:
        mov ax, di
        xor ax, 0A3Ch
        rol ax, 3
        add ax, si
        mov al, ah
        stosb

        loop nextPixel
        add si, 5
        jmp mainLoop

times 510-($-$$) db 0
dw 0xAA55
