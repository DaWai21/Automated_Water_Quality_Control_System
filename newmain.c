
#include "16x2.h"

void Lcd_Port(char a)
{
//    D4=(a & 1) ? 1:0;
//    D5=(a & 2) ? 1:0;
//    D6=(a & 4) ? 1:0;
//    D7=(a & 8) ? 1:0;
	if(a & 1) D4 = 1;
	else D4 = 0;
	if(a & 2) D5 = 1;	
	else D5 = 0;
	if(a & 4) D6 = 1;
	else D6 = 0;
    if(a & 8) D7 = 1;
	else D7 = 0;
}
void Lcd_Cmd(char a)
{
	RS = 0;             // => RS = 0
	Lcd_Port(a);
	EN  = 1;             // => E = 1
    __delay_ms(2);
    EN  = 0;             // => E = 0
}
void Lcd_Clear()
{
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}
void Lcd_Init()
{
    LCD_PORT_DIR=0X03;
    LCD_PORT=0;
    ////////////////////////////////
  Lcd_Port(0x00);
   __delay_ms(100);
  Lcd_Cmd(0x03);
	__delay_ms(5);
  Lcd_Cmd(0x03);
	__delay_ms(2);
  Lcd_Cmd(0x03);
	__delay_ms(2);
  Lcd_Cmd(0x02);
    __delay_ms(2);
/////////////////////////////////////////////////////
  Lcd_Cmd(0x02);//0010
  Lcd_Cmd(0x08);//1000 // N F * *
  __delay_ms(1);
  //N Line Number N=1 2 line use N=0 1 Line use
  //F Font Style  F=1 5x10 Style F=0 5x7 Style
  Lcd_Cmd(0x00);//0000 
  Lcd_Cmd(0x0C);//1100 // 1 Display Cursor Blink
  __delay_ms(1);
  // 1 on // 0 off
  
  Lcd_Clear();
  __delay_ms(4);
  
  Lcd_Cmd(0x00);//0000
  Lcd_Cmd(0x06);//0110  1 0 I/D S
  __delay_ms(1);
  // I/D I/D=1 increase display address I/D=0 decrease display address
  // S=1 Shift S=0 not Shift
}

void Lcd_Set_Cursor(char line, char place)
{
	char temp,z,y;
	if(line == 1)
	{
	  temp = 0x80 + place - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
	else if(line == 2)
	{
		temp = 0xC0 + place - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
}

void Lcd_Write_Char(char a)
{
   char F1,F2;
   F1 = a&0x0F;//LSB 4 bit
   F2 = a>>4;//MSB 4 bit
   RS = 1;                  // => RS = 1
   Lcd_Port(F2); //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
   Lcd_Port(F1);
   EN = 1;
   __delay_us(40);
   EN = 0;
}

void Lcd_Write_String(char *a)
{
	char i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right()
{
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left()
{
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x08);
}

