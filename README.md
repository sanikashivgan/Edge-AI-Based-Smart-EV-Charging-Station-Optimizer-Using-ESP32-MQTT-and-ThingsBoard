# Edge AI Based Smart EV Charging Station Optimizer Using ESP32, MQTT and ThingsBoard

## 📌 Project Overview

The **Edge AI Based Smart EV Charging Station Optimizer** is an IoT-based smart charging management system designed to improve the utilization of multiple EV charging bays.

The system uses **ESP32** as the edge controller for each charging bay. It collects charging-related parameters such as voltage, current, power, energy consumption, temperature, and bay status.

The collected data is processed locally on the ESP32, where a lightweight **Edge AI model** is used for prediction. Based on the charging conditions, station load, tariff period, and prediction results, the system can make local charging decisions such as:

* **ALLOW** – Charging can continue normally.
* **THROTTLE** – Charging power should be reduced.
* **DEFER** – Charging can be delayed when the station is under high demand.

The ESP32 communicates with **ThingsBoard using MQTT** for real-time monitoring, visualization, telemetry, and remote control.

---

## 🎯 Problem Statement

Conventional EV charging stations may face problems such as:

* Uneven utilization of charging bays
* Long waiting times during high-demand periods
* High station power demand
* Increased electricity cost during peak tariff periods
* Lack of predictive charging management
* Limited real-time monitoring of individual charging bays

This project aims to develop a smart system that can monitor multiple charging bays and make intelligent charging-management decisions at the edge.

---

## 🎯 Objectives

The main objectives of this project are:

1. Monitor multiple EV charging bays using ESP32.
2. Measure voltage, current, power, energy, and temperature.
3. Detect charging-bay status in real time.
4. Implement lightweight Edge AI prediction on the ESP32.
5. Optimize charging based on station load and operating conditions.
6. Reduce unnecessary peak power demand.
7. Communicate telemetry using MQTT.
8. Visualize charging-station data using ThingsBoard.
9. Provide remote control using ThingsBoard RPC.
10. Develop a scalable architecture that can be extended to real charging-management systems.

---

## 🏗️ System Architecture

```text
                 ┌───────────────────────┐
                 │     EV Charging       │
                 │       Station         │
                 └───────────┬───────────┘
                             │
          ┌──────────────────┼──────────────────┐
          │                  │                  │
          ▼                  ▼                  ▼
   ┌─────────────┐    ┌─────────────┐    ┌─────────────┐
   │   Bay 01    │    │   Bay 02    │    │   Bay 03    │
   │    ESP32    │    │    ESP32    │    │    ESP32    │
   └──────┬──────┘    └──────┬──────┘    └──────┬──────┘
          │                  │                  │
          │ Sensors          │ Sensors          │ Sensors
          │ + Edge AI        │ + Edge AI        │ + Edge AI
          │                  │                  │
          └──────────────────┼──────────────────┘
                             │
                            MQTT
                             │
                             ▼
                  ┌─────────────────────┐
                  │     ThingsBoard     │
                  │      Platform       │
                  └──────────┬──────────┘
                             │
                             ▼
                  ┌─────────────────────┐
                  │      Dashboard      │
                  │ Monitoring & Alerts │
                  └─────────────────────┘
```

---

## 🔧 Hardware Used

The project uses ESP32-based simulated charging bays.

### Main Components

| Component                     | Purpose                       |
| ----------------------------- | ----------------------------- |
| ESP32                         | Edge controller               |
| Current Sensor / Analog Input | Current measurement           |
| Voltage Sensor / Analog Input | Voltage measurement           |
| DHT22 / Temperature Sensor    | Temperature monitoring        |
| Relay                         | Charging control              |
| Push Buttons                  | Plug-in / plug-out simulation |
| LEDs                          | Bay status indication         |
| Optional OLED                 | Local information display     |

> The project is developed as a low-voltage simulation/prototype. It does **not** directly control real high-voltage EV charging equipment.

---

## 💻 Software and Technologies

* **ESP32**
* **Arduino / PlatformIO**
* **Wokwi**
* **C/C++**
* **MQTT**
* **ThingsBoard**
* **ArduinoJson**
* **PubSubClient**
* **Python**
* **NumPy**
* **Pandas**
* **Scikit-learn**
* **Edge AI / Machine Learning**
* **Git & GitHub**

---

# 🚗 Charging Bay Setup

The project contains three independent charging-bay simulations.

```text
Project
│
├── Bay 1
├── Bay 2
└── Bay 3
```

Each bay contains its own ESP32-based control and monitoring setup.

---

# 🔵 Bay 1

Bay 1 represents the first charging point of the smart EV charging station.

The ESP32 monitors the charging parameters and communicates the data to ThingsBoard through MQTT.

### Main Functions

* Voltage monitoring
* Current monitoring
* Power calculation
* Energy calculation
* Temperature monitoring
* Charging-bay status
* Relay control
* Edge AI prediction
* MQTT telemetry
* ThingsBoard communication

### Bay 1 Screen Recording

The Bay 1 simulation and working demonstration are included in this repository.

---

# 🟢 Bay 2

Bay 2 represents the second charging point.

It operates independently while contributing its telemetry and charging status to the overall station-management system.

### Main Functions

* Voltage monitoring
* Current monitoring
* Power calculation
* Energy calculation
* Temperature monitoring
* Charging status
* Relay control
* Edge AI prediction
* MQTT communication
* ThingsBoard monitoring

### Bay 2 Screen Recording

The Bay 2 simulation and working demonstration are included in this repository.

---

# 🟡 Bay 3

Bay 3 represents the third charging point of the station.

It demonstrates how the system can be extended to multiple charging bays.

### Main Functions

* Voltage monitoring
* Current monitoring
* Power calculation
* Energy calculation
* Temperature monitoring
* Charging status
* Relay control
* Edge AI prediction
* MQTT communication
* ThingsBoard monitoring

### Bay 3 Screen Recording

The Bay 3 simulation and working demonstration are included in this repository.

---

# 🤖 Edge AI

A lightweight Edge AI approach is used to make predictions locally rather than depending completely on cloud processing.

### Prediction Inputs

The model can use parameters such as:

* Hour of day
* Day of week
* Current bay status
* Recent average current
* Session duration
* Number of occupied neighboring bays
* Historical arrival information

### Prediction Outputs

The system can estimate:

* Probability of a vehicle arriving
* Expected charging duration

The predicted information is then used by the charging optimization logic.

---

# ⚡ Charging Optimization

The charging decision is based on both deterministic safety rules and prediction results.

### Example Decision Logic

```text
             Start
               │
               ▼
       Check Current
               │
        ┌──────┴──────┐
        │             │
   Over Current    Normal
        │             │
        ▼             ▼
      STOP       Check Station Load
                      │
                ┌─────┴─────┐
                │           │
             High Load    Normal
                │           │
                ▼           ▼
             THROTTLE     Check
                          Prediction
                              │
                   ┌──────────┴──────────┐
                   │                     │
                High Demand          Normal
                   │                     │
                   ▼                     ▼
                 DEFER                  ALLOW
```

The system separates **safety-related deterministic controls** from AI predictions. AI predictions are used for optimization and forecasting, while protection conditions such as overcurrent and station power limits are handled using predefined rules.

---

# 📡 MQTT Communication

MQTT is used for communication between the ESP32 devices and ThingsBoard.

### Telemetry Topic

```text
v1/devices/me/telemetry
```

### Attributes Topic

```text
v1/devices/me/attributes
```

### RPC Request

```text
v1/devices/me/rpc/request/+
```

### Example Telemetry

```json
{
  "bayId": "BAY_01",
  "voltage": 230,
  "current": 8.5,
  "power": 1955,
  "energyWh": 1250,
  "temperature": 29.5,
  "bayStatus": "CHARGING",
  "predictedArrivalProb": 0.72,
  "predictedDurationMin": 35,
  "loadDecision": "ALLOW",
  "throttleLevel": 100
}
```

---

# ☁️ ThingsBoard Dashboard

ThingsBoard is used as the cloud/IoT monitoring platform.

The dashboard can display:

* Bay status
* Voltage
* Current
* Power
* Energy consumption
* Temperature
* Total station load
* Predicted arrival probability
* Predicted charging duration
* Charging decision
* Throttle level
* Alarms
* Real-time telemetry

The system also supports remote commands through ThingsBoard RPC.

---

# 🔄 Remote Control

The ThingsBoard platform can send commands to the ESP32.

### Supported RPC Functions

```text
setRelayState
setThrottle
getStatus
```

These commands can be used for:

* Turning charging ON/OFF
* Changing charging throttle level
* Requesting current device status

---

# 📊 Project Workflow

```text
1. EV connects to charging bay
              ↓
2. ESP32 detects bay status
              ↓
3. Sensors collect charging data
              ↓
4. ESP32 calculates power & energy
              ↓
5. Edge AI performs prediction
              ↓
6. Optimization logic evaluates station conditions
              ↓
7. Charging decision is generated
              ↓
8. ESP32 controls charging output
              ↓
9. Telemetry is published using MQTT
              ↓
10. ThingsBoard receives the data
              ↓
11. Dashboard displays real-time information
```

---

# 🎥 Project Demonstration

Screen recordings of the three charging-bay simulations are included with the project files.

### Demonstration Includes

* ESP32 simulation
* Charging-bay operation
* Sensor values
* Charging-state changes
* MQTT communication
* ThingsBoard telemetry
* Dashboard monitoring
* Optimization decisions

---


# ▶️ How to Run

## Step 1 — Open the Bay

Open any of the three bay folders.

```text
Bay-1
Bay-2
Bay-3
```

## Step 2 — Open the ESP32 Project

Open the project using:

* Arduino IDE

or

* Visual Studio Code with PlatformIO

## Step 3 — Configure Wi-Fi

Enter the required Wi-Fi credentials in the ESP32 program.

```cpp
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
```

## Step 4 — Configure ThingsBoard

Add the required device in ThingsBoard and configure the MQTT credentials.

Do not upload real access tokens, passwords, or private credentials to GitHub.

## Step 5 — Run the Simulation

Run the Wokwi simulation or upload the firmware to the ESP32.

## Step 6 — Open ThingsBoard

Monitor the telemetry and charging-bay status through the ThingsBoard dashboard.

---

# 🔐 Security Note

Never upload the following information to GitHub:

* ThingsBoard access tokens
* MQTT passwords
* Wi-Fi passwords
* API keys
* Private credentials

Use placeholders such as:

```text
YOUR_WIFI_NAME
YOUR_WIFI_PASSWORD
YOUR_THINGSBOARD_TOKEN
```

---

# 🧪 Testing

The system is tested using multiple charging-bay conditions such as:

* Bay available
* Vehicle connected
* Vehicle disconnected
* Normal charging
* High current
* High station load
* Peak tariff period
* Multiple occupied bays
* MQTT communication
* Remote relay control

---

# 📈 Expected Results

The completed system demonstrates:

* Multi-bay EV charging simulation
* Real-time monitoring
* Local Edge AI prediction
* Intelligent charging decisions
* MQTT-based communication
* ThingsBoard visualization
* Remote charging control
* Load-aware charging management

The system provides a foundation for developing a larger smart EV charging-management solution.

---

# 🚀 Future Scope

The project can be extended with:

* TensorFlow Lite Micro
* Improved Edge AI models
* Real EV charging hardware integration
* Dynamic electricity tariff APIs
* Solar-powered EV charging
* Battery energy storage
* Mobile application
* OTA firmware updates
* Cloud-based historical analytics
* Notification system
* Larger charging-station deployment

---


**Project:** Edge AI Based Smart EV Charging Station Optimizer Using ESP32, MQTT and ThingsBoard

**Domain:** IoT | Edge AI | Embedded Systems | Smart Energy Management

**Development Tools:** ESP32 | Wokwi | MQTT | ThingsBoard | Python | Arduino/PlatformIO

---


This project is an academic prototype and simulation-based implementation.

It is **not intended for direct connection to real high-voltage EV charging infrastructure** without appropriate electrical protection, certified charging hardware, safety systems, and professional engineering validation.
