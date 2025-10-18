# AlgoIoT - Algorand IoT Library for ESP32

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Platform](https://img.shields.io/badge/Platform-ESP32-green.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Algorand](https://img.shields.io/badge/Blockchain-Algorand-orange.svg)](https://www.algorand.com/)

## Overview

AlgoIoT is a lightweight Arduino library that enables ESP32 microcontrollers to notarize sensor data directly on the Algorand blockchain. It creates payment transactions with sensor data embedded in the note field, providing immutable IoT data records.

## Installation

### Arduino Library Manager (Recommended)
1. Open Arduino IDE
2. Go to **Tools > Manage Libraries**
3. Search for "AlgoIoT"
4. Click **Install**

### Manual Installation
1. Download the latest release from GitHub
2. Extract to your Arduino libraries folder:
   - Windows: `Documents\Arduino\libraries\`
   - macOS: `~/Documents/Arduino/libraries/`
   - Linux: `~/Arduino/libraries/`
3. Restart Arduino IDE

## Dependencies

Install these libraries via Arduino Library Manager:
- **ArduinoJson** by Benoit Blanchon
- **Crypto** by Rhys Weatherley
- **Base64** by Densaugeo

## Quick Start

```cpp
#include <AlgoIoT.h>
#include <WiFi.h>

AlgoIoT algoiot("MyApp", "your 25 mnemonic words here...");

void setup() {
  WiFi.begin("YourWiFi", "password");
  while (WiFi.status() != WL_CONNECTED) delay(1000);
}

void loop() {
  algoiot.dataAddFloatField("temp", 25.5);
  algoiot.dataAddUInt8Field("humidity", 60);
  
  int result = algoiot.submitTransactionToAlgorand();
  if (result == 0) {
    Serial.println("Transaction successful!");
  }
  
  delay(60000); // Wait 1 minute
}
```

## Features

- **Single Transaction Type**: Payment transactions with sensor data in note field
- **8 Data Types**: Support for integers, floats, and strings
- **Dual Networks**: Testnet (free) and Mainnet support
- **ARC-2 Compliance**: Standard Algorand data formatting
- **Ed25519 Security**: Cryptographic signatures with BIP-39 mnemonics

## Examples

Check the `examples/` folder for complete working examples:
- `BasicSensorData` - Complete IoT sensor data logging example

## Documentation

- **API Reference**: See header file for complete method documentation
- **Setup Guide**: Detailed installation and configuration instructions
- **Error Codes**: Complete error handling reference

## License

Apache License 2.0

## Support

- **Testnet Explorer**: https://testnet.algoexplorer.io/
- **Mainnet Explorer**: https://algoexplorer.io/
- **Algorand Developer Portal**: https://developer.algorand.org/