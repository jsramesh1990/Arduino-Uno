# docs/api/test_api.md

# Test API Documentation
## Arduino Multi-Sensor Platform

---

## 📚 Table of Contents
1. [Overview](#overview)
2. [Test Manager](#test-manager)
3. [GPIO Test API](#gpio-test-api)
4. [UART Test API](#uart-test-api)
5. [I2C Test API](#i2c-test-api)
6. [SPI Test API](#spi-test-api)
7. [PWM Test API](#pwm-test-api)
8. [ADC Test API](#adc-test-api)
9. [Power Test API](#power-test-api)
10. [Test Results](#test-results)
11. [Examples](#examples)

---

## Overview

The Test API provides a comprehensive testing framework for validating all hardware components and communication protocols in the Multi-Sensor Platform. It includes automated test suites, performance benchmarking, and validation reporting.

### Key Features
- Automated hardware validation
- Communication protocol testing
- Performance benchmarking
- Power consumption analysis
- Comprehensive test reporting
- Error logging and debugging

---

## Test Manager

### Class Definition

```cpp
class TestManager {
public:
    // Constructor & Destructor
    TestManager();
    ~TestManager();
    
    // Initialization
    bool begin();
    void setupTestEnvironment();
    void cleanupTestEnvironment();
    
    // Test Execution
    TestResults runAllTests();
    TestResults runScheduledTests();
    TestResults runQuickTests();
    TestResults runFullTests();
    TestResults runCustomTests(const char** testNames, uint8_t count);
    
    // Individual Tests
    bool testGPIO();
    bool testUART();
    bool testI2C();
    bool testSPI();
    bool testPWM();
    bool testADC();
    bool testPower();
    
    // Performance Tests
    PerformanceResults runPerformanceTest();
    PerformanceResults runBenchmark();
    PerformanceResults runStressTest();
    PerformanceResults runEnduranceTest();
    
    // Configuration
    void setTestTimeout(uint32_t timeout);
    void setTestRetries(uint8_t retries);
    void enableVerboseOutput(bool enable);
    void enableTestLogging(bool enable);
    void setTestLevel(TestLevel level);
    
    // Results
    TestResults getLastResults();
    String getTestReport();
    void saveTestResults();
    void exportTestResults(const String& format);
    
    // Callbacks
    void onTestStart(void (*callback)(const String&));
    void onTestComplete(void (*callback)(const String&, bool));
    void onTestError(void (*callback)(const String&, const String&));
    
private:
    TestResults m_results;
    PerformanceResults m_perfResults;
    bool m_initialized;
    uint32_t m_timeout;
    uint8_t m_retries;
    bool m_verbose;
    bool m_logging;
    TestLevel m_level;
    
    void (*m_testStartCallback)(const String&);
    void (*m_testCompleteCallback)(const String&, bool);
    void (*m_testErrorCallback)(const String&, const String&);
    
    void runGPIO_Test();
    void runUART_Test();
    void runI2C_Test();
    void runSPI_Test();
    void runPWM_Test();
    void runADC_Test();
    void runPower_Test();
    
    bool verifyTestResult(const String& testName, bool result);
    void recordTestFailure(const String& testName, const String& error);
    void updateTestStatistics(bool passed);
};

// Usage Example
TestManager testManager;

void setup() {
    if (testManager.begin()) {
        Serial.println("Test Manager initialized");
        
        // Configure tests
        testManager.setTestTimeout(5000);
        testManager.setTestRetries(3);
        testManager.enableVerboseOutput(true);
        testManager.enableTestLogging(true);
        
        // Set callbacks
        testManager.onTestStart(onTestStart);
        testManager.onTestComplete(onTestComplete);
        testManager.onTestError(onTestError);
    }
}

void loop() {
    // Run all tests
    TestResults results = testManager.runAllTests();
    
    // Display results
    displayTestResults(results);
    
    delay(10000);
}

void onTestStart(const String& testName) {
    Serial.print("Starting test: ");
    Serial.println(testName);
}

void onTestComplete(const String& testName, bool passed) {
    Serial.print("Test ");
    Serial.print(testName);
    Serial.print(": ");
    Serial.println(passed ? "PASSED" : "FAILED");
}

void onTestError(const String& testName, const String& error) {
    Serial.print("Error in test ");
    Serial.print(testName);
    Serial.print(": ");
    Serial.println(error);
}
```

---

## GPIO Test API

### GPIO Testing Functions

```cpp
class GPIOTest {
public:
    // Constructor
    GPIOTest();
    
    // Test Functions
    bool testAllPins();
    bool testDigitalOutput(uint8_t pin);
    bool testDigitalInput(uint8_t pin);
    bool testInterrupt(uint8_t pin);
    bool testPullUp(uint8_t pin);
    bool testPullDown(uint8_t pin);
    
    // Pin State Testing
    bool testPinState(uint8_t pin, uint8_t expectedState);
    bool testPinToggle(uint8_t pin, uint16_t delay_ms = 100);
    bool testPinSpeed(uint8_t pin, uint32_t frequency);
    
    // Performance Testing
    uint32_t measurePinSpeed(uint8_t pin);
    uint16_t measureSwitchingTime(uint8_t pin);
    
    // Advanced Testing
    bool testAllPinsWithLED();
    bool testButtonInputs();
    bool testInterruptHandling();
    
private:
    bool m_verbose;
    uint8_t m_testPins[20];
    uint8_t m_testCount;
    
    void setupPin(uint8_t pin, uint8_t mode);
    void togglePin(uint8_t pin);
    bool readPin(uint8_t pin);
    void writePin(uint8_t pin, bool state);
};

// GPIO Test Implementation Example
bool GPIOTest::testAllPins() {
    bool allPassed = true;
    
    // Test output pins
    for (int i = 0; i < 14; i++) {
        if (i != 0 && i != 1) { // Skip RX/TX
            if (!testDigitalOutput(i)) {
                allPassed = false;
                Serial.print("Pin D");
                Serial.print(i);
                Serial.println(" output test failed");
            }
        }
    }
    
    // Test input pins
    for (int i = A0; i <= A5; i++) {
        if (!testDigitalInput(i)) {
            allPassed = false;
            Serial.print("Pin A");
            Serial.print(i - A0);
            Serial.println(" input test failed");
        }
    }
    
    return allPassed;
}

bool GPIOTest::testDigitalOutput(uint8_t pin) {
    pinMode(pin, OUTPUT);
    
    // Test HIGH
    digitalWrite(pin, HIGH);
    delay(10);
    if (digitalRead(pin) != HIGH) {
        return false;
    }
    
    // Test LOW
    digitalWrite(pin, LOW);
    delay(10);
    if (digitalRead(pin) != LOW) {
        return false;
    }
    
    // Test toggle
    for (int i = 0; i < 10; i++) {
        digitalWrite(pin, !digitalRead(pin));
        delay(1);
    }
    
    return true;
}
```

---

## UART Test API

### UART Communication Testing

```cpp
class UARTTest {
public:
    // Constructor
    UARTTest();
    
    // Test Functions
    bool testHardwareUART();
    bool testSoftwareUART();
    bool testAllUARTs();
    
    // Communication Testing
    bool testUARTLoopback(uint8_t pin, uint32_t baud);
    bool testUARTBaudRate(uint8_t pin, uint32_t baud);
    bool testUARTDataIntegrity(uint8_t pin, uint32_t baud);
    bool testUARTFlowControl(uint8_t pin, uint32_t baud);
    
    // Performance Testing
    float measureUARTThroughput(uint8_t pin, uint32_t baud);
    float measureUARTLatency(uint8_t pin, uint32_t baud);
    uint32_t measureUARTBufferSize(uint8_t pin);
    
    // Advanced Testing
    bool testUARTParity(uint8_t pin, uint32_t baud);
    bool testUARTStopBits(uint8_t pin, uint32_t baud);
    bool testUARTDataBits(uint8_t pin, uint32_t baud);
    bool testUARTMultipoint(uint8_t pin, uint32_t baud);
    
private:
    HardwareSerial* m_hardwareSerial;
    SoftwareSerial* m_softwareSerial;
    bool m_useHardware;
    
    bool sendData(uint8_t pin, const uint8_t* data, uint16_t length);
    bool receiveData(uint8_t pin, uint8_t* buffer, uint16_t length);
    bool compareData(const uint8_t* data1, const uint8_t* data2, uint16_t length);
};

// UART Test Implementation
bool UARTTest::testUARTLoopback(uint8_t pin, uint32_t baud) {
    // Setup software serial for loopback
    SoftwareSerial testSerial(pin, pin); // Same pin for RX and TX (loopback)
    testSerial.begin(baud);
    
    // Test data
    const uint8_t testData[] = "Hello UART Test! 0123456789";
    uint16_t length = sizeof(testData);
    uint8_t buffer[64];
    
    // Send data
    testSerial.write(testData, length);
    delay(10);
    
    // Receive data
    uint16_t received = 0;
    unsigned long start = millis();
    while (received < length && (millis() - start) < 1000) {
        if (testSerial.available()) {
            buffer[received++] = testSerial.read();
        }
    }
    
    // Compare data
    bool success = (received == length);
    if (success) {
        success = compareData(testData, buffer, length);
    }
    
    return success;
}

bool UARTTest::testUARTBaudRate(uint8_t pin, uint32_t baud) {
    // Test multiple baud rates
    const uint32_t baudRates[] = {9600, 19200, 38400, 57600, 115200};
    bool allPassed = true;
    
    for (int i = 0; i < 5; i++) {
        if (!testUARTLoopback(pin, baudRates[i])) {
            Serial.print("Baud rate ");
            Serial.print(baudRates[i]);
            Serial.println(" test failed");
            allPassed = false;
        }
    }
    
    return allPassed;
}
```

---

## I2C Test API

### I2C Communication Testing

```cpp
class I2CTest {
public:
    // Constructor
    I2CTest();
    
    // Test Functions
    bool testI2C();
    bool testI2CBus();
    bool testI2CDevices();
    
    // Device Testing
    bool testI2CDevice(uint8_t address);
    bool testI2CRead(uint8_t address, uint8_t* data, uint8_t length);
    bool testI2CWrite(uint8_t address, const uint8_t* data, uint8_t length);
    bool testI2CCombined(uint8_t address);
    
    // Bus Testing
    bool testI2CSpeed(uint32_t speed);
    bool testI2CTiming();
    bool testI2CPullUps();
    
    // Advanced Testing
    bool testI2CMultimaster();
    bool testI2CClockStretching();
    bool testI2CArbitration();
    bool testI2CDataIntegrity();
    
    // Utility Functions
    uint8_t scanI2CBus();
    String getDeviceName(uint8_t address);
    bool isDeviceConnected(uint8_t address);
    
private:
    TwoWire* m_wire;
    bool m_verbose;
    
    bool sendI2CData(uint8_t address, const uint8_t* data, uint8_t length);
    bool receiveI2CData(uint8_t address, uint8_t* data, uint8_t length);
    bool verifyI2CData(const uint8_t* expected, const uint8_t* actual, uint8_t length);
};

// I2C Test Implementation
bool I2CTest::testI2C() {
    bool allPassed = true;
    
    // Initialize I2C
    Wire.begin();
    Wire.setClock(100000); // Start with 100kHz
    
    // Scan for devices
    uint8_t deviceCount = scanI2CBus();
    if (deviceCount == 0) {
        Serial.println("No I2C devices found!");
        return false;
    }
    
    // Test each device
    for (uint8_t address = 1; address < 127; address++) {
        if (isDeviceConnected(address)) {
            Serial.print("Testing device at 0x");
            Serial.print(address, HEX);
            
            if (testI2CDevice(address)) {
                Serial.println(" - PASSED");
            } else {
                Serial.println(" - FAILED");
                allPassed = false;
            }
        }
    }
    
    // Test different speeds
    const uint32_t speeds[] = {100000, 400000, 1000000};
    for (int i = 0; i < 3; i++) {
        if (!testI2CSpeed(speeds[i])) {
            Serial.print("Speed ");
            Serial.print(speeds[i]);
            Serial.println(" Hz test failed");
            allPassed = false;
        }
    }
    
    return allPassed;
}

uint8_t I2CTest::scanI2CBus() {
    uint8_t deviceCount = 0;
    
    for (uint8_t address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            deviceCount++;
            if (m_verbose) {
                Serial.print("Found device at 0x");
                Serial.println(address, HEX);
            }
        }
    }
    
    return deviceCount;
}
```

---

## SPI Test API

### SPI Communication Testing

```cpp
class SPITest {
public:
    // Constructor
    SPITest();
    
    // Test Functions
    bool testSPI();
    bool testSPIBus();
    bool testSPIDevices();
    
    // Device Testing
    bool testSPIDevice(uint8_t cs_pin);
    bool testSPIRead(uint8_t cs_pin, uint8_t* data, uint8_t length);
    bool testSPIWrite(uint8_t cs_pin, const uint8_t* data, uint8_t length);
    bool testSPITransfer(uint8_t cs_pin, const uint8_t* tx, uint8_t* rx, uint8_t length);
    
    // Bus Testing
    bool testSPISpeed(uint32_t speed);
    bool testSPIMode(uint8_t mode);
    bool testSPIBitOrder(bool msbFirst);
    
    // Advanced Testing
    bool testSPIQueue();
    bool testSPIDMA();
    bool testSPIInterrupt();
    bool testSPIMultiSlave();
    
    // Performance Testing
    float measureSPIThroughput(uint32_t speed);
    uint32_t measureSPILatency(uint32_t speed);
    
private:
    SPIClass* m_spi;
    uint8_t m_csPins[10];
    uint8_t m_csCount;
    bool m_verbose;
    
    bool selectSlave(uint8_t cs_pin);
    void deselectSlave(uint8_t cs_pin);
    bool validateSPIData(const uint8_t* expected, const uint8_t* actual, uint8_t length);
};

// SPI Test Implementation
bool SPITest::testSPI() {
    bool allPassed = true;
    
    // Initialize SPI
    SPI.begin();
    
    // Test different speeds
    const uint32_t speeds[] = {100000, 1000000, 4000000, 8000000};
    for (int i = 0; i < 4; i++) {
        if (!testSPISpeed(speeds[i])) {
            Serial.print("Speed ");
            Serial.print(speeds[i]);
            Serial.println(" Hz test failed");
            allPassed = false;
        }
    }
    
    // Test different modes
    for (uint8_t mode = 0; mode < 4; mode++) {
        if (!testSPIMode(mode)) {
            Serial.print("Mode ");
            Serial.print(mode);
            Serial.println(" test failed");
            allPassed = false;
        }
    }
    
    // Test bit orders
    if (!testSPIBitOrder(true)) {
        Serial.println("MSB First test failed");
        allPassed = false;
    }
    if (!testSPIBitOrder(false)) {
        Serial.println("LSB First test failed");
        allPassed = false;
    }
    
    // Test devices
    for (int i = 0; i < m_csCount; i++) {
        if (!testSPIDevice(m_csPins[i])) {
            Serial.print("Device at CS ");
            Serial.print(m_csPins[i]);
            Serial.println(" test failed");
            allPassed = false;
        }
    }
    
    return allPassed;
}

bool SPITest::testSPISpeed(uint32_t speed) {
    uint8_t tx_data = 0x55;
    uint8_t rx_data = 0x00;
    
    // Set speed
    SPI.beginTransaction(SPISettings(speed, MSBFIRST, SPI_MODE0));
    
    // Test transfer
    rx_data = SPI.transfer(tx_data);
    
    SPI.endTransaction();
    
    // Verify data (loopback)
    return (rx_data == tx_data);
}
```

---

## PWM Test API

### PWM Testing Functions

```cpp
class PWMTest {
public:
    // Constructor
    PWMTest();
    
    // Test Functions
    bool testPWM();
    bool testAllPWMChannels();
    bool testPWMDutyCycle(uint8_t pin);
    bool testPWMFrequency(uint8_t pin);
    bool testPWMResolution(uint8_t pin);
    
    // Performance Testing
    float measurePWMAccuracy(uint8_t pin);
    float measurePWMStability(uint8_t pin);
    float measurePWMPeriod(uint8_t pin);
    
    // Advanced Testing
    bool testPWMSweep(uint8_t pin);
    bool testPWMModulation(uint8_t pin);
    bool testPWMSync(uint8_t pin1, uint8_t pin2);
    bool testPWMInterrupt(uint8_t pin);
    
    // Configuration
    void setPWMPin(uint8_t pin);
    void setPWMFrequency(uint32_t frequency);
    void setPWMResolution(uint8_t bits);
    
private:
    uint8_t m_pwmPins[6];  // Arduino Uno: 3,5,6,9,10,11
    uint8_t m_pwmCount;
    bool m_verbose;
    
    void setupPWMPin(uint8_t pin);
    void setPWMValue(uint8_t pin, uint16_t value);
    uint16_t readPWMValue(uint8_t pin);
    float calculateDutyCycle(uint16_t value, uint16_t maxValue);
};

// PWM Test Implementation
bool PWMTest::testPWM() {
    bool allPassed = true;
    
    // Test each PWM pin
    for (int i = 0; i < m_pwmCount; i++) {
        uint8_t pin = m_pwmPins[i];
        
        Serial.print("Testing PWM pin ");
        Serial.print(pin);
        Serial.print(": ");
        
        if (testPWMDutyCycle(pin)) {
            Serial.println("PASSED");
        } else {
            Serial.println("FAILED");
            allPassed = false;
        }
        
        if (testPWMFrequency(pin)) {
            Serial.println("Frequency test PASSED");
        } else {
            Serial.println("Frequency test FAILED");
            allPassed = false;
        }
    }
    
    return allPassed;
}

bool PWMTest::testPWMDutyCycle(uint8_t pin) {
    bool passed = true;
    
    // Test different duty cycles
    const uint16_t dutyValues[] = {0, 64, 128, 192, 255};
    const float expectedDutyCycles[] = {0, 25, 50, 75, 100};
    
    for (int i = 0; i < 5; i++) {
        analogWrite(pin, dutyValues[i]);
        delay(100);
        
        float measuredDuty = measurePWMValue(pin);
        float expectedDuty = expectedDutyCycles[i];
        float tolerance = 2.0; // 2% tolerance
        
        if (abs(measuredDuty - expectedDuty) > tolerance) {
            Serial.print("Duty cycle ");
            Serial.print(expectedDuty);
            Serial.print("% expected, got ");
            Serial.print(measuredDuty);
            Serial.println("%");
            passed = false;
        }
    }
    
    return passed;
}

float PWMTest::measurePWMValue(uint8_t pin) {
    // Read PWM value using ADC
    // Assumes PWM output is connected to ADC input through RC filter
    int analogValue = analogRead(pin);
    float voltage = (analogValue / 1023.0) * 5.0;
    float dutyCycle = (voltage / 5.0) * 100.0;
    
    return dutyCycle;
}
```

---

## ADC Test API

### ADC Testing Functions

```cpp
class ADCTest {
public:
    // Constructor
    ADCTest();
    
    // Test Functions
    bool testADC();
    bool testAllADCChannels();
    bool testADCAccuracy(uint8_t pin);
    bool testADCLinearity(uint8_t pin);
    bool testADCNoise(uint8_t pin);
    
    // Performance Testing
    float measureADCMaximumSampleRate();
    float measureADCEffectiveResolution();
    float measureADCSNR();
    float measureADCTHD();
    
    // Advanced Testing
    bool testADCDifferential();
    bool testADCTemperature();
    bool testADCAveraging();
    bool testADCInterrupt();
    
    // Calibration
    void calibrateADC();
    void setADCReference(float voltage);
    void setADCPrescaler(uint8_t prescaler);
    
private:
    uint8_t m_adcPins[6];    // A0-A5
    uint8_t m_adcCount;
    bool m_verbose;
    float m_referenceVoltage;
    
    uint16_t readADC(uint8_t pin, uint8_t samples = 10);
    float convertADCToVoltage(uint16_t adcValue);
    float calculateError(float measured, float expected);
};

// ADC Test Implementation
bool ADCTest::testADCAccuracy(uint8_t pin) {
    // Test known voltage levels
    const float testVoltages[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    const float tolerance = 0.02; // 2% tolerance
    bool passed = true;
    
    for (int i = 0; i < 6; i++) {
        // Generate test voltage (requires external voltage source)
        float measured = readADCVoltage(pin);
        float expected = testVoltages[i];
        
        if (abs(measured - expected) > tolerance) {
            Serial.print("ADC accuracy test failed at ");
            Serial.print(expected);
            Serial.print("V: measured ");
            Serial.print(measured);
            Serial.println("V");
            passed = false;
        }
        
        delay(100);
    }
    
    return passed;
}

float ADCTest::measureADCEffectiveResolution() {
    // Measure effective resolution using noise analysis
    const int samples = 1024;
    uint16_t values[samples];
    uint32_t sum = 0;
    
    // Collect samples
    for (int i = 0; i < samples; i++) {
        values[i] = readADC(A0, 1);
        sum += values[i];
        delay(10);
    }
    
    float mean = (float)sum / samples;
    
    // Calculate standard deviation
    float variance = 0;
    for (int i = 0; i < samples; i++) {
        float diff = values[i] - mean;
        variance += diff * diff;
    }
    variance /= samples;
    float stdDev = sqrt(variance);
    
    // Calculate effective resolution
    float effectiveResolution = log2(1024 / stdDev);
    
    return effectiveResolution;
}
```

---

## Power Test API

### Power Consumption Testing

```cpp
class PowerTest {
public:
    // Constructor
    PowerTest();
    
    // Test Functions
    bool testPower();
    bool testPowerConsumption();
    bool testPowerStability();
    bool testPowerEfficiency();
    
    // Power Analysis
    float measureVoltage();
    float measureCurrent();
    float measurePower();
    float measureEnergy();
    
    // Power Profile Testing
    bool testPowerProfile();
    bool testPowerMode(PowerMode mode);
    bool testPowerTransition();
    bool testPowerInterrupt();
    
    // Advanced Testing
    bool testPowerThermal();
    bool testPowerNoise();
    bool testPowerRipple();
    bool testPowerTransient();
    
    // Power Management
    void setPowerThresholds(float voltageMin, float voltageMax, float currentMax);
    void enablePowerMonitoring(bool enable);
    void setPowerSampleRate(uint16_t rate);
    
private:
    uint8_t m_voltagePin;
    uint8_t m_currentPin;
    float m_voltageThresholdMin;
    float m_voltageThresholdMax;
    float m_currentThresholdMax;
    bool m_monitoringEnabled;
    uint16_t m_sampleRate;
    
    float readVoltage();
    float readCurrent();
    float calculatePower(float voltage, float current);
    bool verifyPowerStability(float voltage, float current);
};

// Power Test Implementation
bool PowerTest::testPowerConsumption() {
    bool passed = true;
    
    // Measure idle power
    Serial.println("Measuring idle power...");
    float idleVoltage = readVoltage();
    float idleCurrent = readCurrent();
    float idlePower = calculatePower(idleVoltage, idleCurrent);
    
    Serial.print("Idle: ");
    Serial.print(idleVoltage);
    Serial.print("V, ");
    Serial.print(idleCurrent * 1000);
    Serial.print("mA, ");
    Serial.print(idlePower);
    Serial.println("W");
    
    // Measure active power (all sensors)
    Serial.println("Measuring active power...");
    float activeVoltage = readVoltage();
    float activeCurrent = readCurrent();
    float activePower = calculatePower(activeVoltage, activeCurrent);
    
    Serial.print("Active: ");
    Serial.print(activeVoltage);
    Serial.print("V, ");
    Serial.print(activeCurrent * 1000);
    Serial.print("mA, ");
    Serial.print(activePower);
    Serial.println("W");
    
    // Measure peak power (GSM transmission)
    Serial.println("Measuring peak power...");
    float peakVoltage = readVoltage();
    float peakCurrent = readCurrent();
    float peakPower = calculatePower(peakVoltage, peakCurrent);
    
    Serial.print("Peak: ");
    Serial.print(peakVoltage);
    Serial.print("V, ");
    Serial.print(peakCurrent * 1000);
    Serial.print("mA, ");
    Serial.print(peakPower);
    Serial.println("W");
    
    // Verify power consumption within limits
    if (idlePower > 2.0 || activePower > 5.0 || peakPower > 12.0) {
        passed = false;
    }
    
    return passed;
}

PowerProfile PowerTest::testPowerProfile() {
    PowerProfile profile;
    
    // Test all power modes
    const PowerMode modes[] = {
        POWER_MODE_IDLE,
        POWER_MODE_NORMAL,
        POWER_MODE_ACTIVE,
        POWER_MODE_PEAK
    };
    
    for (int i = 0; i < 4; i++) {
        // Set power mode
        setPowerMode(modes[i]);
        delay(1000);
        
        // Measure power
        float voltage = readVoltage();
        float current = readCurrent();
        float power = calculatePower(voltage, current);
        
        // Store in profile
        profile.modes[i].voltage = voltage;
        profile.modes[i].current = current;
        profile.modes[i].power = power;
        profile.modes[i].timestamp = millis();
    }
    
    return profile;
}
```

---

## Test Results

### Results Data Structures

```cpp
// Test Results Structure
struct TestResults {
    // Test Status
    bool gpioTest;
    bool uartTest;
    bool i2cTest;
    bool spiTest;
    bool pwmTest;
    bool adcTest;
    bool powerTest;
    
    // Test Metrics
    float adcAccuracy;
    float pwmFrequency;
    float powerConsumption;
    float errorRate;
    
    // Test Information
    int totalTests;
    int passedTests;
    int failedTests;
    unsigned long testDuration;
    String testTimestamp;
    bool allPassed;
    bool hasErrors;
    
    // Detailed Test Data
    String testDetails[10];
    String errorMessages[10];
    int errorCount;
};

// Performance Results Structure
struct PerformanceResults {
    // Performance Metrics
    float throughput;
    float latency;
    float jitter;
    float errorRate;
    
    // Resource Usage
    uint16_t memoryUsage;
    uint8_t cpuUsage;
    float powerUsage;
    
    // Performance Details
    uint32_t operationsPerSecond;
    float averageResponseTime;
    float peakResponseTime;
    float minimumResponseTime;
    
    // Stress Test Results
    uint32_t stressTestDuration;
    uint32_t stressTestCycles;
    bool stressTestPassed;
    uint32_t maxLoad;
    uint32_t breakLoad;
};

// Power Profile Structure
struct PowerProfile {
    struct ModeData {
        float voltage;
        float current;
        float power;
        unsigned long timestamp;
    } modes[4];
    
    float averagePower;
    float peakPower;
    float idlePower;
    float energyConsumed;
};
```

---

## Examples

### Complete Test Suite Example

```cpp
#include "tests/tests.h"

TestManager testManager;

void setup() {
    Serial.begin(115200);
    
    // Initialize test manager
    if (testManager.begin()) {
        Serial.println("Test Manager initialized");
        
        // Configure tests
        testManager.setTestTimeout(10000);
        testManager.setTestRetries(2);
        testManager.enableVerboseOutput(true);
        testManager.enableTestLogging(true);
        testManager.setTestLevel(TEST_LEVEL_COMPLETE);
        
        // Set callbacks
        testManager.onTestStart([](const String& name) {
            Serial.print("▶ Starting test: ");
            Serial.println(name);
        });
        
        testManager.onTestComplete([](const String& name, bool passed) {
            Serial.print("  ");
            Serial.print(passed ? "✓" : "✗");
            Serial.print(" Test ");
            Serial.print(name);
            Serial.println(passed ? " PASSED" : " FAILED");
        });
        
        testManager.onTestError([](const String& name, const String& error) {
            Serial.print("  ⚠ Error in ");
            Serial.print(name);
            Serial.print(": ");
            Serial.println(error);
        });
        
        // Run full test suite
        Serial.println("\n=== Running Full Test Suite ===");
        TestResults results = testManager.runFullTests();
        
        // Display results
        displayFullResults(results);
        
        // Export results
        testManager.exportTestResults("json");
        testManager.exportTestResults("csv");
        testManager.saveTestResults();
    }
}

void loop() {
    // Run quick tests periodically
    static unsigned long lastTest = 0;
    if (millis() - lastTest > 60000) { // Every minute
        lastTest = millis();
        Serial.println("\n=== Running Quick Tests ===");
        TestResults results = testManager.runQuickTests();
        displayQuickResults(results);
    }
    
    delay(1000);
}

void displayFullResults(const TestResults& results) {
    Serial.println("\n=== Test Results Summary ===");
    Serial.println("============================");
    Serial.print("Timestamp: ");
    Serial.println(results.testTimestamp);
    Serial.print("Duration: ");
    Serial.print(results.testDuration);
    Serial.println("ms");
    Serial.print("Tests: ");
    Serial.print(results.passedTests);
    Serial.print("/");
    Serial.println(results.totalTests);
    Serial.print("Status: ");
    Serial.println(results.allPassed ? "PASSED ✓" : "FAILED ✗");
    Serial.println("============================");
    Serial.println("\nDetailed Results:");
    Serial.println("----------------");
    Serial.print("GPIO: ");
    Serial.println(results.gpioTest ? "✓ PASSED" : "✗ FAILED");
    Serial.print("UART: ");
    Serial.println(results.uartTest ? "✓ PASSED" : "✗ FAILED");
    Serial.print("I2C: ");
    Serial.println(results.i2cTest ? "✓ PASSED" : "✗ FAILED");
    Serial.print("SPI: ");
    Serial.println(results.spiTest ? "✓ PASSED" : "✗ FAILED");
    Serial.print("PWM: ");
    Serial.println(results.pwmTest ? "✓ PASSED" : "✗ FAILED");
    Serial.print("ADC: ");
    Serial.println(results.adcTest ? "✓ PASSED" : "✗ FAILED");
    Serial.print("Power: ");
    Serial.println(results.powerTest ? "✓ PASSED" : "✗ FAILED");
    Serial.println("----------------");
    Serial.print("ADC Accuracy: ");
    Serial.print(results.adcAccuracy);
    Serial.println("%");
    Serial.print("PWM Frequency: ");
    Serial.print(results.pwmFrequency);
    Serial.println("Hz");
    Serial.print("Power Consumption: ");
    Serial.print(results.powerConsumption);
    Serial.println("W");
    Serial.println("============================");
}

void displayQuickResults(const TestResults& results) {
    Serial.println("\nQuick Test Results:");
    Serial.print("Status: ");
    Serial.println(results.allPassed ? "✓ ALL PASSED" : "✗ SOME FAILED");
    Serial.print("Pass Rate: ");
    Serial.print((results.passedTests * 100.0) / results.totalTests);
    Serial.println("%");
}
```

---

## 📚 Related Documentation

- [Sensor API](sensor_api.md)
- [Communication API](communication_api.md)
- [Hardware Documentation](../hardware/)
- [Build & Deployment Guide](../BUILD_DEPLOY.md)

---

