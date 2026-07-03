/*
 * Configuration File for Arduino Multi-Sensor Platform
 * All configurable parameters are defined here
 */

#ifndef CONFIG_H
#define CONFIG_H

// ====================== SYSTEM CONFIGURATION ======================
#define SYSTEM_NAME            "Arduino Multi-Sensor Platform"
#define SYSTEM_VERSION         "1.0.0"
#define FIRMWARE_VERSION       "v1.0.0"
#define BUILD_DATE             __DATE__ " " __TIME__

// ====================== TIMING CONFIGURATION ======================
#define MAIN_LOOP_INTERVAL     100    // ms
#define SENSOR_READ_INTERVAL   1000   // ms (1 second)
#define COMM_INTERVAL          5000   // ms (5 seconds)
#define TEST_INTERVAL          10000  // ms (10 seconds)
#define CONSOLE_INTERVAL       2000   // ms (2 seconds)
#define WATCHDOG_TIMEOUT       30000  // ms (30 seconds)

// ====================== PIN CONFIGURATION ======================
// GPIO Pins
#define PIN_LED               13
#define PIN_BUTTON            2
#define PIN_GPIO_TEST         7
#define PIN_BUZZER            8

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

// ====================== SENSOR CONFIGURATION ======================
// LiDAR
#define LIDAR_SENSITIVITY     HIGH_ACCURACY
#define LIDAR_TIMEOUT         100     // ms

// GPS
#define GPS_TIMEOUT           5000    // ms
#define GPS_UPDATE_INTERVAL   1000    // ms

// Fingerprint
#define FINGERPRINT_TIMEOUT   2000    // ms
#define MAX_FINGERPRINT_TRIES 3

// RFID/NFC
#define RFID_TIMEOUT          500     // ms

// ====================== ADC CONFIGURATION ======================
#define ADC_REFERENCE_VOLTAGE 5.0     // Volts
#define ADC_RESOLUTION        1024    // 10-bit
#define ADC_SAMPLES           10      // Number of samples for averaging
#define ADC_SAMPLE_DELAY      10      // ms between samples

// ====================== POWER CONFIGURATION ======================
#define POWER_SHUNT_RESISTOR  0.1     // Ohms
#define POWER_MAX_WATTS       5.0     // Maximum expected power
#define POWER_SAMPLE_INTERVAL 1000    // ms
#define POWER_ALARM_THRESHOLD 4.5     // Watts

// ====================== DATA LOGGING ======================
#define ENABLE_LOGGING        true
#define LOG_LEVEL             LOG_DEBUG
#define ENABLE_SD_LOGGING     false
#define LOG_FILE_SIZE_MAX     1024000 // 1MB

// ====================== DEBUG CONFIGURATION ======================
#define DEBUG_MODE            true
#define VERBOSE_OUTPUT        true
#define ENABLE_ERROR_HANDLING true
#define ENABLE_WATCHDOG       true

// ====================== TEST CONFIGURATION ======================
#define AUTO_RUN_TESTS        true
#define TEST_TIMEOUT          5000    // ms
#define RETRY_ON_FAILURE      3
#define SAVE_TEST_RESULTS     true

// ====================== CUSTOM MACROS ======================
#define ARRAY_SIZE(x)         (sizeof(x) / sizeof(x[0]))
#define STRINGIFY(x)          #x
#define TOSTRING(x)           STRINGIFY(x)

// ====================== CONDITIONAL COMPILATION ======================
// Comment out modules you don't want to include
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

#endif // CONFIG_H
