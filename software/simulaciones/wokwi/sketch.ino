#include <Arduino.h>
#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =============================================================
// ESTANDARTE IME - SIMULACION INTEGRADA EN WOKWI
// Un ESP32 controla tres zonas visuales:
//   - MECANICA: tira vertical WS2812
//   - CENTRO: matriz 8x8 para el simbolo de Zeus
//   - ELECTRICA: tira vertical WS2812
//
// En el montaje final cada modulo tendra su propio ESP32 y bateria.
// La coordinacion se realizara con ESP-NOW y el ESP32 central
// ofrecera una pagina web local para el control desde el celular.
// =============================================================

// Pines de datos LED
constexpr uint8_t PIN_MECANICA = 16;
constexpr uint8_t PIN_CENTRO   = 17;
constexpr uint8_t PIN_ELECTRICA = 18;

// Entradas
constexpr uint8_t PIN_POT_SONIDO = 34;
constexpr uint8_t PIN_POT_BRILLO = 35;
constexpr uint8_t PIN_BTN_MODO = 25;
constexpr uint8_t PIN_BTN_COLOR = 26;
constexpr uint8_t PIN_BTN_SECUENCIA = 27;

// OLED I2C
constexpr uint8_t OLED_SDA = 21;
constexpr uint8_t OLED_SCL = 22;
constexpr uint8_t OLED_ADDR = 0x3C;
constexpr int OLED_W = 128;
constexpr int OLED_H = 64;
Adafruit_SSD1306 display(OLED_W, OLED_H, &Wire, -1);
bool oledOK = false;

// Cantidad de LEDs
constexpr uint16_t N_MECANICA = 20;
constexpr uint16_t N_CENTRO = 64; // matriz 8x8
constexpr uint16_t N_ELECTRICA = 20;

CRGB mecanica[N_MECANICA];
CRGB centro[N_CENTRO];
CRGB electrica[N_ELECTRICA];

// Modos
constexpr uint8_t NUM_MODOS = 6;
uint8_t modo = 0;
uint8_t paleta = 0;
uint8_t brilloGlobal = 90;
uint8_t nivelSonido = 0;

const char *NOMBRES_MODO[NUM_MODOS] = {
  "Institucional",
  "Flujo IME",
  "Audio / VU",
  "Tormenta Zeus",
  "Desfile",
  "Apagado"
};

// Debounce sencillo
struct Boton {
  uint8_t pin;
  bool estadoAnterior = HIGH;
  bool estadoEstable = HIGH;
  uint32_t ultimoCambio = 0;
};

Boton btnModo{PIN_BTN_MODO};
Boton btnColor{PIN_BTN_COLOR};
Boton btnSecuencia{PIN_BTN_SECUENCIA};

uint32_t inicioModo = 0;
uint32_t ultimoOLED = 0;
uint32_t ultimoFrame = 0;
uint32_t ultimoRandom = 0;
bool flashZeus = false;

// -------------------------------------------------------------
// Utilidades
// -------------------------------------------------------------
uint16_t xy(uint8_t x, uint8_t y) {
  // Matriz 8x8 con cableado serpentino
  if (y & 1) return y * 8 + (7 - x);
  return y * 8 + x;
}

CRGB colorMecanica() {
  static const CRGB colores[] = {
    CRGB(255, 100, 0),   // naranja mecanico
    CRGB(255, 180, 20),  // dorado
    CRGB(220, 30, 20),   // rojo
    CRGB(190, 190, 190)  // acero
  };
  return colores[paleta % 4];
}

CRGB colorElectrica() {
  static const CRGB colores[] = {
    CRGB(0, 130, 255),   // azul electrico
    CRGB(0, 255, 220),   // cian
    CRGB(150, 40, 255),  // violeta
    CRGB(255, 255, 255)  // blanco
  };
  return colores[paleta % 4];
}

CRGB colorCentro() {
  static const CRGB colores[] = {
    CRGB(30, 80, 255),
    CRGB(80, 20, 255),
    CRGB(0, 200, 255),
    CRGB(255, 180, 0)
  };
  return colores[paleta % 4];
}

bool botonPresionado(Boton &b) {
  bool lectura = digitalRead(b.pin);
  uint32_t ahora = millis();

  if (lectura != b.estadoAnterior) {
    b.ultimoCambio = ahora;
    b.estadoAnterior = lectura;
  }

  if ((ahora - b.ultimoCambio) > 35 && lectura != b.estadoEstable) {
    b.estadoEstable = lectura;
    if (b.estadoEstable == LOW) return true;
  }
  return false;
}

void limpiarTodo() {
  fill_solid(mecanica, N_MECANICA, CRGB::Black);
  fill_solid(centro, N_CENTRO, CRGB::Black);
  fill_solid(electrica, N_ELECTRICA, CRGB::Black);
}

void dibujarRayo(CRGB color, uint8_t intensidad = 255) {
  // Coordenadas aproximadas del simbolo de Zeus/rayo en matriz 8x8
  const uint8_t puntos[][2] = {
    {5,0},{4,1},{4,2},{3,2},{4,3},{3,4},{3,5},{2,5},{3,6},{2,7}
  };
  for (auto &p : puntos) {
    CRGB c = color;
    c.nscale8_video(intensidad);
    centro[xy(p[0], p[1])] = c;
  }
}

void mostrarOLED() {
  if (!oledOK) return;
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("ESTANDARTE IME");
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
  display.setCursor(0, 16);
  display.print("Modo: ");
  display.println(NOMBRES_MODO[modo]);
  display.setCursor(0, 29);
  display.print("Sonido: ");
  display.print(nivelSonido);
  display.println("%");
  display.setCursor(0, 41);
  display.print("Brillo: ");
  display.print(map(brilloGlobal, 0, 255, 0, 100));
  display.println("%");
  display.setCursor(0, 53);
  display.print("Paleta: ");
  display.println(paleta + 1);
  display.display();
}

// -------------------------------------------------------------
// Efectos
// -------------------------------------------------------------
void efectoInstitucional(uint32_t ahora) {
  limpiarTodo();
  uint8_t pulso = beatsin8(18, 80, 230);

  CRGB cm = colorMecanica();
  CRGB ce = colorElectrica();
  cm.nscale8_video(pulso);
  ce.nscale8_video(pulso);

  fill_solid(mecanica, N_MECANICA, cm);
  fill_solid(electrica, N_ELECTRICA, ce);

  // Fondo central tenue y rayo brillante
  CRGB fondo = colorCentro();
  fondo.nscale8_video(45);
  fill_solid(centro, N_CENTRO, fondo);
  dibujarRayo(CRGB::White, 255);

  // Barrido lateral discreto
  uint16_t p = (ahora / 90) % N_MECANICA;
  mecanica[p] = CRGB::White;
  electrica[N_ELECTRICA - 1 - p] = CRGB::White;
}

void efectoFlujo(uint32_t ahora) {
  limpiarTodo();
  const uint32_t duracion = 4200;
  uint32_t t = (ahora - inicioModo) % duracion;
  CRGB cm = colorMecanica();
  CRGB ce = colorElectrica();
  CRGB cc = colorCentro();

  if (t < 1100) {
    uint16_t n = map(t, 0, 1099, 0, N_MECANICA);
    for (uint16_t i = 0; i < n; ++i) mecanica[i] = cm;
    if (n < N_MECANICA) mecanica[n] = CRGB::White;
  } else if (t < 2400) {
    fill_solid(mecanica, N_MECANICA, cm);
    uint8_t intensidad = map(t, 1100, 2399, 40, 255);
    fill_solid(centro, N_CENTRO, CRGB(0, 0, 20));
    dibujarRayo(cc, intensidad);
  } else if (t < 3500) {
    fill_solid(mecanica, N_MECANICA, cm);
    dibujarRayo(CRGB::White, 255);
    uint16_t n = map(t, 2400, 3499, 0, N_ELECTRICA);
    for (uint16_t i = 0; i < n; ++i) electrica[N_ELECTRICA - 1 - i] = ce;
  } else {
    uint8_t destello = sin8(map(t, 3500, 4199, 0, 255));
    CRGB total = blend(cm, ce, 128);
    total.nscale8_video(destello);
    fill_solid(mecanica, N_MECANICA, total);
    fill_solid(centro, N_CENTRO, total);
    fill_solid(electrica, N_ELECTRICA, total);
    dibujarRayo(CRGB::White, 255);
  }
}

void efectoAudioVU() {
  limpiarTodo();
  uint16_t nL = map(nivelSonido, 0, 100, 0, N_MECANICA);
  uint16_t nR = map(nivelSonido, 0, 100, 0, N_ELECTRICA);

  for (uint16_t i = 0; i < nL; ++i) {
    uint8_t hue = map(i, 0, N_MECANICA - 1, 32, 0);
    mecanica[i] = CHSV(hue, 255, 255);
  }
  for (uint16_t i = 0; i < nR; ++i) {
    uint8_t hue = map(i, 0, N_ELECTRICA - 1, 160, 190);
    electrica[N_ELECTRICA - 1 - i] = CHSV(hue, 255, 255);
  }

  uint8_t columnas = map(nivelSonido, 0, 100, 0, 8);
  for (uint8_t x = 0; x < 8; ++x) {
    uint8_t altura = (x < columnas) ? map(nivelSonido, 0, 100, 1, 8) : 0;
    for (uint8_t y = 0; y < altura; ++y) {
      centro[xy(x, 7 - y)] = CHSV(150 + x * 5, 255, 255);
    }
  }
  if (nivelSonido > 70) dibujarRayo(CRGB::White, 255);
}

void efectoTormenta(uint32_t ahora) {
  fadeToBlackBy(mecanica, N_MECANICA, 45);
  fadeToBlackBy(centro, N_CENTRO, 70);
  fadeToBlackBy(electrica, N_ELECTRICA, 45);

  if (ahora - ultimoRandom > random16(80, 260)) {
    ultimoRandom = ahora;
    flashZeus = random8() > 145;

    mecanica[random16(N_MECANICA)] = colorMecanica();
    electrica[random16(N_ELECTRICA)] = colorElectrica();

    if (flashZeus) {
      fill_solid(centro, N_CENTRO, CRGB(20, 30, 80));
      dibujarRayo(CRGB::White, 255);
    } else {
      centro[random16(N_CENTRO)] = colorCentro();
      centro[random16(N_CENTRO)] = CRGB::White;
    }
  }
}

void efectoDesfile(uint32_t ahora) {
  uint8_t base = ahora / 18;
  for (uint16_t i = 0; i < N_MECANICA; ++i)
    mecanica[i] = CHSV(base + i * 7, 255, 255);
  for (uint16_t i = 0; i < N_CENTRO; ++i)
    centro[i] = CHSV(base + i * 3, 255, 255);
  for (uint16_t i = 0; i < N_ELECTRICA; ++i)
    electrica[i] = CHSV(base + 160 + i * 7, 255, 255);

  if ((ahora / 500) % 2 == 0) dibujarRayo(CRGB::White, 255);
}

void aplicarEfecto(uint32_t ahora) {
  switch (modo) {
    case 0: efectoInstitucional(ahora); break;
    case 1: efectoFlujo(ahora); break;
    case 2: efectoAudioVU(); break;
    case 3: efectoTormenta(ahora); break;
    case 4: efectoDesfile(ahora); break;
    case 5: limpiarTodo(); break;
  }
}

// -------------------------------------------------------------
// Setup / Loop
// -------------------------------------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(PIN_BTN_MODO, INPUT_PULLUP);
  pinMode(PIN_BTN_COLOR, INPUT_PULLUP);
  pinMode(PIN_BTN_SECUENCIA, INPUT_PULLUP);
  pinMode(PIN_POT_SONIDO, INPUT);
  pinMode(PIN_POT_BRILLO, INPUT);

  FastLED.addLeds<WS2812B, PIN_MECANICA, GRB>(mecanica, N_MECANICA);
  FastLED.addLeds<WS2812B, PIN_CENTRO, GRB>(centro, N_CENTRO);
  FastLED.addLeds<WS2812B, PIN_ELECTRICA, GRB>(electrica, N_ELECTRICA);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brilloGlobal);
  FastLED.clear(true);

  Wire.begin(OLED_SDA, OLED_SCL);
  oledOK = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  if (!oledOK) {
    Serial.println("OLED no disponible; la simulacion LED continuara.");
  } else {
    mostrarOLED();
  }

  random16_set_seed(analogRead(PIN_POT_SONIDO) + micros());
  inicioModo = millis();

  Serial.println("=== ESTANDARTE IME - SIMULACION WOKWI ===");
  Serial.println("Boton MODO: cambia efecto");
  Serial.println("Boton COLOR: cambia paleta");
  Serial.println("Boton SECUENCIA: activa Flujo IME");
  Serial.println("Pot SONIDO: nivel de audio simulado");
  Serial.println("Pot BRILLO: intensidad general");
}

void loop() {
  const uint32_t ahora = millis();

  // Entradas analogicas
  nivelSonido = constrain(map(analogRead(PIN_POT_SONIDO), 0, 4095, 0, 100), 0, 100);
  brilloGlobal = constrain(map(analogRead(PIN_POT_BRILLO), 0, 4095, 20, 180), 20, 180);
  FastLED.setBrightness(brilloGlobal);

  // Botones
  if (botonPresionado(btnModo)) {
    modo = (modo + 1) % NUM_MODOS;
    inicioModo = ahora;
    Serial.printf("Modo: %s\n", NOMBRES_MODO[modo]);
  }

  if (botonPresionado(btnColor)) {
    paleta = (paleta + 1) % 4;
    Serial.printf("Paleta: %u\n", paleta + 1);
  }

  if (botonPresionado(btnSecuencia)) {
    modo = 1;
    inicioModo = ahora;
    Serial.println("Secuencia coordinada IME activada");
  }

  // 50 FPS aproximados
  if (ahora - ultimoFrame >= 20) {
    ultimoFrame = ahora;
    aplicarEfecto(ahora);
    FastLED.show();
  }

  if (ahora - ultimoOLED >= 250) {
    ultimoOLED = ahora;
    mostrarOLED();
  }

  delay(2);
}
