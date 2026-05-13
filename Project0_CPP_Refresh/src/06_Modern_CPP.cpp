/**
 * PROJECT 0 - Program 06: Modern C++ Features (C++11/C++17)
 *
 * Topik:
 * 1. Smart pointers (unique_ptr, shared_ptr)
 * 2. Auto keyword dan type deduction
 * 3. Range-based for loops
 * 4. Move semantics (konsep performa penting)
 * 5. Lambda functions
 * 6. Structured bindings (C++17)
 *
 * Build: cd build && cmake .. && make 06_modern
 * Run:   ./build/bin/06_modern
 */

/**
 * ============================================================
 * UNTUK DEVELOPER JS/TS - BACA DULU!
 * ============================================================
 *
 * Modern C++ (C++11 dan seterusnya) banyak terinspirasi dari
 * fitur-fitur yang ada di bahasa modern seperti JS/TS!
 *
 * Banyak yang akan terasa familiar:
 *
 *   TypeScript:                    Modern C++:
 *   const x = 42;                  auto x = 42;
 *   (x: number) => x * 2           [](int x) { return x * 2; }
 *   for (const val of arr)         for (const auto& val : arr)
 *   let [a, b] = pair;             auto [a, b] = pair;  // C++17!
 *   Optional<T> / T | undefined    std::optional<T>  // C++17
 *
 * Move semantics adalah konsep BARU - tidak ada di JS.
 * Di JS GC handle segalanya, di C++ kamu bisa "pindahkan" ownership
 * resource dengan sangat efisien tanpa copy.
 *
 * PRINSIP MODERN C++:
 *   1. Pakai smart pointers, hindari raw new/delete
 *   2. Pakai auto untuk tipe yang panjang/obvious
 *   3. Pakai range-based for untuk iterasi
 *   4. Pakai lambda untuk inline functions
 *   5. Pakai make_unique/make_shared, bukan new
 * ============================================================
 */

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cstring>
#include <map>
using namespace std;

// ============================================================================
// SECTION 1: Smart Pointers - Memory Management Otomatis
// ============================================================================
//
// Smart pointer = pointer yang "pintar" karena bisa bersihkan dirinya sendiri.
// Ini yang paling dekat dengan Garbage Collector di JS!
//
// unique_ptr = satu pemilik, auto-delete saat keluar scope
// shared_ptr = banyak pemilik, delete saat semua selesai (reference counting)
//
// Analogi JS:
//   unique_ptr ≈ variabel lokal yang otomatis hilang saat function selesai
//   shared_ptr ≈ GC dengan reference counting (seperti GC di V8)

class Widget {
private:
    int id;

public:
    Widget(int i) : id(i) {
        cout << "    [Widget " << id << " dibuat]" << endl;
    }

    ~Widget() {
        cout << "    [Widget " << id << " dihapus otomatis]" << endl;
    }

    void describe() const {
        cout << "      Saya Widget #" << id << endl;
    }
};

void section1_SmartPointers() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: Smart Pointers - Auto Memory Management" << endl;
    cout << "(Ini yang paling dekat dengan GC di JavaScript!)" << endl;
    cout << string(60, '=') << endl;

    cout << "\nRaw pointer (hindari ini - error-prone):" << endl;
    {
        cout << "  Widget* w = new Widget(99);  // harus delete manual!" << endl;
        cout << "  delete w;  // Mudah terlupa -> memory leak" << endl;
    }

    // --- unique_ptr ---
    cout << "\nstd::unique_ptr (satu pemilik, auto-delete):" << endl;
    {
        // make_unique<T> = cara modern membuat unique_ptr (C++14)
        // Bukan: Widget* w = new Widget(1)
        auto w1 = make_unique<Widget>(1);  // 'auto' deduces: unique_ptr<Widget>
        w1->describe();

        // unique_ptr bisa di-"move" (transfer ownership), tidak bisa di-copy
        cout << "  Transfer ownership (move):" << endl;
        auto w2 = move(w1);  // w1 sekarang nullptr, w2 yang punya
        w2->describe();

        // w1 sekarang kosong (nullptr)
        if (!w1) {
            cout << "  w1 sekarang nullptr (sudah dipindah ke w2)" << endl;
        }

        cout << "  Keluar dari scope, w2 otomatis di-delete:" << endl;
    }
    cout << "  -> Destructor dipanggil otomatis! Tidak perlu delete." << endl;

    // --- shared_ptr ---
    cout << "\nstd::shared_ptr (banyak pemilik, delete saat semua selesai):" << endl;
    {
        auto s1 = make_shared<Widget>(2);
        cout << "  use_count setelah make: " << s1.use_count() << endl;  // 1

        auto s2 = s1;  // Bagi kepemilikan - mirip assign object di JS
        cout << "  use_count setelah copy ke s2: " << s1.use_count() << endl;  // 2

        cout << "  s1 dan s2 menunjuk Widget yang sama:" << endl;
        s1->describe();
        s2->describe();

        cout << "  Keluar scope, keduanya dihapus:" << endl;
    }
    cout << "  -> Widget dihapus saat SEMUA shared_ptr sudah hilang" << endl;

    cout << "\nKapan pakai apa:" << endl;
    cout << "  unique_ptr: ownership jelas (1 pemilik) -> paling sering dipakai" << endl;
    cout << "  shared_ptr: ownership dibagi antar beberapa tempat" << endl;
    cout << "  raw pointer: legacy code, tidak punya ownership (view only)" << endl;
}

// ============================================================================
// SECTION 2: Auto Keyword - Type Deduction
// ============================================================================
//
// `auto` di C++ = type inference di TypeScript
//
// TypeScript:
//   const x = 42;        // TS tau ini number
//   const arr = [1,2,3]; // TS tau ini number[]
//
// C++:
//   auto x = 42;         // C++ tau ini int
//   auto arr = vector<int>{1,2,3}; // C++ tau ini vector<int>
//
// Kapan pakai auto:
//   - Tipe panjang/kompleks (iterators, templates)
//   - Tipe obvious dari context (auto x = make_unique<Widget>())
//   - Generic code (templates)
//
// Kapan JANGAN pakai auto:
//   - Saat tipe tidak obvious: auto x = getResult(); // x tipe apa?
//   - Saat mau lebih eksplisit untuk readability

void section2_AutoKeyword() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: `auto` - Type Deduction" << endl;
    cout << "(Mirip TypeScript type inference!)" << endl;
    cout << string(60, '=') << endl;

    cout << "\nDi TypeScript: compiler deduces tipe:" << endl;
    cout << "  const x = 42;  // TypeScript: number" << endl;
    cout << "  const s = 'hi'; // TypeScript: string" << endl;

    cout << "\nDi C++, `auto` melakukan hal sama:" << endl;

    auto numInt = 42;                        // int
    auto numFloat = 3.14;                    // double
    auto text = string("Halo");              // std::string
    auto vec = vector<int>{1, 2, 3};         // std::vector<int>

    cout << "  auto numInt = 42;      -> " << numInt << " (int)" << endl;
    cout << "  auto numFloat = 3.14;  -> " << numFloat << " (double)" << endl;
    cout << "  auto text = string(...); -> \"" << text << "\" (string)" << endl;

    cout << "\nAuto sangat berguna untuk tipe panjang:" << endl;
    cout << "  // Tanpa auto (verbose):" << endl;
    cout << "  vector<int>::iterator it = vec.begin();" << endl;
    cout << "  // Dengan auto (bersih):" << endl;
    cout << "  auto it = vec.begin();  // Tipe obvious dari context" << endl;

    cout << "\nauto dalam range-based for loop:" << endl;
    for (auto val : vec) {
        cout << "  " << val << " ";
    }
    cout << endl;

    cout << "\nauto& untuk reference (tidak copy, bisa modifikasi):" << endl;
    for (auto& val : vec) {
        val *= 2;  // Modifikasi element asli
    }
    cout << "  Setelah *=2: ";
    for (auto val : vec) cout << val << " ";
    cout << endl;

    cout << "\nconst auto& untuk read-only reference (efisien, tidak copy):" << endl;
    for (const auto& val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// ============================================================================
// SECTION 3: Range-Based For Loops
// ============================================================================
//
// Range-based for = for...of di JavaScript!
//
// JS:   for (const val of arr) { ... }
// C++:  for (const auto& val : arr) { ... }
//
// Bedanya kecil:
//   JS pakai `of`, C++ pakai `:`
//   C++ perlu tentukan tipe atau `auto`

void section3_RangeBasedFor() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: Range-Based For Loops" << endl;
    cout << "(Sama dengan for...of di JavaScript!)" << endl;
    cout << string(60, '=') << endl;

    vector<int> v = {10, 20, 30, 40, 50};

    cout << "\n[1] Old style (seperti for loop biasa di JS):" << endl;
    cout << "  for (let i = 0; i < arr.length; i++) {   // JS" << endl;
    cout << "  for (int i = 0; i < v.size(); i++) {    // C++" << endl;
    cout << "  Hasil: ";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;

    cout << "\n[2] Range-based for (REKOMENDASI - seperti for...of di JS):" << endl;
    cout << "  for (const val of arr) { ... }   // JavaScript" << endl;
    cout << "  for (const auto& val : v) { ... } // C++" << endl;
    cout << "  Hasil: ";
    for (const auto& val : v) cout << val << " ";
    cout << endl;

    cout << "\n[3] Range-based for dengan modifikasi (pakai referensi &):" << endl;
    cout << "  // Di JS: arr.forEach((val, i, arr) => arr[i] = val * 2)" << endl;
    cout << "  // Di C++: for (auto& val : v) { val *= 2; }" << endl;
    for (auto& val : v) {
        val = val * 2;
    }
    cout << "  Setelah *=2: ";
    for (const auto& val : v) cout << val << " ";
    cout << endl;

    cout << "\nBekerja untuk semua container:" << endl;
    cout << "  vector, array, string, map, set, dll." << endl;

    // Demo dengan string
    string word = "Hello";
    cout << "\nIterasi character by character (string):" << endl;
    for (const auto& ch : word) {
        cout << "  '" << ch << "'" << endl;
    }
}

// ============================================================================
// SECTION 4: Move Semantics - Konsep Khusus C++
// ============================================================================
//
// Move semantics tidak ada di JS - ini konsep pure C++.
//
// Masalah: kalau kamu copy object besar, C++ harus copy SEMUA datanya.
//   MyData a = bigData;  // Copy semua bytes -> lambat!
//
// Move semantics: "pindahkan" data dari satu object ke lain
// TANPA copy. Tinggal "curi" pointer-nya!
//   MyData b = std::move(a);  // Steal pointer dari a -> cepat!
//   // a sekarang kosong/null, b punya datanya
//
// Di JS ini tidak perlu karena semua object adalah reference,
// dan GC yang handle memory. Di C++ kamu perlu move eksplisit
// untuk performa optimal.

class HeavyData {
private:
    char* data;
    size_t size;

public:
    HeavyData(const char* s) : size(strlen(s)) {
        data = new char[size + 1];
        strcpy(data, s);
        cout << "    [COPY constructor: alokasi baru untuk \"" << data << "\"]" << endl;
    }

    // Copy constructor - buat salinan lengkap
    HeavyData(const HeavyData& other) : size(other.size) {
        data = new char[size + 1];
        strcpy(data, other.data);
        cout << "    [COPY: alokasi BARU - lambat untuk data besar]" << endl;
    }

    // Move constructor - "curi" data dari other (C++11)
    HeavyData(HeavyData&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;  // "Kosongkan" source
        other.size = 0;
        cout << "    [MOVE: curi pointer - CEPAT tidak peduli ukuran data!]" << endl;
    }

    ~HeavyData() {
        if (data) {
            cout << "    [DESTROY: bersihkan \"" << data << "\"]" << endl;
        }
        delete[] data;
    }

    const char* get() const { return data ? data : "(empty)"; }
};

void section4_MoveSemantics() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: Move Semantics - Performa Optimal" << endl;
    cout << "(Konsep ini tidak ada di JS - GC yang handle)" << endl;
    cout << string(60, '=') << endl;

    cout << "\nCopy: alokasi memori baru, copy semua data (lambat untuk big data):" << endl;
    {
        HeavyData original("Dataset Besar");
        cout << "  Buat copy:" << endl;
        HeavyData copy = original;  // Copy constructor
        cout << "  original: " << original.get() << endl;
        cout << "  copy: " << copy.get() << endl;
    }

    cout << "\nMove: curi pointer (cepat, tidak peduli ukuran data):" << endl;
    {
        HeavyData original("Dataset Besar");
        cout << "  Pindahkan dengan std::move:" << endl;
        HeavyData moved = move(original);  // Move constructor - "curi" dari original
        cout << "  original setelah move: " << original.get() << " (kosong!)" << endl;
        cout << "  moved: " << moved.get() << " (punya datanya sekarang)" << endl;
    }

    cout << "\nKenapa move penting?" << endl;
    cout << "  - Return value dari function: compiler otomatis pakai move (RVO)" << endl;
    cout << "  - vector.push_back(move(bigObj)): tidak perlu copy" << endl;
    cout << "  - Semua STL containers pakai move otomatis kalau bisa" << endl;
    cout << "\nDi JS ini tidak perlu karena:" << endl;
    cout << "  - Object adalah reference otomatis" << endl;
    cout << "  - Assign = share reference, bukan copy" << endl;
    cout << "  - GC handle memory lifecycle" << endl;
}

// ============================================================================
// SECTION 5: Lambda Functions - Arrow Functions di C++
// ============================================================================
//
// Lambda di C++ = Arrow function di JavaScript!
//
// JavaScript:  (x) => x * 2
// C++:         [](int x) { return x * 2; }
//
// Komponen lambda:
//   []          = capture list (siapa dari luar yang bisa diakses)
//   (int x)     = parameter
//   { return x * 2; } = body
//
// Perbedaan utama dari JS arrow function:
//   - Di JS, closure otomatis capture semua dari outer scope
//   - Di C++, HARUS eksplisit di capture list []
//   - [=] = capture semua by value (copy)
//   - [&] = capture semua by reference (seperti JS closure)

void section5_Lambdas() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: Lambda Functions" << endl;
    cout << "(= Arrow Functions di JavaScript!)" << endl;
    cout << string(60, '=') << endl;

    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

    cout << "\nPerbandingan syntax:" << endl;
    cout << "  JS:  (x) => x * 2" << endl;
    cout << "  C++: [](int x) { return x * 2; }" << endl;

    cout << "\nLambda sederhana (tidak capture apapun):" << endl;
    auto double_it = [](int x) { return x * 2; };  // Simpan di variable
    cout << "  double_it(5) = " << double_it(5) << endl;

    cout << "\nLambda dengan variable capture:" << endl;
    int multiplier = 10;
    // Di JS: (x) => x * multiplier  // closure otomatis
    // Di C++: [multiplier](int x) { return x * multiplier; }  // eksplisit
    auto multiply = [multiplier](int x) { return x * multiplier; };
    cout << "  Multiply tiap element dengan " << multiplier << ": ";
    for (int x : v) cout << multiply(x) << " ";
    cout << endl;

    cout << "\nLambda dengan reference capture [&] (bisa modifikasi outer variable):" << endl;
    int sum = 0;
    for_each(v.begin(), v.end(), [&sum](int x) { sum += x; });
    // Di JS: v.forEach(x => sum += x)  // closure otomatis capture sum
    cout << "  Sum semua: " << sum << endl;

    cout << "\nLambda sebagai comparator (sort descending):" << endl;
    cout << "  JS:  arr.sort((a, b) => b - a)" << endl;
    cout << "  C++: sort(v.begin(), v.end(), [](int a, int b) { return a > b; })" << endl;
    sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    cout << "  Sorted descending: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    cout << "\nLambda dengan return type eksplisit (optional):" << endl;
    auto isEven = [](int x) -> bool { return x % 2 == 0; };
    cout << "  Even numbers: ";
    for (int x : v) {
        if (isEven(x)) cout << x << " ";
    }
    cout << endl;

    cout << "\nCapture list options:" << endl;
    cout << "  []        tidak capture apapun (paling aman)" << endl;
    cout << "  [=]       capture semua by VALUE (copy) dari outer scope" << endl;
    cout << "  [&]       capture semua by REFERENCE (mirip JS closure)" << endl;
    cout << "  [x, &y]   capture x by value, y by reference" << endl;
}

// ============================================================================
// SECTION 6: Structured Bindings (C++17) - Destructuring!
// ============================================================================
//
// Structured bindings di C++17 = destructuring di JavaScript!
//
// JavaScript:
//   const [a, b] = [1, 2];
//   const {name, age} = person;
//
// C++17:
//   auto [a, b] = make_pair(1, 2);
//   auto [name, age] = person;  // untuk struct/tuple

void section6_StructuredBindings() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Structured Bindings (C++17)" << endl;
    cout << "(= Destructuring di JavaScript!)" << endl;
    cout << string(60, '=') << endl;

    cout << "\nDestructuring di JavaScript:" << endl;
    cout << "  const [a, b] = [1, 2];" << endl;
    cout << "  const {name, age} = person;" << endl;

    cout << "\nStructured bindings di C++17:" << endl;

    // Pair destructuring
    auto pair_data = make_pair(string("Alice"), 30);
    auto [name, age] = pair_data;  // Destructuring!
    cout << "\n  auto [name, age] = make_pair(\"Alice\", 30);" << endl;
    cout << "  name = " << name << ", age = " << age << endl;

    // Map iteration dengan destructuring
    cout << "\nIterasi map dengan structured binding (mirip for...of Map di JS):" << endl;
    cout << "  // JS: for (const [key, val] of map) { ... }" << endl;
    cout << "  // C++: for (const auto& [key, val] : map) { ... }" << endl;

    map<string, int> scores = {{"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};
    for (const auto& [student, score] : scores) {
        cout << "  " << student << ": " << score << endl;
    }

    cout << "\nLain-lain fitur C++17 yang berguna:" << endl;
    cout << "  if constexpr    - compile-time if (untuk template)" << endl;
    cout << "  std::optional   - seperti T | undefined di TypeScript" << endl;
    cout << "  std::string_view- reference ke string tanpa copy (efisien)" << endl;
}

// ============================================================================
// SECTION 7: Perbandingan Old vs Modern C++
// ============================================================================

void section7_OldVsModern() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: Old C++ vs Modern C++ (2011+)" << endl;
    cout << string(60, '=') << endl;

    cout << "\n[OLD C++98/03 - Jangan tulis kode seperti ini lagi]:" << endl;
    cout << "  std::vector<int> v;" << endl;
    cout << "  for (int i = 0; i < v.size(); ++i) {" << endl;
    cout << "    int* p = new int(v[i]);" << endl;
    cout << "    // ... pakai p ..." << endl;
    cout << "    delete p;  // Manual cleanup - mudah terlupa!" << endl;
    cout << "  }" << endl;
    cout << "  Problem: verbose, manual memory, error-prone" << endl;

    cout << "\n[MODERN C++17 - Yang harus ditulis]:" << endl;
    cout << "  auto v = vector<int>{1, 2, 3};" << endl;
    cout << "  for (const auto& val : v) {" << endl;
    cout << "    auto p = make_unique<int>(val);  // Auto-cleanup!" << endl;
    cout << "    // ... pakai p ..." << endl;
    cout << "  }  // p otomatis dihapus" << endl;
    cout << "  Benefits: clean, safe, automatic cleanup, seperti JS!" << endl;

    cout << "\nTimeline fitur modern C++:" << endl;
    cout << "  C++11: auto, range-for, lambda, smart pointer, move semantics" << endl;
    cout << "  C++14: make_unique, auto lambda params" << endl;
    cout << "  C++17: structured bindings, if constexpr, std::optional" << endl;
    cout << "  C++20: concepts, ranges, coroutines (seperti async/await!)" << endl;

    cout << "\nC++20 coroutines SANGAT mirip dengan async/await di JS:" << endl;
    cout << "  JS:   async function fetchData() { const d = await fetch(url); }" << endl;
    cout << "  C++20: Task<Data> fetchData() { auto d = co_await fetch(url); }" << endl;
}

// ============================================================================
// SECTION 8: Real-World Example - Modern C++ Style
// ============================================================================

void section8_ModernStyle() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 8: Real-World - Modern C++ Style" << endl;
    cout << string(60, '=') << endl;

    // Smart pointer untuk ownership jelas
    auto readings = make_unique<vector<double>>();
    readings->push_back(22.5);
    readings->push_back(23.1);
    readings->push_back(21.9);
    readings->push_back(22.8);
    readings->push_back(23.5);

    cout << "\nTemperature readings:" << endl;
    for (const auto& temp : *readings) {
        cout << "  " << temp << " C" << endl;
    }

    // Hitung statistik dengan modern style
    // Mirip: Math.min(...readings) di JS
    auto [minIt, maxIt] = minmax_element(readings->begin(), readings->end());
    double minTemp = *minIt;
    double maxTemp = *maxIt;

    // Hitung sum - mirip readings.reduce((a, b) => a + b, 0) di JS
    double sum = accumulate(readings->begin(), readings->end(), 0.0);
    double avg = sum / readings->size();

    cout << "\nStatistik:" << endl;
    cout << "  Min: " << minTemp << " C" << endl;
    cout << "  Max: " << maxTemp << " C" << endl;
    cout << "  Avg: " << avg << " C" << endl;

    // Filter di atas rata-rata - mirip readings.filter(t => t > avg) di JS
    cout << "\nDi atas rata-rata: ";
    for_each(readings->begin(), readings->end(),
             [avg](double t) { if (t > avg) cout << t << " "; });
    cout << endl;

    cout << "\nTidak perlu manual cleanup!" << endl;
    cout << "  (readings otomatis dihapus saat keluar scope)" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "MODERN C++ - C++11/C++17 Features" << endl;
    cout << "Banyak yang akan terasa familiar dari TypeScript!" << endl;
    cout << string(60, '*') << endl;

    section1_SmartPointers();
    section2_AutoKeyword();
    section3_RangeBasedFor();
    section4_MoveSemantics();
    section5_Lambdas();
    section6_StructuredBindings();
    section7_OldVsModern();
    section8_ModernStyle();

    cout << "\n" << string(60, '=') << endl;
    cout << "RINGKASAN" << endl;
    cout << string(60, '=') << endl;
    cout << "\nPadanan TypeScript → Modern C++:" << endl;
    cout << "  const x = 42           -> auto x = 42" << endl;
    cout << "  for...of               -> range-based for (:)" << endl;
    cout << "  (x) => x * 2           -> [](int x) { return x * 2; }" << endl;
    cout << "  GC otomatis            -> smart pointers (unique_ptr, shared_ptr)" << endl;
    cout << "  const [a,b] = pair     -> auto [a, b] = pair; (C++17)" << endl;
    cout << "  T | undefined          -> std::optional<T> (C++17)" << endl;
    cout << "  async/await            -> coroutines (C++20)" << endl;
    cout << "\nPrinsip Modern C++ yang harus diikuti:" << endl;
    cout << "  1. make_unique/make_shared bukan new/delete" << endl;
    cout << "  2. auto untuk tipe yang obvious/panjang" << endl;
    cout << "  3. Range-based for untuk iterasi container" << endl;
    cout << "  4. Lambda untuk inline/callback functions" << endl;
    cout << "  5. Structured bindings untuk destructuring" << endl;
    cout << "\nProject 0 SELESAI! Siap untuk Qt development!" << endl;
    cout << string(60, '*') << endl << endl;

    return 0;
}
