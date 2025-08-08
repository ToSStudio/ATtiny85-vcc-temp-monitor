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
- Serial connection (e.g., via USB-Serial adapter, TinyUSB board, or similar)
- LED on pin 4 (optional, for visual heartbeat)

---

## 📷 Example Output
- ATTiny showing Vcc and Temp in °C
- disregard the first 20 or so values of the output
- Temp: 25.4 °C | Vcc: 3.274 V
- Temp: 25.3 °C | Vcc: 3.269 V
- Temp: 25.3 °C | Vcc: 3.270 V

