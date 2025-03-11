# Temperature Monitoring System with FPGA

This project implements a temperature monitoring system using an FPGA (Field-Programmable Gate Array) to process data from a temperature sensor and display the results. The system leverages the **Xilinx Spartan-6 XC6SLX9 FPGA**, along with the **LM35 temperature sensor** and the **ADS1115 analog-to-digital converter (ADC)**, to measure and process temperature data with high precision. The communication between the components is facilitated using the **I2C protocol**.

## Table of Contents
1. [Introduction](#introduction)
2. [Components](#components)
3. [System Design](#system-design)
4. [Challenges](#challenges)
5. [Implementation](#implementation)
6. [Results](#results)
7. [Conclusion](#conclusion)

## Introduction

The project focuses on designing a low-power, efficient temperature monitoring system using an FPGA. The system is capable of real-time temperature measurement and processing, making it suitable for industrial applications such as environmental monitoring, medical devices, and automation systems. The FPGA's flexibility and parallel processing capabilities allow for efficient data handling and control.

## Components

The following components are used in this project:

| **Component**         | **Description**                                                                 |
|------------------------|---------------------------------------------------------------------------------|
| **LM35 Temperature Sensor** | A precision analog temperature sensor that provides a linear output of 10 mV/°C. |
| **ADS1115 ADC**        | A 16-bit analog-to-digital converter with I2C interface for high-precision signal conversion. |
| **Xilinx Spartan-6 XC6SLX9 FPGA** | A low-power FPGA with 9,156 logic cells, 16 DSP slices, and 576 Kb block RAM. |
| **Arduino Nano**       | Used as an intermediary for I2C communication between the ADC and the FPGA.     |
| **ESP32**              | Another microcontroller option for I2C communication.                          |

## System Design

The system is designed to measure temperature using the LM35 sensor, convert the analog signal to digital using the ADS1115 ADC, and process the data using the FPGA. The communication between the ADC and the FPGA is managed via the I2C protocol, with the Arduino Nano acting as an intermediary to simplify the timing and synchronization challenges.

### Block Diagram

```plaintext
LM35 Sensor → ADS1115 ADC → Arduino Nano (I2C) → FPGA (Xilinx Spartan-6) → Display/Output
```
### Key Features
- **LM35 Sensor**: Provides accurate temperature measurements with a linear output.
- **ADS1115 ADC**: Converts analog signals to digital with 16-bit precision.
- **FPGA Processing**: The FPGA processes the digital data and performs real-time control tasks.
- **I2C Communication**: Facilitates data transfer between the ADC and the FPGA.

## Challenges

Implementing the I2C protocol between the FPGA and the ADS1115 ADC posed several challenges, including:

1. **Timing Complexity**: The I2C protocol requires precise timing for clock (SCL) and data (SDA) signals. Any deviation can lead to communication errors.
2. **Signal Management**: Managing the SDA and SCL signals simultaneously in the FPGA required careful design to avoid signal conflicts.
3. **Noise Sensitivity**: The I2C protocol is sensitive to noise, especially over long distances, which can lead to data corruption.

## Implementation

The project was implemented in two phases:

1. **Initial Approach with ESP32**: The ESP32 was used as an intermediary for I2C communication. However, timing issues arose due to the FPGA's inability to precisely control the clock signal.
2. **Final Approach with Arduino Nano**: The Arduino Nano was used to handle the I2C communication, simplifying the timing and synchronization process. The FPGA received the data in parallel, reducing the complexity of the design.

### Code Overview
The FPGA was programmed using **Verilog** to process the incoming data from the ADC and convert it into meaningful temperature values. The Arduino Nano handled the I2C communication, ensuring that the data was correctly transmitted to the FPGA.

## Results

The system successfully measured and displayed temperature data with high accuracy. The use of the Arduino Nano as an intermediary resolved the timing issues encountered in the initial approach, allowing for reliable data transmission and processing.

### Key Achievements
- **High Precision**: The 16-bit ADC provided accurate temperature measurements.
- **Real-Time Processing**: The FPGA enabled real-time data processing and control.
- **Low Power Consumption**: The system was designed to be energy-efficient, making it suitable for industrial applications.

## Conclusion

This project demonstrates the successful implementation of a temperature monitoring system using an FPGA, LM35 sensor, and ADS1115 ADC. The system is capable of real-time temperature measurement and processing, making it suitable for various industrial applications. The challenges of I2C communication were addressed by using the Arduino Nano as an intermediary, ensuring reliable data transmission. Future improvements could focus on optimizing the FPGA design for even lower power consumption and higher performance.

---


