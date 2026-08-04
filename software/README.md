# Software

> Código, firmware y simulaciones del **Estandarte LED IME**.

[![Wokwi](https://img.shields.io/badge/Wokwi-simulaci%C3%B3n-2b7f3b)](../software/simulaciones/wokwi/) [![PlatformIO](https://img.shields.io/badge/PlatformIO-local-00aeef)](../software/simulaciones/platformio/) [![ESP-NOW](https://img.shields.io/badge/Red-ESP--NOW-15a0d8)](../software/firmware/arquitectura_3_esp32/)

## Índice

- [Estructura](#estructura)
- [Simulaciones](#simulaciones)
- [Firmware](#firmware)
- [Instalación](#instalación-de-herramientas)

## Estructura

```
software/
├── README.md          # Este archivo
├── simulaciones/      # Simulaciones (Wokwi y PlatformIO)
│   ├── README.md
│   ├── wokwi/         # Simulación en navegador (Wokwi)
│   └── platformio/    # Proyecto local VS Code + PlatformIO
└── firmware/          # Firmware del estandarte
    ├── README.md
    ├── arquitectura_3_esp32/  # Base física: central + mecánica + eléctrica (ESP-NOW)
    └── prototipo_IA/          # Prototipo previo: LED reactivos a audio con IA
```

## Simulaciones

El firmware principal (tres zonas LED + matriz 8×8 + OLED + botones +
potenciómetros) está disponible en dos entornos:

- **Wokwi (navegador)**: `simulaciones/wokwi/` — rápido, sin instalación.
- **PlatformIO (local)**: `simulaciones/platformio/` — compilar y simular en VS Code.

Ver [`simulaciones/README.md`](simulaciones/README.md).

## Firmware

- [`arquitectura_3_esp32/`](firmware/arquitectura_3_esp32/): arquitectura
  física final con tres ESP32 coordinados por ESP-NOW y página web de control.
- [`prototipo_IA/`](firmware/prototipo_IA/): prototipo previo donde las tiras
  reaccionan al nivel de audio analizado por scripts de IA (Python).

Ver [`firmware/README.md`](firmware/README.md).

## Instalación de herramientas

- **PlatformIO**: VS Code → Extensiones → buscar *PlatformIO IDE* y *Wokwi Simulator*.
- **Python (prototipo IA)**: `pip install -r ia/scripts/requirements.txt`.
