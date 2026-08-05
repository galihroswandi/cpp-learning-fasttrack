# Topik 2 — Fungsi & Parameter
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Sesi 2)

## Ringkasan konsep
Setiap fungsi C++ wajib deklarasikan **tipe return** dan **tipe setiap parameter**. Beda dari JavaScript, C++ tidak ada hoisting otomatis — kalau definisi fungsi ada di bawah `main`, lo wajib bikin **function prototype** di atas (semacam "janji" ke compiler bahwa fungsi ini ada). Fungsi yang gak return apa-apa pakai keyword `void`. Konversi tipe sempit ke luas (`int` → `double`) otomatis dan aman; sebaliknya butuh cast eksplisit.

## Analogi JavaScript/React
| JavaScript | C++ |
|---|---|
| `function foo(a, b)` (dynamic) | `int foo(int a, int b)` (typed) |
| Hoisting otomatis | Wajib prototype kalau definisi di bawah |
| `function fn() { /* no return */ }` | `void fn() { ... }` |
| Argument check runtime | Argument type check compile-time |

## Kode inti
```cpp
#include <iostream>
#include <cmath>

// Prototype — janji ke compiler
double hitungJarak(double lat1, double lon1, double lat2, double lon2);
void tampilkanPosisi(double lat, double lon);

int main() {
    double d = hitungJarak(-6.2, 106.8, -7.2, 112.7);
    tampilkanPosisi(-6.2, 106.8);
    return 0;
}

double hitungJarak(double lat1, double lon1, double lat2, double lon2) {
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    return std::sqrt(dlat * dlat + dlon * dlon);
}

void tampilkanPosisi(double lat, double lon) {
    std::cout << "Lat: " << lat << ", Lon: " << lon << std::endl;
}
```

## Aturan penting
- **Kapan pakai `void`:** fungsi yang cuma punya efek samping (print, tulis file, ubah state global).
- **Kapan pakai return type:** fungsi yang menghasilkan nilai yang caller butuhkan.
- **Kapan TIDAK pakai prototype:** kalau definisi fungsi sudah di atas `main` — gak perlu deklarasi ganda.
- **Common mistake:** lupa prototype → error `use of undeclared identifier`. Atau prototype beda dengan definisi (typo nama parameter type) → linker error.

## Catatan tambahan
- `int` → `double` widening otomatis aman; `double` → `int` butuh `static_cast<int>(x)` dan akan truncate (bukan round).
- Function overloading: bisa ada beberapa fungsi dengan nama sama asal parameter beda (`int add(int,int)` vs `double add(double,double)`).
