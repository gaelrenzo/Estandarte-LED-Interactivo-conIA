/*
 * Estandarte LED Interactivo con IA
 * Firmware principal del ESP32.
 *
 * Funciones:
 *  - Leer nivel de audio desde el micrófono MAX4466 (ADC, GPIO 34).
 *  - Controlar tiras WS2812 con FastLED (GPIO 5).
 *  - Modo autónomo (reactivo al sonido) o asistido por PC (serial).
 *
 * Pines:
 *  - DATOS_LED : GPIO 5
 *  - MIC_PIN   : GPIO 34 (ADC)
 */

#include <Arduino.h>
#include <FastLED.h>

#include "leds.h"
#include "audio.h"

// ---------------------------------------------------------------------
// Configuración
// ---------------------------------------------------------------------
#define NUM_LEDS         60   // Ajustar a la cantidad real de LED
#define DATOS_LED        5    // GPIO de datos WS2812
#define MIC_PIN          34   // GPIO ADC del micrófono
#define MAX_BRIGHTNESS   255
#define FPS              60   // Fotogramas por segundo de animación
#define SERIAL_BAUD      115200

CRGB leds[NUM_LEDS];

// ---------------------------------------------------------------------
// Variables de estado
// ---------------------------------------------------------------------
String modo = "vu";          // Modo de efecto actual
uint8_t intensidad = 80;     // Intensidad objetivo (0-100) usado por el control
CRGB colorFijo = CRGB::Red;

unsigned long ultimoTick = 0;

// ---------------------------------------------------------------------
// Prototipos
// ---------------------------------------------------------------------
void procesarSerial(void);

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(100);

  FastLED.addLeds<WS2812, DATOS_LED, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  audioInit(MIC_PIN);

  Serial.println("Estandarte LED - Listo");
  Serial.println("Comandos: set <modo> | int <0-100> | color <r,g,b>");
}

void loop() {
  unsigned long ahora = millis();

  // Leer y normalizar el nivel de audio (0.0 - 1.0)
  float nivel = audioLeer();

  // Comando periódico de depuración
  if (ahora - ultimoTick > 250) {
    ultimoTick = ahora;
    Serial.print("L0: ");
    Serial.println((int)(nivel * 100));
  }

  // Aplicar el efecto según el modo
  aplicarEfecto(leds, NUM_LEDS, nivel, intensidad, colorFijo, modo);

  FastLED.show();
  delay(1000 / FPS);

  procesarSerial();
}

// ---------------------------------------------------------------------
// Comandos seriales desde la IA (software/ia)
// ---------------------------------------------------------------------
void procesarSerial() {
  while (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd.length() == 0) continue;

    if (cmd.startsWith("set ")) {
      modo = cmd.substring(4);
      modo.trim();
      Serial.print("Modo: ");
      Serial.println(modo);
    } else if (cmd.startsWith("int ")) {
      intensidad = (uint8_t)cmd.substring(4).toInt();
      if (intensidad > 100) intensidad = 100;
      Serial.print("Intensidad: ");
      Serial.println(intensidad);
    } else if (cmd.startsWith("color ")) {
      int r, g, b;
      sscanf(cmd.substring(6).c_str(), "%d,%d,%d", &r, &g, &b);
      colorFijo = CRGB((uint8_t)r, (uint8_t)g, (uint8_t)b);
      Serial.print("Color: ");
      Serial.println(cmd.substring(6));
    } else {
      Serial.print("Comando desconocido: ");
      Serial.println(cmd);
    }
  }
}