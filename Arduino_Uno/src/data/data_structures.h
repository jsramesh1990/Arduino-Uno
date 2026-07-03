#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <Arduino.h>

struct SensorData {
    // LiDAR Data
    float lidarDistance;
    bool lidarValid;
    String lidarStatus;
    
    // GPS Data
    float gpsLatitude;
    float gpsLongitude;
    float gpsAltitude;
    float gpsSpeed;
    int gpsSatellites;
    bool gpsValid;
    String gpsStatus;
    
    // Fingerprint Data
    int fingerprintID;
    int fingerprintConfidence;
    bool fingerprintDetected;
    bool fingerprintMatched;
    String fingerprintStatus;
    
    // RFID Data
    String rfidUID;
    String rfidType;
    bool rfidDetected;
    bool rfidValid;
    String rfidStatus;
    
    // General Sensor Data
    float temperature;
    float humidity;
    float pressure;
    float light;
    unsigned long timestamp;
    int sensorCount;
};

struct TestResults {
    // Test Results
    bool gpioTest;
    bool uartTest;
    bool i2cTest;
    bool spiTest;
    bool pwmTest;
    bool adcTest;
    bool powerTest;
    
    // Test Metrics
    float adcAccuracy;
    float pwmFrequency;
    float powerConsumption;
    float errorRate;
    
    // Test Information
    int totalTests;
    int passedTests;
    int failedTests;
    unsigned long testDuration;
    String testTimestamp;
    bool allPassed;
    bool hasErrors;
    
    // Detailed Test Data
    String testDetails[10];
    String errorMessages[10];
    int errorCount;
};

struct CommunicationData {
    // CAN Bus Data
    bool canSuccess;
    int canID;
    uint8_t canData[8];
    int canDataLength;
    String canStatus;
    
    // LoRa Data
    bool loraSuccess;
    String loraReceived;
    String loraSent;
    int loraRSSI;
    float loraSNR;
    String loraStatus;
    
    // GSM Data
    bool gsmSuccess;
    String gsmResponse;
    String gsmSignalQuality;
    String gsmStatus;
    
    // General Communication
    unsigned long timestamp;
    int packetsSent;
    int packetsReceived;
    float dataRate;
    bool allCommunicationsOK;
};

struct SystemState {
    unsigned long timestamp;
    unsigned long uptime;
    int cycleCount;
    
    SensorData sensorData;
    TestResults testResults;
    CommunicationData commData;
    
    float cpuUsage;
    float memoryUsage;
    float batteryLevel;
    float systemTemperature;
    
    String systemStatus;
    String errorMessage;
    int errorCode;
    bool isError;
    bool isInitialized;
};

struct SystemInfo {
    String systemName;
    String version;
    String buildDate;
    String hardwareID;
    String firmwareVersion;
    
    int totalMemory;
    int usedMemory;
    int availableMemory;
    
    float operatingVoltage;
    float operatingCurrent;
    float operatingPower;
    
    int uptimeDays;
    int uptimeHours;
    int uptimeMinutes;
    int uptimeSeconds;
};

#endif // DATA_STRUCTURES_H
