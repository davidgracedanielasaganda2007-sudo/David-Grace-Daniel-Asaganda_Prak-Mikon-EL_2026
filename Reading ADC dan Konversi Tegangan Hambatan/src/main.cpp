#include <Arduino.h>

// 1. Definisikan pin ADC di sisi sebelah kiri (GPIO 34)
#define POT_PIN 34

// Spesifikasi ESP32
#define ADC_RESOLUTION 4095.0  // ADC 12-bit (0 - 4095)
#define V_REF 3.3              // Tegangan referensi 3.3V
#define R_MAX 10000.0          // Hambatan maksimal potensiometer 10k Ohm (10000 Ohm)

void setup() {
  // 2. Inisialisasi Serial Monitor dengan baudrate 115200
  Serial.begin(115200);
  
  // Konfigurasi pin potensiometer sebagai INPUT
  pinMode(POT_PIN, INPUT);
  
  Serial.println("--- Mulai Pembacaan Potensiometer ESP32 ---");
}

void loop() {
  // 3. Baca nilai mentah (Raw) ADC dari pin GPIO 34
  int rawADC = analogRead(POT_PIN);

  // 4. Hitung nilai konversi Tegangan (Voltage) dan Hambatan (Resistance)
  // Rumus Tegangan = (Raw ADC / 4095) * 3.3V
  float tegangan = (rawADC / ADC_RESOLUTION) * V_REF;
  
  // Rumus Hambatan = (Raw ADC / 4095) * 10000 Ohm
  float hambatan = (rawADC / ADC_RESOLUTION) * R_MAX;

  // 5. Tampilkan data ke Serial Monitor secara rapi
  Serial.print("Raw ADC: ");
  Serial.print(rawADC);
  
  Serial.print(" | Tegangan: ");
  Serial.print(tegangan, 2); // Menampilkan 2 angka di belakang koma
  Serial.print(" V");
  
  Serial.print(" | Hambatan: ");
  Serial.print(hambatan, 0); // Menampilkan bilangan bulat
  Serial.println(" Ohm");

  // Tambahkan delay setiap siklus pembacaan (0.5 detik sekali)
  delay(5000);
}
