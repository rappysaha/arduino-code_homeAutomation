#include <LiquidCrystal.h>
#include <Wire.h>
#define lamp_pin 6
#define fan_pin 9
#define tempSensor A2  // Define the A2 pin as “temperature sensor”

int Vin; // Variable to read the value from the Arduino’s pin A0
float TC; // Variable that receives the converted voltage value to ºCtemperature
float TF; // Variable to receive the converted value from ºC to ºF

int motion = 7; // PIR sensor I/O pin7
int lamp=8; // buzzer I/O pin8 

LiquidCrystal lcd(12,11,5,4,3,2);
int visitor=0;  //variable for counting visitor number
int ir_1,ir_2;  //variables for storing ir value
unsigned long timer_1,timer_2;  //variables for recording time for ir_1 and ir_2

void setup() {
   lcd.begin(20,4);
  pinMode(motion, INPUT); 
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(lamp_pin,OUTPUT); 
  pinMode(fan_pin,OUTPUT);
  pinMode(lamp, OUTPUT);
   
}

void loop(){
  
  long sensor = digitalRead(motion);
  if(sensor == HIGH){
     digitalWrite (lamp, HIGH);
     
   }
   else
   {
      digitalWrite (lamp, LOW);
   
   }
  
   
   lcd.setCursor(0,0);
   lcd.print("-Temperature-");
   Vin = analogRead (tempSensor); /* Tells the Arduino to read A2 and stores the value in “Vin” */
   TC=500.0*(Vin/1023.0); /* Converts the voltage value into temperature and stores it into the “TC” variable (in ºC)*/
   TF = ((9.0*TC)/5.0)+32.0; // Converts ºC to ºF
   lcd.setCursor(0, 2); // Moves the cursor of the display to the next line
   lcd.print (TC);
   lcd.print((char)223);// degree symbol
   lcd.print("C "); // Writes “C” to indicate that it is in Centigrade scale.
   lcd.print(TF); // Exhibits the value of the temperature on the display
   lcd.print((char)223); //degree symbol
   lcd.print("F "); // Writes “F” to indicate that it is in Fahrenheit scale.

   delay(1000); // Waits for one second to read the sensor pin again
   
   lcd.setCursor(0,4);
   lcd.print("visitor=");
   lcd.setCursor(8, 4);

   lcd.print(visitor);

   if(digitalRead(A0)==1 && digitalRead(A1)==0)
  {
    timer_1= millis();
  }
  if(digitalRead(A0)==0 && digitalRead(A1)==1)
  {
    timer_2= millis();
  }
  if(timer_1>timer_2)
  {
   visitor=visitor+1;
   lcd.clear();
   lcd.setCursor(0,4);  
   lcd.print("visitor=");
   lcd.setCursor(8, 4);
   lcd.print(visitor);
   delay(1000);
   timer_1=0;
   timer_2=0;
  } 
 else if(timer_1<timer_2)
  {
  
   visitor=visitor-1;
    if (visitor<=0)
  { 
    visitor=0;
  }
   lcd.clear();
   lcd.setCursor(0,4);  
   lcd.print("visitor=");
   lcd.setCursor(8,4);
   lcd.print(visitor);
   delay(1000);
   timer_1=0;
   timer_2=0;

  } 
  if(visitor>=1)
  {
    digitalWrite(lamp_pin,1);
    digitalWrite(fan_pin,1);
  }
  else
  {digitalWrite(lamp_pin,0);
  digitalWrite(fan_pin,0);
  }
  
   
  
}
