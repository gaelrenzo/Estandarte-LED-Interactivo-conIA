# Estandarte LED IME — Gran Plan y Simulación

Repositorio del **Gran Plan de Trabajo y Simulación del Estandarte LED IME**
(Parada Universitaria 2026): un estandarte luminoso interactivo de la Escuela
Profesional de **Ingeniería Mecánica Eléctrica**, coordinado por tres ESP32 y
controlado por IA.

El repositorio incluye el plan integral, un simulador visual interactivo,
simulaciones Wokwi/PlatformIO y el firmware base de la arquitectura física.

## Contenido

| Carpeta / Archivo | Descripción |
|-------------------|-------------|
| [`web_control/index.html`](web_control/index.html) | **Página web interactiva de control** (Puno 2026) |
| [`software/firmware/version_minima_puno/`](software/firmware/version_minima_puno/) | **Firmware 1× ESP32 + Componentes Mínimos Puno** |
| [`documentacion/gran_plan/`](documentacion/gran_plan/) | Plan de trabajo completo (PDF + LaTeX, 28 págs.) |
| [`simulacion_visual/`](simulacion_visual/) | Simulador HTML interactivo del estandarte (abrir en navegador) |
| [`software/simulaciones/wokwi/`](software/simulaciones/wokwi/) | Simulación integrada en Wokwi (navegador) |
| [`software/simulaciones/platformio/`](software/simulaciones/platformio/) | Proyecto local VS Code + PlatformIO + Wokwi |
| [`software/firmware/`](software/firmware/) | Firmware: arquitectura 3× ESP32 + prototipo IA |
| [`hardware/`](hardware/) | Circuito, esquemático y guía de montaje |
| [`documentacion/`](documentacion/) | Informe, control y documentación general |
| [`recursos/`](recursos/) | QR de acceso, capturas y recursos |

## Empezar (guía rápida)

1. **Montaje Mínimo Puno (1 ESP32):** Revisa [`software/firmware/version_minima_puno/GUIA_MONTAJE_PUNO.md`](software/firmware/version_minima_puno/GUIA_MONTAJE_PUNO.md).
2. **Página Web de Control:** Abre [`web_control/index.html`](web_control/index.html) en tu navegador o celular.
3. Lee el plan: [`documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.pdf`](documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.pdf).
4. Abre el simulador visual en tu navegador: `simulacion_visual/Simulador_Visual_Estandarte_IME.html`.
5. Prueba la simulación Wokwi en línea (instrucciones en `software/simulaciones/wokwi/`).
6. Para la fase física completa con 3 ESP32: revisa `software/firmware/arquitectura_3_esp32/`.

Detalles en [`INICIO.md`](INICIO.md).

## Arquitectura

### 1. Versión Componentes Mínimos (Puno 2026 - Recomendada)
```
   [Celular (Página Web)] ──Wi-Fi (AP)──► [1× ESP32 DevKit] ──GPIO 13──► [Tira LED WS2812B]
```
- **Sin integrados adicionales:** Utiliza el micrófono del celular vía Web Audio API y botón BOOT físico de la misma ESP32.

### 2. Versión Completa Avanzada (3× ESP32)
```
   [Celular / página web] ──Wi-Fi──► [ESP32 CENTRAL] ──ESP-NOW──► [ESP32 MECÁNICA]
                                                        └──────► [ESP32 ELÉCTRICA]
```

- **Central**: red Wi-Fi `ESTANDARTE_IME`, página de control, envía comandos.
- **Mecánica / Eléctrica**: receptores ESP-NOW con tiras WS2812 y modo seguro.

## Modos de iluminación

Institucional · Flujo IME (Mecánica → Zeus → Eléctrica) · Audio/VU (Vía Mic Web o Físico) ·
Tormenta Zeus · Desfile · Color Fijo · Apagado.

## Componentes principales

- **Opción A (Puno Mínimo):** 1× ESP32 + 1× Tira WS2812B + 1× Power Bank USB.
- **Opción B (Avanzada 3 ESP32):** 3× ESP32, tiras WS2812, matriz 8×8, módulo MAX4466, driver 74AHCT125 y OLED SSD1306.

## Estado

Firmware y control web probados y listos para carga física en ESP32 y pruebas en Puno.
