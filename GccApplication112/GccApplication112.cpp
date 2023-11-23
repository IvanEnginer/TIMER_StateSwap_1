#include <avr/io.h>
#include <avr/interrupt.h>

int NewState,OldState,vol,upState,dowState;

ISR(TIMER1_COMPA_vect)
{
	NewState=PINA&0b00000011;
	if (NewState!=OldState)
	{
		switch(OldState)
		{
			case 2:
			{
				if(NewState == 3) upState++;
				if(NewState == 0)dowState++;
				break;
			}
			case 0:
			{
				if(NewState == 2) upState++;
				if(NewState == 1) dowState++;
				break;
			}
			case 1:
			{
				if(NewState == 0) upState++;
				if(NewState == 3) dowState++;
				break;
			}
			case 3:
			{
				if(NewState == 1) upState++;
				if(NewState == 2) dowState++;
				break;
			}
		}
		OldState=NewState;
	}
	TCNT1H=0x00;
	TCNT1L=0x00;
}

int main(void)
{
	PORTA=0x03;
	DDRA=0x00;
	PORTB=0x00;
	DDRB=0xFF;
	TCCR1A=0x00;
	TCCR1B=0x0A;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x03;
	OCR1AL=0xE8;
	OCR1BH=0x00;
	OCR1BL=0x00;
	TIMSK=0x10;
	sei();
	while(1)
	{
		if (upState >= 4)
		{
			vol++;
			upState = 0;
		}
		if (dowState >= 4)
		{
			vol--;
			dowState = 0;
		}
		switch(vol)
		{
			case 0:{PORTB=0x00; break;}
			case 1:{PORTB=0x01; break;}
			case 2:{PORTB=0x02; break;}
			case 3:{PORTB=0x04; break;}
			case 4:{PORTB=0x08; break;}
			case 5:{PORTB=0x10; break;}
			case 6:{PORTB=0x20; break;}
			case 7:{PORTB=0x40; break;}
			case 8:{PORTB=0x80; break;}
			case 9:{PORTB=0x100; break;}
		}
		if (vol == 10)
		{
			vol=0;
		}
		if (vol < 0)
		{
			vol=0;
		}

	}
}