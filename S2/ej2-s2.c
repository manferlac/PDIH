#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

void selecciona_modo_video(unsigned char modo){
	union REGS inregs, outregs;
	inregs.h.ah = 0x00;
	inregs.h.al = modo;
	int86(0x10,&inregs,&outregs);
	return;
}

int main(){
	unsigned char modo;
	modo = 4;
	selecciona_modo_video(modo);
	printf("Modo de vídeo cambiado");
	return 0;
}