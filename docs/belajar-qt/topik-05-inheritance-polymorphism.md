# Topik 5 — Inheritance & Polymorphism
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Sesi 5)

## Ringkasan konsep
Polymorphism di C++ **tidak otomatis** seperti di JavaScript — lo wajib tandai method base class dengan keyword **`virtual`**. Method anak yang override pakai keyword `override` (opsional tapi sangat direkomendasi — compiler akan error kalau signature salah). Destructor di base class harus virtual juga, karena tanpa itu destructor anak gak akan jalan saat hapus via pointer base — resource leak.

## Analogi JavaScript/React
| JavaScript | C++ |
|---|---|
| `class Child extends Parent` | `class Child : public Parent` |
| Override otomatis | Wajib `virtual` di base + `override` di child |
| `super.method()` | `Parent::method()` |
| Tidak ada destructor | `virtual ~Parent()` wajib di base |

## Kode inti
```cpp
class Vessel {
public:
    virtual ~Vessel() {}                            // virtual destructor — WAJIB
    virtual void tampilkan() { std::cout << "Kapal\n"; }
};

class Warship : public Vessel {
public:
    void tampilkan() override {                     // override — type-safe
        Vessel::tampilkan();                        // panggil parent dulu
        std::cout << "Warship\n";
    }
};

// Polymorphism — pointer base, object child
Vessel* armada[2];
armada[0] = new Vessel();
armada[1] = new Warship();
for (auto v : armada) v->tampilkan();   // panggil method yang TEPAT sesuai object asli
for (auto v : armada) delete v;          // virtual destructor → cleanup benar
```

## Aturan penting
- **Kapan pakai `virtual`:** method di base class yang akan di-override anak.
- **Kapan pakai `override`:** semua method di child yang override parent — biarkan compiler catch typo signature.
- **Kapan pakai `final`:** kalau lo mau larang subclass lain override method ini.
- **Common mistake:** lupa `virtual ~Vessel()` → `delete basePtr` cuma panggil destructor base, resource child bocor.

## Catatan tambahan
- Order constructor: induk dipanggil duluan, lalu anak.
- Order destructor: anak dipanggil duluan, lalu induk (reverse).
- **Pure virtual** (`virtual void foo() = 0;`) bikin class jadi abstract — gak bisa di-instantiate, harus di-implement di subclass. Padanan dengan interface/abstract class di JS/TS.
