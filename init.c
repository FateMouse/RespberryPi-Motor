#include<wiringPi.h>
#include<stdio.h>
#include<time.h>

void low();
void high();
void loop(float len);

int main()
{
	int i=0;

	printf("-----micros=%d\n",micros());
	wiringPiSetup();
	pinMode(25,OUTPUT);
	pinMode(24,OUTPUT);
	pinMode(23,OUTPUT);
	pinMode(22,OUTPUT);

	printf("-----micros=%d\n",micros());
	
	printf("-----micros=%d\n",micros());
	for(i = 0; i <= 100; i++) 
	{
		loop(2.1);	
	}

	printf("-----micros=%d\n",micros());
	for(i = 0; i <= 10000; i++) 
	{
		loop(0.9);	
	}



	printf("-----micros=%d\n",micros());
	for(i = 0; i <= 1100; i++) 
	{
		loop(1.3);	
	}
}

void low()
{
	
	digitalWrite(25,LOW);
	digitalWrite(24,LOW);
	digitalWrite(23,LOW);
	digitalWrite(22,LOW);
}
void high()
{
	digitalWrite(25,HIGH);
	digitalWrite(24,HIGH);
	digitalWrite(23,HIGH);
	digitalWrite(22,HIGH);
	
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
