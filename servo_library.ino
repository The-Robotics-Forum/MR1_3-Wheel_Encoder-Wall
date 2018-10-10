#include<avr/io.h>
#include<math.h>
void servoattach(short int num,int value)       //value=clock frequency and num=pin no.to be attached
{
  switch(num)
  {
   case 11 :                            //OC1A
      DDRB|=(1<<PB5); // PORTB as OUTPUT
      TCCR1A|=(1<<WGM11)|(1<<COM1A1)|(1<<COM1A0);  //SETTING PRESCALAR AS 64 
      TCCR1B|=(1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11); //FAST PWM MODE
      ICR1=5000*value/16-1;                    //generating 20msec pulse (pwm method)
      break; 

   case 12 :                            //OC1B
      DDRB|=(1<<PB6); // PORTB as OUTPUT
      TCCR1A|=(1<<WGM11)|(1<<COM1B1)|(1<<COM1B0);  //SETTING PRESCALAR AS 64 
      TCCR1B|=(1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11); //FAST PWM MODE
      ICR1=5000*value/16-1;                    //generating 20msec pulse (pwm method)
      break;

    case 5 :                            //OC3A
      DDRE|=(1<<PE3); // PORTB as OUTPUT
      TCCR3A|=(1<<WGM31)|(1<<COM3A1)|(1<<COM3A0);  //SETTING PRESCALAR AS 64 
      TCCR3B|=(1<<WGM12)|(1<<WGM13)|(1<<CS30)|(1<<CS31); //FAST PWM MODE
      ICR3=5000*value/16-1;                    //generating 20msec pulse (pwm method)
      break;

    case 2 :                            //OC3B
      DDRE|=(1<<PE4); // PORTB as OUTPUT
      TCCR3A|=(1<<WGM31)|(1<<COM3B1)|(1<<COM3B0);  //SETTING PRESCALAR AS 64 
      TCCR3B|=(1<<WGM32)|(1<<WGM33)|(1<<CS30)|(1<<CS31); //FAST PWM MODE
      ICR3=5000*value/16-1;                    //generating 20msec pulse (pwm method)
      break;
   
    case 3 :                            //OC3C
      DDRE|=(1<<PE5); // PORTB as OUTPUT
      TCCR3A|=(1<<WGM31)|(1<<COM3C1)|(1<<COM3C0);  //SETTING PRESCALAR AS 64 
      TCCR3B|=(1<<WGM32)|(1<<WGM33)|(1<<CS30)|(1<<CS31); //FAST PWM MODE
      ICR3=5000*value/16-1;                    //generating 20msec pulse (pwm method)
      break;

    case 6 :                            //OC4A
      DDRH|=(1<<PH3); // PORTB as OUTPUT
      TCCR4A|=(1<<WGM41)|(1<<COM4A1)|(1<<COM4A0);  //SETTING PRESCALAR AS 64 
      TCCR4B|=(1<<WGM42)|(1<<WGM43)|(1<<CS40)|(1<<CS41); //FAST PWM MODE
      ICR4=5000*value/16-1;                    //generating 20msec pulse (pwm method)
      break;

    case 7 :                            //OC4B
      DDRH|=(1<<PH4); // PORTB as OUTPUT
      TCCR4A|=(1<<WGM41)|(1<<COM4B1)|(1<<COM4B0);  //SETTING PRESCALAR AS 64 
      TCCR4B|=(1<<WGM42)|(1<<WGM43)|(1<<CS40)|(1<<CS41); //FAST PWM MODE
      ICR4=5000*value/16-1;                    //generating 20msec pulse (pwm method)
      break;

    case 8 :                            //OC4C
      DDRH|=(1<<PH5); // PORTB as OUTPUT
      TCCR4A|=(1<<WGM41)|(1<<COM4C1)|(1<<COM4C0);  //SETTING PRESCALAR AS 64 
      TCCR4B|=(1<<WGM42)|(1<<WGM43)|(1<<CS40)|(1<<CS41); //FAST PWM MODE
      ICR4=5000*value/16-1;                    //generating 20msec pulse (pwm method)
      break;

    case 46 :                           //OC5A 
      DDRL|=(1<<PL3); // PORTB as OUTPUT
      TCCR5A|=(1<<WGM51)|(1<<COM5A1)|(1<<COM5A0);  //SETTING PRESCALAR AS 64 
      TCCR5B|=(1<<WGM52)|(1<<WGM53)|(1<<CS50)|(1<<CS51); //FAST PWM MODE
      ICR5=5000*value/16-1;                    //generating 20msec pulse (pwm method)
      break;

    case 45 :                           //OC5B
      DDRL|=(1<<PL4); // PORTB as OUTPUT
      TCCR5A|=(1<<WGM51)|(1<<COM5B1)|(1<<COM5B0);  //SETTING PRESCALAR AS 64 
      TCCR5B|=(1<<WGM52)|(1<<WGM53)|(1<<CS50)|(1<<CS51); //FAST PWM MODE
      ICR5=5000*value/16-1;                    //generating 20msec pulse (pwm met)
      break;

    case 44 :                           //OC5C
      DDRL|=(1<<PL5); // PORTB as OUTPUT
      TCCR5A|=(1<<WGM51)|(1<<COM5C1)|(1<<COM5C0);  //SETTING PRESCALAR AS 64 
      TCCR5B|=(1<<WGM52)|(1<<WGM53)|(1<<CS50)|(1<<CS51); //FAST PWM MODE
      ICR5=5000*value/16-1;                    //generating 20msec pulse (pwm method)
      break;

    default :
      break;
   }
}

void servoPSPwrite(short int pin,int val)           //PIN=servo pin no. on mega,val=angle value for the servo at pin
{
  switch(pin)
  {
   case 11:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR1A=ICR1-val;
      break;
    case 12:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR1B=ICR1-val;
      break;
    case 5:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR3A=ICR3-val;
      break;
    case 2:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR3B=ICR3-val;
      break;
    case 3:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR3C=ICR3-val;
      break;
    case 6:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR4A=ICR4-val;
      break;
    case 7:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR4B=ICR4-val;
      break; 
    case 8:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR4C=ICR4-val;
      break;
    case 46:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR5A=ICR5-val;
      break;
    case 45:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR5B=ICR5-val;
      break;
    case 44:
      val=map(val,0,180,ICR1/40,ICR1/8);
      OCR5C=ICR5-val;
      break;
    default :
      break;
  }
  //val = map(val,0,180,125,625);             //mapping one to one values
  //OCR1A= ICR1-val;                              //GENERATING PULSE IN INVERTED MODE
 //_delay_ms(500);                              //give delay in the main code
}

void deattach(short int pin1)                   //pin1=pin no. to be deattached
{
 switch(pin1)
  {
   case 11 :                            //OC1A
      DDRB|=(1<<PB5); // PORTB as OUTPUT
      TCCR1A|=(0<<WGM11)|(0<<COM1A1)|(0<<COM1A0);  //SETTING PRESCALAR AS 64 
      TCCR1B|=(0<<WGM12)|(0<<WGM13)|(0<<CS10)|(0<<CS11); //FAST PWM MODE
      ICR1=0;                    //generating 20msec pulse (pwm method)
      OCR1A=0;
      break; 

   case 12 :                            //OC1B
      DDRB|=(1<<PB6); // PORTB as OUTPUT
      TCCR1A|=(0<<WGM11)|(0<<COM1B1)|(0<<COM1B0);  //SETTING PRESCALAR AS 64 
      TCCR1B|=(0<<WGM12)|(0<<WGM13)|(0<<CS10)|(0<<CS11); //FAST PWM MODE
      ICR1=0;                    //generating 20msec pulse (pwm method)
      OCR1B=0;
      break;

    case 5 :                            //OC3A
      DDRE|=(1<<PE3); // PORTB as OUTPUT
      TCCR3A|=(0<<WGM31)|(0<<COM3A1)|(0<<COM3A0);  //SETTING PRESCALAR AS 64 
      TCCR3B|=(0<<WGM12)|(0<<WGM13)|(0<<CS30)|(0<<CS31); //FAST PWM MODE
      ICR3=0;                    //generating 20msec pulse (pwm method)
      OCR3A=0;
      break;

    case 2 :                            //OC3B
      DDRE|=(1<<PE4); // PORTB as OUTPUT
      TCCR3A|=(0<<WGM31)|(0<<COM3B1)|(0<<COM3B0);  //SETTING PRESCALAR AS 64 
      TCCR3B|=(0<<WGM32)|(0<<WGM33)|(0<<CS30)|(0<<CS31); //FAST PWM MODE
      ICR3=0;                    //generating 20msec pulse (pwm method)
      OCR3B=0;
      break;
   
    case 3 :                            //OC3C
      DDRE|=(1<<PE5); // PORTB as OUTPUT
      TCCR3A|=(0<<WGM31)|(0<<COM3C1)|(0<<COM3C0);  //SETTING PRESCALAR AS 64 
      TCCR3B|=(0<<WGM32)|(0<<WGM33)|(0<<CS30)|(0<<CS31); //FAST PWM MODE
      ICR3=0;                             //generating 20msec pulse (pwm method)
      OCR3C=0;
      break;

    case 6 :                            //OC4A
      DDRH|=(1<<PH3); // PORTB as OUTPUT
      TCCR4A|=(0<<WGM41)|(0<<COM4A1)|(0<<COM4A0);  //SETTING PRESCALAR AS 64 
      TCCR4B|=(0<<WGM42)|(0<<WGM43)|(0<<CS40)|(0<<CS41); //FAST PWM MODE
      ICR4=0;                    //generating 20msec pulse (pwm method)
      OCR4A=0;
      break;

    case 7 :                            //OC4B
      DDRH|=(1<<PH4); // PORTB as OUTPUT
      TCCR4A|=(0<<WGM41)|(0<<COM4B1)|(0<<COM4B0);  //SETTING PRESCALAR AS 64 
      TCCR4B|=(0<<WGM42)|(0<<WGM43)|(0<<CS40)|(0<<CS41); //FAST PWM MODE
      ICR4=0;                    //generating 20msec pulse (pwm method)
      OCR4B=0;
      break;

    case 8 :                            //OC4C
      DDRH|=(1<<PH5); // PORTB as OUTPUT
      TCCR4A|=(0<<WGM41)|(0<<COM4C1)|(0<<COM4C0);  //SETTING PRESCALAR AS 64 
      TCCR4B|=(0<<WGM42)|(0<<WGM43)|(0<<CS40)|(0<<CS41); //FAST PWM MODE
      ICR4=0;                    //generating 20msec pulse (pwm method)
      OCR4C=0;
      break;

    case 46 :                           //OC5A 
      DDRL|=(1<<PL3); // PORTB as OUTPUT
      TCCR5A|=(0<<WGM51)|(0<<COM5A1)|(0<<COM5A0);  //SETTING PRESCALAR AS 64 
      TCCR5B|=(0<<WGM52)|(0<<WGM53)|(0<<CS50)|(0<<CS51); //FAST PWM MODE
      ICR5=0;                    //generating 20msec pulse (pwm method)
      OCR5A=0;
      break;

    case 45 :                           //OC5B
      DDRL|=(1<<PL4); // PORTB as OUTPUT
      TCCR5A|=(0<<WGM51)|(0<<COM5B1)|(0<<COM5B0);  //SETTING PRESCALAR AS 64 
      TCCR5B|=(0<<WGM52)|(0<<WGM53)|(0<<CS50)|(0<<CS51); //FAST PWM MODE
      ICR5=0;                    //generating 20msec pulse (pwm met)
      OCR5B=0;
      break;

    case 44 :                           //OC5C
      DDRL|=(1<<PL5); // PORTB as OUTPUT
      TCCR5A|=(0<<WGM51)|(0<<COM5C1)|(0<<COM5C0);  //SETTING PRESCALAR AS 64 
      TCCR5B|=(0<<WGM52)|(0<<WGM53)|(0<<CS50)|(0<<CS51); //FAST PWM MODE
      ICR5=0;                    //generating 20msec pulse (pwm method)
      OCR5C=0;
      break;

    default :
      break; 
  }   
}
