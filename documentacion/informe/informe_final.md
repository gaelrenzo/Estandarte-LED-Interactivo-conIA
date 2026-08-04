# Informe Final: Estandarte LED Interactivo con IA

**Proyecto:** Estandarte LED Interactivo con IA
**Duración:** 12 días
**Fecha:** [completar]

---

## 1. Introducción

Este proyecto consiste en un estandarte luminoso interactivo controlado por un
microcontrolador **ESP32**, equipado con tiras LED **WS2812** y un **módulo
micrófono MAX4466**. La propuesta combina **electrónica**, **programación de
microcontroladores** e **inteligencia artificial** para crear una iluminación
reactiva al sonido ambiente: la luz cambia de intensidad, color y patrón según
la música, la voz o el ruido captados.

El objetivo principal es validar un flujo de trabajo completo y documentado:
diseño de hardware, desarrollo de firmware, integración de IA y control, en un
cronograma de 12 días, dejando la documentación lista para escalar el proyecto.

## 2. Metodología

El desarrollo siguió un cronograma de 12 días en 4 etapas:

| Días | Etapa | Actividades |
|------|-------|-------------|
| 1–3 | Diseño y prueba del circuito | Esquemático, montaje en protoboard, pruebas de tiras WS2812 y micrófono, verificación de alimentación. |
| 4–6 | Programación del microcontrolador | Firmware ESP32: lectura ADC, animaciones FastLED, protocolo serial con IA. |
| 7–9 | Integración de la IA | Captura de audio, detección de ritmo, clasificación (música/voz/ruido) y mapeo a comandos. |
| 10–11 | Documentación y pruebas finales | READMEs, diagramas, ajustes de control y pruebas de integración. |
| 12 | Informe final | Elaboración de este documento. |

### 2.1 Herramientas

- **Hardware**: ESP32 DevKit, MAX4466, tiras WS2812 (5 V), fuente 5 V.
- **Firmware**: Arduino/PlatformIO con FastLED.
- **IA**: Python 3, numpy, scipy, sounddevice, pyserial.
- **Control**: teoría de control clásica (ver `../control/analisis_control.md`).

### 2.2 Criterios de éxito

- Los LED reaccionan al nivel de audio en menos de ~100 ms.
- El sistema distingue música, voz y ruido con precisión aceptable.
- El firmware es extensible: agregar efectos no requiere reescribir el núcleo.

## 3. Resultados

### 3.1 Circuito

- Se montó el circuito completo en protoboard y luego en el soporte del
  estandarte.
- Con 60 LED, la corriente máxima medida fue ~3.6 A a blanco completo, dentro
  de la capacidad de la fuente de 5 A.

### 3.2 Firmware

- Lectura de audio estable mediante promediado y ventana deslizante.
- Tres efectos base implementados: `vu`, `wave`, `strobe`.
- Protocolo serial funcional: `set`, `int`, `color`.

### 3.3 IA

- Pipeline de 4 etapas funcionando: captura → ritmo → clasificación → control.
- El clasificador heurístico distinguió música, voz y ruido en pruebas
  controladas; se dejó la interfaz lista para sustituirlo por un modelo ML.

### 3.4 Control

- Se aplicó un **control proporcional** del brillo respecto al nivel de audio,
  con suavizado (filtro de media móvil) para evitar parpadeos.
- La respuesta temporal fue estable y sin oscilaciones visibles.

## 4. Conclusiones

- El objetivo se cumplió: un estandarte reactivo al sonido con base de IA,
  documentado para escalabilidad.
- Las etapas más valiosas para la trazabilidad fueron las pruebas tempranas del
  circuito (días 1–3) y la separación modular firmware/IA.
- **Limitaciones**: el clasificador heurístico es simple; para mayor robustez se
  recomienda un modelo entrenado o IA embebida (tflite-micro).

## 5. Trabajo futuro

- Entrenar un clasificador con dataset propio y convertirlo a TensorFlow Lite.
- Agregar más sensores (LDR, acelerómetro) como entradas de interacción.
- Implementar control en lazo cerrado con sensor de luminosidad (fotodiodo).
- Publicar diagramas eléctricos en Fritzing/KiCad.

---

**Anexos:** diagramas en `hardware/circuito/diagramas/`, fotos en
`hardware/circuito/imagenes/`, código en `software/`.