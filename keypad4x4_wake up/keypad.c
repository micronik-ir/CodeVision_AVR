/****************************************************
Project : 4 x 4 Keypad - Wake-up on Keypress
Version : 2
Date    : 4/5/2013
Author  : hossein ghiasvand
Company : https://www.micronik.ir
E-mail  : info@micronik.ir
Comments: 
� 16 Key Pushbutton Pad in 4 x 4 Matrix
� Very Low Power Consumption
� AVR in Sleep Mode and Wakes Up on Keypress
� Minimum External Components
� ESD Protection Included if Necessary
� Efficient Code
� Complete Program Included for AT90S1200
� Suitable for Any AVR MCU


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
****************************************************/
#include <mega16.h>
#include <delay.h>
#include <alcd.h>

#include <keypad.h>
#asm
.equ __kbd_port=0x1b ;PORTA
#endasm

_Bool wakeup=0;
char k;

void main(void)
{
DDRD=0X00;
PORTD=0Xff;
MCUCR=0x30;
GIMSK=0x40;
lcd_init(16);
lcd_clear();      
lcd_gotoxy(0,0);
lcd_putsf("Please Enter Key");
delay_ms(2000);
lcd_clear();
_lcd_write_data(0x0f);     //Cursor blanked
kbd_init();
#asm("sei")
while (1)
      {  
      if(wakeup){  
        k=getkey(); 
        wakeup=0;
        lcd_putchar(k);
        if( k=='C') lcd_clear(); //'C'-----> clear 
        };
      // Place your code here
      }
}
 
interrupt [EXT_INT0] void ext_int0_isr(void)
{
wakeup=1;
}     


