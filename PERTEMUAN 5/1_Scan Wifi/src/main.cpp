#include <WiFi.h>
const char* ssid = "DGDA";
const char* pass = "davidgrace";
void setup() {
Serial.begin(115200);
WiFi.begin(ssid, pass);
Serial.println("Connecting");
while (WiFi.status() != WL_CONNECTED) {
delay(100);
Serial.print(".");
}
Serial.println("WiFi Connected!");
Serial.println(WiFi.localIP());
}
void loop() {
}