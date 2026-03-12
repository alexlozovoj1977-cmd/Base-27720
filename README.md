# The Universal Harmonic Matrix: Base-27720 DDS for ESP32

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-brightgreen.svg)](https://www.espressif.com/)

## 📄 Project Overview
This repository contains the implementation of a Direct Digital Synthesis (DDS) phase accumulator based on the highly composite number **27720**. This architecture guarantees **absolute zero computational phase jitter** for key non-linear resonances (3rd, 5th, 7th, and 11th harmonics), which is critical for plasma control systems, high-precision non-invasive neural stimulation, and power grid stabilization.

## 🧠 Mathematical Foundation
Standard binary DDS systems (e.g., 16-bit or 32-bit matrices) cannot perfectly generate rational fractions, inevitably leading to the accumulation of rounding errors (phase noise) in closed-loop feedback systems.
* **Base-27720 = LCM(1..12)** — It is the lowest common multiple, perfectly divisible by all integers from 1 to 12.
* **7th Harmonic:** 27720 / 7 = 3960 (exact integer).
* **11th Harmonic:** 27720 / 11 = 2520 (exact integer).

## 📊 Comparison with 16-bit Binary DDS

| Harmonic | Phase Shift | 16-bit Binary (N=65536) | Base-27720 Matrix | Binary Error (LSB)* |
| :--- | :--- | :--- | :--- | :--- |
| **3rd** | 1/3 | 21845.333... | **9240** | **0.333 LSB** |
| **5th** | 1/5 | 13107.200 | **5544** | **0.200 LSB** |
| **7th** | 1/7 | 9362.285... | **3960** | **0.285 LSB** |
| **11th** | 1/11 | 5957.818... | **2520** | **0.818 LSB** |

*\*Note: 1 LSB corresponds to approximately 0.0055° phase error in a 16-bit binary system.*

## ⚙️ Hardware Implementation
* **Microcontroller:** ESP32 (any model with a built-in DAC).
* **Output:** GPIO 25 (built-in DAC). PWM output with an integrating RC filter is also supported.
* **Memory Optimization:** An 8-bit lookup table (LUT) is generated dynamically at boot and occupies exactly **27.7 kB**. This perfectly fits into the ultra-fast L1 cache (32 kB) of modern microcontrollers like the ESP32, completely eliminating memory fetch latency.

## 🚀 Quick Start
1. Install Arduino IDE or PlatformIO.
2. Open the `src/main.cpp` file.
3. Compile and upload the firmware to your ESP32 development board.
4. Connect an oscilloscope to **GPIO 25** and open the Serial Monitor (115200 baud).

## 🔬 Demonstration
* On startup, the system performs a mathematical validation check and begins generating a mathematically perfect **7th harmonic** (3960 steps per period).
* Every 10 seconds, it automatically switches to the **11th harmonic** (2520 steps per period).
* **Phase-Continuous Switching:** Frequency shifts occur atomically without resetting the phase accumulator. This guarantees no phase jumps, tearing, or clicking artifacts on the oscilloscope, making it ideal for Phase-Locked Loops (PLL) and FM modulation.

## 📚 References
* **Scientific Paper:** [The Universal Harmonic Matrix: Evolution of DDS Phase Accumulators](https://zenodo.org/records/18990491)
* **Theoretical foundation of the 11th harmonic:** Ruelle, D., & Takens, F. (1971). *On the nature of turbulence*. Communications in Mathematical Physics, 20(3), 167-192.

## 📄 License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details. The mathematical model is protected by academic publication priority.
