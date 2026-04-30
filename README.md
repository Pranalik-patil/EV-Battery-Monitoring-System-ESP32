# EV-Battery-Monitoring-System-ESP32
Cloud-Based Autonomous Tracking of Battery Health for Safe EV Operation


#  Cloud-Based EV Battery Monitoring System (ESP32)

A real-time battery health monitoring system for electric vehicles using ESP32, Arduino, and IoT cloud integration.
This project tracks critical battery parameters and enables remote monitoring, fault detection, and improved safety.

---

## 📌 Project Overview

Electric vehicles rely heavily on battery performance and safety. Traditional systems often lack real-time monitoring and remote accessibility.

This project presents a **cloud-connected Battery Management System (BMS)** that:

* Monitors **Voltage, Current, Temperature, Humidity, and State of Charge (SOC)**
* Uses **ESP-NOW protocol** for fast wireless communication
* Uploads data to the **cloud (Adafruit IO)** for real-time visualization
* Detects faults and sends alerts for unsafe conditions

---

## 🚀 Key Features

✅ Real-time monitoring of battery parameters
✅ SOC (State of Charge) estimation
✅ Wireless communication using ESP32 (ESP-NOW)
✅ Cloud integration with live dashboard
✅ Fault detection system:

* 🔥 Over-temperature alert
* ⚡ Low battery alert
* 📡 Communication failure detection

---

## 🛠️ Tech Stack

**Hardware:**

* ESP32 (Sensor Node + Receiver Node)
* Arduino Uno
* ACS712 Current Sensor
* Voltage Sensor Module
* DHT11 Temperature & Humidity Sensor
* 16x2 I2C LCD

**Software & Tools:**

* Arduino IDE
* Embedded C
* ESP-NOW Protocol
* MQTT Protocol
* Adafruit IO Cloud Platform

---

## 📡 System Architecture

```
Sensors → ESP32 (Transmitter)
        → ESP-NOW Communication
        → ESP32 (Receiver)
        → Wi-Fi → Adafruit Cloud
        → Dashboard Visualization
```

---

## ⚙️ Working Principle

1. Sensors collect battery parameters:

   * Voltage
   * Current
   * Temperature
   * Humidity

2. ESP32 (Sensor Node):

   * Processes sensor data
   * Sends data wirelessly via ESP-NOW

3. ESP32 (Receiver Node):

   * Receives data
   * Sends acknowledgment (ACK)
   * Detects abnormal conditions

4. Cloud Integration:

   * Data uploaded to Adafruit IO via MQTT
   * Real-time dashboard displays parameters

---

## 🔋 SOC Calculation

State of Charge is calculated using linear mapping:

[
SOC = \frac{V - V_{min}}{V_{max} - V_{min}} \times 100
]

Where:

* (V_{max} = 4.2V)
* (V_{min} = 3.0V)

---

## 📂 Project Structure

```
EV-Battery-Monitoring-System/
│
├── README.md
├── code/
│   ├── arduino/
│   ├── esp32/
│
├── hardware/
│   ├── circuit_diagrams/
│   ├── pcb_design/
│
├── results/
│   ├── calibration_data/
│   ├── output_images/
│
├── docs/
│   └── final_report.pdf
│
└── images/
    ├── setup/
    ├── architecture/
```

---

## 🧪 Testing & Calibration

* Sensors calibrated using known reference values
* Verified:

  * Voltage accuracy
  * Current measurements
  * Temperature readings
* System tested under:

  * Different loads
  * Discharge cycles
  * Environmental variations

---

## 📊 Results

* Accurate real-time monitoring achieved
* Reliable ESP-NOW communication
* Successful cloud visualization
* Fault detection working efficiently

---

## ⚠️ Fault Detection & Alerts

| Condition             | Action                  |
| --------------------- | ----------------------- |
| Temperature > 50°C    | Alert: "Cool Down"      |
| Voltage < Threshold   | Alert: "Charge Battery" |
| Communication Failure | Delivery Fail Message   |

---

## 🔮 Future Scope

* AI-based SOC/SOH prediction
* Mobile app integration
* Advanced battery analytics
* Support for larger EV battery packs

---

## 👩‍💻 Contributors

* Pranali Patil
* Rutuja Halgekar
* Shrinidhi Pattar
* Sneha Murgod

---

## 📜 License

This project is for academic and research purposes.

---

## ⭐ Support

If you like this project:

* ⭐ Star the repository
* 🍴 Fork and improve
* 📢 Share with others

---

## 📬 Contact

For queries or collaboration, feel free to connect!

---

