# Simulación integrada en Wokwi

Esta simulación usa un ESP32 virtual para representar las tres zonas del estandarte:

- GPIO 16: tira MECÁNICA (20 WS2812)
- GPIO 17: matriz central 8x8 (ZEUS / escuela)
- GPIO 18: tira ELÉCTRICA (20 WS2812)
- GPIO 34: nivel de sonido simulado
- GPIO 35: brillo
- GPIO 25/26/27: modo, color y secuencia
- GPIO 21/22: OLED SSD1306

## Abrir en Wokwi

1. Abra https://wokwi.com/projects/new/esp32
2. Reemplace `sketch.ino` por el archivo de esta carpeta.
3. Reemplace `diagram.json` por el archivo de esta carpeta.
4. Cree `libraries.txt` y copie su contenido.
5. Presione **Start Simulation**.

Wokwi no admite varios microcontroladores en un mismo proyecto. Esta simulación valida las animaciones y el cableado lógico; la red final de tres ESP32 se prueba con placas físicas o instancias separadas.
