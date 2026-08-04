# Hardware

Descripción del hardware del **Estandarte LED Interactivo con IA**.

## Componentes principales

- **ESP32 DevKit**: microcontrolador con WiFi/Bluetooth. Genera la señal de control para las tiras LED y captura la señal del micrófono a través de un ADC de 12 bits.
- **Módulo micrófono MAX4466**: electret preamplificado con salida analógica (0–VCC), equipado con potenciómetro de ganancia.
- **Tiras LED WS2812**: LED direccionables, 5 V, cada LED es direccionable individualmente (RGB 24 bits). Poliuretano/SMD 5050.
- **Resistencia 330 Ω**: protección de la línea de datos para reducir el ruido y proteger el pin del ESP32.
- **Condensador 1000 µF**: desacople en la alimentación de 5 V para evitar caídas de tensión al activar muchos LED a la vez.
- **Fuente de alimentación 5 V**: debe soportar la corriente máxima de las tiras (aprox. 60 mA por LED a blanco completo).
- **Soporte del estandarte**: estructura (madera, acrílico o varillas) sobre la que se fijan las tiras en patrones (letras, siluetas, gráficas).

## Especificaciones clave

| Parámetro | Valor |
|-----------|-------|
| Tensión de trabajo | 5 V |
| Corriente por LED (blanco) | ~60 mA |
| LEDs por tira | 60/m (típico) |
| Pin ADC ESP32 | eje. GPIO34-39 (inputs solo lectura) |
| Pin datos WS2812 | GPIO con interfaz RMT/NeoPixel |
| Micrófono | analog VCC 2.4–5.5 V, salida ~2 V máx |

## Diagrama de bloques

```
            +-------------+
  Sonido -->| MAX4466    |---> ADC (ESP32)
            +-------------+        |
                                   v
            +-------------+   +----------+
                        |-->| ESP32    |--> Pin datos --> WS2812 (tira)
  5V      -->| Fuente 5V |   | (CPU+IA) |         |
            +-------------+   +----------+         v
                                                  Soporte
```

## Distribución de pines sugerida (ESP32)

| Señal | GPIO | Notas |
|-------|------|-------|
| Datos WS2812 | GPIO 5 | Compatible con FastLED/Neopixel via RMT |
| Mic MAX4466 OUT | GPIO 34 | Entrada analógica (ADC1) |
| 5 V tira | Vin/5V | Alimentación separada y común (GND común) |
| GND común | GND | Retorno común entre ESP32, mic y tira |

## Buenas prácticas

1. **Alimentación dedicada**: las tiras WS2812 con muchos LED deben alimentarse desde la fuente de 5 V por separado del ESP32, compartiendo solo GND.
2. **Condensador**: colocar 470–1000 µF lo más cerca de la tira.
3. **Resistencia en datos**: 330–470 Ω cercana al pin del ESP32.
4. **Tierra común**: conectar todos los GND (fuente, ESP32, micrófono, tira) para evitar flotación de señal.

Ver detalles del esquema y montaje en [`circuito/`](circuito/README.md).