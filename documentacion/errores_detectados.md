# Errores detectados en el repositorio

**Revisión:** 2026-08-04
**Fecha final del proyecto (dato externo):** 24 de agosto de 2026
**Equipo (dato externo):**
- Dilmar H. Siguayro Coila
- Aquiles T. Ramos Yapo
- Renzo G. Mamani Galindo
- Martin Calla Quispe
- Abel Y. Rivera Quispe

Escuela Profesional de Ingeniería Mecánica Eléctrica,
Universidad Nacional del Altiplano, Perú.

---

## 1. Datos de autores, universidad y fecha sin completar

| Archivo | Línea | Problema | Debe decir |
|---|---|---|---|
| `documentacion/informe/informe_final.md` | 5 | `**Fecha:** [completar]` | `24 de agosto de 2026` |
| `documentacion/informe/informe_final.md` | — | No declara autores ni universidad | Añadir autores y filiación |
| `documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.tex` | 163 | `Equipo: [Completar integrantes]` | Listar los 5 integrantes |
| `documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.tex` | 164 | `Universidad: [Completar]` | Universidad Nacional del Altiplano |
| `documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.tex` | 165 | `Responsable técnico: [Completar]` | Definir responsable |
| `documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.tex` | 66 | `pdfauthor={Equipo de Ingenieria Mecanica Electrica}` | Poner nombres de los autores |
| `INICIO.md` / `README.md` | — | Sin autores ni filiación | Añadir si corresponde |

### 1.1 Estado: resuelto ✅
- `informe_final.md`: fecha **24 de agosto de 2026**, 5 autores, filiación y responsable
  de asignatura (**Chura Acero Julio Fredy**).
- Portada del gran plan: equipo (5 integrantes), Universidad Nacional del Altiplano,
  Perú, y responsable de asignatura; `pdfauthor` con los nombres.

## 2. Fechas finales inconsistentes entre documentos

- `informe_final.md` declara **"Duración: 12 días"** (cronograma días 1–12).
- `Gran_Plan_...tex` declaraba **"Cronograma referencial de 30 días"** y su Gantt iba de
  **2026-08-05 a 2026-09-03** (con hito "Ensayo general" el 3 de septiembre).
- La fecha final indicada es el **24 de agosto de 2026**: el cronograma original
  **excedía en ~10 días** la fecha final del proyecto.

Con inicio el 5 de agosto y fin el 24 de agosto, la duración es de **20 días**,
que no coincide ni con los 12 del informe ni con los 30 del gran plan.

### 2.1 Estado: resuelto ✅
- Gantt comprimido a **2026-08-05 → 2026-08-24**: "Cronograma referencial de 20 días"
  y hito final "Ensayo general" el **24 de agosto de 2026** en
  `documentacion/gran_plan/Gran_Plan_Trabajo_Simulacion_Estandarte_IME.tex`.
- Pendiente de coherente: la "Duración: 12 días" del informe (alcance distinto, 1 ESP32
  reactivo al sonido).

## 3. Incoherencia de alcance entre informe y gran plan

- El `informe_final.md` describe un estandarte **reactivo al sonido con 1 ESP32**
  y resultados de prototipo físico (60 LED, ~3,6 A).
- El gran plan y el `README.md` describen **3 estandartes con 3 ESP32 + ESP-NOW**
  y estado "Simulación inicial preparada".
- Ambas versiones conviven en el repositorio sin indicar cuál es la definitiva.

## 4. Rutas y nombres de archivo que no coinciden con el repositorio real

- El árbol "Estructura incluida en el paquete" (`Gran_Plan_...tex`, líneas 883–908)
  usaba carpetas `wokwi_integrado/`, `platformio_simulacion/`, `arquitectura_3_esp32/`
  que no existen en el repositorio (están en `software/...`).
- Los Anexos D, E y F referenciaban archivos con **guion**: `central-maestro.ino`,
  `receptor-mecanica.ino`, `receptor-electrica.ino`; los archivos reales usan
  **guion bajo**: `central_maestro.ino`, `receptor_mecanica.ino`, `receptor_electrica.ino`.
- `\graphicspath{{recursos/}{diagramas/}}` (línea 16): las imágenes QR y la captura
  están en `recursos/` de la **raíz** del repositorio, no en `documentacion/gran_plan/`.

### 4.1 Estado: resuelto ✅
- Rutas de los Anexos A–F corregidas a la estructura real (`../../software/...`).
- `\graphicspath` incluye `../../recursos/` para localizar QR y captura.
- Árbol "Estructura del repositorio" actualizado a la estructura real.
- Añadido `literate` al estilo de código para acentos en los `.ino` (`ñ`, etc.).
- El PDF se recompiló correctamente (`pdflatex`, 3 pasadas, sin errores).

## 5. Recursos pendientes

- `hardware/circuito/imagenes/` solo contiene `.gitkeep`; falta subir las fotos de
  protoboard y soporte que el informe y `hardware/circuito/README.md` declaran como pendientes.
- `hardware/circuito/diagramas/` solo tiene `esquematico.svg`; verificar si faltan más diagramas.

## 6. Contenido por definir (placeholders)

- BOM del gran plan: cantidad de tiras WS2812B **"Por definir"**.
- Tabla de presupuesto ("Cuadro para completar cotizaciones") **vacía**.
- `hardware/circuito/README.md` línea 15: marcado `(pendiente)` para las fotos.

## 7. Estado del proyecto contradictorio

- Gran plan (portada): `Estado: Simulación inicial preparada`.
- `README.md`: "En desarrollo (simulación validada)".
- `informe_final.md`: reporta un prototipo físico con mediciones y resultados.

---

**Conclusión:** los errores más urgentes son: completar autores/fecha en `informe_final.md`
y en la portada del gran plan (fecha final 24 de agosto), comprimir el cronograma para que
termine el 24 de agosto, y corregir las rutas/nombres de archivos del `.tex` para que el PDF
se compile correctamente con la estructura real del repositorio.
