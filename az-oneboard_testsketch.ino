//AZ-Oneboard-Testsketch
//by Niklas Heinzel
//2024

#include <Wire.h>
#include "Adafruit_SGP30.h"
#include <BH1750.h>
#include <WEMOS_SHT3X.h>

// Initialize the SHT30 temperature and humidity sensor at I2C address 0x44
SHT3X sht30(0x44);

// Initialize the Adafruit SGP30 air quality sensor
Adafruit_SGP30 sgp;

// Initialize the BH1750 light intensity sensor
BH1750 lightMeter;

/**
 * Calculates the absolute humidity based on temperature and relative humidity.
 * The formula used is an approximation provided by Sensirion for the SGP30.
 * @param temperature Temperature in Celsius.
 * @param humidity Relative humidity as a percentage.
 * @return Absolute humidity scaled in milligrams per cubic meter (mg/m^3).
 */
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    const float absoluteHumidity = 216.7f * 
        ((humidity / 100.0f) * 6.112f * 
        exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

/**
 * Setup function is executed once when the program starts. It initializes the sensors
 * and configures the serial communication.
 */
void setup() {
    Serial.begin(9600); // Start the serial communication at 9600 baud rate
    Wire.begin(); // Initialize the I2C communication

    while (!Serial) {
        delay(10); // Wait for the Serial connection to be ready
    }

    Serial.println("--------------------------------");
    Serial.println("Test Script: OneBoard All-in-One");
    Serial.println("--------------------------------");

    lightMeter.begin(); // Initialize the BH1750 light sensor

    // Initialize the SGP30 sensor and check if it is available
    if (!sgp.begin()) {
        Serial.println("Sensor not found :(");
        while (1); // Halt execution if the sensor is not found
    }

    // Print the serial number of the SGP30 sensor
    Serial.print("Found SGP30 serial #");
    Serial.print(sgp.serialnumber[0], HEX);
    Serial.print(sgp.serialnumber[1], HEX);
    Serial.println(sgp.serialnumber[2], HEX);
}

// Counter to track iterations in the loop
int counter = 0;

/**
 * Loop function runs continuously after setup. It performs sensor readings,
 * processes the data, and outputs the results via the Serial connection.
 */
void loop() {
    // Perform air quality measurements using the SGP30 sensor
    if (!sgp.IAQmeasure()) {
        Serial.println("Measurement failed");
        return; // Exit the loop if the measurement fails
    }

    Serial.print("TVOC ");
    Serial.print(sgp.TVOC); // Total Volatile Organic Compounds (TVOC) in ppb
    Serial.print(" ppb\t");
    Serial.print("eCO2 ");
    Serial.print(sgp.eCO2); // Equivalent CO2 (eCO2) in ppm
    Serial.println(" ppm");

    // Perform raw measurements for hydrogen and ethanol
    if (!sgp.IAQmeasureRaw()) {
        Serial.println("Raw Measurement failed");
        return;
    }
    Serial.print("Raw H2 ");
    Serial.print(sgp.rawH2); // Raw hydrogen concentration
    Serial.print(" \t");
    Serial.print("Raw Ethanol ");
    Serial.print(sgp.rawEthanol); // Raw ethanol concentration
    Serial.println("");

    delay(2000); // Wait for 2 seconds before the next measurement

    counter++;
    if (counter == 30) { // Every 30 iterations, retrieve the baseline values
        counter = 0;

        uint16_t TVOC_base, eCO2_base;
        if (!sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
            Serial.println("Failed to get baseline readings");
            return;
        }
        Serial.print("****Baseline values: eCO2: 0x");
        Serial.print(eCO2_base, HEX);
        Serial.print(" & TVOC: 0x");
        Serial.println(TVOC_base, HEX);
    }

    // Read and print light intensity from the BH1750 sensor
    float lux = lightMeter.readLightLevel();
    Serial.print("Light: ");
    Serial.print(lux); // Light intensity in lux
    Serial.println(" lx");
    delay(2000); // Wait for 2 seconds

    // Read and print temperature and humidity from the SHT30 sensor
    if (sht30.get() == 0) {
        Serial.print("Temperature in Celsius: ");
        Serial.print(sht30.cTemp); // Temperature in Celsius
        Serial.println(" °C");
        Serial.print("Relative Humidity: ");
        Serial.print(sht30.humidity); // Relative humidity as a percentage
        Serial.println(" %");
        Serial.println("--------------------------------");
    } else {
        Serial.println("Error!"); // Output an error if the SHT30 sensor fails
    }

    delay(5000); // Wait for 5 seconds before restarting the loop
}
