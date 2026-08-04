<div align="center">

# Estandarte LED IME

**Estandarte luminoso interactivo de Ingeniería Mecánica Eléctrica**  
Coordinación inalámbrica de ESP32 · Tiras WS2812 · Control por IA

**Autor:** *Steven Alex Mayta Lampa* · Parada Universitaria 2026

![Placa](https://img.shields.io/badge/Placa-ESP32-15a0d8)
![LED](https://img.shields.io/badge/LED-WS2812-orange)
![Red](https://img.shields.io/badge/Red-ESP--NOW-00aeef)
![Simulación](https://img.shields.io/badge/Simulaci%C3%B3n-Wokwi%20%7C%20PlatformIO-2b7f3b)
![Estado](https://img.shields.io/badge/Estado-En%20desarrollo-ffb300)

</div>

---

## Descripción

El **Estandarte LED IME** es un estandarte luminoso e interactivo de la Escuela
Profesional de **Ingeniería Mecánica Eléctrica**, presentado en la **Parada
Universitaria 2026**. Combina tiras LED **WS2812**, módulos **ESP32** y una
**página web de control** (Web Audio API) para crear iluminación reactiva y
sincronizada.

Este repositorio reúne el **plan integral**, un **simulador visual interactivo**,
las **simulaciones Wokwi/PlatformIO**, el **firmware** para ambas versiones
(mínima 1× ESP32 y avanzada 3× ESP32) y la **página web de control**.

## Características

- **Dos versiones de montaje:** mínima (1× ESP32, Puno 2026) y avanzada (3× ESP32)
- Control desde el **celular** vía página web local con **Web Audio API**
- **Modos de iluminación:** Institucional, Flujo IME, Audio/VU (mic web o físico),
  Tormenta Zeus, Desfile, Color fijo y Apagado
- Modo seguro por módulo si se pierde el enlace inalámbrico
- Módulo micrófono **MAX4466**, botones, potenciómetros y OLED SSD1306 (versión avanzada)
- Despliegue web automático con **Vercel**

## Arquitectura

### 1. Versión Componentes Mínimos (Puno 2026 — Recomendada)
```
[Celular (Página Web)] ──Wi-Fi (AP)──► [1× ESP32 DevKit] ──GPIO 13──► [Tira LED WS2812B]
```
Sin integrados adicionales: usa el **micrófono del celular** (Web Audio API) y el
**botón BOOT** físico de la propia ESP32.

### 2. Versión Completa Avanzada (3× ESP32)
```
[Celular / página web] ──Wi-Fi──► [ESP32 CENTRAL] ──ESP-NOW──► [ESP32 MECÁNICA]
                                                    └──────────────► [ESP32 ELÉCTRICA]
```

| Nodo | Rol |
|------|-----|
| **Central** | Crea la red Wi-Fi `ESTANDARTE_IME`, página de control, envía comandos ESP-NOW |
| **Mecánica** | Receptor, controla su tira WS2812, modo seguro al perder enlace |
| **Eléctrica** | Receptor, controla su tira WS2812, modo seguro al perder enlace |

## Contenido del repositorio

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

## Guía rápida

### Opción A — Montaje Mínimo Puno (1× ESP32)
1. Revisa [`software/firmware/version_minima_puno/GUIA_MONTAJE_PUNO.md`](software/firmware/version_minima_puno/GUIA_MONTAJE_PUNO.md) y el [`DIAGRAMA_CONEXION_MINIMO.md`](software/firmware/version_minima_puno/DIAGRAMA_CONEXION_MINIMO.md).
2. Abre [`web_control/index.html`](web_control/index.html) en tu navegador o celular.
3. Materiales: **1× ESP32 + 1× Tira WS2812B + 1× Power Bank USB**.

### Opción B — Avanzada (3× ESP32)
1. **Lee el plan** → [`documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.pdf`](documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.pdf)
2. **Prueba la demo** → abre `simulacion_visual/Simulador_Visual_Estandarte_IME.html`
3. **Simula en línea** → Wokwi: [`software/simulaciones/wokwi/`](software/simulaciones/wokwi/)
4. **Fase física** → [`software/firmware/arquitectura_3_esp32/`](software/firmware/arquitectura_3_esp32/)
5. Materiales: **3× ESP32**, tiras WS2812, matriz 8×8, módulo MAX4466, driver 74AHCT125 y OLED SSD1306.

Detalle completo en [`INICIO.md`](INICIO.md).

## Presupuesto de materiales (referencial)

| Versión | Electrónica | Con baterías | Total |
|---------|-------------|--------------|-------|
| **Mínima Puno** (1× ESP32) | ≈ $12 | +$7 | **≈ $20** |
| **Avanzada** (3× ESP32) | ≈ $56 | +$20 | **≈ $90–130** |

*(Precios LCSC reales; ver desglose en `documentacion/informe/informe_final.md`.)*

## Estado del proyecto

| Etapa | Estado |
|-------|--------|
| Plan integral | Listo (PDF + LaTeX) |
| Simulador visual HTML | Funcional |
| Simulación Wokwi | Validada (un ESP32 con 3 zonas) |
| Simulación PlatformIO | Lista para compilar |
| Página web de control | Desplegada (Vercel) |
| Firmware mínima Puno | Probado, listo para carga física |
| Arquitectura 3× ESP32 | Base lista, pendiente prueba física |

---

<p align="center">Hecho con <code>ESP32</code> · <code>FastLED</code> · <code>Web Audio API</code> · <code>Vercel</code> · <code>Wokwi</code> · <code>PlatformIO</code></p>