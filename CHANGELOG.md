# Changelog

All notable changes to the AlgoIoT library will be documented in this file.

## [1.0.0] - 2024-01-15

### Added
- Initial release of AlgoIoT library
- Support for ESP32 microcontrollers
- Algorand blockchain integration (Testnet and Mainnet)
- Payment transaction creation with sensor data in note field
- ARC-2 compliant data formatting
- Ed25519 cryptographic signatures
- BIP-39 mnemonic phrase support
- 8 data types support:
  - Int8, UInt8, Int16, UInt16, Int32, UInt32
  - Float (IEEE 754 single precision)
  - Short strings (max 31 characters)
- Network configuration methods
- Complete error handling with 11 error codes
- Example sketch with BME280 sensor support
- Comprehensive documentation

### Dependencies
- ArduinoJson by Benoit Blanchon
- Crypto library by Rhys Weatherley
- Base64 by Densaugeo

### Supported Platforms
- ESP32 (all variants)

### Transaction Types
- Payment transactions only (`"pay"` type)

### Network Support
- Algorand Testnet (free, default)
- Algorand Mainnet (production, costs real Algos)