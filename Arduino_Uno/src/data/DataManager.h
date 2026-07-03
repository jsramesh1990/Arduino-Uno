#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <Arduino.h>
#include "config.h"
#include "SensorData.h"
#include "TestResults.h"
#include "CommData.h"

class DataManager {
public:
    DataManager();
    bool begin();
    
    void saveSensorData(SensorData data);
    void saveTestResults(TestResults results);
    void saveCommData(CommunicationData data);
    void saveSystemLog(String log);
    
    SensorData loadSensorData();
    TestResults loadTestResults();
    CommunicationData loadCommData();
    String loadSystemLog();
    
    void exportDataCSV(String filename);
    void exportDataJSON(String filename);
    void exportDataXML(String filename);
    
    void clearAllData();
    void clearSensorData();
    void clearTestResults();
    void clearCommData();
    
    String getDataStats();
    size_t getDataSize();
    String formatDataForStorage(SensorData data);
    SensorData parseStoredData(String data);

private:
    static const int MAX_DATA_POINTS = 1000;
    
    struct DataPoint {
        unsigned long timestamp;
        SensorData sensorData;
        TestResults testResults;
        CommunicationData commData;
    };
    
    DataPoint m_dataBuffer[MAX_DATA_POINTS];
    int m_dataCount;
    int m_writeIndex;
    
    void storeDataPoint(DataPoint data);
    DataPoint getDataPoint(int index);
    void rotateBuffer();
    
    // File Operations
    bool writeToSD(String filename, String data);
    String readFromSD(String filename);
    bool deleteFromSD(String filename);
    bool checkSDAvailable();
};

#endif // DATA_MANAGER_H
