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

            mov al, 1 ; cambiar a modo texto 40x25 color
            mov ah, 0 ; función para establecer el modo de pantalla
            int 10h ; interrupción BIOS para pantalla


            mov dx, OFFSET mensaje ; escribimos cadena por pantalla
            mov ah, 9
            int 21h

            mov ah,8 ; función para leer una tecla
            int 21h ; Interrupción DOS para teclado

            mov al, 3 ; cambiar a modo texto 80x25 color
            mov ah, 0 ; función para establecer el modo de pantalla
            int 10h ; interrupción BIOS para pantalla


            mov ax, 4C00h ; terminar y salir al S.O
            int 21h

        main ENDP

    codigo ends
    END main