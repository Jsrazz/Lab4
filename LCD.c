/*
 *Author C2C Rasmussen
 * Date Oct 28 13
 *defines methods
 *
 *
 */




#include "LCD.h"
#include <msp430.h>
#define  RS_MASK	0x40
char LCDCON = 0x00;
char LCDATA = 0x00;
char LCDSEND = 0x00;


void initSPI(){				// translated from lab 3
	UCB0CTL1 |= UCSWRST;

	UCB0CTL0 |= UCCKPH|UCMSB|UCMST|UCSYNC;

	UCB0CTL1 |= UCSSEL1;

	UCB0STAT |= UCLISTEN;

	P1SEL |= BIT5;
	P1SEL2 |= BIT5;

	P1SEL  |= BIT6;
	P1SEL2 |= BIT6;

	P1SEL |= BIT7;
	P1SEL2 |= BIT7;



	//P1DIR |= BIT0;

	UCB0CTL1 &= ~UCSWRST;   // where forgotten squiggle was
}

void LCDinit()     			// Captain Branchflower's
{
	writeCommandNibble(0x03);

	writeCommandNibble(0x03);

	writeCommandNibble(0x03);

	writeCommandNibble(0x02);

	writeCommandByte(0x28);

	writeCommandByte(0x0C);

	writeCommandByte(0x01);

	writeCommandByte(0x06);

	writeCommandByte(0x01);

	writeCommandByte(0x02);

	SPI_send(0);
	delayMicro();
}


void LCDclear()
{
	writeCommandByte(1);
}

void writeCommandNibble(char commandNibble)
{
	LCDCON &= ~RS_MASK;
	LCD_write_4(commandNibble);
	delayMilli();
}

void writeCommandByte(char commandByte)
{
	LCDCON &= ~RS_MASK;
	LCD_write_8(commandByte);
	delayMilli();
}

void writeDataByte(char dataByte)
{
	LCDCON |= RS_MASK;
	LCD_write_8(dataByte);
	delayMilli();
}

void LCD_write_8(char byteToSend)
{
	unsigned char sendByte = byteToSend;

	sendByte &= 0xF0;

	sendByte = sendByte >> 4;               // rotate to the right 4 times

	LCD_write_4(sendByte);

	sendByte = byteToSend;

	sendByte &= 0x0F;


	LCD_write_4(sendByte);
}
void LCD_write_4(char byteToSend){				// translated from lab 3
	unsigned char sendByte = byteToSend;

	        sendByte &= 0x7F;

	        sendByte |= LCDCON;

	        SPI_send(sendByte);

	        delayMilli();

	        sendByte |= 0x80;

	        SPI_send(sendByte);

	        delayMilli();

	        sendByte &= 0x7f;

	        SPI_send(sendByte);

	        delayMilli();

}


void SPI_send(char byteToSend)
{
	volatile char readByte;

	set_SS_lo();

	UCB0TXBUF = byteToSend;

	while(!(UCB0RXIFG & IFG2))
	{
		// wait until you've received a byte
	}

	readByte = UCB0RXBUF;

	set_SS_hi();
}


void delayMicro(){			//  delays 42 clock cycles, calculated in lab 3
	__delay_cycles(42);
}
void delayMilli(){			//	delays 1688 clock cycles calculated in lab 3
	__delay_cycles(1688);
}
void set_SS_lo(){
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;


}
void set_SS_hi(){
	P1DIR |= BIT0;
	P1OUT |= BIT0;

}
void cursorToLineOne(){
	writeCommandByte(2);

}

void cursorToLineTwo(){
	writeCommandByte(0xc0);


}

void writeChar( char charToWrite )
{

	writeDataByte( charToWrite );

}
void createString( char string[], int stringLength )		//  consulted c2c mordan. takes the string and writes the character at that location based off of an array
{

	int i;

	for( i=0; i<stringLength; i++ )
	{
		writeChar( string[i] );
	}
}
void scrollLCD( char string[], int stringLength )		//  shifts the characters across the lcd.
{
	int i = 0;
	int tempChar = string[0];
	for( i=0; i < stringLength; i++ )
	{
		string[i] = string[i+1];
	}
	string[stringLength-1] = tempChar;
}


