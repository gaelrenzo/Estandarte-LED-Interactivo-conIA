# Firmware ESP32

Firmware encargado de leer el micrófono y controlar las tiras LED WS2812 del estandarte.

## Características

- Lectura del **nivel de audio** por ADC (GPIO 34).
- Control de animaciones sobre tiras **WS2812** con **FastLED**.
- Modo autónomo (reactivo al sonido) y modo asistido por PC (comandos serial).
- Base extensible: agregar modos de efecto o nuevos sensores sin reescribir todo.

## Dependencias

- `FastLED` (o `Adafruit_NeoPixel`).
- `ArduinoJson` (solo si se usa comunicación JSON por serial).

## Distribución de pines

| Función | Pin |
|---------|-----|
| Datos WS2812 | 5 |
| Micrófono (ADC) | 34 |

## Código fuente

- [`src/main.cpp`](src/main.cpp): programa principal.
- [`src/leds.h`](src/leds.h): funciones de animación de LEDs.
- [`src/audio.h`](src/audio.h): lectura y suavizado del audio.

## Compilación y subida

### PlatformIO
```bash
pio run -t upload
pio device monitor
```

### Arduino IDE
1. Configurar placa **ESP32 Dev Module**.
2. Instalar librería **FastLED**.
3. Abrir `src/main.cpp` y subir.

## Comunicación serial (modo IA)

Mensajes entrantes (desde `../ia/`):
- `set <modo>` → cambia el efecto. Ej: `set vu`, `set wave`, `set strobe`.
- `int <0-100>` → intensidad objetivo (usada por el control).
- `color <r>,<g>,<b>` → color fijo.

Salidas (para depuración):
- `L0: <nivel>` cada N ms con el nivel de audio normalizado.

## Notas de escalabilidad

- El número de LED se define en la constante `NUM_LEDS`; recalcular corriente según el total.
- Agregar efectos = agregar un caso en `applyEffect()` y su función en `leds.h`.
- Para IA embebida, reemplazar el módulo serie por `tflite-micro` (ver `software/ia/`).