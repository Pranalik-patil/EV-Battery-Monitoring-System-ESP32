**First ESP32 Code handles sensing and transmitting data.**
#include <esp_now.h>
#include <WiFi.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
#define ANALOG_IN_PIN 36
#define REF_VOLTAGE 3.3
#define ADC_RESOLUTION 4096.0
#define R1 29000.0
#define R2 7500.0
float tot;
int errorreceived = 0;
uint8_t broadcastAddress[] = {0x30, 0xC6, 0xF7, 0x99, 0x51, 0x18};
typedef struct struct_message
{
float a;
float b;
float c;
float d;
} struct_message;
typedef struct error_message
{
int err;
} error_message;
struct_message myData;
error_message incomingReadings;
esp_now_peer_info_t peerInfo;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
Serial.print("Data Sent to RSU : ");
lcd.setCursor(0,0);
lcd.print("Data Sent to RSU");
lcd.setCursor(0,1);
lcd.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : " Delivery Fail ");
delay(1500);
}
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
Serial.print("Bytes received: ");
Serial.println(len);
errorreceived = incomingReadings.err;
}
void setup()
{
lcd.init();
lcd.backlight();
Serial.begin(115200);
analogSetAttenuation(ADC_11db);
dht.begin();
WiFi.mode(WIFI_STA);
if (esp_now_init() != ESP_OK)
  {
Serial.println("Error initializing ESP-NOW");
return;
}
esp_now_register_send_cb(OnDataSent);
memcpy(peerInfo.peer_addr, broadcastAddress, 6);
peerInfo.channel = 0;
peerInfo.encrypt = false;
if (esp_now_add_peer(&peerInfo) != ESP_OK)
{
Serial.println("Failed to add peer");
return;
}
esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv))
lcd.setCursor(0,0);
lcd.print(" Cloud Based ");
lcd.setCursor(0,1);
lcd.print(" Autonomous ");
delay(2000);
lcd.setCursor(0,0);
lcd.print("Vehicle Tracking");
lcd.setCursor(0,1);
lcd.print(" System ");
delay(2000);
}
void loop()
{
int adc_value = analogRead(ANALOG_IN_PIN);
float voltage_adc = ((float)adc_value * REF_VOLTAGE) / ADC_RESOLUTION;
float voltage_in = voltage_adc * (R1 + R2) / R2;
for(int i = 1; i<=5; i++)
{
// read the input on analog pin 0:
int sensorValue = analogRead(35);
// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
float voltage = sensorValue * (3.3 / 4095.0);
float currentv = voltage - 2.25;
float current = 2222.2222 * currentv;
tot = tot + current;
delay(200);
}
float avg = tot/5;
// print out the value you read
if(avg < 150)
avg = 0;
myData.a = voltage_in;
myData.b = avg / 1000;
myData.c = dht.readTemperature();
myData.d = dht.readHumidity();
lcd.setCursor(0,0);
lcd.print("V: I: ");
lcd.setCursor(0,1);
lcd.print("T: H: ");
lcd.setCursor(2,0);
lcd.print(voltage_in,2);
lcd.setCursor(10,0);
lcd.print(myData.b,2);
lcd.setCursor(2,1);
lcd.print(myData.c,2);
lcd.setCursor(10,1);
lcd.print(myData.d,2);
Serial.print("Error Code : ");
Serial.println(errorreceived);
delay(2000);
if(errorreceived == 1)
{
lcd.setCursor(0,0);
lcd.print("HIGH TEMPERATURE");
lcd.setCursor(0,1);
lcd.print("PLEASE COOL DOWN");
delay(3000);
}
else if(errorreceived == 2)
{
lcd.setCursor(0,0);
lcd.print(" Battery Low ");
lcd.setCursor(0,1);
lcd.print(" Please Charge ");
delay(3000);
}
// Send message via ESP-NOW
esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
if (result == ESP_OK)
{
Serial.println("Sent with success");
}
else
{
Serial.println("Error sending the data");
}
tot = 0;
}
