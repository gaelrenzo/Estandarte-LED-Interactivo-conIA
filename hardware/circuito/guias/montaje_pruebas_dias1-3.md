# Montaje y Pruebas del Circuito (Días 1–3)

Guía paso a paso para ensamblar el circuito en protoboard y probar cada etapa.
Complementa el [`esquematico.svg`](../diagramas/esquematico.svg).

---

## Día 1 · Preparación y conexión de alimentación

### Materiales
- ESP32 DevKit, módulo micrófono MAX4466, tira WS2812, resistencia 330 Ω,
  condensador 1000 µF, cables dupont, fuente 5 V, protoboard.

### Pasos
1. **No conectar nada alimentado todavía.** Con la fuente apagada, monta los
   componentes en el protoboard según el esquemático.
2. Conecta la **fuente 5 V** a la tira: `VCC` (+) y `GND` (−).
3. Coloca el condensador **1000 µF** entre `VCC` y `GND` de la tira, lo más
   cerca posible de su conector de entrada.
4. Aplica 5 V y mide con multímetro: debe leerse **5.0 V** en la tira y una
   **caída mínima** al encender los LED (ver prueba del día 2).

> ⚠️ **Regla de oro:** tierra común. Todos los GND (fuente, ESP32, mic, tira)
> deben estar unidos para que la señal del micrófono sea estable.

---

## Día 2 · Prueba de las tiras WS2812

### Objetivo
Verificar que el ESP32 controla correctamente los LED.

1. Conecta `GPIO5 → resistencia 330 Ω → DIN` de la tira.
2. Conecta GND del ESP32 a GND común.
3. Alimenta el ESP32 por USB (para programarlo).
4. Carga un sketch de prueba con FastLED: `FirstLight` (barrido de colores).

```cpp
// PrimeraPrueba.ino — barrido de colores
#include <FastLED.h>
#define PIN_LED 5
#define NUM 60
CRGB leds[NUM];
void setup(){ FastLED.addLeds<WS2812, PIN_LED, GRB>(leds, NUM); }
void loop(){
  for(int i=0;i<NUM;i++){ leds[i]=CRGB::Red; FastLED.show(); delay(30); }
  FastLED.clear(); FastLED.show(); delay(300);
}
```

5. **Resultado esperado:** los LED se encienden en secuencia de rojo del 1 al 60.
   - Si no encienden: revisa polaridad de DIN y la resistencia.
   - Si se ven "suelto" o aleatorios: revisa la masa común y la fuente.

> Si la tira titila al encender muchos LED, tu fuente o el condensador son
> insuficientes (requisito: ≥ 5 A y 470–1000 µF).

---

## Día 3 · Prueba del micrófono MAX4466

### Objetivo
Verificar que el ADC lee la señal de audio y ajustar la ganancia.

1. Conexiones: `VCC → 3V3`, `GND → común`, `OUT → GPIO34`.
2. Carga un sketch que imprima el valor del ADC por serial:

```cpp
// PruebaMic.ino
void setup(){ Serial.begin(115200); analogSetPinAttenuation(34, ADC_11db); }
void loop(){ Serial.println(analogRead(34)); delay(50); }
```

3. Abre el monitor serie a **115200**.
4. **En silencio:** el valor debe ser más o menos estable (≈ 2000–3000).
5. **Aplaude o silba:** el valor debe fluctuar ampliamente.

### Ajuste de ganancia
- Gira el potenciómetro del MAX4466 hasta que los picos se acerquen a **4095**
  **sin recortarse** (valores planos de 4095 indican saturación).
- Con el firmware final, la lectura se normaliza a 0.0–1.0.

---

## Checklist de validación (días 1–3)

- [ ] 5.0 V medidos en la tira.
- [ ] Condensador entre VCC/GND cerca de la tira.
- [ ] Todos los GND conectados a tierra común.
- [ ] Resistencia 330 Ω entre GPIO5 y DIN.
- [ ] Barrido de colores funciona (60 LED en orden).
- [ ] No hay titileo al encender todos los LED.
- [ ] Micrófono muestra señal estable y reacciona al sonido.
- [ ] Ganancia ajustada sin saturar hacia 4095.