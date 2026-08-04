# Software

Código y simulaciones del **Estandarte LED IME**.

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
