# docs/guides/setup_guide.md

# Setup Guide
## Arduino Multi-Sensor Platform

---

## 📚 Table of Contents
1. [Introduction](#introduction)
2. [Prerequisites](#prerequisites)
3. [Hardware Setup](#hardware-setup)
4. [Software Installation](#software-installation)
5. [Project Configuration](#project-configuration)
6. [Building the Project](#building-the-project)
7. [Uploading Firmware](#uploading-firmware)
8. [Testing the Setup](#testing-the-setup)
9. [First Run](#first-run)
10. [Troubleshooting](#troubleshooting)

---

## Introduction

This guide will walk you through the complete setup process for the Arduino Multi-Sensor Platform. It covers everything from gathering components to running your first test.

### What You'll Build

```
┌─────────────────────────────────────────────────────────────────────┐
│                    SYSTEM OVERVIEW                                 │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   ┌──────────────────────────────────────────────────────────┐    │
│   │   Arduino Multi-Sensor Platform                         │    │
│   │                                                         │    │
│   │   Sensors:                                              │    │
│   │   ● LiDAR (VL53L0X) - Distance Measurement              │    │
│   │   ● GPS (NEO-6M) - Location Tracking                   │    │
│   │   ● Fingerprint (R307) - Biometric Auth                 │    │
│   │   ● RFID/NFC (MFRC522) - Card Reading                   │    │
│   │                                                         │    │
│   │   Communication:                                        │    │
│   │   ● CAN Bus (MCP2515) - Vehicle Network                 │    │
│   │   ● LoRa (SX1278) - Long Range Radio                    │    │
│   │   ● GSM (SIM800L) - Cellular Communication              │    │
│   │                                                         │    │
│   │   Testing Features:                                     │    │
│   │   ● GPIO Testing                                       │    │
│   │   ● UART/I2C/SPI Testing                               │    │
│   │   ● PWM Testing                                        │    │
│   │   ● ADC Accuracy Testing                               │    │
│   │   ● Power Consumption Testing                          │    │
│   └──────────────────────────────────────────────────────────┘    │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## Prerequisites

### Hardware Requirements

```
┌─────────────────────────────────────────────────────────────────────┐
│                    HARDWARE PREREQUISITES                           │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Required Components:                                             │
│   ─────────────────────────────────────────────────────────────────│
│   ● Arduino Uno (ATmega328P)                                       │
│   ● USB Cable (Type A to Type B)                                   │
│   ● 12V 2A Power Supply                                           │
│   ● Breadboard and Jumper Wires                                    │
│   ● Multimeter (for testing)                                       │
│                                                                     │
│   Optional but Recommended:                                        │
│   ─────────────────────────────────────────────────────────────────│
│   ● Oscilloscope (for signal analysis)                             │
│   ● Logic Analyzer (for protocol debugging)                        │
│   ● Soldering Iron (for permanent setup)                           │
│   ● 3D Printer (for enclosure)                                     │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### Software Requirements

```
┌─────────────────────────────────────────────────────────────────────┐
│                    SOFTWARE PREREQUISITES                           │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Required Software:                                               │
│   ─────────────────────────────────────────────────────────────────│
│   ● Arduino CLI 0.20+ or Arduino IDE 2.0+                         │
│   ● Python 3.8+                                                   │
│   ● Git 2.30+                                                     │
│   ● Screen/Putty (Serial Terminal)                                │
│                                                                     │
│   Python Packages:                                                 │
│   ─────────────────────────────────────────────────────────────────│
│   $ pip install pyserial matplotlib numpy pandas                   │
│   $ pip install jinja2 markdown pytest pytest-html                │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## Hardware Setup

### Step 1: Prepare Your Workspace

```
┌─────────────────────────────────────────────────────────────────────┐
│                    WORKSPACE PREPARATION                            │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   □ Clean, flat work surface                                       │
│   □ Good lighting                                                  │
│   □ ESD protection (grounded mat or wrist strap)                   │
│   □ Organized components                                           │
│   □ Easy access to tools                                           │
│   □ Ventilation (if soldering)                                     │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### Step 2: Connect Power Supply

```cpp
/*
 * Power Supply Connection
 */

// Power Distribution Setup
void setupPowerSupply() {
    // 1. Connect 12V DC power supply to Arduino VIN
    // 2. Verify voltage with multimeter
    // 3. Connect 5V to breadboard power rail
    // 4. Connect GND to breadboard ground rail
    
    // Pin connections:
    // VIN -> 12V DC Positive
    // GND -> 12V DC Negative
    // 5V -> Breadboard Positive Rail
    // GND -> Breadboard Negative Rail
    
    Serial.println("Power Supply Connected");
    Serial.println("Voltage: 12V DC");
    Serial.println("Current Capacity: 2A");
}
```

### Step 3: Connect Modules

#### 3.1 LiDAR Sensor (VL53L0X)

```cpp
/*
 * LiDAR Sensor Connection
 */

void connectLiDAR() {
    // VL53L0X Connections
    // ------------------
    // VIN  -> 3.3V
    // GND  -> GND
    // SCL  -> A5
    // SDA  -> A4
    // XSHUT -> D8 (optional)
    
    Serial.println("LiDAR Connected");
    Serial.println("I2C Address: 0x29");
}
```

#### 3.2 GPS Module (NEO-6M)

```cpp
/*
 * GPS Module Connection
 */

void connectGPS() {
    // NEO-6M Connections
    // -----------------
    // VCC  -> 5V
    // GND  -> GND
    // TX   -> D4
    // RX   -> D3
    
    Serial.println("GPS Connected");
    Serial.println("Baud Rate: 9600");
}
```

#### 3.3 Fingerprint Sensor (R307)

```cpp
/*
 * Fingerprint Sensor Connection
 */

void connectFingerprint() {
    // R307 Connections
    // ---------------
    // VCC  -> 5V
    // GND  -> GND
    // TX   -> D5
    // RX   -> D6
    
    Serial.println("Fingerprint Sensor Connected");
    Serial.println("Baud Rate: 57600");
}
```

#### 3.4 RFID/NFC Reader (MFRC522)

```cpp
/*
 * RFID/NFC Reader Connection
 */

void connectRFID() {
    // MFRC522 Connections
    // ------------------
    // VCC  -> 3.3V
    // GND  -> GND
    // RST  -> D9
    // SDA  -> D10
    // MOSI -> D11
    // MISO -> D12
    // SCK  -> D13
    
    Serial.println("RFID Reader Connected");
    Serial.println("SPI Speed: 10MHz");
}
```

#### 3.5 CAN Bus Module (MCP2515)

```cpp
/*
 * CAN Bus Module Connection
 */

void connectCAN() {
    // MCP2515 Connections
    // ------------------
    // VCC  -> 5V
    // GND  -> GND
    // CS   -> D10
    // SI   -> D11
    // SO   -> D12
    // SCK  -> D13
    // INT  -> D2 (optional)
    
    Serial.println("CAN Bus Connected");
    Serial.println("Speed: 500kbps");
}
```

#### 3.6 LoRa Module (SX1278)

```cpp
/*
 * LoRa Module Connection
 */

void connectLoRa() {
    // SX1278 Connections
    // -----------------
    // VCC  -> 3.3V
    // GND  -> GND
    // NSS  -> D10
    // MOSI -> D11
    // MISO -> D12
    // SCK  -> D13
    // RST  -> D8
    // DIO0 -> D2
    
    Serial.println("LoRa Connected");
    Serial.println("Frequency: 868MHz");
}
```

#### 3.7 GSM Module (SIM800L)

```cpp
/*
 * GSM Module Connection
 */

void connectGSM() {
    // SIM800L Connections
    // ------------------
    // VCC  -> 5V (with 1000uF capacitor)
    // GND  -> GND
    // TX   -> D7
    // RX   -> D8
    // RST  -> D5 (optional)
    // PWR  -> D6 (optional)
    
    Serial.println("GSM Connected");
    Serial.println("Baud Rate: 9600");
}
```

### Step 4: Verify Connections

```cpp
/*
 * Connection Verification
 */

void verifyConnections() {
    Serial.println("\n=== VERIFYING CONNECTIONS ===\n");
    
    // 1. Check Power
    Serial.println("1. Checking Power...");
    float voltage = readVoltage(A0);
    if (voltage > 4.8 && voltage < 5.2) {
        Serial.println("   ✓ 5V rail OK");
    } else {
        Serial.println("   ✗ 5V rail ERROR!");
    }
    
    // 2. Check I2C Bus
    Serial.println("2. Checking I2C Bus...");
    uint8_t devices = scanI2C();
    if (devices > 0) {
        Serial.print("   ✓ ");
        Serial.print(devices);
        Serial.println(" devices found");
    } else {
        Serial.println("   ✗ No I2C devices found!");
    }
    
    // 3. Check SPI Bus
    Serial.println("3. Checking SPI Bus...");
    if (testSPI()) {
        Serial.println("   ✓ SPI bus OK");
    } else {
        Serial.println("   ✗ SPI bus ERROR!");
    }
}
```

---

## Software Installation

### Step 1: Install Arduino CLI

#### Windows
```bash
# Download and install Arduino CLI
cd C:\
mkdir Arduino
cd Arduino
curl -L https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Windows_64bit.exe -o arduino-cli.exe
arduino-cli.exe version
```

#### Linux/Ubuntu
```bash
# Install Arduino CLI
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
sudo mv arduino-cli /usr/local/bin/
arduino-cli version
```

#### macOS
```bash
# Install Arduino CLI
brew install arduino-cli
arduino-cli version
```

### Step 2: Install Required Libraries

```bash
# Install libraries
arduino-cli lib install "Adafruit VL53L0X"
arduino-cli lib install "TinyGPSPlus"
arduino-cli lib install "Adafruit Fingerprint Sensor Library"
arduino-cli lib install "MFRC522"
arduino-cli lib install "MCP2515"
arduino-cli lib install "LoRa"
```

### Step 3: Clone the Repository

```bash
# Clone the project repository
git clone https://github.com/yourusername/Arduino-Multi-Sensor-Platform.git
cd Arduino-Multi-Sensor-Platform

# Checkout stable version
git checkout v1.0.0
```

### Step 4: Setup Python Environment

```bash
# Create virtual environment
python3 -m venv venv

# Activate virtual environment
# Windows:
venv\Scripts\activate
# Linux/macOS:
source venv/bin/activate

# Install Python dependencies
pip install -r requirements.txt
```

---

## Project Configuration

### Step 1: Configure Pin Mapping

Edit `src/main/config.h`:

```cpp
/*
 * Configuration File
 * Modify these settings for your setup
 */

// ====================== PIN CONFIGURATION ======================
// GPIO Pins
#define PIN_LED               13
#define PIN_BUTTON            2
#define PIN_GPIO_TEST         7

// PWM Pins
#define PIN_PWM_OUT           9
#define PIN_PWM_IN            10

// ADC Pins
#define PIN_ADC_INPUT         A0
#define PIN_ADC_TEST          A1
#define PIN_POWER_MONITOR     A2

// Communication Pins
#define PIN_SDA               A4
#define PIN_SCL               A5
#define PIN_MOSI              11
#define PIN_MISO              12
#define PIN_SCK               13
#define PIN_SS                10

// Module Specific Pins
#define PIN_LORA_SS           10
#define PIN_LORA_RST          9
#define PIN_LORA_DIO0         2
#define PIN_RFID_RST          9
#define PIN_RFID_SS           10
#define PIN_CAN_CS            10

// Software Serial Pins
#define PIN_GPS_RX            4
#define PIN_GPS_TX            3
#define PIN_FINGER_RX         5
#define PIN_FINGER_TX         6
#define PIN_GSM_RX            7
#define PIN_GSM_TX            8

// ====================== COMMUNICATION CONFIGURATION ======================
// UART Baud Rates
#define BAUD_GPS              9600
#define BAUD_FINGER           57600
#define BAUD_GSM              9600
#define BAUD_SERIAL           115200

// CAN Bus Configuration
#define CAN_SPEED             500000  // 500 kbps

// LoRa Configuration
#define LORA_FREQUENCY        868E6   // 868 MHz (EU) / 915E6 (US)
#define LORA_SPREADING_FACTOR 12
#define LORA_TX_POWER         20
#define LORA_CODING_RATE      5
```

### Step 2: Configure Module Settings

```cpp
/*
 * Module-Specific Configuration
 * Enable/disable modules as needed
 */

// ====================== MODULE ENABLING ======================
// Uncomment to enable modules
#define ENABLE_LIDAR
#define ENABLE_GPS
#define ENABLE_FINGERPRINT
#define ENABLE_RFID
#define ENABLE_CAN
#define ENABLE_LORA
#define ENABLE_GSM
#define ENABLE_PWM_TEST
#define ENABLE_ADC_TEST
#define ENABLE_POWER_TEST

// ====================== TEST CONFIGURATION ======================
#define AUTO_RUN_TESTS        true
#define TEST_TIMEOUT          5000
#define RETRY_ON_FAILURE      3
#define SAVE_TEST_RESULTS     true

// ====================== DEBUG CONFIGURATION ======================
#define DEBUG_MODE            true
#define VERBOSE_OUTPUT        true
#define ENABLE_ERROR_HANDLING true
```

---

## Building the Project

### Step 1: Build Using Arduino CLI

```bash
# Navigate to project directory
cd Arduino-Multi-Sensor-Platform

# Build the project
arduino-cli compile \
    --fqbn arduino:avr:uno \
    --build-path build \
    --output-dir output \
    src/main/Arduino_Multi_Sensor.ino

# Build with debug flags
arduino-cli compile \
    --fqbn arduino:avr:uno \
    --build-path build \
    --output-dir output \
    --build-property build.extra_flags=-DDEBUG_MODE \
    src/main/Arduino_Multi_Sensor.ino
```

### Step 2: Build Using Custom Script

```bash
# Make build script executable
chmod +x scripts/build.sh

# Build the project
./scripts/build.sh -c

# Build with upload
./scripts/build.sh -u

# Build, upload, and run tests
./scripts/build.sh -a
```

### Step 3: Build Using PlatformIO

```bash
# Install PlatformIO (if not installed)
pip install platformio

# Build the project
pio run

# Build with verbose output
pio run -v

# Clean build
pio run --target clean
```

---

## Uploading Firmware

### Step 1: Connect Arduino

```bash
# Find your Arduino port
# Linux:
ls /dev/ttyUSB*
# macOS:
ls /dev/tty.usb*
# Windows:
# Check Device Manager for COM port
```

### Step 2: Upload Firmware

#### Using Arduino CLI

```bash
# Upload to Arduino
arduino-cli upload \
    -p /dev/ttyUSB0 \
    --fqbn arduino:avr:uno \
    src/main/Arduino_Multi_Sensor.ino

# Upload with verification
arduino-cli upload \
    -p /dev/ttyUSB0 \
    --fqbn arduino:avr:uno \
    --verify \
    src/main/Arduino_Multi_Sensor.ino
```

#### Using Custom Script

```bash
# Upload using script
./scripts/build.sh -u

# Upload and monitor
./scripts/build.sh -um
```

#### Using PlatformIO

```bash
# Upload firmware
pio run --target upload

# Upload and monitor
pio run --target upload --target monitor
```

### Step 3: Verify Upload

```bash
# Open serial monitor
arduino-cli monitor -p /dev/ttyUSB0 -c baudrate=115200

# Or use screen
screen /dev/ttyUSB0 115200
```

---

## Testing the Setup

### Step 1: Run Basic Tests

```cpp
/*
 * Basic Hardware Test
 */

void runBasicTests() {
    Serial.println("\n=== RUNNING BASIC TESTS ===\n");
    
    // 1. LED Blink Test
    Serial.println("1. LED Blink Test...");
    for (int i = 0; i < 5; i++) {
        digitalWrite(PIN_LED, HIGH);
        delay(200);
        digitalWrite(PIN_LED, LOW);
        delay(200);
    }
    Serial.println("   ✓ LED test complete");
    
    // 2. Button Test
    Serial.println("2. Button Test...");
    Serial.println("   Press the button...");
    while (digitalRead(PIN_BUTTON) == HIGH) {
        delay(10);
    }
    Serial.println("   ✓ Button pressed");
    
    // 3. Serial Communication Test
    Serial.println("3. Serial Communication Test...");
    Serial.println("   Sending test data...");
    Serial.println("   ✓ Serial communication OK");
}
```

### Step 2: Run Module Tests

```bash
# Run all module tests
python3 scripts/test_runner.py -p /dev/ttyUSB0 -t all

# Run specific tests
python3 scripts/test_runner.py -p /dev/ttyUSB0 -t gpio
python3 scripts/test_runner.py -p /dev/ttyUSB0 -t uart
python3 scripts/test_runner.py -p /dev/ttyUSB0 -t i2c
python3 scripts/test_runner.py -p /dev/ttyUSB0 -t spi
```

### Step 3: Check Output

```bash
# Expected output after successful setup:
#
# ╔═══════════════════════════════════════════════╗
# ║     ARDUINO MULTI-SENSOR PLATFORM             ║
# ╚═══════════════════════════════════════════════╝
# 
# System Initialization Started
# All Modules Initialized
# System Ready
# 
# ========== TEST CYCLE #1 ==========
# Timestamp: 00:00:05
# 
# --- GPIO Test ---
# GPIO Output Test: PASS
# Button State: RELEASED
# 
# --- UART Communication Test ---
# GPS UART: OK
# GSM UART: OK
# Fingerprint UART: OK
# 
# --- I2C Communication Test ---
# I2C device found at address 0x29
# I2C device found at address 0x28
# Total I2C devices: 2
# 
# --- SPI Communication Test ---
# CAN SPI: OK
# LoRa SPI: OK
# 
# ✓ All tests passed!
```

---

## First Run

### Step 1: Power Up Sequence

```cpp
/*
 * First Run Sequence
 */

void firstRunSequence() {
    Serial.println("╔═══════════════════════════════════════════════╗");
    Serial.println("║     FIRST RUN SEQUENCE                       ║");
    Serial.println("╚═══════════════════════════════════════════════╝");
    
    // 1. Initialize System
    Serial.println("\n[1/5] Initializing System...");
    systemManager.begin();
    
    // 2. Initialize Modules
    Serial.println("\n[2/5] Initializing Modules...");
    sensorManager.begin();
    commManager.begin();
    
    // 3. Run Initial Tests
    Serial.println("\n[3/5] Running Initial Tests...");
    TestResults results = testManager.runAllTests();
    
    // 4. Calibrate Sensors
    Serial.println("\n[4/5] Calibrating Sensors...");
    sensorManager.calibrateAll();
    
    // 5. Start Normal Operation
    Serial.println("\n[5/5] Starting Normal Operation...");
    Serial.println("✓ System Ready!");
    
    // Display Status
    displaySystemStatus();
}
```

### Step 2: Monitor Output

```bash
# Open serial monitor
arduino-cli monitor -p /dev/ttyUSB0 -c baudrate=115200

# Expected output:
#
# ╔═══════════════════════════════════════════════╗
# ║         SYSTEM STATUS DASHBOARD              ║
# ╠═══════════════════════════════════════════════╣
# ║ Timestamp: 00:00:10                          ║
# ╠═══════════════════════════════════════════════╣
# ║ SENSORS:                                     ║
# ║  LiDAR    : ONLINE                           ║
# ║  GPS      : SEARCHING                        ║
# ║  Finger   : ONLINE                           ║
# ║  RFID     : ONLINE                           ║
# ╠═══════════════════════════════════════════════╣
# ║ COMMUNICATION:                               ║
# ║  CAN      : OK                               ║
# ║  LoRa     : OK                               ║
# ║  GSM      : OK                               ║
# ╠═══════════════════════════════════════════════╣
# ║ POWER: 1.74W                                 ║
# ╚═══════════════════════════════════════════════╝
```

---

## Troubleshooting

### Common Setup Issues

```
┌─────────────────────────────────────────────────────────────────────┐
│                    TROUBLESHOOTING GUIDE                           │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Issue 1: Arduino Not Detected                                    │
│   ├── Check: USB cable connection                                  │
│   ├── Check: Driver installation                                   │
│   ├── Check: Port permissions                                      │
│   └── Fix: sudo usermod -a -G dialout $USER                       │
│                                                                     │
│   Issue 2: Compilation Fails                                       │
│   ├── Check: Library installation                                  │
│   ├── Check: Board selection                                      │
│   ├── Check: Syntax errors                                        │
│   └── Fix: arduino-cli lib update-index                           │
│                                                                     │
│   Issue 3: Upload Fails                                            │
│   ├── Check: Port selection                                       │
│   ├── Check: Bootloader status                                    │
│   ├── Check: Power supply                                         │
│   └── Fix: Press reset during upload                               │
│                                                                     │
│   Issue 4: No Serial Output                                        │
│   ├── Check: Baud rate (115200)                                   │
│   ├── Check: Serial connection                                    │
│   ├── Check: Code in setup()                                      │
│   └── Fix: Serial.begin(115200) in setup                          │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### Quick Fix Commands

```bash
# Fix permission issues
sudo chmod a+rw /dev/ttyUSB0
sudo usermod -a -G dialout $USER

# Reset Arduino
arduino-cli reset -p /dev/ttyUSB0

# Force upload
arduino-cli upload --force -p /dev/ttyUSB0 --fqbn arduino:avr:uno sketch.ino

# Burn bootloader
arduino-cli burn-bootloader -p /dev/ttyUSB0 --fqbn arduino:avr:uno

# Clean build
arduino-cli compile --clean --fqbn arduino:avr:uno sketch.ino

# Update libraries
arduino-cli lib update-index
arduino-cli lib upgrade-all
```

---

