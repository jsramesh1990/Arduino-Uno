# docs/hardware/pin_configuration.md

# Pin Configuration - Arduino Multi-Sensor Platform

## 📊 Complete Pin Configuration Guide

This document provides detailed pin configuration for all modules in the Arduino Multi-Sensor Platform project.

---

## 🔌 Arduino Uno Pin Mapping

### Complete Pinout Reference

```
┌─────────────────────────────────────────────────────────────────────┐
│                      ARDUINO UNO PINOUT                            │
│                    (ATmega328P - DIP Package)                      │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   ┌───────────────────────────────────────────────────────────┐    │
│   │                                                           │    │
│   │   PC6 ── 1 │                                        28 ── PC5 │    │
│   │   PD0 ── 2 │                                        27 ── PC4 │    │
│   │   PD1 ── 3 │                                        26 ── PC3 │    │
│   │   PD2 ── 4 │                                        25 ── PC2 │    │
│   │   PD3 ── 5 │                                        24 ── PC1 │    │
│   │   PD4 ── 6 │                                        23 ── PC0 │    │
│   │   VCC ── 7 │                                        22 ── GND │    │
│   │   GND ── 8 │                                        21 ── AREF │    │
│   │   PB6 ── 9 │                                        20 ── AVCC │    │
│   │   PB7 ──10 │                                        19 ── PB5  │    │
│   │   PD5 ──11 │                                        18 ── PB4  │    │
│   │   PD6 ──12 │                                        17 ── PB3  │    │
│   │   PD7 ──13 │                                        16 ── PB2  │    │
│   │   PB0 ──14 │                                        15 ── PB1  │    │
│   │                                                           │    │
│   └───────────────────────────────────────────────────────────┘    │
│                                                                     │
│   Legend:                                                          │
│   ● PC0-PC5: Analog Inputs (A0-A5)                                 │
│   ● PD0-PD7: Digital I/O (D0-D7)                                   │
│   ● PB0-PB7: Digital I/O (D8-D13)                                  │
│   ● Special: INT0-INT1, PWM, SPI, UART                            │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 📋 Detailed Pin Configuration Tables

### 1. Digital I/O Pins Configuration

| Pin | Name | Function | Direction | Pull-up | Used By | Alternate Function |
|-----|------|----------|-----------|---------|---------|-------------------|
| D0 | PD0 | RX | Input | Disabled | GPS Module | UART RX |
| D1 | PD1 | TX | Output | Disabled | GPS Module | UART TX |
| D2 | PD2 | Interrupt 0 | Input | Enabled | LoRa DIO0 | External Interrupt |
| D3 | PD3 | Interrupt 1 | Input | Enabled | GPS TX (SW) | External Interrupt |
| D4 | PD4 | Digital I/O | Input | Enabled | GPS RX (SW) | GPIO |
| D5 | PD5 | Digital I/O | Input | Enabled | Finger RX (SW) | GPIO |
| D6 | PD6 | Digital I/O | Output | Disabled | Finger TX (SW) | GPIO |
| D7 | PD7 | Digital I/O | Input | Enabled | GSM RX (SW) | GPIO |
| D8 | PB0 | Digital I/O | Output | Disabled | GSM TX (SW) / LoRa RST | GPIO |
| D9 | PB1 | PWM | Output | Disabled | PWM Out / RFID RST | Timer1 PWM |
| D10 | PB2 | SPI SS | Input | Disabled | SPI Chip Select | SPI Slave Select |
| D11 | PB3 | SPI MOSI | Output | Disabled | SPI Master Out | SPI Data |
| D12 | PB4 | SPI MISO | Input | Disabled | SPI Master In | SPI Data |
| D13 | PB5 | SPI SCK | Output | Disabled | SPI Clock | SPI Clock |

### 2. Analog Input Pins Configuration

| Pin | Name | Function | Resolution | Used By | Features |
|-----|------|----------|------------|---------|----------|
| A0 | PC0 | ADC Input | 10-bit | Analog Sensor Input | Differential Input |
| A1 | PC1 | ADC Input | 10-bit | Power Test | Differential Input |
| A2 | PC2 | ADC Input | 10-bit | Current Sense | Differential Input |
| A3 | PC3 | ADC Input | 10-bit | Temperature Sensor | Differential Input |
| A4 | PC4 | I2C SDA | - | I2C Data Bus | I2C Data Line |
| A5 | PC5 | I2C SCL | - | I2C Clock Bus | I2C Clock Line |

### 3. Power Pins Configuration

| Pin | Name | Voltage | Current | Used By | Notes |
|-----|------|---------|---------|---------|-------|
| VIN | Power Input | 7-12V | 2A | System Power | Power Supply Input |
| 5V | 5V Output | 5V | 500mA | 5V Modules | Regulated Output |
| 3.3V | 3.3V Output | 3.3V | 50mA | 3.3V Modules | Regulated Output |
| GND | Ground | 0V | - | All Modules | Common Ground |
| AREF | ADC Reference | 0-5V | - | ADC | Voltage Reference |

---

## 🧩 Module-Specific Pin Configurations

### 1. LiDAR Sensor (VL53L0X) - I2C Interface

```
┌─────────────────────────────────────────────────────────────────────┐
│                    VL53L0X LiDAR Sensor                            │
│                    I2C Interface Configuration                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module Pin    │  Arduino Pin  │  Signal   │  Description        │
│   ──────────────┼───────────────┼───────────┼─────────────────────│
│   VIN           │  5V           │  Power    │  2.8-5V DC          │
│   GND           │  GND          │  Ground   │  Common Ground      │
│   SCL           │  A5 (SCL)     │  Clock    │  I2C Clock (100kHz) │
│   SDA           │  A4 (SDA)     │  Data     │  I2C Data           │
│   XSHUT         │  D8           │  Shutdown │  Active Low Reset   │
│   GPIO1         │  D2           │  Interrupt│  Interrupt Output   │
│                                                                     │
│   I2C Address:  0x29 (Default)                                    │
│   Speed:        100kHz (Standard) / 400kHz (Fast)                 │
│   Pull-ups:     4.7kΩ on SDA and SCL                              │
│                                                                     │
│   Configuration Registers:                                         │
│   ● 0x00:  Identification Register                                 │
│   ● 0x01:  System Status                                          │
│   ● 0x02:  Result Value                                           │
│   ● 0x03:  Configuration Register                                 │
│   ● 0x04:  Interrupt Configuration                                │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 2. GPS Module (NEO-6M) - UART Interface

```
┌─────────────────────────────────────────────────────────────────────┐
│                      NEO-6M GPS Module                             │
│                    UART Interface Configuration                    │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module Pin    │  Arduino Pin  │  Signal   │  Description        │
│   ──────────────┼───────────────┼───────────┼─────────────────────│
│   VCC           │  5V           │  Power    │  3.3-5V DC          │
│   GND           │  GND          │  Ground   │  Common Ground      │
│   TX            │  D4           │  Data Out │  UART TX (5V Level) │
│   RX            │  D3           │  Data In  │  UART RX (5V Level) │
│   PPS           │  D2           │  PPS      │  Pulse Per Second   │
│                                                                     │
│   Communication Settings:                                          │
│   Baud Rate:    9600 bps (Default)                                 │
│   Data Bits:    8                                                  │
│   Stop Bits:    1                                                  │
│   Parity:       None                                               │
│   Flow Control: None                                               │
│                                                                     │
│   NMEA Sentences:                                                  │
│   ● GGA: Global Positioning System Fix Data                       │
│   ● GLL: Geographic Position - Latitude/Longitude                 │
│   ● GSA: GNSS DOP and Active Satellites                           │
│   ● GSV: GNSS Satellites in View                                  │
│   ● RMC: Recommended Minimum Specific GNSS Data                   │
│   ● VTG: Course Over Ground and Ground Speed                      │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 3. Fingerprint Sensor (R307) - UART Interface

```
┌─────────────────────────────────────────────────────────────────────┐
│                    R307 Fingerprint Sensor                         │
│                    UART Interface Configuration                    │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module Pin    │  Arduino Pin  │  Signal   │  Description        │
│   ──────────────┼───────────────┼───────────┼─────────────────────│
│   VCC           │  5V           │  Power    │  5V DC              │
│   GND           │  GND          │  Ground   │  Common Ground      │
│   TX            │  D5           │  Data Out │  UART TX            │
│   RX            │  D6           │  Data In  │  UART RX            │
│   Touch         │  D7           │  Touch    │  Touch Sensor Input │
│                                                                     │
│   Communication Settings:                                          │
│   Baud Rate:    57600 bps                                          │
│   Data Bits:    8                                                  │
│   Stop Bits:    1                                                  │
│   Parity:       None                                               │
│   Flow Control: None                                               │
│                                                                     │
│   Commands:                                                        │
│   ● 0x01:  Get Image                                              │
│   ● 0x02:  Extract Features                                       │
│   ● 0x03:  Search Fingerprint                                     │
│   ● 0x04:  Match Fingerprint                                      │
│   ● 0x05:  Capture Fingerprint                                    │
│   ● 0x06:  Delete Template                                        │
│   ● 0x07:  Clear Database                                         │
│   ● 0x08:  Get Database Size                                      │
│   ● 0x09:  Set Security Level                                     │
│   ● 0x0A:  Get Security Level                                     │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 4. RFID/NFC Reader (MFRC522) - SPI Interface

```
┌─────────────────────────────────────────────────────────────────────┐
│                     MFRC522 RFID/NFC Reader                        │
│                    SPI Interface Configuration                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module Pin    │  Arduino Pin  │  Signal   │  Description        │
│   ──────────────┼───────────────┼───────────┼─────────────────────│
│   VCC           │  3.3V         │  Power    │  3.3V DC            │
│   GND           │  GND          │  Ground   │  Common Ground      │
│   RST           │  D9           │  Reset    │  Active Low Reset   │
│   SDA/SS        │  D10          │  Chip Sel │  SPI Chip Select    │
│   MOSI          │  D11          │  Data Out │  SPI Master Out     │
│   MISO          │  D12          │  Data In  │  SPI Master In      │
│   SCK           │  D13          │  Clock    │  SPI Clock          │
│   IRQ           │  D2           │  Interrupt│  Interrupt Output   │
│                                                                     │
│   SPI Settings:                                                    │
│   Speed:        10MHz (Max)                                       │
│   Mode:         0 (CPOL=0, CPHA=0)                                │
│   Data Order:   MSB First                                         │
│   Chip Select:  Active Low                                        │
│                                                                     │
│   Supported Tags:                                                 │
│   ● MIFARE Classic 1K/4K                                         │
│   ● MIFARE Ultralight                                             │
│   ● MIFARE DESFire                                                │
│   ● NFC Forum Type 2/3/4                                          │
│   ● ISO 14443A/B                                                 │
│   ● FeliCa                                                        │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 5. CAN Bus Module (MCP2515) - SPI Interface

```
┌─────────────────────────────────────────────────────────────────────┐
│                     MCP2515 CAN Bus Module                         │
│                    SPI Interface Configuration                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module Pin    │  Arduino Pin  │  Signal   │  Description        │
│   ──────────────┼───────────────┼───────────┼─────────────────────│
│   VCC           │  5V           │  Power    │  5V DC              │
│   GND           │  GND          │  Ground   │  Common Ground      │
│   CS            │  D10          │  Chip Sel │  SPI Chip Select    │
│   SI            │  D11          │  Data In  │  SPI Master Out     │
│   SO            │  D12          │  Data Out │  SPI Master In      │
│   SCK           │  D13          │  Clock    │  SPI Clock          │
│   INT           │  D2           │  Interrupt│  Interrupt Output   │
│   CAN_H         │  -            │  CAN High │  CAN Bus High Line  │
│   CAN_L         │  -            │  CAN Low  │  CAN Bus Low Line   │
│                                                                     │
│   SPI Settings:                                                    │
│   Speed:        10MHz (Max)                                       │
│   Mode:         0,0                                               │
│   Data Order:   MSB First                                         │
│   Chip Select:  Active Low                                        │
│                                                                     │
│   CAN Settings:                                                    │
│   Speed:        500kbps (Default)                                 │
│   Mode:        Normal                                             │
│   ID Type:     Standard (11-bit) / Extended (29-bit)              │
│   Filter:      Configurable                                       │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 6. LoRa Module (SX1278) - SPI Interface

```
┌─────────────────────────────────────────────────────────────────────┐
│                     SX1278 LoRa Module                             │
│                    SPI Interface Configuration                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module Pin    │  Arduino Pin  │  Signal   │  Description        │
│   ──────────────┼───────────────┼───────────┼─────────────────────│
│   VCC           │  3.3V         │  Power    │  3.3V DC            │
│   GND           │  GND          │  Ground   │  Common Ground      │
│   NSS           │  D10          │  Chip Sel │  SPI Chip Select    │
│   MOSI          │  D11          │  Data Out │  SPI Master Out     │
│   MISO          │  D12          │  Data In  │  SPI Master In      │
│   SCK           │  D13          │  Clock    │  SPI Clock          │
│   RST           │  D8           │  Reset    │  Active Low Reset   │
│   DIO0          │  D2           │  Interrupt│  Interrupt 0        │
│   DIO1          │  D3           │  Interrupt│  Interrupt 1 (Opt)  │
│   DIO2          │  -            │  Interrupt│  Interrupt 2 (Opt)  │
│   DIO3          │  -            │  Interrupt│  Interrupt 3 (Opt)  │
│   DIO4          │  -            │  Interrupt│  Interrupt 4 (Opt)  │
│   DIO5          │  -            │  Interrupt│  Interrupt 5 (Opt)  │
│   ANT           │  -            │  Antenna  │  RF Output          │
│                                                                     │
│   SPI Settings:                                                    │
│   Speed:        10MHz (Max)                                       │
│   Mode:         0,0                                               │
│   Data Order:   MSB First                                         │
│                                                                     │
│   RF Settings:                                                     │
│   Frequency:    868MHz (EU) / 915MHz (US)                         │
│   Bandwidth:    125kHz                                            │
│   Spreading Factor: 12                                            │
│   Coding Rate:   4/5                                              │
│   TX Power:     20dBm (Max)                                      │
│   Sensitivity:  -148dBm (SF12)                                    │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 7. GSM/GPRS Module (SIM800L) - UART Interface

```
┌─────────────────────────────────────────────────────────────────────┐
│                     SIM800L GSM/GPRS Module                        │
│                    UART Interface Configuration                    │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module Pin    │  Arduino Pin  │  Signal   │  Description        │
│   ──────────────┼───────────────┼───────────┼─────────────────────│
│   VCC           │  5V           │  Power    │  3.7-4.2V DC        │
│   GND           │  GND          │  Ground   │  Common Ground      │
│   TX            │  D7           │  Data Out │  UART TX            │
│   RX            │  D8           │  Data In  │  UART RX            │
│   RST           │  D5           │  Reset    │  Active Low Reset   │
│   PWR           │  D6           │  Power On │  Active Low Enable  │
│   NET           │  -            │  Network  │  Network Status LED │
│   ANT           │  -            │  Antenna  │  GSM Antenna        │
│                                                                     │
│   Communication Settings:                                          │
│   Baud Rate:    9600 bps (Default)                                 │
│   Data Bits:    8                                                  │
│   Stop Bits:    1                                                  │
│   Parity:       None                                               │
│   Flow Control: Hardware (Optional)                                │
│                                                                     │
│   AT Commands:                                                     │
│   ● AT:        Check Communication                                 │
│   ● AT+CSQ:    Signal Quality                                      │
│   ● AT+COPS?:  Network Operator                                   │
│   ● AT+CSTT:   Set APN                                            │
│   ● AT+CIICR:  Activate Bearer                                    │
│   ● AT+CIFSR:  Get IP Address                                     │
│   ● AT+CIPSTART: Start Connection                                 │
│   ● AT+CIPSEND: Send Data                                         │
│   ● AT+CIPCLOSE: Close Connection                                 │
│   ● AT+CIPSHUT: Shutdown Network                                  │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 8. LCD Display (16x2 I2C) - I2C Interface

```
┌─────────────────────────────────────────────────────────────────────┐
│                    16x2 LCD Display (I2C)                          │
│                    I2C Interface Configuration                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module Pin    │  Arduino Pin  │  Signal   │  Description        │
│   ──────────────┼───────────────┼───────────┼─────────────────────│
│   VCC           │  5V           │  Power    │  5V DC              │
│   GND           │  GND          │  Ground   │  Common Ground      │
│   SDA           │  A4 (SDA)     │  Data     │  I2C Data           │
│   SCL           │  A5 (SCL)     │  Clock    │  I2C Clock          │
│                                                                     │
│   I2C Address:  0x27 or 0x3F (Check with scanner)                │
│   Display Type: 16x2 Characters                                   │
│   Backlight:    Blue/White (Configurable)                         │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 9. SD Card Module - SPI Interface

```
┌─────────────────────────────────────────────────────────────────────┐
│                      SD Card Module                                │
│                    SPI Interface Configuration                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module Pin    │  Arduino Pin  │  Signal   │  Description        │
│   ──────────────┼───────────────┼───────────┼─────────────────────│
│   VCC           │  5V           │  Power    │  5V DC              │
│   GND           │  GND          │  Ground   │  Common Ground      │
│   CS            │  D10          │  Chip Sel │  SPI Chip Select    │
│   MOSI          │  D11          │  Data Out │  SPI Master Out     │
│   MISO          │  D12          │  Data In  │  SPI Master In      │
│   SCK           │  D13          │  Clock    │  SPI Clock          │
│                                                                     │
│   SPI Settings:                                                    │
│   Speed:        4MHz (Max)                                        │
│   Mode:         0,0                                               │
│   Data Order:   MSB First                                         │
│   Chip Select:  Active Low                                        │
│                                                                     │
│   File System:  FAT16/FAT32                                       │
│   Max Capacity: 32GB                                              │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

### 10. RTC Module (DS3231) - I2C Interface

```
┌─────────────────────────────────────────────────────────────────────┐
│                      DS3231 RTC Module                             │
│                    I2C Interface Configuration                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Module Pin    │  Arduino Pin  │  Signal   │  Description        │
│   ──────────────┼───────────────┼───────────┼─────────────────────│
│   VCC           │  5V           │  Power    │  5V DC              │
│   GND           │  GND          │  Ground   │  Common Ground      │
│   SDA           │  A4 (SDA)     │  Data     │  I2C Data           │
│   SCL           │  A5 (SCL)     │  Clock    │  I2C Clock          │
│   SQW           │  D2           │  Square   │  Square Wave Output │
│   32K           │  -            │  32kHz    │  32.768kHz Output   │
│   VBAT          │  -            │  Battery  │  Backup Battery     │
│                                                                     │
│   I2C Address:  0x68 (Default)                                   │
│   Battery:      CR2032 3V Lithium                                 │
│   Accuracy:     ±2ppm (0-40°C)                                    │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 📊 Pin Function Summary Table

### Digital/Analog Pin Functions

```
┌─────────────────────────────────────────────────────────────────────┐
│                   COMPLETE PIN FUNCTION SUMMARY                    │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Pin │ Primary Function │ Secondary  │ Used By      │ Type       │
│   ────┼──────────────────┼────────────┼──────────────┼────────────│
│   D0  │ RX (UART)        │ GPIO       │ GPS TX       │ Digital In │
│   D1  │ TX (UART)        │ GPIO       │ GPS RX       │ Digital Out│
│   D2  │ INT0             │ GPIO       │ LoRa DIO0    │ Interrupt  │
│   D3  │ INT1             │ GPIO       │ GPS TX (SW)  │ Interrupt  │
│   D4  │ GPIO             │ -          │ GPS RX (SW)  │ Digital In │
│   D5  │ GPIO             │ -          │ Finger RX    │ Digital In │
│   D6  │ GPIO             │ -          │ Finger TX    │ Digital Out│
│   D7  │ GPIO             │ -          │ GSM RX       │ Digital In │
│   D8  │ GPIO             │ -          │ GSM TX/LoRa  │ Digital Out│
│   D9  │ PWM              │ GPIO       │ PWM Out      │ Analog Out │
│   D10 │ SS (SPI)         │ GPIO       │ SPI CS       │ Digital I/O│
│   D11 │ MOSI (SPI)       │ GPIO       │ SPI MOSI     │ Digital Out│
│   D12 │ MISO (SPI)       │ GPIO       │ SPI MISO     │ Digital In │
│   D13 │ SCK (SPI)        │ GPIO       │ SPI SCK      │ Digital Out│
│   A0  │ ADC0             │ GPIO       │ Sensor Input │ Analog In  │
│   A1  │ ADC1             │ GPIO       │ Power Test   │ Analog In  │
│   A2  │ ADC2             │ GPIO       │ Current Sense│ Analog In  │
│   A3  │ ADC3             │ GPIO       │ Temperature  │ Analog In  │
│   A4  │ SDA (I2C)        │ ADC4       │ I2C Data     │ Digital I/O│
│   A5  │ SCL (I2C)        │ ADC5       │ I2C Clock    │ Digital I/O│
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 🔧 Configuration Jumper Settings

### Hardware Jumper Configurations

```
┌─────────────────────────────────────────────────────────────────────┐
│                  CONFIGURATION JUMPER SETTINGS                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Jumper  │  Default  │  Option 1  │  Option 2  │  Function       │
│   ────────┼───────────┼────────────┼────────────┼─────────────────│
│   J1      │  1-2      │  2-3       │  Open      │  I2C Pull-up    │
│   J2      │  Enable   │  Disable   │  -         │  5V Enable      │
│   J3      │  Enable   │  Disable   │  -         │  3.3V Enable    │
│   J4      │  Normal   │  Program   │  -         │  Boot Mode      │
│   J5      │  SPI      │  I2C       │  -         │  RFID Interface │
│   J6      │  Serial   │  Debug     │  -         │  UART Mode      │
│   J7      │  Can On   │  Can Off   │  -         │  CAN Enable     │
│   J8      │  Normal   │  Reset     │  -         │  LoRa Mode      │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## ⚡ Electrical Characteristics

### Pin Electrical Specifications

```
┌─────────────────────────────────────────────────────────────────────┐
│                   PIN ELECTRICAL CHARACTERISTICS                   │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   Parameter          │  Min     │  Typ     │  Max     │  Unit      │
│   ───────────────────┼──────────┼──────────┼──────────┼────────────│
│   Input High Voltage │  3.0     │  5.0     │  5.5     │  V         │
│   Input Low Voltage  │  -0.5    │  0       │  1.5     │  V         │
│   Output High Voltage│  4.2     │  4.8     │  5.0     │  V         │
│   Output Low Voltage │  0       │  0.1     │  0.4     │  V         │
│   Input Current      │  -10     │  0       │  10      │  µA        │
│   Output Current     │  -40     │  20      │  40      │  mA        │
│   Pin Capacitance    │  -       │  10      │  -       │  pF        │
│   Sink Current       │  -       │  20      │  40      │  mA        │
│   Source Current     │  -       │  10      │  20      │  mA        │
│   Pull-up Resistor   │  20      │  35      │  50      │  kΩ        │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 🎯 Pin Usage Recommendations

### Best Practices

```
┌─────────────────────────────────────────────────────────────────────┐
│                     PIN USAGE RECOMMENDATIONS                      │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   1. I2C Bus:                                                      │
│   ✓ Use 4.7kΩ pull-up resistors                                   │
│   ✓ Keep SDA/SCL lines short                                      │
│   ✓ Use twisted pair for long runs                                │
│   ✓ Add series resistors (100Ω) for noise immunity               │
│                                                                     │
│   2. SPI Bus:                                                      │
│   ✓ Use separate CS pins for each device                          │
│   ✓ Match clock speed to device capabilities                     │
│   ✓ Use proper termination                                         │
│   ✓ Keep MISO/MOSI lines short                                    │
│                                                                     │
│   3. UART:                                                         │
│   ✓ Use 5V level shifters for 3.3V devices                        │
│   ✓ Add protection diodes                                         │
│   ✓ Use proper baud rate matching                                 │
│   ✓ Enable hardware flow control if possible                      │
│                                                                     │
│   4. Analog Inputs:                                                │
│   ✓ Use 100nF capacitor for noise filtering                       │
│   ✓ Keep traces short                                            │
│   ✓ Use separate ground for analog                                │
│   ✓ Add protection diodes                                         │
│                                                                     │
│   5. PWM:                                                         │
│   ✓ Use appropriate frequency                                     │
│   ✓ Add low-pass filter if needed                                 │
│   ✓ Use proper drive strength                                     │
│   ✓ Consider opto-isolation                                      │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 📝 Pin Configuration Checklist

```
┌─────────────────────────────────────────────────────────────────────┐
│                  PIN CONFIGURATION CHECKLIST                       │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│   □ Power Pins Connected                                           │
│   □ Ground Connections Verified                                    │
│   □ I2C Pull-up Resistors Installed                                │
│   □ SPI Pins Correctly Assigned                                    │
│   □ UART Connections Properly Wired                               │
│   □ Interrupt Pins Configured                                     │
│   □ PWM Pins Connected                                            │
│   □ ADC Pins Connected                                            │
│   □ All Jumpers Set Correctly                                     │
│   □ No Pin Conflicts                                              │
│   □ Signal Levels Compatible                                      │
│   □ Termination Resistors Present (CAN Bus)                       │
│   □ Antenna Connections Secure                                    │
│   □ Module Addresses Unique (I2C)                                 │
│   □ Chip Select Pins Configured (SPI)                             │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 🔗 Related Documentation

- [Wiring Diagram](wiring_diagram.md)
- [Power Requirements](power_requirements.md)
- [Build & Deployment Guide](../BUILD_DEPLOY.md)
- [Troubleshooting Guide](../guides/troubleshooting.md)

---

