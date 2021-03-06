/*Author C2C Rasmussen
 * Date Oct 28 13
 *
 * Declares all of the methods
 */



#ifndef LCD_H_
#define LCD_H_

void initSPI();

void LCDinit();

void LCDclear();

void cursorToLineTwo();

void cursorToLineOne();

void writeChar(char letter);

void createString(char string[], int stringLength);

void scrollLCD(char  string[], int stringLength);

void delayMicro();
void delayMilli();
void set_SS_lo();
void set_SS_hi();

//possibly for working on B functionality

void Check_Button();

//here for working on A functionality
void Cal_Clock();
void LCD_write_4(char byteToSend);
void LCD_write_8(char byteToSend);
void SPI_send(char byteToSend);
void writeDataByte(char dataByte);
void writeCommandNibble(char commandNibble);
void writeCommandByte(char commandByte);

#endif


