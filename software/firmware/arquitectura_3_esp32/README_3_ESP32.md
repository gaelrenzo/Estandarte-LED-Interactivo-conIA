# Arquitectura física de tres ESP32

> Coordinación inalámbrica por **ESP-NOW**: un central + dos módulos receptores.

[![Red](https://img.shields.io/badge/Red-ESP--NOW-00aeef)](..#) [![Firmware](https://img.shields.io/badge/Firmware-Arduino%2FPlatformIO-15a0d8)](..#)

- **Central**: crea la red Wi-Fi local `ESTANDARTE_IME`, aloja la página de control y envía comandos ESP-NOW.
- **Mecánica**: recibe comandos, controla sus tiras y mantiene un modo seguro si se pierde el enlace.
- **Eléctrica**: recibe comandos, controla sus tiras y mantiene un modo seguro.

## Antes de cargar

1. Obtenga la MAC de cada receptor con `WiFi.macAddress()`.
2. Reemplace `MAC_MECANICA` y `MAC_ELECTRICA` en `central_maestro.ino`.
3. Mantenga los tres nodos en el mismo canal Wi-Fi (canal 6 en el ejemplo).
4. Ajuste `NUM_LED`, pines y límites de corriente.
5. Use baterías, fusibles y convertidores independientes.

Estos archivos son una base de ingeniería para la fase física. La red ESP-NOW debe validarse con placas reales.
