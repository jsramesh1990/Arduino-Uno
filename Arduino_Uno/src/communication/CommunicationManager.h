#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

#include <Arduino.h>
#include "config.h"
#include "comm_data.h"
#include "SensorData.h"
#include "TestResults.h"

class CommunicationManager {
public:
    CommunicationManager();
    bool begin();
    
    void initCAN();
    void initLoRa();
    void initGSM();
    
    CommunicationData sendAllData(SensorData sensorData, TestResults testResults);
    void sendCANData(SensorData data, TestResults results);
    void sendLoRaData(SensorData data, TestResults results);
    void sendGSMData(SensorData data, TestResults results);
    
    bool isCANReady();
    bool isLoRaReady();
    bool isGSMReady();
    
    String receiveLoRaData();
    String receiveCANData();
    String receiveGSMData();
    
    void configureCAN(int speed);
    void configureLoRa(float frequency, int sf, int power);
    void configureGSM(String apn, String user, String pass);
    
    String getCommunicationStatus();

private:
    CommunicationData m_commData;
    bool m_canReady;
    bool m_loraReady;
    bool m_gsmReady;
    
    unsigned long m_lastSendTime;
    unsigned long m_sendInterval;
    
    void validateCommunicationData();
    void handleCommunicationError(int moduleId, String error);
    String formatDataForTransmission(SensorData sensorData, TestResults testResults);
};

#endif // COMMUNICATION_MANAGER_H
