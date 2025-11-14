 
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE =  ON     // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       
#pragma config FCMEN = OFF      
#pragma config LVP = OFF        

// CONFIG2
#pragma config BOR4V = BOR40V   
#pragma config WRT = OFF       

#define   _XTAL_FREQ   4000000 //to use delay function from XC8 library

#include <xc.h>    
#include <stdio.h>
#include "16x2.h"


int ADC_READ_CH(char channel);
void main() 
{
    int ADC_Value;
    float WL;
    float TD;
    float x;
    char buffer[10];
    ANSELH=0x00;
    ANSEL=0b00001111;//AN0 AN1 & AN2 are analog
    TRISA=0XFF;//RA0 AN1 & RA2 are input
    TRISD=0X00;   
    TRISC=0X00;
    C1ON = C2ON = 0;//Disable comparators
    ADCON0=0X41;
    ADCON1=0X80;
    Lcd_Init();
    Lcd_Clear();
    TRISD=0X00;
    RC1=1;
       Lcd_Set_Cursor(1,1);
    Lcd_Write_String("MarYar Mal");
    __delay_ms(300);
    Lcd_Clear();
    __delay_ms(300);
     ADC_Value=ADC_READ_CH(1);
////       WL= (ADC_Value*5.0)/1023.0;
////       pH= -5.70*WL +CV;
////       sprintf(buffer,"pH =%.2f",pH);//float to string
////     
////       Lcd_Set_Cursor(2 ,1);
////       Lcd_Write_String(buffer);//string output
//        __delay_ms(300);
        do{
        ADC_Value=ADC_READ_CH(1);
       WL= (ADC_Value*5.0)/1023.0;
//       sprintf(buffer,"V2 =%.2fV",Result);//float to string
       if(WL<2.8)
       {
          
           RD1=0;
           Lcd_Set_Cursor(1,1);
           Lcd_Write_String("WL_LOW");
           Lcd_Set_Cursor(2,1);
           Lcd_Write_String("Motor On");
           __delay_ms(1000);
           Lcd_Clear();
       }
       else
       {
          
          RD1=1;
           Lcd_Set_Cursor(1,1);
           Lcd_Write_String("WL_HIGJ");
          Lcd_Set_Cursor(2,1);
          Lcd_Write_String("Motor OFF");
          __delay_ms(1000);
          Lcd_Clear();
   
        do{
            ADC_Value=ADC_READ_CH(0);
       TD= (ADC_Value*5.0)/1023.0;
//       sprintf(buffer,"TD =%.2fV",TD);//float to string
//            Lcd_Set_Cursor(2 ,1);
//            Lcd_Write_String(buffer);//string output
//            __delay_ms(300);
//            Lcd_Clear();
//           __delay_ms(5000);
      if(TD>0.5)
       {
          
          RD0=0;
           Lcd_Set_Cursor(1,1);
           Lcd_Write_String("DIRTY");
           Lcd_Set_Cursor(2,1);
           Lcd_Write_String("OUTLETOn");
           __delay_ms(1000);
           Lcd_Clear();
//         
       }
       else{
          RD0=1;
           Lcd_Set_Cursor(1,1);
           Lcd_Write_String("CLEAR");
          Lcd_Set_Cursor(2,1);
          Lcd_Write_String("OUTLET_OFF");
          __delay_ms(1000);
          Lcd_Clear();
          do{
          ADC_Value=ADC_READ_CH(3);
          x= (ADC_Value*5.0)/1023.0;
  
//          pH= -5.70*x +CV;
            sprintf(buffer,"pH =%.2fV",x);//float to string
            Lcd_Set_Cursor(2 ,1);
            Lcd_Write_String(buffer);//string output
            __delay_ms(3000);
            Lcd_Clear();
            if(x<=3 && x>=2.5)
            {
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Normal pH");
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Finish");
                __delay_ms(1000);
                Lcd_Clear();
            }
            else if(x<2.5)
            {
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Akali");
                RC1=0;
                __delay_ms(1000);
                RC1=1;
                Lcd_Clear();
            }
            else
            {
            Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Acidic");
                RC0=0;
                __delay_ms(1000);
                RC0=1;
                Lcd_Clear();
            }
            __delay_ms(1000);
          }while(x<3 && x>2.5);
       __delay_ms(1000);
       }
        }while(TD>0.5);
          
       __delay_ms(1000);
       }
       }while(WL<2.8);
       
}



int ADC_READ_CH(char channel)//channel 0 to 13
{
    int ADC_value;
    ADCON0bits.CHS=0XF & channel;
    __delay_us(20);//delay for changing Channel
    GO_nDONE=1;//start AD conversion 
    while(GO_nDONE);//wait for GO_nDONE=0 
    ADC_value=(ADRESH<<8) + ADRESL;
    return ADC_value;  
}

