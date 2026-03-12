# The Universal Harmonic Matrix (Base-27720 DDS Architecture)

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-brightgreen.svg)](https://www.espressif.com/)
[![Status: Concept & Proof](https://img.shields.io/badge/Status-Active-success.svg)]()

**Author:** Olexandr Lozovyi  
**Paper:** [The Universal Harmonic Matrix: Evolution of DDS Phase Accumulators from Base-12 to Base-27720](link-to-your-zenodo-or-pdf-here)

## 📌 Overview
This repository contains the theoretical foundation, simulation scripts, and embedded C++ implementation concepts for the **Harmonic Matrix DDS** (Direct Digital Synthesis). 

By shifting the phase accumulator base from standard binary (e.g., 2¹⁶ = 65536) to the highly composite number **27720**, this architecture achieves **absolute zero computational phase jitter** for all fundamental non-linear resonances (3rd, 5th, 7th, 11th harmonics).

This integer-ratio harmonic modulation is designed for high-precision, closed-loop feedback systems such as:
* **Plasma Physics** (Tokamak/Stellarator mode locking suppression)
* **Neural Entrainment** (High-fidelity brainwave modulation without quantization noise)
* **Energy Infrastructure** (Real-time active harmonic filtering)

## 🧮 The Binary Problem vs. The Base-27720 Solution
Standard binary DDS systems cannot perfectly resolve rational fractions. Generating a 3rd, 5th, or 7th harmonic inherently causes infinite decimals and rounding errors. In closed-loop systems, these 0.2 to 0.8 LSB errors accumulate, causing synchronization loss and phase jitter.

**Base-27720** is the smallest number perfectly divisible by all integers from 1 to 12. It guarantees integer precision.

### Comparative Error Analysis

| Harmonic | Phase Shift | Standard 16-bit Binary (N=65536) | Base-27720 Matrix | Phase Error (LSB)* |
| :--- | :--- | :--- | :--- | :--- |
| **3rd** | 1/3 | 21845.333... | **9240** | **0.333** |
| **5th** | 1/5 | 13107.200 | **5544** | **0.200** |
| **7th** | 1/7 | 9362.285... | **3960** | **0.285** |
| **11th** | 1/11 | 5957.818... | **2520** | **0.818** |

*\* 1 LSB ≈ 0.0055° phase error in a 16-bit system. The Base-27720 system produces exactly 0 LSB error.*

## ⚡ Hardware Implementation (ESP32)
The number 27720 is an engineering absolute for 16-bit embedded systems:
* It utilizes the maximum capacity of a 16-bit register without overflow (27720 < 65535).
* An 8-bit output Lookup Table (LUT) mapped to a 27720-step accumulator occupies exactly **27.7 kB**.
* This fits comfortably into the **ultra-fast L1 cache (32 kB)** of modern microcontrollers like the ESP32, completely avoiding memory fetch latency.

## 📂 Repository Structure
* `/docs/` - The complete theoretical paper and mathematical proofs.
* `/simulations/` - Python scripts demonstrating the phase jitter in standard binary systems vs. the Harmonic Matrix.
* `/src/` - C++ header files and ESP32 examples for implementing the Base-27720 phase accumulator and LUT.

## 🚀 Getting Started
*(Instructions for running the Python simulation and flashing the ESP32 example will be added here)*

## 📜 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. Note: The theoretical mathematics (Base-12 to Base-27720 concept) is protected under academic priority via DOI publication.

---
*Created in Lviv, Ukraine as part of the Harmonic Modulation research initiative.*
