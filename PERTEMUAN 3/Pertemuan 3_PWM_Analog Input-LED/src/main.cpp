#include <Arduino.h>

// put function declarations here:
const int potPin = 4;
const int ledPin = 16;
const int freq = 5000;
const int pwmChannel = 0;
const int resolution = 8;

void setup() {
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(ledPin, pwmChannel);
}

void loop() {
  int potValue = analogRead(potPin); // Hasil: 0 - 4095
  int pwmValue = map(potValue, 0, 4095, 0, 255); // Konversi ke 0 - 255
  
  ledcWrite(pwmChannel, pwmValue);
  delay(15);
}