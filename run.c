#include<wiringPi.h>
#include<stdio.h>
#include<time.h>

#define PIN1 25
#define PIN2 24
#define PIN3 23
#define PIN4 22

void low();
void high();
void loop(float len);

int main()
{
	int i=0;

	printf("-----micros=%d\n",micros());
	wiringPiSetup();
	pinMode(PIN1,OUTPUT);
	pinMode(PIN2,OUTPUT);
	pinMode(PIN3,OUTPUT);
	pinMode(PIN4,OUTPUT);
	
	for(i=1;i<=50;i++)
	{
		loop(1+0.3*i/50);	
	}
}

void low()
{
	
	digitalWrite(PIN1,LOW);
	digitalWrite(PIN2,LOW);
	digitalWrite(PIN3,LOW);
	digitalWrite(PIN4,LOW);
	
}
void high()
{
	digitalWrite(PIN1,HIGH);
	digitalWrite(PIN2,HIGH);
	digitalWrite(PIN3,HIGH);
	digitalWrite(PIN4,HIGH);
	
}
//len 0.92-2.12ms
void loop(float len)
{
	int end;
	int start=micros();

	high();
	delayMicroseconds(len*1000);
	end = micros();
	printf("high=%d\n",end-start);

	low();
	delayMicroseconds(20000+start-micros());
	end = micros();
	printf("cycle=%d\n",end-start);
}
