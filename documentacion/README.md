# Documentación

> Índice general de toda la documentación del **Estandarte LED IME**.

[![Plan](https://img.shields.io/badge/Plan-PDF%2BLaTeX-2b7f3b)](gran_plan/) [![Informe](https://img.shields.io/badge/Informe-final-ffb300)](informe/informe_final.md) [![Control](https://img.shields.io/badge/Control-luces-15a0d8)](control/analisis_control.md)

## Índice

- [Documentos incluidos](#documentos-incluidos)
- [Para qué sirve cada documento](#para-qué-sirve-cada-documento)
- [Generar el PDF desde LaTeX](#generar-el-pdf-desde-latex)
- [Guía de lectura](#guía-de-lectura)

## Documentos incluidos

| Carpeta | Contenido | Descripción |
|---------|-----------|-------------|
| `gran_plan/` | `Gran_Plan_Trabajo_Simulacion_Estandarte_IME.pdf` + `.tex` | Plan integral del proyecto (28 págs.): simulación, arquitectura, potencia. |
| `informe/` | `informe_final.md` | Informe final: introducción, metodología, resultados y conclusiones. |
| `control/` | `analisis_control.md` | Análisis del sistema de control de luces e interacción. |

## Para qué sirve cada documento

- **Gran plan (PDF/LaTeX)**: documento principal del proyecto, con instalación
  paso a paso del entorno, simulación, distribución de pines, modos de
  iluminación, arquitectura de tres ESP32 y dimensionamiento de potencia.
- **Informe final**: presentación académica con resultados y conclusiones.
- **Análisis de control**: cómo se traduce el audio en brillo/efecto y cómo
  mejorar la respuesta (filtros, PID, lazo cerrado).

## Generar el PDF desde LaTeX

```bash
cd documentacion/gran_plan
pdflatex Gran_Plan_Trabajo_Simulacion_Estandarte_IME.tex
# repetir si aparece "Rerun to get cross-references right"
```

## Guía de lectura

1. Empieza por el [`README.md`](../../README.md) raíz.
2. Abre el **gran plan** para el contexto completo.
3. Revisa `../simulacion_visual/` para la demo interactiva.
4. Revisa `../software/` para código y simulaciones.
5. Cierra con `informe/` (resultados) y `control/` (teoría de control).
