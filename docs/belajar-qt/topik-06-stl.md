# Topik 6 — STL: vector, map, string
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Sesi 6)

## Ringkasan konsep
**STL (Standard Template Library)** menyediakan container generic mirip dengan koleksi di JS. `std::vector<T>` = `Array` (dynamic, contiguous memory), `std::map<K,V>` = `Map` (selalu terurut by key, BTree-based), `std::string` = `string`. Perbedaan kritis dari JS: akses `map[key]` untuk key yang **tidak ada** akan **membuat entry baru** dengan default value, bukan return undefined — gunakan `.count()` atau `.find()` untuk cek aman.

## Analogi JavaScript/React
| JavaScript | C++ STL | Header |
|---|---|---|
| `Array` / `[]` | `std::vector<T>` | `<vector>` |
| `Map` / `Object` | `std::map<K,V>` (sorted) atau `std::unordered_map<K,V>` (hash) | `<map>`, `<unordered_map>` |
| `string` | `std::string` | `<string>` |
| `arr.push(x)` | `vec.push_back(x)` |  |
| `obj[k] !== undefined` | `map.count(k) > 0` |  |
| `for (const x of arr)` | `for (const auto& x : vec)` |  |

## Kode inti
```cpp
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>

// vector
std::vector<std::string> kapal;
kapal.push_back("KM Nusantara");
for (const std::string& nama : kapal) std::cout << nama << "\n";
// JANGAN push_back di dalam range-based for loop — invalidate iterator!

// map
std::map<std::string, double> kecepatan;
kecepatan["KM Nusantara"] = 14.5;
if (kecepatan.count("KM Nusantara") > 0) { /* aman akses */ }
for (const auto& entry : kecepatan) {
    std::cout << entry.first << ": " << entry.second << "\n";
}

// Format double → string (JANGAN pakai std::to_string — hasilnya 14.500000)
std::ostringstream oss;
oss << std::fixed << std::setprecision(1) << 14.5678;
std::string hasil = oss.str();   // "14.6"
```

## Aturan penting
- **Kapan pakai `vector`:** koleksi terurut by insertion, akses random by index, butuh contiguous memory (cache-friendly).
- **Kapan pakai `map` vs `unordered_map`:** `map` kalau perlu iterasi terurut by key; `unordered_map` kalau cuma butuh O(1) lookup.
- **Kapan TIDAK pakai `map[]`:** untuk cek keberadaan key — pakai `count()` atau `find()`. `map[]` SELALU bikin entry baru kalau gak ada.
- **Common mistake:** modify container saat iterasi → undefined behavior. Pakai index loop atau collect dulu ke vector temp.

## Catatan tambahan
- `vector::reserve(n)` alokasi capacity awal — hindari realokasi berulang kalau lo tahu size approximate.
- `std::to_string(double)` selalu 6 desimal trailing zeros — pakai `ostringstream` untuk kontrol presisi.
- `auto&` di range-for hindari copy; tanpa `&` setiap item di-copy.
