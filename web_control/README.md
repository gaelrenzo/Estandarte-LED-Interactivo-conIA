# Página Web de Control — Estandarte IME (Puno 2026)

Interfaz web interactiva para controlar el estandarte desde el teléfono o
computadora. Funciona en dos modos:

- **Con la ESP32 (firmware)** + la página incrustada (`web_interface.h`), servida
  en `http://192.168.4.1` dentro de la red Wi-Fi `ESTANDARTE_IME_PUNO`.
- **Como demo/despliegue estático** (este `index.html`) en Vercel o abriéndolo en
  el navegador, para revisar el diseño la control remoto sin hardware.

## Modos de iluminación

| Modo | Descripción |
|------|-------------|
| Institucional | Colores oficiales Celeste y Naranja IME |
| Flujo IME | Engranaje mecánico + rayo central |
| Audio / VU | LEDs reaccionan al micrófono del celular (Web Audio API) |
| Tormenta Zeus | Destellos estroboscópicos de alto brillo |
| Desfile | Arcoíris dinámico y festivo |
| Color Fijo | Selector de color RGB |
| Apagado | Standby para ahorrar batería |

## Características de la interfaz

- Selector de modo, brillo y velocidad.
- **Web Audio API** para enviar el nivel de audio del celular a los LEDs.
- **Guardar preset** en la memoria no volátil del ESP32 (`Preferences`).
- Diseño responsive (Outfit / Space Grotesk), optimizado para celular.

## Cómo usarla

### Con la ESP32
1. Carga el firmware [`software/firmware/version_minima_puno/`](../software/firmware/version_minima_puno/).
2. Conéctate a la red `ESTANDARTE_IME_PUNO` y abre `http://192.168.4.1`.
3. Usa los controles de la interfaz para cambiar modos, brillo y audio.

### Como página estática (demo)
Abre este `index.html` directamente en el navegador o usa el despliegue en
[Vercel](https://vercel.com).

## Despliegue (Vercel)

El archivo [`vercel.json`](../vercel.json) configura el despliegue estático
automático de esta página.

## Conexión con el firmware

El `index.html` aquí y el HTML incrustado en
`version_minima_puno/web_interface.h` comparten la misma interfaz. Al modificar
uno para la demo, replica los cambios en el otro para mantener la coherencia.