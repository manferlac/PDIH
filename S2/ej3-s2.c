#include <stdio.h>
#include <dos.h>

int mi_getchar(){
    union REGS inregs, outregs;
    int caracter;
    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
    caracter = outregs.h.al;
    return caracter;
}

int main(){
    int tmp;
    printf("\nPulsa una tecla: ");
    tmp = mi_getchar();
    return 0;
}
