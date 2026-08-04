# Análisis de Control de Luces e Interacción

Documento que explica la teoría de control aplicada al estandarte LED: cómo se
traduce el nivel de audio en brillo y efectos, y cómo mejorar la respuesta.

## 1. Planteamiento del sistema

El sistema puede verse como un lazo que va del sonido a la luz:

```
 Señal de entrada          Planta                    Salida
 [audio ambiente]  -->  [ESP32 + tiras LED] -->  [luz (brillo/color)]
```

- **Entrada**: nivel de audio normalizado 0.0–1.0 (medido por el ADC).
- **Planta**: tiras WS2812 (responden rápido, ancho de banda alto).
- **Salida**: brillo, color y patrón de los LED.

## 2. Tipo de control

### 2.1 Lazo abierto (implementado)
En la configuración actual **no hay sensor de retroalimentación de la luz**: se
le da un nivel y los LED lo dibujan. Es un **control en lazo abierto** proporcional.

```
referencia (audio)  -->  controlador  -->  planta (LED)  --> salida (luz)
```

Fórmula del brillo:
```
brillo = Kp * nivel
```
donde `Kp` es la ganancia proporcional (en firmware se limita a 0–255).

### 2.2 Lazo cerrado (propuesto en el futuro)
Para mantener una iluminación estable aunque cambie la temperatura de los LED o
la tensión, se puede cerrar el lazo con un **fotodiodo/LDR**:

```
r (brillo deseado)  -->  [error = r - y]  -->  controlador  -->  LED  -->  y (luz real)
                                                  ^                                 |
                                                  +--------  sensor (LDR) -----------+
```

## 3. Suavizado y filtrado (disminuye parpadeos)

El audio bruto tiene alta variación; aplicar un filtro de media móvil evita
que el brillo "vibre". En firmware:

```cpp
// media móvil sobre las últimas N muestras
promedio = (promedio * (N-1) + valor) / N;
```

## 4. Diseño con controlador proporcional + filtro

Dado un nivel de audio `a(t)` normalizado:

```
n(t)   = filtro_media(a(t))          // suavizado
u(t)   = Kp * n(t)                   // referencia de brillo
led(t) = sat(u(t), 0, 255)           // saturación a rango válido
```

- **Ganancia Kp** alta → reacción rápida, pero riesgo de oscilación/saturación.
- **Ganancia Kp** baja → luz suave, pero lenta.

En las pruebas `Kp ≈ 200` (sobre `n` normalizado) dio buena sensibilidad sin
oscilación. Con sensor en lazo cerrado, un **PID** de sintonización típica
`Kp=1.2, Ki=0.05, Kd=0.02` sobre el error de luminosidad.

## 5. Mapa de efectos por clase (interacción)

La IA clasifica el audio y el control selecciona efecto y color:

| Clase | Efecto | Intensidad | Descripción |
|-------|--------|-----------|-------------|
| música | `wave` | proporcional al BPM | ondas sincronizadas |
| voz | `vu` | proporcional al volumen | barras tipo VU metro |
| ruido | `strobe` | alta | destellos con picos |
| silencio | `off` | — | apagado/espera |

## 6. Métodos de prueba y verificación

1. **Escalón**: cambiar el nivel de audio de golpe y medir el tiempo de
   establecimiento (~50–100 ms) y el sobrepaso.
2. **Sonda PWM**: asegurar que el brillo no oscila en estado estable.
3. **Carga**: probar con todos los LED a bajo brillo para validar la fuente.

## 7. Conclusión y recomendaciones

- El control en lazo abierto es suficiente para la versión funcional.
- Para robustez y estabilidad (variaciones de temperatura y de fuente), se
  recomienda cerrar el lazo con un **fotodiodo** y usar un **PID** suave.
- Documentar la curva `entrada_nivel → brillo` facilita fijar la ganancia.

Resultados detallados en `informe/informe_final.md`.