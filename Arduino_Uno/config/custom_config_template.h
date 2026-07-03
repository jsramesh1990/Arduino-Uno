# config/custom_config_template.h

/*
 * ====================================================================
 * CUSTOM CONFIGURATION TEMPLATE
 * Arduino Multi-Sensor Platform
 * ====================================================================
 * 
 * This template file contains all configurable parameters for the
 * Arduino Multi-Sensor Platform. Copy this file to custom_config.h
 * and modify the settings according to your requirements.
 * 
 * To use: cp custom_config_template.h custom_config.h
 * 
 * ====================================================================
 */

#ifndef CUSTOM_CONFIG_H
#define CUSTOM_CONFIG_H

// ====================================================================
// 1. SYSTEM CONFIGURATION
// ====================================================================

/**
 * System Identification
 */
#define SYSTEM_NAME             "Arduino Multi-Sensor Platform"
#define SYSTEM_VERSION          "1.0.0"
#define FIRMWARE_VERSION        "v1.0.0"
#define BUILD_DATE              __DATE__ " " __TIME__

/**
 * System Timing (in milliseconds)
 */
#define MAIN_LOOP_INTERVAL      100     // Main loop execution interval
#define SENSOR_READ_INTERVAL    1000    // Sensor reading interval (1 second)
#define COMM_INTERVAL           5000    // Communication interval (5 seconds)
#define TEST_INTERVAL           10000   // Test execution interval (10 seconds)
#define CONSOLE_INTERVAL        2000    // Console update interval (2 seconds)
#define WATCHDOG_TIMEOUT        30000   // Watchdog timeout (30 seconds)

// ====================================================================
// 2. PIN CONFIGURATION
// ====================================================================

/**
 * GPIO Pins
 */
#define PIN_LED                 13      // Built-in LED
#define PIN_BUTTON              2       // User button (with pull-up)
#define PIN_GPIO_TEST           7       // GPIO test pin
#define PIN_BUZZER              8       // Buzzer output

/**
 * PWM Pins
 */
#define PIN_PWM_OUT             9       // PWM output pin
#define PIN_PWM_IN              10      // PWM input pin (for feedback)

/**
 * ADC Pins
 */
#define PIN_ADC_INPUT           A0      // ADC test input
#define PIN_ADC_TEST            A1      // ADC test point
#define PIN_POWER_MONITOR       A2      // Power monitoring input
#define PIN_CURRENT_SENSE       A3      // Current sensor input
#define PIN_TEMPERATURE         A4      // Temperature sensor input

/**
 * I2C Pins (Fixed on Arduino Uno)
 */
#define PIN_SDA                 A4      // I2C Data
#define PIN_SCL                 A5      // I2C Clock

/**
 * SPI Pins (Fixed on Arduino Uno)
 */
#define PIN_MOSI                11      // SPI Master Out Slave In
#define PIN_MISO                12      // SPI Master In Slave Out
#define PIN_SCK                 13      // SPI Clock
#define PIN_SS                  10      // SPI Slave Select

/**
 * Module Specific Pins
 */
// LoRa Module
#define PIN_LORA_SS             10      // LoRa Chip Select
#define PIN_LORA_RST            9       // LoRa Reset
#define PIN_LORA_DIO0           2       // LoRa Interrupt 0
#define PIN_LORA_DIO1           3       // LoRa Interrupt 1 (optional)

// RFID/NFC Module
#define PIN_RFID_RST            9       // RFID Reset
#define PIN_RFID_SS             10      // RFID Chip Select

// CAN Bus Module
#define PIN_CAN_CS              10      // CAN Chip Select
#define PIN_CAN_INT             2       // CAN Interrupt (optional)

// SD Card Module
#define PIN_SD_CS               10      // SD Card Chip Select

/**
 * Software Serial Pins
 */
#define PIN_GPS_RX              4       // GPS RX (connect to GPS TX)
#define PIN_GPS_TX              3       // GPS TX (connect to GPS RX)
#define PIN_FINGER_RX           5       // Fingerprint RX (connect to sensor TX)
#define PIN_FINGER_TX           6       // Fingerprint TX (connect to sensor RX)
#define PIN_GSM_RX              7       // GSM RX (connect to module TX)
#define PIN_GSM_TX              8       // GSM TX (connect to module RX)

// ====================================================================
// 3. COMMUNICATION CONFIGURATION
// ====================================================================

/**
 * UART Baud Rates
 */
#define BAUD_SERIAL             115200  // USB Serial
#define BAUD_GPS                9600    // GPS Module
#define BAUD_FINGER             57600   // Fingerprint Sensor
#define BAUD_GSM                9600    // GSM Module

/**
 * CAN Bus Configuration
 */
#define CAN_SPEED               500000  // CAN bitrate (500 kbps)
#define CAN_MODE                CAN_NORMAL_MODE
#define CAN_ACCEPTANCE_ID       0x000   // Acceptance filter ID (0 = accept all)
#define CAN_ACCEPTANCE_MASK     0x000   // Acceptance filter mask

/**
 * LoRa Configuration
 */
#define LORA_FREQUENCY          868E6   // Frequency (868MHz EU / 915MHz US)
#define LORA_SPREADING_FACTOR   12      // Spreading factor (6-12)
#define LORA_BANDWIDTH          125000  // Bandwidth (Hz)
#define LORA_CODING_RATE        5       // Coding rate (5=4/5, 6=4/6, 7=4/7, 8=4/8)
#define LORA_TX_POWER           20      // TX power (dBm, 0-20)
#define LORA_SYNC_WORD          0x12    // Sync word
#define LORA_PREAMBLE_LENGTH    8       // Preamble length

/**
 * GSM Configuration
 */
#define GSM_APN                 "internet"    // APN for your network
#define GSM_USER                ""            // APN username (if required)
#define GSM_PASS                ""            // APN password (if required)
#define GSM_PIN                 ""            // SIM PIN (if required)
#define GSM_SMS_FORMAT          1             // 0=PDU, 1=Text

// ====================================================================
// 4. SENSOR CONFIGURATION
// ====================================================================

/**
 * LiDAR Sensor (VL53L0X)
 */
#define LIDAR_SENSITIVITY       HIGH_ACCURACY   // HIGH_ACCURACY, HIGH_SPEED, LONG_RANGE
#define LIDAR_TIMEOUT           100             // Timeout in ms
#define LIDAR_I2C_ADDRESS       0x29            // I2C address
#define LIDAR_READ_INTERVAL     100             // Read interval in ms

/**
 * GPS Sensor (NEO-6M)
 */
#define GPS_TIMEOUT             5000            // Timeout in ms
#define GPS_UPDATE_INTERVAL     1000            // Update interval in ms
#define GPS_BAUD_RATE           9600            // Baud rate
#define GPS_ENABLE_NMEA         true            // Enable NMEA sentences
#define GPS_NMEA_SENTENCES      "GGA,GSA,RMC"   // NMEA sentence types

/**
 * Fingerprint Sensor (R307)
 */
#define FINGERPRINT_TIMEOUT     2000            // Timeout in ms
#define FINGERPRINT_BAUD_RATE   57600           // Baud rate
#define FINGERPRINT_SECURITY    3               // Security level (1-5)
#define FINGERPRINT_MAX_TRIES   3               // Max authentication attempts
#define FINGERPRINT_DATABASE    0               // Database ID

/**
 * RFID/NFC Reader (MFRC522)
 */
#define RFID_TIMEOUT            500             // Timeout in ms
#define RFID_ANTENNA_GAIN       4               // Antenna gain (0-7)
#define RFID_MAX_RETRIES        3               // Max retry attempts
#define RFID_SPEED              10000000        // SPI speed (Hz)

// ====================================================================
// 5. ADC CONFIGURATION
// ====================================================================

/**
 * ADC Settings
 */
#define ADC_REFERENCE_VOLTAGE   5.0             // Reference voltage (V)
#define ADC_RESOLUTION          1024            // ADC resolution (10-bit)
#define ADC_SAMPLES             10              // Number of samples for averaging
#define ADC_SAMPLE_DELAY        10              // Delay between samples (ms)
#define ADC_NOISE_FILTER        true            // Enable noise filtering
#define ADC_FILTER_STRENGTH     0.5             // Filter strength (0-1)

// ====================================================================
// 6. POWER CONFIGURATION
// ====================================================================

/**
 * Power Monitoring
 */
#define POWER_SHUNT_RESISTOR    0.1             // Shunt resistor value (Ω)
#define POWER_MAX_WATTS         5.0             // Maximum expected power (W)
#define POWER_SAMPLE_INTERVAL   1000            // Sample interval (ms)
#define POWER_ALARM_THRESHOLD   4.5             // Alarm threshold (W)
#define POWER_VOLTAGE_DIVIDER   0.5             // Voltage divider ratio
#define POWER_CURRENT_SENSITIVITY 0.100         // Current sensor sensitivity (V/A)

/**
 * Power Management
 */
#define POWER_SAVE_MODE         true            // Enable power saving
#define POWER_SLEEP_TIMEOUT     60000           // Sleep timeout (ms)
#define POWER_DEEP_SLEEP        true            // Enable deep sleep
#define POWER_WAKE_PIN          2               // Wake pin

// ====================================================================
// 7. TEST CONFIGURATION
// ====================================================================

/**
 * Test Settings
 */
#define AUTO_RUN_TESTS          true            // Auto-run tests on startup
#define TEST_TIMEOUT            5000            // Test timeout (ms)
#define RETRY_ON_FAILURE        3               // Retry count on failure
#define SAVE_TEST_RESULTS       true            // Save test results
#define TEST_VERBOSE            true            // Verbose test output
#define TEST_LEVEL              TEST_LEVEL_COMPLETE  // TEST_LEVEL_QUICK, NORMAL, COMPLETE

/**
 * Individual Test Enable
 */
#define TEST_GPIO_ENABLE        true
#define TEST_UART_ENABLE        true
#define TEST_I2C_ENABLE         true
#define TEST_SPI_ENABLE         true
#define TEST_PWM_ENABLE         true
#define TEST_ADC_ENABLE         true
#define TEST_POWER_ENABLE       true

// ====================================================================
// 8. MODULE ENABLE
// ====================================================================

/**
 * Enable/Disable Modules
 * Comment out to disable a module
 */
#define ENABLE_LIDAR
#define ENABLE_GPS
#define ENABLE_FINGERPRINT
#define ENABLE_RFID
#define ENABLE_CAN
#define ENABLE_LORA
#define ENABLE_GSM
#define ENABLE_SD_CARD
#define ENABLE_LCD_DISPLAY
#define ENABLE_RTC

/**
 * Enable/Disable Features
 */
#define ENABLE_PWM_TEST
#define ENABLE_ADC_TEST
#define ENABLE_POWER_TEST
#define ENABLE_CALIBRATION
#define ENABLE_DATA_LOGGING

// ====================================================================
// 9. DEBUG CONFIGURATION
// ====================================================================

/**
 * Debug Settings
 */
#define DEBUG_MODE              true            // Enable debug mode
#define VERBOSE_OUTPUT          true            // Enable verbose output
#define ENABLE_ERROR_HANDLING   true            // Enable error handling
#define ENABLE_WATCHDOG         true            // Enable watchdog timer
#define ENABLE_STACK_MONITOR    true            // Enable stack monitoring
#define LOG_LEVEL               LOG_DEBUG       // LOG_NONE, ERROR, WARNING, INFO, DEBUG, VERBOSE

/**
 * Debug Outputs
 */
#define DEBUG_SERIAL            Serial          // Debug serial port
#define DEBUG_BAUD              115200          // Debug baud rate
#define DEBUG_PRINT_FUNCTION    true            // Print function names
#define DEBUG_PRINT_LINE        true            // Print line numbers

// ====================================================================
// 10. DATA LOGGING CONFIGURATION
// ====================================================================

/**
 * Data Logging
 */
#define ENABLE_LOGGING          true            // Enable data logging
#define ENABLE_SD_LOGGING       false           // Enable SD card logging
#define LOG_FILE_SIZE_MAX       1024000         // Max log file size (bytes)
#define LOG_FILE_PREFIX         "sensor_data_"  // Log file prefix
#define LOG_FILE_EXTENSION      ".log"          // Log file extension

/**
 * Logging Format
 */
#define LOG_FORMAT              LOG_FORMAT_CSV  // LOG_FORMAT_CSV, JSON, BINARY
#define LOG_HEADER              true            // Include header in log files
#define LOG_TIMESTAMP           true            // Include timestamps
#define LOG_BUFFER_SIZE         256             // Log buffer size

// ====================================================================
// 11. DISPLAY CONFIGURATION
// ====================================================================

/**
 * LCD Display (if enabled)
 */
#define LCD_I2C_ADDRESS         0x27            // I2C address (0x27 or 0x3F)
#define LCD_COLUMNS             16              // Number of columns
#define LCD_ROWS                2               // Number of rows
#define LCD_BACKLIGHT           true            // Enable backlight
#define LCD_BACKLIGHT_PIN       3               // Backlight control pin
#define LCD_UPDATE_INTERVAL     1000            // Update interval (ms)

// ====================================================================
// 12. RTOS CONFIGURATION (if using FreeRTOS)
// ====================================================================

/**
 * RTOS Settings
 */
#define USE_RTOS                false           // Enable FreeRTOS
#define RTOS_STACK_SIZE         128             // Stack size for tasks
#define RTOS_PRIORITY_LOW       1               // Low priority
#define RTOS_PRIORITY_MEDIUM    2               // Medium priority
#define RTOS_PRIORITY_HIGH      3               // High priority

// ====================================================================
// 13. USER CUSTOM SETTINGS
// ====================================================================

/**
 * User-defined settings
 * Add your custom settings here
 */

// Example: Custom sensor thresholds
#define SENSOR_THRESHOLD_LOW    100
#define SENSOR_THRESHOLD_HIGH   2000

// Example: Custom delay values
#define USER_DELAY_SHORT        50
#define USER_DELAY_MEDIUM       500
#define USER_DELAY_LONG         2000

// Example: Custom module settings
#define CUSTOM_BUFFER_SIZE      64
#define CUSTOM_MAX_RETRIES      5

// ====================================================================
// 14. CONDITIONAL COMPILATION
// ====================================================================

/**
 * Arduino Board Type
 */
#define BOARD_TYPE              BOARD_ARDUINO_UNO  // BOARD_ARDUINO_UNO, BOARD_ARDUINO_MEGA, BOARD_ARDUINO_NANO

/**
 * Development Mode
 */
#ifdef DEBUG_MODE
    #define DEBUG_PRINT(x)      DEBUG_SERIAL.print(x)
    #define DEBUG_PRINTLN(x)    DEBUG_SERIAL.println(x)
    #define DEBUG_PRINTF(...)   DEBUG_SERIAL.printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
    #define DEBUG_PRINTF(...)
#endif

// ====================================================================
// 15. INCLUDE GUARD
// ====================================================================

#endif // CUSTOM_CONFIG_H

// ====================================================================
// END OF CONFIGURATION FILE
// ====================================================================

/*
 * ====================================================================
 * CHANGE LOG
 * ====================================================================
 * 
 * Version 1.0.0 (2026-07-03)
 * - Initial release
 * - Complete configuration template
 * - All modules configurable
 * 
 * ====================================================================
 */

```

---

## Configuration Usage Guide

### How to Use Custom Configuration

```cpp
/*
 * Using Custom Configuration
 * Include this in your main sketch
 */

// Include configuration
#include "config/custom_config.h"

// Use configuration values
void setup() {
    Serial.begin(BAUD_SERIAL);
    
    #ifdef ENABLE_LIDAR
        initLiDAR();
    #endif
    
    #ifdef ENABLE_GPS
        initGPS();
    #endif
    
    #if DEBUG_MODE
        Serial.println("Debug mode enabled");
        Serial.print("System: ");
        Serial.println(SYSTEM_NAME);
        Serial.print("Version: ");
        Serial.println(SYSTEM_VERSION);
    #endif
}
```

### Configuration Validation

```cpp
/*
 * Validate Configuration
 */

bool validateConfig() {
    bool valid = true;
    
    #ifdef ENABLE_LIDAR
        #ifndef LIDAR_I2C_ADDRESS
            #error "LIDAR_I2C_ADDRESS not defined"
        #endif
    #endif
    
    #ifdef ENABLE_GPS
        #ifndef GPS_BAUD_RATE
            #error "GPS_BAUD_RATE not defined"
        #endif
    #endif
    
    #if BAUD_SERIAL < 9600 || BAUD_SERIAL > 115200
        #error "BAUD_SERIAL must be between 9600 and 115200"
    #endif
    
    #if ADC_REFERENCE_VOLTAGE < 1.0 || ADC_REFERENCE_VOLTAGE > 5.0
        #error "ADC_REFERENCE_VOLTAGE must be between 1.0 and 5.0"
    #endif
    
    return valid;
}
```

---

## Configuration Templates

### Different Configuration Profiles

```cpp
/*
 * Configuration Profiles
 * Copy to custom_config.h when needed
 */

// ====================================================================
// Profile 1: Development Configuration
// ====================================================================
#define DEBUG_MODE              true
#define VERBOSE_OUTPUT          true
#define AUTO_RUN_TESTS          true
#define LOG_LEVEL               LOG_VERBOSE
#define ENABLE_ALL_MODULES      true

// ====================================================================
// Profile 2: Production Configuration
// ====================================================================
#define DEBUG_MODE              false
#define VERBOSE_OUTPUT          false
#define AUTO_RUN_TESTS          false
#define LOG_LEVEL               LOG_ERROR
#define ENABLE_ONLY_REQUIRED    true
#define POWER_SAVE_MODE         true

// ====================================================================
// Profile 3: Testing Configuration
// ====================================================================
#define DEBUG_MODE              true
#define VERBOSE_OUTPUT          true
#define AUTO_RUN_TESTS          true
#define LOG_LEVEL               LOG_DEBUG
#define TEST_LEVEL              TEST_LEVEL_COMPLETE
#define RETRY_ON_FAILURE        5

// ====================================================================
// Profile 4: Low Power Configuration
// ====================================================================
#define POWER_SAVE_MODE         true
#define POWER_DEEP_SLEEP        true
#define SENSOR_READ_INTERVAL    5000
#define COMM_INTERVAL           30000
#define TEST_INTERVAL           60000
#define ENABLE_LED_INDICATORS   false
```

---

## Quick Configuration Reference

| Parameter | Default | Description |
|-----------|---------|-------------|
| `BAUD_SERIAL` | 115200 | Serial monitor baud rate |
| `LORA_FREQUENCY` | 868E6 | LoRa frequency (EU/US) |
| `CAN_SPEED` | 500000 | CAN bus speed |
| `GPS_BAUD_RATE` | 9600 | GPS module baud rate |
| `FINGERPRINT_BAUD_RATE` | 57600 | Fingerprint baud rate |
| `GSM_APN` | "internet" | GSM network APN |
| `DEBUG_MODE` | true | Enable debugging |
| `AUTO_RUN_TESTS` | true | Auto-test on startup |
| `POWER_SAVE_MODE` | true | Power saving enabled |

---

## Related Documentation

- [Setup Guide](../docs/guides/setup_guide.md)
- [Calibration Guide](../docs/guides/calibration_guide.md)
- [API Documentation](../docs/api/)
- [Hardware Documentation](../docs/hardware/)

---

**Last Updated:** 2026-07-03
**Version:** 1.0.0
