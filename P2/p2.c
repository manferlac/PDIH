#include <stdio.h>
#include <dos.h>

int color_texto =15; //color blanco
int color_fondo =0; //color negro

//pausa
void pausa(){
    union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
}

//gotoxy(): coloca el cursor en una posición determinada
void gotoxy(int posicionX, int posicionY){
	union REGS inregs, outregs;
	inregs.h.dh = posicionX;
	inregs.h.dl = posicionY;
	inregs.h.bh = 0;		
	inregs.h.ah = 2;		//función para posicionar el cursor
	int86(0x10, &inregs, &outregs);	//interrupción BIOS para pantalla
}

//setcursortype(): fijar el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO
void setcursortype(int cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;

	switch(cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
		break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
		break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
		break;
	}

	int86(0x10, &inregs, &outregs);
}

//setvideomode(): fija el modo de video deseado
void setvideomode(unsigned char modo){
	union REGS inregs, outregs;
	inregs.h.ah = 0x00;
	inregs.h.al = modo;
	int86(0x10,&inregs,&outregs);
}

//getvideomode(): obtiene el modo de video actual
int getvideomode(){
	union REGS inregs, outregs;
	int modo;
	inregs.h.ah = 0xF;
	int86(0x10,&inregs,&outregs);
	modo = outregs.h.al;
	return modo;
}

//textcolor(): modifica el color de primer plano con que se mostrarán los caracteres
void textcolor(int color){
	color_texto = color;
}

//textbackground(): modifica el color de fondo con que se mostrarán los caracteres
void textbackground(int color){
	color_fondo = color;
}

//clrscr(): borra toda la pantalla, hacemos scroll vertical hacia arriba
void clrscr(){
	union REGS inregs, outregs;
	inregs.h.ah = 6;
    inregs.h.al = 0;
    inregs.h.bh = 0;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 100;
    inregs.h.dl = 100;
    int86(0x10, &inregs, &outregs);
}

//cputchar(): escribe un carácter en pantalla con el color indicado actualmente
void cputchar(char caracter){
	union REGS inregs, outregs;
	//int codigoASCII = int (caracter);
	inregs.h.ah = 9;
	inregs.h.al = caracter;
	inregs.h.bl = color_fondo<<4 | color_texto;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10, &inregs, &outregs);
}

//getche(): obtiene un carácter de teclado y lo muestra en pantalla 
int getche(){ //Devuelvo un entero porque el valor almacenado en al es el codigo ASCII
	union REGS inregs, outregs;
	int caracter;
	inregs.h.ah = 1;
	int86(0x21, &inregs, &outregs);
	caracter = outregs.h.al;
	return caracter;
}

//Función principal
int main(){

	int modo;
	//setcursortype() y gotoxy()
	printf("\nCursor invisible\n");
	setcursortype(0);
	pausa();
	printf("\nCursor normal\n");
	setcursortype(1);
	pausa();
	printf("\nCursor grueso\n");
	setcursortype(2);
	gotoxy(0, 30);
    pausa();

    //setvideomode()
    setvideomode(4); //ponemos el modo gráfico
    printf("\nCambiado a modo grafico");
    pausa();
    setvideomode(3); //ponemos el modo texto
	printf("\nCambiado a modo texto");
    pausa();

    //getvideomode()
    modo = getvideomode();
    if(modo == 3){
        printf("\nEl modo de video actualmente es: texto");
    }else if(modo == 4){
        printf("\nEl modo de video actualmente es: grafico");
    }
    
    pausa();

	//textcolor() y textbackground()
    textcolor(5); //magenta
    textbackground(2); //verde
    printf("\nSe ha modificado el color del texto y color de fondo");
    
    //cputchar()
    cputchar((char)'P');
    pausa();
    cputchar((char)'D');
    pausa();
    cputchar((char)'I');
    pausa();
    cputchar((char)'H');
    pausa();

    //getche()
    printf("\nPulsa una tecla:");
    getche();
    pausa();

    //clrscr()
    clrscr();
    pausa();

    return 0;
}
