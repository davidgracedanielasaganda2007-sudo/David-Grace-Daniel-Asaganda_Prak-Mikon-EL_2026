#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUZZER_PIN 4

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int Pin_SDA = 8;
const int Pin_SCL = 9;

void setup() {
  Serial.begin(115200);
  Wire.begin(Pin_SDA, Pin_SCL);
  mpu.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Print accelerometer data to Serial Monitor
  Serial.print("MPU X = "); Serial.println(a.acceleration.x);
  Serial.print("MPU Y = "); Serial.println(a.acceleration.y);
  Serial.print("MPU Z = "); Serial.println(a.acceleration.z);

  // Display accelerometer data on the OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);  
  display.setCursor(0, 0);
  display.println("MPU6050 Accelerometer");
  display.print("X: "); display.println(a.acceleration.x);
  display.print("Y: "); display.println(a.acceleration.y);
  display.print("Z: "); display.println(a.acceleration.z);
  
  //Condition to activate buzzer if the accelerometer values exceed certain thresholds
  if (a.acceleration.x > 1.0){
      digitalWrite(BUZZER_PIN, HIGH);
      display.println("MPU MIRING");
  } else {
      digitalWrite(BUZZER_PIN, LOW);
      display.println("MPU DATAR");
  } 
  
  display.display();
  delay(500);
}