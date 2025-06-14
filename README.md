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
  - Room temp ~31°C
  - Humidity ~57%
  - Hotspot 4G wifi

---

## 📊 Sample Output

![image](https://github.com/user-attachments/assets/93390bae-e346-4589-91e2-00a6bf92df7a)

![image](https://github.com/user-attachments/assets/d9f29aa7-4a91-427e-9b6f-7ca3576f8ad1)

![image](https://github.com/user-attachments/assets/97be5643-fef7-4449-bdbf-a05d4e3d94e7)


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
- Add user-defined thresholds for personalized alerts.
- Support mobile-friendly UI and data export.

---

