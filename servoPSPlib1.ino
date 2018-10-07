/* SERVO MOTOR CONTROL BY GIVING ANY SPECIFIC ANGLE
 * Grp-18
 * date:- 22/07/18
 *  
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
//function to get angular movement of servo
 int count=0,x=0;
void encodercount()
{
  /*//Serial.println("1");
  if(digitalRead(2)==LOW)
  {
    count++;
  }
  else
  {
    count--;
  }
  */
 count++;
}
void servoPSPwrite(int val)
{
  
  val = map(val, 0, 180, 125, 625); //mapping one to one values
  OCR1A= ICR1-val;  //GENERATING PULSE IN INVERTED MODE
  _delay_ms(1000);
}
int main()
{ 
  DDRB |=0xFF; // PORTB as OUTPUT
  TCCR1A |=(1<<WGM11)|(1<<COM1A1)|(1<<COM1A0);  //SETTING PRESCALAR AS 64 
  TCCR1B |=(1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11); //FAST PWM MODE
  ICR1=4999;    //generating 20msec pulse (pwm method)
 Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3),encodercount,RISING);

  while(1)
    {
     for(int i=0;i<180;i=i+10)
      {
      servoPSPwrite(i);
      x=count*360/600;
     //Serial.println(x);
       //  Seral.println(count);
      }
    count=0;
     // servoPSPwrite(85);
      //servoPSPwrite(0);

   }
}
