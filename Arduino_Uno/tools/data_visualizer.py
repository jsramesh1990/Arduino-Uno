#!/usr/bin/env python3
"""
Data Visualizer for Arduino Multi-Sensor Platform
Real-time visualization of sensor data
"""

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serialimport json
import numpy as np
from datetime import datetime
from collections import deque
import threading
import queue

class SensorDataVisualizer:
    def __init__(self, port: str, baudrate: int = 115200):
        self.port = port
        self.baudrate = baudrate
        self.serial = None
        self.running = True
        
        # Data buffers (deque for efficient memory usage)
        self.max_data_points = 100
        self.lidar_data = deque(maxlen=self.max_data_points)
        self.gps_data = deque(maxlen=self.max_data_points)
        self.temperature_data = deque(maxlen=self.max_data_points)
        self.power_data = deque(maxlen=self.max_data_points)
        self.timestamps = deque(maxlen=self.max_data_points)
        
        # Create figure and subplots
        self.fig, self.axes = plt.subplots(3, 2, figsize=(12, 10))
        self.fig.suptitle('Arduino Multi-Sensor Data Dashboard', fontsize=16)
        
        # Queue for thread-safe data transfer
        self.data_queue = queue.Queue()
        
        # Start serial thread
        self.serial_thread = threading.Thread(target=self.read_serial_data)
        self.serial_thread.daemon = True
        
    def connect(self):
        """Establish connection to Arduino"""
        try:
            self.serial = serial.Serial(self.port, self.baudrate, timeout=1)
            print(f"Connected to {self.port}")
            return True
        except Exception as e:
            print(f"Connection failed: {e}")
            return False
    
    def read_serial_data(self):
        """Thread function to read serial data continuously"""
        while self.running:
            if self.serial and self.serial.in_waiting:
                try:
                    line = self.serial.readline().decode().strip()
                    if line:
                        # Parse data (assumes JSON format)
                        data = self.parse_data(line)
                        if data:
                            self.data_queue.put(data)
                except Exception as e:
                    print(f"Error reading serial: {e}")
            time.sleep(0.01)
    
    def parse_data(self, line: str) -> dict:
        """Parse serial data (expects JSON format)"""
        try:
            # Try to parse JSON
            if line.startswith('{'):
                return json.loads(line)
            else:
                # Parse custom format if needed
                return self.parse_custom_format(line)
        except:
            return None
    
    def parse_custom_format(self, line: str) -> dict:
        """Parse custom data format (example)"""
        data = {}
        parts = line.split(',')
        for part in parts:
            if ':' in part:
                key, value = part.split(':', 1)
                data[key.strip()] = value.strip()
        return data
    
    def update_data(self, data: dict):
        """Update data buffers with new data"""
        timestamp = datetime.now()
        self.timestamps.append(timestamp)
        
        # LiDAR
        if 'lidar' in data:
            self.lidar_data.append(float(data.get('lidar', 0)))
        
        # GPS (simplified - use 1 value for visualization)
        if 'gps' in data:
            self.gps_data.append(float(data.get('gps', 0)))
        
        # Temperature
        if 'temperature' in data:
            self.temperature_data.append(float(data.get('temperature', 0)))
        
        # Power
        if 'power' in data:
            self.power_data.append(float(data.get('power', 0)))
    
    def plot_animation(self, frame):
        """Animation function for real-time plotting"""
        # Clear all axes
        for ax in self.axes.flat:
            ax.clear()
        
        # Plot LiDAR Data
        ax = self.axes[0, 0]
        if self.lidar_data:
            ax.plot(list(self.timestamps), list(self.lidar_data), 'b-', linewidth=2)
        ax.set_title('LiDAR Distance')
        ax.set_xlabel('Time')
        ax.set_ylabel('Distance (mm)')
        ax.grid(True)
        
        # Plot GPS Data
        ax = self.axes[0, 1]
        if self.gps_data:
            ax.plot(list(self.timestamps), list(self.gps_data), 'g-', linewidth=2)
        ax.set_title('GPS Data')
        ax.set_xlabel('Time')
        ax.set_ylabel('Value')
        ax.grid(True)
        
        # Plot Temperature
        ax = self.axes[1, 0]
        if self.temperature_data:
            ax.plot(list(self.timestamps), list(self.temperature_data), 'r-', linewidth=2)
        ax.set_title('Temperature')
        ax.set_xlabel('Time')
        ax.set_ylabel('°C')
        ax.grid(True)
        
        # Plot Power Consumption
        ax = self.axes[1, 1]
        if self.power_data:
            ax.plot(list(self.timestamps), list(self.power_data), 'm-', linewidth=2)
        ax.set_title('Power Consumption')
        ax.set_xlabel('Time')
        ax.set_ylabel('Watts')
        ax.grid(True)
        
        # Plot Histogram of Recent Data
        ax = self.axes[2, 0]
        if self.lidar_data:
            ax.hist(list(self.lidar_data), bins=20, color='blue', alpha=0.7)
        ax.set_title('LiDAR Distribution')
        ax.set_xlabel('Distance (mm)')
        ax.set_ylabel('Frequency')
        ax.grid(True)
        
        # Plot Statistics
        ax = self.axes[2, 1]
        if self.power_data:
            stats = [
                f'Min: {np.min(self.power_data):.2f}W',
                f'Max: {np.max(self.power_data):.2f}W',
                f'Mean: {np.mean(self.power_data):.2f}W',
                f'Std: {np.std(self.power_data):.2f}W',
                f'Count: {len(self.power_data)}'
            ]
            ax.text(0.1, 0.5, '\n'.join(stats), transform=ax.transAxes,
                   fontsize=12, verticalalignment='center')
        ax.set_title('Power Statistics')
        ax.axis('off')
        
        # Rotate and align timestamps
        for ax in self.axes.flat:
            ax.xaxis.set_tick_params(rotation=45)
    
    def start_visualization(self):
        """Start the visualization"""
        if not self.connect():
            return
        
        # Start serial reading thread
        self.serial_thread.start()
        
        # Set up animation
        ani = animation.FuncAnimation(self.fig, self.plot_animation, 
                                     interval=500, blit=False)
        
        # Show plot
        plt.tight_layout()
        plt.show()
    
    def stop_visualization(self):
        """Stop visualization and clean up"""
        self.running = False
        if self.serial and self.serial.is_open:
            self.serial.close()
        print("Visualization stopped")

def main():
    import argparse
    
    parser = argparse.ArgumentParser(description='Sensor Data Visualizer')
    parser.add_argument('-p', '--port', required=True, help='Serial port')
    parser.add_argument('-b', '--baudrate', type=int, default=115200, help='Baud rate')
    
    args = parser.parse_args()
    
    visualizer = SensorDataVisualizer(args.port, args.baudrate)
    
    try:
        visualizer.start_visualization()
    except KeyboardInterrupt:
        visualizer.stop_visualization()
        print("Visualization terminated")

if __name__ == "__main__":
    main()
