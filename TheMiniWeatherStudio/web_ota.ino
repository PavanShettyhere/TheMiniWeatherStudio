#include "config.h"

static const char* OTA_FORM = R"HTML(
<!DOCTYPE html><html><head>
<meta charset="utf-8"/>
<meta name="viewport" content="width=device-width, initial-scale=1"/>
<title>ESP32 Web OTA</title>
<style>
body{font-family:Arial;margin:24px;background:#0b1220;color:#e6edf7}
.card{max-width:520px;margin:auto;padding:18px;border:1px solid rgba(255,255,255,.12);border-radius:14px;background:rgba(255,255,255,.04)}
button{padding:10px 14px;border-radius:10px;border:1px solid rgba(59,130,246,.6);background:rgba(59,130,246,.22);color:#e6edf7;font-weight:700}
input{width:100%}
.small{color:#9db0cc;font-size:13px}
</style></head>
<body><div class="card">
<h2>Web OTA Update</h2>
<p class="small">Upload a firmware <b>.bin</b> file.</p>
<form method="POST" action="/update" enctype="multipart/form-data">
  <input type="file" name="update" accept=".bin" required><br><br>
  <button type="submit">Upload</button>
</form>
<p class="small">Device will reboot after update.</p>
</div></body></html>
)HTML";

static void handleUpdatePage() {
  if (!checkAuth()) return;
  server.send(200, "text/html", OTA_FORM);
}

static void handleUpdateUpload() {
  if (!checkAuth()) return;

  HTTPUpload& up = server.upload();

  if (up.status == UPLOAD_FILE_START) {
    Serial.printf("WebOTA: start %s\n", up.filename.c_str());
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
      Update.printError(Serial);
    }
  } else if (up.status == UPLOAD_FILE_WRITE) {
    if (Update.write(up.buf, up.currentSize) != up.currentSize) {
      Update.printError(Serial);
    }
  } else if (up.status == UPLOAD_FILE_END) {
    if (Update.end(true)) {
      Serial.printf("WebOTA: success %u bytes. Rebooting...\n", up.totalSize);
    } else {
      Update.printError(Serial);
    }
  }
}

void setupWebOTA() {
  server.on("/update", HTTP_GET, handleUpdatePage);
  server.on(
    "/update", HTTP_POST,
    []() {
      if (!checkAuth()) return;
      server.send(200, "text/plain", Update.hasError() ? "Update Failed" : "Update OK. Rebooting...");
      delay(200);
      ESP.restart();
    },
    handleUpdateUpload
  );
}
