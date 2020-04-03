#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h> 
#include <stdlib.h>

/*void init_adc()
{
	DDRA = 0x0;
    //set ADC VRef to AVCC
    ADMUX |= (1 << REFS0);
    //enable ADC and set pre-scaler to 128
    ADCSRA = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADEN);
}

uint16_t read_adc(unsigned char channel)
{       
    ADMUX |= (ADMUX & 0xF8) | (channel & 0x0F);

    //start ADC conversion
    ADCSRA |= (1 << ADSC);

    //wait for conversion to finish
    while(ADCSRA & (1 << ADSC));

    //ADCSRA |= (1 << ADIF); //reset as required      

    return ADC;
}
*/
#define SERVO1_CONTROL_PORT PD5
#define SERVO2_CONTROL_PORT PD4

// OCR1B
#define SERVO1_UP 200
#define SERVO1_DOWN 400

// OCR1A
#define SERVO2_UP 200
#define SERVO2_DOWN 400

void timer1_init() {
	OCR1A = SERVO1_UP;
	OCR1B = SERVO2_UP;
   //Configure TIMER1
   TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
   TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

   ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).
}

void IO_init() {
    // PWM Pins as Out
    // SERVO1 is controled by OCR1B
    // SERVO2 is controlled by OCR1A
    DDRD |= (1 << SERVO1_CONTROL_PORT) | (1 << SERVO2_CONTROL_PORT);
}

void Wait()
{
   uint8_t i;
   for(i=0;i<12;i++)
   {
      _delay_loop_2(0);
      _delay_loop_2(0);
      _delay_loop_2(0);
   }

}

void shuffleTarg() {
	int target = rand();
	if (target % 2 == 0) {
		// servo1 sus
		OCR1A = SERVO1_UP;
	} else {
		// servo2 sus
		OCR1B = SERVO2_UP;
	}
}

void easy() {
	for(int i = 0; i < 10; i++) {
		shuffleTarg();
		_delay_ms(200);
		if(OCR1A == SERVO1_UP) {
			OCR1A = SERVO1_DOWN;
		}
		if(OCR1B == SERVO2_UP) {
			OCR1B = SERVO2_DOWN;
		}
		//_delay_ms(200);
	}
}

void medium() {
	for(int i = 0; i < 10; i++) {
		shuffleTarg();
		if(OCR1A == SERVO1_UP) {
			OCR1A = SERVO1_DOWN;
		}
		if(OCR1B == SERVO2_UP) {
			OCR1B = SERVO2_DOWN;
		}
		_delay_ms(100);
	}
}

void hard() {
	for(int i = 0; i < 10; i++) {
		shuffleTarg();
		if(OCR1A == SERVO1_UP) {
			OCR1A = SERVO1_DOWN;
		}
		if(OCR1B == SERVO2_UP) {
			OCR1B = SERVO2_DOWN;
		}
		_delay_ms(50);
	}
}


int main()
{	
	//double sensorPin1, sensorPin2, room1, room2, diff0, diff1, tolerance = 80;
	//int threshold = 60; 
	timer1_init();
	IO_init();
	//init_adc();
	int i;
	//room1 = read_adc(0);
	//room2 = read_adc(1);


	while(1) {
		//sensorPin1 = read_adc(0);
		//sensorPin2 = read_adc(1);

		//diff0 = sensorPin1 - room1;
		//diff1 = sensorPin2 - room2;
		/*if (diff0 > tolerance && OCR1A == SERVO1_UP) {
				// servo1 jos
			OCR1A = SERVO1_DOWN;
			_delay_ms(200);
			
		}
		if (diff1 > tolerance && OCR1B == SERVO2_UP) {		
			// servo2 jos
			OCR1B = SERVO2_DOWN;
			_delay_ms(200);
			}
		if (OCR1B == SERVO2_DOWN && OCR1A == SERVO1_DOWN) {
			shuffleTarg();
		}*/
		OCR1A = SERVO1_DOWN;

		//_delay_ms(2000);

		OCR1B = SERVO2_DOWN;
		_delay_ms(200);
		OCR1A = SERVO1_UP;
		OCR1B = SERVO2_UP;
		// easy:
		for(i = 0; i < 20; i++) {
			shuffleTarg();
			_delay_ms(1600);
			if(OCR1A == SERVO1_UP) {
				OCR1A = SERVO1_DOWN;
			}
			if(OCR1B == SERVO2_UP) {
				OCR1B = SERVO2_DOWN;
			}
			_delay_ms(800);
		}
		//medium:
		for(i = 0; i < 20; i++) {
			shuffleTarg();
			_delay_ms(800);
			if(OCR1A == SERVO1_UP) {
				OCR1A = SERVO1_DOWN;
			}
			if(OCR1B == SERVO2_UP) {
				OCR1B = SERVO2_DOWN;
			}
			_delay_ms(400);
		}
		//hard():
		for(i = 0; i < 20; i++) {
			shuffleTarg();
			_delay_ms(400);
			if(OCR1A == SERVO1_UP) {
				OCR1A = SERVO1_DOWN;
			}
			if(OCR1B == SERVO2_UP) {
				OCR1B = SERVO2_DOWN;
			}
			_delay_ms(200);
		}
	}
	return 0;
}

