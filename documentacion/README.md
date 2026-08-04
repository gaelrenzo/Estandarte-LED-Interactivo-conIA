# Documentación

Índice general de toda la documentación técnica del **Estandarte LED Interactivo con IA**.

## Documentos incluidos

| Carpeta | Contenido | Descripción |
|---------|-----------|-------------|
| `informe/` | `informe_final.md` | Informe final del proyecto: introducción, metodología, resultados y conclusiones. |
| `control/` | `analisis_control.md` | Análisis del sistema de control de luces e interacción (lazo abierto/cerrado, PIDs, sintonización). |

## Para qué sirve cada documento

- **Informe final**: documento académico/técnico de presentación del proyecto, con resultados medidos y conclusiones.
- **Análisis de control**: explica cómo se traduce el nivel de audio en brillo/efecto, qué tipo de control se usa y cómo mejorarlo (respuesta temporal, filtros, estabilidad).

## Convenciones del proyecto

- Todos los README de carpetas explican el contenido y cómo usarlo.
- Los diagramas van en `hardware/circuito/diagramas/` y las fotos en `hardware/circuito/imagenes/`.
- Los documentos técnicos se escriben en Markdown para mantener versionado y trazabilidad.

## Guía de lectura

1. Empieza por el [`README.md`](../../README.md) raíz para el contexto.
2. Revisa `hardware/` para el montaje.
3. Revisa `software/` para el código y la IA.
4. Cierra con `informe/` (resultados) y `control/` (teoría de control aplicada).