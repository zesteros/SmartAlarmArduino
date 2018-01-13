#include <SoftwareSerial.h>

/*
  8->rxbt
  9->txbt
  4->pir
  5->relay
*/
const int rxbt = 8;
const int txbt = 9;
const int pirPin = 4;
const int relayPin = 5;
SoftwareSerial bt(rxbt, txbt); //tx,rx

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {

}
