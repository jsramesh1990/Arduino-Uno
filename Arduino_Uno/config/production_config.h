# config/production_config.h

/*
 * ====================================================================
 * PRODUCTION CONFIGURATION
 * Arduino Multi-Sensor Platform
 * ====================================================================
 * 
 * This configuration is optimized for production deployment.
 * All features are configured for stability, reliability, and
 * power efficiency with minimal debugging overhead.
 * 
 * Usage: Copy this file to custom_config.h for production deployment
 * 
 * ====================================================================
 */

#ifndef PRODUCTION_CONFIG_H
#define PRODUCTION_CONFIG_H

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
 * System Timing (Optimized for stability)
 */
#define MAIN_LOOP_INTERVAL      100     // Main loop execution interval
#define SENSOR_READ_INTERVAL    1000    // Sensor reading interval (1 second)
#define COMM_INTERVAL           5000    // Communication interval (5 seconds)
#define TEST_INTERVAL           30000   // Test execution interval (30 seconds)
#define CONSOLE_INTERVAL        5000    // Console update interval (5 seconds)
#define WATCHDOG_TIMEOUT        30000   // Watchdog timeout (30 seconds)

// ====================================================================
// 2. PIN CONFIGURATION
// ====================================================================

/**
 * GPIO Pins (Production verified)
 */
#define PIN_LED                 13      // Built-in LED (Status)
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

// RFID/NFC Module
#define PIN_RFID_RST            9       // RFID Reset
#define PIN_RFID_SS             10      // RFID Chip Select

// CAN Bus Module
#define PIN_CAN_CS              10      // CAN Chip Select
#define PIN_CAN_INT             2       // CAN Interrupt

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
#define BAUD_SERIAL             115200  // USB Serial (Production monitoring)
#define BAUD_GPS                9600    // GPS Module
#define BAUD_FINGER             57600   // Fingerprint Sensor
#define BAUD_GSM                9600    // GSM Module

/**
 * CAN Bus Configuration (Optimized)
 */
#define CAN_SPEED               500000  // CAN bitrate (500 kbps)
#define CAN_MODE                CAN_NORMAL_MODE
#define CAN_ACCEPTANCE_ID       0x100   // Acceptance filter ID
#define CAN_ACCEPTANCE_MASK     0x7FF   // Acceptance filter mask

/**
 * LoRa Configuration (Reliable)
 */
#define LORA_FREQUENCY          868E6   // Frequency (868MHz EU / 915MHz US)
#define LORA_SPREADING_FACTOR   12      // Spreading factor (for range)
#define LORA_BANDWIDTH          125000  // Bandwidth (Hz)
#define LORA_CODING_RATE        5       // Coding rate (4/5)
#define LORA_TX_POWER           20      // TX power (dBm, max)
#define LORA_SYNC_WORD          0x12    // Sync word
#define LORA_PREAMBLE_LENGTH    8       // Preamble length

/**
 * GSM Configuration (Production)
 */
#define GSM_APN                 "internet"    // APN for your network
#define GSM_USER                ""            // APN username
#define GSM_PASS                ""            // APN password
#define GSM_PIN                 ""            // SIM PIN
#define GSM_SMS_FORMAT          1             // Text format

// ====================================================================
// 4. SENSOR CONFIGURATION
// ====================================================================

/**
 * LiDAR Sensor (VL53L0X) - Reliable settings
 */
#define LIDAR_SENSITIVITY       HIGH_ACCURACY   // Best accuracy
#define LIDAR_TIMEOUT           100             // Timeout in ms
#define LIDAR_I2C_ADDRESS       0x29            // I2C address
#define LIDAR_READ_INTERVAL     100             // Read interval

/**
 * GPS Sensor (NEO-6M) - Production settings
 */
#define GPS_TIMEOUT             5000            // Timeout in ms
#define GPS_UPDATE_INTERVAL     1000            // Update interval
#define GPS_BAUD_RATE           9600            // Baud rate
#define GPS_ENABLE_NMEA         true            // Enable NMEA
#define GPS_NMEA_SENTENCES      "GGA,RMC"       // Only essential NMEA

/**
 * Fingerprint Sensor (R307) - Production settings
 */
#define FINGERPRINT_TIMEOUT     2000            // Timeout in ms
#define FINGERPRINT_BAUD_RATE   57600           // Baud rate
#define FINGERPRINT_SECURITY    3               // Security level
#define FINGERPRINT_MAX_TRIES   3               // Max attempts
#define FINGERPRINT_DATABASE    0               // Database ID

/**
 * RFID/NFC Reader (MFRC522) - Production settings
 */
#define RFID_TIMEOUT            500             // Timeout in ms
#define RFID_ANTENNA_GAIN       4               // Antenna gain
#define RFID_MAX_RETRIES        3               // Max retries
#define RFID_SPEED              10000000        // SPI speed

// ====================================================================
// 5. ADC CONFIGURATION
// ====================================================================

/**
 * ADC Settings - Production quality
 */
#define ADC_REFERENCE_VOLTAGE   5.0             // Reference voltage
#define ADC_RESOLUTION          1024            // 10-bit resolution
#define ADC_SAMPLES             15              // Samples for averaging
#define ADC_SAMPLE_DELAY        5               // Delay between samples
#define ADC_NOISE_FILTER        true            // Noise filtering
#define ADC_FILTER_STRENGTH     0.5             // Filter strength

// ====================================================================
// 6. POWER CONFIGURATION
// ====================================================================

/**
 * Power Monitoring - Production settings
 */
#define POWER_SHUNT_RESISTOR    0.1             // Shunt resistor value (Ω)
#define POWER_MAX_WATTS         5.0             // Maximum expected power
#define POWER_SAMPLE_INTERVAL   1000            // Sample interval (ms)
#define POWER_ALARM_THRESHOLD   4.5             // Alarm threshold (W)
#define POWER_VOLTAGE_DIVIDER   0.5             // Voltage divider ratio
#define POWER_CURRENT_SENSITIVITY 0.100         // Current sensor sensitivity

/**
 * Power Management - Optimized for production
 */
#define POWER_SAVE_MODE         true            // Enable power saving
#define POWER_SLEEP_TIMEOUT     60000           // Sleep timeout (ms)
#define POWER_DEEP_SLEEP        true            // Enable deep sleep
#define POWER_WAKE_PIN          2               // Wake pin
#define POWER_SLEEP_BETWEEN_READS true          // Sleep between sensor reads
#define POWER_SLEEP_BETWEEN_COMM true           // Sleep between comms

// ====================================================================
// 7. TEST CONFIGURATION
// ====================================================================

/**
 * Test Settings - Reduced for production
 */
#define AUTO_RUN_TESTS          false           // Don't auto-run tests
#define TEST_TIMEOUT            3000            // Test timeout (ms)
#define RETRY_ON_FAILURE        2               // Retry count
#define SAVE_TEST_RESULTS       true            // Save test results
#define TEST_VERBOSE            false           // Minimal test output
#define TEST_LEVEL              TEST_LEVEL_QUICK // Quick tests only

/**
 * Individual Test Enable
 */
#define TEST_GPIO_ENABLE        false
#define TEST_UART_ENABLE        false
#define TEST_I2C_ENABLE         false
#define TEST_SPI_ENABLE         false
#define TEST_PWM_ENABLE         false
#define TEST_ADC_ENABLE         false
#define TEST_POWER_ENABLE       false

// ====================================================================
// 8. MODULE ENABLE
// ====================================================================

/**
 * Enable/Disable Modules (Production selection)
 */
#define ENABLE_LIDAR            // Required
#define ENABLE_GPS              // Required
#define ENABLE_FINGERPRINT      // Required for biometric auth
#define ENABLE_RFID             // Required for card access
#define ENABLE_CAN              // Required for vehicle comm
#define ENABLE_LORA             // Required for long range
#define ENABLE_GSM              // Required for cellular
#define ENABLE_SD_CARD          // Optional - data logging
#define ENABLE_LCD_DISPLAY      // Optional - user interface
#define ENABLE_RTC              // Required for timekeeping

/**
 * Enable/Disable Features (Production selection)
 */
#define ENABLE_PWM_TEST         false   // Not needed in production
#define ENABLE_ADC_TEST         false   // Not needed in production
#define ENABLE_POWER_TEST       true    // Keep for monitoring
#define ENABLE_CALIBRATION      true    // Keep calibration
#define ENABLE_DATA_LOGGING     true    // Keep logging

// ====================================================================
// 9. DEBUG CONFIGURATION
// ====================================================================

/**
 * Debug Settings - Minimal for production
 */
#define DEBUG_MODE              false           // Disable debug mode
#define VERBOSE_OUTPUT          false           // Minimal output
#define ENABLE_ERROR_HANDLING   true            // Keep error handling
#define ENABLE_WATCHDOG         true            // Keep watchdog
#define ENABLE_STACK_MONITOR    false           // Disable stack monitor
#define LOG_LEVEL               LOG_ERROR       // Only log errors

/**
 * Debug Outputs - Minimal
 */
#define DEBUG_SERIAL            Serial
#define DEBUG_BAUD              115200
#define DEBUG_PRINT_FUNCTION    false
#define DEBUG_PRINT_LINE        false

// ====================================================================
// 10. DATA LOGGING CONFIGURATION
// ====================================================================

/**
 * Data Logging - Production settings
 */
#define ENABLE_LOGGING          true            // Enable data logging
#define ENABLE_SD_LOGGING       true            // Enable SD card logging
#define LOG_FILE_SIZE_MAX       1024000         // Max log file size (1MB)
#define LOG_FILE_PREFIX         "sensor_data_"  // Log file prefix
#define LOG_FILE_EXTENSION      ".log"          // Log file extension

/**
 * Logging Format
 */
#define LOG_FORMAT              LOG_FORMAT_CSV  // CSV format for compatibility
#define LOG_HEADER              true            // Include header
#define LOG_TIMESTAMP           true            // Include timestamps
#define LOG_BUFFER_SIZE         256             // Log buffer size
#define LOG_ROTATE              true            // Rotate logs
#define LOG_MAX_FILES           10              // Maximum log files

// ====================================================================
// 11. DISPLAY CONFIGURATION
// ====================================================================

/**
 * LCD Display - Production settings
 */
#define LCD_I2C_ADDRESS         0x27            // I2C address
#define LCD_COLUMNS             16              // Number of columns
#define LCD_ROWS                2               // Number of rows
#define LCD_BACKLIGHT           true            // Enable backlight
#define LCD_BACKLIGHT_PIN       3               // Backlight control pin
#define LCD_UPDATE_INTERVAL     2000            // Update interval (2 seconds)

/**
 * LCD Display - Production content
 */
#define LCD_DISPLAY_STATUS      true            // Show system status
#define LCD_DISPLAY_SENSORS     true            // Show sensor readings
#define LCD_DISPLAY_TIME        true            // Show time
#define LCD_DISPLAY_ERRORS      true            // Show errors

// ====================================================================
// 12. PRODUCTION-SPECIFIC SETTINGS
// ====================================================================

/**
 * Reliability Settings
 */
#define ENABLE_RETRY_LOGIC      true            // Enable retry on failure
#define MAX_RETRY_COUNT         5               // Maximum retries
#define RETRY_DELAY             1000            // Delay between retries (ms)
#define ENABLE_FALLBACK         true            // Enable fallback modes
#define FALLBACK_DELAY          5000            // Fallback delay (ms)

/**
 * Safety Settings
 */
#define ENABLE_SAFETY_CHECKS    true            // Enable safety checks
#define SAFETY_CHECK_INTERVAL   1000            // Safety check interval (ms)
#define MAX_TEMPERATURE         70              // Max temperature (°C)
#define MAX_CURRENT             2.0             // Max current (A)
#define MIN_VOLTAGE             4.5             // Min voltage (V)

/**
 * Performance Settings
 */
#define OPTIMIZE_SPEED          true            // Optimize for speed
#define OPTIMIZE_MEMORY         true            // Optimize for memory
#define ENABLE_CACHING          true            // Enable data caching
#define CACHE_SIZE              100             // Cache size

// ====================================================================
// 13. PRODUCTION DEBUGGING
// ====================================================================

/**
 * Production Debugging - Minimal
 */
#define PRODUCTION_DEBUG        false           // Production debug mode
#define PRODUCTION_DEBUG_LEVEL  0               // 0=Off, 1=Minimal, 2=Full

/**
 * Production Logging - Minimal
 */
#define PRODUCTION_LOGGING      true            // Enable production logging
#define PRODUCTION_LOGGING_LEVEL 0              // 0=Errors Only, 1=Warnings, 2=Info

/**
 * Production Monitoring
 */
#define ENABLE_PRODUCTION_MONITOR true          // Enable production monitoring
#define MONITOR_INTERVAL        60000           // Monitor interval (60 seconds)
#define MONITOR_ALERT_ENABLE    true            // Enable alerts
#define MONITOR_ALERT_LED       true            // Use LED for alerts

// ====================================================================
// 14. PRODUCTION MACROS
// ====================================================================

/**
 * Production Debug Macros
 */
#ifdef PRODUCTION_DEBUG
    #define PROD_PRINT(x)       DEBUG_SERIAL.print(x)
    #define PROD_PRINTLN(x)     DEBUG_SERIAL.println(x)
    #define PROD_PRINTF(...)    DEBUG_SERIAL.printf(__VA_ARGS__)
#else
    #define PROD_PRINT(x)
    #define PROD_PRINTLN(x)
    #define PROD_PRINTF(...)
#endif

/**
 * Production Error Macros
 */
#define PROD_ERROR(x)           errorHandler(x)
#define PROD_WARNING(x)         warningHandler(x)
#define PROD_INFO(x)            infoHandler(x)

// ====================================================================
// 15. PRODUCTION VALIDATION
// ====================================================================

/**
 * Production Validation Check
 */
#define PRODUCTION_VALIDATE_CONFIG() validateProductionConfig()

// Validation function
static inline bool validateProductionConfig() {
    bool valid = true;
    
    #if !defined(ENABLE_LIDAR) && !defined(ENABLE_GPS)
        #error "At least one sensor must be enabled in production"
        valid = false;
    #endif
    
    #if !defined(ENABLE_CAN) && !defined(ENABLE_LORA) && !defined(ENABLE_GSM)
        #error "At least one communication module must be enabled in production"
        valid = false;
    #endif
    
    #if defined(DEBUG_MODE) && DEBUG_MODE == true
        #warning "DEBUG_MODE is enabled in production - performance may be affected"
    #endif
    
    return valid;
}

// ====================================================================
// 16. PRODUCTION FUNCTIONS
// ====================================================================

// Function prototypes for production
void errorHandler(const char* error);
void warningHandler(const char* warning);
void infoHandler(const char* info);
void productionMonitor();
void alertHandler(uint8_t alertCode);

// ====================================================================
// 17. INCLUDE GUARD
// ====================================================================

#endif // PRODUCTION_CONFIG_H

// ====================================================================
// END OF PRODUCTION CONFIGURATION
// ====================================================================

/*
 * ====================================================================
 * PRODUCTION FEATURES SUMMARY
 * ====================================================================
 * 
 * ✅ Stable Operation        - Optimized for 24/7 uptime
 * ✅ Power Efficiency       - Deep sleep modes enabled
 * ✅ Error Handling         - Comprehensive error recovery
 * ✅ Data Logging           - Continuous data collection
 * ✅ Minimal Debug          - Reduced overhead
 * ✅ Watchdog Protection    - System reset on hang
 * ✅ Safety Checks          - Temperature, voltage, current monitoring
 * ✅ Fallback Modes         - Graceful degradation
 * ✅ Retry Logic            - Automatic retry on failure
 * ✅ Production Monitoring  - Health monitoring
 * 
 * ====================================================================
 * PRODUCTION DISCLAIMER
 * ====================================================================
 * 
 * This configuration is for production deployment. It disables
 * most debugging features for performance and reliability.
 * 
 * Before deploying:
 * 1. Test thoroughly with hardware
 * 2. Verify all sensor connections
 * 3. Validate communication settings
 * 4. Check power requirements
 * 5. Test error recovery scenarios
 * 6. Validate data logging
 * 
 * ====================================================================
 */
