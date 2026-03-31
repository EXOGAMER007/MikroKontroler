

// 1. Identitas Blynk
#define BLYNK_TEMPLATE_ID "TMPL6hMV8s4H5"
#define BLYNK_TEMPLATE_NAME "monitor suhu esp32"
#define BLYNK_AUTH_TOKEN "DSORNVTgYLbO4gdzuSoJTn7rSQjyM2U5"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// 2. Konfigurasi WiFi & Sensor
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define DHT11_PIN 15 // Pin data DHT11
// #define DHTTYPE DHT11       // Jenis sensor
DHT dht11(DHT11_PIN, DHT11);

BlynkTimer timer; // Membuat timer agar tidak membanjiri server Blynk

// 3. Fungsi Kirim Data Sensor
void kirimDataSensor()
{
  float h = dht11.readHumidity();
  float t = dht11.readTemperature();

  // Cek jika sensor gagal terbaca
  if (isnan(h) || isnan(t))
  {
    Serial.println("Gagal membaca sensor DHT!");
    return;
  }

  // Kirim data ke Virtual Pin Blynk
  Blynk.virtualWrite(V0, t); // V0 untuk Suhu
  Blynk.virtualWrite(V1, h); // V1 untuk Kelembapan

  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print("°C | Kelembapan: ");
  Serial.print(h);
  Serial.println("%");
}

void testData()
{
  float h = dht11.readHumidity();
  float t = dht11.readTemperature();
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print("°C | Kelembapan: ");
  Serial.print(h);
  Serial.println("%");
}

void delayTest()
{
  delay(2000); // Delay selama 2 detik
  testData();  // Panggil fungsi testData setelah delay
}

void setup()
{
  Serial.begin(115200);
  dht11.begin();

  Blynk.begin(auth, ssid, pass);

  // Setel timer untuk kirim data setiap 2 detik (2000 milidetik)
  timer.setInterval(2000L, kirimDataSensor);
}

void loop()
{
  // Blynk.run();
  // timer.run(); // Menjalankan timer
  delayTest(); // Panggil fungsi delayTest untuk menguji delay dan pembacaan sensor
}