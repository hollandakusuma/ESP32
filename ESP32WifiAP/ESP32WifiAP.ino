#include <WiFi.h>

const char* ssid     = "esp32";
const char* password = "12345678";

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.print("\n\nMengkonfigurasi ESP32 sebagai router dengan nama ");
  Serial.println(ssid);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
}

void loop() {
  

}
