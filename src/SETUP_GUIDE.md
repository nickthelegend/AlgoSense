# AlgoIoT Setup Guide

## Prerequisites

### Hardware
- ESP32 development board (any variant)
- USB cable for programming
- WiFi network access
- Optional: BME280 sensor module

### Software
- Arduino IDE 1.8.x or 2.x
- ESP32 board package installed

## Step 1: Arduino IDE Setup

### Install ESP32 Board Package
1. Open Arduino IDE
2. Go to **File > Preferences**
3. Add this URL to "Additional Board Manager URLs":
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
4. Go to **Tools > Board > Boards Manager**
5. Search "ESP32" and install "ESP32 by Espressif Systems"

### Install Required Libraries
Go to **Tools > Manage Libraries** and install:

1. **ArduinoJson** by Benoit Blanchon
   - Version: Latest stable
   - Used for: JSON data formatting

2. **Crypto** by Rhys Weatherley
   - Version: Latest stable  
   - Used for: Ed25519 cryptographic signatures

3. **Base64** by Densaugeo
   - Version: Latest stable
   - Used for: Base64 encoding/decoding

## Step 2: Get Algorand Account

### For Testnet (Recommended for Testing)
1. Go to https://testnet.algoexplorer.io/dispenser
2. Click "Create Account"
3. **SAVE THE 25 MNEMONIC WORDS SECURELY**
4. Fund account with test Algos from dispenser

### For Mainnet (Production)
1. Use official Algorand wallet (Pera Wallet, etc.)
2. Create new account and backup mnemonic
3. Purchase real Algos from exchange
4. **WARNING: Mainnet uses real money!**

## Step 3: Hardware Connections

### Basic ESP32 Setup
```
ESP32 Board
├── USB Cable → Computer (for programming)
└── WiFi → Internet (for blockchain access)
```

### Optional BME280 Sensor
```
ESP32          BME280
├── 3.3V   →   VCC
├── GND    →   GND  
├── GPIO21 →   SDA
└── GPIO22 →   SCL
```

## Step 4: Configure the Code

### Edit Algo.ino
Replace these values with your own:

```cpp
// WiFi Settings
#define MYWIFI_SSID "YourWiFiName"
#define MYWIFI_PWD "YourWiFiPassword"

// App Configuration  
#define DAPP_NAME "YourAppName"  // Max 31 characters

// Algorand Account (25 words from Step 2)
#define NODE_ACCOUNT_MNEMONICS "word1 word2 word3 ... word25"

// Network Selection
#define USE_TESTNET  // Comment out for Mainnet

// Optional: Set destination address
#define RECEIVER_ADDRESS ""  // Leave empty for self-transactions
```

### Sensor Configuration
```cpp
// For fake sensor data (testing)
#define FAKE_TPH_SENSOR

// For real BME280 sensor
// Comment out FAKE_TPH_SENSOR and set:
#define SDA_PIN 21
#define SCL_PIN 22
```

## Step 5: Upload and Test

### Upload Code
1. Connect ESP32 via USB
2. Select correct board: **Tools > Board > ESP32 Dev Module**
3. Select correct port: **Tools > Port > COMx** (Windows) or **/dev/ttyUSBx** (Linux)
4. Click **Upload** button

### Monitor Output
1. Open **Tools > Serial Monitor**
2. Set baud rate to **115200**
3. Watch for connection and transaction messages

### Expected Output
```
Trying to connect to WiFi network YourWiFi
Connected to YourWiFi

Data OK, ready to be encoded
Data encoded, ready to be submitted to the blockchain
Ready to submit transaction to Algorand network

*** Algorand transaction successfully submitted with ID = ABC123... ***
```

## Step 6: Verify Transaction

### Check on Explorer
1. Copy transaction ID from Serial Monitor
2. Go to:
   - **Testnet**: https://testnet.algoexplorer.io/tx/[TRANSACTION_ID]
   - **Mainnet**: https://algoexplorer.io/tx/[TRANSACTION_ID]
3. Verify your sensor data appears in the "Note" field

## Troubleshooting

### WiFi Connection Issues
```cpp
// Check SSID and password
// Ensure 2.4GHz network (ESP32 doesn't support 5GHz)
// Try different WiFi network
```

### Compilation Errors
```cpp
// Verify all libraries are installed
// Check ESP32 board package version
// Ensure correct board selected
```

### Transaction Failures
```cpp
// Check mnemonic words (must be exactly 25 words)
// Verify network connection
// For Mainnet: ensure account has sufficient Algos
// Check Algorand network status
```

### Memory Issues
```cpp
// Reduce note field data
// Use shorter labels
// Check available heap memory
```

## Advanced Configuration

### Custom API Endpoints
Edit in AlgoIoT.h:
```cpp
#define ALGORAND_TESTNET_API_ENDPOINT "https://your-node.com"
#define ALGORAND_MAINNET_API_ENDPOINT "https://your-node.com"
```

### Transaction Timing
```cpp
#define DATA_SEND_INTERVAL_MINS 60  // Minutes between transactions
```

### Data Limits
```cpp
#define ALGORAND_MAX_NOTES_SIZE 1000  // Max bytes in note field
#define NOTE_LABEL_MAX_LEN 31         // Max characters in field labels
```

## Security Best Practices

1. **Never share mnemonic words**
2. **Use Testnet for development**
3. **Keep firmware updated**
4. **Use secure WiFi networks**
5. **Monitor transaction costs on Mainnet**

## Next Steps

- Read [API_REFERENCE.md](API_REFERENCE.md) for detailed method documentation
- Customize sensor data fields for your application
- Implement error handling and retry logic
- Consider power management for battery-powered devices