/**
 * AlgoIoT Asset Opt-In Example for ESP32
 * 
 * This example demonstrates how to opt-in to an existing asset on the Algorand blockchain
 * using the AlgoIoT library.
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
#define DAPP_NAME "AssetOptIn"
#define NODE_ACCOUNT_MNEMONICS "your 25 mnemonic words here separated by spaces"

// Asset Configuration
#define ASSET_ID 733709260  // Replace with the asset ID you want to opt-in to

// Use testnet by default (comment out for mainnet)
#define USE_TESTNET

AlgoIoT algoiot(DAPP_NAME, NODE_ACCOUNT_MNEMONICS);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("AlgoIoT Asset Opt-In Example");
  Serial.println("============================");
  
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
  Serial.printf("Opting in to Asset ID: %llu\n", (uint64_t)ASSET_ID);
  Serial.println("This allows your account to receive this asset.");
  Serial.println();
  
  // Opt-in to the asset
  result = algoiot.createAssetOptInTransaction(ASSET_ID);
  
  if (result == ALGOIOT_NO_ERROR) {
    Serial.println("✓ Asset opt-in successful!");
    Serial.printf("Transaction ID: %s\n", algoiot.getTransactionID());
    Serial.println("Your account can now receive this asset.");
    Serial.println("Check your transaction on:");
    #ifdef USE_TESTNET
    Serial.println("https://testnet.algoexplorer.io/");
    #else
    Serial.println("https://algoexplorer.io/");
    #endif
  } else {
    Serial.printf("✗ Asset opt-in failed with error: %d\n", result);
  }
}

void loop() {
  // Nothing to do in loop
  delay(1000);
}