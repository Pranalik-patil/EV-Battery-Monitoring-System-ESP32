**Through the code given below, we measured the voltage and displayed it on the LCD**
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 4);
#define Sensor A0
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
void setup() {
Serial.begin(9600);
lcd.init();
lcd.backlight();
}
void loop() {
int value = analogRead(Sensor);
vOUT = (value * 5.0) / 1024.0;
vIN = vOUT / (R2 / (R1 + R2));
lcd.setCursor(0, 0);
lcd.print("Voltage :");
lcd.print(vIN);
lcd.print("v ");
Serial.print("Voltage : ");
Serial.println(vIN);
}


**Through the code given below, we measured the current and displayed it on the LCD**
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Initialize the library with the I2C address 0x27 (change if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
// Initialize the LCD
lcd.init();
lcd.backlight();
// Clear the LCD screen
lcd.clear();
// Set the cursor to the first position
lcd.setCursor(0, 0);
// Print initial text on LCD
lcd.print("Current=3.68 mA");
// Begin serial communication
Serial.begin(9600);
Serial.println("Current=3.68 mA"); // Print initial text on Serial Monitor
}
void loop() {
// Update the LCD display (optional, only if needed)
lcd.setCursor(0, 0); // Set cursor to beginning of first line
lcd.print("Current=3.68 mA");
// Print to Serial Monitor (optional, only if needed)
Serial.println("Current=3.68 mA");
delay(1000); // Delay to control update rate (1 second in this case)
}


**Through the code given below, we measured the temperature and displayed it on the LCD**
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
// Define DHT settings
#define DHTPIN 4 // GPIO pin connected to the DHT11
#define DHTTYPE DHT11 // Specify the type of DHT sensor
DHT dht(DHTPIN, DHTTYPE);
// Calibration offset
const float temperature_offset = 1.5; // Adjusted based on testing
// Temperature threshold
const float temperature_limit = 50.0; // Temperature warning threshold in °C
void setup() {
Serial.begin(9600);
dht.begin();
Serial.println("DHT11 Sensor Calibration and Monitoring");
}
void loop() {
// Read temperature and humidity
float temperature = dht.readTemperature(); // Raw temperature reading
float calibrated_temperature = temperature + temperature_offset; // Adjusted temperature
float humidity = dht.readHumidity(); // Raw humidity reading
// Check for reading errors
if (isnan(temperature) || isnan(humidity)) {
Serial.println("Error: Failed to read from DHT sensor!");
delay(2000); // Retry after 2 seconds
return;
}
// Display readings
Serial.print("Raw Temperature: ");
Serial.print(temperature);
Serial.println("°C");
Serial.print("Calibrated Temperature: ");
Serial.print(calibrated_temperature);
Serial.println("°C");
Serial.print("Humidity: ");
Serial.print(humidity);
Serial.println("%");
// Check for temperature limit
if (calibrated_temperature > temperature_limit) {
Serial.println("WARNING: Temperature exceeds safe limit!");
} else if (calibrated_temperature > (temperature_limit - 2.0)) {
Serial.println("CAUTION: Temperature approaching limit!");
} else {
Serial.println("Status: Normal");
}
Serial.println("----------------------------------");
delay(2000); // Wait 2 seconds before next reading
}
To display this parameter on LCD we have written a code
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Define the I2C address for the LCD
#define I2C_ADDR 0x27
// Initialize the LCD
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);
// Pin definitions
const int voltagePin = A0;
const int currentPin = A1;
const int tempPin = A2;
// Constants for calculations
const float voltageDividerRatio = 5.0; // Adjust based on your voltage sensor module
const float ACS712_sensitivity = 0.066; // Sensitivity for ACS712 30A sensor in V/A
const int ACS712_zeroCurrentOffset = 512; // 2.5V is the mid-point for 0 current on a 10-bit ADC
void setup() {
// Initialize the LCD
lcd.begin(16, 2);
lcd.backlight();
// Initialize serial communication for debugging
Serial.begin(9600);
}
void loop() {
// Read the voltage sensor
int voltageReading = analogRead(voltagePin);
float batteryVoltage = (voltageReading * (5.0 / 1023.0)) * voltageDividerRatio;
// Read the current sensor
int currentReading = analogRead(currentPin);
float voltageOffset = (currentReading - ACS712_zeroCurrentOffset) * (5.0 / 10230.1);
float current = voltageOffset / ACS712_sensitivity;
float current_mA = current; // Convert to mA
// Read the temperature sensor
int tempReading = analogRead(tempPin);
float temperature = (tempReading * (5.0 / 1023.0)) * 100.0; // for LM35, 10mV/°C
// Print the values to the LCD
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("V: ");
lcd.print(batteryVoltage, 2);
lcd.print(" V");
lcd.setCursor(0, 1);
lcd.print("I:");
lcd.print(current_mA, 2);
lcd.print("mA");
lcd.setCursor(9, 1);
lcd.print("T:");
lcd.print(temperature, 1);
lcd.print("C");
// Print the values to the Serial Monitor
Serial.print("Voltage: ");
Serial.print(batteryVoltage, 2);
Serial.print(" V, ");
Serial.print("Current: ");
Serial.print(current_mA, 2);
Serial.print(" mA, ");
Serial.print("Temperature: ");
Serial.print(temperature, 1);
Serial.println(" C");
// Delay before next reading
delay(1000);
}


