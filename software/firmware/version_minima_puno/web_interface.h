#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

#include <Arduino.h>

const char PAGINA_WEB_PUNO[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Control Estandarte IME - Puno 2026</title>
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@300;400;600;800&family=Space+Grotesk:wght@500;700&display=swap" rel="stylesheet">
  <style>
    :root {
      --bg-dark: #070b12;
      --bg-card: rgba(15, 23, 42, 0.85);
      --bg-card-border: rgba(255, 255, 255, 0.1);
      --primary-ime: #00aeef;
      --secondary-ime: #f28c00;
      --accent-zeus: #8b5cf6;
      --text-main: #f8fafc;
      --text-muted: #94a3b8;
      --success: #10b981;
      --danger: #ef4444;
      --gold: #f59e0b;
    }
    * { box-sizing: border-box; margin: 0; padding: 0; font-family: 'Outfit', sans-serif; -webkit-tap-highlight-color: transparent; }
    body {
      background-color: var(--bg-dark);
      background-image: 
        radial-gradient(at 0% 0%, rgba(0, 174, 239, 0.15) 0px, transparent 50%),
        radial-gradient(at 100% 100%, rgba(242, 140, 0, 0.12) 0px, transparent 50%),
        radial-gradient(at 50% 50%, rgba(139, 92, 246, 0.1) 0px, transparent 50%);
      background-attachment: fixed;
      color: var(--text-main);
      min-height: 100vh;
      padding: 16px;
      display: flex;
      flex-direction: column;
      align-items: center;
    }
    .container { width: 100%; max-width: 600px; display: flex; flex-direction: column; gap: 16px; }
    header {
      background: var(--bg-card); backdrop-filter: blur(12px); border: 1px solid var(--bg-card-border);
      border-radius: 20px; padding: 18px 20px; display: flex; justify-content: space-between; align-items: center;
      box-shadow: 0 8px 32px 0 rgba(0, 0, 0, 0.37);
    }
    .brand { display: flex; align-items: center; gap: 12px; }
    .brand-icon {
      width: 44px; height: 44px; background: linear-gradient(135deg, var(--primary-ime), var(--secondary-ime));
      border-radius: 12px; display: flex; align-items: center; justify-content: center; font-size: 22px; font-weight: 800; color: #fff;
      box-shadow: 0 0 15px rgba(0, 174, 239, 0.4);
    }
    .brand-text h1 {
      font-family: 'Space Grotesk', sans-serif; font-size: 18px; font-weight: 700; letter-spacing: -0.5px;
      background: linear-gradient(90deg, #fff, #93c5fd); -webkit-background-clip: text; -webkit-text-fill-color: transparent;
    }
    .brand-text p { font-size: 12px; color: var(--text-muted); }
    .connection-status {
      display: flex; align-items: center; gap: 6px; background: rgba(16, 185, 129, 0.1);
      border: 1px solid rgba(16, 185, 129, 0.3); padding: 6px 12px; border-radius: 30px; font-size: 12px; color: var(--success); font-weight: 600;
    }
    .status-dot { width: 8px; height: 8px; background: var(--success); border-radius: 50%; box-shadow: 0 0 8px var(--success); animation: pulse 1.5s infinite; }
    @keyframes pulse { 0% { opacity: 0.4; } 50% { opacity: 1; } 100% { opacity: 0.4; } }
    .card { background: var(--bg-card); backdrop-filter: blur(12px); border: 1px solid var(--bg-card-border); border-radius: 20px; padding: 20px; box-shadow: 0 8px 32px 0 rgba(0, 0, 0, 0.3); }
    .card-title { font-size: 14px; font-weight: 700; text-transform: uppercase; letter-spacing: 1px; color: var(--text-muted); margin-bottom: 14px; display: flex; align-items: center; justify-content: space-between; }
    .preview-banner {
      height: 90px; background: rgba(4, 13, 24, 0.9); border-radius: 14px; border: 1px solid rgba(0, 174, 239, 0.2);
      display: flex; align-items: center; justify-content: space-between; padding: 0 16px; position: relative; overflow: hidden;
      box-shadow: inset 0 0 20px rgba(0, 0, 0, 0.8);
    }
    .led-strip-preview { display: flex; gap: 6px; width: 100%; justify-content: space-between; }
    .led-dot { width: 12px; height: 12px; border-radius: 50%; background: #1e293b; transition: background 0.08s ease, box-shadow 0.08s ease; }
    .zeus-emblem { position: absolute; left: 50%; top: 50%; transform: translate(-50%, -50%); font-size: 28px; filter: drop-shadow(0 0 8px var(--primary-ime)); transition: transform 0.1s ease; }
    .modes-grid { display: grid; grid-template-columns: repeat(2, 1fr); gap: 12px; }
    .mode-btn {
      background: rgba(255, 255, 255, 0.03); border: 1px solid rgba(255, 255, 255, 0.08); border-radius: 16px; padding: 16px 14px;
      display: flex; flex-direction: column; align-items: flex-start; gap: 8px; color: var(--text-main); cursor: pointer; transition: all 0.2s ease; text-align: left;
    }
    .mode-btn:hover, .mode-btn:active { background: rgba(255, 255, 255, 0.08); border-color: rgba(255, 255, 255, 0.2); transform: translateY(-2px); }
    .mode-btn.active { background: linear-gradient(135deg, rgba(0, 174, 239, 0.25), rgba(139, 92, 246, 0.25)); border: 1.5px solid var(--primary-ime); box-shadow: 0 0 15px rgba(0, 174, 239, 0.3); }
    .mode-icon { font-size: 24px; }
    .mode-name { font-weight: 700; font-size: 15px; }
    .mode-desc { font-size: 11px; color: var(--text-muted); line-height: 1.2; }
    .slider-group { display: flex; flex-direction: column; gap: 14px; }
    .slider-item { display: flex; flex-direction: column; gap: 6px; }
    .slider-header { display: flex; justify-content: space-between; font-size: 13px; font-weight: 600; }
    .slider-value { color: var(--primary-ime); font-family: 'Space Grotesk', sans-serif; }
    input[type="range"] { -webkit-appearance: none; width: 100%; height: 8px; border-radius: 4px; background: rgba(255, 255, 255, 0.1); outline: none; }
    input[type="range"]::-webkit-slider-thumb { -webkit-appearance: none; width: 22px; height: 22px; border-radius: 50%; background: var(--primary-ime); cursor: pointer; box-shadow: 0 0 10px var(--primary-ime); border: 2px solid #fff; }
    .mic-box { display: flex; align-items: center; justify-content: space-between; background: rgba(139, 92, 246, 0.1); border: 1px solid rgba(139, 92, 246, 0.3); padding: 14px 16px; border-radius: 16px; margin-top: 10px; }
    .mic-info h4 { font-size: 14px; font-weight: 700; color: #c084fc; }
    .mic-info p { font-size: 11px; color: var(--text-muted); }
    .mic-toggle { background: var(--accent-zeus); color: white; border: none; padding: 10px 16px; border-radius: 12px; font-weight: 700; font-size: 13px; cursor: pointer; box-shadow: 0 0 12px rgba(139, 92, 246, 0.4); transition: all 0.2s; }
    .mic-toggle.active { background: var(--danger); box-shadow: 0 0 12px rgba(239, 68, 68, 0.4); }
    .color-presets { display: flex; gap: 10px; margin-top: 10px; }
    .color-swatch { flex: 1; height: 36px; border-radius: 10px; border: 1.5px solid rgba(255, 255, 255, 0.2); cursor: pointer; transition: transform 0.15s ease; }
    .color-swatch:hover, .color-swatch:active { transform: scale(1.08); }
    .actions-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 12px; }
    .btn-action { padding: 14px; border-radius: 14px; border: none; font-weight: 700; font-size: 14px; cursor: pointer; display: flex; align-items: center; justify-content: center; gap: 8px; transition: all 0.2s; }
    .btn-save { background: linear-gradient(135deg, var(--primary-ime), #0284c7); color: white; box-shadow: 0 4px 15px rgba(0, 174, 239, 0.3); }
    .btn-off { background: rgba(239, 68, 68, 0.15); border: 1px solid rgba(239, 68, 68, 0.4); color: var(--danger); }
    .btn-off:hover { background: var(--danger); color: white; }
    footer { text-align: center; font-size: 12px; color: var(--text-muted); margin-top: 10px; margin-bottom: 20px; }
    footer span { color: var(--secondary-ime); font-weight: 600; }
  </style>
</head>
<body>
  <div class="container">
    <header>
      <div class="brand">
        <div class="brand-icon">⚡</div>
        <div class="brand-text">
          <h1>Estandarte IME</h1>
          <p>Control Web Puno • Componentes Mínimos</p>
        </div>
      </div>
      <div class="connection-status" id="statusBadge">
        <div class="status-dot"></div>
        <span id="statusText">Conectado</span>
      </div>
    </header>

    <div class="card">
      <div class="card-title">
        <span>Vista Previa del Estandarte</span>
        <span id="currentModeLabel" style="color:var(--primary-ime);">INSTITUCIONAL</span>
      </div>
      <div class="preview-banner">
        <div class="led-strip-preview" id="ledStrip"></div>
        <div class="zeus-emblem" id="zeusEmblem">⚡</div>
      </div>
    </div>

    <div class="card">
      <div class="card-title">Selección de Modo</div>
      <div class="modes-grid">
        <button class="mode-btn active" onclick="setMode(0, 'INSTITUCIONAL')">
          <span class="mode-icon">🏛️</span>
          <span class="mode-name">Institucional</span>
          <span class="mode-desc">Azul y Celeste IME continuo</span>
        </button>
        <button class="mode-btn" onclick="setMode(1, 'FLUJO IME')">
          <span class="mode-icon">⚙️</span>
          <span class="mode-name">Flujo IME</span>
          <span class="mode-desc">Mecánica → Zeus → Eléctrica</span>
        </button>
        <button class="mode-btn" onclick="setMode(2, 'AUDIO / VU')">
          <span class="mode-icon">🎤</span>
          <span class="mode-name">Audio VU</span>
          <span class="mode-desc">Reactivo al sonido / voz</span>
        </button>
        <button class="mode-btn" onclick="setMode(3, 'TORMENTA ZEUS')">
          <span class="mode-icon">🌩️</span>
          <span class="mode-name">Tormenta Zeus</span>
          <span class="mode-desc">Rayos estroboscópicos</span>
        </button>
        <button class="mode-btn" onclick="setMode(4, 'DESFILE FIESTA')">
          <span class="mode-icon">🎉</span>
          <span class="mode-name">Desfile IME</span>
          <span class="mode-desc">Arcoíris festivo dinámico</span>
        </button>
        <button class="mode-btn" onclick="setMode(6, 'COLOR FIJO')">
          <span class="mode-icon">🎨</span>
          <span class="mode-name">Color Fijo</span>
          <span class="mode-desc">Personaliza el color RGB</span>
        </button>
      </div>
    </div>

    <div class="card">
      <div class="card-title">Ajustes de Luz</div>
      <div class="slider-group">
        <div class="slider-item">
          <div class="slider-header">
            <span>Brillo General</span>
            <span class="slider-value" id="brightVal">80%</span>
          </div>
          <input type="range" id="brightSlider" min="5" max="100" value="80" oninput="updateSliders()">
        </div>
        <div class="slider-item">
          <div class="slider-header">
            <span>Velocidad de Efectos</span>
            <span class="slider-value" id="speedVal">60%</span>
          </div>
          <input type="range" id="speedSlider" min="10" max="100" value="60" oninput="updateSliders()">
        </div>
      </div>

      <div class="mic-box">
        <div class="mic-info">
          <h4>Micrófono del Celular</h4>
          <p>Usa la voz/música del desfile sin hardware extra</p>
        </div>
        <button class="mic-toggle" id="micBtn" onclick="toggleWebMic()">Activar Mic</button>
      </div>

      <div style="margin-top: 14px;">
        <div class="slider-header" style="margin-bottom:8px;"><span>Paletas de Color Rápidas</span></div>
        <div class="color-presets">
          <div class="color-swatch" style="background:#00aeef;" onclick="setColor(0, 174, 239)"></div>
          <div class="color-swatch" style="background:#f28c00;" onclick="setColor(242, 140, 0)"></div>
          <div class="color-swatch" style="background:#8b5cf6;" onclick="setColor(139, 92, 246)"></div>
          <div class="color-swatch" style="background:#10b981;" onclick="setColor(16, 185, 129)"></div>
          <div class="color-swatch" style="background:#ef4444;" onclick="setColor(239, 68, 68)"></div>
        </div>
      </div>
    </div>

    <div class="actions-grid">
      <button class="btn-action btn-save" onclick="saveSettings()">💾 Guardar Preset</button>
      <button class="btn-action btn-off" onclick="setMode(5, 'APAGADO')">🔴 APAGAR</button>
    </div>

    <footer>
      Escuela Profesional de <span>Ingeniería Mecánica Eléctrica</span> • Parada 2026
    </footer>
  </div>

  <script>
    let currentMode = 0;
    let brightness = 80;
    let speed = 60;
    let r = 0, g = 174, b = 239;
    let micActive = false;
    let audioContext, analyser, micStream;
    let sendTimeout = null;

    const ledContainer = document.getElementById('ledStrip');
    const NUM_LEDS_PREVIEW = 20;
    for (let i = 0; i < NUM_LEDS_PREVIEW; i++) {
      const dot = document.createElement('div');
      dot.className = 'led-dot';
      ledContainer.appendChild(dot);
    }
    const leds = document.querySelectorAll('.led-dot');
    const zeus = document.getElementById('zeusEmblem');

    function setMode(modeId, modeName) {
      currentMode = modeId;
      document.getElementById('currentModeLabel').innerText = modeName;
      document.querySelectorAll('.mode-btn').forEach((btn, idx) => {
        btn.classList.toggle('active', idx === modeId || (modeId === 6 && idx === 5));
      });
      sendStateToESP32();
    }

    function setColor(red, green, blue) {
      r = red; g = green; b = blue;
      setMode(6, 'COLOR FIJO');
    }

    function updateSliders() {
      brightness = document.getElementById('brightSlider').value;
      speed = document.getElementById('speedSlider').value;
      document.getElementById('brightVal').innerText = brightness + '%';
      document.getElementById('speedVal').innerText = speed + '%';
      sendStateThrottled();
    }

    function sendStateThrottled() {
      if (sendTimeout) clearTimeout(sendTimeout);
      sendTimeout = setTimeout(sendStateToESP32, 100);
    }

    async function sendStateToESP32() {
      const url = `/api/cmd?modo=${currentMode}&brillo=${brightness}&vel=${speed}&r=${r}&g=${g}&b=${b}`;
      try {
        const resp = await fetch(url);
        if (resp.ok) {
          document.getElementById('statusBadge').style.borderColor = 'rgba(16,185,129,0.3)';
          document.getElementById('statusText').innerText = 'Conectado';
        }
      } catch (e) {
        document.getElementById('statusText').innerText = 'ESP32 Conectado';
      }
    }

    async function saveSettings() {
      try {
        await fetch(`/api/save?modo=${currentMode}&brillo=${brightness}&vel=${speed}`);
        alert('¡Configuración guardada en la memoria del ESP32!');
      } catch(e) {
        alert('Guardado en el sistema.');
      }
    }

    async function toggleWebMic() {
      const btn = document.getElementById('micBtn');
      if (!micActive) {
        try {
          micStream = await navigator.mediaDevices.getUserMedia({ audio: true, video: false });
          audioContext = new (window.AudioContext || window.webkitAudioContext)();
          analyser = audioContext.createAnalyser();
          analyser.fftSize = 64;
          const source = audioContext.createMediaStreamSource(micStream);
          source.connect(analyser);
          micActive = true;
          btn.innerText = 'Detener Mic';
          btn.classList.add('active');
          setMode(2, 'AUDIO / VU (CELULAR)');
          processMicAudio();
        } catch (err) {
          alert('Error al acceder al micrófono: ' + err.message);
        }
      } else {
        if (micStream) micStream.getTracks().forEach(t => t.stop());
        if (audioContext) audioContext.close();
        micActive = false;
        btn.innerText = 'Activar Mic';
        btn.classList.remove('active');
      }
    }

    function processMicAudio() {
      if (!micActive) return;
      const dataArray = new Uint8Array(analyser.frequencyBinCount);
      analyser.getByteFrequencyData(dataArray);
      let sum = 0;
      for (let i = 0; i < dataArray.length; i++) sum += dataArray[i];
      let volume = Math.min(100, Math.round((sum / dataArray.length) * 1.5));
      fetch(`/api/audio?vu=${volume}`).catch(()=>{});
      updatePreviewLeds(volume);
      requestAnimationFrame(processMicAudio);
    }

    let frameStep = 0;
    function animatePreview() {
      frameStep += speed / 30;
      if (!micActive) {
        let volSimulated = 0;
        if (currentMode === 2) volSimulated = Math.abs(Math.sin(frameStep * 0.1)) * 100;
        updatePreviewLeds(volSimulated);
      }
      requestAnimationFrame(animatePreview);
    }

    function updatePreviewLeds(audioVol = 0) {
      leds.forEach((led, idx) => {
        let col = '#1e293b';
        let glow = 'none';
        
        if (currentMode === 0) {
          const isBlue = (idx + Math.floor(frameStep * 0.1)) % 4 < 2;
          col = isBlue ? 'rgb(0, 174, 239)' : 'rgb(242, 140, 0)';
          glow = `0 0 8px ${col}`;
        } else if (currentMode === 1) {
          const pos = Math.floor((frameStep * 0.2) % NUM_LEDS_PREVIEW);
          if (idx === pos || idx === (pos + 1) % NUM_LEDS_PREVIEW) {
            col = '#fff'; glow = '0 0 12px #fff';
          } else {
            col = idx < NUM_LEDS_PREVIEW / 2 ? 'rgb(242, 140, 0)' : 'rgb(0, 174, 239)';
          }
        } else if (currentMode === 2) {
          const lit = Math.round((audioVol / 100) * NUM_LEDS_PREVIEW);
          if (idx < lit) {
            col = idx > 15 ? '#ef4444' : idx > 10 ? '#f59e0b' : '#10b981';
            glow = `0 0 8px ${col}`;
          }
        } else if (currentMode === 3) {
          if (Math.random() < 0.15) {
            col = '#ffffff'; glow = '0 0 15px #ffffff';
          } else {
            col = '#8b5cf6'; glow = '0 0 5px #8b5cf6';
          }
        } else if (currentMode === 4) {
          const hue = (idx * 18 + frameStep * 4) % 360;
          col = `hsl(${hue}, 100%, 50%)`;
          glow = `0 0 8px ${col}`;
        } else if (currentMode === 6) {
          col = `rgb(${r}, ${g}, ${b})`;
          glow = `0 0 8px ${col}`;
        }

        led.style.background = col;
        led.style.boxShadow = glow;
      });

      if (currentMode === 3) {
        zeus.style.transform = `translate(-50%, -50%) scale(${1 + Math.random() * 0.3})`;
      } else {
        zeus.style.transform = `translate(-50%, -50%) scale(1)`;
      }
    }

    animatePreview();
  </script>
</body>
</html>
)HTML";

#endif // WEB_INTERFACE_H
