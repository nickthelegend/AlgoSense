/**
 * AlgoIoT Payment Transaction Example for ESP32
 * 
 * This example demonstrates how to send a payment transaction with sensor data
 * on the Algorand blockchain using the AlgoIoT library.
 * 
 * Copyright 2024 GT50 S.r.l.
 * Licensed under the Apache License, Version 2.0
 */

#include <WiFi.h>
#include <AlgoIoT.h>

// WiFi Configuration
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"

// Algorand Configuration
#define DAPP_NAME "PaymentDemo"
#define NODE_ACCOUNT_MNEMONICS "your 25 mnemonic words here separated by spaces"

// Payment Configuration
#define PAYMENT_AMOUNT 100000  // 0.1 ALGO in microAlgos
#define SEND_INTERVAL_MS 60000  // Send every 60 seconds

// Use testnet by default (comment out for mainnet)
#define USE_TESTNET

AlgoIoT algoiot(DAPP_NAME, NODE_ACCOUNT_MNEMONICS);
unsigned long lastSendTime = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("AlgoIoT Payment Transaction Example");
  Serial.println("==================================");
  
  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Configure network (testnet by default)
  #ifdef USE_TESTNET
  int result = algoiot.setAlgorandNetwork(ALGORAND_TESTNET);
  if (result != ALGOIOT_NO_ERROR) {
    Serial.printf("Error setting testnet: %d\n", result);
    return;
  }
  Serial.println("Using Algorand Testnet");
  #else
  int result = algoiot.setAlgorandNetwork(ALGORAND_MAINNET);
  if (result != ALGOIOT_NO_ERROR) {
    Serial.printf("Error setting mainnet: %d\n", result);
    return;
  }
  Serial.println("Using Algorand Mainnet");
  #endif
  
  Serial.println();
  Serial.println("Ready to send payment transactions with sensor data!");
  Serial.printf("Payment amount: %d microAlgos (%.6f ALGO)\n", PAYMENT_AMOUNT, PAYMENT_AMOUNT / 1000000.0);
  Serial.println();
}

void loop() {
  unsigned long currentTime = millis();
  
  // Check if it's time to send a transaction
  if (currentTime - lastSendTime >= SEND_INTERVAL_MS) {
    Serial.println("Preparing payment transaction with sensor data...");
    
    // Add some sample sensor data
    int result = algoiot.dataAddFloatField("temperature", 25.5);
    if (result != ALGOIOT_NO_ERROR) {
      Serial.printf("Error adding temperature: %d\n", result);
      return;
    }
    
    result = algoiot.dataAddUInt8Field("humidity", 60);
    if (result != ALGOIOT_NO_ERROR) {
      Serial.printf("Error adding humidity: %d\n", result);
      return;
    }
    
    result = algoiot.dataAddUInt32Field("timestamp", currentTime);
    if (result != ALGOIOT_NO_ERROR) {
      Serial.printf("Error adding timestamp: %d\n", result);
      return;
    }
    
    // Send the payment transaction
    result = algoiot.createPaymentTransaction(PAYMENT_AMOUNT);
    
    if (result == ALGOIOT_NO_ERROR) {
      Serial.println("✓ Payment transaction successful!");
      Serial.printf("Transaction ID: %s\n", algoiot.getTransactionID());
      Serial.println("Sensor data has been recorded on the blockchain!");
      Serial.println("Check your transaction on:");
      #ifdef USE_TESTNET
      Serial.println("https://testnet.algoexplorer.io/");
      #else
      Serial.println("https://algoexplorer.io/");
      #endif
    } else {
      Serial.printf("✗ Payment transaction failed with error: %d\n", result);
    }
    
    lastSendTime = currentTime;
    Serial.println();
    Serial.printf("Next transaction in %d seconds...\n", SEND_INTERVAL_MS / 1000);
    Serial.println();
  }
  
  delay(1000);
}