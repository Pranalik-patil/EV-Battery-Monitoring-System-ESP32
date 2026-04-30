**Third ESP32 Code handles cloud communication.**
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <HardwareSerial.h>
#define WLAN_SSID "Cloud"
#define WLAN_PASS "12345678"
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883 // use 8883 for SSL
  #define AIO_USERNAME "SnehaM10"
#define AIO_KEY "YOUR_AIO_KEY"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish batvoltage = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Battery Voltage");
Adafruit_MQTT_Publish batcurrent = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Current Consumption");
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Humidity");
HardwareSerial SerialPort(2);
float batv, bati, temp, hum;
char inChar;
unsigned long previousMillis = 0;
const long interval = 20000;
void MQTT_connect();
void setup()
{
Serial.begin(115200);
SerialPort.begin(15200, SERIAL_8N1, 16, 17);
WiFi.begin(WLAN_SSID, WLAN_PASS);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("Wifi Connected");
}
void loop()
{
MQTT_connect();
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval)
{
previousMillis = currentMillis;
batvoltage.publish(batv);
batcurrent.publish(bati);
temperature.publish(temp);
humidity.publish(hum);
}
while (SerialPort.available() > 0)
{
inChar = SerialPort.read();
while (inChar != 'a')
{
inChar = SerialPort.read();
}
batv = SerialPort.parseFloat();
inChar = SerialPort.read();
if (inChar == 'b')
{
bati = SerialPort.parseFloat();
}
inChar = SerialPort.read();
if (inChar == 'd')
{
temp = SerialPort.parseFloat();
}
inChar = SerialPort.read();
if (inChar == 'e')
{
hum = SerialPort.parseFloat();
}
inChar = SerialPort.read();
if (inChar == 'c')
{
break;
}
}
}
void MQTT_connect() {
int8_t ret;
// Stop if already connected.
if (mqtt.connected()) {return;}
Serial.println("Connecting to MQTT..");
uint8_t retries = 3;
while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
Serial.println(mqtt.connectErrorString(ret));
Serial.println("Retrying MQTT connection in 5 seconds...");
mqtt.disconnect();
delay(5000); // wait 5 seconds
retries--;
if (retries == 0) {
// basically die and wait for WDT to reset me
while (1);
}
}
Serial.println("MQTT Connected!");}
  
