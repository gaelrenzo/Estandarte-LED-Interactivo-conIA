"""
clasificador.py
===============
Clasifica el audio en clases simples (musica, voz, ruido) a partir de
características extraídas de cada ventana.

Paso 3 del pipeline IA. Usa reglas interpretables; puede sustituirse
por un modelo ML (sklearn/tensorflow) manteniendo la misma interfaz.
"""

import numpy as np

from detectar_ritmo import energia_por_banda, RATE


def extraer_features(audio, rate=RATE):
    """Vector de características de una ventana de audio."""
    bandas = energia_por_banda(audio, rate)
    total = sum(bandas.values()) or 1.0
    return {
        "rms": float(np.sqrt(np.mean(audio ** 2))),
        "zcr": float(np.mean(np.abs(np.diff(np.sign(audio)))) / 2),  # cruces por cero
        "proporcion_media": bandas["media"] / total,
        "proporcion_aguda": bandas["alta"] / total,
    }


def clasificar(audio, rate=RATE, hist=None):
    """Devuelve una de las clases: 'musica', 'voz' o 'ruido'.

    Reglas heurísticas:
      - 'voz': muchas cruces por cero y energía repartida en medios.
      - 'musica': energía concentrada en graves/bajos + ritmo.
      - 'ruido': alta energía de agudos con RMS bajo.
    """
    f = extraer_features(audio, rate)
    zcr = f["zcr"]
    rms = f["rms"]

    if rms < 0.02:
        return "silencio"
    if zcr > 0.1 and f["proporcion_media"] > 0.35:
        return "voz"
    if f["proporcion_aguda"] > 0.5:
        return "ruido"
    return "musica"


if __name__ == "__main__":
    import sounddevice as sd

    sr = RATE
    dev = sd.InputStream(samplerate=sr, channels=1, dtype="float32", blocksize=2048)
    dev.start()
    print("Clasificando en vivo... Ctrl+C para salir.")
    try:
        while True:
            datos, _ = dev.read(2048)
            print("\r", clasificar(datos[:, 0], sr), end="", flush=True)
    except KeyboardInterrupt:
        print("\nFin.")
