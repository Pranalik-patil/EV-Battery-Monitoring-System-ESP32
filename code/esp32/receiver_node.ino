**Second ESP32 Code handles acknowledgment and relaying data.**
#include <esp_now.h>
#include <WiFi.h>
#include <HardwareSerial.h>
HardwareSerial SerialPort(2);
uint8_t broadcastAddress[] = {0x30, 0xC6, 0xF7, 0x99, 0x63, 0xE0};
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
float a;
float b;
float c;
float d;
} struct_message;
typedef struct error_message
{
int err;
} error_message;
// Create a struct_message called myData
struct_message myData;
error_message incomingReadings;
esp_now_peer_info_t peerInfo;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
Serial.print("Data Sent to RSU : ");
Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
memcpy(&myData, incomingData, sizeof(myData));
Serial.print("Bytes received: ");
Serial.println(len);
Serial.print("Battery Voltage : ");
Serial.println(myData.a);
Serial.print("Battery Current : ");
Serial.println(myData.b);
Serial.print("Temperature : ");
Serial.println(myData.c);
Serial.print("Humidity : ");
Serial.println(myData.d);
Serial.println();
SerialPort.write('a');
delay(5);
SerialPort.print(myData.a);
delay(5);
SerialPort.write('b');
delay(5);
SerialPort.print(myData.b);
delay(5);
SerialPort.write('d');
delay(5);
SerialPort.print(myData.c);
delay(5);
SerialPort.write('e');
delay(5);
SerialPort.print(myData.d);
delay(5);
SerialPort.write('c');
delay(5);
}
void setup()
{
// Initialize Serial Monitor
Serial.begin(115200);
SerialPort.begin(15200, SERIAL_8N1, 16, 17);
// Set device as a Wi-Fi Station
WiFi.mode(WIFI_STA);
// Init ESP-NOW
if (esp_now_init() != ESP_OK) {
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
// Once ESPNow is successfully Init, we will register for recv CB to
// get recv packer info
esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
void loop()
{
if(myData.c > 50)
{
incomingReadings.err = 1;
}
else
{
incomingReadings.err = 0;
}
if(myData.a < 8)
{
incomingReadings.err = 2;
}
else
{
incomingReadings.err = 0;
}
esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &incomingReadings, sizeof(incomingReadings));
delay(500);
}
