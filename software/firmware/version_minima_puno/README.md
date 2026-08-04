# Firmware — Versión Componentes Mínimos (Puno 2026)

Firmware del estandarte optimizado para montarse con los mínimos componentes
posibles: **1× ESP32 + 1× tira WS2812B + 1× Power Bank USB**.

## Por qué esta versión

- **Solo 1 ESP32**: sin red ESP-NOW de múltiples placas.
- **Sin integrados adicionales**: no requiere driver 74AHCT125 ni módulo MAX4466.
- **Micrófono del celular**: la página web transmite el audio en tiempo real por Wi-Fi.
- **Alimentación simple**: cualquier power bank USB de 5 V.
- **Reserva manual**: botón BOOT de la propia placa para cambiar modos sin celular.

## Archivos

| Archivo | Descripción |
|---------|-------------|
| `version_minima_puno.ino` | Firmware principal (Wi-Fi AP, servidor web, efectos FastLED) |
| `web_interface.h` | Página web de control incrustada (`/static/192.168.4.1`) |
| `GUIA_MONTAJE_PUNO.md` | Guía de montaje rápido y uso en la parada |
| `DIAGRAMA_CONEXION_MINIMO.md` | Diagrama de conexión ultrasimple |

## Requisitos de hardware

- Placa **ESP32** (DevKit V1 / NodeMCU)
- Tira **WS2812B** (5 V), datos → **GPIO 13**
- **Power Bank 5 V** (≥ 2 A, ≥ 5000 mAh)
- Cables dupont / calibre 22 (VCC, GND, DATOS)

## Conexión

```
[ Power Bank 5V ] ──USB──► [ ESP32 ]
                              ├─► 5V (VIN)  ──► (+) VCC Tira
                              └─► GND       ──► (-) GND Tira
[ ESP32 GPIO 13 ] ────────────────────────► DIN Tira WS2812B
[ GPIO 0 (BOOT)  ] ──────────────────────── Botón de manual
```

Ver [`DIAGRAMA_CONEXION_MINIMO.md`](DIAGRAMA_CONEXION_MINIMO.md) y
[`GUIA_MONTAJE_PUNO.md`](GUIA_MONTAJE_PUNO.md).

## Cargar y usar

1. Arduino IDE → instalar **FastLED**.
2. Abrir `version_minima_puno.ino`, placa `DOIT ESP32 DEVKIT V1`.
3. Subir (Upload).
4. Conectar el móvil a la red `ESTANDARTE_IME_PUNO` y abrir `http://192.168.4.1`.

## Librerías

- `FastLED`
- `WiFi`, `WebServer`, `Preferences` (incluidas en el núcleo ESP32 Arduino)

## Notas

- Ajusta `NUM_LEDS` y `PIN_LED` según tu tira.
- `CANAL_WIFI = 6` por defecto.
- La configuración se guarda en memoria no volátil (`Preferences`) al
  presionar "Guardar preset".