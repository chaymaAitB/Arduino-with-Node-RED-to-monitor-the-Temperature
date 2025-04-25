#include <DHT.h>

// Constants
#define DHTPIN 2         // Pin where the DHT is connected
#define DHTTYPE DHT11    // DHT 11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float T = dht.readTemperature();  // Read temperature in Celsius

  if (isnan(T)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send temperature with manual \n
  // Serial.println(String(T, 2));  // Or use "\r\n" for full newline
  Serial.print(String(T, 2));
  Serial.print("\n");  // Single newline character
  delay(2000);
}