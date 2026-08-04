# Circuito

Explicación detallada del circuito del estandarte, incluyendo esquema, montaje y pruebas.

## Contenido de esta carpeta

```
circuito/
├── README.md          # Este archivo
├── diagramas/         # Esquemáticos y diagramas de conexión
│   └── (pendiente)    # Fritzing / KiCad / capturas
└── imagenes/          # Fotos del montaje real y pruebas
    └── (pendiente)    # Fotos de protoboard y soporte
```

## Partes del circuito

### 1. Alimentación (5 V)
- **Fuente 5 V** → terminal de la tira WS2812 (VCC).
- **Condensador 470–1000 µF** entre VCC y GND de la tira, cerca de la alimentación.
- Los GND de fuente, ESP32, micrófono y tira se conectan a un **punto común**.

### 2. Microcontrolador ESP32
- Pin de datos WS2812: **GPIO 5** (se puede cambiar en el firmware).
- Pin del micrófono: **GPIO 34** (ADC, entrada analógica).
- Se alimenta por USB o por el pin Vin (3.3 V regulado internamente).

### 3. Micrófono MAX4466
- **VCC** → 3.3 V del ESP32 (o 5 V según modelo).
- **GND** → común.
- **OUT** → GPIO 34 (ADC).
- Potenciómetro de ganancia ajustado para no saturar la entrada (lecturas entre 0 y 4095 sin recorte).

### 4. Tiras WS2812
- **DIN** ← GPIO 5 del ESP32 mediante **resistencia 330 Ω** en serie.
- **VCC** → 5 V de la fuente.
- **GND** → común.

## Diagrama de conexión (texto)

```
    Fuente 5V
    ├── VCC ──────────────► Tira WS2812 VCC
    │                       (paralelo a condensador 1000uF)
    └── GND ──────────────► GND común
                                   │
    ESP32                         │
    ├── GPIO5 ──[330 Ω]───► DIN WS2812
    ├── GPIO34 ◄────────── OUT MAX4466
    ├── 3.3V ────────────► VCC MAX4466
    └── GND ──────────────► GND común ──► GND MAX4466 ──► GND Tira
```

## Pruebas del circuito (días 1–3)

1. **Prueba de LED**: cargar un sketch de ejemplo (FastLED `FirstLight` / NeoPixel `strandtest`) y verificar que los LED encienden en orden.
2. **Prueba de micrófono**: cargar el ejemplo de lectura ADC y mostrar valores en el monitor serie; aplaudir o silbar y ver cambios.
3. **Prueba combinada**: mover el LED con el nivel de audio.
4. **Verificación de alimentación**: medir con multímetro 5 V en la tira y 3.3 V en el ESP32. Observar caídas al encender todos los LED.

## Notas de escalabilidad

- Para **tiras largas** (más de ~1 A) usar alimentación inyectada en ambos extremos.
- Agregar más tiras se hace conectando el **DOUT** de una tira al **DIN** de la siguiente.
- Si se agregan sensores nuevos (LDR, IR), usar los pines libres del ESP32.
