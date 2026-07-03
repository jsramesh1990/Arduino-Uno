#ifndef TEST_MANAGER_H
#define TEST_MANAGER_H

#include <Arduino.h>
#include "config.h"
#include "TestResults.h"

class TestManager {
public:
    TestManager();
    bool begin();
    
    TestResults runAllTests();
    TestResults runScheduledTests();
    TestResults runQuickTests();
    TestResults runFullTests();
    
    // Individual Tests
    bool testGPIO();
    bool testUART();
    bool testI2C();
    bool testSPI();
    bool testPWM();
    bool testADC();
    bool testPower();
    
    // Test Helpers
    void setupTestEnvironment();
    void cleanupTestEnvironment();
    void calibrateTestEquipment();
    String getTestReport(TestResults results);
    void saveTestResults(TestResults results);
    
    // Test Configuration
    void setTestTimeout(unsigned long timeout);
    void setTestRetries(int retries);
    void enableTestLogging(bool enable);

private:
    TestResults m_results;
    unsigned long m_testTimeout;
    int m_testRetries;
    bool m_testLogging;
    unsigned long m_lastTestTime;
    unsigned long m_testInterval;
    
    // Test Data
    float m_testVoltage;
    float m_testCurrent;
    float m_testFrequency;
    int m_testCounter;
    
    void runGPIO_Test();
    void runUART_Test();
    void runI2C_Test();
    void runSPI_Test();
    void runPWM_Test();
    void runADC_Test();
    void runPower_Test();
    
    bool verifyTestResult(String testName, bool result);
    void recordTestFailure(String testName, String error);
    void updateTestStatistics(bool passed);
};

#endif // TEST_MANAGER_H
