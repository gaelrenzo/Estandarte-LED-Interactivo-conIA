#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <esp_now.h>
#include "../comun/protocolo.h"

// Reemplazar con las MAC reales obtenidas de cada ESP32 receptor.
uint8_t MAC_MECANICA[] = {0x24,0x6F,0x28,0x00,0x00,0x01};
uint8_t MAC_ELECTRICA[] = {0x24,0x6F,0x28,0x00,0x00,0x02};
constexpr uint8_t CANAL_WIFI = 6;

WebServer servidor(80);
ComandoIME comando;
uint16_t secuencia = 0;

const char PAGINA[] PROGMEM = R"HTML(
<!doctype html><html><meta name=viewport content="width=device-width,initial-scale=1">
<style>body{font-family:Arial;background:#071a2b;color:white;margin:0;padding:20px}main{max-width:560px;margin:auto}button,input,select{width:100%;padding:13px;margin:6px 0;border-radius:10px;border:0}button{background:#00aeef;font-weight:bold}.danger{background:#ff5468}</style>
<main><h1>Control Estandarte IME</h1><select id=m><option value=0>Institucional</option><option value=1>Flujo IME</option><option value=2>Audio/VU</option><option value=3>Tormenta Zeus</option><option value=4>Desfile</option><option value=5>Apagado</option></select><label>Brillo</label><input id=b type=range min=10 max=100 value=70><label>Velocidad</label><input id=v type=range min=10 max=100 value=50><button onclick=go()>Enviar a los tres</button><button class=danger onclick=stopAll()>APAGADO</button><p id=s></p></main><script>async function send(q){s.textContent=await(await fetch(q)).text()}function go(){send('/cmd?modo='+m.value+'&brillo='+b.value+'&vel='+v.value)}function stopAll(){send('/cmd?modo=5&brillo=0&vel=20')}</script></html>
)HTML";

void agregarPeer(const uint8_t *mac) {
  esp_now_peer_info_t peer{};
  memcpy(peer.peer_addr, mac, 6);
  peer.channel = CANAL_WIFI;
  peer.encrypt = false;
  if (!esp_now_is_peer_exist(mac)) esp_now_add_peer(&peer);
}

void enviarA(const uint8_t *mac, Destino destino) {
  comando.destino = destino;
  comando.secuencia = ++secuencia;
  comando.ejecutarEnMs = millis() + 350; // inicio coordinado
  comando.crcSimple = calcularCrcSimple(comando);
  esp_now_send(mac, reinterpret_cast<const uint8_t *>(&comando), sizeof(comando));
}

void enviarTodos() {
  enviarA(MAC_MECANICA, Destino::MECANICA);
  delay(8);
  enviarA(MAC_ELECTRICA, Destino::ELECTRICA);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESTANDARTE_IME", "IME-2026-LED", CANAL_WIFI, false, 2);
  if (esp_now_init() != ESP_OK) ESP.restart();
  agregarPeer(MAC_MECANICA);
  agregarPeer(MAC_ELECTRICA);

  servidor.on("/", [](){ servidor.send_P(200, "text/html", PAGINA); });
  servidor.on("/cmd", [](){
    comando.modo = static_cast<ModoIME>(constrain(servidor.arg("modo").toInt(), 0, 6));
    comando.brillo = constrain(servidor.arg("brillo").toInt(), 0, 100);
    comando.velocidad = constrain(servidor.arg("vel").toInt(), 1, 100);
    enviarTodos();
    servidor.send(200, "text/plain", "Comando enviado. Secuencia " + String(secuencia));
  });
  servidor.begin();
  Serial.print("Abra http://"); Serial.println(WiFi.softAPIP());
}

void loop() {
  servidor.handleClient();
  delay(2);
}
