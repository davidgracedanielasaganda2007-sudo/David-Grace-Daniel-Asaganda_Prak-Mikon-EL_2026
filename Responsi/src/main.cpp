#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;
const char* ssid = "DGDA";
const char* password = "davidgrace";
String apiKey = "R8B2CRWKUQ6SCM9V"; // GANTI dengan API Key kalian
const int pinLED = 13;
const int pinBuzz = 12;
const int pwmPin = 16;
const int freq = 5000;
const int pwmChannel = 0;
const int resolution = 8;

const unsigned long intervalThingspeak = 20000;
unsigned long lastSend = 0;
void kirimThingspeak(float suhu, float kelembapan) {
HTTPClient http;
String url = "http://api.thingspeak.com/update?api_key=" + apiKey +
"&field1=" + String(suhu) +
"&field2=" + String(kelembapan);
http.begin(url);
int httpCode = http.GET();
String respon = http.getString();
http.end();
if (httpCode == 200 && respon != "0") {
Serial.println(">> ThingSpeak terkirim, entry ke-" + respon);
} else {
Serial.println(">> ThingSpeak GAGAL (kode " + String(httpCode) + ")");
}
}
void setup() {
Serial.begin(115200);
pinMode(pinLED, OUTPUT);
pinMode(pinBuzz, OUTPUT);
digitalWrite(pinLED, LOW);
digitalWrite(pinBuzz, LOW);
Wire.begin(25, 26);
bme.begin(0x76);
ledcSetup(pwmChannel, freq, resolution);
ledcAttachPin(pwmPin, pwmChannel);

}
void loop() {
if (millis() - lastSend >= intervalThingspeak) {
lastSend = millis();
float suhu = bme.readTemperature();
float kelembapan = bme.readHumidity();
int pwmValue = map(suhu, 20, 30, 0, 255);
ledcWrite(pwmChannel, pwmValue);
kirimThingspeak(suhu, kelembapan);
}
delay(50);
}