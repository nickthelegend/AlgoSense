# AlgoIoT - Algorand IoT Library for ESP32

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Platform](https://img.shields.io/badge/Platform-ESP32-green.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Algorand](https://img.shields.io/badge/Blockchain-Algorand-orange.svg)](https://www.algorand.com/)

## Overview

AlgoIoT is a lightweight Arduino library that enables ESP32 microcontrollers to notarize sensor data directly on the Algorand blockchain. It creates payment transactions with sensor data embedded in the note field, providing immutable IoT data records.

## Key Features

- **Direct Blockchain Integration**: Submit transactions from ESP32 to Algorand
- **Sensor Data Notarization**: Embed sensor readings in blockchain transactions
- **ARC-2 Compliance**: Uses Algorand Request for Comments standard for data formatting
- **Cryptographic Security**: Ed25519 signatures with BIP-39 mnemonic support
- **Network Flexibility**: Supports both Testnet (free) and Mainnet
- **Minimal Dependencies**: Optimized for microcontroller constraints

## Transaction Types

**Supported: 1 Transaction Type**
- **Payment Transaction (`pay`)**: Only transaction type supported, with sensor data in note field

## Quick Start

### 1. Hardware Requirements
- ESP32 development board
- WiFi connection
- Optional: BME280 sensor (Temperature/Humidity/Pressure)

### 2. Dependencies
Install these libraries in Arduino IDE:
```
- ArduinoJson by Benoit Blanchon
- Crypto library
- Base64 by Densaugeo
```

### 3. Basic Usage
```cpp
#include <AlgoIoT.h>

// Initialize with app name and 25-word mnemonic
AlgoIoT algoiot("MyApp", "your 25 mnemonic words here...");

// Add sensor data
algoiot.dataAddFloatField("temp", 25.5);
algoiot.dataAddUInt8Field("humidity", 60);

// Submit to blockchain
int result = algoiot.submitTransactionToAlgorand();
```

### 4. Configuration
Edit these settings in your `.ino` file:
```cpp
#define MYWIFI_SSID "YourWiFi"
#define MYWIFI_PWD "YourPassword"
#define DAPP_NAME "YourAppName"
#define NODE_ACCOUNT_MNEMONICS "your 25 word mnemonic phrase"
```

## Data Types Supported

| Method | Data Type | Range |
|--------|-----------|-------|
| `dataAddInt8Field()` | Signed 8-bit | -128 to 127 |
| `dataAddUInt8Field()` | Unsigned 8-bit | 0 to 255 |
| `dataAddInt16Field()` | Signed 16-bit | -32,768 to 32,767 |
| `dataAddUInt16Field()` | Unsigned 16-bit | 0 to 65,535 |
| `dataAddInt32Field()` | Signed 32-bit | -2,147,483,648 to 2,147,483,647 |
| `dataAddUInt32Field()` | Unsigned 32-bit | 0 to 4,294,967,295 |
| `dataAddFloatField()` | Float | IEEE 754 single precision |
| `dataAddShortStringField()` | String | Max 31 characters |

## Network Configuration

### Testnet (Default - Free)
```cpp
// No additional configuration needed
// Uses: https://testnet-api.algonode.cloud
```

### Mainnet (Costs Real Algos)
```cpp
algoiot.setAlgorandNetwork(ALGORAND_MAINNET);
```

## Example Transaction

The library creates transactions like this:
```json
{
  "sig": "<64-byte-signature>",
  "txn": {
    "amt": 100000,
    "fee": 1000,
    "fv": 32752600,
    "gen": "testnet-v1.0",
    "gh": "<network-hash>",
    "lv": 32753600,
    "note": "MyApp:j{\"temp\":25.5,\"humidity\":60}",
    "rcv": "<receiver-address>",
    "snd": "<sender-address>",
    "type": "pay"
  }
}
```

## Error Codes

| Code | Constant | Description |
|------|----------|-------------|
| 0 | `ALGOIOT_NO_ERROR` | Success |
| 1 | `ALGOIOT_NULL_POINTER_ERROR` | Null pointer passed |
| 2 | `ALGOIOT_JSON_ERROR` | JSON formatting error |
| 3 | `ALGOIOT_BAD_PARAM` | Invalid parameter |
| 4 | `ALGOIOT_MEMORY_ERROR` | Memory allocation failed |
| 5 | `ALGOIOT_INTERNAL_GENERIC_ERROR` | Internal error |
| 6 | `ALGOIOT_NETWORK_ERROR` | Network connection error |
| 7 | `ALGOIOT_MESSAGEPACK_ERROR` | MessagePack encoding error |
| 8 | `ALGOIOT_SIGNATURE_ERROR` | Cryptographic signature error |
| 9 | `ALGOIOT_TRANSACTION_ERROR` | Transaction submission error |
| 10 | `ALGOIOT_DATA_STRUCTURE_TOO_LONG` | Data exceeds limits |

## Files Structure

```
algoiot-implementation/
├── AlgoIoT.h              # Library header
├── AlgoIoT.cpp            # Library implementation
├── Algo.ino               # Example sketch
├── README.md              # This file
├── SETUP_GUIDE.md         # Detailed setup instructions
└── API_REFERENCE.md       # Complete API documentation
```

## Getting Started

1. Read [SETUP_GUIDE.md](SETUP_GUIDE.md) for detailed installation
2. Check [API_REFERENCE.md](API_REFERENCE.md) for complete method documentation
3. Run the example `Algo.ino` sketch

## License

Apache License 2.0 - See LICENSE file for details

## Support

- **Testnet Explorer**: https://testnet.algoexplorer.io/
- **Mainnet Explorer**: https://algoexplorer.io/
- **Algorand Developer Portal**: https://developer.algorand.org/

## Example Transaction

Live example: https://testnet.algoexplorer.io/tx/OWXK33Z6DGWDTYRKU7ZD5K2GMFNDVYMWR3QUHRBY3TUDM4DIQAIQ