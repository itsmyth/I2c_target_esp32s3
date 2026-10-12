#include <Arduino.h>
#include <SPI.h>
#include <ESP32SPISlave.h>

ESP32SPISlave slave;

static constexpr size_t BUFFER_SIZE = 64;
uint8_t rx_buf[BUFFER_SIZE];
uint8_t tx_buf[BUFFER_SIZE];
uint8_t dummy_buf[BUFFER_SIZE];

#define MOSI_PIN 11
#define MISO_PIN 13
#define SCK_PIN  12
#define CS_PIN   10

void setup() {
  Serial.begin(115200);
  delay(1000);

  slave.begin(FSPI, SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN); 
  Serial.println("\n--- ESP32-S3 SPI Target Initialized ---");
}

void loop() {
  memset(rx_buf, 0, BUFFER_SIZE);
  memset(tx_buf, 0, BUFFER_SIZE);
  memset(dummy_buf, 0, BUFFER_SIZE);

  // 1. Wait for Transaction 1: Master writes the string to slave
  size_t recv_len = slave.transfer(dummy_buf, rx_buf, BUFFER_SIZE);
  
  if (recv_len > 0) {
    rx_buf[recv_len] = '\0';
    Serial.print("ESP32-S3 Received: ");
    Serial.println((char*)rx_buf);

    // Copy received data into tx_buf to echo back
    memcpy(tx_buf, rx_buf, recv_len);

    // 2. Wait for Transaction 2: Master reads the response back
    slave.transfer(tx_buf, dummy_buf, recv_len);
  }
}