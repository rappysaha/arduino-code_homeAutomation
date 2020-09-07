#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

#define tempSensor A2

int Vin; // Variable to read the value from the Arduino’s pin A0
float TC; // Variable that receives the converted voltage value to ºCtemperature

char inchar;
char message[160];

SoftwareSerial SIM900(2,3);

#define ONE_WIRE_BUS A2 

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);


void setup() {
  Serial.begin(9600);
  SIM900.begin(19200);
  SIM900power();
  delay(3000);  
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(1000);

}

void SIM900power()
// Start equivalent software for gsm module.
{
  digitalWrite(8, HIGH);
  delay(5000);
  digitalWrite(8, LOW);
  delay(10000);
}

void sendSMS(char *message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(100);
  SIM900.println("AT + CMGS = \"+8801671663112\"");  // recipient's mobile number, in international format
  delay(100);
  SIM900.println(message);                         // message to send
  delay(100);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900.println();
  delay(5000);                                     // give module time to send SMS
  SIM900power();                                   // turn off module
}


void loop() {
  
  Vin = analogRead (tempSensor);
  TC=500.0*(Vin/1023.0);
  int temp = TC;
  //delay(1000);
  
  char command[255] = {0};
  while (SIM900.available() > 0)
  {
    char ch = SIM900.read();
    sprintf(command, "%s%c", command, ch);
  }

  Serial.print(command); //for debugging purpose only - can be commented

  if (strstr(command, "t")) /* if in the text message string is found "temp" it will return a message with inside temperature */
  {
    char message[160];
    delay(100);
    sprintf(message, "The inside temperature is: %d degrees C. ", temp);
    delay(100);
    sendSMS(message);
  }


}
