# AlgoIoT Arduino Library Structure

## Directory Structure

```
AlgoIoT/                          # Main library folder
├── library.properties            # Arduino Library Manager metadata
├── README.md                     # Library documentation
├── LICENSE                       # Apache 2.0 license
├── CHANGELOG.md                  # Version history
├── keywords.txt                  # Arduino IDE syntax highlighting
├── src/                          # Source code folder
│   ├── AlgoIoT.h                # Main library header
│   ├── AlgoIoT.cpp              # Main library implementation
│   ├── minmpk.h/.cpp            # MessagePack encoding
│   ├── base32decode.h/.cpp      # Base32 decoding for Algorand addresses
│   ├── bip39enwords.h           # BIP-39 word list for mnemonics
│   ├── Ed25519.h/.cpp           # Ed25519 cryptographic signatures
│   ├── SHA512.h/.cpp            # SHA-512 hash function
│   ├── Hash.h/.cpp              # Hash base class
│   ├── BigNumberUtil.h/.cpp     # Big number arithmetic
│   ├── Crypto.h/.cpp            # Crypto utilities
│   └── utility/                 # Utility headers
│       ├── EndianUtil.h         # Endian conversion utilities
│       ├── LimbUtil.h           # Limb arithmetic utilities
│       ├── ProgMemUtil.h        # Program memory utilities
│       └── RotateUtil.h         # Bit rotation utilities
└── examples/                     # Example sketches
    └── BasicSensorData/
        └── BasicSensorData.ino   # Complete IoT example
```

## File Descriptions

### Core Library Files

**AlgoIoT.h/.cpp**
- Main library interface
- Class definition and implementation
- Public API methods for sensor data and blockchain interaction

### Cryptographic Dependencies

**Ed25519.h/.cpp**
- Ed25519 digital signature implementation
- Used for signing Algorand transactions
- Requires SHA512 and BigNumberUtil

**SHA512.h/.cpp**
- SHA-512 hash function implementation
- Required by Ed25519 for key derivation and signing

**Hash.h/.cpp**
- Base class for hash functions
- Provides common interface for cryptographic hashing

**BigNumberUtil.h/.cpp**
- Big number arithmetic operations
- Required for Ed25519 elliptic curve operations

**Crypto.h/.cpp**
- General cryptographic utilities
- Random number generation and other crypto helpers

### Algorand-Specific Files

**minmpk.h/.cpp**
- Minimal MessagePack implementation
- Encodes transaction data in MessagePack format for Algorand

**base32decode.h/.cpp**
- Base32 decoding implementation
- Converts Algorand addresses from Base32 to binary format

**bip39enwords.h**
- BIP-39 English word list
- Used for converting mnemonic phrases to private keys

### Utility Files

**utility/EndianUtil.h**
- Endian conversion utilities
- Handles byte order conversions

**utility/LimbUtil.h**
- Limb arithmetic utilities
- Low-level arithmetic operations for big numbers

**utility/ProgMemUtil.h**
- Program memory utilities
- Efficient access to constants stored in program memory

**utility/RotateUtil.h**
- Bit rotation utilities
- Cryptographic bit manipulation functions

## Dependencies

### External Libraries (Install via Arduino Library Manager)
- **ArduinoJson** - JSON data formatting
- **Base64** - Base64 encoding/decoding

### Internal Dependencies (Included)
- All cryptographic functions (Ed25519, SHA512, etc.)
- MessagePack encoding
- Base32 decoding
- BIP-39 mnemonic support

## Installation Methods

### Method 1: Arduino Library Manager (Recommended)
1. Open Arduino IDE
2. Tools > Manage Libraries
3. Search "AlgoIoT"
4. Click Install

### Method 2: Manual Installation
1. Download/clone the `AlgoIoT/` folder
2. Copy to Arduino libraries directory:
   - Windows: `Documents\Arduino\libraries\`
   - macOS: `~/Documents/Arduino/libraries/`
   - Linux: `~/Arduino/libraries/`
3. Restart Arduino IDE

### Method 3: ZIP Installation
1. Compress `AlgoIoT/` folder to `AlgoIoT.zip`
2. Arduino IDE: Sketch > Include Library > Add .ZIP Library
3. Select the ZIP file

## Usage in Sketches

```cpp
#include <AlgoIoT.h>  // Include the library

AlgoIoT algoiot("MyApp", "mnemonic words...");  // Create instance

void setup() {
  // Initialize WiFi, sensors, etc.
}

void loop() {
  // Add sensor data
  algoiot.dataAddFloatField("temp", 25.5);
  
  // Submit to blockchain
  int result = algoiot.submitTransactionToAlgorand();
}
```

## Self-Contained Library

This library is now **self-contained** with all required cryptographic and encoding functions included. Users only need to install:
- ArduinoJson (for JSON formatting)
- Base64 (for Base64 encoding)

All Algorand-specific functionality and cryptography is built-in.

## Supported Platforms

- **ESP32** - All variants (ESP32, ESP32-S2, ESP32-S3, ESP32-C3)
- **Architecture**: `esp32` only (defined in library.properties)

## Version Management

- Version defined in `library.properties`
- Follow semantic versioning (MAJOR.MINOR.PATCH)
- Update `CHANGELOG.md` for each release
- Tag releases in Git for Library Manager

## Publishing to Arduino Library Manager

1. Ensure proper structure and files
2. Test library thoroughly
3. Create Git tag with version number
4. Submit to Arduino Library Registry
5. Library Manager will pull from tagged releases