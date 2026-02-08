#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "PCM";
const char* password = "YOUR PASSWORD HERE";

WebServer server(80);

void handlePing() {
  server.send(200, "text/plain", "pong");
  Serial.println("Ping received from bot");
}

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  server.on("/ping", handlePing);
  server.begin();
}

void loop() {
  server.handleClient();
}
