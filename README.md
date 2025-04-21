# OneBoard All-in-One Sensor Test by Niklas Heinzel
## Description

This project utilizes an ESP12F-based board designed to make IoT projects modular and easy to implement. The board features a plug-and-play system with sockets and connectors, allowing a variety of sensors to be connected to the mainboard via I2C. This system enables quick, hassle-free expansion of the board, making it ideal for projects with specific requirements. With minimal wiring, time, and cost involved, the board can be extended as needed.

![1](https://github.com/user-attachments/assets/dc78ef25-a077-45df-b6b0-412a87980131)

Future expansion boards, including sensors like the SHT30, SGP30, and BH1750, will follow the same form factor. This product is especially beneficial for beginners or for projects with limited budgets and tight schedules, providing a simple way to realize planned IoT solutions.

### Supported Modules

- **SHT30-DIS-B (Temperature and Humidity Sensor Extension Board)**  
  This compact 8-pin DFN sensor offers advanced signal processing and two selectable I2C addresses, with communication speeds of up to 1 MHz. It provides a fully calibrated, linearized, and temperature-compensated digital output with a typical accuracy of ±1.5% (humidity) and ±0.1°C (temperature).

- **BH1750 (Ambient Light Sensor Extension Board)**  
  A small ambient light sensor capable of precise measurements ranging from 1 to 65,535 lux. It features an I2C interface, selectable I2C addresses, and can be calibrated depending on external interference. It has low light-source dependency and a measurement deviation of ±20%.

- **SGP30 (VOC Gas Sensor Extension Board)**  
  An ultra-low-power gas sensor solution designed for detecting a wide range of volatile organic compounds (VOCs), ideal for air quality monitoring. It includes an integrated analog-to-digital converter (ADC) and an I2C interface. The sensor displays eCO2 or TVOC values and has an optimized low-power mode for energy efficiency.

The system is designed for rapid and efficient prototyping, providing a plug-and-play experience that saves time and eliminates the need for complex wiring or pin configuration knowledge. With a wide range of extension boards available, this platform is ideal for creating interesting projects housed in an attractive, compact board.

### Project Ideas

- Indoor/Outdoor Weather Station
- Air Quality Monitor
- Ambient Light Sensor that Automatically Controls Devices via WiFi
- Sensor Station with Cloud Dashboard Integration

## Requirements

- Arduino IDE
- Libraries:
  - [Wire](https://www.arduino.cc/en/Reference/Wire)
  - [Adafruit_SGP30](https://github.com/adafruit/Adafruit_SGP30)
  - [BH1750](https://github.com/claws/BH1750)
  - [WEMOS_SHT3X](https://github.com/wemos/WEMOS_SHT3X)

## Installation

1. Clone this repository to your local machine or download the code as a ZIP file.
2. Open the code in the Arduino IDE.
3. Install the necessary libraries via the Arduino Library Manager or manually.
4. Connect the sensors to your Arduino board as follows:
   - **SHT30**: I2C (0x44)
   - **SGP30**: I2C
   - **BH1750**: I2C
5. Upload the code to your Arduino board.

## Usage

1. Open the Serial Monitor in the Arduino IDE.
2. The sensor data will be printed every 2 seconds, showing:
   - Temperature (°C)
   - Humidity (%)
   - TVOC (ppb)
   - eCO2 (ppm)
   - Light intensity (lx)
3. Every 30 measurements, the baseline values for TVOC and eCO2 will be displayed.

## Example Output
--------------------------------
Test Script: OneBoard All-in-One
--------------------------------
Found SGP30 serial # 123456
TVOC 123 ppb    eCO2 400 ppm
Raw H2 100      Raw Ethanol 150
Light: 350 lx
Temperature in Celsius: 25.30 °C
Relative Humidity: 55.5 %
--------------------------------


