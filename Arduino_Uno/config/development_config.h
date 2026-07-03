# config/development_config.h

/*
 * ====================================================================
 * DEVELOPMENT CONFIGURATION
 * Arduino Multi-Sensor Platform
 * ====================================================================
 * 
 * This configuration is optimized for development and debugging.
 * All features are enabled with verbose output for maximum visibility.
 * 
 * Usage: Copy this file to custom_config.h for development work
 * 
 * ====================================================================
 */

#ifndef DEVELOPMENT_CONFIG_H
#define DEVELOPMENT_CONFIG_H

// ====================================================================
// 1. SYSTEM CONFIGURATION
// ====================================================================

#define SYSTEM_NAME             "Arduino Multi-Sensor Platform (DEV)"
#define SYSTEM_VERSION          "1.0.0-dev"
#define FIRMWARE_VERSION        "v1.0.0-dev"
#define BUILD_DATE              __DATE__ " " __TIME__

// Development Timing (faster for debugging)
#define MAIN_LOOP_INTERVAL      50      // Faster loop for debugging
#define SENSOR_READ_INTERVAL    500     // Faster sensor reading
#define COMM_INTERVAL           2000    // Faster communication
#define TEST_INTERVAL           5000    // More frequent tests
#define CONSOLE_INTERVAL        1000    // Faster console updates
#define WATCHDOG_TIMEOUT        60000   // Longer watchdog for debugging

// ====================================================================
// 2. PIN CONFIGURATION
// ====================================================================

// GPIO Pins
#define PIN_LED                 13
#define PIN_BUTTON              2
#define PIN_GPIO_TEST           7
#define PIN_BUZZER              8

// PWM Pins
#define PIN_PWM_OUT             9
#define PIN_PWM_IN              10

// ADC Pins
#define PIN_ADC_INPUT           A0
#define PIN_ADC_TEST            A1
#define PIN_POWER_MONITOR       A2
#define PIN_CURRENT_SENSE       A3
#define PIN_TEMPERATURE         A4

// I2C Pins
#define PIN_SDA                 A4
#define PIN_SCL                 A5

// SPI Pins
#define PIN_MOSI                11
#define PIN_MISO                12
#define PIN_SCK                 13
#define PIN_SS                  10

// Module Specific Pins
#define PIN_LORA_SS             10
#define PIN_LORA_RST            9
#define PIN_LORA_DIO0           2
#define PIN_LORA_DIO1           3

#define PIN_RFID_RST            9
#define PIN_RFID_SS             10

#define PIN_CAN_CS              10
#define PIN_CAN_INT             2

#define PIN_SD_CS               10

// Software Serial Pins
#define PIN_GPS_RX              4
#define PIN_GPS_TX              3
#define PIN_FINGER_RX           5
#define PIN_FINGER_TX           6
#define PIN_GSM_RX              7
#define PIN_GSM_TX              8

// ====================================================================
// 3. COMMUNICATION CONFIGURATION
// ====================================================================

// UART Baud Rates
#define BAUD_SERIAL             115200
#define BAUD_GPS                9600
#define BAUD_FINGER             57600
#define BAUD_GSM                9600

// CAN Bus Configuration
#define CAN_SPEED               500000
#define CAN_MODE                CAN_NORMAL_MODE
#define CAN_ACCEPTANCE_ID       0x000
#define CAN_ACCEPTANCE_MASK     0x000

// LoRa Configuration
#define LORA_FREQUENCY          868E6
#define LORA_SPREADING_FACTOR   12
#define LORA_BANDWIDTH          125000
#define LORA_CODING_RATE        5
#define LORA_TX_POWER           20
#define LORA_SYNC_WORD          0x12
#define LORA_PREAMBLE_LENGTH    8

// GSM Configuration
#define GSM_APN                 "internet"
#define GSM_USER                ""
#define GSM_PASS                ""
#define GSM_PIN                 ""
#define GSM_SMS_FORMAT          1

// ====================================================================
// 4. SENSOR CONFIGURATION
// ====================================================================

// LiDAR Sensor (VL53L0X)
#define LIDAR_SENSITIVITY       HIGH_ACCURACY
#define LIDAR_TIMEOUT           100
#define LIDAR_I2C_ADDRESS       0x29
#define LIDAR_READ_INTERVAL     100

// GPS Sensor (NEO-6M)
#define GPS_TIMEOUT             5000
#define GPS_UPDATE_INTERVAL     1000
#define GPS_BAUD_RATE           9600
#define GPS_ENABLE_NMEA         true
#define GPS_NMEA_SENTENCES      "GGA,GSA,RMC"

// Fingerprint Sensor (R307)
#define FINGERPRINT_TIMEOUT     2000
#define FINGERPRINT_BAUD_RATE   57600
#define FINGERPRINT_SECURITY    3
#define FINGERPRINT_MAX_TRIES   3
#define FINGERPRINT_DATABASE    0

// RFID/NFC Reader (MFRC522)
#define RFID_TIMEOUT            500
#define RFID_ANTENNA_GAIN       4
#define RFID_MAX_RETRIES        3
#define RFID_SPEED              10000000

// ====================================================================
// 5. ADC CONFIGURATION
// ====================================================================

#define ADC_REFERENCE_VOLTAGE   5.0
#define ADC_RESOLUTION          1024
#define ADC_SAMPLES             20      // More samples for accuracy
#define ADC_SAMPLE_DELAY        5
#define ADC_NOISE_FILTER        true
#define ADC_FILTER_STRENGTH     0.3

// ====================================================================
// 6. POWER CONFIGURATION
// ====================================================================

// Power Monitoring
#define POWER_SHUNT_RESISTOR    0.1
#define POWER_MAX_WATTS         5.0
#define POWER_SAMPLE_INTERVAL   500
#define POWER_ALARM_THRESHOLD   4.5
#define POWER_VOLTAGE_DIVIDER   0.5
#define POWER_CURRENT_SENSITIVITY 0.100

// Power Management (disabled in development)
#define POWER_SAVE_MODE         false
#define POWER_SLEEP_TIMEOUT     0
#define POWER_DEEP_SLEEP        false
#define POWER_WAKE_PIN          2

// ====================================================================
// 7. TEST CONFIGURATION
// ====================================================================

#define AUTO_RUN_TESTS          true
#define TEST_TIMEOUT            10000   // Longer timeout for debugging
#define RETRY_ON_FAILURE        5       // More retries
#define SAVE_TEST_RESULTS       true
#define TEST_VERBOSE            true
#define TEST_LEVEL              TEST_LEVEL_COMPLETE

// Individual Test Enable
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

// All modules enabled for development
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

// All features enabled
#define ENABLE_PWM_TEST
#define ENABLE_ADC_TEST
#define ENABLE_POWER_TEST
#define ENABLE_CALIBRATION
#define ENABLE_DATA_LOGGING

// ====================================================================
// 9. DEBUG CONFIGURATION
// ====================================================================

// Maximum debug output
#define DEBUG_MODE              true
#define VERBOSE_OUTPUT          true
#define ENABLE_ERROR_HANDLING   true
#define ENABLE_WATCHDOG         true
#define ENABLE_STACK_MONITOR    true
#define LOG_LEVEL               LOG_VERBOSE

// Debug Outputs
#define DEBUG_SERIAL            Serial
#define DEBUG_BAUD              115200
#define DEBUG_PRINT_FUNCTION    true
#define DEBUG_PRINT_LINE        true

// Extended debugging
#define DEBUG_STACK_TRACE       true
#define DEBUG_PROFILE           true
#define DEBUG_MEMORY            true
#define DEBUG_TIMING            true

// ====================================================================
// 10. DATA LOGGING CONFIGURATION
// ====================================================================

#define ENABLE_LOGGING          true
#define ENABLE_SD_LOGGING       true
#define LOG_FILE_SIZE_MAX       1024000
#define LOG_FILE_PREFIX         "dev_sensor_data_"
#define LOG_FILE_EXTENSION      ".log"

#define LOG_FORMAT              LOG_FORMAT_CSV
#define LOG_HEADER              true
#define LOG_TIMESTAMP           true
#define LOG_BUFFER_SIZE         512

// ====================================================================
// 11. DISPLAY CONFIGURATION
// ====================================================================

#define LCD_I2C_ADDRESS         0x27
#define LCD_COLUMNS             16
#define LCD_ROWS                2
#define LCD_BACKLIGHT           true
#define LCD_BACKLIGHT_PIN       3
#define LCD_UPDATE_INTERVAL     500

// ====================================================================
// 12. DEVELOPMENT-SPECIFIC SETTINGS
// ====================================================================

// Performance Profiling
#define ENABLE_PROFILING        true
#define PROFILE_INTERVAL        5000    // Profile every 5 seconds

// Simulated Data (for testing without hardware)
#define ENABLE_SIMULATION       false   // Set to true to test without hardware
#define SIMULATION_MODE         false   // If true, generate fake data

// Debugging Helpers
#define DUMP_VARIABLES          true    // Dump important variables
#define DUMP_INTERVAL           10000   // Dump every 10 seconds
#define DUMP_TO_SERIAL          true    // Dump to Serial
#define DUMP_TO_SD              true    // Dump to SD card

// Development Tools
#define ENABLE_COMMAND_INTERFACE true   // Enable serial command interface
#define ENABLE_WEB_INTERFACE    true    // Enable web interface (if supported)
#define ENABLE_TELNET           false   // Enable telnet debugging

// ====================================================================
// 13. ADVANCED DEBUGGING
// ====================================================================

// Memory Debugging
#define MEMORY_DEBUG            true
#define MEMORY_WATERMARK        true    // Track memory high water mark
#define MEMORY_FRAGMENTATION    true    // Track heap fragmentation

// Timing Debugging
#define TIMING_DEBUG            true
#define TIMING_TRACK            true    // Track execution times
#define TIMING_PRINT            true    // Print timing information

// Communication Debugging
#define COMM_DEBUG              true
#define COMM_DUMP_PACKETS       true    // Dump packet contents
#define COMM_DUMP_RAW           true    // Dump raw bytes

// Error Debugging
#define ERROR_DEBUG             true
#define ERROR_STACK_TRACE       true    // Show error stack trace
#define ERROR_CRASH_DUMP        true    // Dump system state on crash

// ====================================================================
// 14. TESTING MODE SETTINGS
// ====================================================================

// Unit Test Settings
#define UNIT_TEST_ENABLE        true
#define UNIT_TEST_AUTO_RUN      true
#define UNIT_TEST_REPORT        true

// Integration Test Settings
#define INTEGRATION_TEST_ENABLE true
#define INTEGRATION_TEST_AUTO   false
#define INTEGRATION_TEST_VERBOSE true

// Regression Test Settings
#define REGRESSION_TEST_ENABLE  true
#define REGRESSION_TEST_AUTO    true
#define REGRESSION_TEST_SAVE    true

// ====================================================================
// 15. DEVELOPMENT MACROS
// ====================================================================

// Debug Print Macros
#ifdef DEBUG_MODE
    #define DEV_PRINT(x)        DEBUG_SERIAL.print(x)
    #define DEV_PRINTLN(x)      DEBUG_SERIAL.println(x)
    #define DEV_PRINTF(...)     DEBUG_SERIAL.printf(__VA_ARGS__)
    #define DEV_PRINT_DUMP(x)   printDump(x)
    #define DEV_PRINT_STACK()   printStackTrace()
    #define DEV_PRINT_MEM()     printMemoryInfo()
    #define DEV_PRINT_TIME()    printTimingInfo()
    #define DEV_ASSERT(x)       if(!(x)) { printAssertError(#x, __FILE__, __LINE__); }
#else
    #define DEV_PRINT(x)
    #define DEV_PRINTLN(x)
    #define DEV_PRINTF(...)
    #define DEV_PRINT_DUMP(x)
    #define DEV_PRINT_STACK()
    #define DEV_PRINT_MEM()
    #define DEV_PRINT_TIME()
    #define DEV_ASSERT(x)
#endif

// ====================================================================
// 16. DEVELOPMENT FUNCTIONS
// ====================================================================

// Function prototypes for debugging
void printDump(const void* data, size_t length);
void printStackTrace();
void printMemoryInfo();
void printTimingInfo();
void printAssertError(const char* expression, const char* file, int line);

// ====================================================================
// 17. INCLUDE GUARD
// ====================================================================

#endif // DEVELOPMENT_CONFIG_H

// ====================================================================
// END OF DEVELOPMENT CONFIGURATION
// ====================================================================

/*
 * ====================================================================
 * DEVELOPMENT FEATURES SUMMARY
 * ====================================================================
 * 
 * ✅ Verbose Output          - All debug messages enabled
 * ✅ Auto Tests              - Tests run automatically on startup
 * ✅ All Modules             - All sensors and modules enabled
 * ✅ Full Logging            - Complete data logging enabled
 * ✅ Memory Monitoring       - Track memory usage and leaks
 * ✅ Timing Analysis         - Profile execution times
 * ✅ Error Stack Trace       - Detailed error information
 * ✅ Command Interface       - Interactive debugging
 * ✅ Profiling               - Performance profiling enabled
 * 
 * ====================================================================
 */
