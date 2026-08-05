# Topik 7 — Memory Management
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Sesi 7)

## Ringkasan konsep
C++ punya 2 area memory: **stack** (variabel lokal, otomatis dihapus saat keluar scope `{}`) dan **heap** (`new`, harus manual `delete` — kalau lupa = **memory leak**). Untuk hindari leak, kode modern pakai **smart pointer**: `std::unique_ptr` (satu pemilik, auto-delete) atau `std::shared_ptr` (banyak pemilik, reference counting). Konsep **RAII** (Resource Acquisition Is Initialization) = resource dipegang object yang umurnya dikontrol scope, sehingga destructor selalu jalan termasuk saat exception.

## Analogi JavaScript/React
| JavaScript | C++ |
|---|---|
| Garbage Collector otomatis | Manual `delete` atau smart pointer |
| Tidak ada `new`/`delete` eksplisit | Stack vs heap dibedakan |
| Tidak ada "leak" konseptual (kecuali reference cycle) | Lupa `delete` = leak |
| Reference counting otomatis | `shared_ptr` (explicit ref counting) |

## Kode inti
```cpp
#include <memory>

// Stack — otomatis dihapus
{
    Sensor s("GPS");
    s.baca();
}   // destructor s otomatis jalan

// Raw pointer — hindari di kode modern
Sensor* raw = new Sensor("GPS");
raw->baca();
delete raw;                                 // wajib

// unique_ptr — satu pemilik
auto uptr = std::make_unique<Sensor>("Radar");
uptr->baca();
auto uptr2 = std::move(uptr);               // ownership transfer; uptr sekarang null

// shared_ptr — banyak pemilik, ref counting
auto sptr1 = std::make_shared<Sensor>("AIS");
{ auto sptr2 = sptr1; }                     // count=2, lalu 1 setelah keluar scope

// Ambil raw pointer dari smart pointer (non-owning)
Sensor* observer = uptr.get();              // JANGAN delete observer
```

## Aturan penting
- **Kapan pakai `unique_ptr`:** default untuk heap allocation; satu pemilik yang jelas.
- **Kapan pakai `shared_ptr`:** kepemilikan dibagi (cache, observer pattern dengan lifetime tidak jelas).
- **Kapan pakai raw pointer:** non-owning observer (cuma akses, gak punya); polymorphism via Qt parent (`new QLabel(this)`).
- **Common mistake:** double-delete (delete pointer yang udah di-delete), atau delete pointer yang dapat dari `.get()` (smart pointer akan delete juga → crash).

## Catatan tambahan
- **RAII:** destructor selalu jalan saat scope berakhir, bahkan kalau ada exception. Pakai class wrapper untuk resource (file handle, lock, network connection).
- `std::move` itu cast, bukan operasi — beneran "memindahkan" ownership untuk move-only types seperti `unique_ptr`.
- `shared_ptr` punya overhead ref counter (atomic increment/decrement) — `unique_ptr` zero-cost.
- Hindari `shared_ptr` cycle (A punya shared_ptr ke B, B punya shared_ptr ke A) — leak. Pakai `weak_ptr` untuk salah satu arah.
