#include <Arduino.h>

// Semua PIN dipindahkan ke SISI KIRI ESP32
#define BUTTON_PIN 13
#define LED_MERAH  12
#define LED_KUNING 14
#define LED_HIJAU  27

void setup() {
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);

  // Menggunakan internal PULLDOWN agar default bernilai LOW (0V)
  pinMode(BUTTON_PIN, INPUT_PULLDOWN); 
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_KUNING, HIGH);
    digitalWrite(LED_HIJAU, HIGH);
  } else {
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_KUNING, LOW);
    digitalWrite(LED_HIJAU, LOW);
  }
}
