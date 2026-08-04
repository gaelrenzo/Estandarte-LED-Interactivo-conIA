# Firmware del Estandarte IME

Código de control del estandarte LED, tanto en simulación como en la
arquitectura física de tres ESP32.

## Estructura

```
firmware/
├── README.md                    # Este archivo
├── arquitectura_3_esp32/        # Base de la versión física (ESP-NOW)
│   ├── README_3_ESP32.md
│   ├── central/central_maestro.ino    # Wi-Fi + página web + envía comandos
│   ├── electrica/receptor_electrica.ino
│   ├── mecanica/receptor_mecanica.ino
│   └── comun/protocolo.h              # Protocolo compartido (ComandoIME)
└── prototipo_IA/                # Prototipo previo: tiras reactivas a audio + IA
    ├── README.md
    ├── main.cpp                 # Lectura ADC, efectos FastLED, serial
    ├── leds.h                   # Efectos de animación
    └── audio.h                  # Lectura y suavizado del micrófono
```

## Arquitectura física: tres ESP32

- **Central**: crea la red Wi-Fi local `ESTANDARTE_IME`, aloja la página de
  control y envía comandos **ESP-NOW**.
- **Mecánica** y **Eléctrica**: reciben comandos, controlan sus tiras WS2812 y
  entran en un **modo seguro** si pierden el enlace.

Ver [`arquitectura_3_esp32/README_3_ESP32.md`](arquitectura_3_esp32/README_3_ESP32.md).

## Firmware principal (simulación integrada)

El firmware con los efectos de las tres zonas se encuentra en
[`../simulaciones/platformio/src/main.cpp`](../simulaciones/platformio/src/main.cpp)
(idéntico a `../simulaciones/wokwi/sketch.ino`). Contiene 6 modos:
Institucional, Flujo IME, Audio/VU, Tormenta Zeus, Desfile y Apagado.

## Prototipo IA (previo)

Versión inicial donde las tiras reaccionan al **nivel de audio** del micrófono
MAX4466, controladas por scripts de IA en Python. Ver
[`prototipo_IA/README.md`](prototipo_IA/README.md).

## Notas

- Los sketches `.ino` incluyen `../comun/protocolo.h`; conserva la estructura
  de carpetas al abrirlos en Arduino IDE.
- La red ESP-NOW debe validarse con placas reales (Wokwi no simula multi-ESP32).
