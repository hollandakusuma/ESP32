/*
  WiFi Web Server LED Blink

  A simple web server that lets you blink an LED via the web.
  This sketch will print the IP address of your WiFi Shield (once connected)
  to the Serial monitor. From there, you can open that address in a web browser
  to turn on and off the LED on pin 5.

  If the IP address of your shield is yourAddress:
  http://yourAddress/H turns the LED on
  http://yourAddress/L turns it off

  This example is written for a network using WPA encryption. For
  WEP or WPA, change the Wifi.begin() call accordingly.

  Circuit:
   WiFi shield attached
   LED attached to pin 5

  created for arduino 25 Nov 2012
  by Tom Igoe

  ported for sparkfun esp32
  31.01.2017 by Jan Hendrik Berlin

*/

#include <WiFi.h>

const char* ssid     = "hollanda";
const char* password = "dunedin1996";

WiFiServer server(80);
byte led = 12;

void setup()
{
  Serial.begin(115200);
  pinMode(led, OUTPUT);      // set the LED pin mode

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

int value = 0;

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client request web page");
    String html = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {                    // if the byte is a newline character

          if (html.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println(" <!DOCTYPE html><html><head>");
            client.println("<title>WiFi LED</title>");
            client.println("");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: 2px solid #4CAF50;; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            // Web Page Heading
            client.println("</style></head><body>");
            client.println("<center><h1>ESP32 Web server LED</h1></center>");
            client.println(" <p> <button class=\"button\" name=\"nyala\" value=\"nyala\"><a href=\"/H\">LED NYALA</a></button></a></p> ");
            client.println(" <p> <button class=\"button\" name=\"mati\" value=\"mati\"><a href=\"/L\">LED MATI</a></button></p> ");

            client.println("</body>");
            client.println("</html> ");
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            html = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          html += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (html.endsWith("GET /H")) {
          digitalWrite(led, HIGH);               // GET /H turns the LED on
        }
        if (html.endsWith("GET /L")) {
          digitalWrite(led, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
