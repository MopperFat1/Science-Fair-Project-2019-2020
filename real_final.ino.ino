#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
int ledPin1 = 8;            
int pir1 = 2;               
int pirState1 = LOW;            
int val1 = 0;
int ledPin2 = 12;            
int pir2 = 4;               
int pirState2 = LOW;            
int val2 = 0;   
int ledPin3 = 13;            
int pir3 = 7;               
int pirState3 = LOW;            
int val3 = 0;            
VR myVR(2,3);
uint8_t records[7];
uint8_t buf[64];
int led = 13;
#define onRecord    (0)
#define offRecord   (1) 
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");
  Serial.print(buf[2], DEC);
  Serial.print("\t\t");
  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}
void setup()
{
  myVR.begin(9600);
  pinMode(ledPin1, OUTPUT);     
  pinMode(pir1, INPUT);  
  pinMode(ledPin2, OUTPUT);     
  pinMode(pir2, INPUT);     
  pinMode(ledPin2, OUTPUT);     
  pinMode(pir2, INPUT);
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");  
  pinMode(led, OUTPUT);    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  if(myVR.load((uint8_t)onRecord) >= 0){
    Serial.println("onRecord loaded");
  } 
  if(myVR.load((uint8_t)offRecord) >= 0){
    Serial.println("offRecord loaded");
  }
}
void loop()
{
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case onRecord:
#include <VoiceRecognitionV3.h>                 
  val1 = digitalRead(pir1);
  val2 = digitalRead(pir2);
  val3 = digitalRead(pir3); 
  if (val1 == HIGH) {           
    digitalWrite(ledPin1, HIGH);
    if (pirState1 == LOW) {
      Serial.println("Motion detected!1");
      pirState1 = HIGH;
    }
  } else {
    digitalWrite(ledPin1, LOW); 
    if (pirState1 == HIGH){
      Serial.println("Motion ended!1");
      pirState1 = LOW;
    }
  }  
  if (val2 == HIGH) {           
    digitalWrite(ledPin2, HIGH);
    if (pirState2 == LOW) {
      Serial.println("Motion detected!2");
      pirState2 = HIGH;
    }
  } else {
    digitalWrite(ledPin2, LOW); 
    if (pirState2 == HIGH){
      Serial.println("Motion ended!2");
      pirState2 = LOW;
    }
  }
  if (val3 == HIGH) {           
    digitalWrite(ledPin3, HIGH);
    if (pirState3 == LOW) {
      Serial.println("Motion detected!3");
      pirState3 = HIGH;
    } 
  } else {
    digitalWrite(ledPin3, LOW); 
    if (pirState3 == HIGH){
      Serial.println("Motion ended!3");
      pirState3 = LOW;
    }
  }
  if (pirState1 == HIGH){
    pirState2 = LOW;
    digitalWrite(ledPin2, LOW);
    pirState3 = LOW;
    digitalWrite(ledPin3, LOW);
  }else{
    if(pirState2 == HIGH){
      pirState1 = LOW;
      digitalWrite(ledPin1, LOW);
      pirState3 = LOW;
      digitalWrite(ledPin3, LOW);
    }else{
        if(pirState3 == HIGH){
          pirState2 = LOW;
          digitalWrite(ledPin2, LOW);
          pirState1 = LOW;
          digitalWrite(ledPin1, LOW); 
        }
      }
    }
        break;
      case offRecord:
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        break;
      default:
        Serial.println("Record function undefined");
        break;
    }
    printVR(buf);
    }
  }
--------------------------------------
