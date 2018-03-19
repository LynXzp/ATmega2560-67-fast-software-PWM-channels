#include <avr/io.h>
#include <avr/interrupt.h>
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

#define MAX 67
uint8_t maxi[MAX];//={255, 253, 251, 249, 247, 245, 243, 241, 239, 237, 235, 233, 231, 229, 227, 225, 223, 221, 219, 217, 215, 213, 211, 209};

uint8_t tcnt=1;	// software TCNT - counter itself
uint8_t ocr[MAX]; // software compare registers
int8_t direction[MAX];	// direction - raising or faiding
uint16_t aditionalOffDelay[MAX];	// additional delay, because led ever with 1% is bright, and almost never real off
uint16_t PORT=0;

#define CLR_BIT(a,b) ((a) &=~(1<<(b)))
#define SET_BIT(a,b) ((a) |= (1<<(b)))
#define TST_BIT(a,b) ((a) & (1<<(b)))
#define CHANGE_BIT(a,b) ((a) ^= (1<<(b)))

enum{HIGH=1,LOW=0};

#define MAX_PWM 256
uint8_t PA[MAX_PWM];
uint8_t PB[MAX_PWM];
uint8_t PC[MAX_PWM];
uint8_t PD[MAX_PWM];
uint8_t PE[MAX_PWM];
uint8_t PF[MAX_PWM];
uint8_t PG[MAX_PWM];
uint8_t PH[MAX_PWM];
uint8_t PJ[MAX_PWM];
uint8_t PK[MAX_PWM];
uint8_t PL[MAX_PWM];

int main()
{	
	DDRA=DDRB=DDRD=DDRC=DDRE=DDRF=DDRG=DDRH=DDRJ=DDRK=DDRL=0xff;
	// PORTA=PORTB=PORTC=PORTD=PORTE=PORTF=PORTG=PORTH=PORTJ=PORTK=PORTL=0xff;
	// while(1);

	// timer2
	TCCR2A=0;
	TCCR2B=(0<<CS22)|(0<<CS21)|(1<<CS20); 
	TIMSK2=(1<<TOIE2)|1;
	sei();

	for(uint8_t i=0;i<MAX;i++)
		{
			ocr[i]=1;
			direction[i]=1;
			maxi[i]=10+i*3.64;
		}
	while(1)
		{	
			for(uint8_t pin=0;pin<MAX;pin+=1)
				{
					if(aditionalOffDelay[pin])
						{	aditionalOffDelay[pin]--; 
							if(aditionalOffDelay[pin]==0)
								{	
									ocr[pin]=1; direction[pin]=1;
								}
							continue;
						}

					ocr[pin]+=direction[pin];
					if(ocr[pin]>=maxi[pin])
						{	ocr[pin]=maxi[pin]-1; direction[pin]=-1;
						}
					// else if(ocr[pin]<=0)
					// 	{	
					// 	}

					if((ocr[pin]==0))
						{	aditionalOffDelay[pin]=((uint16_t)maxi[pin])<<1;
							continue;
						}
				}

			for(uint16_t i=0;i<MAX_PWM;i++)
				{	if(i<ocr[0])	SET_BIT(PF[i],0);
					else		CLR_BIT(PF[i],0);
					if(i<ocr[1])	SET_BIT(PF[i],1);
					else		CLR_BIT(PF[i],1);
					if(i<ocr[2])	SET_BIT(PF[i],2);
					else		CLR_BIT(PF[i],2);
					if(i<ocr[3])	SET_BIT(PF[i],3);
					else		CLR_BIT(PF[i],3);
					if(i<ocr[4])	SET_BIT(PF[i],4);
					else		CLR_BIT(PF[i],4);
					if(i<ocr[5])	SET_BIT(PF[i],5);
					else		CLR_BIT(PF[i],5);
					if(i<ocr[6])	SET_BIT(PF[i],6);
					else		CLR_BIT(PF[i],6);
					if(i<ocr[7])	SET_BIT(PF[i],7);
					else		CLR_BIT(PF[i],7);

					if(i<ocr[8])	SET_BIT(PK[i],0);
					else		CLR_BIT(PK[i],0);
					if(i<ocr[9])	SET_BIT(PK[i],1);
					else		CLR_BIT(PK[i],1);
					if(i<ocr[10])	SET_BIT(PK[i],2);
					else		CLR_BIT(PK[i],2);
					if(i<ocr[11])	SET_BIT(PK[i],3);
					else		CLR_BIT(PK[i],3);
					if(i<ocr[12])	SET_BIT(PK[i],4);
					else		CLR_BIT(PK[i],4);
					if(i<ocr[13])	SET_BIT(PK[i],5);
					else		CLR_BIT(PK[i],5);
					if(i<ocr[14])	SET_BIT(PK[i],6);
					else		CLR_BIT(PK[i],6);
					if(i<ocr[15])	SET_BIT(PK[i],7);
					else		CLR_BIT(PK[i],7);

					if(i<ocr[16])	SET_BIT(PB[i],0);
					else		CLR_BIT(PB[i],0);
					if(i<ocr[17])	SET_BIT(PB[i],1);
					else		CLR_BIT(PB[i],1);
					if(i<ocr[18])	SET_BIT(PB[i],2);
					else		CLR_BIT(PB[i],2);
					if(i<ocr[19])	SET_BIT(PB[i],3);
					else		CLR_BIT(PB[i],3);

					if(i<ocr[20])	SET_BIT(PL[i],0);
					else		CLR_BIT(PL[i],0);
					if(i<ocr[21])	SET_BIT(PL[i],1);
					else		CLR_BIT(PL[i],1);
					if(i<ocr[22])	SET_BIT(PL[i],2);
					else		CLR_BIT(PL[i],2);
					if(i<ocr[23])	SET_BIT(PL[i],3);
					else		CLR_BIT(PL[i],3);
					if(i<ocr[24])	SET_BIT(PL[i],4);
					else		CLR_BIT(PL[i],4);
					if(i<ocr[25])	SET_BIT(PL[i],5);
					else		CLR_BIT(PL[i],5);
					if(i<ocr[26])	SET_BIT(PL[i],6);
					else		CLR_BIT(PL[i],6);
					if(i<ocr[27])	SET_BIT(PL[i],7);
					else		CLR_BIT(PL[i],7);

					if(i<ocr[28])	SET_BIT(PG[i],0);
					else		CLR_BIT(PG[i],0);
					if(i<ocr[29])	SET_BIT(PG[i],1);
					else		CLR_BIT(PG[i],1);
					if(i<ocr[30])	SET_BIT(PG[i],2);
					else		CLR_BIT(PG[i],2);

					if(i<ocr[31])	SET_BIT(PD[i],7);
					else		CLR_BIT(PD[i],7);

					if(i<ocr[32])	SET_BIT(PC[i],0);
					else		CLR_BIT(PC[i],0);
					if(i<ocr[33])	SET_BIT(PC[i],1);
					else		CLR_BIT(PC[i],1);
					if(i<ocr[34])	SET_BIT(PC[i],2);
					else		CLR_BIT(PC[i],2);
					if(i<ocr[35])	SET_BIT(PC[i],3);
					else		CLR_BIT(PC[i],3);
					if(i<ocr[36])	SET_BIT(PC[i],4);
					else		CLR_BIT(PC[i],4);
					if(i<ocr[37])	SET_BIT(PC[i],5);
					else		CLR_BIT(PC[i],5);
					if(i<ocr[38])	SET_BIT(PC[i],6);
					else		CLR_BIT(PC[i],6);
					if(i<ocr[39])	SET_BIT(PC[i],7);
					else		CLR_BIT(PC[i],7);

					if(i<ocr[47])	SET_BIT(PA[i],0);
					else		CLR_BIT(PA[i],0);
					if(i<ocr[46])	SET_BIT(PA[i],1);
					else		CLR_BIT(PA[i],1);
					if(i<ocr[45])	SET_BIT(PA[i],2);
					else		CLR_BIT(PA[i],2);
					if(i<ocr[44])	SET_BIT(PA[i],3);
					else		CLR_BIT(PA[i],3);
					if(i<ocr[43])	SET_BIT(PA[i],4);
					else		CLR_BIT(PA[i],4);
					if(i<ocr[42])	SET_BIT(PA[i],5);
					else		CLR_BIT(PA[i],5);
					if(i<ocr[41])	SET_BIT(PA[i],6);
					else		CLR_BIT(PA[i],6);
					if(i<ocr[40])	SET_BIT(PA[i],7);
					else		CLR_BIT(PA[i],7);

					if(i<ocr[48])	SET_BIT(PD[i],0);
					else		CLR_BIT(PD[i],0);
					if(i<ocr[49])	SET_BIT(PD[i],1);
					else		CLR_BIT(PD[i],1);
					if(i<ocr[50])	SET_BIT(PD[i],2);
					else		CLR_BIT(PD[i],2);
					if(i<ocr[51])	SET_BIT(PD[i],3);
					else		CLR_BIT(PD[i],3);

					if(i<ocr[52])	SET_BIT(PH[i],0);
					else		CLR_BIT(PH[i],0);
					if(i<ocr[53])	SET_BIT(PH[i],1);
					else		CLR_BIT(PH[i],1);

					if(i<ocr[54])	SET_BIT(PJ[i],0);
					else		CLR_BIT(PJ[i],0);
					if(i<ocr[55])	SET_BIT(PJ[i],1);
					else		CLR_BIT(PJ[i],1);

					if(i<ocr[56])	SET_BIT(PE[i],0);
					else		CLR_BIT(PE[i],0);
					if(i<ocr[57])	SET_BIT(PE[i],1);
					else		CLR_BIT(PE[i],1);
					if(i<ocr[58])	SET_BIT(PE[i],4);
					else		CLR_BIT(PE[i],4);
					if(i<ocr[58])	SET_BIT(PE[i],5);
					else		CLR_BIT(PE[i],5);

					if(i<ocr[59])	SET_BIT(PG[i],5);
					else		CLR_BIT(PG[i],5);

					if(i<ocr[60])	SET_BIT(PE[i],3);
					else		CLR_BIT(PE[i],3);

					if(i<ocr[61])	SET_BIT(PH[i],3);
					else		CLR_BIT(PH[i],3);
					if(i<ocr[62])	SET_BIT(PH[i],4);
					else		CLR_BIT(PH[i],4);
					if(i<ocr[63])	SET_BIT(PH[i],5);
					else		CLR_BIT(PH[i],5);
					if(i<ocr[64])	SET_BIT(PH[i],6);
					else		CLR_BIT(PH[i],6);

					if(i<ocr[65])	SET_BIT(PB[i],4);
					else		CLR_BIT(PB[i],4);
					if(i<ocr[66])	SET_BIT(PB[i],5);
					else		CLR_BIT(PB[i],5);
					if(i<ocr[67])	SET_BIT(PB[i],6);
					else		CLR_BIT(PB[i],6);
					if(i<ocr[68])	SET_BIT(PB[i],7);
					else		CLR_BIT(PB[i],7);
					// _delay_us(100);
				}
		}
}

ISR(TIMER2_OVF_vect)
{
	static uint8_t iteration=0;
	iteration++;
	if(iteration==MAX_PWM)iteration=0;
	PORTA=PA[iteration];
	PORTB=PB[iteration];
	PORTC=PC[iteration];
	PORTD=PD[iteration];
	PORTE=PE[iteration];
	PORTF=PF[iteration];
	PORTG=PG[iteration];
	PORTH=PH[iteration];
	PORTJ=PJ[iteration];
	PORTK=PK[iteration];
	PORTL=PL[iteration];
}
