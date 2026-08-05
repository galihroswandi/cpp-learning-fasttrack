# Topik 3 — Pointer & Referensi
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Sesi 3)

## Ringkasan konsep
Setiap variabel di C++ punya **alamat di RAM**. **Pointer** (`*`) menyimpan alamat itu — bisa null, bisa diarahkan ulang. **Referensi** (`&`) adalah alias permanen untuk variabel yang sama — tidak bisa null, tidak bisa di-rebind. Untuk parameter fungsi, pakai `const&` kalau cuma baca, `&` kalau perlu modifikasi caller, dan pointer kalau parameter opsional atau bisa berubah ke objek lain.

## Analogi JavaScript/React
JavaScript gak punya pointer eksplisit — semua object dipass by reference otomatis, primitive by value. Di C++ lo eksplisit kontrol:
| JavaScript | C++ |
|---|---|
| Object dipass otomatis by reference | `void fn(Obj& o)` atau `void fn(Obj* o)` |
| Primitive dipass by value | `void fn(int x)` (copy) |
| `null` | `nullptr` (untuk pointer), referensi tidak bisa null |

## Kode inti
```cpp
double latitude = -6.2088;

// Pointer
double* ptr = &latitude;    // & = address-of
*ptr = -7.2575;             // * = dereference → sama dengan latitude = -7.2575

// Referensi
double& ref = latitude;     // alias permanen
ref = -7.2575;              // langsung pakai, tanpa dereference

// Pass by reference di fungsi
void tambahOffset(double lat)         { lat += 0.5; }   // caller TIDAK berubah
void tambahOffsetRef(double& lat)     { lat += 0.5; }   // caller IKUT berubah
void tampilkan(const double& lat)     { /* baca saja */ }  // tidak copy, tidak modif
```

## Aturan penting
- **Kapan pakai pointer:** data opsional (`nullptr` valid), array dinamis, kepemilikan heap, polymorphism dengan virtual function.
- **Kapan pakai referensi:** parameter fungsi yang wajib ada dan harus dimodifikasi/dibaca tanpa copy.
- **Kapan pakai `const&`:** parameter object besar (struct, class) yang cuma dibaca — hindari copy mahal.
- **Common mistake:** dereference pointer null → segfault. Pakai `*ptr` tanpa cek `if (ptr)`.

## Catatan tambahan
- `Vessel* v = new Warship(...)` → valid (child IS-A parent, polymorphism).
- `Warship* v = new Vessel(...)` → invalid (parent bukan child).
- Pointer ke pointer (`int**`) ada, tapi jarang dipakai di kode modern — biasanya ganti dengan reference atau container.
