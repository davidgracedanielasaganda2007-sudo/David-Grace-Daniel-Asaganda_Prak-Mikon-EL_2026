#include <Arduino.h>

// Definisikan Semua Pin di Sisi Kiri ESP32
#define POT_PIN    34
#define BUTTON_PIN 13
#define LED_MERAH  12
#define LED_KUNING 14
#define LED_HIJAU  27

// Resolusi ADC 12-bit ESP32 (0 - 4095)
#define ADC_RESOLUTION 4095.0
#define V_REF 3.3

void setup() {
  // Inisialisasi Serial Monitor untuk memantau nilai
  Serial.begin(115200);

  // Konfigurasi Pin
  pinMode(POT_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN); // Menggunakan internal pulldown
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
}

void loop() {
  // 1. Membaca kondisi tombol darurat dan nilai mentah potensiometer
  int isButtonPressed = digitalRead(BUTTON_PIN);
  int rawADC = analogRead(POT_PIN);
  
  // Konversi nilai mentah menjadi Tegangan (Volt)
  float tegangan = (rawADC / ADC_RESOLUTION) * V_REF;

  // Tampilkan data ke Serial Monitor untuk mempermudah pengamatan
  Serial.print("Tombol: "); Serial.print(isButtonPressed);
  Serial.print(" | Raw ADC: "); Serial.print(rawADC);
  Serial.print(" | Tegangan: "); Serial.print(tegangan); Serial.println(" V");

  // 2. LOGIKA UTAMA: Cek Tombol Darurat Terlebih Dahulu
  if (isButtonPressed == HIGH) {
    // Jika tombol ditekan, SEMUA LED WAJIB MATI seketika
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_KUNING, LOW);
    digitalWrite(LED_HIJAU, LOW);
  } 
  else {
    // Jika tombol tidak ditekan, logika tegangan potensiometer berjalan:
    
    // Rentang Tegangan Rendah: Kurang dari 1.1V
    if (tegangan < 1.1) {
      digitalWrite(LED_MERAH, HIGH);
      digitalWrite(LED_KUNING, LOW);
      digitalWrite(LED_HIJAU, LOW);
    } 
    // Rentang Tegangan Sedang: Antara 1.1V sampai 2.2V
    else if (tegangan >= 1.1 && tegangan < 2.2) {
      digitalWrite(LED_MERAH, LOW);
      digitalWrite(LED_KUNING, HIGH);
      digitalWrite(LED_HIJAU, LOW);
    } 
    // Rentang Tegangan Tinggi: Di atas atau sama dengan 2.2V
    else {
      digitalWrite(LED_MERAH, LOW);
      digitalWrite(LED_KUNING, LOW);
      digitalWrite(LED_HIJAU, HIGH);
    }
  }

  // 3. Delay pembacaan sesuai instruksi (100 ms)
  delay(100);
}
