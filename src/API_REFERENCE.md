# AlgoIoT API Reference

## Class: AlgoIoT

### Constructor

#### `AlgoIoT(const char* appName, const char* algoAccountWords)`
Creates a new AlgoIoT instance.

**Parameters:**
- `appName`: Application name (max 31 characters)
- `algoAccountWords`: 25-word BIP-39 mnemonic phrase

**Example:**
```cpp
AlgoIoT algoiot("MyIoTApp", "abandon abandon abandon ... abandon abandon about");
```

---

## Configuration Methods

### `int setDestinationAddress(const char* algorandAddress)`
Sets the transaction recipient address.

**Parameters:**
- `algorandAddress`: 58-character Algorand address

**Returns:**
- `0`: Success
- `1`: Null pointer error
- `3`: Invalid address format

**Default:** Self-address (transaction to self, no fee)

**Example:**
```cpp
int result = algoiot.setDestinationAddress("ABCD1234EFGH5678IJKL9012MNOP3456QRST7890UVWX1234YZAB5678");
```

### `int setAlgorandNetwork(const uint8_t networkType)`
Switches between Testnet and Mainnet.

**Parameters:**
- `networkType`: `ALGORAND_TESTNET` (0) or `ALGORAND_MAINNET` (1)

**Returns:**
- `0`: Success
- `3`: Invalid network type

**Default:** Testnet

**Example:**
```cpp
// Switch to Mainnet (costs real Algos!)
int result = algoiot.setAlgorandNetwork(ALGORAND_MAINNET);
```

---

## Data Field Methods

### `int dataAddInt8Field(const char* label, const int8_t value)`
Adds signed 8-bit integer field.

**Parameters:**
- `label`: Field name (max 31 characters)
- `value`: Integer value (-128 to 127)

**Returns:** Error code (0 = success)

**Example:**
```cpp
algoiot.dataAddInt8Field("temperature", -5);
```

### `int dataAddUInt8Field(const char* label, const uint8_t value)`
Adds unsigned 8-bit integer field.

**Parameters:**
- `label`: Field name (max 31 characters)  
- `value`: Integer value (0 to 255)

**Example:**
```cpp
algoiot.dataAddUInt8Field("humidity", 65);
```

### `int dataAddInt16Field(const char* label, const int16_t value)`
Adds signed 16-bit integer field.

**Parameters:**
- `label`: Field name (max 31 characters)
- `value`: Integer value (-32,768 to 32,767)

**Example:**
```cpp
algoiot.dataAddInt16Field("altitude", 1500);
```

### `int dataAddUInt16Field(const char* label, const uint16_t value)`
Adds unsigned 16-bit integer field.

**Parameters:**
- `label`: Field name (max 31 characters)
- `value`: Integer value (0 to 65,535)

**Example:**
```cpp
algoiot.dataAddUInt16Field("pressure", 1013);
```

### `int dataAddInt32Field(const char* label, const int32_t value)`
Adds signed 32-bit integer field.

**Parameters:**
- `label`: Field name (max 31 characters)
- `value`: Integer value (-2,147,483,648 to 2,147,483,647)

**Example:**
```cpp
algoiot.dataAddInt32Field("timestamp", 1640995200);
```

### `int dataAddUInt32Field(const char* label, const uint32_t value)`
Adds unsigned 32-bit integer field.

**Parameters:**
- `label`: Field name (max 31 characters)
- `value`: Integer value (0 to 4,294,967,295)

**Example:**
```cpp
algoiot.dataAddUInt32Field("serial", 1234567890);
```

### `int dataAddFloatField(const char* label, const float value)`
Adds floating-point field.

**Parameters:**
- `label`: Field name (max 31 characters)
- `value`: IEEE 754 single precision float

**Example:**
```cpp
algoiot.dataAddFloatField("voltage", 3.14159);
```

### `int dataAddShortStringField(const char* label, char* shortCString)`
Adds string field.

**Parameters:**
- `label`: Field name (max 31 characters)
- `shortCString`: String value (max 31 characters)

**Example:**
```cpp
char status[] = "OK";
algoiot.dataAddShortStringField("status", status);
```

---

## Transaction Methods

### `int submitTransactionToAlgorand()`
Submits the transaction with all added data fields to Algorand blockchain.

**Returns:**
- `0`: Success
- `2`: JSON formatting error
- `5`: Internal error
- `6`: Network error
- `7`: MessagePack error
- `8`: Signature error
- `9`: Transaction error

**Example:**
```cpp
int result = algoiot.submitTransactionToAlgorand();
if (result == 0) {
    Serial.println("Transaction successful!");
    Serial.println(algoiot.getTransactionID());
}
```

### `const char* getTransactionID()`
Returns the transaction ID of the last successful submission.

**Returns:** 64-character transaction ID string or empty string

**Example:**
```cpp
const char* txId = algoiot.getTransactionID();
Serial.print("Transaction ID: ");
Serial.println(txId);
```

---

## Error Codes Reference

| Code | Constant | Description | Common Causes |
|------|----------|-------------|---------------|
| 0 | `ALGOIOT_NO_ERROR` | Success | - |
| 1 | `ALGOIOT_NULL_POINTER_ERROR` | Null pointer | Invalid parameters |
| 2 | `ALGOIOT_JSON_ERROR` | JSON error | Data serialization failed |
| 3 | `ALGOIOT_BAD_PARAM` | Bad parameter | Invalid address/network type |
| 4 | `ALGOIOT_MEMORY_ERROR` | Memory error | Insufficient RAM |
| 5 | `ALGOIOT_INTERNAL_GENERIC_ERROR` | Internal error | Library bug |
| 6 | `ALGOIOT_NETWORK_ERROR` | Network error | WiFi/internet issues |
| 7 | `ALGOIOT_MESSAGEPACK_ERROR` | MessagePack error | Transaction encoding failed |
| 8 | `ALGOIOT_SIGNATURE_ERROR` | Signature error | Cryptographic failure |
| 9 | `ALGOIOT_TRANSACTION_ERROR` | Transaction error | Blockchain rejection |
| 10 | `ALGOIOT_DATA_STRUCTURE_TOO_LONG` | Data too long | Exceeds 1000 byte limit |

---

## Constants Reference

### Network Types
```cpp
#define ALGORAND_TESTNET 0    // Free test network
#define ALGORAND_MAINNET 1    // Production network (costs real Algos)
```

### Limits
```cpp
#define ALGORAND_MAX_NOTES_SIZE 1000        // Max bytes in note field
#define NOTE_LABEL_MAX_LEN 31               // Max chars in field labels
#define DAPP_NAME_MAX_LEN 31                // Max chars in app name
#define PAYMENT_AMOUNT_MICROALGOS 100000    // Default payment amount
```

### API Endpoints
```cpp
#define ALGORAND_TESTNET_API_ENDPOINT "https://testnet-api.algonode.cloud"
#define ALGORAND_MAINNET_API_ENDPOINT "https://mainnet-api.algonode.cloud"
```

---

## Usage Patterns

### Basic Sensor Reading
```cpp
AlgoIoT algoiot("SensorApp", "your 25 mnemonic words...");

// Add sensor data
algoiot.dataAddFloatField("temp", 25.5);
algoiot.dataAddUInt8Field("humidity", 60);
algoiot.dataAddUInt16Field("pressure", 1013);

// Submit to blockchain
int result = algoiot.submitTransactionToAlgorand();
if (result == 0) {
    Serial.println("Success!");
} else {
    Serial.print("Error: ");
    Serial.println(result);
}
```

### Error Handling
```cpp
int result = algoiot.dataAddFloatField("temp", temperature);
switch (result) {
    case ALGOIOT_NO_ERROR:
        Serial.println("Field added successfully");
        break;
    case ALGOIOT_NULL_POINTER_ERROR:
        Serial.println("Invalid label");
        break;
    case ALGOIOT_DATA_STRUCTURE_TOO_LONG:
        Serial.println("Too much data, reduce fields");
        break;
    default:
        Serial.print("Unknown error: ");
        Serial.println(result);
}
```

### Network Configuration
```cpp
AlgoIoT algoiot("MyApp", mnemonics);

// Configure for production use
algoiot.setAlgorandNetwork(ALGORAND_MAINNET);
algoiot.setDestinationAddress("RECEIVER_ADDRESS_HERE");

// Add data and submit...
```

---

## Data Format

The library creates ARC-2 compliant note fields:
```
Format: <app-name>:j<json-data>
Example: "MyApp:j{\"temp\":25.5,\"humidity\":60}"
```

This format ensures compatibility with Algorand ecosystem tools and standards.