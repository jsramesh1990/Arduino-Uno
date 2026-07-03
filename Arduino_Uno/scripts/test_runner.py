#!/usr/bin/env python3
"""
Test Runner for Arduino Multi-Sensor Platform
Automates testing, data collection, and reporting
"""

import serial
import time
import json
import csv
import os
import sys
import argparse
from datetime import datetime
from typing import List, Dict, Any

class ArduinoTestRunner:
    def __init__(self, port: str, baudrate: int = 115200):
        self.port = port
        self.baudrate = baudrate
        self.serial = None
        self.test_results = []
        self.start_time = None
        
    def connect(self) -> bool:
        """Establish connection to Arduino"""
        try:
            self.serial = serial.Serial(self.port, self.baudrate, timeout=2)
            time.sleep(2)
            print(f"Connected to {self.port}")
            return True
        except Exception as e:
            print(f"Connection failed: {e}")
            return False
    
    def send_command(self, command: str) -> str:
        """Send command to Arduino and get response"""
        if not self.serial:
            return ""
        
        self.serial.write((command + "\n").encode())
        time.sleep(0.5)
        
        response = ""
        while self.serial.in_waiting:
            response += self.serial.readline().decode()
        
        return response
    
    def run_all_tests(self) -> Dict[str, Any]:
        """Run all tests and collect results"""
        print("Running all tests...")
        self.start_time = datetime.now()
        
        # Send test command
        response = self.send_command("TEST_ALL")
        
        # Parse results
        results = self.parse_results(response)
        results["timestamp"] = self.start_time.isoformat()
        results["duration"] = (datetime.now() - self.start_time).total_seconds()
        
        return results
    
    def run_individual_test(self, test_name: str) -> Dict[str, Any]:
        """Run individual test"""
        print(f"Running {test_name} test...")
        response = self.send_command(f"TEST_{test_name.upper()}")
        return self.parse_results(response)
    
    def parse_results(self, response: str) -> Dict[str, Any]:
        """Parse test results from Arduino response"""
        results = {}
        
        lines = response.split('\n')
        for line in lines:
            if ':' in line:
                key, value = line.strip().split(':', 1)
                results[key.strip()] = value.strip()
        
        return results
    
    def save_results_json(self, results: Dict[str, Any], filename: str = None):
        """Save results in JSON format"""
        if not filename:
            filename = f"test_results_{datetime.now().strftime('%Y%m%d_%H%M%S')}.json"
        
        with open(filename, 'w') as f:
            json.dump(results, f, indent=2)
        
        print(f"Results saved to {filename}")
    
    def save_results_csv(self, results: List[Dict[str, Any]], filename: str = None):
        """Save results in CSV format"""
        if not filename:
            filename = f"test_results_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"
        
        if results:
            keys = results[0].keys()
            with open(filename, 'w', newline='') as f:
                writer = csv.DictWriter(f, fieldnames=keys)
                writer.writeheader()
                writer.writerows(results)
            
            print(f"Results saved to {filename}")
    
    def generate_report(self, results: Dict[str, Any]) -> str:
        """Generate test report"""
        report = f"""
===========================================
    ARDUINO TEST REPORT
===========================================
Timestamp: {results.get('timestamp', 'N/A')}
Duration: {results.get('duration', 0):.2f}s
===========================================
RESULTS SUMMARY
-------------------------------------------
GPIO Test:      {results.get('GPIO', 'FAIL')}
UART Test:      {results.get('UART', 'FAIL')}
I2C Test:       {results.get('I2C', 'FAIL')}
SPI Test:       {results.get('SPI', 'FAIL')}
PWM Test:       {results.get('PWM', 'FAIL')}
ADC Test:       {results.get('ADC', 'FAIL')}
Power Test:     {results.get('POWER', 'FAIL')}
-------------------------------------------
ADC Accuracy:   {results.get('ADC Accuracy', 'N/A')}
Power Consumption: {results.get('Power Cons.', 'N/A')}
===========================================
        """
        return report
    
    def disconnect(self):
        """Close serial connection"""
        if self.serial and self.serial.is_open:
            self.serial.close()
            print("Disconnected from Arduino")

def main():
    parser = argparse.ArgumentParser(description='Arduino Test Runner')
    parser.add_argument('-p', '--port', required=True, help='Serial port (e.g., COM3 or /dev/ttyUSB0)')
    parser.add_argument('-b', '--baudrate', type=int, default=115200, help='Baud rate')
    parser.add_argument('-t', '--test', help='Specific test to run (all, gpio, uart, i2c, spi, pwm, adc, power)')
    parser.add_argument('-o', '--output', help='Output file prefix')
    parser.add_argument('-f', '--format', choices=['json', 'csv', 'both'], default='both', help='Output format')
    
    args = parser.parse_args()
    
    runner = ArduinoTestRunner(args.port, args.baudrate)
    
    try:
        if runner.connect():
            if args.test and args.test.lower() != 'all':
                # Run individual test
                results = runner.run_individual_test(args.test)
                report = runner.generate_report(results)
                print(report)
                
                if args.format in ['json', 'both']:
                    runner.save_results_json(results, f"{args.output or 'test'}_test.json")
                if args.format in ['csv', 'both']:
                    runner.save_results_csv([results], f"{args.output or 'test'}_test.csv")
            else:
                # Run all tests
                results = runner.run_all_tests()
                report = runner.generate_report(results)
                print(report)
                
                if args.format in ['json', 'both']:
                    runner.save_results_json(results, f"{args.output or 'test_results'}.json")
                if args.format in ['csv', 'both']:
                    # Convert to list for CSV
                    runner.save_results_csv([results], f"{args.output or 'test_results'}.csv")
        else:
            print("Failed to connect to Arduino")
            sys.exit(1)
            
    except KeyboardInterrupt:
        print("\nTest interrupted by user")
    finally:
        runner.disconnect()

if __name__ == "__main__":
    main()
