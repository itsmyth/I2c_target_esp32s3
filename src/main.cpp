#include <Arduino.h>

// Define Hardware Serial 2 pins for ESP32-S3
#define RX_PIN 16 // Connected to NodeMCU TX (D1 / GPIO5)
#define TX_PIN 17 // Connected to NodeMCU RX (D2 / GPIO4)

void setup() {
  Serial.begin(115200);  // For PC Serial Monitor (USB)
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); // Inter-MCU Serial
  
  delay(1000);
  Serial.println("\n--- ESP32-S3 Serial Target Initialized ---");
}

void loop() {
  // Check if data is available from the Master
  if (Serial2.available() > 0) {
    String receivedString = Serial2.readStringUntil('\n');
    receivedString.trim();

    // Print to PC Serial Monitor via USB
    Serial.print("ESP32-S3 Received: ");
    Serial.println(receivedString);

    // Echo the exact string back to the Master
    Serial2.println(receivedString);
  }
}