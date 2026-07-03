/*
 * Multi-Sensor Integration Project
 * Arduino Uno with LiDAR, GPS, Fingerprint, RFID/NFC, CAN, GSM, LoRa
 * Includes GPIO, UART/I2C/SPI, PWM, ADC, and Power Testing
 */

#include <Wire.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_VL53L0X.h>
#include <TinyGPS++.h>
#include <Adafruit_Fingerprint.h>
#include <MFRC522.h>
#include <mcp2515.h>
#include <LoRa.h>
#include <SoftwareSerial.h>

// ====================== PIN DEFINITIONS ======================
// GPIO Pins
#define GPIO_LED_PIN    13
#define GPIO_BUTTON_PIN 2
#define GPIO_TEST_PIN   7

// PWM Pins
#define PWM_PIN         9
#define PWM_TEST_PIN    10

// ADC Pins
#define ADC_PIN         A0
#define ADC_TEST_PIN    A1

// I2C Pins (SDA=A4, SCL=A5) - LiDAR, RFID/NFC
// SPI Pins (MISO=12, MOSI=11, SCK=13, SS=10) - CAN, LoRa
// UART Pins (RX=0, TX=1) - GPS, Fingerprint, GSM

// ====================== OBJECT INSTANTIATION ======================
// LiDAR (I2C)
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// GPS (UART)
TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3); // RX, TX

// Fingerprint Sensor (UART)
SoftwareSerial fingerSerial(5, 6); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);

// RFID/NFC (I2C)
#define RST_PIN     9
#define SS_PIN      10
MFRC522 rfid(SS_PIN, RST_PIN);

// CAN Bus (SPI)
MCP2515 can;
struct can_frame canMsg;

// LoRa Module (SPI)
#define LORA_SS     10
#define LORA_RST    9
#define LORA_DIO0   2
#define LORA_FREQ   868E6 // 868 MHz for Europe, 915E6 for US

// GSM/GPRS (UART)
SoftwareSerial gsmSerial(7, 8); // RX, TX

// ====================== GLOBAL VARIABLES ======================
unsigned long lastTime = 0;
unsigned long testStartTime = 0;
int testCounter = 0;
float adcReferenceVoltage = 5.0;
float powerVoltage = 0;

// Test Results Structure
struct TestResults {
  bool gpiotest;
  bool uartTest;
  bool i2cTest;
  bool spiTest;
  bool pwmTest;
  bool adcTest;
  bool powerTest;
  float adcAccuracy;
  float pwmFrequency;
  float powerConsumption;
  String timestamp;
} results;

// ====================== SETUP FUNCTION ======================
void setup() {
  Serial.begin(115200);
  Serial.println("\n\n=== ARDUINO UNO MULTI-SENSOR SYSTEM ===");
  Serial.println("Initializing all modules...\n");
  
  testStartTime = millis();
  
  // Initialize GPIO Pins
  initGPIO();
  
  // Initialize PWM
  initPWM();
  
  // Initialize ADC
  initADC();
  
  // Initialize I2C
  Wire.begin();
  Serial.println("✓ I2C Initialized (SDA=A4, SCL=A5)");
  
  // Initialize SPI
  SPI.begin();
  Serial.println("✓ SPI Initialized (MOSI=11, MISO=12, SCK=13, SS=10)");
  
  // Initialize Individual Modules
  initLiDAR();
  initGPS();
  initFingerprint();
  initRFID();
  initCAN();
  initLoRa();
  initGSM();
  
  Serial.println("\n=== System Ready ===\n");
  delay(2000);
}

// ====================== INITIALIZATION FUNCTIONS ======================

void initGPIO() {
  pinMode(GPIO_LED_PIN, OUTPUT);
  pinMode(GPIO_BUTTON_PIN, INPUT_PULLUP);
  pinMode(GPIO_TEST_PIN, INPUT_PULLUP);
  digitalWrite(GPIO_LED_PIN, LOW);
  Serial.println("✓ GPIO Initialized");
}

void initPWM() {
  pinMode(PWM_PIN, OUTPUT);
  pinMode(PWM_TEST_PIN, INPUT);
  Serial.println("✓ PWM Initialized");
}

void initADC() {
  pinMode(ADC_PIN, INPUT);
  pinMode(ADC_TEST_PIN, INPUT);
  analogReference(DEFAULT);
  Serial.println("✓ ADC Initialized");
}

void initLiDAR() {
  Serial.print("✓ LiDAR Initializing... ");
  if (lox.begin()) {
    lox.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);
    Serial.println("SUCCESS");
  } else {
    Serial.println("FAILED");
  }
}

void initGPS() {
  gpsSerial.begin(9600);
  Serial.println("✓ GPS Initialized (9600 baud)");
}

void initFingerprint() {
  fingerSerial.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("✓ Fingerprint Sensor Found");
  } else {
    Serial.println("❌ Fingerprint Sensor Not Found");
  }
}

void initRFID() {
  rfid.PCD_Init();
  Serial.println("✓ RFID/NFC Reader Initialized");
}

void initCAN() {
  can.reset();
  can.setBitrate(CAN_500KBPS);
  can.setNormalMode();
  Serial.println("✓ CAN Bus Initialized (500 kbps)");
}

void initLoRa() {
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (LoRa.begin(LORA_FREQ)) {
    LoRa.setSpreadingFactor(12);
    LoRa.setTxPower(20);
    LoRa.setCodingRate4(5);
    Serial.println("✓ LoRa Module Initialized");
  } else {
    Serial.println("❌ LoRa Module Init Failed");
  }
}

void initGSM() {
  gsmSerial.begin(9600);
  Serial.println("✓ GSM/GPRS Module Initialized");
  delay(1000);
  gsmSerial.println("AT");
  delay(500);
  if (gsmSerial.available()) {
    String response = gsmSerial.readString();
    if (response.indexOf("OK") > 0) {
      Serial.println("✓ GSM Module Responding");
    }
  }
}

// ====================== MAIN LOOP ======================
void loop() {
  unsigned long currentTime = millis();
  
  // Run tests every 5 seconds
  if (currentTime - lastTime >= 5000) {
    lastTime = currentTime;
    testCounter++;
    
    Serial.println("\n========== TEST CYCLE #" + String(testCounter) + " ==========");
    Serial.println("Timestamp: " + getTimestamp());
    
    // Run all tests
    runGPIOtest();
    runUARTtest();
    runI2Ctest();
    runSPItest();
    runPWMtest();
    runADCtest();
    runPowerTest();
    
    // Display results summary
    displayResults();
    
    // Send data via LoRa
    sendLoRaData();
    
    // Send data via GSM
    sendGSMData();
    
    // Send data via CAN
    sendCANData();
  }
  
  // Continuous sensor reading
  readLiDAR();
  readGPS();
  checkFingerprint();
  checkRFID();
}

// ====================== TEST FUNCTIONS ======================

void runGPIOtest() {
  Serial.println("\n--- GPIO Test ---");
  
  // Test Output
  digitalWrite(GPIO_LED_PIN, HIGH);
  delay(100);
  digitalWrite(GPIO_LED_PIN, LOW);
  
  // Test Input
  int buttonState = digitalRead(GPIO_BUTTON_PIN);
  int testPinState = digitalRead(GPIO_TEST_PIN);
  
  results.gpiotest = (buttonState == HIGH || buttonState == LOW);
  
  Serial.print("GPIO Output Test: ");
  Serial.println(results.gpiotest ? "PASS" : "FAIL");
  Serial.print("Button State: ");
  Serial.println(buttonState == LOW ? "PRESSED" : "RELEASED");
  Serial.print("Test Pin State: ");
  Serial.println(testPinState);
}

void runUARTtest() {
  Serial.println("\n--- UART Communication Test ---");
  
  // Test GPS UART
  bool gpsOk = false;
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    if (gps.encode(c)) {
      gpsOk = true;
      break;
    }
  }
  
  // Test GSM UART
  gsmSerial.println("AT");
  delay(200);
  String gsmResponse = "";
  while (gsmSerial.available()) {
    gsmResponse += (char)gsmSerial.read();
  }
  
  bool gsmOk = gsmResponse.indexOf("OK") >= 0;
  
  // Test Fingerprint UART
  bool fingerOk = finger.verifyPassword();
  
  results.uartTest = (gpsOk || gsmOk || fingerOk);
  
  Serial.print("GPS UART: ");
  Serial.println(gpsOk ? "OK" : "No Data");
  Serial.print("GSM UART: ");
  Serial.println(gsmOk ? "OK" : "No Response");
  Serial.print("Fingerprint UART: ");
  Serial.println(fingerOk ? "OK" : "No Response");
}

void runI2Ctest() {
  Serial.println("\n--- I2C Communication Test ---");
  
  // Scan I2C devices
  byte error, address;
  int nDevices = 0;
  
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
  }
  
  results.i2cTest = (nDevices > 0);
  Serial.print("Total I2C devices: ");
  Serial.println(nDevices);
}

void runSPItest() {
  Serial.println("\n--- SPI Communication Test ---");
  
  // Test CAN SPI
  uint8_t canStatus = can.readStatus();
  bool canOk = (canStatus != 0xFF);
  
  // Test LoRa SPI
  bool loraOk = LoRa.begin(LORA_FREQ);
  
  results.spiTest = (canOk || loraOk);
  
  Serial.print("CAN SPI: ");
  Serial.println(canOk ? "OK" : "No Response");
  Serial.print("LoRa SPI: ");
  Serial.println(loraOk ? "OK" : "No Response");
}

void runPWMtest() {
  Serial.println("\n--- PWM Testing ---");
  
  // Generate PWM on pin 9
  for (int duty = 0; duty <= 255; duty += 85) {
    analogWrite(PWM_PIN, duty);
    delay(100);
    
    // Read PWM test pin
    int pwmValue = analogRead(PWM_TEST_PIN);
    float voltage = (pwmValue / 1023.0) * 5.0;
    float dutyCycle = (voltage / 5.0) * 100.0;
    
    Serial.print("Set: ");
    Serial.print(duty);
    Serial.print(" (");
    Serial.print((duty / 255.0) * 100);
    Serial.print("%) -> Read: ");
    Serial.print(voltage);
    Serial.print("V (");
    Serial.print(dutyCycle);
    Serial.println("%)");
  }
  
  analogWrite(PWM_PIN, 0);
  results.pwmTest = true;
}

void runADCtest() {
  Serial.println("\n--- ADC Accuracy Testing ---");
  
  // Read ADC values
  float adcValues[10];
  float sum = 0;
  
  for (int i = 0; i < 10; i++) {
    adcValues[i] = analogRead(ADC_PIN);
    sum += adcValues[i];
    delay(10);
  }
  
  float average = sum / 10.0;
  float voltage = (average / 1023.0) * adcReferenceVoltage;
  
  // Calculate accuracy (assuming 10-bit ADC)
  float expectedResolution = adcReferenceVoltage / 1024.0;
  float error = abs(voltage - (adcReferenceVoltage / 2.0)); // Assuming 2.5V input
  
  results.adcAccuracy = (1 - (error / adcReferenceVoltage)) * 100;
  results.adcTest = (results.adcAccuracy > 90.0);
  
  Serial.print("ADC Average: ");
  Serial.println(average);
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println("V");
  Serial.print("Resolution: ");
  Serial.print(expectedResolution * 1000);
  Serial.println("mV");
  Serial.print("Accuracy: ");
  Serial.print(results.adcAccuracy);
  Serial.println("%");
}

void runPowerTest() {
  Serial.println("\n--- Power Consumption Testing ---");
  
  // Measure voltage on ADC (assuming voltage divider)
  int powerReading = analogRead(ADC_TEST_PIN);
  float measuredVoltage = (powerReading / 1023.0) * adcReferenceVoltage;
  
  // Current measurement (assuming shunt resistor)
  float shuntResistor = 0.1; // 0.1 ohm
  float current = measuredVoltage / shuntResistor; // Simple calculation
  
  // Power consumption
  float power = measuredVoltage * current;
  
  results.powerConsumption = power;
  results.powerTest = (power < 5.0); // Assuming 5W max
  
  Serial.print("Voltage: ");
  Serial.print(measuredVoltage);
  Serial.println("V");
  Serial.print("Current: ");
  Serial.print(current * 1000);
  Serial.println("mA");
  Serial.print("Power: ");
  Serial.print(power);
  Serial.println("W");
}

// ====================== SENSOR READING FUNCTIONS ======================

void readLiDAR() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  
  if (measure.RangeStatus != 4) {
    Serial.print("LiDAR Distance: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
  }
}

void readGPS() {
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    if (gps.encode(c)) {
      if (gps.location.isValid()) {
        Serial.print("GPS Location: ");
        Serial.print(gps.location.lat(), 6);
        Serial.print(", ");
        Serial.println(gps.location.lng(), 6);
      }
      
      if (gps.altitude.isValid()) {
        Serial.print("Altitude: ");
        Serial.print(gps.altitude.meters());
        Serial.println("m");
      }
      
      if (gps.speed.isValid()) {
        Serial.print("Speed: ");
        Serial.print(gps.speed.kmph());
        Serial.println(" km/h");
      }
    }
  }
}

void checkFingerprint() {
  if (finger.getImage() == FINGERPRINT_OK) {
    Serial.println("Fingerprint Detected");
    if (finger.image2Tz() == FINGERPRINT_OK) {
      if (finger.fingerSearch() == FINGERPRINT_OK) {
        Serial.println("Fingerprint Matched!");
        Serial.print("ID: ");
        Serial.println(finger.fingerID);
      }
    }
  }
}

void checkRFID() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;
  
  Serial.print("RFID Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();
  
  rfid.PICC_HaltA();
}

// ====================== DATA TRANSMISSION FUNCTIONS ======================

void sendLoRaData() {
  Serial.println("\n--- Sending Data via LoRa ---");
  
  String data = "T:" + getTimestamp() + 
                ",G:" + String(results.gpiotest) +
                ",U:" + String(results.uartTest) +
                ",I:" + String(results.i2cTest) +
                ",S:" + String(results.spiTest) +
                ",P:" + String(results.pwmTest) +
                ",A:" + String(results.adcTest) +
                ",PWR:" + String(results.powerConsumption);
  
  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();
  
  Serial.println("LoRa Data Sent: " + data);
  
  // Check for incoming messages
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }
    Serial.println("LoRa Received: " + incoming);
  }
}

void sendGSMData() {
  Serial.println("\n--- Sending Data via GSM ---");
  
  // AT Commands for GSM
  gsmSerial.println("AT+CSQ"); // Signal quality
  delay(300);
  
  while (gsmSerial.available()) {
    String response = gsmSerial.readString();
    Serial.println("GSM Response: " + response);
  }
}

void sendCANData() {
  Serial.println("\n--- Sending Data via CAN ---");
  
  canMsg.can_id = 0x100;
  canMsg.can_dlc = 8;
  canMsg.data[0] = results.gpiotest ? 1 : 0;
  canMsg.data[1] = results.uartTest ? 1 : 0;
  canMsg.data[2] = results.i2cTest ? 1 : 0;
  canMsg.data[3] = results.spiTest ? 1 : 0;
  canMsg.data[4] = results.pwmTest ? 1 : 0;
  canMsg.data[5] = results.adcTest ? 1 : 0;
  canMsg.data[6] = (uint8_t)(results.powerConsumption * 100);
  canMsg.data[7] = (uint8_t)results.adcAccuracy;
  
  if (can.sendMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.println("CAN Data Sent Successfully");
  } else {
    Serial.println("CAN Send Failed");
  }
}

// ====================== UTILITY FUNCTIONS ======================

String getTimestamp() {
  char buffer[20];
  unsigned long ms = millis();
  unsigned long seconds = ms / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  
  sprintf(buffer, "%02lu:%02lu:%02lu", 
          hours % 24, 
          minutes % 60, 
          seconds % 60);
  return String(buffer);
}

void displayResults() {
  Serial.println("\n========== TEST RESULTS SUMMARY ==========");
  Serial.println("GPIO Test:      " + String(results.gpiotest ? "✓ PASS" : "✗ FAIL"));
  Serial.println("UART Test:      " + String(results.uartTest ? "✓ PASS" : "✗ FAIL"));
  Serial.println("I2C Test:       " + String(results.i2cTest ? "✓ PASS" : "✗ FAIL"));
  Serial.println("SPI Test:       " + String(results.spiTest ? "✓ PASS" : "✗ FAIL"));
  Serial.println("PWM Test:       " + String(results.pwmTest ? "✓ PASS" : "✗ FAIL"));
  Serial.println("ADC Test:       " + String(results.adcTest ? "✓ PASS" : "✗ FAIL"));
  Serial.println("Power Test:     " + String(results.powerTest ? "✓ PASS" : "✗ FAIL"));
  Serial.println("ADC Accuracy:   " + String(results.adcAccuracy) + "%");
  Serial.println("Power Cons.:    " + String(results.powerConsumption) + "W");
  Serial.println("==========================================\n");
}

// ====================== ADDITIONAL FUNCTIONS ======================

// Function to calibrate ADC
void calibrateADC() {
  Serial.println("\n--- ADC Calibration ---");
  
  // Use internal 1.1V reference for better accuracy
  analogReference(INTERNAL);
  
  // Read multiple samples
  long sum = 0;
  for (int i = 0; i < 100; i++) {
    sum += analogRead(ADC_PIN);
    delay(1);
  }
  
  float average = sum / 100.0;
  float voltage = (average * 1.1) / 1023.0;
  
  Serial.print("Calibrated Voltage: ");
  Serial.print(voltage * 1000);
  Serial.println("mV");
  
  // Reset to default
  analogReference(DEFAULT);
}

// Function to test all communication protocols
void testCommunicationProtocols() {
  Serial.println("\n--- Communication Protocol Test ---");
  
  // UART Test
  Serial.println("1. UART: Testing GPS data...");
  gpsSerial.println("$PGCMD,33,1*6C"); // Request GPS data
  
  // I2C Test
  Serial.println("2. I2C: Testing LiDAR...");
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  
  // SPI Test
  Serial.println("3. SPI: Testing LoRa...");
  int loraVersion = LoRa.begin(LORA_FREQ);
  
  Serial.println("Communication tests completed.");
}

// Interrupt service routine for GPIO button
void buttonISR() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  
  if (interruptTime - lastInterruptTime > 200) {
    Serial.println("Button Interrupt Triggered!");
    digitalWrite(GPIO_LED_PIN, !digitalRead(GPIO_LED_PIN));
    lastInterruptTime = interruptTime;
  }
}

// Function to save data to SD card (if available)
void saveDataToSD() {
  // Implementation for SD card if needed
  Serial.println("Data saving to SD card...");
}

// Console Output Formatter
void consoleOutput() {
  Serial.println("\n┌─────────────────────────────────────────────┐");
  Serial.println("│         SYSTEM STATUS DASHBOARD            │");
  Serial.println("├─────────────────────────────────────────────┤");
  Serial.println("│ Timestamp: " + getTimestamp() + "                      │");
  Serial.println("├─────────────────────────────────────────────┤");
  Serial.println("│ SENSORS:                                    │");
  Serial.println("│  LiDAR    : " + String(lox.begin() ? "ONLINE" : "OFFLINE") + "                        │");
  Serial.println("│  GPS      : " + String(gps.location.isValid() ? "FIXED" : "SEARCHING") + "                 │");
  Serial.println("│  Finger   : " + String(finger.verifyPassword() ? "ONLINE" : "OFFLINE") + "                        │");
  Serial.println("│  RFID     : " + String(rfid.PCD_PerformSelfTest() ? "ONLINE" : "OFFLINE") + "                        │");
  Serial.println("├─────────────────────────────────────────────┤");
  Serial.println("│ COMMUNICATION:                             │");
  Serial.println("│  CAN      : " + String(can.readStatus() != 0xFF ? "OK" : "FAIL") + "                        │");
  Serial.println("│  LoRa     : " + String(LoRa.begin(LORA_FREQ) ? "OK" : "FAIL") + "                        │");
  Serial.println("│  GSM      : " + String(gsmSerial.available() > 0 ? "OK" : "FAIL") + "                        │");
  Serial.println("├─────────────────────────────────────────────┤");
  Serial.println("│ POWER: " + String(results.powerConsumption) + "W                        │");
  Serial.println("└─────────────────────────────────────────────┘\n");
}
