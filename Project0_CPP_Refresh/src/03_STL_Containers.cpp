/**
 * PROJECT 0 - Program 03: STL Containers dan Algorithms
 *
 * Topik:
 * 1. std::vector - dynamic arrays
 * 2. std::string - string dengan methods yang powerful
 * 3. std::map - key-value data structure
 * 4. Iterators - cara traversal container
 * 5. Algorithms - sort, find, transform, dll
 * 6. Lambda functions - anonymous functions
 *
 * STL = Standard Template Library
 *
 * Build: cd build && cmake .. && make 03_stl
 * Run:   ./build/bin/03_stl
 */

/**
 * ============================================================
 * UNTUK DEVELOPER JS/TS - BACA DULU!
 * ============================================================
 *
 * Kabar baik: STL containers mirip sekali dengan built-in JS/TS!
 *
 * Padanan JS/TS → C++ STL:
 *   Array     → std::vector<T>
 *   Map       → std::map<K,V> atau std::unordered_map<K,V>
 *   Set       → std::set<T>
 *   String    → std::string
 *
 * Contoh perbandingan:
 *   // JS:                          // C++:
 *   let arr = [];                   vector<int> v;
 *   arr.push(10);                   v.push_back(10);
 *   arr.length                      v.size()
 *   arr[0]                          v[0] atau v.at(0)
 *
 *   let map = new Map();            map<string,int> m;
 *   map.set("key", 1);              m["key"] = 1;
 *   map.get("key")                  m["key"]
 *   map.has("key")                  m.find("key") != m.end()
 *
 * Lambda di C++ = Arrow function di JS:
 *   // JS:  (x) => x * 2
 *   // C++: [](int x) { return x * 2; }
 *
 * PERBEDAAN penting:
 *   - C++ containers STRONGLY TYPED: vector<int> hanya bisa int
 *   - Di JS, array bisa campur tipe: [1, "hello", true]
 *   - C++ perlu deklarasi tipe: vector<int>, map<string, int>
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

// ============================================================================
// SECTION 1: std::vector - Dynamic Array
// ============================================================================
//
// vector<T> adalah padanan Array di JavaScript, tapi strongly typed.
//
// JS:   let arr = [10, 20, 30];
// C++:  vector<int> v = {10, 20, 30};
//
// Perbandingan method:
//   JS arr.push(x)      → C++ v.push_back(x)
//   JS arr.pop()        → C++ v.pop_back()
//   JS arr.length       → C++ v.size()
//   JS arr[i]           → C++ v[i]  (tidak cek bounds!)
//   JS arr.at(i)        → C++ v.at(i) (cek bounds, throw exception)
//   JS arr.splice(i,1)  → C++ v.erase(v.begin() + i)
//   JS arr.splice(i,0,x)→ C++ v.insert(v.begin() + i, x)

void section1_Vector() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: std::vector - Dynamic Array" << endl;
    cout << "(Padanan: Array di JavaScript)" << endl;
    cout << string(60, '=') << endl;

    vector<int> v;  // Empty vector - seperti [] di JS

    cout << "\nMenambah elemen dengan push_back() (= Array.push() di JS):" << endl;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    cout << "  v = [";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i < v.size()-1) cout << ", ";
    }
    cout << "]" << endl;

    cout << "\nInfo vector:" << endl;
    cout << "  v.size() = " << v.size() << "  (= arr.length di JS)" << endl;
    cout << "  v[0] = " << v[0] << "  (= arr[0] di JS)" << endl;
    cout << "  v.front() = " << v.front() << "  (elemen pertama)" << endl;
    cout << "  v.back() = " << v.back() << "  (elemen terakhir, seperti arr.at(-1) di JS)" << endl;

    cout << "\nOperasi umum:" << endl;

    v.pop_back();  // Hapus elemen terakhir - seperti arr.pop() di JS
    cout << "  Setelah pop_back(): [";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i < v.size()-1 ? ", " : "");
    cout << "]" << endl;

    v.insert(v.begin() + 1, 15);  // Insert di posisi 1
    cout << "  Setelah insert(pos=1, val=15): [";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i < v.size()-1 ? ", " : "");
    cout << "]" << endl;

    v.erase(v.begin() + 2);  // Hapus element di posisi 2
    cout << "  Setelah erase(pos=2): [";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i < v.size()-1 ? ", " : "");
    cout << "]" << endl;

    cout << "\nKenapa vector > raw array:" << endl;
    cout << "  - Ukuran dinamis (tumbuh sesuai kebutuhan)" << endl;
    cout << "  - Akses random O(1): v[i] cepat" << endl;
    cout << "  - Lebih aman dari C array biasa" << endl;
    cout << "  - Kompatibel dengan semua STL algorithm" << endl;
}

// ============================================================================
// SECTION 2: std::string - String Manipulation
// ============================================================================
//
// std::string = padanan String di JavaScript.
// Syntax sedikit berbeda tapi konsep sama.
//
// Perbandingan:
//   JS "hello".length     → C++ s.length() atau s.size()
//   JS str1 + str2        → C++ s1 + s2  (sama!)
//   JS s.toUpperCase()    → C++ transform(s.begin(), s.end(), s.begin(), ::toupper)
//   JS s.indexOf("x")     → C++ s.find("x")
//   JS s.substring(0,5)   → C++ s.substr(0, 5)
//   JS parseInt("42")     → C++ stoi("42")
//   JS String(123)        → C++ to_string(123)

void section2_String() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: std::string - Text Manipulation" << endl;
    cout << "(Padanan: String di JavaScript)" << endl;
    cout << string(60, '=') << endl;

    string s1 = "Hello";
    string s2 = "World";

    cout << "\nString basics:" << endl;
    cout << "  s1 = \"" << s1 << "\"" << endl;
    cout << "  s1.length() = " << s1.length() << "  (= s.length di JS)" << endl;
    cout << "  s1[0] = '" << s1[0] << "'  (= s[0] di JS)" << endl;

    cout << "\nOperasi string:" << endl;

    string s3 = s1 + " " + s2;  // Concatenation - SAMA dengan JS!
    cout << "  s1 + \" \" + s2 = \"" << s3 << "\"" << endl;

    string s4 = s1;
    transform(s4.begin(), s4.end(), s4.begin(), ::toupper);
    cout << "  Uppercase: \"" << s4 << "\"  (di JS: s.toUpperCase())" << endl;

    size_t pos = s3.find("World");
    cout << "  s3.find(\"World\") = " << pos << "  (di JS: s.indexOf(\"World\"))" << endl;

    string s5 = s3.substr(0, 5);
    cout << "  s3.substr(0, 5) = \"" << s5 << "\"  (di JS: s.substring(0,5))" << endl;

    int val = stoi("42");       // String to integer - di JS: parseInt("42")
    string s7 = to_string(123); // Integer to string - di JS: String(123)
    cout << "  stoi(\"42\") = " << val << "  (di JS: parseInt(\"42\"))" << endl;
    cout << "  to_string(123) = \"" << s7 << "\"  (di JS: String(123))" << endl;

    cout << "\nKenapa std::string > char array:" << endl;
    cout << "  - Memory management otomatis" << endl;
    cout << "  - Concatenation aman dengan +" << endl;
    cout << "  - Banyak built-in method" << endl;
    cout << "  - Tidak ada buffer overflow seperti char[]" << endl;
}

// ============================================================================
// SECTION 3: Iterators - Cara Traversal Container
// ============================================================================
//
// Iterator = cara generik untuk mengakses elemen container, seperti pointer
//
// Di JS, kamu biasa pakai:
//   for (const val of arr) { ... }
//   arr.forEach(val => ...)
//
// Di C++, ada beberapa cara:
//   - Iterator eksplisit (verbose, jarang dipakai langsung)
//   - Range-based for loop (REKOMENDASI, mirip for...of di JS)
//   - Index-based for (klasik)

void section3_Iterators() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: Iterators - Traversal Container" << endl;
    cout << string(60, '=') << endl;

    vector<int> v = {10, 20, 30, 40, 50};

    cout << "\nCara traversal vector (pilih yang paling sesuai):" << endl;

    // Cara 1: Index (seperti for(let i = 0; i < arr.length; i++) di JS)
    cout << "\n[1] Index-based for (klasik):" << endl;
    for (size_t i = 0; i < v.size(); i++) {
        cout << "  v[" << i << "] = " << v[i] << endl;
    }

    // Cara 2: Range-based for (PALING DIREKOMENDASIKAN - seperti for...of di JS)
    cout << "\n[2] Range-based for (REKOMENDASI, = for...of di JS):" << endl;
    cout << "  for (int val : v) { ... }" << endl;
    for (int val : v) {
        cout << "  " << val << endl;
    }

    // Cara 3: Iterator eksplisit (verbose, dibutuhkan untuk algoritma STL)
    cout << "\n[3] Iterator eksplisit (dipakai dengan STL algorithms):" << endl;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << "  *it = " << *it << endl;
    }

    // Cara 4: auto iterator (lebih clean dari cara 3)
    cout << "\n[4] Auto iterator (versi lebih bersih dari cara 3):" << endl;
    auto it = v.begin();
    cout << "  begin() = " << *it << endl;
    ++it;
    cout << "  Setelah ++it: " << *it << endl;
    it += 2;
    cout << "  Setelah it += 2: " << *it << endl;

    cout << "\nRekomendasi: pakai range-based for untuk kebanyakan kasus" << endl;
    cout << "Pakai iterator eksplisit kalau butuh posisi atau STL algorithm" << endl;
}

// ============================================================================
// SECTION 4: std::map - Key-Value Pairs
// ============================================================================
//
// std::map = padanan Map atau Object di JavaScript
//
// Perbandingan:
//   JS:   let m = new Map();           C++: map<string,int> m;
//   JS:   m.set("Alice", 30)           C++: m["Alice"] = 30;
//   JS:   m.get("Alice")               C++: m["Alice"]
//   JS:   m.has("Alice")               C++: m.find("Alice") != m.end()
//   JS:   m.delete("Bob")              C++: m.erase("Bob")
//   JS:   m.size                       C++: m.size()
//   JS:   for (const [k,v] of m) {}    C++: for (auto& [k,v] : m) {} // C++17
//
// PERBEDAAN penting:
//   - std::map selalu SORTED by key (tidak seperti Map JS)
//   - Untuk behavior seperti Map JS (tidak sorted), pakai unordered_map
//   - Key dan Value harus tipe yang sama di seluruh map

void section4_Map() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: std::map - Key-Value Dictionary" << endl;
    cout << "(Padanan: Map atau Object di JavaScript)" << endl;
    cout << string(60, '=') << endl;

    map<string, int> ages;  // Key: string, Value: int

    cout << "\nMenambah key-value pairs:" << endl;
    ages["Alice"] = 30;   // = m.set("Alice", 30) di JS
    ages["Bob"] = 25;
    ages["Charlie"] = 35;

    cout << "  ages[\"Alice\"] = " << ages["Alice"] << "  (= m.get(\"Alice\") di JS)" << endl;
    cout << "  ages[\"Bob\"] = " << ages["Bob"] << endl;

    cout << "\nIterasi map (otomatis tersort by key):" << endl;
    cout << "(Di JS: Map tidak sorted, tapi C++ map selalu sorted)" << endl;
    for (auto& [name, age] : ages) {  // C++17 structured bindings, mirip for...of di JS!
        cout << "  " << name << ": " << age << " tahun" << endl;
    }

    cout << "\nOperasi map:" << endl;
    cout << "  size = " << ages.size() << endl;

    // Cek apakah key ada - di JS: m.has("Alice")
    if (ages.find("Alice") != ages.end()) {
        cout << "  Alice ada di map  (= m.has(\"Alice\") di JS)" << endl;
    }

    ages.erase("Bob");   // = m.delete("Bob") di JS
    cout << "  Setelah erase(\"Bob\"): size = " << ages.size() << endl;

    cout << "\nPilih container yang tepat:" << endl;
    cout << "  map<K,V>             -> sorted, O(log n) lookup, = sorted Map di TS" << endl;
    cout << "  unordered_map<K,V>   -> tidak sorted, O(1) avg lookup, = Map di JS" << endl;
}

// ============================================================================
// SECTION 5: STL Algorithms
// ============================================================================
//
// STL menyediakan banyak algorithm yang bisa dipakai dengan semua container.
//
// Analogi dengan Array methods di JS:
//   JS: arr.sort()               → C++: sort(v.begin(), v.end())
//   JS: arr.find(x => x > 5)     → C++: find_if(v.begin(), v.end(), [](int x){ return x>5; })
//   JS: arr.indexOf(20)          → C++: find(v.begin(), v.end(), 20)
//   JS: arr.filter(x => x > 5)   → C++: copy_if(...) atau manual loop
//   JS: arr.map(x => x * 2)      → C++: transform(...)
//   JS: arr.reverse()            → C++: reverse(v.begin(), v.end())
//   JS: arr.reduce((a,b) => a+b) → C++: accumulate(v.begin(), v.end(), 0)

void section5_Algorithms() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: STL Algorithms" << endl;
    cout << "(Mirip Array methods di JavaScript!)" << endl;
    cout << string(60, '=') << endl;

    vector<int> v = {30, 10, 40, 20, 50, 5, 15};

    cout << "\nOriginal: [";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i < v.size()-1 ? ", " : "");
    cout << "]" << endl;

    // Sort - seperti arr.sort() di JS
    sort(v.begin(), v.end());
    cout << "\nSetelah sort() (= arr.sort() di JS):" << endl;
    cout << "  [";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i < v.size()-1 ? ", " : "");
    cout << "]" << endl;

    // Find - seperti arr.indexOf(20) di JS
    auto it = find(v.begin(), v.end(), 20);
    if (it != v.end()) {
        cout << "\nfind(20) ada di posisi: " << (it - v.begin())
             << "  (= arr.indexOf(20) di JS)" << endl;
    }

    // Count
    int count20 = std::count(v.begin(), v.end(), 20);
    cout << "\nCount nilai 20: " << count20 << endl;

    // Transform - seperti arr.map(x => x * 2) di JS
    vector<int> doubled;
    transform(v.begin(), v.end(), back_inserter(doubled),
              [](int x) { return x * 2; });  // Lambda = arrow function!
    cout << "\nTransform *2 (= arr.map(x => x*2) di JS):" << endl;
    cout << "  [";
    for (size_t i = 0; i < doubled.size(); i++) cout << doubled[i] << (i < doubled.size()-1 ? ", " : "");
    cout << "]" << endl;

    // Reverse - seperti arr.reverse() di JS
    reverse(v.begin(), v.end());
    cout << "\nSetelah reverse() (= arr.reverse() di JS):" << endl;
    cout << "  [";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i < v.size()-1 ? ", " : "");
    cout << "]" << endl;

    cout << "\nAlgorithm STL yang sering dipakai:" << endl;
    cout << "  sort, stable_sort        -> arr.sort()" << endl;
    cout << "  find, find_if            -> arr.indexOf(), arr.find()" << endl;
    cout << "  count, count_if          -> arr.filter().length" << endl;
    cout << "  transform                -> arr.map()" << endl;
    cout << "  copy_if                  -> arr.filter()" << endl;
    cout << "  accumulate               -> arr.reduce()" << endl;
    cout << "  reverse                  -> arr.reverse()" << endl;
    cout << "  min_element, max_element -> Math.min/max di JS" << endl;
}

// ============================================================================
// SECTION 6: Real-World Example - Student Record System
// ============================================================================

struct Student {
    string name;
    int id;
    double gpa;

    Student(const string& n, int i, double g)
        : name(n), id(i), gpa(g) {}
};

void section6_RealWorldExample() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Real-World - Student Record System" << endl;
    cout << string(60, '=') << endl;

    vector<Student> students;
    students.emplace_back("Alice", 101, 3.8);    // emplace_back = push langsung
    students.emplace_back("Bob", 102, 3.5);
    students.emplace_back("Charlie", 103, 3.9);
    students.emplace_back("Diana", 104, 3.7);
    students.emplace_back("Eve", 105, 3.6);

    cout << "\nData students:" << endl;
    for (const auto& s : students) {  // const auto& = tidak mau ubah, tidak mau copy
        cout << "  " << setw(10) << s.name
             << " ID: " << s.id
             << " GPA: " << fixed << setprecision(2) << s.gpa << endl;
    }

    // Sort by GPA descending - pakai lambda (= arrow function di JS)
    cout << "\nSort by GPA descending (sort dengan comparator, mirip JS arr.sort((a,b) => b.gpa - a.gpa)):" << endl;
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.gpa > b.gpa;  // Lambda = arrow function di JS!
         });

    for (const auto& s : students) {
        cout << "  " << setw(10) << s.name
             << " GPA: " << fixed << setprecision(2) << s.gpa << endl;
    }

    // Filter GPA > 3.7 - seperti arr.filter(s => s.gpa > 3.7) di JS
    cout << "\nFilter GPA > 3.7 (seperti arr.filter() di JS):" << endl;
    for (const auto& s : students) {
        if (s.gpa > 3.7) {
            cout << "  " << s.name << " (" << fixed << setprecision(2)
                 << s.gpa << ")" << endl;
        }
    }

    // Calculate average - seperti arr.reduce((sum, s) => sum + s.gpa, 0) / arr.length di JS
    double totalGPA = 0;
    for (const auto& s : students) totalGPA += s.gpa;
    double avgGPA = totalGPA / students.size();
    cout << "\nRata-rata GPA: " << fixed << setprecision(2) << avgGPA << endl;

    // Map for quick lookup by ID
    cout << "\nBuat map untuk lookup cepat by ID:" << endl;
    map<int, Student*> byId;
    for (auto& s : students) {
        byId[s.id] = &s;
    }

    int searchId = 103;
    if (byId.find(searchId) != byId.end()) {
        cout << "  ID " << searchId << " adalah " << byId[searchId]->name << endl;
    }
}

// ============================================================================
// SECTION 7: Lambda Functions
// ============================================================================
//
// Lambda di C++ = Arrow function di JavaScript!
//
// JS:   (x) => x * 2
// C++:  [](int x) { return x * 2; }
//
// Syntax breakdown:
//   []     = capture list (lihat bawah)
//   (int x)= parameter
//   { }    = body function
//
// Capture list (TIDAK ADA di JS - karena JS punya closure otomatis):
//   []      = tidak capture apapun dari outer scope
//   [=]     = capture semua variabel outer by VALUE (copy)
//   [&]     = capture semua variabel outer by REFERENCE
//   [x]     = capture variabel x saja by value
//   [&x]    = capture variabel x saja by reference

void section7_Lambdas() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: Lambda Functions" << endl;
    cout << "(Padanan: Arrow Functions di JavaScript!)" << endl;
    cout << string(60, '=') << endl;

    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "\nSyntax lambda:" << endl;
    cout << "  JS:  (x) => x * 2" << endl;
    cout << "  C++: [](int x) { return x * 2; }" << endl;

    // Lambda sederhana
    cout << "\nLambda sederhana:" << endl;
    auto printVal = [](int x) { cout << x << " "; };  // Seperti (x) => print(x)
    cout << "  Nilai: ";
    for (int x : v) printVal(x);
    cout << endl;

    // Lambda dengan capture - akses variabel dari luar
    // Di JS, closure otomatis. Di C++, harus eksplisit.
    cout << "\nLambda dengan capture (= closure di JS tapi eksplisit):" << endl;
    int threshold = 6;
    auto aboveThreshold = [threshold](int x) {   // [threshold] = capture by value
        return x > threshold;
    };
    cout << "  Angka > " << threshold << ": ";
    for (int x : v) {
        if (aboveThreshold(x)) cout << x << " ";
    }
    cout << endl;

    // Lambda dengan reference capture - bisa modify outer variable
    cout << "\nLambda dengan reference capture [&] (= closure di JS):" << endl;
    int sum = 0;
    for_each(v.begin(), v.end(), [&sum](int x) { sum += x; });
    cout << "  Sum semua elemen: " << sum << endl;

    // Pakai lambda dengan algorithm
    cout << "\nLambda dengan STL algorithm (sort descending):" << endl;
    cout << "  JS:  arr.sort((a, b) => b - a)" << endl;
    cout << "  C++: sort(v.begin(), v.end(), [](int a, int b) { return a > b; })" << endl;
    sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    cout << "  Hasil: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    cout << "\nCapture list (konsep ini tidak ada di JS - JS closure otomatis):" << endl;
    cout << "  []      = tidak capture (tidak bisa akses variabel luar)" << endl;
    cout << "  [=]     = capture semua by value (copy)" << endl;
    cout << "  [&]     = capture semua by reference (seperti closure JS)" << endl;
    cout << "  [x]     = capture x saja by value" << endl;
    cout << "  [&x]    = capture x saja by reference" << endl;
}

// ============================================================================
// SECTION 8: Kesalahan Umum STL
// ============================================================================

void section8_CommonMistakes() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 8: Kesalahan Umum STL" << endl;
    cout << string(60, '=') << endl;

    cout << "\n[KESALAHAN 1] Akses out-of-bounds:" << endl;
    vector<int> v = {1, 2, 3};
    cout << "  v[5] = UNDEFINED BEHAVIOR (tidak crash tapi nilai acak!)" << endl;
    cout << "  FIX: pakai v.at(5) yang throw exception jika out of bounds" << endl;
    cout << "  Di JS: arr[5] = undefined (lebih aman)" << endl;
    cout << "  Di C++: v[5] = memory sampah atau crash!" << endl;

    cout << "\n[KESALAHAN 2] Iterator invalidation:" << endl;
    cout << "  Jangan erase/insert sambil iterasi:" << endl;
    cout << "  for (auto it = v.begin(); it != v.end(); ++it) {" << endl;
    cout << "    v.erase(it);  // CRASH! it sudah invalid setelah erase" << endl;
    cout << "  }" << endl;

    cout << "\n[KESALAHAN 3] std::map - akses key tidak ada membuat key baru!" << endl;
    map<string, int> m;
    int val = m["nonexistent"];  // Ini MEMBUAT key baru dengan value 0!
    cout << "  m[\"nonexistent\"] = " << val << " (key baru dibuat dengan value 0!)" << endl;
    cout << "  FIX: cek dulu dengan m.find() sebelum akses" << endl;
    cout << "  Di JS: m.get(\"nonexistent\") = undefined (tidak buat key baru)" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "STL - STANDARD TEMPLATE LIBRARY" << endl;
    cout << "Containers, Iterators, Algorithms" << endl;
    cout << "(Banyak yang mirip dengan built-in JS/TS!)" << endl;
    cout << string(60, '*') << endl;

    section1_Vector();
    section2_String();
    section3_Iterators();
    section4_Map();
    section5_Algorithms();
    section6_RealWorldExample();
    section7_Lambdas();
    section8_CommonMistakes();

    cout << "\n" << string(60, '=') << endl;
    cout << "RINGKASAN" << endl;
    cout << string(60, '=') << endl;
    cout << "\nPadanan JS/TS -> C++ STL:" << endl;
    cout << "  Array         -> vector<T>" << endl;
    cout << "  Map           -> unordered_map<K,V> atau map<K,V>" << endl;
    cout << "  Set           -> set<T>" << endl;
    cout << "  String        -> string" << endl;
    cout << "  Arrow function-> Lambda [](params) { body }" << endl;
    cout << "  for...of      -> for (auto& val : container)" << endl;
    cout << "  arr.map()     -> transform()" << endl;
    cout << "  arr.filter()  -> copy_if() atau manual loop" << endl;
    cout << "  arr.reduce()  -> accumulate()" << endl;
    cout << "\nBedanya dari JS:" << endl;
    cout << "  - Strongly typed: harus tentukan tipe (vector<int>, tidak bisa campur)" << endl;
    cout << "  - std::map selalu sorted, pakai unordered_map untuk behavior seperti JS Map" << endl;
    cout << "  - Lambda perlu capture list (tidak otomatis closure seperti JS)" << endl;
    cout << "\nNext: File I/O untuk baca/tulis data!" << endl;
    cout << string(60, '*') << endl << endl;

    return 0;
}
