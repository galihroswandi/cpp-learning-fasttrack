# Topik 20 — Networking
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 3 Topik 7)
Project: [networking_basic/](../../networking_basic/)

## Ringkasan konsep
`QNetworkAccessManager` (QNAM) = `fetch` di Qt — async, non-blocking. Satu QNAM per app sudah cukup. Pakai signal `finished` untuk handle response (dipanggil untuk **setiap reply**). Wajib `reply->deleteLater()` di setiap exit path supaya gak leak. Untuk pakai module Network, tambah di CMake: `find_package(Qt6 COMPONENTS Network)` + `target_link_libraries(... Qt6::Network)`.

## Analogi JavaScript/React
| JavaScript | Qt |
|---|---|
| `fetch(url)` | `manager->get(QNetworkRequest(url))` |
| `.then(res => res.text())` | signal `finished` → slot |
| `res.ok` | `reply->error() == QNetworkReply::NoError` |
| `res.text()` | `QString::fromUtf8(reply->readAll())` |
| `res.json()` | `QJsonDocument::fromJson(reply->readAll())` |
| `await fetch(...)` | tidak ada — selalu signal-based async |

## Kode inti
```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)
target_link_libraries(app PRIVATE Qt6::Widgets Qt6::Network)
```

```cpp
// Setup — satu QNAM per app
manager = new QNetworkAccessManager(this);
connect(manager, &QNetworkAccessManager::finished,
        this, &MainWindow::onReplyFinished);

// Send request — async, langsung return
QNetworkRequest request;
request.setUrl(QUrl("https://api.example.com/data"));
manager->get(request);                         // GET; ada juga post(), put()

// Handle response
void onReplyFinished(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << reply->errorString();
        reply->deleteLater();                  // WAJIB di setiap exit
        return;
    }
    QString data = QString::fromUtf8(reply->readAll());
    label->setText(data);
    reply->deleteLater();                      // bukan delete — masih di call stack Qt
}
```

## Aturan penting
- **Kapan pakai QNetworkAccessManager:** semua HTTP/HTTPS request.
- **Kapan pakai 1 QNAM vs banyak:** 1 cukup, di-reuse untuk semua request. Banyak QNAM cuma untuk separation of concerns ekstrim.
- **Common mistake:** `delete reply` (langsung) → crash karena reply masih ada di call stack Qt. Pakai `deleteLater()`.
- **Common mistake:** lupa disable tombol saat request in-flight → double-click bikin 2 request bersamaan.

## Catatan tambahan
- `finished` signal dipanggil untuk **SETIAP** reply — kalau ada 2 request bersamaan, slot dipanggil 2x. Pakai `reply->property("requestId", id)` untuk disambiguate.
- Untuk POST dengan body: `manager->post(request, byteArray)`. Set header `request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json")`.
- WebSocket pakai `QWebSocket` (module `WebSockets`).
- Untuk SSL self-signed: handle `sslErrors` signal lalu `reply->ignoreSslErrors()` (cuma untuk dev).
