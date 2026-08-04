#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <FastLED.h>
#include "../comun/protocolo.h"

constexpr uint8_t PIN_LED = 18;
constexpr uint16_t NUM_LED = 72; // ajustar al diseño real
CRGB leds[NUM_LED];
ComandoIME pendiente;
volatile bool nuevoComando = false;
uint32_t ultimaRecepcion = 0;

void recibir(const esp_now_recv_info_t*, const uint8_t *datos, int len) {
  if (len != sizeof(ComandoIME)) return;
  memcpy(&pendiente, datos, sizeof(pendiente));
  if (comandoValido(pendiente)) { nuevoComando = true; ultimaRecepcion = millis(); }
}

void aplicarModo(const ComandoIME &c) {
  FastLED.setBrightness(map(c.brillo, 0, 100, 0, 180));
  switch (c.modo) {
    case ModoIME::APAGADO: fill_solid(leds, NUM_LED, CRGB::Black); break;
    case ModoIME::TORMENTA:
      fill_solid(leds, NUM_LED, CRGB::Black);
      for (uint8_t i=0;i<8;i++) leds[random16(NUM_LED)] = CRGB::White;
      break;
    default: fill_rainbow(leds, NUM_LED, millis()/18 + 120, 4); break;
  }
  FastLED.show();
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.setChannel(6);
  FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, NUM_LED);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 3500);
  if (esp_now_init() != ESP_OK) ESP.restart();
  esp_now_register_recv_cb(recibir);
}

void loop() {
  if (nuevoComando && (int32_t)(millis() - pendiente.ejecutarEnMs) >= 0) {
    nuevoComando = false;
    aplicarModo(pendiente);
  }
  if (millis() - ultimaRecepcion > 5000) {
    fadeToBlackBy(leds, NUM_LED, 8);
    leds[NUM_LED-1-(millis()/100)%NUM_LED] = CRGB(0,150,255);
    FastLED.show();
  }
  delay(10);
}
