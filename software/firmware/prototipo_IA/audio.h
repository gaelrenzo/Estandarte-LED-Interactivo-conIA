/*
 * Lectura del micrófono MAX4466 por ADC.
 *
 * Incluye muestreo múltiple, suavizado (media móvil) y normalización
 * del nivel para obtener un valor estable 0.0-1.0.
 */

#pragma once

#include <Arduino.h>

#ifndef MIC_PIN
#define MIC_PIN 34
#endif

static const int NUM_MUESTRAS = 64;
static int muestras[NUM_MUESTRAS];
static int indice = 0;
static uint8_t pinMic = MIC_PIN;

// Aproximación del mínimo/máximo en valores ADC (calibrar empíricamente)
#define ADC_MIN 0
#define ADC_MAX 4095

// ---------------------------------------------------------------------
// Inicializa el ADC
// ---------------------------------------------------------------------
void audioInit(uint8_t pin) {
  pinMic = pin;
  pinMode(pinMic, INPUT);
  analogSetPinAttenuation(pinMic, ADC_11db); // 0-3.3V rango completo
  for (int i = 0; i < NUM_MUESTRAS; i++) muestras[i] = analogRead(pin);
}

// ---------------------------------------------------------------------
// Lee y calcula el nivel de audio normalizado (0.0 - 1.0)
// ---------------------------------------------------------------------
float audioLeer() {
  muestras[indice] = analogRead(pinMic);
  indice = (indice + 1) % NUM_MUESTRAS;

  // Pista (peak-peak) sobre la ventana
  int vmin = 4095, vmax = 0;
  for (int i = 0; i < NUM_MUESTRAS; i++) {
    if (muestras[i] < vmin) vmin = muestras[i];
    if (muestras[i] > vmax) vmax = muestras[i];
  }

  int pico = vmax - vmin;
  float rango = (float)(ADC_MAX - ADC_MIN);
  float nivel = (float)pico / rango;

  // Saturación y curva suave
  if (nivel > 1.0f) nivel = 1.0f;
  return nivel * nivel;  // dar sensibilidad a señales bajas
}