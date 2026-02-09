#include <WiFi.h>
#include <WebServer.h>

// --- WiFi config ---
const char* ssid = "PCM";
const char* password = "makerspace";

// --- LED pins ---
const int RED_PIN = 26;
const int GREEN_PIN = 27;
const int YELLOW_PIN = 14;
const int delay_ms = 100;

// --- Web server ---
WebServer server(80);

// --- Flag to trigger LED sequence ---
bool runSequence = false;

// --- Function to run the LED sequence ---
void ledSequence(int iterations = 2) {
  for (int iter = 0; iter < iterations; iter++) {
    // Yellow
    digitalWrite(YELLOW_PIN, HIGH);
    delay(delay_ms);
    digitalWrite(YELLOW_PIN, LOW);

    // Green
    digitalWrite(GREEN_PIN, HIGH);
    delay(delay_ms);
    digitalWrite(GREEN_PIN, LOW);

    // Yellow again
    digitalWrite(YELLOW_PIN, HIGH);
    delay(delay_ms);
    digitalWrite(YELLOW_PIN, LOW);

    // Red
    digitalWrite(RED_PIN, HIGH);
    delay(delay_ms);
    digitalWrite(RED_PIN, LOW);
  }
}

// --- HTTP handler for /chime ---
void handleChime() {
  server.send(200, "text/plain", "LED sequence triggered!");
  Serial.println("[ESP32] LED sequence triggered via HTTP");
  runSequence = true;  // set flag to run sequence in loop
}

// --- WiFi connection ---
void connectWiFi() {
  Serial.print("[ESP32] Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[ESP32] WiFi connected!");
  Serial.print("[ESP32] IP: ");
  Serial.println(WiFi.localIP());
}

// --- Setup ---
void setup() {
  Serial.begin(9600);

  // Initialize LED pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);

  connectWiFi();

  // HTTP route
  server.on("/chime", handleChime);
  server.begin();
  Serial.println("[ESP32] HTTP server started");
}

// --- Loop ---
void loop() {
  server.handleClient();  // Handle incoming HTTP requests

  if (runSequence) {
    ledSequence(10);      // Run the LED sequence 2 iterations
    runSequence = false; // Reset flag
  }
}
