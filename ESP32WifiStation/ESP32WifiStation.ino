#include <WiFi.h>

const char* ssid     = "SSID";
const char* password = "password";

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.print("\n\nMenghubungkan ke ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); //fungsi untuk mengkoneksikan ke router

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi terkoneksi.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  

}
