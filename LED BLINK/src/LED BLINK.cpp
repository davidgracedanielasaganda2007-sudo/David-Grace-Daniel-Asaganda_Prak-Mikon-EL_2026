#include <Arduino.h>

#define LED1 16

void setup() {
  pinMode(LED1, OUTPUT);
}

void loop() {
  digitalWrite(LED1, !digitalRead(LED1));
  delay(1000);
}