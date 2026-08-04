# IA (Inteligencia Artificial)

Scripts que analizan el audio ambiente para generar decisiones que controlen las tiras LED del estandarte, explicados paso a paso.

## Rol de la IA

La IA complementa el firmware añadiendo **interpretación** sobre el sonido:

1. **Nivel de audio** → intensidad y volumen de la luz.
2. **Ritmo / BPM** → sincronización de destellos y pulsos.
3. **Clasificación** (música / voz / ruido) → paleta de colores y efecto adecuado.
4. **Detección de picos** → disparo de efectos (strobe, onda).

## Modos de implementación

| Modo | Dónde corre | Latencia | Descripción |
|------|-------------|----------|-------------|
| Asistido por PC | Python | baja-media | El PC captura audio, clasifica y manda comandos al ESP32 por serial. |
| Embbido | ESP32 (tflite-micro) | muy baja | El modelo corre en el propio microcontrolador. |

## Estructura de scripts

```
ia/
├── README.md
└── scripts/
    ├── audio_capture.py   # Captura y nivel de audio
    ├── detectar_ritmo.py  # Detección de BPM y picos
    ├── clasificador.py    # Clasifica música/voz/ruido
    ├── control_leds.py    # Toma decisiones y envía al ESP32
    └── requirements.txt   # Dependencias
```

## Flujo paso a paso

```
Entrada de audio (micrófono del PC o señal del ESP32)
        │
        v
[1] audio_capture.py  → ventana de n muestras, nivel RMS
        │
        v
[2] audio_ritmo.py    → FFT, energía por banda, onset, BPM
        │
        v
[3] clasificador.py   → reglas/ML: musica | voz | ruido
        │
        v
[4] control_leds.py   → cartografía nivel/BPM/clase → comando serial
        │
        v
    ESP32 (firmware) → animación LED
```

Consulta de ejemplo de uso completo en [`control_leds.py`](scripts/control_leds.py).

## Instalación

```bash
cd software/ia
python3 -m venv .venv
source .venv/bin/activate
pip install -r scripts/requirements.txt
```

## Notas de escalabilidad

- El clasificador puede pasarse de reglas (umbrales) a un **modelo entrenado** (p. ej. `sklearn` o `tensorflow`) sin tocar el módulo de control.
- Para IA embebida, convertir el modelo a `.tflite` y cargarlo con `tflite-micro` en el ESP32.
- Nuevas señales (acelerómetro, LDR) se integran como entradas adicionales al mismo clasificador.