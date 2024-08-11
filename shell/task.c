/*
 * task.c
 *
 *  Created on: Aug 9, 2024
 *      Author: Mariam
 */


#include "LBIT_math.h"
#include "LSTD_types.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "timers.h"

#ifdef 	F_CPU
#undef 	F_CPU
#endif
#define F_CPU 						8000000L

#define VREF                           5
#define MAXTEMPVALUE                  150
#define MAXTEMPVOLT                  1.5
#define MAXADCVALUE                   1023



u8 overflow0,overflow2;  // Overflow counters for Timer0 and Timer2
volatile u32 temp;

volatile u32 hum;

u8 speed=0;

char buffer[10];//buffer to put value of temp
char buffer1[10];//buffer to put value of speed
char buffer2[10];//buffer to put value of humidity


void UART_Ini(u32 copy_u32BaudRate)
{
	u32 UBRR_vlue=(F_CPU /(16*copy_u32BaudRate))-1;
		UBRRL=(u8)UBRR_vlue;
		UBRRH=(u8)(UBRR_vlue>>8);
		// enable transmitter and receiver
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);

	SET_BIT(UCSRC,URSEL);//writing the UCSRC.
	CLR_BIT(UCSRC, UMSEL);//Asynchronous Operation
	//SELECT Stop Bit Select
	CLR_BIT(UCSRC,USBS);
		//Character Size 8-bit
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);

}

void UART_Transmit(u8 data){
	while(GET_BIT(UCSRA,UDRE)==0);// If UDRE is one, the buffer is empty, and therefore ready to be written.
	UDR=data;
	while(GET_BIT(UCSRA,TXC)==0);//This flag bit is set when the entire frame in the transmit Shift Register has been shifted out and
	//there are no new data currently present in the transmit buffer (UDR).
}
u8 	UART_Receive(void){
	while(GET_BIT(UCSRA,RXC)==0);//This flag bit is set when there are unread data in the receive buffer and cleared when the receive
	//buffer is empty (that is, does not contain any unread data)
	return UDR;
}

void UART_TransmitString(u8* ptr_u8Data){
	u32 local_u32Counter=0;
	for(local_u32Counter=0;ptr_u8Data[local_u32Counter]!='\0';local_u32Counter++){
		UART_Transmit(ptr_u8Data[local_u32Counter]);
	}
}


int main(void)
 {
	 CLR_BIT(DDRA,PIN0);//set temp senor pin as input
	 CLR_BIT(DDRA,PIN1);//set humidity senor pin as input
	 UART_Ini(9600);//9600 baud rate
	 adc_init();
	 Timer0_init() ;
	 Timer2_init();
	 Timer1_PWM_init();

	 sei();//for interrupts


 for(;;)
	 {



	 }
 return 0;
 }





ISR(TIMER0_OVF_vect) {
   overflow0++;
   if (overflow0 >= 12) {
   	temp=read1(0);// Read temperature from ADC0
   	u32 tempValue =  (((f32) temp * VREF * MAXTEMPVALUE)/(MAXTEMPVOLT * MAXADCVALUE));


   	        if (tempValue > 25)
   	        {
   	            speed = ((tempValue - 25) * (510)/125);
   	            OCR1A = speed;
               }
   	        else
   	        {
   	          speed = 0;
   	          OCR1A = speed;
   	        }
   	  	// save temperature value in array of char to send to UART
   	        char *ptr=&tempValue;

   	        int i=0;
   	        while(i<5)
   	        {
   	        	buffer[i]=*ptr;
   	        	ptr++;
   	        	i++;
   	        }
   	     buffer[4]='\0';

   	  UART_TransmitString(buffer);
   	buffer1[0]=speed;
   	buffer1[1]='\0';
   	UART_TransmitString(buffer1);
       overflow0 = 0;
       TCNT0 = 200;  //  preload for 100ms
   }
}


ISR(TIMER2_OVF_vect) {


	 overflow2++;
   if (overflow2 >= 24) {
   	hum=read2(1); // Read humidity from ADC1

   	// save humidity  value in array of char to send to UART
   	char *ptr1=&hum;
   	   	        int i=0;
   	   	        while(i<5)
   	   	        {
   	   	        	buffer2[i]=*ptr1;
   	   	        	ptr1++;
   	   	            i++;
   	   	        }
   	   	     buffer2[4]='\0';
   	   	  UART_TransmitString(buffer2);


       overflow2 = 0;
       TCNT2 = 154;  // Reload with preload value
   }
}


