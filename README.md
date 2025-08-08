# ATtiny85 Vcc and Temperature Monitor (No External Parts)

This project reads the **supply voltage (Vcc)** and **internal temperature sensor** of an ATtiny85 using only its built-in ADC channels.  
No external components or sensors are needed — just the microcontroller and Serial output.

## ✨ Features

- 🧠 **Exponential Moving Average (EMA)** filtering for smooth readings  
- ⚡ **Vcc measurement** using the internal 1.1V bandgap reference  
- 🌡️ **Temperature sensing** via internal sensor  
- 💡 LED blink on Pin 4 as heartbeat indicator  
- 🪶 Minimal RAM and CPU usage  
- 🔧 Easy calibration via top-of-sketch constants

---

## 🧰 Requirements

- ATtiny85 (tested with 8 MHz internal clock)
- µC must be flashed with the Spence Konde Optiboot bootloader to understand ADC-channels
- Serial connection (e.g., via USB-Serial adapter, TinyUSB board, or similar)
- LED on pin 4 (optional, for visual heartbeat)

---

## 📷 Example Output
- ATTiny showing Vcc and Temp in °C
- disregard the first 20 or so values of the output
- Temp: 25.4 °C | Vcc: 3.274 V
- Temp: 25.3 °C | Vcc: 3.269 V
- Temp: 25.3 °C | Vcc: 3.270 V


---

## ⚙️ Configuration

At the top of the sketch, you’ll find two important constants:

```cpp
#define TEMP_OFFSET   4     // Adjust this to match actual ambient temp
#define ADC_REF       988   // Internal 1.1V reference voltage in mV (tweak per chip)
```
Use these to calibrate against a trusted thermometer and known power supply.



🧪 How It Works
The bandgap channel (ADC 0x0E) allows calculation of Vcc by comparing the internal 1.1V reference to the actual supply.

The temperature sensor (ADC 0x0F) gives a raw ADC value that is approximately linear but varies per chip — a manual offset is used to bring it close to ambient.

🧵 License
MIT License — free to use, modify, and share. Attribution appreciated.

💡 Author
Created by ToS with technical input from ChatGPT.

The EMA filter helps smooth both values while keeping RAM usage low and speed high.

```cpp
// EMA: smoothing = (old * (N-1) + new) / N
filtered = (filtered * (EMA_DIVISOR - 1) + raw) / EMA_DIVISOR;
```
