# docs/api/communication_api.md

# Communication API Documentation
## Arduino Multi-Sensor Platform

---

## 📚 Table of Contents
1. [Overview](#overview)
2. [Communication Manager](#communication-manager)
3. [CAN Bus API](#can-bus-api)
4. [LoRa API](#lora-api)
5. [GSM/GPRS API](#gsmgprs-api)
6. [Serial Communication API](#serial-communication-api)
7. [Data Structures](#data-structures)
8. [Error Handling](#error-handling)
9. [Examples](#examples)

---

## Overview

The Communication API provides a unified interface for all communication modules in the Multi-Sensor Platform. It abstracts the low-level hardware communication and provides consistent methods for sending and receiving data across different protocols.

### Key Features
- Multi-protocol support (CAN, LoRa, GSM, Serial)
- Unified data transmission interface
- Automatic retry and error recovery
- Configurable communication parameters
- Real-time status monitoring
- Data encryption support

---

## Communication Manager

### Class Definition

```cpp
class CommunicationManager {
public:
    // Constructor & Destructor
    CommunicationManager();
    ~CommunicationManager();
    
    // Initialization
    bool begin();
    void initCAN(uint32_t speed = CAN_500KBPS);
    void initLoRa(float frequency = 868E6);
    void initGSM(uint32_t baud = 9600);
    void initAll();
    
    // Data Transmission
    CommunicationData sendAllData(SensorData data, TestResults results);
    bool sendCANData(const CANMessage& msg);
    bool sendLoRaData(const String& data);
    bool sendGSMData(const String& data);
    bool sendSerialData(const String& data);
    
    // Data Reception
    String receiveLoRaData();
    CANMessage receiveCANData();
    String receiveGSMData();
    String receiveSerialData();
    
    // Status Functions
    bool isCANReady();
    bool isLoRaReady();
    bool isGSMReady();
    bool isSerialReady();
    String getCommunicationStatus();
    
    // Configuration Functions
    void setCANConfig(CANConfig config);
    void setLoRaConfig(LoRaConfig config);
    void setGSMConfig(GSMConfig config);
    void setSerialConfig(SerialConfig config);
    
    // Callback Functions
    void onDataReceived(void (*callback)(uint8_t, String));
    void onTransmissionComplete(void (*callback)(uint8_t, bool));
    void onError(void (*callback)(uint8_t, String));
    
private:
    CommunicationData m_commData;
    bool m_initialized[4];
    void (*m_dataCallback)(uint8_t, String);
    void (*m_transmitCallback)(uint8_t, bool);
    void (*m_errorCallback)(uint8_t, String);
};
```

---

## CAN Bus API

### MCP2515 CAN Bus Controller

```cpp
class CANBus {
public:
    // Constructor
    CANBus();
    
    // Initialization
    bool begin(uint32_t speed = CAN_500KBPS);
    void reset();
    void setMode(CANMode mode);
    
    // Transmission
    bool sendMessage(const CANMessage& msg);
    bool sendData(uint32_t id, uint8_t* data, uint8_t length);
    bool sendRemoteFrame(uint32_t id);
    
    // Reception
    bool receiveMessage(CANMessage& msg);
    bool isMessageAvailable();
    void clearBuffer();
    
    // Configuration
    void setBitrate(uint32_t speed);
    void setAcceptanceFilter(uint32_t id, uint32_t mask);
    void enableInterrupt(bool enable);
    void setInterruptPin(uint8_t pin);
    
    // Status
    bool isReady();
    uint8_t getStatus();
    uint32_t getErrorCount();
    String getStatusString();
    
    // Statistics
    uint32_t getTxCount();
    uint32_t getRxCount();
    uint32_t getErrorCount();
    void resetStatistics();
    
private:
    MCP2515 m_can;
    CANMessage m_lastMessage;
    bool m_initialized;
    uint32_t m_txCount;
    uint32_t m_rxCount;
    uint32_t m_errorCount;
    unsigned long m_lastActivity;
};

// Usage Example
CANBus canBus;

void setup() {
    if (canBus.begin(CAN_500KBPS)) {
        Serial.println("CAN Bus initialized");
        
        // Set acceptance filter
        canBus.setAcceptanceFilter(0x100, 0x7FF);
        
        // Enable interrupt
        canBus.enableInterrupt(true);
        canBus.setInterruptPin(2);
    }
}

void loop() {
    // Send CAN message
    CANMessage msg;
    msg.id = 0x100;
    msg.length = 8;
    msg.data[0] = 0x01;
    msg.data[1] = 0x02;
    msg.data[2] = 0x03;
    msg.data[3] = 0x04;
    msg.data[4] = 0x05;
    msg.data[5] = 0x06;
    msg.data[6] = 0x07;
    msg.data[7] = 0x08;
    
    if (canBus.sendMessage(msg)) {
        Serial.println("CAN message sent");
    }
    
    // Receive CAN message
    if (canBus.isMessageAvailable()) {
        CANMessage received;
        if (canBus.receiveMessage(received)) {
            processCANMessage(received);
        }
    }
}

void processCANMessage(const CANMessage& msg) {
    Serial.print("CAN ID: 0x");
    Serial.print(msg.id, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < msg.length; i++) {
        Serial.print(msg.data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}
```

### CAN Data Structures

```cpp
// CAN Message Structure
struct CANMessage {
    uint32_t id;              // 11-bit or 29-bit identifier
    uint8_t length;           // Data length (0-8)
    uint8_t data[8];          // Data bytes
    bool extended;            // Extended ID flag
    bool remote;              // Remote frame flag
    bool rtr;                 // Remote transmission request
    uint8_t dlc;              // Data length code
    unsigned long timestamp;  // Timestamp of message
};

// CAN Configuration
struct CANConfig {
    uint32_t bitrate;         // CAN bitrate (100k, 125k, 250k, 500k, 1M)
    uint32_t acceptanceID;    // Acceptance filter ID
    uint32_t acceptanceMask;  // Acceptance filter mask
    bool loopback;            // Loopback mode enable
    bool listenOnly;          // Listen-only mode
    uint8_t mode;             // Normal, Sleep, Loopback, Listen
};

// CAN Error Codes
enum CANError {
    CAN_OK = 0,
    CAN_ERROR_INIT = 1,
    CAN_ERROR_TX = 2,
    CAN_ERROR_RX = 3,
    CAN_ERROR_BUFFER_FULL = 4,
    CAN_ERROR_TIMEOUT = 5,
    CAN_ERROR_BUS_OFF = 6,
    CAN_ERROR_PASSIVE = 7,
    CAN_ERROR_WARNING = 8
};

// CAN Message Processing
class CANProcessor {
public:
    static void processMessage(const CANMessage& msg);
    static String formatMessage(const CANMessage& msg);
    static bool validateMessage(const CANMessage& msg);
    static uint16_t calculateCRC(const CANMessage& msg);
};
```

### CAN Protocol Examples

```cpp
// OBD-II Protocol Example
class OBDIICAN {
public:
    // OBD-II PIDs
    static const uint8_t PID_ENGINE_RPM = 0x0C;
    static const uint8_t PID_VEHICLE_SPEED = 0x0D;
    static const uint8_t PID_COOLANT_TEMP = 0x05;
    static const uint8_t PID_THROTTLE_POS = 0x11;
    static const uint8_t PID_ENGINE_LOAD = 0x04;
    static const uint8_t PID_FUEL_LEVEL = 0x2F;
    static const uint8_t PID_AMBIENT_TEMP = 0x46;
    static const uint8_t PID_BATTERY_VOLTAGE = 0x42;
    
    // Request OBD-II Data
    CANMessage requestPID(uint8_t pid) {
        CANMessage msg;
        msg.id = 0x7DF;  // OBD-II Request ID
        msg.length = 8;
        msg.data[0] = 0x02;  // Length
        msg.data[1] = 0x01;  // Show current data
        msg.data[2] = pid;   // PID
        msg.data[3] = 0x00;  // Padding
        msg.data[4] = 0x00;
        msg.data[5] = 0x00;
        msg.data[6] = 0x00;
        msg.data[7] = 0x00;
        return msg;
    }
    
    // Parse OBD-II Response
    float parseResponse(const CANMessage& msg) {
        if (msg.length < 5) return 0.0;
        
        uint8_t pid = msg.data[2];
        uint16_t raw = (msg.data[3] << 8) | msg.data[4];
        
        switch(pid) {
            case PID_ENGINE_RPM:
                return raw / 4.0;  // RPM
            case PID_VEHICLE_SPEED:
                return raw;  // km/h
            case PID_COOLANT_TEMP:
                return raw - 40.0;  // °C
            default:
                return raw;
        }
    }
};
```

---

## LoRa API

### SX1278 LoRa Module

```cpp
class LoRaComm {
public:
    // Constructor
    LoRaComm();
    
    // Initialization
    bool begin(float frequency = 868E6);
    void reset();
    void setPins(uint8_t ss, uint8_t rst, uint8_t dio0);
    
    // Transmission
    bool sendPacket(const String& data);
    bool sendPacket(const uint8_t* data, size_t length);
    bool sendPacket(const String& data, uint32_t destination);
    
    // Reception
    bool receivePacket(String& data);
    bool receivePacket(uint8_t* data, size_t& length);
    int parsePacket();
    
    // Configuration
    void setFrequency(float frequency);
    void setSpreadingFactor(uint8_t sf);
    void setBandwidth(uint32_t bandwidth);
    void setCodingRate(uint8_t cr);
    void setTxPower(uint8_t power);
    void setSyncWord(uint8_t word);
    
    // Status
    bool isReady();
    float getFrequency();
    uint8_t getSpreadingFactor();
    int getRSSI();
    float getSNR();
    String getStatus();
    
    // Advanced
    void enableCRC(bool enable);
    void enableInvertIQ(bool enable);
    void setPreambleLength(uint16_t length);
    void setPacketLength(uint8_t length);
    void setOOKMode(bool enable);
    
private:
    bool m_initialized;
    float m_frequency;
    uint8_t m_spreadingFactor;
    int m_lastRSSI;
    float m_lastSNR;
    unsigned long m_lastActivity;
    
    void (*m_packetReceived)(String);
};

// Usage Example
LoRaComm lora;

void setup() {
    if (lora.begin(868E6)) {
        lora.setSpreadingFactor(12);
        lora.setTxPower(20);
        lora.setBandwidth(125000);
        lora.enableCRC(true);
        
        Serial.println("LoRa initialized");
    }
}

void loop() {
    // Send LoRa packet
    String message = "Hello from Arduino!";
    if (lora.sendPacket(message)) {
        Serial.println("LoRa packet sent");
    }
    
    // Receive LoRa packet
    String received;
    if (lora.receivePacket(received)) {
        Serial.print("LoRa received: ");
        Serial.println(received);
        
        // Process received message
        processLoRaMessage(received);
    }
    
    // Check signal quality
    int rssi = lora.getRSSI();
    float snr = lora.getSNR();
    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.print(" dBm, SNR: ");
    Serial.print(snr);
    Serial.println(" dB");
}

void processLoRaMessage(String message) {
    // Parse JSON or custom protocol
    if (message.startsWith("SENSOR")) {
        // Process sensor data
    } else if (message.startsWith("COMMAND")) {
        // Process command
        processCommand(message);
    }
}
```

### LoRa Data Structures

```cpp
// LoRa Configuration
struct LoRaConfig {
    float frequency;          // Frequency in Hz (868E6, 915E6)
    uint8_t spreadingFactor;  // 6-12 (higher = longer range)
    uint32_t bandwidth;       // 7800, 15600, 31250, 62500, 125000, 250000, 500000
    uint8_t codingRate;       // 4/5, 4/6, 4/7, 4/8 (5,6,7,8)
    uint8_t txPower;          // 0-20 dBm
    uint8_t syncWord;         // 0x12 default
    uint8_t preambleLength;   // 8-65535
    bool crcEnabled;          // CRC enable
    bool invertIQ;           // Invert IQ
};

// LoRa Packet Structure
struct LoRaPacket {
    uint8_t header[4];       // Protocol header
    uint8_t payload[256];    // Data payload
    uint16_t crc;           // CRC checksum
    uint8_t length;          // Payload length
    uint32_t sourceID;       // Source node ID
    uint32_t destinationID;  // Destination node ID
    uint8_t sequenceNumber;  // Packet sequence number
    unsigned long timestamp; // Packet timestamp
};

// LoRa Protocol
enum LoRaProtocol {
    LORA_PROTOCOL_SENSOR = 0x01,
    LORA_PROTOCOL_COMMAND = 0x02,
    LORA_PROTOCOL_ACK = 0x03,
    LORA_PROTOCOL_CONFIG = 0x04,
    LORA_PROTOCOL_ALIVE = 0x05,
    LORA_PROTOCOL_ERROR = 0x06
};

// LoRa Network Manager
class LoRaNetwork {
public:
    bool joinNetwork(uint32_t nodeID);
    bool leaveNetwork();
    bool sendToNode(uint32_t nodeID, const String& data);
    bool broadcastMessage(const String& data);
    bool isNodeActive(uint32_t nodeID);
    uint8_t getNodeCount();
    uint32_t* getActiveNodes();
    
private:
    uint32_t m_nodeID;
    uint32_t m_networkID;
    bool m_joined;
    uint32_t m_activeNodes[10];
    uint8_t m_nodeCount;
};
```

---

## GSM/GPRS API

### SIM800L GSM Module

```cpp
class GSMComm {
public:
    // Constructor
    GSMComm();
    
    // Initialization
    bool begin(uint32_t baud = 9600);
    void reset();
    bool isReady();
    
    // AT Commands
    bool sendAT(const String& command);
    bool sendAT(const String& command, String& response);
    bool sendAT(const String& command, String& response, uint32_t timeout);
    
    // Network
    bool connectNetwork(const String& apn);
    bool connectNetwork(const String& apn, const String& user, const String& pass);
    bool disconnectNetwork();
    bool isNetworkConnected();
    String getSignalQuality();
    String getOperatorName();
    
    // SMS
    bool sendSMS(const String& number, const String& message);
    bool sendSMS(const String& number, const String& message, bool unicode);
    bool readSMS(uint8_t index);
    bool deleteSMS(uint8_t index);
    uint8_t getSMSCount();
    bool setSMSFormat(uint8_t format);
    
    // GPRS
    bool connectGPRS(const String& apn);
    bool disconnectGPRS();
    bool isGPRSConnected();
    String getIPAddress();
    
    // TCP/IP
    bool createTCPSocket(const String& server, uint16_t port);
    bool sendTCPData(const String& data);
    bool receiveTCPData(String& data);
    bool closeTCPSocket();
    
    // HTTP
    bool httpGET(const String& url, String& response);
    bool httpPOST(const String& url, const String& data, String& response);
    bool httpPUT(const String& url, const String& data, String& response);
    bool httpDELETE(const String& url, String& response);
    
    // Status
    String getStatus();
    uint32_t getIMSI();
    String getIMEI();
    String getFirmwareVersion();
    
private:
    SoftwareSerial m_serial;
    bool m_initialized;
    bool m_networkConnected;
    bool m_gprsConnected;
    String m_lastResponse;
    unsigned long m_lastCommandTime;
    
    bool waitForResponse(const String& expected, uint32_t timeout);
    String readSerial();
    void flushSerial();
};

// Usage Example
GSMComm gsm;

void setup() {
    if (gsm.begin(9600)) {
        Serial.println("GSM initialized");
        
        // Connect to network
        if (gsm.connectNetwork("internet")) {
            Serial.println("Network connected");
            
            // Get network info
            String signal = gsm.getSignalQuality();
            String operator = gsm.getOperatorName();
            Serial.print("Signal: ");
            Serial.print(signal);
            Serial.print(" Operator: ");
            Serial.println(operator);
        }
    }
}

void loop() {
    // Send SMS
    if (gsm.sendSMS("+1234567890", "Hello from Arduino!")) {
        Serial.println("SMS sent");
    }
    
    // HTTP GET Request
    String response;
    if (gsm.httpGET("http://api.example.com/data", response)) {
        Serial.print("HTTP Response: ");
        Serial.println(response);
        processJSONData(response);
    }
    
    // TCP Socket Communication
    if (gsm.createTCPSocket("192.168.1.100", 8080)) {
        gsm.sendTCPData("GET /data HTTP/1.1\r\nHost: 192.168.1.100\r\n\r\n");
        
        String received;
        if (gsm.receiveTCPData(received)) {
            Serial.println(received);
        }
        gsm.closeTCPSocket();
    }
    
    delay(5000);
}
```

### GSM Data Structures

```cpp
// GSM Configuration
struct GSMConfig {
    String apn;                // Access Point Name
    String username;           // APN username
    String password;           // APN password
    uint32_t baudRate;         // Serial baud rate
    uint8_t smsFormat;         // 0=PDU, 1=Text
    bool echoEnabled;          // Command echo
    uint32_t timeout;          // Command timeout (ms)
    String pin;                // SIM PIN (if required)
};

// SMS Message Structure
struct SMSMessage {
    String sender;            // Sender number
    String message;           // Message content
    String timestamp;         // Message timestamp
    uint8_t index;            // Storage index
    bool read;                // Read flag
    bool sent;               // Sent flag
    bool unicode;            // Unicode flag
};

// Network Status
struct NetworkStatus {
    bool connected;           // Network connection status
    bool gprsActive;         // GPRS activation status
    int signalStrength;      // Signal strength (0-31)
    int ber;                 // Bit Error Rate
    String operatorName;     // Network operator name
    String networkType;      // 2G, 3G, 4G
    String ipAddress;        // IP Address (if connected)
};

// HTTP Request/Response
struct HTTPRequest {
    String method;            // GET, POST, PUT, DELETE
    String url;               // URL
    String headers;          // HTTP headers
    String body;             // Request body
    uint32_t timeout;        // Request timeout
};

struct HTTPResponse {
    int statusCode;           // HTTP status code
    String statusText;        // HTTP status text
    String headers;           // Response headers
    String body;              // Response body
    uint32_t size;           // Response size in bytes
    bool success;            // Success flag
};
```

---

## Serial Communication API

### Software Serial Manager

```cpp
class SerialComm {
public:
    // Constructor
    SerialComm();
    
    // Initialization
    bool begin(uint32_t baud = 115200);
    bool beginSoftware(uint8_t rx, uint8_t tx, uint32_t baud);
    void end();
    
    // Data Transmission
    size_t write(const uint8_t* data, size_t length);
    size_t write(const String& data);
    size_t write(const char* data);
    size_t write(uint8_t data);
    
    // Data Reception
    int available();
    int read();
    String readString();
    String readStringUntil(char terminator);
    size_t readBytes(uint8_t* buffer, size_t length);
    
    // Configuration
    void setBaudRate(uint32_t baud);
    void setTimeout(uint32_t timeout);
    void setDataBits(uint8_t bits);
    void setStopBits(uint8_t bits);
    void setParity(uint8_t parity);
    
    // Flow Control
    void enableHardwareFlow(bool enable);
    void enableSoftwareFlow(bool enable);
    
    // Status
    bool isReady();
    uint32_t getBaudRate();
    uint32_t getTxCount();
    uint32_t getRxCount();
    void resetCounters();
    
private:
    HardwareSerial* m_hardware;
    SoftwareSerial* m_software;
    bool m_usingSoftware;
    uint32_t m_baudRate;
    uint32_t m_txCount;
    uint32_t m_rxCount;
    unsigned long m_lastActivity;
};

// Usage Example
SerialComm serialComm;

void setup() {
    // Hardware Serial
    serialComm.begin(115200);
    
    // Software Serial
    serialComm.beginSoftware(10, 11, 9600);
    
    Serial.println("Serial communication initialized");
}

void loop() {
    // Send data
    serialComm.write("Hello World\n");
    
    // Receive data
    if (serialComm.available()) {
        String data = serialComm.readString();
        processSerialData(data);
    }
}
```

### Serial Data Structures

```cpp
// Serial Configuration
struct SerialConfig {
    uint32_t baudRate;         // 300-115200
    uint8_t dataBits;          // 5-8
    uint8_t stopBits;          // 1-2
    uint8_t parity;            // 0=None, 1=Even, 2=Odd
    bool hardwareFlow;         // RTS/CTS
    bool softwareFlow;         // XON/XOFF
    uint32_t timeout;          // Timeout in ms
};

// Serial Protocol
struct SerialPacket {
    uint8_t header;           // Packet header byte
    uint8_t length;           // Data length
    uint8_t data[64];         // Data payload
    uint8_t checksum;         // XOR checksum
    uint8_t footer;           // Packet footer byte
};

// Serial Protocol Handler
class SerialProtocol {
public:
    static SerialPacket createPacket(uint8_t* data, uint8_t length);
    static bool validatePacket(const SerialPacket& packet);
    static String formatPacket(const SerialPacket& packet);
    static SerialPacket parsePacket(const String& raw);
    
private:
    static const uint8_t HEADER = 0xAA;
    static const uint8_t FOOTER = 0x55;
    static uint8_t calculateChecksum(const SerialPacket& packet);
};
```

---

## Data Structures

### Communication Data Structure

```cpp
struct CommunicationData {
    // Timestamp
    unsigned long timestamp;
    uint16_t sequenceNumber;
    
    // CAN Data
    struct CANData {
        uint32_t lastID;
        uint8_t lastLength;
        uint8_t lastData[8];
        uint32_t txCount;
        uint32_t rxCount;
        uint32_t errorCount;
        bool active;
    } can;
    
    // LoRa Data
    struct LoRaData {
        String lastSent;
        String lastReceived;
        int rssi;
        float snr;
        uint32_t txCount;
        uint32_t rxCount;
        bool active;
    } lora;
    
    // GSM Data
    struct GSMData {
        String lastSMS;
        String lastCall;
        String signalQuality;
        String operatorName;
        bool networkConnected;
        bool gprsConnected;
        String ipAddress;
    } gsm;
    
    // Serial Data
    struct SerialData {
        String lastSent;
        String lastReceived;
        uint32_t txCount;
        uint32_t rxCount;
        bool active;
    } serial;
    
    // Status
    uint8_t status;
    uint16_t errorFlags;
    bool allCommunicationsOK;
};
```

---

## Error Handling

### Communication Error Codes

```cpp
// Communication Error Codes
enum CommError {
    COMM_OK = 0,
    COMM_NOT_INITIALIZED = 1,
    COMM_INIT_FAILED = 2,
    COMM_SEND_FAILED = 3,
    COMM_RECEIVE_FAILED = 4,
    COMM_TIMEOUT = 5,
    COMM_BUFFER_OVERFLOW = 6,
    COMM_INVALID_DATA = 7,
    COMM_NOT_CONNECTED = 8,
    COMM_CONNECTION_LOST = 9,
    COMM_HARDWARE_ERROR = 10,
    COMM_CONFIG_ERROR = 11,
    COMM_BUS_ERROR = 12,
    COMM_CRC_ERROR = 13,
    COMM_ACK_TIMEOUT = 14,
    COMM_BUSY = 15
};

// Error Handler
class CommErrorHandler {
public:
    static void handleError(CommError error, uint8_t module, String message);
    static String getErrorMessage(CommError error);
    static void resetError();
    static bool hasError();
    static CommError getLastError();
    static String getLastModule();
    static String getLastMessage();
    
private:
    static CommError m_lastError;
    static uint8_t m_lastModule;
    static String m_lastMessage;
    static unsigned long m_lastErrorTime;
};
```

---

## Examples

### Complete Communication Example

```cpp
#include "communication/communication.h"

CommunicationManager commManager;

void setup() {
    Serial.begin(115200);
    
    // Initialize all communication modules
    if (commManager.begin()) {
        Serial.println("All communication modules initialized");
        
        // Configure CAN
        CANConfig canConfig;
        canConfig.bitrate = CAN_500KBPS;
        canConfig.acceptanceID = 0x100;
        canConfig.acceptanceMask = 0x7FF;
        commManager.setCANConfig(canConfig);
        
        // Configure LoRa
        LoRaConfig loraConfig;
        loraConfig.frequency = 868E6;
        loraConfig.spreadingFactor = 12;
        loraConfig.txPower = 20;
        commManager.setLoRaConfig(loraConfig);
        
        // Configure GSM
        GSMConfig gsmConfig;
        gsmConfig.apn = "internet";
        gsmConfig.baudRate = 9600;
        commManager.setGSMConfig(gsmConfig);
        
        // Set callbacks
        commManager.onDataReceived(onDataReceived);
        commManager.onTransmissionComplete(onTransmissionComplete);
        commManager.onError(onCommError);
    }
}

void loop() {
    // Read sensor data
    SensorData data = sensorManager.readAllSensors();
    TestResults results = testManager.runScheduledTests();
    
    // Send data via all communication channels
    CommunicationData commData = commManager.sendAllData(data, results);
    
    // Display communication status
    displayCommStatus(commData);
    
    delay(1000);
}

void onDataReceived(uint8_t module, String data) {
    Serial.print("Data received on module ");
    Serial.print(module);
    Serial.print(": ");
    Serial.println(data);
    
    // Process received data
    if (module == MODULE_LORA) {
        processLoRaData(data);
    } else if (module == MODULE_GSM) {
        processGSMData(data);
    }
}

void onTransmissionComplete(uint8_t module, bool success) {
    Serial.print("Transmission on module ");
    Serial.print(module);
    Serial.print(success ? " succeeded" : " failed");
    Serial.println();
}

void onCommError(uint8_t module, String error) {
    Serial.print("Communication error on module ");
    Serial.print(module);
    Serial.print(": ");
    Serial.println(error);
    
    // Attempt recovery
    if (module == MODULE_CAN) {
        commManager.initCAN();
    } else if (module == MODULE_LORA) {
        commManager.initLoRa();
    } else if (module == MODULE_GSM) {
        commManager.initGSM();
    }
}

void displayCommStatus(const CommunicationData& data) {
    Serial.println("\n=== Communication Status ===");
    Serial.print("CAN: ");
    Serial.println(data.can.active ? "Active" : "Inactive");
    Serial.print("LoRa: ");
    Serial.println(data.lora.active ? "Active" : "Inactive");
    Serial.print("GSM: ");
    Serial.println(data.gsm.networkConnected ? "Connected" : "Disconnected");
    Serial.print("Packets Sent: ");
    Serial.println(data.lora.txCount + data.can.txCount);
    Serial.print("Packets Received: ");
    Serial.println(data.lora.rxCount + data.can.rxCount);
    Serial.println("=============================");
}
```

---

## 📚 Related Documentation

- [Sensor API](sensor_api.md)
- [Test API](test_api.md)
- [Hardware Documentation](../hardware/)
- [Build & Deployment Guide](../BUILD_DEPLOY.md)

---

