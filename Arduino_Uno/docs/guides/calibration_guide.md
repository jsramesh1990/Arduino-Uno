# docs/guides/calibration_guide.md

# Calibration Guide
## Arduino Multi-Sensor Platform

---

## 📚 Table of Contents
1. [Overview](#overview)
2. [Calibration Requirements](#calibration-requirements)
3. [LiDAR Calibration](#lidar-calibration)
4. [GPS Calibration](#gps-calibration)
5. [Fingerprint Sensor Calibration](#fingerprint-sensor-calibration)
6. [RFID/NFC Calibration](#rfidnfc-calibration)
7. [ADC Calibration](#adc-calibration)
8. [Power Monitoring Calibration](#power-monitoring-calibration)
9. [Temperature Sensor Calibration](#temperature-sensor-calibration)
10. [Calibration Procedures](#calibration-procedures)
11. [Calibration Verification](#calibration-verification)
12. [Troubleshooting Calibration Issues](#troubleshooting-calibration-issues)

---

## Overview

This guide provides comprehensive calibration procedures for all sensors and modules in the Arduino Multi-Sensor Platform. Proper calibration ensures accurate measurements and reliable system operation.

### Why Calibration is Important
- **Accuracy**: Ensures precise measurements
- **Reliability**: Consistent performance over time
- **Repeatability**: Reproducible results
- **Tolerance**: Compensates for component variations
- **Optimization**: Maximizes sensor performance

### Calibration Schedule

| Component | Initial Calibration | Regular Calibration | Condition |
|-----------|-------------------|-------------------|-----------|
| LiDAR | Required | Monthly | - |
| GPS | Required | Quarterly | - |
| Fingerprint | Required | Never | - |
| RFID/NFC | Required | Never | - |
| ADC | Required | Monthly | - |
| Power Monitor | Required | Monthly | - |
| Temperature Sensor | Required | Quarterly | - |

---

## Calibration Requirements

### Equipment Required

```
┌─────────────────────────────────────────────────────────────────────┐
│                    CALIBRATION EQUIPMENT                           │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   1. Multimeter (Digital)                                          │
│      ● Accuracy: ±0.5% or better                                  │
│      ● True RMS capable                                           │
│      ● For voltage and current measurement                        │
│                                                                     │
│   2. Reference Voltage Source                                     │
│      ● 0-5V precision output                                      │
│      ● Accuracy: ±0.01%                                          │
│      ● For ADC calibration                                        │
│                                                                     │
│   3. Distance Reference                                            │
│      ● Calibrated ruler or measuring tape                         │
│      ● 0-2000mm range                                             │
│      ● For LiDAR calibration                                      │
│                                                                     │
│   4. Known Good GPS Reference                                     │
│      ● External GPS receiver                                      │
│      ● Known location coordinates                                 │
│      ● For GPS verification                                       │
│                                                                     │
│   5. Known Good RFID/NFC Tags                                     │
│      ● MIFARE Classic 1K                                          │
│      ● MIFARE Ultralight                                          │
│      ● For RFID verification                                      │
│                                                                     │
│   6. Fingerprint Test Subjects                                    │
│      ● 3-5 known fingerprints                                     │
│      ● For fingerprint testing                                    │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## LiDAR Calibration

### VL53L0X Calibration

```cpp
/*
 * LiDAR Calibration Procedure
 * VL53L0X Time-of-Flight Sensor
 */

class LiDARCalibration {
public:
    // Calibration Structure
    struct CalibrationData {
        uint16_t offset;           // Distance offset in mm
        uint16_t signalRateOffset; // Signal rate offset
        uint16_t crossTalkOffset;  // Cross-talk offset
        float temperatureOffset;   // Temperature compensation
        bool calibrated;          // Calibration status
    };
    
    // Calibration Functions
    bool calibrateOffset(uint16_t referenceDistance);
    bool calibrateSignalRate();
    bool calibrateCrossTalk();
    void setTemperatureOffset(float temperature);
    void resetCalibration();
    
    // Verification Functions
    bool verifyCalibration(uint16_t referenceDistance, float tolerance = 5.0);
    String getCalibrationReport();
    
    // Data Management
    bool saveCalibration();
    bool loadCalibration();
    bool exportCalibration(const String& filename);
    bool importCalibration(const String& filename);
    
private:
    CalibrationData m_calData;
    Adafruit_VL53L0X m_sensor;
    
    uint16_t readDistance();
    float calculateError(uint16_t measured, uint16_t expected);
    void applyCalibration();
};

// LiDAR Calibration Implementation
bool LiDARCalibration::calibrateOffset(uint16_t referenceDistance) {
    Serial.println("=== LiDAR Offset Calibration ===");
    Serial.print("Place target at exactly ");
    Serial.print(referenceDistance);
    Serial.println(" mm");
    delay(2000);
    
    // Take multiple readings
    const int samples = 10;
    uint32_t sum = 0;
    for (int i = 0; i < samples; i++) {
        sum += readDistance();
        delay(100);
    }
    uint16_t average = sum / samples;
    
    // Calculate offset
    int16_t offset = referenceDistance - average;
    m_calData.offset = offset;
    m_calData.calibrated = true;
    
    Serial.print("Average measured: ");
    Serial.print(average);
    Serial.println(" mm");
    Serial.print("Offset: ");
    Serial.print(offset);
    Serial.println(" mm");
    
    applyCalibration();
    return true;
}

bool LiDARCalibration::verifyCalibration(uint16_t referenceDistance, float tolerance) {
    // Test at multiple distances
    const uint16_t testDistances[] = {100, 500, 1000, 1500, 2000};
    bool allPassed = true;
    
    Serial.println("=== LiDAR Calibration Verification ===");
    
    for (int i = 0; i < 5; i++) {
        uint16_t measured = readDistance();
        float error = calculateError(measured, testDistances[i]);
        float percentageError = (error / testDistances[i]) * 100.0;
        
        Serial.print("Distance: ");
        Serial.print(testDistances[i]);
        Serial.print("mm, Measured: ");
        Serial.print(measured);
        Serial.print("mm, Error: ");
        Serial.print(percentageError);
        Serial.println("%");
        
        if (abs(percentageError) > tolerance) {
            allPassed = false;
        }
    }
    
    return allPassed;
}
```

### Calibration Procedure Steps

```
┌─────────────────────────────────────────────────────────────────────┐
│                    LIDAR CALIBRATION PROCEDURE                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Step 1: Offset Calibration                                       │
│   ─────────────────────────────────────────────────────────────────│
│   1. Place sensor at known distance from target                    │
│   2. Take 10-20 readings                                          │
│   3. Calculate average distance                                    │
│   4. Calculate offset = known_distance - measured_distance        │
│   5. Apply offset to all subsequent readings                      │
│                                                                     │
│   Step 2: Signal Rate Calibration                                 │
│   ─────────────────────────────────────────────────────────────────│
│   1. Place target at 200mm                                        │
│   2. Measure signal rate                                           │
│   3. Repeat at different distances                                 │
│   4. Create signal rate profile                                    │
│   5. Apply compensation factor                                     │
│                                                                     │
│   Step 3: Cross-Talk Calibration                                  │
│   ─────────────────────────────────────────────────────────────────│
│   1. Measure with no target                                        │
│   2. Measure with 50% reflective target                           │
│   3. Calculate cross-talk coefficient                              │
│   4. Apply compensation                                            │
│                                                                     │
│   Step 4: Verification                                             │
│   ─────────────────────────────────────────────────────────────────│
│   1. Test at 5 different distances                                 │
│   2. Calculate error percentage                                    │
│   3. Ensure error < 2%                                             │
│   4. Save calibration data                                         │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## GPS Calibration

### NEO-6M GPS Calibration

```cpp
/*
 * GPS Calibration Procedure
 * NEO-6M GPS Module
 */

class GPSCalibration {
public:
    // Calibration Data
    struct CalibrationData {
        double latitude;           // Reference latitude
        double longitude;          // Reference longitude
        float altitude;            // Reference altitude
        float horizontalAccuracy;  // Horizontal accuracy
        float verticalAccuracy;    // Vertical accuracy
        uint32_t fixTime;          // Time to first fix
        bool calibrated;
    };
    
    // Calibration Functions
    bool calibratePosition(double refLat, double refLng, float refAlt);
    bool calibrateTime();
    bool calibrateSatellites();
    void setTimeToFix(uint32_t time);
    
    // Verification Functions
    bool verifyPosition(double tolerance = 10.0);
    bool verifyAccuracy();
    String getCalibrationReport();
    
    // Data Management
    bool saveCalibration();
    bool loadCalibration();
    bool exportCalibration(const String& filename);
    bool importCalibration(const String& filename);
    
private:
    CalibrationData m_calData;
    TinyGPSPlus m_gps;
    
    double getLatitude();
    double getLongitude();
    float getAltitude();
    float calculateDistance(double lat1, double lng1, double lat2, double lng2);
};

// GPS Calibration Implementation
bool GPSCalibration::calibratePosition(double refLat, double refLng, float refAlt) {
    Serial.println("=== GPS Position Calibration ===");
    Serial.println("Waiting for GPS fix...");
    
    // Wait for valid GPS fix
    unsigned long start = millis();
    while (!m_gps.location.isValid() && (millis() - start) < 300000) { // 5 min timeout
        // Keep reading GPS data
        while (m_serial.available()) {
            m_gps.encode(m_serial.read());
        }
        delay(100);
    }
    
    if (!m_gps.location.isValid()) {
        Serial.println("GPS fix timeout!");
        return false;
    }
    
    // Store reference position
    m_calData.latitude = refLat;
    m_calData.longitude = refLng;
    m_calData.altitude = refAlt;
    m_calData.calibrated = true;
    
    // Calculate accuracy
    float horizontalError = calculateDistance(
        m_gps.location.lat(), m_gps.location.lng(),
        refLat, refLng
    );
    m_calData.horizontalAccuracy = horizontalError;
    
    Serial.print("Reference position: ");
    Serial.print(refLat, 6);
    Serial.print(", ");
    Serial.println(refLng, 6);
    Serial.print("GPS position: ");
    Serial.print(m_gps.location.lat(), 6);
    Serial.print(", ");
    Serial.println(m_gps.location.lng(), 6);
    Serial.print("Horizontal error: ");
    Serial.print(horizontalError);
    Serial.println("m");
    
    return true;
}
```

---

## Fingerprint Sensor Calibration

### R307 Fingerprint Calibration

```cpp
/*
 * Fingerprint Sensor Calibration
 * R307 Fingerprint Module
 */

class FingerprintCalibration {
public:
    // Calibration Data
    struct CalibrationData {
        uint8_t securityLevel;     // 1-5 (higher = more secure)
        uint8_t confidence;        // Match confidence threshold
        uint16_t enrollmentCount;  // Number of enrolled fingerprints
        uint8_t defaultLevel;      // Default security level
        bool calibrated;
    };
    
    // Calibration Functions
    bool calibrateSecurityLevel(uint8_t level);
    bool calibrateConfidence(uint8_t confidence);
    bool testMatchingAccuracy();
    bool optimizeSettings();
    
    // Verification Functions
    bool verifyEnrollment();
    bool verifyMatching();
    String getCalibrationReport();
    
    // Data Management
    bool saveCalibration();
    bool loadCalibration();
    bool exportCalibration(const String& filename);
    bool importCalibration(const String& filename);
    
private:
    CalibrationData m_calData;
    Adafruit_Fingerprint m_sensor;
    
    uint8_t getCurrentConfidence();
    uint8_t getCurrentLevel();
    bool testFingerDetection();
};

// Fingerprint Calibration Implementation
bool FingerprintCalibration::calibrateSecurityLevel(uint8_t level) {
    Serial.println("=== Fingerprint Security Calibration ===");
    
    // Set security level
    m_calData.securityLevel = level;
    m_calData.calibrated = true;
    
    Serial.print("Security level set to: ");
    Serial.println(level);
    Serial.println(" 1 = Lowest security, 5 = Highest security");
    
    // Test with known fingerprints
    uint8_t matched = 0;
    uint8_t total = 5;
    
    for (int i = 0; i < total; i++) {
        Serial.print("Place finger ");
        Serial.print(i + 1);
        Serial.println(" on sensor...");
        
        uint8_t result = m_sensor.getImage();
        if (result == FINGERPRINT_OK) {
            result = m_sensor.image2Tz();
            if (result == FINGERPRINT_OK) {
                result = m_sensor.fingerSearch();
                if (result == FINGERPRINT_OK) {
                    matched++;
                    Serial.print("✓ Finger ");
                    Serial.print(i + 1);
                    Serial.println(" matched!");
                }
            }
        }
        
        delay(1000);
    }
    
    float accuracy = (matched * 100.0) / total;
    Serial.print("Matching accuracy: ");
    Serial.print(accuracy);
    Serial.println("%");
    
    if (accuracy >= 95.0) {
        Serial.println("✓ Calibration successful");
        return true;
    } else {
        Serial.println("✗ Calibration failed - adjust security level");
        return false;
    }
}
```

---

## RFID/NFC Calibration

### MFRC522 RFID Calibration

```cpp
/*
 * RFID/NFC Reader Calibration
 * MFRC522 Module
 */

class RFIDCalibration {
public:
    // Calibration Data
    struct CalibrationData {
        uint8_t antennaGain;       // 0-7 (higher = more sensitive)
        uint16_t readRange;        // Read range in mm
        uint8_t maxRetries;        // Maximum retry attempts
        bool calibrated;
    };
    
    // Calibration Functions
    bool calibrateAntenna(uint8_t gain);
    bool calibrateReadRange();
    bool calibrateRetries(uint8_t retries);
    
    // Verification Functions
    bool verifyReadRange();
    bool verifyRFIDReading();
    String getCalibrationReport();
    
    // Data Management
    bool saveCalibration();
    bool loadCalibration();
    bool exportCalibration(const String& filename);
    bool importCalibration(const String& filename);
    
private:
    CalibrationData m_calData;
    MFRC522 m_rfid;
    
    uint16_t measureReadRange();
    bool detectCard();
    String readCardUID();
};

// RFID Calibration Implementation
bool RFIDCalibration::calibrateAntenna(uint8_t gain) {
    Serial.println("=== RFID Antenna Calibration ===");
    
    // Set antenna gain
    m_rfid.PCD_SetAntennaGain(gain);
    m_calData.antennaGain = gain;
    
    // Test read range
    uint16_t range = measureReadRange();
    m_calData.readRange = range;
    m_calData.calibrated = true;
    
    Serial.print("Antenna gain set to: ");
    Serial.println(gain);
    Serial.print("Read range: ");
    Serial.print(range);
    Serial.println(" mm");
    
    // Verify range is acceptable
    if (range > 30) {
        Serial.println("✓ Calibration successful");
        return true;
    } else {
        Serial.println("✗ Range too short - adjust gain");
        return false;
    }
}

uint16_t RFIDCalibration::measureReadRange() {
    // Move card away until not detected
    // This is a simplified version
    uint16_t range = 0;
    
    // Test at different distances
    for (uint16_t distance = 5; distance <= 80; distance += 5) {
        // Simulated distance test
        if (detectCard()) {
            range = distance;
        } else {
            break;
        }
        delay(100);
    }
    
    return range;
}
```

---

## ADC Calibration

### ADC Reference Calibration

```cpp
/*
 * ADC Calibration
 * ATmega328P 10-bit ADC
 */

class ADCCalibration {
public:
    // Calibration Data
    struct CalibrationData {
        float referenceVoltage;    // Reference voltage
        float offset;             // Offset error
        float gain;               // Gain error
        float linearity;          // Linearity error
        bool calibrated;
    };
    
    // Calibration Functions
    bool calibrateReference(float knownVoltage);
    bool calibrateOffset();
    bool calibrateGain(float knownVoltage1, float knownVoltage2);
    bool calibrateLinearity();
    
    // Verification Functions
    bool verifyADCAccuracy();
    bool verifyResolution();
    String getCalibrationReport();
    
    // Data Management
    bool saveCalibration();
    bool loadCalibration();
    bool exportCalibration(const String& filename);
    bool importCalibration(const String& filename);
    
    // Utility
    float readCalibratedADC(uint8_t pin);
    float convertToVoltage(uint16_t adcValue);
    
private:
    CalibrationData m_calData;
    uint16_t m_reference;
    
    uint16_t readADC(uint8_t pin, uint8_t samples = 10);
    float calculateError(uint16_t measured, uint16_t expected);
};

// ADC Calibration Implementation
bool ADCCalibration::calibrateReference(float knownVoltage) {
    Serial.println("=== ADC Reference Calibration ===");
    Serial.print("Applying known voltage: ");
    Serial.print(knownVoltage);
    Serial.println("V");
    
    // Read ADC value
    uint16_t adcValue = readADC(A0, 50);
    float measuredVoltage = (adcValue * 5.0) / 1023.0;
    
    // Calculate reference voltage
    m_calData.referenceVoltage = (knownVoltage * 5.0) / measuredVoltage;
    m_calData.calibrated = true;
    
    Serial.print("ADC Reading: ");
    Serial.println(adcValue);
    Serial.print("Measured Voltage: ");
    Serial.print(measuredVoltage);
    Serial.println("V");
    Serial.print("Calculated Reference: ");
    Serial.print(m_calData.referenceVoltage);
    Serial.println("V");
    
    // Verify within tolerance
    if (abs(measuredVoltage - knownVoltage) < 0.01) {
        Serial.println("✓ Calibration successful");
        return true;
    } else {
        Serial.println("✗ Calibration failed - check reference");
        return false;
    }
}

float ADCCalibration::readCalibratedADC(uint8_t pin) {
    uint16_t raw = readADC(pin, 10);
    
    // Apply calibration
    float voltage = (raw / 1023.0) * m_calData.referenceVoltage;
    voltage += m_calData.offset;
    voltage *= m_calData.gain;
    
    return voltage;
}
```

---

## Power Monitoring Calibration

### Power Monitor Calibration

```cpp
/*
 * Power Monitoring Calibration
 * Voltage Divider + ACS712 Current Sensor
 */

class PowerCalibration {
public:
    // Calibration Data
    struct CalibrationData {
        float voltageDividerRatio;   // R1/R2 ratio
        float currentSensorOffset;   // ACS712 zero offset
        float currentSensitivity;    // ACS712 mV/A
        float powerFactor;          // Power factor correction
        bool calibrated;
    };
    
    // Calibration Functions
    bool calibrateVoltageDivider(float knownVoltage);
    bool calibrateCurrentSensor(float knownCurrent);
    bool calibratePowerFactor();
    
    // Verification Functions
    bool verifyPowerAccuracy();
    bool verifyCurrentAccuracy();
    String getCalibrationReport();
    
    // Data Management
    bool saveCalibration();
    bool loadCalibration();
    bool exportCalibration(const String& filename);
    bool importCalibration(const String& filename);
    
    // Measurements
    float readCalibratedVoltage();
    float readCalibratedCurrent();
    float readCalibratedPower();
    
private:
    CalibrationData m_calData;
    uint8_t m_voltagePin;
    uint8_t m_currentPin;
    
    float readADCVoltage(uint8_t pin);
};

// Power Calibration Implementation
bool PowerCalibration::calibrateVoltageDivider(float knownVoltage) {
    Serial.println("=== Voltage Divider Calibration ===");
    Serial.print("Applying known voltage: ");
    Serial.print(knownVoltage);
    Serial.println("V");
    
    float measuredVoltage = readADCVoltage(m_voltagePin);
    m_calData.voltageDividerRatio = knownVoltage / measuredVoltage;
    m_calData.calibrated = true;
    
    Serial.print("Measured voltage: ");
    Serial.print(measuredVoltage);
    Serial.println("V");
    Serial.print("Voltage divider ratio: ");
    Serial.println(m_calData.voltageDividerRatio);
    
    if (abs(measuredVoltage - knownVoltage) < 0.1) {
        Serial.println("✓ Calibration successful");
        return true;
    } else {
        Serial.println("✗ Calibration failed - check connections");
        return false;
    }
}

bool PowerCalibration::calibrateCurrentSensor(float knownCurrent) {
    Serial.println("=== Current Sensor Calibration ===");
    Serial.print("Applying known current: ");
    Serial.print(knownCurrent);
    Serial.println("A");
    
    float measuredCurrent = readADCVoltage(m_currentPin);
    // ACS712: 185mV/A for 5A version, 100mV/A for 20A version
    float sensitivity = 0.100; // 20A version
    
    m_calData.currentSensorOffset = 2.5; // 2.5V at zero current
    m_calData.currentSensitivity = sensitivity;
    
    Serial.print("Measured current: ");
    Serial.print(measuredCurrent);
    Serial.println("A");
    
    if (abs(measuredCurrent - knownCurrent) < 0.05) {
        Serial.println("✓ Calibration successful");
        return true;
    } else {
        Serial.println("✗ Calibration failed - check connections");
        return false;
    }
}
```

---

## Temperature Sensor Calibration

### Temperature Sensor Calibration

```cpp
/*
 * Temperature Sensor Calibration
 * LM35/Thermistor Sensor
 */

class TemperatureCalibration {
public:
    // Calibration Data
    struct CalibrationData {
        float offset;               // Temperature offset in °C
        float gain;                // Gain correction
        float referenceTemp;       // Reference temperature
        bool calibrated;
    };
    
    // Calibration Functions
    bool calibrateOffset(float referenceTemperature);
    bool calibrateGain();
    
    // Verification Functions
    bool verifyTemperatureAccuracy();
    String getCalibrationReport();
    
    // Data Management
    bool saveCalibration();
    bool loadCalibration();
    bool exportCalibration(const String& filename);
    bool importCalibration(const String& filename);
    
    // Measurements
    float readCalibratedTemperature();
    
private:
    CalibrationData m_calData;
    uint8_t m_sensorPin;
    
    float readRawTemperature();
};

// Temperature Calibration Implementation
bool TemperatureCalibration::calibrateOffset(float referenceTemperature) {
    Serial.println("=== Temperature Sensor Calibration ===");
    Serial.print("Reference temperature: ");
    Serial.print(referenceTemperature);
    Serial.println("°C");
    
    float measuredTemp = readRawTemperature();
    m_calData.offset = referenceTemperature - measuredTemp;
    m_calData.referenceTemp = referenceTemperature;
    m_calData.calibrated = true;
    
    Serial.print("Measured temperature: ");
    Serial.print(measuredTemp);
    Serial.println("°C");
    Serial.print("Offset: ");
    Serial.print(m_calData.offset);
    Serial.println("°C");
    
    if (abs(measuredTemp - referenceTemperature) < 1.0) {
        Serial.println("✓ Calibration successful");
        return true;
    } else {
        Serial.println("✗ Calibration failed - check sensor");
        return false;
    }
}
```

---

## Calibration Procedures

### Full System Calibration Procedure

```cpp
/*
 * Full System Calibration
 * Complete calibration sequence
 */

class SystemCalibration {
public:
    // Run full calibration
    bool runFullCalibration();
    bool runQuickCalibration();
    bool runSensorCalibration();
    bool runPowerCalibration();
    
    // Calibration Sequence
    void calibrationSequence();
    
    // Status
    bool isCalibrated();
    String getCalibrationStatus();
    
    // Data Management
    bool saveAllCalibrations();
    bool loadAllCalibrations();
    bool exportAllCalibrations(const String& directory);
    bool importAllCalibrations(const String& directory);
    
private:
    LiDARCalibration m_lidarCal;
    GPSCalibration m_gpsCal;
    FingerprintCalibration m_fingerCal;
    RFIDCalibration m_rfidCal;
    ADCCalibration m_adcCal;
    PowerCalibration m_powerCal;
    TemperatureCalibration m_tempCal;
    
    bool m_allCalibrated;
};

// Full Calibration Implementation
bool SystemCalibration::runFullCalibration() {
    Serial.println("╔═══════════════════════════════════════════════╗");
    Serial.println("║     FULL SYSTEM CALIBRATION                  ║");
    Serial.println("╚═══════════════════════════════════════════════╝");
    
    bool allPassed = true;
    
    // 1. Power Calibration
    Serial.println("\n[1/7] Power Calibration...");
    if (!m_powerCal.calibrateVoltageDivider(5.0)) {
        allPassed = false;
    }
    if (!m_powerCal.calibrateCurrentSensor(0.5)) {
        allPassed = false;
    }
    
    // 2. ADC Calibration
    Serial.println("\n[2/7] ADC Calibration...");
    if (!m_adcCal.calibrateReference(2.5)) {
        allPassed = false;
    }
    
    // 3. LiDAR Calibration
    Serial.println("\n[3/7] LiDAR Calibration...");
    if (!m_lidarCal.calibrateOffset(200)) {
        allPassed = false;
    }
    
    // 4. GPS Calibration
    Serial.println("\n[4/7] GPS Calibration...");
    // Requires user to enter reference coordinates
    double refLat = 37.774929;
    double refLng = -122.419418;
    float refAlt = 15.2;
    if (!m_gpsCal.calibratePosition(refLat, refLng, refAlt)) {
        allPassed = false;
    }
    
    // 5. Fingerprint Calibration
    Serial.println("\n[5/7] Fingerprint Calibration...");
    if (!m_fingerCal.calibrateSecurityLevel(3)) {
        allPassed = false;
    }
    
    // 6. RFID Calibration
    Serial.println("\n[6/7] RFID Calibration...");
    if (!m_rfidCal.calibrateAntenna(4)) {
        allPassed = false;
    }
    
    // 7. Temperature Calibration
    Serial.println("\n[7/7] Temperature Calibration...");
    if (!m_tempCal.calibrateOffset(25.0)) {
        allPassed = false;
    }
    
    // Final Verification
    Serial.println("\n=== Verification ===");
    if (allPassed) {
        Serial.println("✓ All calibrations completed successfully");
        m_allCalibrated = true;
        saveAllCalibrations();
    } else {
        Serial.println("✗ Some calibrations failed");
    }
    
    return allPassed;
}
```

---

## Calibration Verification

### Verification Procedure

```cpp
/*
 * Calibration Verification
 * Verify all calibrations
 */

void verifyAllCalibrations() {
    Serial.println("\n=== CALIBRATION VERIFICATION ===");
    
    // Test LiDAR
    Serial.println("\nTesting LiDAR accuracy...");
    // Use known distances: 100mm, 500mm, 1000mm
    int testDistances[] = {100, 500, 1000, 1500, 2000};
    for (int i = 0; i < 5; i++) {
        // Place target at testDistances[i]
        uint16_t measured = readLiDARDistance();
        float error = abs(measured - testDistances[i]);
        float percentage = (error / testDistances[i]) * 100.0;
        
        Serial.print("  ");
        Serial.print(testDistances[i]);
        Serial.print("mm: ");
        Serial.print(measured);
        Serial.print("mm (");
        Serial.print(percentage);
        Serial.println("% error)");
    }
    
    // Test GPS
    Serial.println("\nTesting GPS accuracy...");
    // Wait for GPS fix
    waitForGPSFix();
    double lat = getGPSLatitude();
    double lng = getGPSLongitude();
    Serial.print("  GPS Position: ");
    Serial.print(lat, 6);
    Serial.print(", ");
    Serial.println(lng, 6);
    
    // Test ADC
    Serial.println("\nTesting ADC accuracy...");
    // Apply known voltages: 0V, 1.0V, 2.0V, 3.0V, 4.0V, 5.0V
    float voltages[] = {0, 1.0, 2.0, 3.0, 4.0, 5.0};
    for (int i = 0; i < 6; i++) {
        float measured = readADCVoltage(A0);
        float error = abs(measured - voltages[i]);
        Serial.print("  ");
        Serial.print(voltages[i]);
        Serial.print("V: ");
        Serial.print(measured);
        Serial.print("V (");
        Serial.print(error * 100);
        Serial.println("% error)");
    }
}
```

---

## Troubleshooting Calibration Issues

### Common Issues and Solutions

```
┌─────────────────────────────────────────────────────────────────────┐
│                    CALIBRATION TROUBLESHOOTING                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Issue 1: LiDAR Calibration Fails                                 │
│   ├── Possible Causes:                                             │
│   │   ● Target not reflective enough                              │
│   │   ● Sensor not stable                                         │
│   │   ● Ambient light interference                                │
│   └── Solutions:                                                   │
│       ● Use white paper target                                    │
│       ● Mount sensor securely                                     │
│       ● Reduce ambient light                                      │
│                                                                     │
│   Issue 2: GPS Not Getting Fix                                     │
│   ├── Possible Causes:                                             │
│   │   ● Antenna not connected                                     │
│   │   ● Not enough satellites                                     │
│   │   ● RF interference                                           │
│   └── Solutions:                                                   │
│       ● Check antenna connection                                  │
│       ● Move to open area                                         │
│       ● Wait for satellites                                       │
│                                                                     │
│   Issue 3: Fingerprint Not Matching                                │
│   ├── Possible Causes:                                             │
│   │   ● Dirty sensor                                              │
│   │   ● Poor finger placement                                     │
│   │   ● Security level too high                                   │
│   └── Solutions:                                                   │
│       ● Clean sensor surface                                      │
│       ● Proper finger placement                                   │
│       ● Lower security level                                      │
│                                                                     │
│   Issue 4: ADC Readings Inaccurate                                 │
│   ├── Possible Causes:                                             │
│   │   ● Noisy power supply                                        │
│   │   ● Reference voltage drift                                   │
│   │   ● Temperature effects                                       │
│   └── Solutions:                                                   │
│       ● Use stable power supply                                   │
│       ● Check reference voltage                                   │
│       ● Allow warm-up time                                        │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### Calibration Error Codes

```cpp
// Calibration Error Codes
enum CalibrationError {
    CAL_OK = 0,
    CAL_ERROR_TIMEOUT = 1,
    CAL_ERROR_READING = 2,
    CAL_ERROR_STABILITY = 3,
    CAL_ERROR_OFFSET = 4,
    CAL_ERROR_GAIN = 5,
    CAL_ERROR_REFERENCE = 6,
    CAL_ERROR_SENSOR = 7,
    CAL_ERROR_COMMUNICATION = 8,
    CAL_ERROR_SAVE = 9,
    CAL_ERROR_LOAD = 10,
    CAL_ERROR_VERIFY = 11
};

// Error Handling
void handleCalibrationError(CalibrationError error, const String& component) {
    Serial.print("Calibration error in ");
    Serial.print(component);
    Serial.print(": ");
    
    switch(error) {
        case CAL_ERROR_TIMEOUT:
            Serial.println("Operation timed out");
            break;
        case CAL_ERROR_READING:
            Serial.println("Failed to read sensor");
            break;
        case CAL_ERROR_STABILITY:
            Serial.println("Reading not stable");
            break;
        case CAL_ERROR_OFFSET:
            Serial.println("Offset calculation failed");
            break;
        case CAL_ERROR_GAIN:
            Serial.println("Gain calculation failed");
            break;
        case CAL_ERROR_REFERENCE:
            Serial.println("Invalid reference value");
            break;
        case CAL_ERROR_SENSOR:
            Serial.println("Sensor not responding");
            break;
        default:
            Serial.println("Unknown error");
            break;
    }
}
```

---

## 📚 Related Documentation

- [Sensor API](../api/sensor_api.md)
- [Hardware Documentation](../hardware/)
- [Troubleshooting Guide](troubleshooting.md)
- [Build & Deployment Guide](../BUILD_DEPLOY.md)

---

