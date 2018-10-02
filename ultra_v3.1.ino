/***inverting motor driver used for wheel 2***/
/********************Defining motor driver pins **********************/
#define Dir_W1 11
#define Dir_W2 7
#define Dir_W3 16

#define PWM_W1 8
#define PWM_W2 12
#define PWM_W3 10


/****************************defining distances*****************************/
#define dist1 90  //above this run at base, below this decelerate upto dist2 linerally
#define dist2 75  //above this decelerate upto dist2 linerally, below this stop
#define dist3 60  //above this stop, below this go backwards until dist3

#define dist4 160  //below this run at base,above this decelerate upto dist5 linearly
#define dist5 180  //below this decelerate and above this stop 
#define dist6 200  //below this stop and above this go backwards
#define kp 1.25
#define base1 90
#define pingPin1 3
#define echoPin1 2
#define pingPin2 21
#define echoPin2 20

/*****************************variables**********************************/

float duration1, duration2, pwm1=0, pwm2=0, pwm3=0, cm1, cm2, i=0, j=0, x=0,base=0;
bool dirFlag=0;   //specifies the direction of the bot. 0 for forward and 1 for backward
long  microsecondsToCentimeters(long microseconds) ;
char recieved,prev=0;

/***************************functions************************************/

void forward()                                              //moves towards the wall
{
  digitalWrite(Dir_W1,HIGH);
  digitalWrite(Dir_W3,HIGH);
 for(i=pwm1;i<base1;i++) 
 {                           
    analogWrite(PWM_W1,constrain(i,0,150));
    analogWrite(PWM_W3,constrain(i,0,150));
    delay(5);
 }
 prev='f';
 pwm1=base1;
 pwm3=base1;
 base=base1;
}
 
void decelerate()                                             //decelerate the bot proportional to the cm1-dist2 from dist1                                     
{         
  i=pwm1;                                                     //storing initial value of i
  pwm1=base1*(cm1-dist2)/(dist1-dist2);                       //reduce the speed till this pwm
  pwm3=base1*(cm1-dist2)/(dist1-dist2);
  digitalWrite(Dir_W1,HIGH);
  digitalWrite(Dir_W3,HIGH);
  for(;i>=pwm1;i--)
  { 
    analogWrite(PWM_W1,constrain(i,0,150));
    analogWrite(PWM_W3,constrain(i,0,150));   
    delay(5);
  }
 prev='d';
}

void Stop()
{
    for(i=pwm1;i>=0;i--)
    {
      analogWrite(PWM_W1,constrain(i,0,150));
      analogWrite(PWM_W3,constrain(i,0,150));
      delay(5);  
    }
  pwm1=0;
  pwm3=0;  
  prev='s';                                         //to know the previous state
  base=0;
}

void reverse()                                      //reverse function i.e:away from wall 
{  
    Stop();                                         //first stop the bot before reversing the direction
    digitalWrite(Dir_W1,LOW);
    digitalWrite(Dir_W3,LOW);
    for(i=0;i<50;i+=5)
    {
      analogWrite(PWM_W1,constrain(i,0,150));
      analogWrite(PWM_W3,constrain(i,0,150));
      delay(10);  
    }
  pwm1=50;
  pwm3=50;  
  prev='r';
  base=50;
}

void forward1()                                     //moves forward i.e away from wall
{
  digitalWrite(Dir_W1,LOW);
  digitalWrite(Dir_W2,LOW);
 for(i=pwm1;i<base1;i++) 
 {                           
    analogWrite(PWM_W1,constrain(i,0,150));
    analogWrite(PWM_W2,constrain(i,0,150));
    delay(5);
 }
 prev='F';
 pwm1=base1;
 pwm2=base1;
 base=base1;
}
 
void decelerate1()
{
  i=pwm1;                                               //storing initial value of i
  digitalWrite(Dir_W1,LOW);
  digitalWrite(Dir_W2,LOW);
  pwm1=base1*(cm1-dist5)/(dist4-dist5);                 //reduce to this pwm value
  pwm2=base1*(cm1-dist5)/(dist4-dist5);     
 
  for(;i>=pwm1;i--)
  { 
    analogWrite(PWM_W1,constrain(i,0,150));
    analogWrite(PWM_W2,constrain(i,0,150));   
    delay(5);
  }
  prev='D';
}

void Stop1()
{
    for(i=pwm1;i>=0;i--)
    {
      analogWrite(PWM_W1,constrain(i,0,150));
      analogWrite(PWM_W2,constrain(i,0,150));
      delay(5);  
    }
  pwm1=0;
  pwm2=0;  
  prev='S';
  base=0;
}

void reverse1()
{  
    Stop1();
    digitalWrite(Dir_W1,HIGH);
    digitalWrite(Dir_W2,HIGH);
    for(i=0;i<50;i+=5)
    {
      analogWrite(PWM_W1,constrain(i,0,150));
      analogWrite(PWM_W2,constrain(i,0,150));
      delay(5);  
    }
  pwm1=50;
  pwm2=50;  
  prev='R';
  base=50;
}



void setup() 
{
    pinMode(pingPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(pingPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(Dir_W3, OUTPUT);
    pinMode(Dir_W2, OUTPUT);
    pinMode(Dir_W1, OUTPUT);
    Serial.begin(9600);
   
}


void loop()
{
  
    
  // put your main code here, to run repeatedly:
  digitalWrite(pingPin1, LOW);                                   //excite ultrasonic1   
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  cm1 = constrain(microsecondsToCentimeters(duration1),0,200);   //calculates ultra1 distance from wall
  
  digitalWrite(pingPin2, LOW);                                  //excite ultra2 
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  cm2 = constrain(microsecondsToCentimeters(duration2),0,200);    //calculates ultra2 distance from wall
/*if(Serial.available()>0)
{
    recieved=Serial.read();  
}
switch(recieved)
{ 
 case '1':*/
  if(abs(cm1-cm2)<=2)
  {
    dirFlag=0;
    if((cm1<=dist2&&cm1>=dist3))  //stop
     {       
      Stop();
     }
   else if(cm1>dist1)                           //run at base
    {                      
      //digitalWrite(Dir_W1,LOW);
      //digitalWrite(Dir_W3,LOW);
       forward();
    }
    
    else if(cm1<=dist1 && cm1>dist2-2)          //decelerate
     {      
      /*digitalWrite(Dir_W1,LOW);
      digitalWrite(Dir_W3,LOW);
      pwm1=base*(cm1-dist2)/(dist1-dist2);
      pwm3=base*(cm1-dist2)/(dist1-dist2);*/
      decelerate();     
     }
    else if(cm1<dist3+2)                              //move backwards, adding two for common area
    { 
      //digitalWrite(Dir_W1,HIGH);
     // digitalWrite(Dir_W3,HIGH);
      if(prev!='r')
      reverse();
      
      dirFlag=1;
     }
    else if(cm1==0) 
    {
      pwm1=0;
      pwm3=0;
      analogWrite(PWM_W1,constrain(pwm1,0,150));
      analogWrite(PWM_W3,constrain(pwm3,0,150));
    }
  }                                                   //if cm1-cm2 condition ends  
   

 else                                                //if orientation of link on which ultra are mounted not parallel to wall  
  {
    if(cm1<dist2+2&&cm1>=dist3)                      //not changing orientation in stop region 
    {
      Stop();
    }
    else 
    {
    //x=0;
    switch(dirFlag)                                 
     {
      case 0:                                         //dirflag=0 when cm1>stop condition 
        i=pwm1;
        j=pwm3;
        pwm1=base+kp*(cm2-cm1);
        pwm3=base+kp*(cm1-cm2);
        prev='3';                                      //changing prev value for (prev!=r) condition to become true if bot is in reverse region
        
        if(pwm1>i)                                    //i.e cm2>cm1 ,therefore attach ultra2 on wheel-1 side
        {
          for(;i<pwm1 && j>pwm3;i+=2,j-=2)            
          {
           analogWrite(PWM_W1,constrain(i,0,150));
           analogWrite(PWM_W3,constrain(j,0,150));
           delay(5);
          } 
        }
        else
        {
          for(;i>pwm1 && j<pwm3;i-=2,j+=2)
          {
           analogWrite(PWM_W1,constrain(i,0,150));
           analogWrite(PWM_W3,constrain(j,0,150));
           delay(5);
          } 
         }
        break;
      
      case 1:                                         //if bot is in reverse region
        i=pwm1;
        j=pwm3;
        pwm1=base+kp*(cm1-cm2);                       
        pwm3=base+kp*(cm2-cm1);
        if(pwm1>i)
        {
          for(;i<pwm1 && j>pwm3;i+=2,j-=2)
          {
           analogWrite(PWM_W1,constrain(i,0,150));
           analogWrite(PWM_W3,constrain(j,0,150));
           delay(5);
          } 
        }
        
        else
        {
          for(;i>pwm1 && j<pwm3;i-=2,j+=2)
          {
           analogWrite(PWM_W1,constrain(i,0,150));
           analogWrite(PWM_W3,constrain(j,0,150));
           delay(5);
          } 
         }
        break;
      
       default:
        pwm1=0;
        pwm3=0;
        break;         
      }                                                      //switch case ends
    }                                                        //else for switch case ends
  }                                                          //else for orientation ends
  
  /*Serial.print(constrain(pwm1,0,150));
  Serial.print("\t");
  Serial.print(cm1);
  Serial.print("\t");
  Serial.print(constrain(pwm3,0,150));
  Serial.print("\t");
  Serial.println(cm2);
  delay(500);*/

if(cm1<=dist2&&cm1>=dist3)                                  //if bot is in stop region ,move in opposite diagonal 
{                                                           //for that we use wheel 1 and wheel 2
  while(1)
  {  
      // put your main code here, to run repeatedly:
  digitalWrite(pingPin1, LOW);                                   //excite ultrasonic1   
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  cm1 = constrain(microsecondsToCentimeters(duration1),0,200);   //calculates ultra1 distance from wall
  
  digitalWrite(pingPin2, LOW);                                  //excite ultra2 
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  cm2 = constrain(microsecondsToCentimeters(duration2),0,200);    //calculates ultra2 distance from wall
    if(abs(cm1-cm2)<=1)
       {
            dirFlag=0;
            
            if( cm1>=dist5)                         //stop
            {       
              Stop1();
            }
            else if(cm1>=dist3&&cm1<dist4)               //run at base
            {                      
             // digitalWrite(Dir_W1,HIGH);
             // digitalWrite(Dir_W2,HIGH);
             forward1();
            }
            else if(cm1>=dist4 && cm1<dist5+2)           //decelerate
            {      
              decelerate1();
            }
            
            else if(cm1==0) 
            {
              pwm1=0;
              pwm2=0;
              analogWrite(PWM_W1,0);
              analogWrite(PWM_W2,255);                           //255-pwm2 used since inverting motor driver was used for wheel 2
            }
         }                                                        //if cm1-cm2 condition ends

         else                                                     //for orientation
          {
            if( cm1>=dist5)
            Stop1();

           else
           { 
           switch(dirFlag)
            {
            case 0:
              i=pwm1;
              j=pwm2;
              prev='3';
              pwm1=base1+kp*(cm1-cm2);
              pwm2=base1+kp*(cm2-cm1);
                    if(pwm1>i)
                    {
                      for(;i<pwm1 && j>pwm2;i+=2,j-=2)
                      {
                       analogWrite(PWM_W1,constrain(i,0,150));
                       analogWrite(PWM_W2,constrain(j,0,150));
                       delay(5);
                      } 
                    }
                    else
                    {
                      for(;i>pwm1 && j<pwm2;i-=2,j+=2)
                      {
                       analogWrite(PWM_W1,constrain(i,0,150));
                       analogWrite(PWM_W2,constrain(j,0,150));
                       delay(5);
                      } 
                     }
                    break;
                  
            case 1:
              i=pwm1;
              j=pwm2;
              pwm1=base1+kp*(cm2-cm1);
              pwm2=base1+kp*(cm1-cm2);
                  if(pwm1>i)
                  {
                    for(;i<pwm1 && j>pwm2;i+=2,j-=2)
                    {
                     analogWrite(PWM_W1,constrain(i,0,150));
                     analogWrite(PWM_W2,constrain(j,0,150));
                     delay(5);
                    } 
                  }
                  else
                  {
                    for(;i>pwm1 && j<pwm2;i-=2,j+=2)
                    {
                     analogWrite(PWM_W1,constrain(i,0,150));
                     analogWrite(PWM_W2,constrain(j,0,150));
                     delay(5);
                    } 
                  }
                  break;
                
              
                default:
                pwm1=0;
                pwm2=0;
                break;         
            }
         } 
       
       }
      if(cm1>180 && cm2>180)
      {
       for(;i>pwm1 && j<pwm2;i-=2,j+=2)
       {
         analogWrite(PWM_W1,constrain(i,0,150));
         analogWrite(PWM_W2,constrain(j,0,150));
         delay(5);
       } 
       break; 
      }
       Serial.print(cm1);
   Serial.print("\t");
   Serial.print(cm2);
   Serial.print("\t");
   Serial.print(pwm1);
   Serial.print("\t");
   
   Serial.print("\t");
   Serial.print(pwm2);
   Serial.println("\t");
    
    }
  }


   Serial.print(cm1);
   Serial.print("\t");
   Serial.print(cm2);
   Serial.print("\t");
   Serial.print(pwm1);
   Serial.print("\t");
   Serial.print(pwm3);
   Serial.println("\t");

}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) 
{
 return microseconds / 29 / 2;
}
