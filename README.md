# ESP32 Biometric Authentication System

🚀 **An ESP32-based authentication system integrating a SparkFun GT-521F32 fingerprint sensor, OLED display, and WiFi connectivity.**
---
## ✨ Features
- 📡 **WiFi Connectivity**  
  - Connects to multiple predefined SSIDs.  
  - Displays network status on an OLED screen.  
  - Uses **rotating dots animation** while connecting.  
- 🔍 **Biometric Authentication**  
  - Integrates with **GT-521F32** fingerprint sensor.  
  - Supports **fingerprint enrollment, verification, and deletion**.  
  - Automatically skips fingerprint scanning if the sensor is missing.  
- 📅 **Real-Time Date & Time Display**  
  - Fetches time via **NTP (Network Time Protocol)**.  
  - Displays **HH:MM AM/PM** format with **MM-DD** date.  
- 📟 **OLED Display UI Enhancements**  
  - Shows **WiFi & Fingerprint icons** with dynamic updates.  
  - Displays a **bordered section for information**.  
  - Uses **animated elements** for a better user experience.  
- 💾 **Future Plans**  
  - Store **fingerprint images** in a **MySQL database**.  
  - Create a **GitHub Wiki** for detailed documentation.

---

## 🛠️ **Hardware Requirements**
- **ESP32 DevKit V1**  
- **SparkFun GT-521F32 Fingerprint Sensor**  
- **0.96" OLED Display (128x64, SH1106 or SSD1306)**  
- **Jumper Wires & Breadboard**  

### **🔌 Wiring Guide**
| **GT-521F32 Pin** | **ESP32 Pin** |
|-------------------|--------------|
| VCC (3.3V or 5V) | 3.3V or 5V   |
| GND              | GND          |
| TX (Output)      | GPIO16 (RX2) |
| RX (Input)       | GPIO17 (TX2) |

---

## 📦 **Installation**
### **1️⃣ Clone the Repository**
```sh
git clone https://github.com/yourusername/your-repo.git
cd your-repo
```

### **2️⃣ Install Dependencies**
Ensure you have the required **Arduino libraries** installed:

- **Adafruit GFX**  
- **Adafruit SH110X** (for OLED display)  
- **Adafruit Fingerprint Sensor Library**  
- **WiFi** (built-in for ESP32)  
- **NTPClient** (for fetching time from the internet)

#### **📌 Arduino Library Installation Steps**
1. Open **Arduino IDE**  
2. Go to **Sketch > Include Library > Manage Libraries**  
3. Search and install:
   - `"Adafruit GFX"`
   - `"Adafruit SH110X"`
   - `"Adafruit Fingerprint Sensor Library"`
   - `"NTPClient"`

#### **📌 PlatformIO (VS Code) Library Installation**
If you're using **PlatformIO (VS Code)**, add the following to your `platformio.ini` file:
```ini
lib_deps =
    adafruit/Adafruit GFX Library
    adafruit/Adafruit SH110X
    adafruit/Adafruit Fingerprint Sensor Library
    arduino-libraries/NTPClient
```

### **3️⃣ Upload the Code**
```sh
1. Open the project in **Arduino IDE** or **PlatformIO (VS Code)**.  
2. Select your **ESP32 board** and **correct COM port**.  
3. Click **Upload** to flash the firmware.  
```
---
### **4️⃣ Run the Code**
After uploading, open the **Serial Monitor** in Arduino IDE or PlatformIO to check the output:  

```sh
1. Open **Serial Monitor** (115200 baud rate).
2. Observe the ESP32 connecting to WiFi and initializing the fingerprint sensor.
3. If the fingerprint sensor is missing, the system will skip fingerprint functions.
4. If connected successfully, the OLED display will update with time, date, WiFi, and fingerprint status.
```
---
## 📷 **Screenshots (Coming Soon)**
- UI mockups  
- Fingerprint authentication demo  

---

## 🛠️ **Planned GitHub Wiki**
📖 **Once fingerprint functions are finalized, a detailed Wiki will be created**, including:
- **Setup & Configuration**
- **How to Enroll & Verify Fingerprints**
- **MySQL Database Integration**
- **Troubleshooting & FAQs**

---

## 🤝 **Contributing**
Want to improve this project? Fork the repo and submit a PR!  
