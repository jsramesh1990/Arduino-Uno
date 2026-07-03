# docs/hardware/power_requirements.md

# Power Requirements - Arduino Multi-Sensor Platform

## 📊 Complete Power Analysis & Requirements

This document provides comprehensive power requirements, calculations, and recommendations for the Arduino Multi-Sensor Platform.

---

## 🔋 System Power Overview

### Power Distribution Architecture

```
┌─────────────────────────────────────────────────────────────────────┐
│                     SYSTEM POWER ARCHITECTURE                      │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   ┌────────────────────────────────────────────────────────────┐   │
│   │                  EXTERNAL POWER SUPPLY                     │   │
│   │                   12V DC / 2A (24W)                       │   │
│   └────────────────────────┬───────────────────────────────────┘   │
│                            │                                       │
│                            ▼                                       │
│   ┌────────────────────────────────────────────────────────────┐   │
│   │              VOLTAGE REGULATION STAGE                      │   │
│   │  ┌────────────────────────────────────────────────────┐   │   │
│   │  │  LM2596 Buck Converter (Step-Down)                │   │   │
│   │  │  Input: 7-12V DC   Output: 5V @ 2A (10W)         │   │   │
│   │  └────────────────────────────────────────────────────┘   │   │
│   │  ┌────────────────────────────────────────────────────┐   │   │
│   │  │  AMS1117-3.3 LDO Regulator                        │   │   │
│   │  │  Input: 5V          Output: 3.3V @ 0.8A (2.64W)   │   │   │
│   │  └────────────────────────────────────────────────────┘   │   │
│   └────────────────────────┬───────────────────────────────────┘   │
│                            │                                       │
│              ┌─────────────┴─────────────┐                       │
│              │                           │                       │
│              ▼                           ▼                       │
│   ┌────────────────────┐    ┌────────────────────┐              │
│   │    5V POWER BUS    │    │   3.3V POWER BUS   │              │
│   │   Max: 2A (10W)    │    │   Max: 0.8A (2.6W) │              │
│   └─────────┬──────────┘    └─────────┬──────────┘              │
│             │                         │                          │
│             ▼                         ▼                          │
│   ┌────────────────────┐    ┌────────────────────┐              │
│   │  5V Modules:       │    │  3.3V Modules:     │              │
│   │  - Arduino Uno     │    │  - LiDAR VL53L0X   │              │
│   │  - GPS NEO-6M      │    │  - RFID MFRC522    │              │
│   │  - Fingerprint     │    │  - LoRa SX1278     │              │
│   │  - GSM SIM800L     │    │  - RTC DS3231      │              │
│   │  - CAN MCP2515     │    └────────────────────┘              │
│   │  - SD Card Module  │                                         │
│   │  - LCD Display     │                                         │
│   └────────────────────┘                                         │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 📊 Detailed Power Consumption

### 1. Individual Module Power Requirements

| Module | Voltage | Current (Max) | Current (Typical) | Power (Max) | Power (Typical) | Sleep Mode |
|--------|---------|---------------|-------------------|-------------|-----------------|------------|
| **Arduino Uno** | 5V | 500mA | 200mA | 2.5W | 1.0W | 10mA (0.05W) |
| **LiDAR (VL53L0X)** | 3.3V | 40mA | 20mA | 0.132W | 0.066W | 1µA (0.000003W) |
| **GPS (NEO-6M)** | 5V | 100mA | 50mA | 0.5W | 0.25W | 10mA (0.05W) |
| **Fingerprint (R307)** | 5V | 150mA | 80mA | 0.75W | 0.4W | 2mA (0.01W) |
| **RFID (MFRC522)** | 3.3V | 100mA | 50mA | 0.33W | 0.165W | 10µA (0.000033W) |
| **CAN (MCP2515)** | 5V | 100mA | 60mA | 0.5W | 0.3W | 1mA (0.005W) |
| **LoRa (SX1278)** | 3.3V | 120mA | 40mA (RX) | 0.396W | 0.132W (RX) | 1µA (0.000003W) |
| **GSM (SIM800L)** | 5V | 2A (Peak) | 200mA (Idle) | 10W (Peak) | 1.0W (Idle) | 5mA (0.025W) |
| **LCD Display** | 5V | 100mA | 50mA | 0.5W | 0.25W | 1mA (0.005W) |
| **SD Card** | 5V | 100mA | 50mA | 0.5W | 0.25W | 1mA (0.005W) |
| **RTC (DS3231)** | 3.3V | 10mA | 5mA | 0.033W | 0.0165W | 0.1µA (0.0000003W) |
| **Total** | - | **3.3A** | **0.8A** | **15.6W** | **3.8W** | **0.15W** |

### 2. Power Consumption by State

```
┌─────────────────────────────────────────────────────────────────────┐
│                   POWER CONSUMPTION BY STATE                       │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   State                  │  Current  │  Power    │  Duration       │
│   ───────────────────────┼───────────┼───────────┼─────────────────│
│   Idle Mode              │  200mA    │  1.0W     │  80% of time    │
│   Active Mode            │  800mA    │  4.0W     │  15% of time    │
│   GSM Transmission       │  2.0A     │  10.0W    │  2% of time     │
│   LoRa Transmission      │  120mA    │  0.396W   │  1% of time     │
│   All Sensors Active     │  1.2A     │  6.0W     │  1% of time     │
│   Sleep Mode             │  15mA     │  0.075W   │  1% of time     │
│                                                                     │
│   Average Power Consumption (Typical):                             │
│   ─────────────────────────────────────────────────────────────────│
│   Idle:         1.0W  × 0.80 = 0.80W                              │
│   Active:       4.0W  × 0.15 = 0.60W                              │
│   GSM TX:       10.0W × 0.02 = 0.20W                              │
│   LoRa TX:      0.4W  × 0.01 = 0.004W                            │
│   All Sensors:  6.0W  × 0.01 = 0.06W                             │
│   Sleep:        0.075W × 0.01 = 0.00075W                         │
│   ─────────────────────────────────────────────────────────────────│
│   Average Power: ~1.66W                                           │
│   Average Current (5V): ~332mA                                    │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## ⚡ Power Supply Specifications

### 1. Recommended Power Supply

```
┌─────────────────────────────────────────────────────────────────────┐
│                    POWER SUPPLY SPECIFICATIONS                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Parameter              │  Minimum   │  Recommended   │  Maximum   │
│   ───────────────────────┼────────────┼────────────────┼────────────│
│   Input Voltage          │  7.0V      │  12.0V         │  24.0V     │
│   Input Current          │  1.0A      │  2.0A          │  3.0A      │
│   Input Power            │  12W       │  24W           │  36W       │
│   Output Voltage (5V)    │  4.75V     │  5.0V          │  5.25V     │
│   Output Current (5V)    │  1.5A      │  2.0A          │  2.5A      │
│   Output Voltage (3.3V)  │  3.135V    │  3.3V          │  3.465V    │
│   Output Current (3.3V)  │  0.5A      │  0.8A          │  1.0A      │
│   Efficiency             │  70%       │  85%           │  95%       │
│   Ripple & Noise         │  -         │  <50mV         │  <100mV    │
│   Line Regulation        │  -         │  ±0.5%         │  ±2%       │
│   Load Regulation        │  -         │  ±1%           │  ±3%       │
│   Temperature Range      │  -20°C     │  25°C          │  70°C      │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 2. Power Supply Options

| Type | Model | Voltage | Current | Power | Price | Pros | Cons |
|------|-------|---------|---------|-------|-------|------|------|
| **Wall Adapter** | Generic 12V/2A | 12V | 2A | 24W | $10-15 | Cheap, Available | Unregulated, Noisy |
| **Bench Supply** | Generic 3A | 12V | 3A | 36W | $30-50 | Regulated, Stable | Expensive, Bulky |
| **Car Adapter** | 12V Cigarette | 12V | 2A | 24W | $8-12 | Portable | Noisy, Unstable |
| **USB Power Bank** | QC 3.0 | 5V | 2A | 10W | $15-25 | Portable, Clean | Limited Current |
| **ATX PSU** | PC Power Supply | 12V | 10A | 120W | $20-30 | High Power, Clean | Bulky, Overkill |
| **Battery Pack** | 12V SLA | 12V | 7Ah | 84Wh | $25-35 | Portable | Heavy, Needs Charging |
| **LiPo Battery** | 3S 2200mAh | 11.1V | 2.2Ah | 24Wh | $20-30 | Light, Portable | Needs Charger |

---

## 🔋 Battery Backup System

### Battery Sizing Calculations

```
┌─────────────────────────────────────────────────────────────────────┐
│                     BATTERY BACKUP SYSTEM                          │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   1. Battery Selection:                                            │
│   ─────────────────────────────────────────────────────────────────│
│   For 24-hour operation at average 1.66W:                          │
│   Energy Required = 1.66W × 24h = 39.84Wh                         │
│   Battery Capacity (12V) = 39.84Wh / 12V = 3.32Ah                │
│   Recommended Battery = 12V 4.5Ah (54Wh)                          │
│                                                                     │
│   2. Battery Types:                                                │
│   ┌─────────────────┬──────────────┬──────────────┬───────────────┐│
│   │ Type            │ Capacity     │ Weight       │ Cost          ││
│   ├─────────────────┼──────────────┼──────────────┼───────────────┤│
│   │ Lead Acid 4.5Ah │ 12V 4.5Ah    │ 1.8kg        │ $20-25        ││
│   │ Li-ion 3S2P     │ 11.1V 4.4Ah  │ 0.4kg        │ $35-45        ││
│   │ LiFePO4 3S      │ 9.9V 5.0Ah   │ 0.5kg        │ $40-50        ││
│   │ NiMH 10S        │ 12V 4.0Ah    │ 1.2kg        │ $30-40        ││
│   └─────────────────┴──────────────┴──────────────┴───────────────┘│
│                                                                     │
│   3. Charging Requirements:                                        │
│   ● Charging Current: 0.5A (C/10 rate for Lead Acid)              │
│   ● Charging Voltage: 13.8V (Float) / 14.4V (Bulk)                │
│   ● Charge Time: 8-12 hours                                       │
│   ● Protection: Over-discharge protection required                │
│                                                                     │
│   4. Backup Time Calculations:                                     │
│   ┌─────────────────┬──────────────┬──────────────┬───────────────┐│
│   │ Battery         │ Capacity     │ Average Load │ Backup Time   ││
│   ├─────────────────┼──────────────┼──────────────┼───────────────┤│
│   │ 12V 4.5Ah       │ 54Wh         │ 1.66W        │ 32.5 hours    ││
│   │ 12V 7.2Ah       │ 86.4Wh       │ 1.66W        │ 52.0 hours    ││
│   │ 12V 12Ah        │ 144Wh        │ 1.66W        │ 86.7 hours    ││
│   │ 12V 18Ah        │ 216Wh        │ 1.66W        │ 130.1 hours   ││
│   └─────────────────┴──────────────┴──────────────┴───────────────┘│
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 📈 Power Consumption Analysis

### 1. Dynamic Power Profile

```
┌─────────────────────────────────────────────────────────────────────┐
│                   DYNAMIC POWER PROFILE                            │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Power (W)                                                         │
│   ▲                                                                 │
│   │                                                                 │
│   │      ▲                                                         │
│   │     /│\                                                        │
│   │    / │ \                                                       │
│   │   /  │  \                                                      │
│   │  /   │   \                                                     │
│   │ /    │    \                                                    │
│   │/     │     \                                                   │
│   │      │      \                                                  │
│   │      │       \                                                 │
│   │      │        \      ▲                                         │
│   │      │         \    /│\                                        │
│   │      │          \  / │ \                                       │
│   │──────┼─────────────┼──┼────────────────────────► Time         │
│   │      │             │  │                                        │
│   │      │             │  │                                        │
│   │      │             │  │                                        │
│   │      │             │  │                                        │
│   │      │             │  │                                        │
│   └────────────────────────────────────────────────────────────────│
│                                                                     │
│   Legend:                                                          │
│   ─────  Idle Mode (1.0W)                                          │
│   ░░░░░  Active Mode (4.0W)                                       │
│   █████  GSM Transmit (10.0W)                                     │
│   ▓▓▓▓▓  LoRa Transmit (0.4W)                                     │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 2. Peak Power Scenarios

```
┌─────────────────────────────────────────────────────────────────────┐
│                     PEAK POWER SCENARIOS                           │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Scenario                    │  Power   │  Current │  Duration   │
│   ────────────────────────────┼──────────┼──────────┼─────────────│
│   Normal Operation            │  3.8W    │  760mA   │  Continuous │
│   GSM Transmission            │  10.0W   │  2000mA  │  <2s        │
│   All Sensors Active          │  6.0W    │  1200mA  │  <1s        │
│   Boot-Up Sequence            │  8.0W    │  1600mA  │  <3s        │
│   Fingerprint Enrollment      │  5.0W    │  1000mA  │  <5s        │
│   SD Card Write               │  4.5W    │  900mA   │  <1s        │
│   LoRa Transmission           │  4.2W    │  840mA   │  <0.5s      │
│   CAN Bus Active              │  4.0W    │  800mA   │  Continuous │
│   LCD Backlight Full          │  4.5W    │  900mA   │  Continuous │
│   All Combined (Worst Case)   │  15.6W   │  3120mA  │  <1s        │
│                                                                     │
│   Total Energy per Day (Typical):                                  │
│   ─────────────────────────────────────────────────────────────────│
│   Average Power: 1.66W                                            │
│   Daily Energy: 1.66W × 24h = 39.84Wh                            │
│   Monthly Energy: 39.84Wh × 30 = 1.195kWh                        │
│   Yearly Energy: 39.84Wh × 365 = 14.54kWh                        │
│   Electricity Cost (0.12/kWh): ~$1.74/year                       │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 🔌 Power Distribution Network

### 1. PCB Power Distribution

```
┌─────────────────────────────────────────────────────────────────────┐
│                   PCB POWER DISTRIBUTION                           │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   ┌──────────────────────────────────────────────────────┐        │
│   │                  12V INPUT (J1)                     │        │
│   │                  ┌────────────┐                     │        │
│   │                  │            │                     │        │
│   │                  │  F1 2A     │                     │        │
│   │                  │  ┌────┐    │                     │        │
│   │                  │  │    │    │                     │        │
│   │                  │  └────┘    │                     │        │
│   │                  │  D1 1N4007 │                     │        │
│   │                  │  ┌────┐    │                     │        │
│   │                  │  │    │    │                     │        │
│   │                  │  └────┘    │                     │        │
│   │                  │  ┌──────────────┐                │        │
│   │                  │  │   LM2596     │                │        │
│   │                  │  │   Step-Down  │                │        │
│   │                  │  │  12V → 5V    │                │        │
│   │                  │  └──────────────┘                │        │
│   │                  │   │         │                    │        │
│   │                  │  ┌▼─────────▼┐                   │        │
│   │                  │  │  5V BUS   │                   │        │
│   │                  │  └┬─────────┬┘                   │        │
│   │                  │   │         │                    │        │
│   │                  │   │    ┌────▼────┐               │        │
│   │                  │   │    │ AMS1117 │               │        │
│   │                  │   │    │ 5V→3.3V │               │        │
│   │                  │   │    └────┬────┘               │        │
│   │                  │   │         │                    │        │
│   │                  │  ┌▼─────────▼┐                   │        │
│   │                  │  │ 3.3V BUS  │                   │        │
│   │                  │  └┬─────────┬┘                   │        │
│   │                  │   │         │                    │        │
│   │                  │   │    ┌────▼────┐               │        │
│   │                  │   │    │Current  │               │        │
│   │                  │   │    │Sensor   │               │        │
│   │                  │   │    │ACS712   │               │        │
│   │                  │   │    └────┬────┘               │        │
│   │                  │   │         │                    │        │
│   │                  │  ┌▼─────────▼┐                   │        │
│   │                  │  │   LOAD    │                   │        │
│   │                  │  │  Modules  │                   │        │
│   │                  │  └───────────┘                   │        │
│   │                  └──────────────────────────────────┘        │
│   └──────────────────────────────────────────────────────┘        │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 2. Voltage Rail Specifications

```
┌─────────────────────────────────────────────────────────────────────┐
│                     VOLTAGE RAIL DETAILS                           │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Rail          │  Voltage  │  Current   │  Ripple   │  Protection │
│   ──────────────┼───────────┼────────────┼───────────┼─────────────│
│   12V Rail      │  12.0V    │  2.0A      │  <100mV   │  Fuse 2A    │
│   5V Rail       │  5.0V     │  2.0A      │  <50mV    │  Overload   │
│   3.3V Rail     │  3.3V     │  0.8A      │  <30mV    │  Overload   │
│   AREF          │  5.0V     │  10mA      │  <10mV    │  Protected  │
│   USB 5V        │  5.0V     │  500mA     │  <100mV   │  USB Fuse   │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 🛡️ Power Protection

### 1. Protection Circuits

```
┌─────────────────────────────────────────────────────────────────────┐
│                     POWER PROTECTION CIRCUITS                      │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   1. Input Protection:                                             │
│   ┌────────────────────────────────────────────────────────────┐   │
│   │  ● Reverse Polarity Protection (Diode)                     │   │
│   │  ● Over-voltage Protection (TVS Diode SMCJ18A)            │   │
│   │  ● Over-current Protection (Fuse 2A)                      │   │
│   │  ● EMI Filtering (Ferrite Bead + Capacitors)              │   │
│   │  ● Soft Start (Inrush Current Limiting)                   │   │
│   └────────────────────────────────────────────────────────────┘   │
│                                                                     │
│   2. Output Protection:                                            │
│   ┌────────────────────────────────────────────────────────────┐   │
│   │  ● Short Circuit Protection                               │   │
│   │  ● Over-current Protection (2A limit)                     │   │
│   │  ● Thermal Protection (Over-temperature shutdown)         │   │
│   │  ● Under-voltage Protection (UVLO)                       │   │
│   │  ● Output Capacitors (220µF + 0.1µF)                     │   │
│   └────────────────────────────────────────────────────────────┘   │
│                                                                     │
│   3. Module Protection:                                            │
│   ┌────────────────────────────────────────────────────────────┐   │
│   │  ● Individual Module Fuses (500mA)                        │   │
│   │  ● Series Resistors (Protection against shorts)           │   │
│   │  ● ESD Protection (TVS Diodes)                            │   │
│   │  ● Over-voltage Clamps (Zener Diodes)                    │   │
│   └────────────────────────────────────────────────────────────┘   │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 2. Recommended Protection Components

| Component | Part Number | Value | Package | Function |
|-----------|-------------|-------|---------|----------|
| **Input Fuse** | 1812L110 | 1.1A | 1812 SMD | Over-current |
| **TVS Diode** | SMCJ18A | 18V | SMC | Over-voltage |
| **Reverse Diode** | 1N4007 | 1A/1000V | DO-41 | Reverse Polarity |
| **Ferrite Bead** | BLM21PG221 | 220Ω | 0805 | EMI Filtering |
| **Bulk Capacitor** | Electrolytic | 1000µF/25V | Through-hole | Smoothing |
| **Decoupling Cap** | Ceramic | 0.1µF/50V | 0805 | High-frequency |
| **Output Cap** | Electrolytic | 220µF/10V | Through-hole | Stability |
| **Power LED** | RED LED | 2V/20mA | 3mm | Status Indication |
| **Power Resistor** | Metal Film | 220Ω/0.25W | Through-hole | LED Current Limit |

---

## 🔋 Power Management Strategies

### 1. Power Saving Modes

```
┌─────────────────────────────────────────────────────────────────────┐
│                   POWER SAVING MODES                               │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Mode         │  Current  │  Power   │  Features Active           │
│   ─────────────┼───────────┼──────────┼────────────────────────────│
│   Full Active  │  800mA    │  4.0W    │  All sensors, comms active │
│   Normal       │  400mA    │  2.0W    │  Select sensors active     │
│   Power Save   │  150mA    │  0.75W   │  Sensors in low power      │
│   Deep Sleep   │  50mA     │  0.25W   │  RTC active, wake on int   │
│   Hibernate    │  15mA     │  0.075W  │  Minimal operation         │
│   Off          │  0mA      │  0W      │  Completely off            │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 2. Power Saving Techniques

```cpp
// Power Saving Implementation
void enterPowerSaveMode() {
    // 1. Disable non-essential modules
    disableModule(GSM_MODULE);
    disableModule(LORA_MODULE);
    disableModule(CAN_MODULE);
    
    // 2. Reduce sensor sampling rate
    sensorSamplingRate = 1000; // 1Hz
    
    // 3. Turn off LCD backlight
    lcd.setBacklight(0);
    
    // 4. Put GPS to standby
    gps.standby();
    
    // 5. Arduino sleep
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);
    sleep_enable();
    sleep_cpu();
    
    // 6. Wake on interrupt
    attachInterrupt(digitalPinToInterrupt(WAKE_PIN), wakeHandler, LOW);
}

void enterDeepSleep() {
    // 1. Disable all non-essential modules
    disableAllModules();
    
    // 2. Reduce clock speed
    CLKPR = 0x80;
    CLKPR = 0x01; // 1/2 clock
    
    // 3. Power down peripherals
    power_all_disable();
    
    // 4. Enable only RTC and wake pin
    power_timer0_enable(); // Keep RTC running
    power_timer1_disable();
    power_timer2_disable();
    power_adc_disable();
    power_spi_disable();
    power_twi_disable(); // I2C off
    power_usart0_disable(); // UART off
    
    // 5. Enter sleep
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
}
```

---

## 📊 Power Monitoring

### 1. Monitoring Circuit

```
┌─────────────────────────────────────────────────────────────────────┐
│                    POWER MONITORING CIRCUIT                        │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   ┌──────────────────────────────────────────────────────────┐    │
│   │                     Power Supply                         │    │
│   │                     12V DC Input                        │    │
│   └────────────────────────┬─────────────────────────────────┘    │
│                            │                                       │
│                            ▼                                       │
│   ┌──────────────────────────────────────────────────────────┐    │
│   │                  Voltage Divider                         │    │
│   │                  (R1=10k, R2=10k)                       │    │
│   │                  Gain = 0.5                             │    │
│   │                  Vout = Vin × 0.5                      │    │
│   └────────────────────────┬─────────────────────────────────┘    │
│                            │                                       │
│                            ▼                                       │
│   ┌──────────────────────────────────────────────────────────┐    │
│   │                   ADC Input (A1)                        │    │
│   │                  10-bit Resolution                      │    │
│   │                  Range: 0-5V                           │    │
│   └──────────────────────────────────────────────────────────┘    │
│                                                                     │
│   ┌──────────────────────────────────────────────────────────┐    │
│   │                 Current Sensor (ACS712)                  │    │
│   │                  Sensitivity: 100mV/A                   │    │
│   │                  Range: 0-20A                          │    │
│   └────────────────────────┬─────────────────────────────────┘    │
│                            │                                       │
│                            ▼                                       │
│   ┌──────────────────────────────────────────────────────────┐    │
│   │                   ADC Input (A2)                        │    │
│   │                  10-bit Resolution                      │    │
│   └──────────────────────────────────────────────────────────┘    │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 2. Monitoring Implementation

```cpp
// Power Monitoring Functions
struct PowerData {
    float voltage;
    float current;
    float power;
    float energy;
    float voltage5V;
    float voltage3V3;
    float temperature;
    unsigned long timestamp;
};

PowerData monitorPower() {
    PowerData data;
    
    // 1. Measure 12V Input Voltage
    int v12Raw = analogRead(ADC_PIN_V12);
    data.voltage = (v12Raw / 1023.0) * 5.0 * 2.0; // Voltage divider: 0.5
    
    // 2. Measure 5V Rail
    int v5Raw = analogRead(ADC_PIN_V5);
    data.voltage5V = (v5Raw / 1023.0) * 5.0;
    
    // 3. Measure 3.3V Rail
    int v33Raw = analogRead(ADC_PIN_V33);
    data.voltage3V3 = (v33Raw / 1023.0) * 5.0;
    
    // 4. Measure Current
    int currentRaw = analogRead(ADC_PIN_CURRENT);
    float currentVoltage = (currentRaw / 1023.0) * 5.0;
    data.current = (currentVoltage - 2.5) / 0.1; // ACS712: 100mV/A
    
    // 5. Calculate Power
    data.power = data.voltage * data.current;
    
    // 6. Calculate Energy
    static float totalEnergy = 0;
    totalEnergy += data.power * (millis() - lastTime) / 3600000.0; // Wh
    data.energy = totalEnergy;
    
    // 7. Measure Temperature
    int tempRaw = analogRead(ADC_PIN_TEMP);
    data.temperature = (tempRaw / 1023.0) * 5.0 * 100.0;
    
    data.timestamp = millis();
    
    return data;
}
```

---

## 🌡️ Thermal Management

### 1. Heat Dissipation

```
┌─────────────────────────────────────────────────────────────────────┐
│                     THERMAL MANAGEMENT                             │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Component              │  Max Temp │  Dissipation │  Cooling     │
│   ───────────────────────┼───────────┼──────────────┼──────────────│
│   Arduino Uno            │  85°C     │  1.0W        │  Passive     │
│   LM2596 Regulator       │  125°C    │  2.0W        │  Heatsink    │
│   AMS1117-3.3            │  85°C     │  1.0W        │  Passive     │
│   GSM SIM800L            │  85°C     │  10.0W (Peak)│  Active      │
│   LoRa SX1278            │  85°C     │  0.4W        │  Passive     │
│   Fingerprint R307       │  55°C     │  0.75W       │  Passive     │
│   Total System           │  70°C     │  15.6W (Max) │  Mixed       │
│                                                                     │
│   Heat Sink Requirements (LM2596):                                 │
│   ● Type: Aluminum finned heatsink                                │
│   ● Size: 25mm × 25mm × 10mm                                     │
│   ● Thermal Resistance: <10°C/W                                  │
│   ● Mounting: TO-220 package                                     │
│                                                                     │
│   Enclosure Cooling:                                               │
│   ● Ventilation holes required                                     │
│   ● Minimum 2cm spacing around components                         │
│   ● Forced air cooling if GSM used frequently                     │
│   ● Avoid direct sunlight                                         │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 2. Temperature Monitoring

```cpp
// Temperature Monitoring Function
float readTemperature(int pin) {
    // LM35 temperature sensor on ADC pin
    int raw = analogRead(pin);
    float voltage = (raw / 1023.0) * 5.0;
    float tempC = voltage * 100.0; // LM35: 10mV/°C
    return tempC;
}

void monitorTemperatures() {
    float tempCPU = readTemperature(TEMP_SENSOR_CPU);
    float tempGSM = readTemperature(TEMP_SENSOR_GSM);
    float tempAmbient = readTemperature(TEMP_SENSOR_AMBIENT);
    
    // Check thresholds
    if (tempGSM > 80.0) {
        Serial.println("WARNING: GSM module overheating!");
        // Reduce GSM usage or activate cooling
    }
    
    if (tempCPU > 70.0) {
        Serial.println("WARNING: CPU overheating!");
        // Enter power save mode
        enterPowerSaveMode();
    }
}
```

---

## 📐 Power Supply Design Guidelines

### 1. PCB Design Rules

```
┌─────────────────────────────────────────────────────────────────────┐
│                   PCB POWER DESIGN GUIDELINES                      │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Rule                             │  Requirement                   │
│   ─────────────────────────────────┼────────────────────────────────│
│   Power Trace Width (5V)           │  2mm (1A) / 3mm (2A)         │
│   Power Trace Width (3.3V)         │  1mm (0.5A) / 2mm (1A)       │
│   Power Trace Width (12V Input)    │  2mm (2A)                     │
│   Ground Plane                     │  Solid copper (preferred)    │
│   Decoupling Capacitors            │  <10mm from ICs              │
│   PCB Copper Weight                │  2oz (preferred)             │
│   Thermal Vias for Regulators      │  4-6 vias                    │
│   Input Filtering                  │  Ferrite bead + capacitor    │
│   Power Supply Separations         │  Analog/Digital split        │
│   Return Paths                     │  Shortest possible           │
│   Glue Components                  │  For heavy components        │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 2. Component Selection Guidelines

```
┌─────────────────────────────────────────────────────────────────────┐
│                   COMPONENT SELECTION GUIDELINES                   │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Component              │  Rating        │  Derating              │
│   ───────────────────────┼────────────────┼────────────────────────│
│   Capacitors             │  25V (for 12V) │  80% of rated voltage  │
│   Fuses                  │  2A            │  80% of rated current  │
│   Diodes                 │  1A/100V       │  80% of rated current  │
│   Resistors              │  0.25W         │  50% of rated power    │
│   TVS Diodes             │  18V           │  Clamp > VIN max       │
│   Inductors              │  3A            │  80% of rated current  │
│   Connectors             │  5A            │  Oversized for safety  │
│   PCB Traces             │  3A/mm²        │  70% of current limit  │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## ⚡ Power Quality Recommendations

### 1. Input Power Quality

```
┌─────────────────────────────────────────────────────────────────────┐
│                   POWER QUALITY REQUIREMENTS                       │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Parameter              │  Minimum  │  Typical   │  Maximum       │
│   ───────────────────────┼───────────┼────────────┼────────────────│
│   Voltage Tolerance      │  -10%     │  ±5%       │  +10%          │
│   Frequency              │  50Hz     │  60Hz      │  60Hz          │
│   Ripple & Noise (5V)    │  -        │  50mV      │  100mV         │
│   Ripple & Noise (3.3V)  │  -        │  30mV      │  50mV          │
│   Transient Response     │  -        │  100µs     │  500µs         │
│   Line Regulation        │  -        │  0.5%      │  2%            │
│   Load Regulation        │  -        │  1%        │  3%            │
│   Efficiency             │  75%      │  85%       │  95%           │
│   PSRR (5V)              │  60dB     │  70dB      │  80dB          │
│   Inrush Current         │  -        │  1A        │  3A            │
│   Hold-up Time           │  10ms     │  20ms      │  -             │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 2. Noise Reduction Techniques

```
┌─────────────────────────────────────────────────────────────────────┐
│                   NOISE REDUCTION TECHNIQUES                       │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   1. Input Filtering:                                              │
│   ● LC Filter (10µH + 10µF)                                       │
│   ● EMI Filter (Common mode choke)                                │
│   ● Ferrite Bead on input power line                              │
│   ● Bulk capacitor (1000µF) near input                            │
│                                                                     │
│   2. Voltage Regulation:                                           │
│   ● Use linear regulator for sensitive circuits                   │
│   ● Use low ESR capacitors on outputs                             │
│   ● Separate analog and digital grounds                           │
│   ● Star grounding configuration                                   │
│                                                                     │
│   3. PCB Layout:                                                   │
│   ● Keep high-current paths short                                 │
│   ● Minimize ground loops                                         │
│   ● Use ground planes for shielding                               │
│   ● Separate noisy and sensitive traces                           │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 📊 Power Budget Calculator

### Complete Power Budget Table

```
┌─────────────────────────────────────────────────────────────────────┐
│                     POWER BUDGET CALCULATOR                        │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module          │  Current  │  Power   │  Duty    │  Average    │
│                   │   (mA)    │   (W)    │  Cycle   │   Power     │
│   ────────────────┼───────────┼──────────┼──────────┼─────────────│
│   Arduino Uno     │  200      │  1.000   │  100%    │  1.000W     │
│   LiDAR VL53L0X   │  20       │  0.066   │  20%     │  0.013W     │
│   GPS NEO-6M      │  50       │  0.250   │  50%     │  0.125W     │
│   Fingerprint     │  80       │  0.400   │  5%      │  0.020W     │
│   RFID MFRC522    │  50       │  0.165   │  10%     │  0.017W     │
│   CAN MCP2515     │  60       │  0.300   │  20%     │  0.060W     │
│   LoRa SX1278 (RX)│  40       │  0.132   │  30%     │  0.040W     │
│   LoRa SX1278 (TX)│  120      │  0.396   │  1%      │  0.004W     │
│   GSM SIM800L (ID)│  200      │  1.000   │  80%     │  0.800W     │
│   GSM SIM800L (TX)│  2000     │  10.000  │  2%      │  0.200W     │
│   LCD Display     │  50       │  0.250   │  100%    │  0.250W     │
│   SD Card Module  │  50       │  0.250   │  10%     │  0.025W     │
│   RTC DS3231      │  5        │  0.017   │  100%    │  0.017W     │
│   Total Average   │  -        │  -       │  -       │  2.57W      │
│   Total Peak      │  -        │  -       │  -       │  14.55W     │
│                                                                     │
│   Power Supply Requirements:                                       │
│   ─────────────────────────────────────────────────────────────────│
│   Average Current: 2.57W / 5V = 514mA                             │
│   Peak Current: 14.55W / 5V = 2.91A                               │
│   Recommended PSU: 5V @ 3A (15W) or 12V @ 2A (24W)              │
│   Safety Margin: 30%                                              │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 🔗 Related Documentation

- [Wiring Diagram](wiring_diagram.md)
- [Pin Configuration](pin_configuration.md)
- [Build & Deployment Guide](../BUILD_DEPLOY.md)
- [Troubleshooting Guide](../guides/troubleshooting.md)

---

