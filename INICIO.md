# Estandarte IME - Gran plan y simulación

## Comience aquí

1. **Página Web de Control (Celular/PC):** Abra [`web_control/index.html`](web_control/index.html) para controlar los modos, brillo, velocidad y reactividad por micrófono de celular.
2. **Firmware Mínimo Puno (1 ESP32):** Abra la guía [`software/firmware/version_minima_puno/GUIA_MONTAJE_PUNO.md`](software/firmware/version_minima_puno/GUIA_MONTAJE_PUNO.md) y cargue `version_minima_puno.ino`.
3. Abra `documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.pdf`.
4. Abra `simulacion_visual/Simulador_Visual_Estandarte_IME.html` para ver la demostración interactiva.
5. Para la arquitectura completa de 3 ESP32, consulte `software/firmware/arquitectura_3_esp32/`.

## Contenido principal

- **Web Control (Puno):** Aplicación web táctil moderna para smartphone con audio reactivo (`web_control/`).
- **Versión Mínima ESP32:** Código Arduino listo con servidor web embebido y memoria EEPROM (`software/firmware/version_minima_puno/`).
- **PDF y LaTeX:** plan integral de 28 páginas (`documentacion/gran_plan/`).
- **Simulador HTML:** estructura iluminada, circuito, drivers y red inalámbrica (`simulacion_visual/`).
- **Wokwi:** ESP32, dos tiras WS2812, matriz 8x8, OLED, botones y potenciómetros (`software/simulaciones/wokwi/`).
- **PlatformIO:** proyecto listo para compilar (`software/simulaciones/platformio/`).
- **Tres ESP32:** código base para central, Mecánica y Eléctrica (`software/firmware/arquitectura_3_esp32/`).


## Nota técnica

Wokwi no admite varios microcontroladores en un mismo proyecto. La simulación integrada valida los efectos con un ESP32; la red ESP-NOW debe probarse con tres placas reales o con instancias separadas.
