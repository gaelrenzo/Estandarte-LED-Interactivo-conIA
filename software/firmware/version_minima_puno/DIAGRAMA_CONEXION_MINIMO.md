# 🔌 Diagrama de Conexiones Eléctricas Mínimas (ESP32 + WS2812B)

Este esquema representa la conexión directa sin componentes adicionales para ensamble rápido en Puno.

```
       ┌───────────────────────────────┐
       │   POWER BANK / BATERÍA USB    │
       │           (5V / 2.1A)         │
       └───────────────┬───────────────┘
                       │ [Cable USB]
                       ▼
            ┌─────────────────────┐
            │     ESP32 DEVKIT    │
            │                     │
            │  [VIN/5V] ───┬──────┼──────┐ (+5V Alimentación LED)
            │  [GND]    ───┼──┬───┼──┐   │
            │  [GPIO13] ───┼──┼───┼──┼───┼──┐ (Señal de Datos DIN)
            └──────────────┴──┴───┴──┴───┴──┴──────────────┐
                              │   │   │   │                │
                              ▼   ▼   ▼   ▼                ▼
                     ┌──────────────────────────────────────────┐
                     │          TIRA LED WS2812B (5V)           │
                     │  [+5V]      [GND]       [DIN / DATA]     │
                     └──────────────────────────────────────────┘
```

## 📌 Tabla de Asignación de Pines (Pinout)

| Pin ESP32 | Conexión Tira LED | Función | Color de Cable Sugerido |
|-----------|-------------------|---------|-------------------------|
| **VIN / 5V** | `+5V` / `VCC` | Alimentación positiva de los LEDs | Rojo |
| **GND** | `GND` / `G` | Tierra común | Negro o Blanco |
| **GPIO 13** | `DIN` / `DATA` | Señal digital de datos Neopixel | Verde o Azul |
| **GPIO 0** | Botón BOOT integrado | Cambio manual de efectos | N/A (en la placa) |

> ⚠️ **Nota de seguridad:**
> Para tiras con más de 60 LEDs, se recomienda conectar la alimentación de +5V y GND directamente desde la salida de la batería al inicio de la tira y alimentar la ESP32 por su puerto USB. El cable de datos (GPIO 13) debe ser de longitud corta (< 30 cm).
