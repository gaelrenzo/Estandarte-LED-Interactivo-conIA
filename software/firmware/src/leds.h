/*
 * Efectos de animación para las tiras WS2812.
 *
 * Cada función recibe el nivel de audio normalizado (0.0-1.0),
 * la intensidad (0-100) y el color base, y actualiza el array leds[].
 */

#pragma once

#include <Arduino.h>
#include <FastLED.h>

// ---------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------
// Convierte la intensidad 0-100 a un brillo máximo por LED (0-255)
inline uint8_t brilloMax(uint8_t intensidad) {
  return (uint8_t)((intensidad * 255UL) / 100UL);
}

// ---------------------------------------------------------------------
// Modo VU: medidor de nivel de audio (barras)
// ---------------------------------------------------------------------
void efectoVU(CRGB *leds, int numLeds, float nivel, uint8_t intensidad, CRGB color) {
  uint8_t bm = brilloMax(intensidad);
  int ledEncendidos = (int)(nivel * numLeds);
  if (ledEncendidos > numLeds) ledEncendidos = numLeds;

  // Degradado: verde -> amarillo -> rojo
  for (int i = 0; i < numLeds; i++) {
    if (i < ledEncendidos) {
      uint8_t hue = map(i, 0, numLeds, 96, 0); // verde(96) a rojo(0)
      leds[i] = CHSV(hue, 255, bm);
    } else {
      leds[i] = CRGB::Black;
    }
  }
}

// ---------------------------------------------------------------------
// Modo WAVE: onda suave que sube con el audio
// ---------------------------------------------------------------------
void efectoWave(CRGB *leds, int numLeds, float nivel, uint8_t intensidad, CRGB color) {
  uint8_t bm = brilloMax(intensidad);
  float t = (float)millis() / 1000.0f;
  float amplitud = 0.2f + nivel * 0.8f;

  for (int i = 0; i < numLeds; i++) {
    float v = (sin(t * 6.0f + i * 0.4f) + 1.0f) / 2.0f; // 0-1
    float brillo = v * amplitud;
    leds[i] = color;
    leds[i].fadeToBlackBy((uint8_t)((1.0f - brillo) * 255));
    leds[i].nscale8(bm);
  }
}

// ---------------------------------------------------------------------
// Modo STROBE: destellos sincronizados con picos de audio
// ---------------------------------------------------------------------
void efectoStrobe(CRGB *leds, int numLeds, float nivel, uint8_t intensidad, CRGB color) {
  uint8_t bm = brilloMax(intensidad);
  bool on = (nivel > 0.6f);  // umbral de disparo

  CRGB valor = on ? color : CRGB::Black;
  for (int i = 0; i < numLeds; i++) {
    leds[i] = valor;
    if (on) leds[i].nscale8(bm);
  }
}

// ---------------------------------------------------------------------
// Selector de modo
// ---------------------------------------------------------------------
void aplicarEfecto(CRGB *leds, int numLeds, float nivel, uint8_t intensidad,
                   CRGB color, const String &modo) {
  if (modo == "vu") {
    efectoVU(leds, numLeds, nivel, intensidad, color);
  } else if (modo == "wave") {
    efectoWave(leds, numLeds, nivel, intensidad, color);
  } else if (modo == "strobe") {
    efectoStrobe(leds, numLeds, nivel, intensidad, color);
  } else if (modo == "off") {
    FastLED.clear();
  } else {
    // Modo desconocido -> apagado
    FastLED.clear();
  }
}