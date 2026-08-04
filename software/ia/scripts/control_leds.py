"""
control_leds.py
===============
Toma las decisiones finales y envía comandos al ESP32 por serial.

Paso 4 del pipeline IA y conexión con el firmware. Convierte las
entradas del resto de módulos (nivel, BPM, clase) en comandos como
`set vu`, `int 80`, `color 255,0,0`.
"""

import time

import serial

from audio_capture import abrir, leer_bloque, RATE
from clasificador import clasificar
from detectar_ritmo import EstimadorBPM, detectar_pico

# Puerto serie del ESP32 (ajustar en Windows: COMx)
PUERTO = "/dev/ttyUSB0"
BAUD = 115200

# Paletas según clase de audio
PALETAS = {
    "musica":   ("wave",  (255, 120, 0)),
    "voz":      ("vu",    (0, 200, 255)),
    "ruido":    ("strobe",(255, 0, 0)),
    "silencio": ("off",   (0, 0, 0)),
}


def enviar(ser, comandos):
    """Envía una lista de comandos al ESP32."""
    for c in comandos:
        ser.write((c + "\n").encode())
        time.sleep(0.02)
        echo = ser.readline().decode().strip()
        if echo:
            print("ESP32 <-", echo)


def elegir_comandos(nivel, bpm, clase):
    """Cartografía nivel/BPM/clase -> lista de comandos serial."""
    efecto, color = PALETAS.get(clase, PALETAS["musica"])
    com = [f"set {efecto}"]
    # Intensidad proporcional al nivel, con saturación en 100
    com.append(f"int {int(min(100, max(0, nivel * 120)))}")
    com.append(f"color {color[0]},{color[1]},{color[2]}")
    return com


def bucle():
    ser = serial.Serial(PUERTO, BAUD, timeout=1)
    time.sleep(2)  # esperar reinicio del ESP32

    abrir()  # stream de audio
    energia_hist = []
    estimador = EstimadorBPM()

    print("Control en marcha... Ctrl+C para salir.")
    try:
        while True:
            audio, nivel = leer_bloque()
            clase = clasificar(audio, RATE)

            energia_hist.append(nivel * 100)
            energia_hist = energia_hist[-30:]

            if detectar_pico(energia_hist):
                estimador.registrar_pico(time.time())
            bpm = estimador.bpm

            comandos = elegir_comandos(nivel, bpm, clase)
            enviar(ser, comandos)
            print(f"nivel={nivel:5.3f} bpm={bpm:3d} clase={clase}")
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("\nFin.")


if __name__ == "__main__":
    bucle()
