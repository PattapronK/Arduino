#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
SoftwareSerial BTserial (0,1); // RX / IX
char c = ' ' ;

const int motro1=2;
const int motro2=4;

void setup()
{
Serial.begin(9600);
BTserial.begin(9600);
pinMode (motro1,OUTPUT);
pinMode (motro2,OUTPUT);
}

void loop() {
  {
    BTserial.println(66);
    Serial.println(66);
    delay (1000);
  }
  if (Serial.available ()>0);
  {
    char C =Serial.read ();
      if (C ='L');
      {
        digitalWrite (motro1,HIGH) ;
        digitalWrite (motro2,LOW);
      }
      if (C ='R')
      {
        digitalWrite (motro1, LOW) ;
        digitalWrite (motro2, HIGH) ;
      }
      if (C ='S');
      {
        digitalWrite (motro1, HIGH) ;
        digitalWrite (motro2, HIGH) ;
      }
      if (C ='E');
      {
        digitalWrite (motro1,LOW) ;
        digitalWrite (motro2,LOW);
      }
  }
}
