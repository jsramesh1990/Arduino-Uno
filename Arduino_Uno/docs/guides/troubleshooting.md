# docs/guides/troubleshooting.md

# Troubleshooting Guide
## Arduino Multi-Sensor Platform

---

## 📚 Table of Contents
1. [Introduction](#introduction)
2. [General Troubleshooting](#general-troubleshooting)
3. [Hardware Issues](#hardware-issues)
4. [Software Issues](#software-issues)
5. [Sensor-Specific Issues](#sensor-specific-issues)
6. [Communication Issues](#communication-issues)
7. [Power Issues](#power-issues)
8. [Performance Issues](#performance-issues)
9. [Error Codes](#error-codes)
10. [Diagnostic Tools](#diagnostic-tools)
11. [Recovery Procedures](#recovery-procedures)

---

## Introduction

This comprehensive troubleshooting guide helps you diagnose and resolve common issues with the Arduino Multi-Sensor Platform. It covers hardware, software, sensors, and communication problems with step-by-step solutions.

### Quick Reference

```
┌─────────────────────────────────────────────────────────────────────┐
│                    QUICK DIAGNOSTIC FLOW                            │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Problem Detected                                                 │
│         │                                                          │
│         ▼                                                          │
│   Check Power Supply                                               │
│         │                                                          │
│         ▼                                                          │
│   Check Physical Connections                                       │
│         │                                                          │
│         ▼                                                          │
│   Check Serial Output                                              │
│         │                                                          │
│         ▼                                                          │
│   Run Diagnostic Tests                                             │
│         │                                                          │
│         ▼                                                          │
│   Check Module-Specific Issues                                     │
│         │                                                          │
│         ▼                                                          │
│   Implement Solution                                               │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## General Troubleshooting

### System Not Responding

```cpp
/*
 * System Health Check
 * Run this diagnostic to check system status
 */

void systemHealthCheck() {
    Serial.println("╔═══════════════════════════════════════════════╗");
    Serial.println("║     SYSTEM HEALTH CHECK                      ║");
    Serial.println("╚═══════════════════════════════════════════════╝");
    
    bool allOK = true;
    
    // 1. Check Power
    Serial.print("\n[1/5] Checking Power... ");
    float voltage = readSystemVoltage();
    if (voltage > 4.8 && voltage < 5.2) {
        Serial.println("✓ OK (" + String(voltage) + "V)");
    } else {
        Serial.println("✗ FAILED (" + String(voltage) + "V)");
        allOK = false;
    }
    
    // 2. Check Serial Connection
    Serial.print("[2/5] Checking Serial... ");
    if (Serial) {
        Serial.println("✓ OK");
    } else {
        Serial.println("✗ FAILED");
        allOK = false;
    }
    
    // 3. Check Memory
    Serial.print("[3/5] Checking Memory... ");
    int freeMem = freeMemory();
    if (freeMem > 100) {
        Serial.println("✓ OK (" + String(freeMem) + " bytes)");
    } else {
        Serial.println("✗ LOW (" + String(freeMem) + " bytes)");
        allOK = false;
    }
    
    // 4. Check I2C Bus
    Serial.print("[4/5] Checking I2C... ");
    uint8_t devices = scanI2C();
    if (devices > 0) {
        Serial.println("✓ OK (" + String(devices) + " devices)");
    } else {
        Serial.println("✗ FAILED (No devices found)");
        allOK = false;
    }
    
    // 5. Check SPI Bus
    Serial.print("[5/5] Checking SPI... ");
    if (testSPI()) {
        Serial.println("✓ OK");
    } else {
        Serial.println("✗ FAILED");
        allOK = false;
    }
    
    // Summary
    Serial.println("\n" + String(allOK ? "✅ SYSTEM HEALTHY" : "❌ SYSTEM ISSUES DETECTED"));
}
```

### Diagnostic LED Patterns

```cpp
/*
 * LED Error Code Patterns
 * Blink patterns indicate specific issues
 */

enum ErrorCode {
    ERROR_NONE = 0,
    ERROR_POWER = 1,        // 1 blink
    ERROR_I2C = 2,          // 2 blinks
    ERROR_SPI = 3,          // 3 blinks
    ERROR_UART = 4,         // 4 blinks
    ERROR_SENSOR = 5,       // 5 blinks
    ERROR_COMM = 6,         // 6 blinks
    ERROR_MEMORY = 7,       // 7 blinks
    ERROR_CONFIG = 8,       // 8 blinks
    ERROR_GSM = 9,          // 9 blinks
    ERROR_LORA = 10         // 10 blinks
};

void blinkErrorCode(ErrorCode code) {
    int count = (int)code;
    
    for (int i = 0; i < count; i++) {
        digitalWrite(PIN_LED, HIGH);
        delay(200);
        digitalWrite(PIN_LED, LOW);
        delay(200);
    }
    
    // Pause between patterns
    delay(1000);
}
```

---

## Hardware Issues

### Arduino Not Detected

```
┌─────────────────────────────────────────────────────────────────────┐
│                    ARDUINO NOT DETECTED                            │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Symptoms:                                                        │
│   ● Board not listed in Arduino CLI                               │
│   ● Port not found                                                │
│   ● Upload fails                                                  │
│                                                                     │
│   Steps to Fix:                                                    │
│   ─────────────────────────────────────────────────────────────────│
│   □ Check USB cable                                                │
│   □ Try different USB port                                        │
│   □ Install/Update drivers                                        │
│   □ Check board power                                             │
│   □ Reset board manually                                          │
│   □ Check for hardware damage                                     │
│                                                                     │
│   Linux Specific:                                                  │
│   $ sudo lsusb                                                    │
│   $ sudo dmesg | grep tty                                        │
│   $ sudo chmod a+rw /dev/ttyUSB0                                 │
│                                                                     │
│   Windows Specific:                                                │
│   ● Check Device Manager                                          │
│   ● Install CH340/FTDI drivers                                    │
│   ● Try different USB port                                        │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### Module Not Initializing

```cpp
/*
 * Module Initialization Diagnostic
 */

bool diagnoseModuleInit(int moduleID) {
    String moduleName;
    bool result = false;
    
    switch(moduleID) {
        case MODULE_LIDAR:
            moduleName = "LiDAR";
            result = lidar.begin();
            break;
        case MODULE_GPS:
            moduleName = "GPS";
            result = gps.begin(9600);
            break;
        case MODULE_FINGERPRINT:
            moduleName = "Fingerprint";
            result = finger.begin(57600);
            break;
        case MODULE_RFID:
            moduleName = "RFID";
            result = rfid.begin();
            break;
        case MODULE_CAN:
            moduleName = "CAN";
            result = can.begin(CAN_500KBPS);
            break;
        case MODULE_LORA:
            moduleName = "LoRa";
            result = lora.begin(868E6);
            break;
        case MODULE_GSM:
            moduleName = "GSM";
            result = gsm.begin(9600);
            break;
        default:
            moduleName = "Unknown";
            result = false;
    }
    
    if (result) {
        Serial.println("✓ " + moduleName + " initialized");
    } else {
        Serial.println("✗ " + moduleName + " initialization failed");
        Serial.println("  Check:");
        Serial.println("  - Power connections");
        Serial.println("  - Signal connections");
        Serial.println("  - Module address/settings");
    }
    
    return result;
}
```

---

## Software Issues

### Compilation Errors

```
┌─────────────────────────────────────────────────────────────────────┐
│                    COMPILATION ERRORS                              │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Common Errors:                                                   │
│   ─────────────────────────────────────────────────────────────────│
│                                                                     │
│   1. "Board not found"                                             │
│      Solution: Verify board selection                              │
│      $ arduino-cli board list                                      │
│                                                                     │
│   2. "Library not found"                                           │
│      Solution: Install missing libraries                           │
│      $ arduino-cli lib install <library>                          │
│                                                                     │
│   3. "Multiple libraries found"                                    │
│      Solution: Specify library path                                │
│      #include <path/to/library.h>                                  │
│                                                                     │
│   4. "Sketch too large"                                            │
│      Solution: Optimize code                                       │
│      - Remove unused libraries                                     │
│      - Use PROGMEM for strings                                     │
│      - Optimize global variables                                   │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### Serial Communication Issues

```cpp
/*
 * Serial Communication Diagnostic
 */

void diagnoseSerial() {
    Serial.println("\n=== SERIAL DIAGNOSTIC ===\n");
    
    // 1. Check Serial Availability
    if (Serial) {
        Serial.println("✓ Serial available");
    } else {
        Serial.println("✗ Serial not available");
        return;
    }
    
    // 2. Check Baud Rate
    Serial.println("Current baud rate: 115200");
    Serial.println("Testing communication...");
    
    // 3. Send Test Data
    Serial.println("Sending test data...");
    uint8_t testData[] = {0xAA, 0x55, 0x01, 0x02, 0x03, 0x04, 0xCC, 0x33};
    Serial.write(testData, sizeof(testData));
    
    // 4. Check Receive Buffer
    if (Serial.available()) {
        Serial.print("Data available: ");
        Serial.println(Serial.available());
    }
    
    // 5. Test Loopback
    Serial.println("\nTesting loopback...");
    Serial.println("Please connect TX to RX (pins 1 and 0)");
    delay(2000);
    
    Serial.write("LOOPBACK TEST");
    delay(100);
    
    if (Serial.available()) {
        String response = Serial.readString();
        if (response == "LOOPBACK TEST") {
            Serial.println("✓ Loopback test passed");
        } else {
            Serial.println("✗ Loopback test failed");
        }
    }
}
```

---

## Sensor-Specific Issues

### LiDAR Issues

```
┌─────────────────────────────────────────────────────────────────────┐
│                    LIDAR TROUBLESHOOTING                           │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Issue: No Readings                                               │
│   ├── Check: Power (3.3V)                                         │
│   ├── Check: I2C connection (A4/A5)                               │
│   ├── Check: Address (0x29)                                       │
│   └── Fix: Reset sensor, check wiring                             │
│                                                                     │
│   Issue: Inaccurate Readings                                       │
│   ├── Check: Target reflectivity                                  │
│   ├── Check: Ambient light                                        │
│   ├── Check: Calibration                                          │
│   └── Fix: Re-calibrate, use reference target                     │
│                                                                     │
│   Issue: Fluctuating Readings                                      │
│   ├── Check: Power stability                                      │
│   ├── Check: Mechanical stability                                 │
│   ├── Check: Interference                                         │
│   └── Fix: Stabilize mounting, filter readings                    │
│                                                                     │
│   Diagnostic Code:                                                 │
│   ─────────────────────────────────────────────────────────────────│
│   void diagnoseLiDAR() {                                          │
│       if (!lidar.begin()) {                                       │
│           Serial.println("LiDAR not found!");                     │
│           Serial.println("Check I2C connections");               │
│           return;                                                 │
│       }                                                           │
│       uint16_t distance = lidar.getDistance();                    │
│       uint8_t status = lidar.getRangeStatus();                   │
│       Serial.print("Distance: ");                                │
│       Serial.print(distance);                                    │
│       Serial.print(" mm, Status: ");                             │
│       Serial.println(status == 0 ? "Good" : "Bad");             │
│   }                                                               │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### GPS Issues

```
┌─────────────────────────────────────────────────────────────────────┐
│                    GPS TROUBLESHOOTING                             │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Issue: No Fix                                                    │
│   ├── Check: Antenna connection                                   │
│   ├── Check: Sky visibility                                       │
│   ├── Check: Time to fix (>60s)                                   │
│   └── Fix: Move to open area, check antenna                       │
│                                                                     │
│   Issue: No Data                                                   │
│   ├── Check: UART connections (D3/D4)                             │
│   ├── Check: Baud rate (9600)                                     │
│   ├── Check: Power (5V)                                           │
│   └── Fix: Check wiring, verify serial                            │
│                                                                     │
│   Issue: Wrong Location                                            │
│   ├── Check: Satellites in view                                   │
│   ├── Check: HDOP value                                           │
│   ├── Check: Obstructions                                         │
│   └── Fix: Wait for better signal, calibrate                      │
│                                                                     │
│   Diagnostic Code:                                                 │
│   ─────────────────────────────────────────────────────────────────│
│   void diagnoseGPS() {                                            │
│       if (gps.location.isValid()) {                               │
│           Serial.print("Lat: ");                                  │
│           Serial.print(gps.location.lat(), 6);                   │
│           Serial.print(", Lng: ");                                │
│           Serial.print(gps.location.lng(), 6);                   │
│           Serial.print(", Sats: ");                               │
│           Serial.println(gps.satellites.value());                │
│       } else {                                                    │
│           Serial.println("No GPS fix");                          │
│           Serial.print("Satellites: ");                           │
│           Serial.println(gps.satellites.value());                │
│       }                                                           │
│   }                                                               │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### Fingerprint Issues

```
┌─────────────────────────────────────────────────────────────────────┐
│                    FINGERPRINT TROUBLESHOOTING                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Issue: Sensor Not Detected                                       │
│   ├── Check: Power (5V)                                           │
│   ├── Check: UART connections (D5/D6)                             │
│   ├── Check: Baud rate (57600)                                    │
│   └── Fix: Verify wiring, reset sensor                            │
│                                                                     │
│   Issue: No Finger Detected                                        │
│   ├── Check: Sensor surface clean                                 │
│   ├── Check: Finger placement                                     │
│   ├── Check: Sensitivity                                          │
│   └── Fix: Clean sensor, adjust placement                         │
│                                                                     │
│   Issue: False Matches                                             │
│   ├── Check: Security level                                       │
│   ├── Check: Database size                                        │
│   ├── Check: Enrollment quality                                   │
│   └── Fix: Re-enroll, increase security level                     │
│                                                                     │
│   Diagnostic Code:                                                 │
│   ─────────────────────────────────────────────────────────────────│
│   void diagnoseFingerprint() {                                    │
│       if (finger.verifyPassword()) {                              │
│           Serial.println("✓ Fingerprint sensor found");          │
│           Serial.print("Database size: ");                        │
│           Serial.println(finger.getDatabaseSize());              │
│       } else {                                                    │
│           Serial.println("✗ Fingerprint sensor not found");      │
│           Serial.println("Check connections and power");         │
│       }                                                           │
│   }                                                               │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### RFID Issues

```
┌─────────────────────────────────────────────────────────────────────┐
│                    RFID TROUBLESHOOTING                            │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Issue: No Card Detected                                          │
│   ├── Check: Power (3.3V)                                         │
│   ├── Check: SPI connections                                      │
│   ├── Check: Antenna                                              │
│   └── Fix: Check wiring, adjust antenna gain                      │
│                                                                     │
│   Issue: Can't Read Card                                           │
│   ├── Check: Card type                                            │
│   ├── Check: Card placement                                       │
│   ├── Check: Antenna tuning                                       │
│   └── Fix: Try different card, reposition card                    │
│                                                                     │
│   Issue: Intermittent Reading                                      │
│   ├── Check: Power stability                                      │
│   ├── Check: EMI interference                                     │
│   ├── Check: Antenna connections                                  │
│   └── Fix: Shield cables, use ferrite bead                        │
│                                                                     │
│   Diagnostic Code:                                                 │
│   ─────────────────────────────────────────────────────────────────│
│   void diagnoseRFID() {                                           │
│       if (rfid.PCD_PerformSelfTest()) {                           │
│           Serial.println("✓ RFID reader self-test passed");      │
│           if (rfid.isNewCardPresent()) {                          │
│               Serial.println("✓ Card present");                  │
│               if (rfid.readCardSerial()) {                        │
│                   String uid = rfid.getUID();                    │
│                   Serial.print("UID: ");                          │
│                   Serial.println(uid);                            │
│               }                                                   │
│           } else {                                                │
│               Serial.println("No card detected");                │
│           }                                                       │
│       } else {                                                    │
│           Serial.println("✗ RFID reader self-test failed");      │
│       }                                                           │
│   }                                                               │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## Communication Issues

### CAN Bus Issues

```
┌─────────────────────────────────────────────────────────────────────┐
│                    CAN BUS TROUBLESHOOTING                         │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Issue: No Communication                                          │
│   ├── Check: Termination resistors (120Ω)                         │
│   ├── Check: CAN_H/CAN_L wiring                                   │
│   ├── Check: Baud rate (500kbps)                                  │
│   └── Fix: Verify termination, check wiring                       │
│                                                                     │
│   Issue: Error Frames                                              │
│   ├── Check: Bus load                                             │
│   ├── Check: Wiring quality                                       │
│   ├── Check: Node IDs                                             │
│   └── Fix: Reduce bus load, improve wiring                        │
│                                                                     │
│   Issue: No Messages Received                                      │
│   ├── Check: Filter settings                                      │
│   ├── Check: Message IDs                                          │
│   ├── Check: DLC                                                  │
│   └── Fix: Configure filters, verify IDs                          │
│                                                                     │
│   Diagnostic Code:                                                 │
│   ─────────────────────────────────────────────────────────────────│
│   void diagnoseCAN() {                                            │
│       uint8_t status = can.readStatus();                          │
│       if (status == 0) {                                          │
│           Serial.println("✓ CAN bus OK");                        │
│           Serial.print("Error count: ");                          │
│           Serial.println(can.getErrorCount());                   │
│       } else {                                                    │
│           Serial.println("✗ CAN bus error");                     │
│           Serial.print("Status: 0x");                             │
│           Serial.println(status, HEX);                           │
│       }                                                           │
│   }                                                               │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### LoRa Issues

```
┌─────────────────────────────────────────────────────────────────────┐
│                    LORA TROUBLESHOOTING                            │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Issue: No Communication                                          │
│   ├── Check: Frequency (868/915MHz)                               │
│   ├── Check: SPI connections                                      │
│   ├── Check: Antenna                                              │
│   └── Fix: Check frequency, verify antenna                        │
│                                                                     │
│   Issue: Short Range                                               │
│   ├── Check: Spreading factor                                     │
│   ├── Check: TX power                                             │
│   ├── Check: Antenna quality                                      │
│   └── Fix: Increase SF, max power, better antenna                 │
│                                                                     │
│   Issue: Packet Loss                                               │
│   ├── Check: Interference                                         │
│   ├── Check: SNR/RSSI                                            │
│   ├── Check: Bandwidth                                            │
│   └── Fix: Change frequency, reduce BW                           │
│                                                                     │
│   Diagnostic Code:                                                 │
│   ─────────────────────────────────────────────────────────────────│
│   void diagnoseLoRa() {                                           │
│       if (lora.begin(868E6)) {                                    │
│           Serial.println("✓ LoRa initialized");                 │
│           Serial.print("RSSI: ");                                │
│           Serial.println(lora.getRSSI());                        │
│           Serial.print("SNR: ");                                 │
│           Serial.println(lora.getSNR());                         │
│       } else {                                                    │
│           Serial.println("✗ LoRa initialization failed");        │
│       }                                                           │
│   }                                                               │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### GSM Issues

```
┌─────────────────────────────────────────────────────────────────────┐
│                    GSM TROUBLESHOOTING                             │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Issue: No Network                                                │
│   ├── Check: SIM card                                             │
│   ├── Check: Antenna                                              │
│   ├── Check: Signal strength                                      │
│   └── Fix: Insert SIM, connect antenna, move to better area       │
│                                                                     │
│   Issue: No Response to AT Commands                                │
│   ├── Check: Power (5V with capacitor)                            │
│   ├── Check: UART connections (D7/D8)                             │
│   ├── Check: Baud rate (9600)                                     │
│   └── Fix: Check power, verify wiring                             │
│                                                                     │
│   Issue: Can't Send SMS                                            │
│   ├── Check: SMS format                                           │
│   ├── Check: Network registration                                 │
│   ├── Check: Balance (SIM)                                        │
│   └── Fix: Set SMS format, check credit                           │
│                                                                     │
│   Diagnostic Code:                                                 │
│   ─────────────────────────────────────────────────────────────────│
│   void diagnoseGSM() {                                            │
│       if (gsm.sendAT("AT")) {                                     │
│           Serial.println("✓ GSM responding");                    │
│           String signal = gsm.getSignalQuality();                 │
│           Serial.print("Signal: ");                               │
│           Serial.println(signal);                                 │
│       } else {                                                    │
│           Serial.println("✗ GSM not responding");                │
│           Serial.println("Check power and connections");         │
│       }                                                           │
│   }                                                               │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## Power Issues

### Power Supply Problems

```
┌─────────────────────────────────────────────────────────────────────┐
│                    POWER SUPPLY ISSUES                             │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Issue: System Not Powering On                                    │
│   ├── Check: Power supply connection                              │
│   ├── Check: Voltage regulator                                    │
│   ├── Check: Short circuits                                       │
│   └── Fix: Verify power supply, check for shorts                  │
│                                                                     │
│   Issue: Intermittent Resets                                       │
│   ├── Check: Power stability                                      │
│   ├── Check: Current draw                                         │
│   ├── Check: Brown-out protection                                 │
│   └── Fix: Upgrade power supply, add capacitor                    │
│                                                                     │
│   Issue: Noisy Power                                               │
│   ├── Check: Filtering capacitors                                 │
│   ├── Check: Grounding                                            │
│   ├── Check: Load spikes                                          │
│   └── Fix: Add capacitors, improve grounding                      │
│                                                                     │
│   Diagnostic Code:                                                 │
│   ─────────────────────────────────────────────────────────────────│
│   void diagnosePower() {                                          │
│       float v5 = readVoltage(A0);                                 │
│       float v3 = readVoltage(A1);                                 │
│       float current = readCurrent(A2);                            │
│                                                                    │
│       Serial.print("5V: ");                                       │
│       Serial.print(v5);                                           │
│       Serial.println("V " + String(abs(v5-5.0)<0.1 ? "✓" : "✗"));│
│                                                                    │
│       Serial.print("3.3V: ");                                     │
│       Serial.print(v3);                                           │
│       Serial.println("V " + String(abs(v3-3.3)<0.1 ? "✓" : "✗"));│
│                                                                    │
│       Serial.print("Current: ");                                  │
│       Serial.print(current * 1000);                               │
│       Serial.println("mA");                                       │
│   }                                                               │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## Performance Issues

### Memory Issues

```cpp
/*
 * Memory Diagnostic
 */

void diagnoseMemory() {
    Serial.println("\n=== MEMORY DIAGNOSTIC ===\n");
    
    // Check free RAM
    int freeRam = freeMemory();
    Serial.print("Free RAM: ");
    Serial.print(freeRam);
    Serial.println(" bytes");
    
    if (freeRam < 100) {
        Serial.println("⚠ LOW MEMORY WARNING!");
        Serial.println("Optimization suggestions:");
        Serial.println("  - Use PROGMEM for constant strings");
        Serial.println("  - Reduce global variables");
        Serial.println("  - Use smaller data types");
    }
    
    // Check stack usage
    extern int __heap_start, *__brkval;
    int stackUsage = (int)&__heap_start - (int)__brkval;
    Serial.print("Stack usage: ");
    Serial.print(stackUsage);
    Serial.println(" bytes");
    
    // Check heap
    if (__brkval != 0) {
        int heapSize = (int)__brkval - (int)&__heap_start;
        Serial.print("Heap size: ");
        Serial.print(heapSize);
        Serial.println(" bytes");
    }
}

int freeMemory() {
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
```

### Speed Issues

```cpp
/*
 * Performance Diagnostic
 */

void diagnosePerformance() {
    Serial.println("\n=== PERFORMANCE DIAGNOSTIC ===\n");
    
    // 1. Loop Speed Test
    Serial.println("1. Loop Speed Test...");
    unsigned long start = micros();
    for (int i = 0; i < 1000; i++) {
        // Empty loop
        asm volatile("nop");
    }
    unsigned long duration = micros() - start;
    float speed = 1000.0 / duration;
    Serial.print("   Loop speed: ");
    Serial.print(speed);
    Serial.println(" kHz");
    
    // 2. ADC Read Speed
    Serial.println("2. ADC Read Speed...");
    start = micros();
    for (int i = 0; i < 100; i++) {
        analogRead(A0);
    }
    duration = micros() - start;
    float adcSpeed = 100000.0 / duration;
    Serial.print("   ADC speed: ");
    Serial.print(adcSpeed);
    Serial.println(" reads/s");
    
    // 3. I2C Read Speed
    Serial.println("3. I2C Read Speed...");
    start = micros();
    for (int i = 0; i < 10; i++) {
        Wire.requestFrom(0x29, 2);
        while (Wire.available()) {
            Wire.read();
        }
    }
    duration = micros() - start;
    float i2cSpeed = 10000.0 / duration;
    Serial.print("   I2C speed: ");
    Serial.print(i2cSpeed);
    Serial.println(" reads/s");
}
```

---

## Error Codes

### Error Code Reference

```
┌─────────────────────────────────────────────────────────────────────┐
│                    ERROR CODE REFERENCE                            │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Code  │  Error                  │  Description                   │
│   ──────┼─────────────────────────┼────────────────────────────────│
│   0x00  │  SUCCESS                │  Operation completed           │
│   0x01  │  TIMEOUT                │  Operation timed out           │
│   0x02  │  INIT_FAILED            │  Initialization failed         │
│   0x03  │  READ_FAILED            │  Read operation failed         │
│   0x04  │  WRITE_FAILED           │  Write operation failed        │
│   0x05  │  DEVICE_NOT_FOUND       │  Device not detected           │
│   0x06  │  BUS_ERROR              │  Bus communication error       │
│   0x07  │  CRC_ERROR              │  CRC check failed              │
│   0x08  │  PARSE_ERROR            │  Data parsing failed           │
│   0x09  │  CONFIG_ERROR           │  Configuration error           │
│   0x0A  │  MEMORY_ERROR           │  Memory allocation error       │
│   0x0B  │  POWER_ERROR            │  Power supply error            │
│   0x0C  │  SENSOR_ERROR           │  Sensor error                  │
│   0x0D  │  COMMUNICATION_ERROR    │  Communication error           │
│   0x0E  │  TIMING_ERROR           │  Timing error                  │
│   0x0F  │  UNKNOWN_ERROR          │  Unknown error                 │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### Error Code Handler

```cpp
/*
 * Error Code Handler
 */

void handleError(uint8_t errorCode, const String& module, const String& details) {
    Serial.println("╔═══════════════════════════════════════════════╗");
    Serial.println("║     ERROR REPORT                             ║");
    Serial.println("╚═══════════════════════════════════════════════╝");
    Serial.print("Module: ");
    Serial.println(module);
    Serial.print("Error: 0x");
    Serial.println(errorCode, HEX);
    Serial.print("Details: ");
    Serial.println(details);
    
    switch(errorCode) {
        case 0x01:
            Serial.println("Solution: Increase timeout or check device");
            break;
        case 0x02:
            Serial.println("Solution: Check power, wiring, and device");
            break;
        case 0x03:
            Serial.println("Solution: Verify device communication");
            break;
        case 0x05:
            Serial.println("Solution: Check device connection and address");
            break;
        case 0x06:
            Serial.println("Solution: Check bus wiring and termination");
            break;
        case 0x07:
            Serial.println("Solution: Check data integrity");
            break;
        case 0x0B:
            Serial.println("Solution: Check power supply connections");
            break;
        default:
            Serial.println("Solution: Unknown error");
    }
    
    // Trigger error LED pattern
    blinkErrorCode((ErrorCode)errorCode);
}
```

---

## Diagnostic Tools

### Built-in Diagnostic Functions

```cpp
/*
 * Complete Diagnostic Suite
 */

void runFullDiagnostic() {
    Serial.println("╔═══════════════════════════════════════════════╗");
    Serial.println("║     FULL DIAGNOSTIC SUITE                    ║");
    Serial.println("╚═══════════════════════════════════════════════╝");
    
    // 1. System Diagnostic
    Serial.println("\n[1/8] System Diagnostic...");
    systemHealthCheck();
    
    // 2. Power Diagnostic
    Serial.println("\n[2/8] Power Diagnostic...");
    diagnosePower();
    
    // 3. Memory Diagnostic
    Serial.println("\n[3/8] Memory Diagnostic...");
    diagnoseMemory();
    
    // 4. Performance Diagnostic
    Serial.println("\n[4/8] Performance Diagnostic...");
    diagnosePerformance();
    
    // 5. Sensor Diagnostic
    Serial.println("\n[5/8] Sensor Diagnostic...");
    diagnoseAllSensors();
    
    // 6. Communication Diagnostic
    Serial.println("\n[6/8] Communication Diagnostic...");
    diagnoseAllCommunications();
    
    // 7. Error Log
    Serial.println("\n[7/8] Error Log...");
    printErrorLog();
    
    // 8. Summary
    Serial.println("\n[8/8] Summary...");
    printDiagnosticSummary();
}

void printDiagnosticSummary() {
    Serial.println("\n╔═══════════════════════════════════════════════╗");
    Serial.println("║     DIAGNOSTIC SUMMARY                       ║");
    Serial.println("╚═══════════════════════════════════════════════╝");
    
    // Count passed/failed tests
    int passed = 0, failed = 0;
    // ... test results
    
    Serial.println("Status: " + String(failed == 0 ? "✅ ALL OK" : "⚠ SOME ISSUES"));
    Serial.println("Passed: " + String(passed));
    Serial.println("Failed: " + String(failed));
}
```

---

## Recovery Procedures

### Emergency Recovery

```cpp
/*
 * Emergency Recovery Procedures
 */

void emergencyRecovery() {
    Serial.println("⚠ EMERGENCY RECOVERY MODE ⚠");
    
    // 1. Save current state
    saveSystemState();
    
    // 2. Reset all modules
    resetAllModules();
    
    // 3. Clear error states
    clearErrorStates();
    
    // 4. Re-initialize system
    systemManager.begin();
    
    // 5. Run basic tests
    if (runBasicTests()) {
        Serial.println("✓ Recovery successful");
    } else {
        Serial.println("✗ Recovery failed");
        // Enter factory reset
        factoryReset();
    }
}

void factoryReset() {
    Serial.println("🔄 FACTORY RESET");
    
    // 1. Clear all calibration data
    clearAllCalibrations();
    
    // 2. Reset configuration
    loadDefaultConfig();
    
    // 3. Clear error log
    clearErrorLog();
    
    // 4. Reset EEPROM
    resetEEPROM();
    
    // 5. Reboot
    Serial.println("Rebooting in 5 seconds...");
    delay(5000);
    reboot();
}

void reboot() {
    // Software reset
    asm volatile ("jmp 0");
}
```

---

