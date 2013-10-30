#include <msp430.h> 
#include "LCD.h"
//#include "button.c"
//#include "LCD.c"
#include "button.h"
/*Author C2C Rasmussen
 * Date Oct 28 13
 *
 *  Implements the program
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	//stores strings in an arrays (idea from C2C Mordan)

	char string1[] = {'E','C','E',' ','3', '8', '2',' ','i','s',' ','m','y',' ','f','a','v','o','r','i','t','e',' ','c','l','a','s','s','!',' ',' '};

	char message[] = {'P','R','E','S','S',' ','K','E','Y',' ',' '}; // 11 in length
	char message1[] = {'w','a','z','z','u','p'}; // 6 in length
	char message2[] = {'h','o','w',' ','d','o',' ','y','o','u', ' ','d','o','?',' ',' '}; // 16 in length
	char message3[] = {'f','a','l','c','o','n',' ','p','u','n','c','h',' ',' '}; // 14 in length

	initSPI();
	LCDinit();
	LCDclear();

		while(1){
	cursorToLineOne();
	createString(message, 11);

	scrollLCD(message, 11);



	configureP1PinAsButton(BIT1|BIT2|BIT3);         // configure pins 1, 2, and 3 as buttons

	P1DIR |= BIT0|BIT6;                             // set launchpad LEDs to output

	while (1) {
		char buttons[] = {BIT1, BIT2, BIT3};
		char pressedButton = pollP1Buttons(buttons, 3);

		switch (pressedButton) {
		case BIT1:							// detects if Bit1 is enabled
			P1OUT ^= BIT0|BIT6;
			waitForP1ButtonRelease(BIT1);

			while(1){
			cursorToLineOne();						//passes new message
			createString(string1, 31);
			cursorToLineTwo();
			createString(message1, 6 );
			scrollLCD(string1, 31);
			scrollLCD(message1, 6);
			}
			// do something in response
			break;


		case BIT2:

			P1OUT ^= BIT0|BIT6;
			waitForP1ButtonRelease(BIT2);
			// do something in response

			while(1){
			cursorToLineOne();
			createString(string1, 31);
			cursorToLineTwo();
			createString(message2, 16 );
			scrollLCD(string1, 31);
			scrollLCD(message2, 16);
			}
			break;


		case BIT3:
			// toggle LEDs and wait for release
			P1OUT ^= BIT0|BIT6;
			waitForP1ButtonRelease(BIT3);


			while(1){
			cursorToLineOne();
			createString(string1, 31);
			cursorToLineTwo();
			createString(message3, 14 );
			scrollLCD(string1, 31);
			scrollLCD(message3, 14);
			}
			break;
		}
	}

		}

}
