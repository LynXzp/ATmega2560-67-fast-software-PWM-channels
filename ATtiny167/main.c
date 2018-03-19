#include <avr/io.h>
// #include <avr/interrupt.h>
// #include <avr/pgmspace.h>
// #include <avr/wdt.h>
#include <limits.h>
#define CLR_BIT(a,b) ((a) &=~(1<<(b)))
#define SET_BIT(a,b) ((a) |= (1<<(b)))
#define TST_BIT(a,b) ((a) & (1<<(b)))
#define CHANGE_BIT(a,b) ((a) ^= (1<<(b)))
#define F_CPU 16000000UL  // 16 MHz
#ifndef ALIBC_OLD
#include <util/delay.h>
#else
#include <avr/delay.h>
#endif

uint8_t maxi[13]={251, 241, 239, 233, 229, 227, 223, 211, 199, 197, 193, 191, 181}; // prime numbers, using cicada cycles

uint8_t tcnt=1;	// software TCNT - counter itself
uint8_t ocr[13]={1,1,1,1,1,1,1,1,1,1,1,1,1}; // software compare registers
int8_t direction[13]={1,1,1,1,1,1,1,1,1,1,1,1,1};	// direction - raising or faiding
uint16_t aditionalOffDelay[13];	// additional delay, because led ever with 1% is bright, and almost never real off

enum{LOW=0,HIGH=1};
static void digitalWrite(uint8_t pin,uint8_t voltage);
static void blink(int n);
int main(void)
{
	DDRB|=0b01001111;
	DDRA|=0b01111111;

	while(1)
	{	tcnt++;
		for(uint8_t pin=0;pin<=12;pin+=1)
		{
			if(aditionalOffDelay[pin])
				{	aditionalOffDelay[pin]--; 
					continue;
				}

			if(tcnt==0)
				{	ocr[pin]+=direction[pin];
				}

			if(ocr[pin]>=maxi[pin])
				{	ocr[pin]=maxi[pin]-1; direction[pin]=-1;
				}

			if(ocr[pin]<=0)
				{	ocr[pin]=1; direction[pin]=1;
				}

			if((ocr[pin]==1)&&(tcnt==0))
				{	aditionalOffDelay[pin]=1ULL*maxi[pin]*maxi[pin];
					continue;
				}

			if(tcnt<ocr[pin])
				{	digitalWrite(pin,HIGH);
				}
			else
				digitalWrite(pin,LOW);
		}
	}
}

static void digitalWrite(uint8_t pin,uint8_t voltage)
{
	switch (pin)
		{	case 0:	voltage ? SET_BIT(PORTB,0) : CLR_BIT(PORTB,0);	break;
			case 1:	voltage ? SET_BIT(PORTB,1) : CLR_BIT(PORTB,1);	break;
			case 2:	voltage ? SET_BIT(PORTB,2) : CLR_BIT(PORTB,2);	break;
			case 3:	voltage ? SET_BIT(PORTB,6) : CLR_BIT(PORTB,6);	break;
			case 4:	voltage ? SET_BIT(PORTB,3) : CLR_BIT(PORTB,3);	break;
			case 5:	voltage ? SET_BIT(PORTA,7) : CLR_BIT(PORTA,7);	break;
			case 6:	voltage ? SET_BIT(PORTA,0) : CLR_BIT(PORTA,0);	break;
			case 7:	voltage ? SET_BIT(PORTA,1) : CLR_BIT(PORTA,1);	break;
			case 8:	voltage ? SET_BIT(PORTA,2) : CLR_BIT(PORTA,2);	break;
			case 9:	voltage ? SET_BIT(PORTA,3) : CLR_BIT(PORTA,3);	break;
			case 10:voltage ? SET_BIT(PORTA,4) : CLR_BIT(PORTA,4);	break;
			case 11:voltage ? SET_BIT(PORTA,5) : CLR_BIT(PORTA,5);	break;
			case 12:voltage ? SET_BIT(PORTA,6) : CLR_BIT(PORTA,6);	break;
		}
}
