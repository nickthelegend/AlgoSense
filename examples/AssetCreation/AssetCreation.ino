/**
 * AlgoIoT Asset Creation Example for ESP32
 * 
 * This example demonstrates how to create a new asset on the Algorand blockchain
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
#define DAPP_NAME "AssetCreator"
#define NODE_ACCOUNT_MNEMONICS "your 25 mnemonic words here separated by spaces"

// Asset Configuration
#define ASSET_NAME "MyToken"
#define UNIT_NAME "MTK"
#define ASSET_URL "https://example.com/asset"
#define DECIMALS 0
#define TOTAL_SUPPLY 1000

// Use testnet by default (comment out for mainnet)
#define USE_TESTNET

AlgoIoT algoiot(DAPP_NAME, NODE_ACCOUNT_MNEMONICS);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("AlgoIoT Asset Creation Example");
  Serial.println("==============================");
  
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
  Serial.println("Creating asset...");
  Serial.printf("Asset Name: %s\n", ASSET_NAME);
  Serial.printf("Unit Name: %s\n", UNIT_NAME);
  Serial.printf("Total Supply: %d\n", TOTAL_SUPPLY);
  Serial.printf("Decimals: %d\n", DECIMALS);
  Serial.println();
  
  // Create the asset
  result = algoiot.createAssetTransaction(ASSET_NAME, UNIT_NAME, ASSET_URL, DECIMALS, TOTAL_SUPPLY);
  
  if (result == ALGOIOT_NO_ERROR) {
    Serial.println("✓ Asset creation successful!");
    Serial.printf("Transaction ID: %s\n", algoiot.getTransactionID());
    Serial.println("Check your transaction on:");
    #ifdef USE_TESTNET
    Serial.println("https://testnet.algoexplorer.io/");
    #else
    Serial.println("https://algoexplorer.io/");
    #endif
  } else {
    Serial.printf("✗ Asset creation failed with error: %d\n", result);
  }
}

void loop() {
  // Nothing to do in loop
  delay(1000);
}