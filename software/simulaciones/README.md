# Simulaciones

Índice de las simulaciones del estandarte IME. Todas reproducen la misma
firmware/estructura; cambia el entorno de ejecución.

## Opciones

| Carpeta | Entorno | Cómo se usa |
|---------|---------|-------------|
| [`wokwi/`](wokwi/) | Wokwi (navegador) | Importa `sketch.ino`, `diagram.json` y `libraries.txt` en https://wokwi.com/projects/new/esp32 |
| [`platformio/`](platformio/) | VS Code + PlatformIO + Wokwi | Abre la carpeta como proyecto y ejecuta Build / Start Simulator |

## ¿Cuál usar?

- **Ruta rápida**: Wokwi en el navegador, sin instalar nada.
- **Ruta profesional**: PlatformIO para compilar localmente y simular con la
  extensión Wokwi de VS Code.

## Nota técnica

Ambas simulaciones usan **un solo ESP32** que representa las tres zonas
(MECÁNICA, CENTRO, ELÉCTRICA). La red final de tres ESP32 se prueba con placas
físicas (ver `../firmware/arquitectura_3_esp32/`).
