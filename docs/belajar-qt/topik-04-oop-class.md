# Topik 4 — OOP: Class, Constructor, Destructor
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Sesi 4)

## Ringkasan konsep
Class di C++ mirip JS ES6, dengan 3 perbedaan kunci: **(1)** default access modifier adalah `private` (di JS semuanya public), **(2)** ada **destructor** yang otomatis dipanggil saat object dihancurkan (untuk cleanup resource), dan **(3)** ada **initializer list** (`: nama(n), lat(l)`) yang lebih efisien daripada assignment di body constructor karena langsung construct member, bukan default-construct lalu assign.

## Analogi JavaScript/React
| JavaScript ES6 | C++ |
|---|---|
| `class Foo { constructor() {} }` | `class Foo { public: Foo() {} };` |
| Semua field public default | Default `private` (kalau pakai `class`) atau `public` (kalau `struct`) |
| Tidak ada destructor | `~Foo() { /* cleanup */ }` |
| `this.x = x` di constructor | `Foo(int x) : x(x) {}` (initializer list, lebih efisien) |
| Tidak ada `protected` runtime | `protected:` access modifier |

## Kode inti
```cpp
class Vessel {
private:
    std::string nama;
    double latitude, longitude, kecepatan;

public:
    Vessel(std::string n, double lat, double lon)
        : nama(n), latitude(lat), longitude(lon), kecepatan(0.0) {}

    ~Vessel() { std::cout << "[-] Dihapus: " << nama << std::endl; }

    void setKecepatan(double k) { if (k >= 0) kecepatan = k; }
    double getLatitude() const { return latitude; }   // const = method tidak mengubah state
};

{
    Vessel v("KM A", -6.2, 106.8);    // constructor dipanggil
}   // destructor dipanggil saat keluar scope
```

## Aturan penting
- **Kapan pakai `private`:** field internal yang gak boleh diakses langsung dari luar (encapsulation).
- **Kapan pakai `protected`:** field yang perlu diakses oleh class anak (subclass) tapi gak public.
- **Kapan pakai initializer list:** selalu, kecuali ada logic kompleks yang butuh body constructor.
- **Common mistake:** lupa `const` di method getter → method gak bisa dipanggil dari objek `const`. Atau assign di constructor body bukan initializer list → 2× kerja (default-construct + assign).

## Catatan tambahan
- Selalu pass object ke fungsi pakai `const Vessel&` — hindari copy mahal.
- Member function di-define di dalam class body otomatis `inline` (suggest compiler untuk inline).
- `class` vs `struct`: identik kecuali default access (`private` vs `public`). Konvensi: `struct` untuk POD (plain data), `class` untuk yang punya behavior.
