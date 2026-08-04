# Estandarte LED Interactivo con IA

Un estandarte publicitario/académico de tiras LED WS2812 controlado por un **ESP32**, que reacciona al sonido ambiental capturado por un **módulo micrófono MAX4466**. La inteligencia artificial integrada analiza la señal de audio en tiempo real para generar patrones de luz dinámicos e interactivos.

## Objetivos

- Diseñar un estandarte con tiras LED WS2812 (direccionables) montadas sobre un soporte.
- Capturar el sonido ambiente con un micrófono MAX4466 conectado al ESP32.
- Analizar la señal de audio mediante un modelo de IA (en el PC o en el dispositivo) para detectar nivel sonoro, ritmo y clasificación.
- Controlar las tiras LED con efectos dinámicos proporcionales a la música/voz capturada.
- Documentar cada etapa (hardware, firmware, IA, control, informe) para permitir escalabilidad y mantenimiento.

## Tecnologías

| Área | Tecnología |
|------|------------|
| Microcontrolador | ESP32 (devkit) |
| Tiras LED | WS2812 (NeoPixel), 5V, control vía GPIO |
| Micrófono | MAX4466 (analog output, electret preamplificado) |
| Alimentación | Fuente 5V (5 A o superior) |
| Firmware | Arduino / PlatformIO (C++) con FastLED o Adafruit_NeoPixel |
| IA | Python 3 + bibliotecas de análisis de audio (ver `software/ia/`) |
| Control | Teoría de control aplicada a la iluminación (ver `documentacion/control/`) |

## Estructura del repositorio

```
├── README.md                     # Este archivo (visión general)
├── hardware/
│   ├── README.md                 # Descripción del hardware
│   └── circuito/
│       ├── README.md             # Explicación del circuito
│       ├── diagramas/            # Esquemáticos (pendientes)
│       └── imagenes/             # Fotos y capturas del montaje
├── software/
│   ├── README.md                 # Descripción del código y entorno
│   ├── firmware/
│   │   ├── README.md             # Documentación del firmware ESP32
│   │   └── src/                  # Código fuente (Arduino/PlatformIO)
│   └── ia/
│       ├── README.md             # Documentación de los scripts de IA
│       └── scripts/              # Scripts Python de análisis de audio
└── documentacion/
    ├── README.md                 # Índice de toda la documentación
    ├── informe/                  # Informe final del proyecto
    └── control/                  # Análisis de control de luces e interacción
```

## Lista de componentes

| Componente | Cantidad | Notas |
|------------|----------|-------|
| ESP32 DevKit | 1 | Microcontrolador principal |
| Módulo micrófono MAX4466 | 1 | Salida analógica, preamplificado |
| Tiras LED WS2812 | según medida | 5 V, direccionables, ~60 LED/m |
| Resistencia 330 Ω (o 470 Ω) | 1 | En la línea de datos entre ESP32 y tira |
| Condensador 1000 µF / 470 µF | 1 | Desacople en alimentación de LEDs |
| Cables y conectores | varios | Cables dupont, AWG 20/22 |
| Fuente de alimentación 5 V | 1 | ≥ 5 A según número de LEDs |
| Soporte del estandarte | 1 | Base/marco para montar las tiras |

## Cronograma (12 días)

| Días | Etapa | Entregables |
|------|-------|-------------|
| 1–3 | Diseño y prueba del circuito | Esquemático, montaje protoboard, pruebas de LEDs y micrófono |
| 4–6 | Programación del microcontrolador | Firmware ESP32: lectura ADC, efectos LED, comunicación |
| 7–9 | Integración de la IA | Scripts de análisis de audio, enlace con firmware |
| 10–11 | Documentación y pruebas finales | READMEs, diagramas, ajustes de control |
| 12 | Informe final | Informe completo en `documentacion/informe/` |

## Guía de uso (resumen)

1. **Hardware**: conecta el micrófono al pin ADC del ESP32 y las tiras WS2812 al pin de datos (ver `hardware/circuito/README.md`).
2. **Firmware**: sube el código del ESP32 desde `software/firmware/`.
3. **IA**: ejecuta los scripts de análisis de audio desde `software/ia/` (o integra la IA embebida).
4. **Alimentación**: energiza con la fuente de 5 V y observa los efectos reactivos al sonido.

## Estado del proyecto

En desarrollo. Documentación estructurada por etapas para permitir **escalabilidad**: agregar más tiras, nuevos sensores o modelos de IA más avanzados sin rehacer el proyecto completo.
