# Estandarte LED IME — Gran Plan y Simulación

Repositorio del **Gran Plan de Trabajo y Simulación del Estandarte LED IME**
(Parada Universitaria 2026): un estandarte luminoso interactivo de la Escuela
Profesional de **Ingeniería Mecánica Eléctrica**, coordinado por tres ESP32 y
controlado por IA.

El repositorio incluye el plan integral, un simulador visual interactivo,
simulaciones Wokwi/PlatformIO y el firmware base de la arquitectura física.

## Contenido

| Carpeta | Descripción |
|---------|-------------|
| [`documentacion/gran_plan/`](documentacion/gran_plan/) | Plan de trabajo completo (PDF + LaTeX, 28 págs.) |
| [`simulacion_visual/`](simulacion_visual/) | Simulador HTML interactivo del estandarte (abrir en navegador) |
| [`software/simulaciones/wokwi/`](software/simulaciones/wokwi/) | Simulación integrada en Wokwi (navegador) |
| [`software/simulaciones/platformio/`](software/simulaciones/platformio/) | Proyecto local VS Code + PlatformIO + Wokwi |
| [`software/firmware/`](software/firmware/) | Firmware: arquitectura 3× ESP32 + prototipo IA |
| [`hardware/`](hardware/) | Circuito, esquemático y guía de montaje |
| [`documentacion/`](documentacion/) | Informe, control y documentación general |
| [`recursos/`](recursos/) | QR de acceso, capturas y recursos |

## Empezar (guía rápida)

1. Lee el plan: [`documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.pdf`](documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.pdf).
2. Abre el simulador visual en tu navegador: `simulacion_visual/Simulador_Visual_Estandarte_IME.html`.
3. Prueba la simulación Wokwi en línea (instrucciones en `software/simulaciones/wokwi/`).
4. Trabaja localmente con VS Code + PlatformIO (instrucciones en `software/simulaciones/platformio/`).
5. Para la fase física: revisa `software/firmware/arquitectura_3_esp32/`.

Detalles en [`INICIO.md`](INICIO.md).

## Arquitectura

```
   [Celular / página web] ──Wi-Fi──► [ESP32 CENTRAL] ──ESP-NOW──► [ESP32 MECÁNICA]
                                                        └──────► [ESP32 ELÉCTRICA]
```

- **Central**: red Wi-Fi `ESTANDARTE_IME`, página de control, envía comandos.
- **Mecánica / Eléctrica**: receptores ESP-NOW con tiras WS2812 y modo seguro.

## Modos de iluminación

Institucional · Flujo IME (Mecánica → Zeus → Eléctrica) · Audio/VU ·
Tormenta Zeus · Desfile · Apagado.

## Componentes principales

- 3× ESP32 (central, mecánica, eléctrica)
- Tiras WS2812 (5 V) y matriz 8×8 central (símbolo Zeus)
- Módulo micrófono MAX4466, botones, potenciómetros, OLED SSD1306
- Driver lógico 74AHCT125 (3.3 V → 5 V) y baterías independientes por módulo

## Estado

En desarrollo (simulación validada). La red ESP-NOW se prueba con placas
físicas o instancias Wokwi separadas.
