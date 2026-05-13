/**
 * PROJECT 0 - Program 01: Memory Management Fundamentals
 *
 * Topik:
 * 1. Stack vs Heap allocation
 * 2. Pointers dan dereferencing
 * 3. References
 * 4. Dynamic memory dengan new/delete
 * 5. Kesalahan umum memory management
 * 6. Smart pointers (solusi modern C++)
 *
 * Build: cd build && cmake .. && make 01_memory
 * Run:   ./build/bin/01_memory
 */

/**
 * ============================================================
 * UNTUK DEVELOPER JS/TS - BACA DULU!
 * ============================================================
 *
 * Di JavaScript/TypeScript, kamu TIDAK PERNAH memikirkan memory.
 * Garbage Collector (GC) bekerja di belakang layar:
 *   - Allocate otomatis saat buat variabel/object
 *   - Free otomatis saat sudah tidak ada yang pakai
 *
 * Contoh JS - kamu tidak peduli memory:
 *   let user = { name: "Alice" };   // GC alokasi otomatis
 *   user = null;                     // GC bebas memory kapanpun
 *
 * Di C++, KAMU yang bertanggung jawab:
 *   - Allocate dengan: new
 *   - Free dengan: delete (WAJIB dilakukan manual!)
 *   - Lupa delete = MEMORY LEAK (memori bocor, program lambat/crash)
 *
 * Kenapa C++ begini? Karena C++ dipakai untuk software yang butuh:
 *   - Kontrol penuh atas performa (game engine, ECDIS, embedded)
 *   - Tidak ada overhead dari GC
 *   - Predictable timing (GC bisa pause program kapanpun)
 *
 * Tapi tenang - Modern C++ punya "smart pointers" yang mirip GC!
 * ============================================================
 */

#include <iostream>
#include <iomanip>
#include <memory>
using namespace std;

// ============================================================================
// SECTION 1: Stack vs Heap
// ============================================================================
//
// STACK = memori yang dikelola OTOMATIS oleh compiler
//   - Variabel lokal tinggal di stack
//   - Hilang otomatis saat function selesai
//   - Analogi JS: variabel lokal di dalam function
//
// HEAP = memori yang dikelola MANUAL oleh programmer
//   - Dibuat dengan `new`, harus dihapus dengan `delete`
//   - Bisa hidup lebih lama dari function yang membuatnya
//   - Analogi JS: object yang kamu buat dengan `new` - tapi tanpa GC!

void section1_StackVsHeap() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: Stack vs Heap Allocation" << endl;
    cout << string(60, '=') << endl;

    // --- STACK ---
    // Seperti `let x = 42` di JS, tapi lokasi memorinya lebih efisien
    int stackVar = 42;
    double stackArray[5] = {1.1, 2.2, 3.3, 4.4, 5.5};

    cout << "\n[STACK] stackVar = " << stackVar << endl;
    cout << "[STACK] Alamat stackVar di memori: " << &stackVar << endl;
    cout << "[STACK] stackArray[0] = " << stackArray[0] << endl;
    cout << "[STACK] -> Otomatis dihapus saat function ini selesai" << endl;

    // --- HEAP ---
    // `new int(42)` = alokasi manual di heap
    // Analogi JS: seperti `new Number(42)` tapi TANPA garbage collector
    // Bedanya: kamu WAJIB panggil delete sendiri!
    int* heapVar = new int(42);
    double* heapArray = new double[5]{1.1, 2.2, 3.3, 4.4, 5.5};

    cout << "\n[HEAP] Nilai *heapVar = " << *heapVar << endl;
    cout << "[HEAP] Alamat yang disimpan pointer heapVar = " << heapVar << endl;
    cout << "[HEAP] Alamat pointer heapVar sendiri = " << &heapVar << endl;
    cout << "[HEAP] heapArray[0] = " << heapArray[0] << endl;
    cout << "[HEAP] -> TIDAK otomatis dihapus! Harus panggil delete manual" << endl;

    // WAJIB: Hapus memori heap setelah selesai
    delete heapVar;      // Hapus single value
    delete[] heapArray;  // Hapus array (pakai [] untuk array!)

    cout << "\n[CLEANUP] delete heapVar dan delete[] heapArray dipanggil" << endl;
    cout << "[CLEANUP] heapVar & heapArray sekarang 'dangling pointer' - jangan dipakai!" << endl;
}

// ============================================================================
// SECTION 2: Pointers - Konsep PALING BERBEDA dari JS
// ============================================================================
//
// Pointer = variabel yang menyimpan ALAMAT MEMORI (bukan nilai itu sendiri)
//
// Analogi (tidak sempurna tapi membantu):
//   Di JS:    let x = 42;              // x holds the value 42
//   Di C++:   int x = 42;
//             int* ptr = &x;           // ptr menyimpan ALAMAT x di memori
//
// Operator penting:
//   & (address-of)  = "berikan alamat memori dari variabel ini"
//   * (dereference) = "pergi ke alamat itu, ambil nilainya"

void section2_PointersBasics() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: Pointers - & (alamat) dan * (nilai di alamat)" << endl;
    cout << string(60, '=') << endl;

    int x = 100;
    int* ptr = &x;  // ptr menyimpan ALAMAT x, bukan nilai x

    cout << "\n--- Variabel x ---" << endl;
    cout << "  Nilai x:       " << x << endl;
    cout << "  Alamat x (&x): " << &x << " (ini yang disimpan ptr)" << endl;

    cout << "\n--- Pointer ptr = &x ---" << endl;
    cout << "  ptr (isi pointer = alamat): " << ptr << endl;
    cout << "  *ptr (nilai DI alamat itu): " << *ptr << endl;
    cout << "  &ptr (alamat pointer itu sendiri): " << &ptr << endl;

    // Modifikasi melalui pointer = seperti mutate object via reference di JS
    *ptr = 200;  // Ubah nilai x melalui pointer
    cout << "\nSetelah *ptr = 200:" << endl;
    cout << "  x = " << x << " (berubah via pointer!)" << endl;

    // Beberapa pointer ke variabel yang sama
    int* ptr2 = &x;
    cout << "\nDua pointer ke variabel yang sama:" << endl;
    cout << "  *ptr = " << *ptr << ", *ptr2 = " << *ptr2 << " (keduanya ke x)" << endl;

    *ptr2 = 500;
    cout << "  Setelah *ptr2 = 500, x = " << x << " (semua pointer lihat perubahan)" << endl;
}

// ============================================================================
// SECTION 3: References - Cara yang Lebih Aman dari Pointer
// ============================================================================
//
// Reference = ALIAS untuk variabel yang sudah ada
//
// Mirip dengan bagaimana object di JS di-pass by reference:
//   JS:   function edit(obj) { obj.name = "Bob"; }  // obj adalah alias ke object asli
//   C++:  void edit(string& name) { name = "Bob"; } // & = reference parameter
//
// Bedanya dengan pointer:
//   - Reference tidak bisa null
//   - Reference tidak bisa di-reassign ke variabel lain
//   - Syntax lebih bersih (tidak perlu * atau &)

void section3_References() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: References - Alias yang Lebih Aman" << endl;
    cout << string(60, '=') << endl;

    int original = 42;
    int& ref = original;  // ref = ALIAS untuk original (bukan copy!)

    cout << "\nint original = 42;" << endl;
    cout << "int& ref = original;  // ref adalah alias, bukan copy" << endl;
    cout << "\n  original = " << original << endl;
    cout << "  ref = " << ref << endl;
    cout << "  &original = " << &original << " (alamat sama!)" << endl;
    cout << "  &ref = " << &ref << " (sama persis dengan &original)" << endl;

    // Mengubah ref = mengubah original
    ref = 99;
    cout << "\nSetelah ref = 99:" << endl;
    cout << "  original = " << original << " (ikut berubah!)" << endl;

    cout << "\n--- Pointer vs Reference ---" << endl;
    cout << "  Pointer: bisa null, bisa reassign, syntax: int* ptr / *ptr" << endl;
    cout << "  Reference: tidak bisa null, lebih aman, syntax: int& ref / ref" << endl;
    cout << "\n  Rekomendasi modern C++: PAKAI reference kecuali butuh pointer" << endl;
}

// ============================================================================
// SECTION 4: Pointer Arithmetic - Navigasi Array via Pointer
// ============================================================================
//
// Di C++, nama array sebenarnya adalah pointer ke elemen pertama.
// Kamu bisa "melompat" ke elemen berikutnya dengan ptr++
//
// Analogi JS:
//   JS: arr[0], arr[1], arr[2]  - akses langsung dengan index
//   C++: ptr, ptr+1, ptr+2      - sama, tapi lewat pointer arithmetic

void section4_PointerArithmetic() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: Pointer Arithmetic & Array" << endl;
    cout << string(60, '=') << endl;

    int arr[5] = {10, 20, 30, 40, 50};
    int* ptr = arr;  // Nama array = pointer ke elemen pertama

    cout << "\nint arr[5] = {10, 20, 30, 40, 50};" << endl;
    cout << "int* ptr = arr;  // ptr menunjuk ke arr[0]" << endl;

    cout << "\nDua cara akses yang SAMA:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  arr[" << i << "] = " << arr[i]
             << "  |  *(ptr+" << i << ") = " << *(ptr + i) << endl;
    }

    cout << "\nAlamat setiap elemen (berurutan, jarak = sizeof(int) = 4 byte):" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  &arr[" << i << "] = " << &arr[i] << endl;
    }
}

// ============================================================================
// SECTION 5: Function Parameters - Pointer vs Reference vs Value
// ============================================================================
//
// Ini SANGAT PENTING dan sering bikin bingung developer JS!
//
// Di JS semua primitif (number, string, bool) di-pass by VALUE:
//   function add(x) { x += 10; }  // tidak mengubah variabel asli
//   let n = 5; add(n); console.log(n); // masih 5
//
// Object di JS di-pass by reference (sort of):
//   function edit(obj) { obj.name = "Bob"; }  // mengubah object asli
//
// Di C++ kamu bisa PILIH secara eksplisit:

void incrementByPointer(int* ptr, int amount) {
    *ptr += amount;  // Modifikasi via pointer - ubah nilai di alamat itu
}

void incrementByReference(int& ref, int amount) {
    ref += amount;   // Modifikasi via reference - lebih clean, sama efeknya
}

void incrementByValue(int val, int amount) {
    val += amount;   // Hanya ubah COPY lokal - tidak pengaruh variabel asli
    // Seperti parameter function di JS dengan primitive type
}

void section5_FunctionParameters() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: Pass by Pointer vs Reference vs Value" << endl;
    cout << string(60, '=') << endl;

    int x = 100, y = 100, z = 100;

    cout << "\nNilai awal: x=100, y=100, z=100" << endl;

    incrementByPointer(&x, 50);    // Kirim ALAMAT x
    incrementByReference(y, 50);   // Kirim REFERENCE ke y
    incrementByValue(z, 50);       // Kirim COPY dari z

    cout << "\nSetelah increment by 50:" << endl;
    cout << "  x (by pointer)   = " << x << " -> BERUBAH" << endl;
    cout << "  y (by reference) = " << y << " -> BERUBAH" << endl;
    cout << "  z (by value)     = " << z << " -> TIDAK berubah (hanya copy)" << endl;

    cout << "\nKapan pakai apa:" << endl;
    cout << "  - By value:     Data kecil (int, double), function tidak perlu mengubah" << endl;
    cout << "  - By reference: Modern C++, syntax bersih, dijamin tidak null" << endl;
    cout << "  - By pointer:   Legacy code, perlu check null, parameter optional" << endl;
}

// ============================================================================
// SECTION 6: Dynamic Arrays - Array dengan Ukuran Dinamis
// ============================================================================
//
// Di JS, array bisa tumbuh otomatis: arr.push(value)
// Di C++ (raw array), ukuran harus diketahui saat compile time.
//
// Tapi dengan `new int[n]`, kamu bisa buat array ukuran dinamis di HEAP.
// Bedanya: harus delete[] sendiri!
//
// Solusi lebih baik: pakai std::vector (dibahas di file 03)

void section6_DynamicArrays() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Dynamic Arrays di Heap" << endl;
    cout << string(60, '=') << endl;

    int n = 5;

    // Buat array ukuran n di heap
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;  // 10, 20, 30, 40, 50
    }

    cout << "\nnew int[" << n << "] dibuat di heap:" << endl;
    cout << "  Isi: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    // WAJIB: delete[] untuk array (BUKAN delete biasa!)
    delete[] arr;

    cout << "\ndelete[] arr dipanggil - memori dikembalikan" << endl;
    cout << "  PENTING: pakai delete[] (dengan []) untuk array!" << endl;
    cout << "  Pakai delete (tanpa []) untuk single value" << endl;
    cout << "\nTip: Di kode modern, lebih baik pakai std::vector" << endl;
    cout << "  std::vector otomatis resize & cleanup sendiri!" << endl;
}

// ============================================================================
// SECTION 7: Kesalahan Umum Memory Management
// ============================================================================
//
// Di JS, GC melindungimu dari semua ini.
// Di C++, semua ini bisa terjadi dan bikin bug yang sulit dilacak!

void section7_MemoryMistakes() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: Kesalahan Umum Memory (Jangan Dilakukan!)" << endl;
    cout << string(60, '=') << endl;

    cout << "\n[KESALAHAN 1] Memory Leak - Alokasi tapi lupa delete:" << endl;
    cout << "  int* leaked = new int(42);" << endl;
    cout << "  // Lupa delete -> memori tidak pernah dibebaskan!" << endl;
    cout << "  // Kalau terjadi berulang kali -> program makin lama makin lambat/crash" << endl;
    {
        int* leaked = new int(42);
        delete leaked;  // Kita cleanup untuk demo, di kode buruk baris ini tidak ada
    }

    cout << "\n[KESALAHAN 2] Dangling Pointer - Pakai pointer setelah delete:" << endl;
    cout << "  int* ptr = new int(42);" << endl;
    cout << "  delete ptr;           // ptr sudah tidak valid!" << endl;
    cout << "  cout << *ptr;         // UNDEFINED BEHAVIOR - bisa crash, bisa nilai acak!" << endl;
    {
        int* ptr = new int(42);
        delete ptr;
        ptr = nullptr;  // Solusi: set ke nullptr setelah delete
    }

    cout << "\n[KESALAHAN 3] Double Delete - Delete pointer yang sudah didelete:" << endl;
    cout << "  int* ptr = new int(42);" << endl;
    cout << "  delete ptr;" << endl;
    cout << "  delete ptr;  // CRASH! Menghapus memori yang sudah dibebaskan" << endl;

    cout << "\n[KESALAHAN 4] Delete vs Delete[] - Salah pilih operator:" << endl;
    cout << "  int* arr = new int[5];" << endl;
    cout << "  delete arr;   // SALAH! Undefined behavior" << endl;
    cout << "  delete[] arr; // BENAR untuk array" << endl;
    {
        int* arr = new int[5];
        delete[] arr;  // Yang benar
    }

    cout << "\nSOLUSI Modern C++: Pakai smart pointers!" << endl;
    cout << "  Mereka handle semua ini otomatis, tidak bisa double delete, dll." << endl;
}

// ============================================================================
// SECTION 8: Smart Pointers - Solusi Modern C++ (Mirip GC di JS)
// ============================================================================
//
// Smart pointers = wrapper yang otomatis memanggil delete saat sudah tidak dipakai
//
// Mirip seperti GC di JS! Tapi lebih predictable:
//   - unique_ptr: dihapus saat keluar dari scope (RAII)
//   - shared_ptr: dihapus saat tidak ada lagi yang memakai (reference counting)
//
// Analogi:
//   unique_ptr ≈ variable lokal biasa di JS (hilang saat function selesai)
//   shared_ptr ≈ GC di JS (dihapus saat reference count = 0)
//
// DI KODE MODERN C++: SELALU pakai smart pointers, hindari raw new/delete!

void section8_SmartPointers() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 8: Smart Pointers - Modern C++ (C++11+)" << endl;
    cout << string(60, '=') << endl;

    // --- unique_ptr: Satu pemilik, auto-delete saat keluar scope ---
    cout << "\nstd::unique_ptr (kepemilikan eksklusif):" << endl;
    {
        auto uptr = make_unique<int>(42);  // Prefer make_unique<> daripada new
        cout << "  Dibuat: make_unique<int>(42)" << endl;
        cout << "  Nilai: *uptr = " << *uptr << endl;
        cout << "  Alamat: uptr.get() = " << uptr.get() << endl;
        // Tidak perlu delete! Auto-delete saat uptr keluar dari {} ini
    }
    cout << "  -> Auto-dihapus saat keluar scope (tidak perlu delete!)" << endl;

    // --- shared_ptr: Banyak pemilik, delete saat semua selesai ---
    cout << "\nstd::shared_ptr (kepemilikan bersama):" << endl;
    {
        auto sptr1 = make_shared<int>(99);
        auto sptr2 = sptr1;  // Dua-duanya "milik" data yang sama

        cout << "  sptr1 dan sptr2 keduanya menunjuk ke int(99)" << endl;
        cout << "  sptr1.use_count() = " << sptr1.use_count() << " (ada 2 yang pakai)" << endl;
        cout << "  *sptr1 = " << *sptr1 << ", *sptr2 = " << *sptr2 << endl;
        // Data dihapus saat sptr1 DAN sptr2 keduanya keluar scope
    }
    cout << "  -> Auto-dihapus saat semua shared_ptr sudah tidak dipakai" << endl;

    cout << "\nKeuntungan smart pointers:" << endl;
    cout << "  - Tidak perlu manual delete (seperti GC!)" << endl;
    cout << "  - Aman dari exception (tetap cleanup walau ada throw)" << endl;
    cout << "  - Lebih sulit membuat memory mistakes" << endl;
    cout << "  - Kepemilikan jelas (unique = 1 owner, shared = banyak owner)" << endl;
}

// ============================================================================
// MAIN - Jalankan semua section
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "C++ MEMORY MANAGEMENT FUNDAMENTALS" << endl;
    cout << "(Untuk JS/TS Developer - Ini yang paling beda dari JS!)" << endl;
    cout << string(60, '*') << endl;

    section1_StackVsHeap();
    section2_PointersBasics();
    section3_References();
    section4_PointerArithmetic();
    section5_FunctionParameters();
    section6_DynamicArrays();
    section7_MemoryMistakes();
    section8_SmartPointers();

    cout << "\n" << string(60, '=') << endl;
    cout << "RINGKASAN" << endl;
    cout << string(60, '=') << endl;
    cout << "\nKey Takeaways untuk JS/TS Developer:" << endl;
    cout << "1. Stack: otomatis, cepat, scope terbatas (seperti var lokal JS)" << endl;
    cout << "2. Heap: fleksibel, manual, kamu yang tanggung jawab cleanup" << endl;
    cout << "3. Pointer (*): menyimpan ALAMAT, bukan nilai. Tidak ada di JS!" << endl;
    cout << "4. Reference (&): alias yang lebih aman dari pointer" << endl;
    cout << "5. Smart pointer: pakai ini! Mirip GC-nya JS tapi lebih predictable" << endl;
    cout << "\nBedanya dengan JS:" << endl;
    cout << "  JS: GC otomatis - enak tapi tidak ada kontrol" << endl;
    cout << "  C++: Manual/Smart ptr - lebih kerja tapi performa lebih baik" << endl;
    cout << "\nNext: OOP dengan classes dan inheritance!" << endl;
    cout << string(60, '*') << endl << endl;

    return 0;
}
