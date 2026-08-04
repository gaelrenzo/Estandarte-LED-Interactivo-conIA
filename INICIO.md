# Estandarte IME - Gran plan y simulación

## Comience aquí

1. Abra `documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.pdf`.
2. Abra `simulacion_visual/Simulador_Visual_Estandarte_IME.html` para ver la demostración interactiva.
3. Para ejecutar el firmware en línea, visite https://wokwi.com/projects/new/esp32 e importe los archivos de `software/simulaciones/wokwi/`.
4. Para trabajar localmente, abra `software/simulaciones/platformio/` con Visual Studio Code + PlatformIO + Wokwi.
5. La carpeta `software/firmware/arquitectura_3_esp32/` contiene la base de la versión física con ESP-NOW.

## Contenido principal

- **PDF y LaTeX:** plan integral de 28 páginas (`documentacion/gran_plan/`).
- **Simulador HTML:** estructura iluminada, circuito, drivers y red inalámbrica (`simulacion_visual/`).
- **Wokwi:** ESP32, dos tiras WS2812, matriz 8x8, OLED, botones y potenciómetros (`software/simulaciones/wokwi/`).
- **PlatformIO:** proyecto listo para compilar cuando las herramientas estén instaladas (`software/simulaciones/platformio/`).
- **Tres ESP32:** código base para central, Mecánica y Eléctrica (`software/firmware/arquitectura_3_esp32/`).

## Nota técnica

Wokwi no admite varios microcontroladores en un mismo proyecto. La simulación integrada valida los efectos con un ESP32; la red ESP-NOW debe probarse con tres placas reales o con instancias separadas.
