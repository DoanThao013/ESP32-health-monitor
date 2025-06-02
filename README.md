# ESP32-Based Real-Time Health Monitoring System

## 📋 Overview

This project implements a low-cost, real-time health monitoring system using an ESP32 microcontroller. It measures and displays:
- Heart rate and SpO₂ (blood oxygen level) using the MAX30100 sensor.
- Body temperature using the DS18B20 digital sensor.
- Ambient temperature and humidity using the DHT11 sensor.

All data is presented on a real-time web dashboard hosted directly by the ESP32 over Wi-Fi.

---

## 🔧 Features

- Real-time heart rate and SpO₂ monitoring.
- Accurate body temperature tracking.
- Ambient temperature and humidity sensing.
- Live web-based interface (auto-refresh every 2 seconds).
- Non-blocking, multi-thread-like behavior using Ticker.
- Error handling for sensor disconnection or invalid data.

---

## 🛠️ Hardware Used

| Component              | Description                               |
|------------------------|-------------------------------------------|
| ESP32 Dev Module       | Wi-Fi-enabled microcontroller             |
| MAX30100               | Heart rate and SpO₂ sensor                |
| DS18B20                | Digital body temperature sensor           |
| DHT11                  | Temperature and humidity sensor (ambient) |
| Breadboard + jumpers   | For connecting all components             |
| Power supply           | 5V USB or regulated 3.3V for stability     |

---

## 🌐 Network Setup

The ESP32 creates or connects to a **local Wi-Fi network**. It does **not require Internet**. IP is assigned by the router. Access the dashboard by opening the ESP32's IP in a web browser.

> Example: `http://192.168.1.42`

---

## ⚙️ How It Works

1. Sensors collect data and send it to the ESP32.
2. The ESP32 processes the data and serves a dynamic HTML page.
3. JavaScript on the web page fetches sensor values every 2 seconds.
4. Ticker ensures that sensor readings and updates are done non-blocking.

---

## 🧪 Testing Environment

- **Test location**: Classroom environment
- **Duration**: 20-minute continuous logging sessions
- **Conditions**:
  - Room temp ~30°C
  - Humidity ~55%
  - Local Wi-Fi router without internet

---

## 📊 Sample Output

| Time     | Heart Rate (BPM) | SpO₂ (%) | Body Temp (°C) | Room Temp (°C) | Humidity (%) |
|----------|------------------|----------|----------------|----------------|---------------|
| 14:00:00 | 78               | 98       | 36.5           | 30.2           | 55            |
| 14:00:10 | 81               | 97       | 36.6           | 30.3           | 56            |

---

## 🚫 Known Limitations

- No automatic Wi-Fi reconnection.
- Static health thresholds (not personalized).
- MAX30100 placement can affect accuracy.
- DHT11 has limited precision.
- No long-term data storage (e.g., cloud or file).

---

## 🏁 Future Improvements

- Add auto-reconnect for Wi-Fi.
- Implement cloud storage (e.g., Firebase).
- Replace DHT11 with more accurate sensors (e.g., DHT22 or BME280).
- Add user-defined thresholds for personalized alerts.
- Support mobile-friendly UI and data export.

---

## 📁 File Structure

