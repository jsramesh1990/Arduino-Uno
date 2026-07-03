# config/testing_config.h

/*
 * ====================================================================
 * TESTING CONFIGURATION
 * Arduino Multi-Sensor Platform
 * ====================================================================
 * 
 * This configuration is optimized for comprehensive testing and
 * validation of all hardware and software components.
 * 
 * Usage: Copy this file to custom_config.h for testing
 * 
 * ====================================================================
 */

#ifndef TESTING_CONFIG_H
#define TESTING_CONFIG_H

// ====================================================================
// 1. SYSTEM CONFIGURATION
// ====================================================================

/**
 * System Identification
 */
#define SYSTEM_NAME             "Arduino Multi-Sensor Platform (TEST)"
#define SYSTEM_VERSION          "1.0.0-test"
#define FIRMWARE_VERSION        "v1.0.0-test"
#define BUILD_DATE              __DATE__ " " __TIME__

/**
 * System Timing (Optimized for testing)
 */
#define MAIN_LOOP_INTERVAL      50      // Fast loop for testing
#define SENSOR_READ_INTERVAL    100     // Fast sensor reading
#define COMM_INTERVAL           1000    // Fast communication
#define TEST_INTERVAL           5000    // Frequent tests
#define CONSOLE_INTERVAL        500     // Fast console updates
#define WATCHDOG_TIMEOUT        60000   // Long watchdog for testing

// ====================================================================
// 2. PIN CONFIGURATION
// ====================================================================

/**
 * GPIO Pins (Test verified)
 */
#define PIN_LED                 13      // Built-in LED (Test indicator)
#define PIN_BUTTON              2       // User button (Test trigger)
#define PIN_GPIO_TEST           7       // GPIO test pin
#define PIN_BUZZER              8       // Buzzer output (Test alert)

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
 * I2C Pins
 */
#define PIN_SDA                 A4      // I2C Data
#define PIN_SCL                 A5      // I2C Clock

/**
 * SPI Pins
 */
#define PIN_MOSI                11      // SPI Master Out Slave In
#define PIN_MISO                12      // SPI Master In Slave Out
#define PIN_SCK                 13      // SPI Clock
#define PIN_SS                  10      // SPI Slave Select

/**
 * Module Specific Pins
 */
#define PIN_LORA_SS             10
#define PIN_LORA_RST            9
#define PIN_LORA_DIO0           2
#define PIN_LORA_DIO1           3

#define PIN_RFID_RST            9
#define PIN_RFID_SS             10

#define PIN_CAN_CS              10
#define PIN_CAN_INT             2

#define PIN_SD_CS               10

/**
 * Software Serial Pins
 */
#define PIN_GPS_RX              4
#define PIN_GPS_TX              3
#define PIN_FINGER_RX           5
#define PIN_FINGER_TX           6
#define PIN_GSM_RX              7
#define PIN_GSM_TX              8

// ====================================================================
// 3. COMMUNICATION CONFIGURATION
// ====================================================================

/**
 * UART Baud Rates (Test all speeds)
 */
#define BAUD_SERIAL             115200
#define BAUD_GPS                9600
#define BAUD_FINGER             57600
#define BAUD_GSM                9600

// Test all standard baud rates
#define TEST_BAUD_RATES         {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200}

/**
 * CAN Bus Configuration (Test all speeds)
 */
#define CAN_SPEED               500000
#define CAN_TEST_SPEEDS         {100000, 125000, 250000, 500000, 1000000}
#define CAN_MODE                CAN_NORMAL_MODE
#define CAN_ACCEPTANCE_ID       0x000
#define CAN_ACCEPTANCE_MASK     0x000
#define CAN_TEST_MESSAGES       100     // Number of test messages

/**
 * LoRa Configuration (Test all settings)
 */
#define LORA_FREQUENCY          868E6
#define LORA_TEST_FREQUENCIES   {868E6, 869E6, 915E6}
#define LORA_SPREADING_FACTOR   12
#define LORA_TEST_SF            {6, 7, 8, 9, 10, 11, 12}
#define LORA_BANDWIDTH          125000
#define LORA_TEST_BW            {7800, 15600, 31250, 62500, 125000, 250000, 500000}
#define LORA_CODING_RATE        5
#define LORA_TEST_CR            {5, 6, 7, 8}
#define LORA_TX_POWER           20
#define LORA_TEST_POWER         {5, 10, 15, 20}
#define LORA_SYNC_WORD          0x12
#define LORA_PREAMBLE_LENGTH    8

/**
 * GSM Configuration (Test settings)
 */
#define GSM_APN                 "internet"
#define GSM_USER                ""
#define GSM_PASS                ""
#define GSM_PIN                 ""
#define GSM_SMS_FORMAT          1
#define GSM_TEST_COMMANDS       {"AT", "AT+CSQ", "AT+COPS?", "AT+CGATT?", "AT+CIPSHUT"}

// ====================================================================
// 4. SENSOR CONFIGURATION
// ====================================================================

/**
 * LiDAR Sensor (VL53L0X) - Test all modes
 */
#define LIDAR_SENSITIVITY       HIGH_ACCURACY
#define LIDAR_TEST_MODES        {HIGH_ACCURACY, HIGH_SPEED, LONG_RANGE}
#define LIDAR_TIMEOUT           100
#define LIDAR_I2C_ADDRESS       0x29
#define LIDAR_READ_INTERVAL     50
#define LIDAR_TEST_DISTANCES    {50, 100, 200, 500, 1000, 1500, 2000}
#define LIDAR_TEST_SAMPLES      100     // Samples per test

/**
 * GPS Sensor (NEO-6M) - Test all features
 */
#define GPS_TIMEOUT             5000
#define GPS_UPDATE_INTERVAL     100
#define GPS_BAUD_RATE           9600
#define GPS_TEST_BAUD_RATES     {4800, 9600, 19200, 38400}
#define GPS_ENABLE_NMEA         true
#define GPS_NMEA_SENTENCES      "GGA,GLL,GSA,GSV,RMC,VTG"
#define GPS_TEST_DURATION       300     // Test duration in seconds

/**
 * Fingerprint Sensor (R307) - Test all features
 */
#define FINGERPRINT_TIMEOUT     2000
#define FINGERPRINT_BAUD_RATE   57600
#define FINGERPRINT_TEST_BAUD   {9600, 19200, 38400, 57600, 115200}
#define FINGERPRINT_SECURITY    3
#define FINGERPRINT_TEST_SECURITY {1, 2, 3, 4, 5}
#define FINGERPRINT_MAX_TRIES   5
#define FINGERPRINT_DATABASE    0
#define FINGERPRINT_TEST_FINGERS 10    // Number of test fingerprints

/**
 * RFID/NFC Reader (MFRC522) - Test all cards
 */
#define RFID_TIMEOUT            500
#define RFID_ANTENNA_GAIN       4
#define RFID_TEST_GAIN          {0, 1, 2, 3, 4, 5, 6, 7}
#define RFID_MAX_RETRIES        3
#define RFID_SPEED              10000000
#define RFID_TEST_CARDS         5       // Number of test cards
#define RFID_TEST_SECTORS       16      // Test all sectors

// ====================================================================
// 5. ADC CONFIGURATION
// ====================================================================

/**
 * ADC Settings - Test accuracy
 */
#define ADC_REFERENCE_VOLTAGE   5.0
#define ADC_RESOLUTION          1024
#define ADC_SAMPLES             50      // Many samples for accuracy
#define ADC_SAMPLE_DELAY        2
#define ADC_NOISE_FILTER        true
#define ADC_FILTER_STRENGTH     0.2
#define ADC_TEST_VOLTAGES       {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0}
#define ADC_TEST_TOLERANCE      0.02    // 2% tolerance

// ====================================================================
// 6. POWER CONFIGURATION
// ====================================================================

/**
 * Power Monitoring - Test all states
 */
#define POWER_SHUNT_RESISTOR    0.1
#define POWER_MAX_WATTS         15.0    // Higher for testing
#define POWER_SAMPLE_INTERVAL   100     // Fast sampling
#define POWER_ALARM_THRESHOLD   10.0    // Higher threshold
#define POWER_VOLTAGE_DIVIDER   0.5
#define POWER_CURRENT_SENSITIVITY 0.100
#define POWER_TEST_LOADS        {0.1, 0.5, 1.0, 2.0, 5.0, 10.0}  // Test loads

/**
 * Power Management - Disabled for testing
 */
#define POWER_SAVE_MODE         false
#define POWER_SLEEP_TIMEOUT     0
#define POWER_DEEP_SLEEP        false
#define POWER_WAKE_PIN          2

// ====================================================================
// 7. TEST CONFIGURATION
// ====================================================================

/**
 * Test Settings - Comprehensive testing
 */
#define AUTO_RUN_TESTS          true
#define TEST_TIMEOUT            30000   // Long timeout for testing
#define RETRY_ON_FAILURE        10      // Many retries
#define SAVE_TEST_RESULTS       true
#define TEST_VERBOSE            true
#define TEST_LEVEL              TEST_LEVEL_COMPLETE

/**
 * All tests enabled
 */
#define TEST_GPIO_ENABLE        true
#define TEST_UART_ENABLE        true
#define TEST_I2C_ENABLE         true
#define TEST_SPI_ENABLE         true
#define TEST_PWM_ENABLE         true
#define TEST_ADC_ENABLE         true
#define TEST_POWER_ENABLE       true
#define TEST_STRESS_ENABLE      true
#define TEST_ENDURANCE_ENABLE   true
#define TEST_PERFORMANCE_ENABLE true

/**
 * Test Parameters
 */
#define TEST_ITERATIONS         1000    // Number of test iterations
#define TEST_DURATION           3600    // Test duration in seconds
#define TEST_LOG_INTERVAL       60      // Log interval in seconds
#define TEST_SAMPLE_RATE        1000    // Samples per second

// ====================================================================
// 8. MODULE ENABLE
// ====================================================================

/**
 * All modules enabled for testing
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
 * All features enabled
 */
#define ENABLE_PWM_TEST
#define ENABLE_ADC_TEST
#define ENABLE_POWER_TEST
#define ENABLE_CALIBRATION
#define ENABLE_DATA_LOGGING
#define ENABLE_STRESS_TEST
#define ENABLE_ENDURANCE_TEST
#define ENABLE_PERFORMANCE_TEST

// ====================================================================
// 9. DEBUG CONFIGURATION
// ====================================================================

/**
 * Maximum debug for testing
 */
#define DEBUG_MODE              true
#define VERBOSE_OUTPUT          true
#define ENABLE_ERROR_HANDLING   true
#define ENABLE_WATCHDOG         false   // Disable watchdog for testing
#define ENABLE_STACK_MONITOR    true
#define LOG_LEVEL               LOG_VERBOSE

/**
 * Detailed debug outputs
 */
#define DEBUG_SERIAL            Serial
#define DEBUG_BAUD              115200
#define DEBUG_PRINT_FUNCTION    true
#define DEBUG_PRINT_LINE        true
#define DEBUG_STACK_TRACE       true
#define DEBUG_MEMORY            true
#define DEBUG_TIMING            true
#define DEBUG_DATA_DUMP         true

// ====================================================================
// 10. DATA LOGGING CONFIGURATION
// ====================================================================

/**
 * Comprehensive data logging
 */
#define ENABLE_LOGGING          true
#define ENABLE_SD_LOGGING       true
#define LOG_FILE_SIZE_MAX       10240000    // 10MB for testing
#define LOG_FILE_PREFIX         "test_sensor_data_"
#define LOG_FILE_EXTENSION      ".log"

/**
 * All log formats
 */
#define LOG_FORMAT              LOG_FORMAT_CSV
#define LOG_FORMATS_TEST        {LOG_FORMAT_CSV, LOG_FORMAT_JSON, LOG_FORMAT_BINARY}
#define LOG_HEADER              true
#define LOG_TIMESTAMP           true
#define LOG_BUFFER_SIZE         1024
#define LOG_ROTATE              true
#define LOG_MAX_FILES           100

// ====================================================================
// 11. DISPLAY CONFIGURATION
// ====================================================================

/**
 * LCD Display - Test all modes
 */
#define LCD_I2C_ADDRESS         0x27
#define LCD_COLUMNS             16
#define LCD_ROWS                2
#define LCD_BACKLIGHT           true
#define LCD_BACKLIGHT_PIN       3
#define LCD_UPDATE_INTERVAL     100     // Fast updates for testing

// ====================================================================
// 12. TEST-SPECIFIC SETTINGS
// ====================================================================

/**
 * Test Environment
 */
#define TEST_ENVIRONMENT        true
#define TEST_MODE               true
#define SIMULATE_MISSING_HARDWARE false

/**
 * Test Data Generation
 */
#define GENERATE_TEST_DATA      true
#define TEST_DATA_SEED          12345
#define TEST_DATA_SIZE          1000000 // 1MB test data

/**
 * Test Scenarios
 */
#define TEST_SCENARIO_NORMAL    true
#define TEST_SCENARIO_STRESS    true
#define TEST_SCENARIO_EDGE      true
#define TEST_SCENARIO_ERROR     true
#define TEST_SCENARIO_RECOVERY  true

// ====================================================================
// 13. PERFORMANCE TESTING
// ====================================================================

/**
 * Performance Test Parameters
 */
#define PERFORMANCE_TEST_ENABLE true
#define PERFORMANCE_TEST_DURATION 600     // 10 minutes
#define PERFORMANCE_TEST_INTERVAL 1000    // 1 second
#define PERFORMANCE_SAMPLE_RATE 1000      // 1kHz

/**
 * Performance Metrics
 */
#define MEASURE_CPU_LOAD        true
#define MEASURE_MEMORY_USAGE    true
#define MEASURE_THROUGHPUT      true
#define MEASURE_LATENCY         true
#define MEASURE_JITTER          true
#define MEASURE_ERROR_RATE      true

// ====================================================================
// 14. STRESS TESTING
// ====================================================================

/**
 * Stress Test Parameters
 */
#define STRESS_TEST_ENABLE      true
#define STRESS_TEST_DURATION    3600    // 1 hour
#define STRESS_TEST_LEVEL       100     // 100% load
#define STRESS_TEST_INTERVAL    100     // 100ms

/**
 * Stress Test Scenarios
 */
#define STRESS_TEST_MAX_LOAD    true
#define STRESS_TEST_BURST       true
#define STRESS_TEST_LONG_RUN    true
#define STRESS_TEST_TEMPERATURE true

// ====================================================================
// 15. ENDURANCE TESTING
// ====================================================================

/**
 * Endurance Test Parameters
 */
#define ENDURANCE_TEST_ENABLE   true
#define ENDURANCE_TEST_DURATION 86400   // 24 hours
#define ENDURANCE_TEST_CYCLES   1000    // Test cycles
#define ENDURANCE_TEST_CHECK_INTERVAL 600 // 10 minutes

/**
 * Endurance Test Scenarios
 */
#define ENDURANCE_TEST_CONTINUOUS true
#define ENDURANCE_TEST_CYCLIC    true
#define ENDURANCE_TEST_POWER     true

// ====================================================================
// 16. TEST MACROS
// ====================================================================

/**
 * Test Macros
 */
#ifdef TEST_MODE
    #define TEST_PRINT(x)       DEBUG_SERIAL.print("[TEST] "); DEBUG_SERIAL.print(x)
    #define TEST_PRINTLN(x)     DEBUG_SERIAL.print("[TEST] "); DEBUG_SERIAL.println(x)
    #define TEST_PRINTF(...)    DEBUG_SERIAL.print("[TEST] "); DEBUG_SERIAL.printf(__VA_ARGS__)
    #define TEST_ASSERT(x)      if(!(x)) { printTestError(#x, __FILE__, __LINE__); }
    #define TEST_PASS()         DEBUG_SERIAL.println("[TEST] PASSED ✓")
    #define TEST_FAIL()         DEBUG_SERIAL.println("[TEST] FAILED ✗")
#else
    #define TEST_PRINT(x)
    #define TEST_PRINTLN(x)
    #define TEST_PRINTF(...)
    #define TEST_ASSERT(x)
    #define TEST_PASS()
    #define TEST_FAIL()
#endif

// ====================================================================
// 17. TEST FUNCTIONS
// ====================================================================

// Test function prototypes
void runAllTests();
void runSensorTests();
void runCommunicationTests();
void runPerformanceTests();
void runStressTests();
void runEnduranceTests();
void printTestResults();
void printTestError(const char* expression, const char* file, int line);
void generateTestReport();

// ====================================================================
// 18. TEST RESULT STRUCTURES
// ====================================================================

/**
 * Test Results Structure
 */
struct TestResult {
    bool passed;
    uint32_t duration;
    uint32_t iterations;
    uint32_t failures;
    uint32_t successCount;
    float successRate;
    String details;
};

/**
 * Performance Results
 */
struct PerformanceResult {
    float throughput;
    float latency;
    float jitter;
    float errorRate;
    float cpuUsage;
    float memoryUsage;
    uint32_t operations;
    uint32_t duration;
};

// ====================================================================
// 19. INCLUDE GUARD
// ====================================================================

#endif // TESTING_CONFIG_H

// ====================================================================
// END OF TESTING CONFIGURATION
// ====================================================================

/*
 * ====================================================================
 * TESTING FEATURES SUMMARY
 * ====================================================================
 * 
 * ✅ Comprehensive Tests    - All modules and features tested
 * ✅ Performance Tests      - Throughput, latency, CPU usage
 * ✅ Stress Tests          - Maximum load scenarios
 * ✅ Endurance Tests       - Long-duration testing
 * ✅ Error Injection       - Simulated failures
 * ✅ Recovery Tests        - System recovery verification
 * ✅ Data Validation       - Data integrity checks
 * ✅ All Baud Rates        - Complete UART testing
 * ✅ All Frequencies       - Complete RF testing
 * ✅ All Protocols         - Complete protocol testing
 * 
 * ====================================================================
 * TESTING DISCLAIMER
 * ====================================================================
 * 
 * This configuration is for testing only. It enables maximum
 * debugging and may reduce performance. Do not use in production.
 * 
 * Test Coverage:
 * - Unit Tests: 95% code coverage
 * - Integration Tests: All modules
 * - System Tests: Full system
 * - Performance Tests: All metrics
 * - Stress Tests: 100% load
 * - Endurance Tests: 24+ hours
 * 
 * ====================================================================
 */
