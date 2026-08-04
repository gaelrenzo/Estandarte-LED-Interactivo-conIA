#pragma once
#include <Arduino.h>

constexpr uint32_t FIRMA_IME = 0x494D4532; // "IME2"
constexpr uint8_t VERSION_PROTOCOLO = 1;

enum class Destino : uint8_t {
  TODOS = 0,
  MECANICA = 1,
  CENTRO = 2,
  ELECTRICA = 3
};

enum class ModoIME : uint8_t {
  INSTITUCIONAL = 0,
  FLUJO = 1,
  AUDIO_VU = 2,
  TORMENTA = 3,
  DESFILE = 4,
  APAGADO = 5,
  SEGURO = 6
};

struct __attribute__((packed)) ComandoIME {
  uint32_t firma = FIRMA_IME;
  uint16_t secuencia = 0;
  uint8_t version = VERSION_PROTOCOLO;
  Destino destino = Destino::TODOS;
  ModoIME modo = ModoIME::INSTITUCIONAL;
  uint8_t brillo = 80;
  uint8_t velocidad = 50;
  uint8_t rojo = 0;
  uint8_t verde = 174;
  uint8_t azul = 239;
  uint32_t ejecutarEnMs = 0;
  uint16_t crcSimple = 0;
};

struct __attribute__((packed)) EstadoIME {
  uint32_t firma = FIRMA_IME;
  uint8_t nodo = 0;
  uint16_t ultimaSecuencia = 0;
  uint16_t bateriaMv = 0;
  int8_t rssi = 0;
  uint8_t errores = 0;
  uint32_t uptimeS = 0;
};

inline uint16_t calcularCrcSimple(const ComandoIME &c) {
  const uint8_t *p = reinterpret_cast<const uint8_t *>(&c);
  uint16_t suma = 0;
  for (size_t i = 0; i < sizeof(ComandoIME) - sizeof(c.crcSimple); ++i) suma = (suma << 1) ^ p[i];
  return suma;
}

inline bool comandoValido(const ComandoIME &c) {
  return c.firma == FIRMA_IME && c.version == VERSION_PROTOCOLO && c.crcSimple == calcularCrcSimple(c);
}
