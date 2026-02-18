#include "config.h"

static String htmlPage() {
  return R"HTML(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>The Grand Display</title>
  <style>
    :root{
      --bg:#0b1220;
      --card:#111b2e;
      --card2:#0f172a;
      --text:#e6edf7;
      --muted:#9db0cc;
      --line:rgba(255,255,255,.08);
      --accent:#3b82f6;
      --accent2:#22c55e;
      --warn:#f59e0b;
      --danger:#ef4444;
      --shadow: 0 10px 30px rgba(0,0,0,.35);
      --radius:16px;
    }
    :root[data-theme="light"]{
    --bg:#f5f7fb;
    --text:#0b1220;
    --muted:#4b5a73;
    --line:rgba(0,0,0,.10);
    }
    :root[data-theme="light"] body{
      background: #f5f7fb;
    }
    :root:not([data-theme="light"]) body{
      background: radial-gradient(1200px 700px at 20% -10%, rgba(59,130,246,.25), transparent 60%),
                  radial-gradient(900px 600px at 90% 10%, rgba(34,197,94,.18), transparent 55%),
                  var(--bg);
    }



    *{ box-sizing:border-box; }
    body{
      margin:0;
      font-family: ui-sans-serif, system-ui, -apple-system, Segoe UI, Roboto, Arial;
      background: var(--bg);
      color:var(--text);
    }


    .wrap{
      max-width: 1100px;
      margin: 26px auto;
      padding: 0 16px 30px;
    }

    header{
      display:flex;
      align-items:flex-end;
      justify-content:space-between;
      gap: 16px;
      margin-bottom: 18px;
    }

    .title{
      display:flex;
      flex-direction:column;
      gap:6px;
    }

    h1{
      margin:0;
      font-size: 26px;
      letter-spacing:.2px;
    }
    .sub{
      margin:0;
      color:var(--muted);
      font-size:13px;
    }

    .pill button{
      padding: 8px 10px;
      border-radius: 10px;
      font-size: 13px;
    }
    .pill a{ padding: 8px 10px; }


    .pill{
      display:inline-flex;
      align-items:center;
      gap:8px;
      padding:10px 12px;
      border:1px solid var(--line);
      border-radius:999px;
      background:rgba(255,255,255,.03);
      box-shadow: var(--shadow);
      font-size: 13px;
      color: var(--muted);
      white-space:nowrap;
    }
    .dot{
      width:10px; height:10px; border-radius:50%;
      background: var(--danger);
      box-shadow: 0 0 0 4px rgba(239,68,68,.15);
    }
    .dot.ok{
      background: var(--accent2);
      box-shadow: 0 0 0 4px rgba(34,197,94,.15);
    }

    .grid{
      display:grid;
      grid-template-columns: repeat(12, 1fr);
      gap: 14px;
    }

    .card{
      grid-column: span 6;
      background: linear-gradient(180deg, rgba(255,255,255,.04), rgba(255,255,255,.02));
      border: 1px solid var(--line);
      border-radius: var(--radius);
      box-shadow: var(--shadow);
      overflow:hidden;
    }

    .card .hd{
      padding: 14px 16px 0;
      display:flex;
      align-items:baseline;
      justify-content:space-between;
      gap:12px;
    }
    .card h2{
      margin:0;
      font-size:16px;
      letter-spacing:.2px;
    }
    .badge{
      color: var(--muted);
      font-size:12px;
      padding:6px 10px;
      border:1px solid var(--line);
      border-radius:999px;
      background:rgba(255,255,255,.03);
    }

    .body{
      padding: 12px 16px 16px;
    }

    .row{
      display:flex;
      gap: 14px;
      align-items:center;
      justify-content:space-between;
      flex-wrap:wrap;
    }

    .big{
      font-size: 32px;
      font-weight: 700;
      letter-spacing:.2px;
    }
    .unit{
      font-size: 14px;
      color: var(--muted);
      font-weight: 600;
      margin-left: 6px;
    }

    .kv{
      color: var(--muted);
      font-size: 13px;
    }

    canvas{
      width: 100%;
      max-width: 520px;
      height: 170px;
      display:block;
      margin: 8px auto 0;
    }

    /* GPIO list */
    .gpioItem{
      display:flex;
      align-items:center;
      justify-content:space-between;
      padding: 12px 0;
      border-top:1px solid var(--line);
      gap: 12px;
    }
    .gpioItem:first-child{ border-top:0; }
    .gpioLeft{
      display:flex;
      flex-direction:column;
      gap:4px;
    }
    .gpioName{
      font-weight:700;
      letter-spacing:.2px;
    }
    .gpioState{
      font-size:12px;
      color: var(--muted);
    }

    /* Toggle switch */
    .switch{
      position:relative;
      width: 54px;
      height: 30px;
      flex: 0 0 auto;
    }
    .switch input{ display:none; }
    .slider{
      position:absolute; inset:0;
      background: rgba(255,255,255,.10);
      border:1px solid var(--line);
      border-radius:999px;
      transition:.2s;
      cursor:pointer;
    }
    .slider:before{
      content:"";
      position:absolute;
      width: 24px; height: 24px;
      left: 3px; top: 2px;
      border-radius:50%;
      background: #fff;
      transition:.2s;
      box-shadow: 0 8px 20px rgba(0,0,0,.35);
    }
    .switch input:checked + .slider{
      background: rgba(34,197,94,.35);
      border-color: rgba(34,197,94,.55);
    }
    .switch input:checked + .slider:before{
      transform: translateX(24px);
    }

    /* Message */
    .msgRow{
      display:flex;
      gap: 10px;
      margin-top: 8px;
    }
    input[type="text"]{
      flex:1;
      padding: 12px 12px;
      border-radius: 12px;
      border: 1px solid var(--line);
      background: rgba(255,255,255,.04);
      color: var(--text);
      outline:none;
    }
    button{
      padding: 12px 14px;
      border-radius: 12px;
      border: 1px solid rgba(59,130,246,.55);
      background: rgba(59,130,246,.18);
      color: var(--text);
      cursor:pointer;
      font-weight:700;
      transition:.2s;
    }
    button:hover{ transform: translateY(-1px); background: rgba(59,130,246,.25); }
    button:active{ transform: translateY(0px); }

    /* Responsive */
    @media (max-width: 980px){
      .card{ grid-column: span 12; }
      header{ align-items:flex-start; flex-direction:column; }
      .pill{ width: fit-content; }
    }
  </style>
</head>

<body>
  <div class="wrap">
    <header>
      <div class="title">
        <h1>The Great Wall</h1>
        <p class="sub">A Project by Pavan Shetty</p>
      </div>
      <div class="pill">
        <button id="themeBtn" style="margin-left:10px;">Theme</button>
        <a href="/update" style="color:var(--muted);font-size:13px;text-decoration:none;">Web OTA</a>
        <span id="netDot" class="dot"></span>
        <span id="netText">Connecting…</span>
      </div>
    </header>

    <div class="grid">
      <!-- Temperature -->
      <section class="card">
        <div class="hd">
          <h2>Room Temperature</h2>
          <span class="badge">DHT11</span>
        </div>
        <div class="body">
          <div class="row">
            <div>
              <span class="big" id="tempVal">--.-</span><span class="unit">&deg;C</span>
              <div class="kv" id="tempHint">Comfort band: 20–26&deg;C</div>
            </div>
          </div>
          <canvas id="tempGauge" width="900" height="320"></canvas>
        </div>
      </section>

      <!-- Humidity -->
      <section class="card">
        <div class="hd">
          <h2>Room Humidity</h2>
          <span class="badge">DHT11</span>
        </div>
        <div class="body">
          <div class="row">
            <div>
              <span class="big" id="humVal">--</span><span class="unit">%</span>
              <div class="kv" id="humHint">Comfort band: 40–60%</div>
            </div>
          </div>
          <canvas id="humGauge" width="900" height="320"></canvas>
        </div>
      </section>

      <!-- Potentiometer -->
      <section class="card">
        <div class="hd">
          <h2>Potentiometer</h2>
          <span class="badge">ADC</span>
        </div>
        <div class="body">
          <div class="row">
            <div>
              <span class="big" id="potVal">--</span><span class="unit">%</span>
              <div class="kv">Live analog input</div>
            </div>
          </div>

          <div style="margin-top:12px;">
            <div style="height:14px;border-radius:999px;background:rgba(255,255,255,.10);border:1px solid var(--line);overflow:hidden;">
              <div id="potBar" style="height:100%;width:0%;border-radius:999px;background:linear-gradient(90deg, rgba(59,130,246,.95), rgba(34,197,94,.95));"></div>
            </div>
            <div class="kv" style="margin-top:8px;">Raw: <span id="potRaw">0</span></div>
          </div>
        </div>
      </section>


      <!-- GPIO -->
      <section class="card">
        <div class="hd">
          <h2>GPIO Outputs</h2>
          <span class="badge">Pins</span>
        </div>
        <div class="body" id="gpioList">
          Loading…
        </div>
      </section>

      <!-- Outside Weather -->
      <section class="card">
        <div class="hd">
          <h2>Outside Weather</h2>
          <span class="badge" id="wLoc">--</span>
        </div>
        <div class="body">
          <div class="row">
            <div>
              <span class="big" id="wTemp">--</span><span class="unit">&deg;C</span>
              <div class="kv" id="wDesc">--</div>
            </div>
            <div class="kv" id="wMeta">--</div>
          </div>
        </div>
      </section>



      <!-- OLED message -->
      <section class="card">
        <div class="hd">
          <h2>OLED Message</h2>
          <span class="badge">Bottom line</span>
        </div>
        <div class="body">
          <div class="kv">Type a short message and it will appear on your OLED.</div>
          <div class="msgRow">
            <input id="msg" type="text" maxlength="24" placeholder="Type something…" />
            <button onclick="sendMessage()">Send</button>
          </div>
          <div class="kv" style="margin-top:10px;" id="msgStatus"></div>
        </div>
      </section>
    </div>
  </div>

  <script>
    // ---------- Gauge engine (animated, needle, gradient) ----------
    function clamp(x,a,b){ return Math.max(a, Math.min(b, x)); }

    function applyTheme(t){
      document.documentElement.dataset.theme = t;
      localStorage.setItem('theme', t);
    }
    (function(){
      const saved = localStorage.getItem('theme') || 'dark';
      applyTheme(saved);
      document.getElementById('themeBtn').onclick = () => {
        const cur = localStorage.getItem('theme') || 'dark';
        applyTheme(cur === 'dark' ? 'light' : 'dark');
      };
    })();


    function makeGauge(canvasId, opts){
      const c = document.getElementById(canvasId);
      const ctx = c.getContext('2d');

      const st = {
        value: NaN,
        drawValue: NaN,
        target: NaN,
        min: opts.min,
        max: opts.max,
        unit: opts.unit,
        label: opts.label,
        accent: opts.accent
      };

      function draw(v){
        const w = c.width, h = c.height;
        ctx.clearRect(0,0,w,h);

        const cx = w/2, cy = h*0.88;
        const r  = Math.min(w,h)*0.70;

        const start = Math.PI;   // left
        const end   = 0;         // right

        // Track
        ctx.lineWidth = 32;
        ctx.lineCap = 'round';
        ctx.beginPath();
        ctx.strokeStyle = 'rgba(255,255,255,0.10)';
        ctx.arc(cx, cy, r, start, end);
        ctx.stroke();

        // Value arc
        const vv = isFinite(v) ? clamp(v, st.min, st.max) : st.min;
        const p  = (vv - st.min) / (st.max - st.min);
        const ang = start + (end - start) * p;

        const grad = ctx.createLinearGradient(cx - r, 0, cx + r, 0);
        grad.addColorStop(0.0, 'rgba(59,130,246,0.25)');
        grad.addColorStop(0.5, st.accent);
        grad.addColorStop(1.0, 'rgba(34,197,94,0.30)');

        ctx.beginPath();
        ctx.strokeStyle = grad;
        ctx.arc(cx, cy, r, start, ang);
        ctx.stroke();

        // Needle
        const needleLen = r - 18;
        const nx = cx + Math.cos(ang) * needleLen;
        const ny = cy - Math.sin(ang) * needleLen;

        ctx.lineWidth = 6;
        ctx.beginPath();
        ctx.strokeStyle = 'rgba(255,255,255,0.5)';
        ctx.moveTo(cx, cy);
        ctx.lineTo(nx, ny);
        ctx.stroke();

        ctx.beginPath();
        ctx.fillStyle = 'rgba(255,255,255,0.5)';
        ctx.arc(cx, cy, 10, 0, Math.PI*2);
        ctx.fill();

        // Text
        ctx.textAlign = 'center';
        ctx.fillStyle = 'rgba(230,237,247,0.95)';
        ctx.font = '700 34px Arial';
        const text = isFinite(v) ? (opts.format ? opts.format(v) : v.toFixed(1)) : '--';
        ctx.fillText(text + (st.unit ? (' ' + st.unit) : ''), cx, h*0.48);

        ctx.fillStyle = 'rgba(157,176,204,0.95)';
        ctx.font = '500 18px Arial';
        ctx.fillText(st.label + '  (' + st.min + '–' + st.max + ')', cx, h*0.62);
      }

      function animate(){
        // Smooth easing towards target
        if (!isFinite(st.drawValue) && isFinite(st.target)) st.drawValue = st.target;
        if (isFinite(st.drawValue) && isFinite(st.target)) {
          st.drawValue += (st.target - st.drawValue) * 0.12; // easing factor
          if (Math.abs(st.target - st.drawValue) < 0.02) st.drawValue = st.target;
        }
        draw(st.drawValue);
        requestAnimationFrame(animate);
      }

      requestAnimationFrame(animate);

      return {
        setTarget(v){
          st.target = v;
        }
      };
    }

    const tempGauge = makeGauge('tempGauge', {
      min: 0, max: 50, unit: '°C', label: 'Temperature', accent: 'rgba(59,130,246,0.95)',
      format: (v) => v.toFixed(1)
    });

    const humGauge = makeGauge('humGauge', {
      min: 0, max: 100, unit: '%', label: 'Humidity', accent: 'rgba(34,197,94,0.95)',
      format: (v) => v.toFixed(0)
    });

    // ---------- UI helpers ----------
    function setNet(ok, text){
      const dot = document.getElementById('netDot');
      const t = document.getElementById('netText');
      dot.className = ok ? 'dot ok' : 'dot';
      t.textContent = text;
    }

    async function refreshPot(){
      const res = await fetch('/api/pot');
      if(!res.ok) throw new Error('pot failed');
      const p = await res.json();

      document.getElementById('potVal').textContent = Number(p.percent).toFixed(0);
      document.getElementById('potRaw').textContent = p.raw;

      const bar = document.getElementById('potBar');
      bar.style.width = p.percent + '%';
    }


    // ---------- GPIO ----------
    async function loadGPIO(){
      const res = await fetch('/api/status');
      if(!res.ok) throw new Error('status failed');
      const data = await res.json();

      const wrap = document.getElementById('gpioList');
      wrap.innerHTML = '';

      data.gpios.forEach(g => {
        const row = document.createElement('div');
        row.className = 'gpioItem';

        const left = document.createElement('div');
        left.className = 'gpioLeft';
        left.innerHTML = '<div class="gpioName">GPIO ' + g.pin + '</div>' +
                         '<div class="gpioState">State: <b>' + (g.state ? 'ON' : 'OFF') + '</b></div>';

        const sw = document.createElement('label');
        sw.className = 'switch';
        sw.innerHTML = '<input type="checkbox"' + (g.state ? ' checked' : '') + ' />' +
                       '<span class="slider"></span>';

        sw.querySelector('input').addEventListener('change', async (e) => {
          const state = e.target.checked ? 1 : 0;
          await setGPIO(g.pin, state);
          await loadGPIO();
        });

        row.appendChild(left);
        row.appendChild(sw);
        wrap.appendChild(row);
      });
    }

    async function setGPIO(pin, state){
      const url = '/api/gpio?pin=' + encodeURIComponent(pin) + '&state=' + encodeURIComponent(state);
      const res = await fetch(url, { method:'POST' });
      if(!res.ok) throw new Error('gpio failed');
    }


    //Weather on Web
async function refreshWeather(){
  const res = await fetch('/api/weather');
  if(!res.ok) throw new Error('weather failed');
  const w = await res.json();

  document.getElementById('wLoc').textContent = w.location || '--';

  // Convert "7.2 C" or "7.2C" into just "7.2"
  const tempText = (w.temp || '--')
    .replace('°C','')
    .replace(' C','')
    .replace('C','')
    .trim();

  document.getElementById('wTemp').textContent = tempText;
  document.getElementById('wDesc').textContent = w.desc || '--';
  document.getElementById('wMeta').textContent = 'Updated via Open-Meteo';
}



    // ---------- OLED message ----------
    async function sendMessage(){
      const text = document.getElementById('msg').value || '';
      const status = document.getElementById('msgStatus');
      status.textContent = 'Sending…';

      const res = await fetch('/api/message', {
        method:'POST',
        headers:{ 'Content-Type':'application/x-www-form-urlencoded' },
        body:'text=' + encodeURIComponent(text)
      });

      if(res.ok){
        status.textContent = 'Sent to OLED ✅';
        document.getElementById('msg').value = '';
        setTimeout(()=> status.textContent='', 1200);
      } else {
        status.textContent = 'Failed to send ❌';
      }
    }

    // ---------- DHT refresh ----------
    async function refreshDHT(){
      const res = await fetch('/api/dht');
      if(!res.ok) throw new Error('dht failed');
      const d = await res.json();

      const t = (d.tempC === null) ? NaN : Number(d.tempC);
      const h = (d.hum === null) ? NaN : Number(d.hum);

      document.getElementById('tempVal').textContent = isFinite(t) ? t.toFixed(1) : '--.-';
      document.getElementById('humVal').textContent  = isFinite(h) ? h.toFixed(0) : '--';

      tempGauge.setTarget(t);
      humGauge.setTarget(h);

      setNet(true, 'Online • Live updates');
    }

    async function refreshSys(){
        const res = await fetch('/api/sys');
        if(!res.ok) throw new Error('sys failed');
        const s = await res.json();
        if (s.wifi) setNet(true, 'WiFi OK • ' + (s.rssi ?? '') + ' dBm');
        else setNet(false, 'WiFi DOWN');
      }

    // ---------- Boot ----------
    async function boot(){
      try{
        setNet(false, 'Connecting…');
        await loadGPIO();
        await refreshDHT();
        await refreshPot();
        await refreshWeather();
        await refreshSys();
        
        setInterval(async () => {
          try { await refreshSys(); } catch(e) { setNet(false,'Offline • retrying'); }
        }, 5000);
        setInterval(async () => {
          try { await refreshWeather(); } catch(e) { /* ignore */ }
        }, 10000);
        setInterval(async () => {
          try { await refreshPot(); } catch(e) { /* ignore */ }
        }, 200);
        setInterval(async () => {
          try { await refreshDHT(); } catch(e){ setNet(false,'Offline • retrying'); }
        }, 5000);

        setInterval(async () => {
          try { await loadGPIO(); } catch(e){ /* ignore */ }
        }, 4000);

      } catch(e){
        setNet(false, 'Offline • refresh page');
      }
    }
    boot();
  </script>
</body>
</html>
)HTML";
}

// GET /
static void handleRoot() {
  if (!checkAuth())
    return;
  server.send(200, "text/html", htmlPage());
}

// GET /api/status
static void handleStatus() {
  if (!checkAuth())
    return;

  String json = "{\"gpios\":[";
  for (int i = 0; i < pinCount; i++) {
    json += "{\"pin\":" + String(pins[i]) + ",\"state\":" + (pinState[i] ? "true" : "false") + "}";
    if (i < pinCount - 1)
      json += ",";
  }
  json += "]}";

  server.send(200, "application/json", json);
}

// POST /api/gpio?pin=4&state=1
static void handleGPIO() {
  if (!checkAuth())
    return;

  if (!server.hasArg("pin") || !server.hasArg("state")) {
    server.send(400, "application/json", "{\"error\":\"Missing pin/state\"}");
    return;
  }

  int pin = server.arg("pin").toInt();
  int state = server.arg("state").toInt();

  int idx = indexOfPin(pin);
  if (idx < 0) {
    server.send(404, "application/json", "{\"error\":\"Pin not allowed\"}");
    return;
  }

  if (state != 0 && state != 1) {
    server.send(400, "application/json", "{\"error\":\"State must be 0 or 1\"}");
    return;
  }

  pinState[idx] = (state == 1);
  digitalWrite(pin, pinState[idx] ? HIGH : LOW);

  server.send(200, "application/json", "{\"ok\":true}");
}

// POST /api/message (form: text=...)
static void handleMessage() {
  if (!checkAuth())
    return;

  if (!server.hasArg("text")) {
    server.send(400, "application/json", "{\"error\":\"Missing text\"}");
    return;
  }

  userMessage = server.arg("text");
  if (userMessage.length() == 0)
    userMessage = " ";
  if (userMessage.length() > 24)
    userMessage = userMessage.substring(0, 24);

  saveUserMessage();

  server.send(200, "application/json", "{\"ok\":true}");
}
// GET /api/dht  -> JSON { tempC, hum }
static void handleDHT() {
  if (!checkAuth())
    return;

  String json = "{";
  if (isnan(roomTempC))
    json += "\"tempC\":null,";
  else
    json += "\"tempC\":" + String(roomTempC, 1) + ",";

  if (isnan(roomHum))
    json += "\"hum\":null";
  else
    json += "\"hum\":" + String(roomHum, 0);

  json += "}";
  server.send(200, "application/json", json);
}

// GET /api/pot -> JSON { raw, percent }
static void handlePot() {
  if (!checkAuth())
    return;
  String json = "{\"raw\":" + String(potRaw) + ",\"percent\":" + String(potPercent) + "}";
  server.send(200, "application/json", json);
}

static void handleSys() {
  if (!checkAuth()) return;
  String json = "{";
  json += "\"wifi\":" + String(wifiConnected ? "true" : "false") + ",";
  json += "\"ip\":\"" + wifiIP + "\",";
  json += "\"rssi\":" + String(wifiRSSI) + ",";
  json += "\"page\":" + String(oledPage) + ",";
  json += "\"potMode\":" + String(oledUsePotSelector ? "true" : "false");
  json += "}";
  json += ",\"ap_ip\":\"" + apIP + "\"";
  json += ",\"sta_ip\":\"" + staIP + "\"";
  json += ",\"sta\":" + String(wifiSTAConnected ? "true" : "false");

  server.send(200, "application/json", json);
}

static void handleWeather() {
  if (!checkAuth()) return;

  String loc = LOCATION_NAME;
  loc.replace("\"", "'");
  String t = weatherTemp;
  t.replace("\"", "'");
  String d = weatherDesc;
  d.replace("\"", "'");

  String json = "{";
  json += "\"location\":\"" + loc + "\",";
  json += "\"temp\":\"" + t + "\",";
  json += "\"desc\":\"" + d + "\"";
  json += "}";
  server.send(200, "application/json", json);
}



void setupWebRoutes() {
  server.on("/", handleRoot);
  server.on("/api/status", HTTP_GET, handleStatus);
  server.on("/api/gpio", HTTP_POST, handleGPIO);
  server.on("/api/message", HTTP_POST, handleMessage);
  server.on("/api/dht", HTTP_GET, handleDHT);
  server.on("/api/pot", HTTP_GET, handlePot);
  server.on("/api/weather", HTTP_GET, handleWeather);
  server.on("/api/sys", HTTP_GET, handleSys);

  setupWebOTA();   // adds /update

  
}
