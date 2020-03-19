punto MACRO ejex,ejey,color
    push ax
    push cx
    push dx
    mov ax,ejey
    mov cx,ejex
    mov dx,ax
    mov al,color
    mov ah,0Ch
    int 10h
    pop dx
    pop cx
    pop ax
ENDM

pila segment stack 'stack'
        dw 100h dup (?)
    pila ends

    datos segment 'data'
        mensaje db '- - - Cambiar modo de video pulsando tecla - - -$'
    datos ends

    codigo segment 'code'
        assume cs:codigo, ds:datos, ss:pila
        main PROC
            mov ax, datos
            mov ds, ax

            mov al, 4 ; cambiar a modo texto 320x200 con 4 colores
            mov ah, 0 ; función para establecer el modo de pantalla
            int 10h ; interrupción BIOS para pantalla

            ; PINTAMOS RECTANGULO
            mov cx, 30 ; columna
            mov dx, 30 ; fila
            mov al, 3 ; color
            mov ah, 0Ch ; funcion para iluminar un pixel
            
            
            bucle:
                int 10h ;interrupción bios para pantalla
                inc cx ; incrementamos columna
                cmp cx, 260 ; comparamos hasta que llegue a 260
                jl bucle ; saltamos al bucle de nuevo si no ha llegado a 260

                mov cx, 30 
                inc dx ; incrementamos fila
                cmp dx, 100 ; comparamos hasta que llegue a 150
                jl bucle ; saltamos al bucle de nuevo si no ha llegado a 150

            ; Aqui hemos terminado de pintar el rectangulo blanco
            ; Procedemos a pintar distintos pixeles dentro del mismo
            punto 100,80,1
            punto 120,40,4
            punto 150,70,5
            punto 134,50,4
            punto 100,35,2

            mov ah, 8 ; hacemos pausa hasta pulsar una tecla
            int 21h

            mov al, 3 ; cambiar a modo texto 80x25
            mov ah, 0 ; función para establecer el modo de pantalla
            int 10h ; ; interrupción BIOS para pantalla

            mov ax, 4C00h ; Salir a S.O
            int 21h

        main ENDP

    codigo ends
    END main