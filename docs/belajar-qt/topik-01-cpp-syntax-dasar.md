# Topik 1 — C++ Syntax Dasar & Tipe Statis
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Sesi 1)

## Ringkasan konsep
Di JavaScript tipe variabel bisa berubah kapan saja, di C++ tipe **dikunci saat deklarasi**. Error tipe ketahuan saat **compile time**, bukan runtime. Tipe dasar yang sering dipakai: `int`, `double`, `float`, `bool`, dan `std::string` (perlu `#include <string>`). Untuk koordinat GPS wajib pakai `double` karena `float` cuma 7 digit presisi — bisa beda puluhan meter di skala global.

## Analogi JavaScript/React
| JavaScript | C++ |
|---|---|
| `let x = 10` → tipe dinamis | `int x = 10` → tipe dikunci |
| `typeof x` runtime check | error tipe = compile error |
| `number` (semua angka) | `int`, `double`, `float` (terpisah) |
| `string` (bawaan) | `std::string` (butuh `#include <string>`) |
| `boolean` | `bool` (disimpan sebagai 1/0) |

## Kode inti
```cpp
#include <iostream>
#include <string>
#include <iomanip>

int main() {
    int kecepatan = 12;
    double latitude = -6.2088;        // wajib double untuk GPS
    bool berlayar = true;
    std::string nama_kapal = "KM Nusantara";

    std::cout << nama_kapal << std::endl;
    std::cout << std::boolalpha << berlayar << std::endl;   // "true" bukan "1"
    std::cout << std::fixed << std::setprecision(4) << latitude;
    std::cout << std::setw(3) << std::setfill('0') << 45;   // "045"
    return 0;
}
```

Compile: `g++ main.cpp -o output && ./output`

## Aturan penting
- **Kapan pakai `double`:** koordinat GPS, kalkulasi presisi tinggi, default untuk floating point.
- **Kapan pakai `float`:** embedded system dengan RAM terbatas, GPU shader.
- **Kapan TIDAK pakai `float`:** koordinat GPS global (presisi 7 digit → error puluhan meter).
- **Common mistake:** lupa `#include <string>` saat pakai `std::string`, atau `std::cout << bool` tanpa `std::boolalpha` → keluar `1`/`0` bukan `true`/`false`.

## Catatan tambahan
- `iomanip` punya manipulator persisten (`std::fixed`, `std::setprecision`) — sekali set, semua output berikutnya ikut format itu.
- `std::endl` flush buffer; `"\n"` tidak flush — `\n` lebih cepat untuk loop besar.
