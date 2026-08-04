# Software

Descripción del código y del entorno de desarrollo del **Estandarte LED Interactivo con IA**.

## Estructura del software

```
software/
├── README.md          # Este archivo
├── firmware/          # Código del ESP32 (Arduino / PlatformIO)
│   ├── README.md
│   └── src/           # Código fuente principal
└── ia/                # Scripts de IA para análisis de audio
    ├── README.md
    └── scripts/       # Scripts Python
```

## Entornos

### Firmware (ESP32)
- **Plataforma**: Arduino IDE o PlatformIO.
- **Librerías**: `FastLED` (o `Adafruit_NeoPixel`), `WiFi`, `ArduinoJson` (para comunicación con IA externa).
- **Placa**: ESP32 DevKit V1 (DOIT).
- **Baudrate serial**: 115200.

### IA (Python)
- **Python 3.9+**
- **Bibliotecas**: `numpy`, `scipy`, `sounddevice` (o `pyaudio`), `matplotlib` (visualización), `pyserial` (comunicación con ESP32).
- Opcional: `tensorflow`/`tflite-micro` para IA embebida en el ESP32.

## Flujo de datos

```
MAX4466 ──► ESP32 ADC ──► Firmware (efectos LED)
   │                         │
   └──► [opcional] Serial ───┴──► PC (Python IA) ──► comandos back
```

Modos:
1. **Autónomo**: el ESP32 mide el nivel de audio y decide los efectos.
2. **Asistido por PC**: el Python captura audio, clasifica (música/voz/ruido, BPM, intensidad) y envía comandos al ESP32 por serial.

## Instalación

### Firmware
```bash
cd software/firmware
# Con PlatformIO:
pio run -t upload
# Con Arduino IDE: abrir src/main.cpp y subir a la placa ESP32
```

### IA
```bash
cd software/ia
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

Ver más detalles en [`firmware/`](firmware/README.md) e [`ia/`](ia/README.md).