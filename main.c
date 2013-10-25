#include <msp430.h> 
#include "LCD.h"
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    char string[] = {'E','C','E',' ','3', '8', '2',' ','i','s',' ','m','y',' ','f','a','v','o','r','i','t','e',' ','c','l','a','s','s','!',' ',' '};
    char string2[] = {'f','a','l','c','o','n',' ','p','u','n','c','h',' ',' '};
	initSPI();
	LCDinit();
	LCDclear();
	

	while(1){
		cursorToLineOne();
		createString(string, 31);
		cursorToLineTwo();
		createString(string2, 14);

	}


}
