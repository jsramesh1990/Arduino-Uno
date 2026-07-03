/*
 * Arduino Multi-Sensor Integration Platform
 * Version: 1.0.0
 * Repository: https://github.com/yourusername/Arduino-Multi-Sensor-Platform
 * 
 * A comprehensive multi-sensor platform for testing and validation
 * of various sensors and communication modules with Arduino Uno.
 */

#include "config.h"
#include "globals.h"
#include "system.h"
#include "sensors/sensors.h"
#include "communication/communication.h"
#include "tests/tests.h"
#include "utilities/utilities.h"
#include "data/DataManager.h"

// System State
SystemState systemState;
TestResults testResults;
SensorData sensorData;
CommunicationData commData;

// System Objects
SystemManager systemManager;
SensorManager sensorManager;
CommunicationManager commManager;
TestManager testManager;
DataManager dataManager;
Logger logger;
Timer systemTimer;

void setup() {
    // Initialize Serial
    Serial.begin(115200);
    delay(1000);
    
    // Initialize System
    systemManager.begin();
    logger.log("System Initialization Started", LOG_INFO);
    
    // Initialize All Modules
    initializeModules();
    
    // Run Initial Tests
    runInitialTests();
    
    // Display Status
    displaySystemStatus();
    
    logger.log("System Ready", LOG_SUCCESS);
}

void loop() {
    systemTimer.update();
    
    // Main Loop Operations
    if (systemTimer.isTime(MAIN_LOOP_INTERVAL)) {
        performMainLoop();
    }
    
    // Sensor Reading Operations
    if (systemTimer.isTime(SENSOR_READ_INTERVAL)) {
        readAllSensors();
    }
    
    // Communication Operations
    if (systemTimer.isTime(COMM_INTERVAL)) {
        sendAllData();
    }
    
    // Test Operations
    if (systemTimer.isTime(TEST_INTERVAL)) {
        runScheduledTests();
    }
    
    // Console Output
    if (systemTimer.isTime(CONSOLE_INTERVAL)) {
        updateConsoleOutput();
    }
    
    // Error Handling
    systemManager.handleErrors();
    
    // Power Management
    systemManager.managePower();
}

void initializeModules() {
    logger.log("Initializing Modules...", LOG_INFO);
    
    // Initialize Sensor Manager
    sensorManager.begin();
    
    // Initialize Communication Manager
    commManager.begin();
    
    // Initialize Test Manager
    testManager.begin();
    
    // Initialize Data Manager
    dataManager.begin();
    
    // Initialize Individual Modules
    sensorManager.initLiDAR();
    sensorManager.initGPS();
    sensorManager.initFingerprint();
    sensorManager.initRFID();
    
    commManager.initCAN();
    commManager.initLoRa();
    commManager.initGSM();
    
    logger.log("All Modules Initialized", LOG_SUCCESS);
}

void runInitialTests() {
    logger.log("Running Initial Tests...", LOG_INFO);
    
    TestResults results = testManager.runAllTests();
    displayResults(results);
    
    if (results.allPassed) {
        logger.log("All Initial Tests Passed", LOG_SUCCESS);
    } else {
        logger.log("Some Tests Failed - Check System", LOG_ERROR);
    }
}

void performMainLoop() {
    // Update System State
    systemState.timestamp = getTimestamp();
    systemState.uptime = millis() / 1000;
    systemState.cycleCount++;
    
    // Check for commands
    if (Serial.available()) {
        processSerialCommand(Serial.readString());
    }
}

void readAllSensors() {
    sensorData = sensorManager.readAllSensors();
    
    // Log sensor data
    logger.logSensorData(sensorData);
    
    // Update system state with sensor data
    systemState.sensorData = sensorData;
}

void sendAllData() {
    commData = commManager.sendAllData(sensorData, testResults);
    
    // Log communication data
    logger.logCommunicationData(commData);
    
    // Update system state with communication data
    systemState.commData = commData;
}

void runScheduledTests() {
    testResults = testManager.runScheduledTests();
    
    if (testResults.hasErrors) {
        logger.log("Scheduled tests detected errors", LOG_WARNING);
    }
}

void updateConsoleOutput() {
    ConsoleOutput::displayDashboard(systemState, sensorData, testResults, commData);
}

void processSerialCommand(String command) {
    CommandProcessor::processCommand(command);
}

void displaySystemStatus() {
    ConsoleOutput::displaySystemInfo(systemManager.getSystemInfo());
}
