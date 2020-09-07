//GSM Shield for Arduino
//www.open-electronics.org
//this code is based on the example of Arduino Labs
 
#include "SIM900.h"
#include "sms.h"
#include "SoftwareSerial.h"
#include "sms.h"
SMSGSM sms;
//int red = 10;    // RED LED connected to PWM pin 3
int green = 9;    // GREEN LED connected to PWM pin 5
int blue = 6;    // BLUE LED connected to PWM pin 6
//int r=50; 
int g;//=100; 
int b;//=150;
//int rup; 
int gup; int bup;
 
boolean started=false;
char smsbuffer[160];
char n[20];
int fader=1;
int inc=10;
 
void setup() 
{
  //Serial connection.
  //Serial.begin(9600);
  //Serial.println("GSM Shield testing.");
  //Start configuration of shield with baudrate.
  if (gsm.begin(2400)){
    //Serial.println("\nstatus=READY");
    started=true;  
  }
 // else Serial.println("\nstatus=IDLE");
  if(started){
    delsms();
  }
 
};
 
void loop() 
{
  int pos=0;
  //Serial.println("Loop");
  if(started){
    pos=sms.IsSMSPresent(SMS_ALL);
    if(pos){
      //Serial.println("IsSMSPresent at pos ");
      //Serial.println(pos); 
      sms.GetSMS(pos,n,smsbuffer,100);
        //Serial.println(n);
      //  Serial.println(smsbuffer);
       /* if(!strcmp(smsbuffer,"R")){
          Serial.println("RED");
          r=255;
          g=0;
          b=0;
        }      
        if(!strcmp(smsbuffer,"G")){
          Serial.println("GREEN");
          r=0;
          g=255;
          b=0;
        }  */  
        if(!strcmp(smsbuffer,"LIGHTON")){
         // Serial.println("BLUE");
         // r=0;
          //`g=0;
          b=255;
        }  
       /* if(!strcmp(smsbuffer,"P")){
          Serial.println("PURPLE");
          r=255;
          g=0;
          b=255;
        }  */
        if(!strcmp(smsbuffer,"LIGHTOFF")){
         // Serial.println("YELLOW");
         // r=255;
          //g=255;
          b=0;
        }  
        if(!strcmp(smsbuffer,"FANON")){
          //Serial.println("ORANGE");
         // r=255;
          g=255;
        //  b=0;
        }  
        if(!strcmp(smsbuffer,"FANOFF")){
         // Serial.println("WHITE");
          //r=255;
          g=0;
         // b=255;
        } 
  
        if(!strcmp(smsbuffer,"F")){
          Serial.println("FADER");
          fader=1;
          g=100; b=150;
        }
        else
        {
          fader=0;
        }  
        rgb( g,b);
        //r, g,
        delsms();
 
    }
    if(fader){
      funcfader();
    }
 
  }
}
 
void delsms(){
  Serial.println("delsms");
  for (int i=0; i<10; i++){  //do it max 10 times
      int pos=sms.IsSMSPresent(SMS_ALL);
      if (pos!=0){
        Serial.print("\nFind SMS at the pos ");
        Serial.println(pos); 
        if (sms.DeleteSMS(pos)==1){    
          Serial.print("\nDeleted SMS at the pos ");
          Serial.println(pos);      
        }
        else
        {
          Serial.print("\nCant del SMS at the pos ");
          Serial.println(pos);         
        }
      }
    }
 
}
 
void funcfader(){
    /*if (rup==1){r+=1;}
    else{r-=1;}
    if (r>=255){rup=0;}
    if (r<=0){rup=1;}*/
 
    if (gup==1){g+=1;}
    else{g-=1;}
    if (g>=255){gup=0;}
    if (g<=0){gup=1;}
 
   if (bup==1){b+=1;}
    else{b-=1;}
    if (b>=255){bup=0;}
    if (b<=0){bup=1;}  
    rgb( g,b);
    //r, g,
}
 
void rgb( int g, int b)
{
 //int r, int g,
 // if (r>255) r=255;
  if (g>255) g=255;
  if (b>255) b=255;
 // if (r<0) r=0;
  if (g<0) g=0;
  if (b<0) b=0;
 
 // analogWrite(red, r); 
  analogWrite(green, g); 
  analogWrite(blue, b);   
}
