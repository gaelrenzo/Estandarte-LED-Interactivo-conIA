"""
audio_capture.py
----------------
Captura audio en tiempo real y calcula el nivel RMS por ventana.

Paso 1 del pipeline de IA. Produce una señal de nivel normalizado
(0.0 - 1.0) que consume el resto de módulos.
"""

import numpy as np
import sounddevice as sd

# Parámetros de captura
RATE = 16000        # Hz (suficiente para análisis de energía)
CHUNK = 1024        # muestras por ventana

_dev = None


def abrir(rate=RATE, chunk=CHUNK):
    """Abre el stream de audio y lo guarda en el módulo."""
    global _dev
    _dev = sd.InputStream(samplerate=rate, channels=1, dtype="float32",
                          blocksize=chunk)
    _dev.start()
    return _dev


def leer_bloque(chunk=CHUNK):
    """Lee un bloque de audio y devuelve el nivel RMS normalizado.

    Retorna (audio, nivel) donde audio es el array de flotantes y
    nivel es un valor 0.0-1.0 proporcional a la energía.
    """
    datos, _ = _dev.read(chunk)
    audio = datos[:, 0]
    rms = float(np.sqrt(np.mean(audio ** 2)))
    # Normalización empírica: niveles RMS > 0.3 se saturan a 1.0
    nivel = min(1.0, rms / 0.3)
    return audio, nivel


if __name__ == "__main__":
    import time

    abrir()
    print("Capturando audio... Ctrl+C para salir.")
    try:
        while True:
            _, nivel = leer_bloque()
            barras = int(nivel * 50)
            print(f"\r{'#' * barras:<50} {nivel:6.3f}", end="", flush=True)
            time.sleep(0.03)
    except KeyboardInterrupt:
        print("\nFin.")
