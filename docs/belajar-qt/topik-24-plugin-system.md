# Topik 24 — Plugin System
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 4 Topik 3, referensi)

## Ringkasan konsep
Plugin system memungkinkan load kode saat **runtime** tanpa recompile app utama — mirip VSCode extensions atau browser plugins. Pattern: **Interface** (abstract class, kontrak shared) → **Plugin** (implement interface, dikompile sebagai shared library `.so`) → **App** (load `.so` saat runtime via `QPluginLoader`). Bedanya dengan library biasa: library di-link compile-time, plugin di-load runtime.

## Analogi JavaScript/React
| Web ecosystem | Qt Plugin |
|---|---|
| VSCode `extension` | Qt plugin (.so / .dll / .dylib) |
| `package.json` interface contract | C++ abstract class + `Q_DECLARE_INTERFACE` |
| `require('./plugin.js')` runtime | `QPluginLoader::instance()` |
| Static `import` | Library linked at compile time |

## Kode inti
```cpp
// Interface — shared antara app dan plugin (file .h)
class ITranslator {
public:
    virtual ~ITranslator() {}
    virtual QString translate(const QString& text) const = 0;
};
Q_DECLARE_INTERFACE(ITranslator, "com.app.ITranslator/1.0")

// Plugin — dikompile sebagai shared library terpisah
class EnglishPlugin : public QObject, public ITranslator {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.app.ITranslator/1.0")
    Q_INTERFACES(ITranslator)
public:
    QString translate(const QString& text) const override {
        return "[EN] " + text;
    }
};

// App — load plugin saat runtime
QPluginLoader loader("./libplugin_english.so");
QObject* obj = loader.instance();
if (!obj) { qWarning() << loader.errorString(); return; }
ITranslator* plugin = qobject_cast<ITranslator*>(obj);
if (plugin) {
    qDebug() << plugin->translate("Halo");
}
```

```cmake
# CMake plugin — bikin shared library, bukan executable
add_library(plugin_english SHARED plugin_english.cpp)
target_link_libraries(plugin_english PRIVATE Qt6::Core)
```

## Aturan penting
- **Kapan pakai plugin system:** app yang perlu di-extend pihak ketiga tanpa akses source code utama (editor, IDE, browser).
- **Kapan TIDAK pakai:** lo + tim lo control semua kode → pakai library biasa, recompile saja.
- **Common mistake:** IID interface beda antara declaration dan plugin metadata → `instance()` return nullptr.
- **Common mistake:** plugin di-build dengan Qt version berbeda dari app → ABI incompatibility, crash atau gagal load.

## Catatan tambahan
- **Library vs Plugin:**
  - Library (`.so`/`.a`) → di-link saat **compile time**, sudah fix di executable
  - Plugin (`.so`) → di-load saat **runtime** via QPluginLoader
- Plugin discovery pattern: scan folder `plugins/` di app dir, load semua `.so` yang valid.
- Untuk multi-platform: extension berbeda (`.so` Linux, `.dll` Windows, `.dylib` macOS). CMake handle otomatis.
- Topik ini di catatan asli cuma referensi konseptual — belum implementasi end-to-end.
