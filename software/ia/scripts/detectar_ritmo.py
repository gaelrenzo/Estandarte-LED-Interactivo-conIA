"""
detectar_ritmo.py
=================
Detección de ritmo (BPM) y de picos de energía.

Paso 2 del pipeline IA. Entrega el BPM estimado y el flag de pico
(onset) para sincronizar destellos y ondas con la música.
"""

import numpy as np

RATE = 44100


def energia_por_banda(audio, rate=RATE):
    """Energía por bandas de frecuencia (baja, media, alta) vía FFT."""
    n = len(audio)
    win = np.hanning(n)
    espectro = np.abs(np.fft.rfft(audio * win))
    freqs = np.fft.rfftfreq(n, 1.0 / rate)
    bandas = {
        "baja": espectro[(freqs >= 40) & (freqs < 200)],
        "media": espectro[(freqs >= 200) & (freqs < 2000)],
        "alta": espectro[freqs >= 2000],
    }
    return {k: float(np.sum(v)) for k, v in bandas.items()}


def detectar_pico(energia_hist, umbral=0.5):
    """True si la última muestra de energía es un pico (onset).

    Usa la mediana de la ventana como referencia para ser robusto a
    señales planas o de fondo.
    """
    if len(energia_hist) < 3:
        return False
    ref = float(np.median(energia_hist))
    actual = energia_hist[-1]
    return actual > umbral * ref and actual == max(energia_hist[-3:])


class EstimadorBPM:
    """Estima el BPM acumulando los intervalos entre picos de energía."""

    def __init__(self, ventana_max=30):
        self.intervalos = []
        self.ultimo_t = None
        self.ventana_max = ventana_max

    def registrar_pico(self, t):
        if self.ultimo_t is not None:
            intervalo = t - self.ultimo_t
            if 0.25 < intervalo < 2.0:  # 30–240 BPM
                self.intervalos.append(intervalo)
                if len(self.intervalos) > self.ventana_max:
                    self.intervalos.pop(0)
        self.ultimo_t = t

    @property
    def bpm(self):
        if not self.intervalos:
            return 0.0
        return round(60.0 / (sum(self.intervalos) / len(self.intervalos)))


if __name__ == "__main__":
    import numpy as np

    # Señal de prueba: pulso a 120 BPM (periodo 0.5 s)
    t = np.linspace(0, 4, 4 * RATE, endpoint=False)
    pulso = (np.sin(t * 2 * np.pi * 10.0)) * (np.sin(t * 2 * np.pi * 2.0) > 0)

    print("Energía por banda:", energia_por_banda(pulso))

    est = EstimadorBPM()
    paso = int(RATE * 0.01)
    for i in range(0, len(pulso), paso):
        seg = pulso[i:i + paso]
        if np.max(np.abs(seg)) > 0.3:
            est.registrar_pico(i / RATE)
    print("BPM estimado:", est.bpm)