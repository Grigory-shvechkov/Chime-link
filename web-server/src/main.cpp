#include <WiFi.h>
#include <WebServer.h>

// --- WIFI CONFIG ---
const char* ssid = "PCM";
const char* password = "makerspace";

// --- WEB SERVER ---
WebServer server(80);

// --- FUNCTION TO HANDLE /ping ---
void handlePing() {
  server.send(200, "text/plain", "pong");
  Serial.println("[ESP32] Ping received from bot");
}

// --- FUNCTION TO HANDLE /chime ---
void handleChime() {
  server.send(200, "text/plain", "chime");
  Serial.println("[ESP32] Chime triggered!");

  // Example tone on pin 27 (replace with your speaker pin)
  // frequency 1kHz, duration 500ms
  ledcSetup(0, 1000, 8);    // channel 0, 1kHz, 8-bit resolution
  ledcAttachPin(27, 0);
  ledcWriteTone(0, 1000);
  delay(500);
  ledcWriteTone(0, 0);      // stop tone
}

// --- WIFI CONNECTION FUNCTION ---
void connectWiFi() {
  Serial.print("[ESP32] Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n[ESP32] WiFi connected!");
  Serial.print("[ESP32] IP Address: ");
  Serial.println(WiFi.localIP());
}

// --- SETUP ---
void setup() {
  Serial.begin(9600);

  connectWiFi();

  // Define server routes
  server.on("/ping", handlePing);
  server.on("/chime", handleChime);

  server.begin();
  Serial.println("[ESP32] HTTP server started");
}

// --- LOOP ---
void loop() {
  server.handleClient();
}
