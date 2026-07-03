# docs/api/sensor_api.md

# Sensor API Documentation
## Arduino Multi-Sensor Platform

---

## 📚 Table of Contents
1. [Overview](#overview)
2. [Sensor Manager Class](#sensor-manager-class)
3. [LiDAR Sensor API](#lidar-sensor-api)
4. [GPS Sensor API](#gps-sensor-api)
5. [Fingerprint Sensor API](#fingerprint-sensor-api)
6. [RFID/NFC Sensor API](#rfidnfc-sensor-api)
7. [Data Structures](#data-structures)
8. [Error Handling](#error-handling)
9. [Examples](#examples)

---

## Overview

The Sensor API provides a unified interface for controlling and reading data from all sensors in the Multi-Sensor Platform. It abstracts the low-level hardware communication and provides consistent methods for sensor initialization, reading, and calibration.

### Key Features
- Unified sensor management interface
- Automatic sensor detection and initialization
- Error handling and recovery
- Configurable sampling rates
- Power management support
- Calibration utilities

---

## Sensor Manager Class

### Class Definition

```cpp
class SensorManager {
public:
    // Constructor & Destructor
    SensorManager();
    ~SensorManager();
    
    // Initialization
    bool begin();
    void initLiDAR();
    void initGPS();
    void initFingerprint();
    void initRFID();
    void initAll();
    
    // Reading Functions
    SensorData readAllSensors();
    LiDARData readLiDAR();
    GPSData readGPS();
    FingerprintData readFingerprint();
    RFIDData readRFID();
    
    // Status Functions
    bool isLiDARReady();
    bool isGPSReady();
    bool isFingerprintReady();
    bool isRFIDReady();
    String getSensorStatus();
    
    // Configuration Functions
    void setSamplingRate(uint16_t rate);
    void setPowerMode(PowerMode mode);
    void enableAutoCalibration(bool enable);
    void setErrorCallback(void (*callback)(int, String));
    
    // Calibration Functions
    void calibrateAll();
    void calibrateLiDAR();
    void calibrateGPS();
    void calibrateFingerprint();
    void calibrateRFID();
    
private:
    SensorData m_sensorData;
    bool m_initialized[4];
    uint16_t m_samplingRate;
    PowerMode m_powerMode;
    bool m_autoCalibration;
    void (*m_errorCallback)(int, String);
};
```

---

## LiDAR Sensor API

### VL53L0X LiDAR Sensor

```cpp
class LiDAR {
public:
    // Constructor
    LiDAR();
    
    // Initialization
    bool begin(uint8_t address = 0x29);
    void reset();
    
    // Reading
    uint16_t getDistance();
    uint8_t getRangeStatus();
    bool isDataReady();
    
    // Configuration
    void setSensitivity(SensitivityMode mode);
    void setTimeout(uint16_t ms);
    void setMeasurementMode(MeasurementMode mode);
    
    // Calibration
    void calibrateOffset();
    void calibrateSignalRate();
    void calibrateCrossTalk();
    
    // Status
    String getStatus();
    uint8_t getDeviceID();
    bool isCalibrated();
    
    // Advanced
    void setInterruptThreshold(uint16_t low, uint16_t high);
    void enableInterrupt(bool enable);
    void startContinuous(uint16_t period_ms);
    void stopContinuous();
    
private:
    Adafruit_VL53L0X m_sensor;
    uint16_t m_offset;
    bool m_calibrated;
    uint16_t m_lastDistance;
    unsigned long m_lastReadTime;
    uint16_t m_samplingPeriod;
};

// Usage Example
LiDAR lidar;

void setup() {
    if (lidar.begin()) {
        lidar.setSensitivity(HIGH_ACCURACY);
        lidar.setTimeout(100);
        Serial.println("LiDAR initialized");
    }
}

void loop() {
    uint16_t distance = lidar.getDistance();
    if (distance < 2000) { // 2 meters max
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" mm");
    }
}
```

### LiDAR Data Structure

```cpp
struct LiDARData {
    uint16_t distance;        // Distance in millimeters
    uint8_t status;           // Range status (0=good, 4=bad)
    uint8_t signalRate;       // Signal rate in kcps
    uint8_t ambientRate;      // Ambient rate in kcps
    uint8_t rangeCount;       // Number of readings
    uint16_t maxRange;        // Maximum range in mm
    uint16_t minRange;        // Minimum range in mm
    float confidence;         // Confidence level (0-100%)
    unsigned long timestamp;  // Reading timestamp
    bool valid;              // Data validity flag
};
```

### LiDAR Configuration Options

```cpp
enum SensitivityMode {
    HIGH_ACCURACY,      // Best accuracy, slowest
    HIGH_SPEED,         // Fastest, lower accuracy
    LONG_RANGE,         // Long range, lower accuracy
    STANDARD           // Balanced mode
};

enum MeasurementMode {
    SINGLE_SHOT,       // One measurement
    CONTINUOUS,        // Continuous measurements
    TIMED            // Timed measurements
};
```

---

## GPS Sensor API

### NEO-6M GPS Sensor

```cpp
class GPS {
public:
    // Constructor
    GPS();
    
    // Initialization
    bool begin(uint32_t baud = 9600);
    void reset();
    void enable(bool enable);
    
    // Reading
    GPSData readData();
    bool isDataValid();
    bool isFixed();
    uint8_t getSatellites();
    
    // Configuration
    void setUpdateRate(uint16_t rate_ms);
    void setBaudRate(uint32_t baud);
    void enableNMEA(bool enable);
    void setNMEAOutput(const char* sentences);
    
    // Navigation
    double getLatitude();
    double getLongitude();
    float getAltitude();
    float getSpeed();
    float getCourse();
    float getHDOP();
    
    // Time
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();
    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    
    // Status
    String getStatus();
    bool isReady();
    float getSignalQuality();
    
private:
    TinyGPSPlus m_gps;
    SoftwareSerial m_serial;
    GPSData m_lastData;
    bool m_enabled;
    uint32_t m_baudRate;
    unsigned long m_lastUpdate;
};

// Usage Example
GPS gps;

void setup() {
    if (gps.begin(9600)) {
        gps.setUpdateRate(1000); // 1Hz update
        Serial.println("GPS initialized");
    }
}

void loop() {
    if (gps.isDataValid()) {
        double lat = gps.getLatitude();
        double lng = gps.getLongitude();
        float alt = gps.getAltitude();
        
        Serial.print("Location: ");
        Serial.print(lat, 6);
        Serial.print(", ");
        Serial.print(lng, 6);
        Serial.print(" Alt: ");
        Serial.print(alt);
        Serial.println(" m");
    }
}
```

### GPS Data Structure

```cpp
struct GPSData {
    // Location
    double latitude;          // Degrees (-90 to 90)
    double longitude;         // Degrees (-180 to 180)
    float altitude;           // Meters above sea level
    
    // Movement
    float speed;              // Kilometers per hour
    float course;             // Degrees true (0-359)
    float heading;            // Degrees magnetic
    
    // Accuracy
    float hdop;              // Horizontal dilution of precision
    float pdop;              // Position dilution of precision
    float vdop;              // Vertical dilution of precision
    
    // Satellite Info
    uint8_t satellites;      // Number of satellites tracked
    uint8_t usedSatellites;  // Number of satellites in fix
    
    // Time
    uint8_t hour;            // 0-23
    uint8_t minute;          // 0-59
    uint8_t second;          // 0-59
    uint16_t year;           // YYYY
    uint8_t month;           // 1-12
    uint8_t day;             // 1-31
    
    // Status
    bool valid;              // Data valid flag
    bool fixed;              // Position fix flag
    uint8_t fixQuality;      // 0=invalid, 1=GPS, 2=DGPS
    uint8_t fixMode;         // 1=no fix, 2=2D, 3=3D
    unsigned long timestamp; // Reading timestamp
};
```

### NMEA Sentence Configuration

```cpp
// NMEA Sentence Types
const char* NMEA_GGA = "GGA";   // Global Positioning System Fix Data
const char* NMEA_GLL = "GLL";   // Geographic Position - Latitude/Longitude
const char* NMEA_GSA = "GSA";   // GNSS DOP and Active Satellites
const char* NMEA_GSV = "GSV";   // GNSS Satellites in View
const char* NMEA_RMC = "RMC";   // Recommended Minimum Specific GNSS Data
const char* NMEA_VTG = "VTG";   // Course Over Ground and Ground Speed

// Configuration
void configureNMEA() {
    // Enable specific sentences
    gps.enableNMEA(true);
    gps.setNMEAOutput("GGA,GSA,RMC");
    
    // Disable unwanted sentences for bandwidth
    gps.setNMEAOutput("GLL"); // Only send GLL
}
```

---

## Fingerprint Sensor API

### R307 Fingerprint Sensor

```cpp
class FingerprintSensor {
public:
    // Constructor
    FingerprintSensor();
    
    // Initialization
    bool begin(uint32_t baud = 57600);
    void reset();
    
    // Fingerprint Operations
    uint8_t enrollFinger(uint8_t id);
    uint8_t deleteFinger(uint8_t id);
    uint8_t deleteAllFingers();
    uint8_t searchFinger();
    uint8_t verifyFinger(uint8_t id);
    
    // Image Operations
    uint8_t getImage();
    uint8_t convertToTemplate();
    uint8_t convertToTemplate2();
    uint8_t createModel();
    uint8_t storeTemplate(uint8_t id);
    uint8_t loadTemplate(uint8_t id);
    
    // Database Operations
    uint8_t getDatabaseSize();
    uint8_t getFingerCount();
    uint8_t getCapacity();
    uint8_t getSecurityLevel();
    void setSecurityLevel(uint8_t level);
    
    // Status
    bool isReady();
    bool isFingerDetected();
    String getStatusMessage(uint8_t code);
    uint8_t getLastError();
    
    // Callbacks
    void onFingerDetected(void (*callback)());
    void onFingerMatched(void (*callback)(uint8_t));
    
private:
    Adafruit_Fingerprint m_sensor;
    uint8_t m_lastError;
    bool m_fingerDetected;
    uint16_t m_fingerID;
    uint16_t m_confidence;
    unsigned long m_lastDetectionTime;
};

// Usage Example
FingerprintSensor fingerprint;

void setup() {
    if (fingerprint.begin(57600)) {
        Serial.println("Fingerprint sensor initialized");
        fingerprint.onFingerDetected(onFingerDetected);
        fingerprint.onFingerMatched(onFingerMatched);
    }
}

void loop() {
    // Search for a finger
    if (fingerprint.searchFinger() == FINGERPRINT_OK) {
        // Finger found!
    }
}

void onFingerDetected() {
    Serial.println("Finger detected!");
}

void onFingerMatched(uint8_t id) {
    Serial.print("Finger matched! ID: ");
    Serial.println(id);
}
```

### Fingerprint Data Structure

```cpp
struct FingerprintData {
    uint8_t status;           // Operation status (0=OK)
    uint16_t fingerID;        // Fingerprint ID (0-127)
    uint16_t confidence;      // Match confidence (0-65535)
    uint8_t templateCount;    // Number of stored templates
    uint8_t maxTemplates;     // Maximum templates (127)
    uint8_t securityLevel;    // Security level (1-5)
    uint32_t lastMatchTime;   // Timestamp of last match
    uint32_t lastEnrollTime;  // Timestamp of last enrollment
    bool fingerDetected;      // Finger presence flag
    bool matched;             // Match flag
    String statusMessage;     // Human-readable status
    unsigned long timestamp;  // Reading timestamp
};
```

### Fingerprint Error Codes

```cpp
// Return Codes
#define FINGERPRINT_OK             0x00
#define FINGERPRINT_NOFINGER       0x01
#define FINGERPRINT_IMAGEFAIL      0x02
#define FINGERPRINT_IMAGEMESS      0x03
#define FINGERPRINT_FEATUREFAIL    0x04
#define FINGERPRINT_NOMATCH        0x05
#define FINGERPRINT_NOTFOUND       0x06
#define FINGERPRINT_ENROLLMISMATCH 0x07
#define FINGERPRINT_BADLOCATION    0x08
#define FINGERPRINT_DBERROR        0x09
#define FINGERPRINT_UPLOADFAIL     0x0A
#define FINGERPRINT_DOWNLOADFAIL   0x0B
#define FINGERPRINT_IMAGECANCEL    0x0C
#define FINGERPRINT_DISFULL        0x0D
#define FINGERPRINT_INVALIDFILE    0x0E
#define FINGERPRINT_FLASHERR       0x0F

// Error Message Mapping
String getFingerprintMessage(uint8_t code) {
    switch(code) {
        case FINGERPRINT_OK: return "Success";
        case FINGERPRINT_NOFINGER: return "No finger detected";
        case FINGERPRINT_IMAGEFAIL: return "Failed to capture image";
        case FINGERPRINT_IMAGEMESS: return "Image too messy";
        case FINGERPRINT_FEATUREFAIL: return "Feature extraction failed";
        case FINGERPRINT_NOMATCH: return "No match found";
        case FINGERPRINT_NOTFOUND: return "Fingerprint not found";
        case FINGERPRINT_ENROLLMISMATCH: return "Enrollment mismatch";
        case FINGERPRINT_BADLOCATION: return "Invalid location";
        case FINGERPRINT_DBERROR: return "Database error";
        default: return "Unknown error";
    }
}
```

---

## RFID/NFC Sensor API

### MFRC522 RFID Reader

```cpp
class RFIDReader {
public:
    // Constructor
    RFIDReader();
    
    // Initialization
    bool begin();
    void reset();
    void setAntenna(bool enable);
    
    // Reading
    bool readCard();
    bool readCardSerial();
    bool readCardData(byte *data, byte *length);
    
    // UID Operations
    String getUID();
    uint8_t getUIDLength();
    byte* getUIDBytes();
    
    // Card Operations
    bool isCardPresent();
    bool isNewCardPresent();
    bool authenticate(byte sector, byte block, byte* key);
    bool readBlock(byte block, byte* data);
    bool writeBlock(byte block, byte* data);
    bool readSector(byte sector, byte* data, byte length);
    bool writeSector(byte sector, byte* data, byte length);
    
    // Card Types
    String getCardType();
    uint8_t getCardTypeValue();
    
    // Configuration
    void setAntennaGain(uint8_t gain);
    void setMaxRetries(uint8_t retries);
    void setSpeed(uint32_t speed);
    
    // Status
    bool isReady();
    String getStatus();
    uint8_t getLastError();
    
    // Callbacks
    void onCardDetected(void (*callback)(String uid));
    void onCardRead(void (*callback)(String uid, String data));
    
private:
    MFRC522 mfrc522;
    MFRC522::MIFARE_Key m_key;
    String m_lastUID;
    bool m_cardPresent;
    uint8_t m_lastError;
    unsigned long m_lastReadTime;
};

// Usage Example
RFIDReader rfid;

void setup() {
    if (rfid.begin()) {
        Serial.println("RFID reader initialized");
        rfid.onCardDetected(onCardDetected);
        rfid.setAntennaGain(4); // Max gain
    }
}

void loop() {
    if (rfid.isNewCardPresent()) {
        if (rfid.readCard()) {
            String uid = rfid.getUID();
            String cardType = rfid.getCardType();
            
            Serial.print("Card UID: ");
            Serial.println(uid);
            Serial.print("Card Type: ");
            Serial.println(cardType);
            
            // Read sector 1
            byte key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
            rfid.authenticate(1, 4, key);
            
            byte data[16];
            rfid.readBlock(4, data);
            
            // Process data
            processCardData(data, 16);
        }
    }
}

void onCardDetected(String uid) {
    Serial.print("Card detected: ");
    Serial.println(uid);
}
```

### RFID Data Structure

```cpp
struct RFIDData {
    String uid;               // Card UID as hex string
    byte uidBytes[10];        // UID as bytes
    uint8_t uidLength;        // UID length (4 or 7 bytes)
    uint8_t cardType;         // Card type code
    String cardTypeName;      // Human-readable card type
    byte sectorData[64][16];  // Sector data (16 sectors)
    byte blockData[64][16];   // Block data (64 blocks)
    bool cardPresent;         // Card presence flag
    bool dataValid;           // Data validity flag
    uint32_t lastDetected;    // Last detection timestamp
    uint32_t lastRead;        // Last read timestamp
    uint8_t rssi;             // Signal strength
    unsigned long timestamp;  // Reading timestamp
};
```

### RFID Card Types

```cpp
// MIFARE Card Types
#define RFID_MIFARE_1K     0x01
#define RFID_MIFARE_2K     0x02
#define RFID_MIFARE_4K     0x03
#define RFID_MIFARE_MINI   0x04
#define RFID_MIFARE_ULTRALIGHT 0x05
#define RFID_MIFARE_DESFIRE 0x06
#define RFID_NFC_FORUM_TYPE2 0x07
#define RFID_NFC_FORUM_TYPE3 0x08
#define RFID_NFC_FORUM_TYPE4 0x09

// Get Card Type Name
String getCardTypeName(uint8_t type) {
    switch(type) {
        case RFID_MIFARE_1K: return "MIFARE Classic 1K";
        case RFID_MIFARE_2K: return "MIFARE Classic 2K";
        case RFID_MIFARE_4K: return "MIFARE Classic 4K";
        case RFID_MIFARE_MINI: return "MIFARE Mini";
        case RFID_MIFARE_ULTRALIGHT: return "MIFARE Ultralight";
        case RFID_MIFARE_DESFIRE: return "MIFARE DESFire";
        case RFID_NFC_FORUM_TYPE2: return "NFC Forum Type 2";
        case RFID_NFC_FORUM_TYPE3: return "NFC Forum Type 3";
        case RFID_NFC_FORUM_TYPE4: return "NFC Forum Type 4";
        default: return "Unknown";
    }
}
```

---

## Data Structures

### Master Sensor Data Structure

```cpp
struct SensorData {
    // Timestamp
    unsigned long timestamp;
    uint16_t sequenceNumber;
    
    // LiDAR Data
    struct LiDARData {
        uint16_t distance;
        uint8_t status;
        uint8_t signalRate;
        uint8_t ambientRate;
        bool valid;
    } lidar;
    
    // GPS Data
    struct GPSData {
        double latitude;
        double longitude;
        float altitude;
        float speed;
        float course;
        uint8_t satellites;
        bool valid;
        bool fixed;
    } gps;
    
    // Fingerprint Data
    struct FingerprintData {
        uint16_t id;
        uint16_t confidence;
        bool detected;
        bool matched;
        uint8_t templateCount;
    } fingerprint;
    
    // RFID Data
    struct RFIDData {
        String uid;
        uint8_t type;
        bool present;
        bool valid;
    } rfid;
    
    // System Data
    struct SystemData {
        float temperature;
        float humidity;
        float pressure;
        float batteryLevel;
        uint16_t freeMemory;
        uint8_t cpuLoad;
    } system;
    
    // Status
    uint8_t status;
    uint16_t errorFlags;
    bool allValid;
};
```

---

## Error Handling

### Error Codes and Handling

```cpp
// Sensor Error Codes
enum SensorError {
    SENSOR_OK = 0,
    SENSOR_NOT_FOUND = 1,
    SENSOR_INIT_FAILED = 2,
    SENSOR_READ_FAILED = 3,
    SENSOR_TIMEOUT = 4,
    SENSOR_BUSY = 5,
    SENSOR_CALIBRATION_FAILED = 6,
    SENSOR_COMMUNICATION_ERROR = 7,
    SENSOR_POWER_ERROR = 8,
    SENSOR_INVALID_DATA = 9,
    SENSOR_OUT_OF_RANGE = 10,
    SENSOR_OVERFLOW = 11,
    SENSOR_UNDERFLOW = 12,
    SENSOR_HARDWARE_ERROR = 13,
    SENSOR_CONFIG_ERROR = 14
};

// Error Handler
class SensorErrorHandler {
public:
    static void handleError(SensorError error, String module, String message);
    static String getErrorMessage(SensorError error);
    static void resetError();
    static bool hasError();
    
private:
    static SensorError m_lastError;
    static String m_lastModule;
    static String m_lastMessage;
    static unsigned long m_lastErrorTime;
};

// Error Handling Example
void setup() {
    // Set error callback
    SensorErrorHandler::onError([](SensorError error, String module, String msg) {
        Serial.print("ERROR [");
        Serial.print(module);
        Serial.print("]: ");
        Serial.println(msg);
        
        if (error == SENSOR_READ_FAILED) {
            // Attempt recovery
            if (module == "LiDAR") {
                lidar.reset();
                lidar.begin();
            }
        }
    });
}
```

---

## Examples

### Complete Sensor Initialization

```cpp
#include "sensors/sensors.h"

SensorManager sensorManager;

void setup() {
    Serial.begin(115200);
    
    // Initialize all sensors
    if (sensorManager.begin()) {
        Serial.println("All sensors initialized");
        
        // Configure sensors
        sensorManager.setSamplingRate(100); // 100ms
        sensorManager.setPowerMode(POWER_MODE_NORMAL);
        sensorManager.enableAutoCalibration(true);
        
        // Set callbacks
        sensorManager.onError([](int code, String msg) {
            Serial.print("Sensor Error: ");
            Serial.println(msg);
        });
    }
}

void loop() {
    // Read all sensors
    SensorData data = sensorManager.readAllSensors();
    
    if (data.allValid) {
        // Process sensor data
        processSensorData(data);
    }
    
    delay(100);
}
```

### Custom Sensor Reading

```cpp
void processSensorData(SensorData data) {
    // Process LiDAR data
    if (data.lidar.valid) {
        processLiDAR(data.lidar.distance);
    }
    
    // Process GPS data
    if (data.gps.valid && data.gps.fixed) {
        processGPS(data.gps.latitude, data.gps.longitude, data.gps.altitude);
    }
    
    // Process Fingerprint data
    if (data.fingerprint.detected) {
        if (data.fingerprint.matched) {
            authenticateUser(data.fingerprint.id);
        }
    }
    
    // Process RFID data
    if (data.rfid.present && data.rfid.valid) {
        processRFID(data.rfid.uid);
    }
}
```

---

## 📚 Related Documentation

- [Communication API](communication_api.md)
- [Test API](test_api.md)
- [Hardware Documentation](../hardware/)
- [Build & Deployment Guide](../BUILD_DEPLOY.md)

---

