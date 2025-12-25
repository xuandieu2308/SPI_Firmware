| Supported Targets | ESP32 | ESP32-C3 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- |

# SPI RTOS Layered Firmware Example (Master ↔ Slave)

This project demonstrates **SPI communication** between two ESP32 boards (**SPI Master** and **SPI Slave**) using **ESP-IDF** and **FreeRTOS**, designed with a **layered firmware architecture**.

The firmware is structured into **Application**, **Service**, and **Hardware Driver** layers to ensure clear separation of responsibilities and easy scalability.

---

## Firmware layering architecture

The project is divided into the following layers:

Application Layer
├── app_main.c

Service Layer
├── spi_service.c
└── spi_service.h

Hardware Driver Layer
├── spi_master_driver.c / spi_slave_driver.c
└── spi_master_driver.h / spi_slave_driver.h

markdown
Sao chép mã

### Application Layer
- Entry point of the firmware
- Creates and manages FreeRTOS tasks
- Calls service-layer APIs only
- Contains no direct hardware access

### Service Layer
- Abstracts SPI communication logic
- Handles data preparation and parsing
- Decouples application logic from hardware drivers

### Hardware Driver Layer
- Low-level SPI drivers
- Directly interfaces with ESP-IDF SPI APIs
- Responsible for SPI initialization and data transfer

---

## Project structure
---
SPI
├── esp32_spi_master
│ ├── hardware
│ │ ├── spi_master_driver.c
│ │ └── spi_master_driver.h
│ ├── service
│ │ ├── spi_service.c
│ │ └── spi_service.h
│ ├── main
│ │ └── app_main.c
│ ├── CMakeLists.txt
│ └── sdkconfig
│
├── esp32_spi_slave
│ ├── hardware
│ │ ├── spi_slave_driver.c
│ │ └── spi_slave_driver.h
│ ├── service
│ │ ├── spi_service.c
│ │ └── spi_service.h
│ ├── main
│ │ └── app_main.c
│ └── CMakeLists.txt
│
└── README.md
---

## How the example works

- One ESP32 acts as **SPI Master**
- One ESP32 acts as **SPI Slave**
- SPI initialization is handled in the hardware layer
- Data exchange logic is implemented in the service layer
- Application layer triggers SPI communication using FreeRTOS tasks

---

## Hardware required

- 2 × ESP32 development boards
- Jumper wires

### SPI wiring (example)

| Signal | Master GPIO | Slave GPIO |
|------|-------------|------------|
| MOSI | GPIO23 | GPIO23 |
| MISO | GPIO19 | GPIO19 |
| SCLK | GPIO18 | GPIO18 |
| CS   | GPIO5  | GPIO5  |
| GND  | GND    | GND    |

GPIO pins may be adjusted in driver configuration.

---

## FreeRTOS usage

- SPI communication runs inside FreeRTOS tasks
- Architecture supports:
  - Mutex protection for SPI bus
  - Queue-based message passing
  - Easy extension to multiple SPI devices

---

## Build, flash and monitor

### SPI Master
```bash
cd esp32_spi_master
idf.py set-target esp32
idf.py build flash monitor
SPI Slave
bash
Sao chép mã
cd esp32_spi_slave
idf.py set-target esp32
idf.py build flash monitor
Expected behavior
SPI Master sends data periodically

SPI Slave receives data and responds if implemented

Logs are printed on both boards

Clean separation between application, service, and hardware layers

Troubleshooting
SPI communication issues
Check MOSI/MISO/SCLK/CS wiring

Ensure Master and Slave use compatible SPI modes

Verify clock speed configuration

Confirm both boards share a common GND

Technical support and feedback
ESP32 Forum: https://esp32.com/

ESP-IDF Issues: https://github.com/espressif/esp-idf/issues
