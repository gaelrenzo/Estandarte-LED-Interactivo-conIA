# 🛠️ Guía de Montaje Rápido con Componentes MÍNIMOS (Puno 2026)

Esta versión ha sido optimizada especialmente para ser montada y ejecutada en **Puno** con la menor cantidad de componentes posibles y el presupuesto más accesible, manteniendo una estética visual impactante para la **Parada Universitaria IME 2026**.

---

## ⚡ ¿Por qué esta versión para Puno?

1. **Solo 1 ESP32:** No necesitas comprar 3 placas ni configuraciones complejas de red ESP-NOW.
2. **Sin integrados difíciles de conseguir:** No requiere el driver lógico `74AHCT125` ni módulos de micrófono `MAX4466`.
3. **Micrófono del Celular:** La página web del celular transmite la música/gritos del desfile a los LEDs en tiempo real por Wi-Fi.
4. **Alimentación Simple:** Funciona con cualquier **Power Bank** o cargador portátil USB de 5V.
5. **Reserva manual:** Si no tienes celular a la mano durante el recorrido, presiona el botón **BOOT** de la misma placa ESP32 para cambiar los modos manualmente.

---

## 📦 Lista de Materiales Mínimos

| Componente | Cantidad | Notas / Alternativa local en Puno |
|------------|----------|-----------------------------------|
| **ESP32 DevKit V1** (30 pines) | 1 unidad | Placa microcontroladora principal. |
| **Tira LED WS2812B (5V)** | 1 a 2 metros | Tira direccionable RGB (60 leds/metro recomendados). |
| **Power Bank USB (5V / 2A+)** | 1 unidad | Batería portátil para celulares (mínimo 5000 mAh para 2-3 horas). |
| **Cable micro-USB o Tipo C** | 1 unidad | Para energizar la ESP32 desde la batería portátil. |
| **Cables Dupont / Calibre 22** | 3 hilos | Para conectar VCC (+5V), GND (Tierra) y DATOS (DIN). |

---

## 🔌 Diagrama de Conexión Ultrasimple

```text
[ Power Bank / Batería 5V ] ──────► Conectado por Cable USB al puerto del ESP32
                                  │
                                  ├─► 5V (VIN)  ───► (+) VCC Tira WS2812B (Cable Rojo)
                                  └─► GND       ───► (-) GND Tira WS2812B (Cable Blanco/Negro)

[ ESP32 Pin GPIO 13 ] ─────────────────────────────► DIN Tira WS2812B (Cable Verde)
[ ESP32 Pin BOOT (GPIO 0) ] ──────────────────────── Botón integrado en la misma placa
```

---

## 📱 Pasos para Cargar y Usar

### Paso 1: Compilar y Cargar el Código
1. Abre el programa **Arduino IDE** en tu computadora.
2. Instala la librería **FastLED** (`Programa` -> `Incluir Librería` -> `Administrar Librerías` -> Buscar `FastLED`).
3. Abre el archivo `software/firmware/version_minima_puno/version_minima_puno.ino`.
4. Selecciona la placa `DOIT ESP32 DEVKIT V1` y el puerto COM correspondiente.
5. Haz clic en **Subir** (Upload).

### Paso 2: Conectar al Estandarte
1. Enciende la batería portátil (Power Bank) y conecta el cable USB al ESP32.
2. En tu celular, abre la configuración de **Wi-Fi**.
3. Conéctate a la red llamada: **`ESTANDARTE_IME_PUNO`** (red libre sin contraseña).
4. Abre tu navegador (Chrome, Safari o Firefox) e ingresa a: **`http://192.168.4.1`**

---

## 🎨 Modos Disponibles desde la Página Web

- 🏛️ **Institucional:** Colores oficial Celeste y Naranja IME.
- ⚙️ **Flujo IME:** Efectos de engranaje mecánico y rayo central.
- 🎤 **Audio / VU:** Activa el botón "Activar Mic" en tu celular para que los LEDs respondan a la banda de música y los aplausos.
- 🌩️ **Tormenta Zeus:** Destellos estroboscópicos de alto brillo.
- 🎉 **Desfile IME:** Arcoíris dinámico y festivo.
- 🎨 **Color Fijo:** Picker de color directo para elegir cualquier tono RGB.
- 🔴 **Apagado:** Standby para conservar batería.

---

## 💡 Consejos para la Parada Universitaria 2026 en Puno

- **Brillo recomendado:** Mantén el brillo en **70%-80%** en la página web. Esto reduce el consumo de la batería y evita calentamientos.
- **Memoria permanente:** Puedes presionar **"💾 Guardar Preset"** en la web. Al desconectar y volver a conectar la batería en la calle, el estandarte encenderá directamente en el modo que guardaste.
