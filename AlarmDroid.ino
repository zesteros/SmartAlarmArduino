#include <SoftwareSerial.h>

/*
  8->rxbt
  9->txbt
  4->pir
  5->relay
*/
const int rxbt = 8;
const int txbt = 9;

const int pirPin = 6;

const int relayPin = 4;


SoftwareSerial bt(rxbt, txbt); //tx,rx
boolean isAlarmOn = false;
long actualTime;
long alarmDuration = 30000;//300000;//5 minutes;
boolean sensorDetected = false;
boolean alwaysOn = false;
boolean isAlarmTriggered = false;


void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  checkBt();
  sensorDetected = digitalRead(pirPin) == HIGH;
  if (sensorDetected) {
    Serial.println("MOTION DETECTED");
    actualTime = millis();
    if (isAlarmOn) {
      while (((millis() < (actualTime + alarmDuration))/* || alwaysOn*/) && isAlarmOn ) {
        digitalWrite(relayPin, HIGH);
        checkBt();
      }
    }
  }
  digitalWrite(relayPin, LOW);
  delay(300); 
  

}

void checkBt() {
  if (bt.available()) {
    char c = bt.read();
    Serial.println(c);
    switch (c) {
      case '0':
        isAlarmOn = false;
        alwaysOn = false;
        alarmDuration = 0;
        break;
      case '1':
        isAlarmOn = true;
      case 'a':
        alarmDuration = 300000;//5 minutes
        break;
      case 'b':
        alarmDuration = 600000;//10 minutes
        break;
      case 'c':
        alarmDuration = 1200000;//20 minutes
        break;
      case 'd':
        alarmDuration = 1800000;//30 minutes
        break;
      case 'e':
        alwaysOn = true;
        break;
    }
  }
}
