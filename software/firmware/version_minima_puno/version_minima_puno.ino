/*
 * =================================================================================
 * ESTANDARTE INTERACTIVO LED IME - VERSIÓN COMPONENTES MÍNIMOS (PUNO 2026)
 * Escuela Profesional de Ingeniería Mecánica Eléctrica - UNA PUNO
 * =================================================================================
 * Hardware Requerido Mínimo:
 *  - 1x Placa ESP32 (DevKit v1 o NodeMCU ESP32)
 *  - 1x Tira LED WS2812B (5V) -> Cable de datos a GPIO 13
 *  - 1x Fuente/Power Bank 5V (Conectada a 5V/VIN y GND de ESP32 y Tira LED)
 *  - Botón integrado en ESP32 (Pin GPIO 0 / BOOT) para cambio manual de modo
 * 
 * Ventajas:
 *  - NO requiere circuito integrado 74AHCT125 ni micrófonos externos.
 *  - El micrófono del celular transmite audio vía Wi-Fi directamente a la ESP32.
 *  - Servidor Web integrado autónomo en http://192.168.4.1
 *  - Guarda la configuración en la memoria del ESP32 al apagar/encender.
 * =================================================================================
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <FastLED.h>

#include "web_interface.h"

// ---------------------------------------------------------------------------------
// CONFIGURACIÓN DE HARDWARE DE COMPONENTES MÍNIMOS
// ---------------------------------------------------------------------------------
#define PIN_LED          13     // GPIO 13 de la ESP32 conectado al DIN de la tira WS2812B
#define NUM_LEDS         60     // Número total de LEDs en el estandarte (Ajustable)
#define PIN_BOTON        0      // Botón BOOT integrado en la placa ESP32 (GPIO 0)
#define CANAL_WIFI       6

// Estructura de animación FastLED
CRGB leds[NUM_LEDS];

// Servidor Web y Memoria No Volátil
WebServer server(80);
Preferences prefs;

// ---------------------------------------------------------------------------------
// VARIABLES GLOBAL DE ESTADO
// ---------------------------------------------------------------------------------
enum ModoIluminacion {
  MODO_INSTITUCIONAL = 0,
  MODO_FLUJO         = 1,
  MODO_AUDIO_VU      = 2,
  MODO_TORMENTA      = 3,
  MODO_DESFILE       = 4,
  MODO_APAGADO       = 5,
  MODO_COLOR_FIJO    = 6
};

uint8_t  modoActual  = MODO_INSTITUCIONAL;
uint8_t  brillo      = 80;   // 0 a 100%
uint8_t  velocidad   = 60;   // 10 a 100%
uint8_t  colorR      = 0;
uint8_t  colorG      = 174;
uint8_t  colorB      = 239;
uint8_t  volumenAudio = 0;   // Transmitido por el celular (0-100)

unsigned long ultimoCambioBoton = 0;
unsigned long ultimoFrame = 0;
uint16_t pasoAnimacion = 0;

// ---------------------------------------------------------------------------------
// DECLARACIÓN DE FUNCIONES
// ---------------------------------------------------------------------------------
void inicializarWiFiAP();
void inicializarServidorWeb();
void cargarConfiguracion();
void guardarConfiguracion();
void actualizarAnimacion();
void verificarBotonFisico();

// ---------------------------------------------------------------------------------
// SETUP PRINCIPAL
// ---------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println(F("\n========================================================"));
  Serial.println(F(" ESTANDARTE LED IME - VERSIÓN PUNO COMPONENTES MÍNIMOS "));
  Serial.println(F("========================================================"));

  // Configurar pin de botón con Pull-Up interno
  pinMode(PIN_BOTON, INPUT_PULLUP);

  // Inicializar LEDs WS2812B
  FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2500); // Protección de potencia para Power Bank 2.5A
  FastLED.clear();
  FastLED.show();

  // Cargar preferencias guardadas en Flash
  cargarConfiguracion();

  // Iniciar Wi-Fi y Servidor Web
  inicializarWiFiAP();
  inicializarServidorWeb();

  Serial.println(F(">> Sistema listo. Conéctese al Wi-Fi 'ESTANDARTE_IME_PUNO'"));
  Serial.println(F(">> Abra en su celular la dirección: http://192.168.4.1"));
}

// ---------------------------------------------------------------------------------
// LOOP PRINCIPAL (NON-BLOCKING)
// ---------------------------------------------------------------------------------
void loop() {
  server.handleClient();
  verificarBotonFisico();
  actualizarAnimacion();
  delay(2);
}

// ---------------------------------------------------------------------------------
// INICIALIZACIÓN DE WI-FI ACCESS POINT (PUNTO DE ACCESO AUTÓNOMO)
// ---------------------------------------------------------------------------------
void inicializarWiFiAP() {
  WiFi.mode(WIFI_AP);
  // Red sin contraseña para conexión rápida de la delegación en la parada
  WiFi.softAP("ESTANDARTE_IME_PUNO", "", CANAL_WIFI, false, 4);
  Serial.print(F(">> Punto de Acceso Creado. IP: "));
  Serial.println(WiFi.softAPIP());
}

// ---------------------------------------------------------------------------------
// RUTAS Y ENDPOINTS DEL SERVIDOR WEB
// ---------------------------------------------------------------------------------
void inicializarServidorWeb() {
  // Página principal servida desde PROGMEM
  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html", PAGINA_WEB_PUNO);
  });

  // Endpoint de comandos del panel web
  server.on("/api/cmd", HTTP_GET, []() {
    if (server.hasArg("modo")) modoActual = server.arg("modo").toInt();
    if (server.hasArg("brillo")) brillo = constrain(server.arg("brillo").toInt(), 0, 100);
    if (server.hasArg("vel")) velocidad = constrain(server.arg("vel").toInt(), 10, 100);
    if (server.hasArg("r")) colorR = server.arg("r").toInt();
    if (server.hasArg("g")) colorG = server.arg("g").toInt();
    if (server.hasArg("b")) colorB = server.arg("b").toInt();

    FastLED.setBrightness(map(brillo, 0, 100, 0, 255));
    server.send(200, "application/json", "{\"status\":\"ok\"}");
  });

  // Endpoint de recepción de micrófono de celular
  server.on("/api/audio", HTTP_GET, []() {
    if (server.hasArg("vu")) {
      volumenAudio = constrain(server.arg("vu").toInt(), 0, 100);
      modoActual = MODO_AUDIO_VU;
    }
    server.send(200, "application/json", "{\"status\":\"ok\"}");
  });

  // Guardar configuración actual en memoria permanente
  server.on("/api/save", HTTP_GET, []() {
    guardarConfiguracion();
    server.send(200, "application/json", "{\"status\":\"saved\"}");
  });

  // Estado del sistema
  server.on("/api/status", HTTP_GET, []() {
    String json = "{\"modo\":" + String(modoActual) + 
                  ",\"brillo\":" + String(brillo) + 
                  ",\"vel\":" + String(velocidad) + "}";
    server.send(200, "application/json", json);
  });

  server.begin();
  Serial.println(F(">> Servidor Web iniciado correctamente."));
}

// ---------------------------------------------------------------------------------
// LECTURA / GUARDADO DE MEMORIA PREFERENCES (FLASH)
// ---------------------------------------------------------------------------------
void cargarConfiguracion() {
  prefs.begin("ime_puno", true);
  modoActual = prefs.getUChar("modo", MODO_INSTITUCIONAL);
  brillo     = prefs.getUChar("brillo", 80);
  velocidad  = prefs.getUChar("vel", 60);
  prefs.end();
  FastLED.setBrightness(map(brillo, 0, 100, 0, 255));
}

void guardarConfiguracion() {
  prefs.begin("ime_puno", false);
  prefs.putUChar("modo", modoActual);
  prefs.putUChar("brillo", brillo);
  prefs.putUChar("vel", velocidad);
  prefs.end();
  Serial.println(F(">> Ajustes guardados en memoria no volátil EEPROM."));
}

// ---------------------------------------------------------------------------------
// CAMBIO MANUAL CON BOTÓN BOOT DE LA ESP32
// ---------------------------------------------------------------------------------
void verificarBotonFisico() {
  if (digitalRead(PIN_BOTON) == LOW) {
    if (millis() - ultimoCambioBoton > 350) { // Debounce
      ultimoCambioBoton = millis();
      modoActual = (modoActual + 1) % 7;
      Serial.print(F(">> Botón presionado. Cambio a modo: "));
      Serial.println(modoActual);
    }
  }
}

// ---------------------------------------------------------------------------------
// MOTOR DE ANIMACIÓN LED (EFECTOS VISUALES)
// ---------------------------------------------------------------------------------
void actualizarAnimacion() {
  unsigned long ahora = millis();
  uint16_t intervalo = map(110 - velocidad, 10, 100, 15, 120);

  if (ahora - ultimoFrame < intervalo) return;
  ultimoFrame = ahora;
  pasoAnimacion++;

  FastLED.setBrightness(map(brillo, 0, 100, 0, 255));

  switch (modoActual) {

    // 0: INSTITUCIONAL (Azul + Celeste IME)
    case MODO_INSTITUCIONAL: {
      for (int i = 0; i < NUM_LEDS; i++) {
        if ((i + (pasoAnimacion / 3)) % 4 < 2) {
          leds[i] = CRGB(0, 174, 239); // Celeste IME
        } else {
          leds[i] = CRGB(242, 140, 0); // Naranja Mecánica
        }
      }
      break;
    }

    // 1: FLUJO IME (Mecánica -> Zeus -> Eléctrica)
    case MODO_FLUJO: {
      uint8_t pos = (pasoAnimacion) % NUM_LEDS;
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i < NUM_LEDS / 2) leds[i] = CRGB(242, 140, 0);
        else leds[i] = CRGB(0, 174, 239);
      }
      leds[pos] = CRGB::White;
      if (pos > 0) leds[pos - 1] = CRGB::White;
      break;
    }

    // 2: AUDIO VU (Micrófono del celular o simulado)
    case MODO_AUDIO_VU: {
      uint8_t ledsEncendidos = map(volumenAudio, 0, 100, 0, NUM_LEDS);
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      for (int i = 0; i < ledsEncendidos; i++) {
        if (i > NUM_LEDS * 0.8) leds[i] = CRGB::Red;
        else if (i > NUM_LEDS * 0.5) leds[i] = CRGB(245, 158, 11);
        else leds[i] = CRGB(16, 185, 129);
      }
      break;
    }

    // 3: TORMENTA ZEUS (Destellos de Rayos)
    case MODO_TORMENTA: {
      fill_solid(leds, NUM_LEDS, CRGB(139, 92, 246));
      if (random8() < 35) {
        fill_solid(leds, NUM_LEDS, CRGB::White);
      }
      break;
    }

    // 4: DESFILE / FIESTA (Arcoíris dinámico)
    case MODO_DESFILE: {
      fill_rainbow(leds, NUM_LEDS, pasoAnimacion * 4, 7);
      break;
    }

    // 5: APAGADO DE EMERGENCIA
    case MODO_APAGADO: {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
    }

    // 6: COLOR FIJO PERSONALIZADO
    case MODO_COLOR_FIJO: {
      fill_solid(leds, NUM_LEDS, CRGB(colorR, colorG, colorB));
      break;
    }
  }

  FastLED.show();
}
