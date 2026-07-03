#ifndef CONSOLE_OUTPUT_H
#define CONSOLE_OUTPUT_H

#include <Arduino.h>
#include "config.h"
#include "SensorData.h"
#include "TestResults.h"
#include "CommData.h"

class ConsoleOutput {
public:
    static void displayDashboard(SystemState state, SensorData sensors, 
                                 TestResults tests, CommunicationData comm);
    static void displaySystemInfo(SystemInfo info);
    static void displaySensorStatus(SensorData data);
    static void displayTestResults(TestResults results);
    static void displayCommunicationStatus(CommunicationData data);
    static void displayErrorLog(String error);
    
    static void displayHeader(String title);
    static void displayFooter();
    static void displayDivider();
    static void displayProgressBar(float progress);
    static void displayTable(String headers[], String rows[], int rowCount);
    
    static void setConsoleWidth(int width);
    static void setOutputFormat(int format); // 0: Text, 1: JSON, 2: CSV
    
private:
    static int m_consoleWidth;
    static int m_outputFormat;
    
    static void centerText(String text);
    static String padString(String text, int length, char padChar = ' ');
    static String getTimestamp();
    static String getStatusSymbol(bool status);
    static String getColorCode(String color);
    static String resetColor();
    
    static void printJSON(SystemState state, SensorData sensors, 
                         TestResults tests, CommunicationData comm);
    static void printCSV(SystemState state, SensorData sensors, 
                        TestResults tests, CommunicationData comm);
    static void printText(SystemState state, SensorData sensors, 
                         TestResults tests, CommunicationData comm);
};

#endif // CONSOLE_OUTPUT_H
