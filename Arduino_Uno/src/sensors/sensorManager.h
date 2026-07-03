#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include "config.h"
#include "sensor_data.h"

class SensorManager {
public:
    SensorManager();
    bool begin();
    void initLiDAR();
    void initGPS();
    void initFingerprint();
    void initRFID();
    
    SensorData readAllSensors();
    void readLiDAR();
    void readGPS();
    void readFingerprint();
    void readRFID();
    
    bool isLiDARReady();
    bool isGPSReady();
    bool isFingerprintReady();
    bool isRFIDReady();
    
    void calibrateAll();
    void calibrateLiDAR();
    void calibrateGPS();
    void calibrateFingerprint();
    void calibrateRFID();
    
    String getSensorStatus();

private:
    SensorData m_sensorData;
    bool m_lidarReady;
    bool m_gpsReady;
    bool m_fingerprintReady;
    bool m_rfidReady;
    
    unsigned long m_lastReadTime;
    unsigned long m_readInterval;
    
    void validateSensorData();
    void handleSensorError(int sensorId, String error);
};

#endif // SENSOR_MANAGER_H
