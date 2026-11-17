#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int in1 = 17;
const int in2 = 18;
const int pwmPin = 16;
const int stby = 19
const int potPin = 34;
const int LEDpin = 2;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(stby, OUTPUT);
  digitalWrite(stby, HIGH); // Aktifkan driver
  digitalWrite(in1, HIGH); // Atur arah putaran maju
  digitalWrite(in2, LOW);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(pwmPin, 0);

  float persentasePWM = 0.0;
  float arus = ina219.getCurrent_mA();
  float tegangan_V = ina219.getBusVoltage_V();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  int potValue = analogRead(potPin); // Hasil: 0 - 4095
  int pwmValue = map(potValue, 0, 4095, 0, 255); // Konversi ke 0 - 255 

  ledcWrite(0, pwmValue); // Set kecepatan motor (0-255)
  delay(15);

  float persentasePWM = (pwmValue / 255.0) * 100.0;
  float arus = ina219.getCurrent_mA();
  float tegangan_V = ina219.getBusVoltage_V();
  delay(1000);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Arus: ");
  display.print(arus);
  display.println(" mA");
  display.print("Tegangan: ");
  display.print(tegangan_V);
  display.println(" V");
  display.print("persen PWM: ");
  display.print(pwmValue);
  display.println("%");
  display.display();

  if (pwmValue==255)
  {
    digitalWrite(LEDpin, HIGH);
  }
  else
  {
    digitalWrite(LEDpin, LOW);
  }

}