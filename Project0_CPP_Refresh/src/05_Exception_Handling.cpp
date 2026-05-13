/**
 * PROJECT 0 - Program 05: Exception Handling
 *
 * Topik:
 * 1. Try-catch blocks
 * 2. Throwing exceptions
 * 3. Standard exception hierarchy
 * 4. Custom exception classes
 * 5. Exception safety dan RAII pattern
 * 6. Best practices
 *
 * Build: cd build && cmake .. && make 05_exceptions
 * Run:   ./build/bin/05_exceptions
 */

/**
 * ============================================================
 * UNTUK DEVELOPER JS/TS - BACA DULU!
 * ============================================================
 *
 * KABAR BAIK: Exception handling di C++ SANGAT mirip dengan JS/TS!
 *
 * Padanan langsung:
 *   JavaScript/TypeScript:          C++:
 *   try {                           try {
 *     throw new Error("msg");         throw runtime_error("msg");
 *   }                               }
 *   catch (e) {                     catch (const runtime_error& e) {
 *     console.log(e.message);         cout << e.what();
 *   }                               }
 *   finally {                       // Tidak ada finally di C++!
 *     cleanup();                    // Pakai destructor atau RAII
 *   }
 *
 * PERBEDAAN dari JS/TS:
 *   1. Catch HARUS spesifikan tipe exception: catch (const std::exception& e)
 *      Di JS: catch (e) - catch semua tipe
 *
 *   2. Catch by REFERENCE: catch (const SomeError& e)
 *      Di JS: catch (e) - tidak ada pilihan
 *
 *   3. Tidak ada `finally` keyword di C++!
 *      Gantinya: destructor + RAII pattern (lebih elegant sebenarnya)
 *
 *   4. TypeScript bisa type exception: catch (e: Error) tidak benar-benar checked
 *      C++: benar-benar type safe, salah tipe = tidak ke-catch
 *
 *   5. e.message di JS  →  e.what() di C++
 * ============================================================
 */

#include <iostream>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <string>
using namespace std;

// ============================================================================
// SECTION 1: Basic Try-Catch
// ============================================================================
//
// Hampir identik dengan JS! Bedanya: harus tentukan tipe exception.

void section1_BasicTryCatch() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: Basic Try-Catch (Mirip JS!)" << endl;
    cout << string(60, '=') << endl;

    cout << "\nDi JS:" << endl;
    cout << "  try {" << endl;
    cout << "    throw new Error('Cannot divide by zero!');" << endl;
    cout << "  } catch (e) {" << endl;
    cout << "    console.log(e.message);" << endl;
    cout << "  }" << endl;

    cout << "\nDi C++ (hampir sama!):" << endl;
    cout << "  try {" << endl;
    cout << "    throw invalid_argument('Cannot divide by zero!');" << endl;
    cout << "  } catch (const invalid_argument& e) {  // Harus spesifikan tipe" << endl;
    cout << "    cout << e.what();" << endl;
    cout << "  }" << endl;

    cout << "\n--- Demo ---" << endl;
    try {
        int dividend = 10;
        int divisor = 0;

        if (divisor == 0) {
            throw invalid_argument("Tidak bisa dibagi dengan nol!");
            // Di JS: throw new Error("...")
        }

        int result = dividend / divisor;
        cout << "  Hasil: " << result << endl;
    }
    catch (const invalid_argument& e) {
        cout << "  Exception ditangkap: " << e.what() << endl;
        // e.what() = e.message di JavaScript
        cout << "  Program tetap jalan normal setelah catch" << endl;
    }
}

// ============================================================================
// SECTION 2: Multiple Catch Blocks
// ============================================================================
//
// Di JS, catch (e) menangkap semua tipe.
// Di C++, kamu bisa punya beberapa catch untuk tipe berbeda.
// Urutan penting: tangkap yang lebih spesifik dulu!

int safeDivide(int a, int b) {
    if (b == 0) {
        throw invalid_argument("Divisor tidak boleh nol");
    }
    return a / b;
}

string getString(int index) {
    if (index < 0 || index > 4) {
        throw out_of_range("Index di luar range valid (0-4)");
    }
    string arr[] = {"satu", "dua", "tiga", "empat", "lima"};
    return arr[index];
}

void section2_MultipleCatches() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: Multiple Catch Blocks" << endl;
    cout << string(60, '=') << endl;

    // Di JS: catch (e) { if (e instanceof RangeError) {...} }
    // Di C++: bisa langsung buat catch terpisah per tipe, lebih clean!

    cout << "\nTest division valid:" << endl;
    try {
        cout << "  10 / 2 = " << safeDivide(10, 2) << endl;
    }
    catch (const invalid_argument& e) {
        cout << "  Error: " << e.what() << endl;
    }

    cout << "\nTest division by zero:" << endl;
    try {
        cout << "  10 / 0 = " << safeDivide(10, 0) << endl;
    }
    catch (const invalid_argument& e) {
        cout << "  Tertangkap invalid_argument: " << e.what() << endl;
    }

    cout << "\nTest array access valid:" << endl;
    try {
        cout << "  Index 2: " << getString(2) << endl;
    }
    catch (const out_of_range& e) {
        cout << "  Error: " << e.what() << endl;
    }

    cout << "\nTest array access out of range:" << endl;
    try {
        cout << "  Index 10: " << getString(10) << endl;
    }
    catch (const out_of_range& e) {
        cout << "  Tertangkap out_of_range: " << e.what() << endl;
    }

    cout << "\nCatch base class exception (menangkap semua turunan):" << endl;
    cout << "(Di JS: catch (e) menangkap semuanya tanpa perlu hierarki)" << endl;
    try {
        safeDivide(5, 0);
    }
    catch (const exception& e) {
        cout << "  Tertangkap sebagai exception: " << e.what() << endl;
        cout << "  std::exception = catch-all untuk exception standard" << endl;
    }
}

// ============================================================================
// SECTION 3: Standard Exception Hierarchy
// ============================================================================
//
// Di JS, ada built-in Error types: Error, TypeError, RangeError, dll
// Di C++, ada hierarki std::exception yang mirip

void section3_ExceptionHierarchy() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: Exception Hierarchy" << endl;
    cout << string(60, '=') << endl;

    cout << "\nPadanan JS Error types → C++ exceptions:" << endl;
    cout << "\n  JS:                    C++:" << endl;
    cout << "  Error                  std::exception" << endl;
    cout << "  TypeError              std::invalid_argument" << endl;
    cout << "  RangeError             std::out_of_range" << endl;
    cout << "  (tidak ada padanan)    std::runtime_error" << endl;
    cout << "  (tidak ada padanan)    std::logic_error" << endl;

    cout << "\nHierarki C++ Exception:" << endl;
    cout << "\n  exception  (base semua)" << endl;
    cout << "    |" << endl;
    cout << "    +-- logic_error  (bug logika programmer)" << endl;
    cout << "    |     +-- invalid_argument  (parameter tidak valid)" << endl;
    cout << "    |     +-- out_of_range      (index/nilai di luar range)" << endl;
    cout << "    |     +-- length_error      (panjang tidak valid)" << endl;
    cout << "    |" << endl;
    cout << "    +-- runtime_error  (error saat runtime, tidak bisa diprediksi)" << endl;
    cout << "          +-- range_error" << endl;
    cout << "          +-- overflow_error" << endl;
    cout << "          +-- underflow_error" << endl;

    cout << "\nKapan pakai apa:" << endl;
    cout << "  invalid_argument -> input tidak valid (mirip TypeError di JS)" << endl;
    cout << "  out_of_range     -> index di luar batas (mirip RangeError di JS)" << endl;
    cout << "  runtime_error    -> error yang tidak bisa dihindari saat runtime" << endl;
    cout << "  logic_error      -> bug logika programmer" << endl;
}

// ============================================================================
// SECTION 4: Custom Exception Classes
// ============================================================================
//
// Di JS/TS:
//   class AppError extends Error {
//     constructor(message: string) { super(message); }
//   }
//
// Di C++:
//   class AppError : public exception {
//     string message;
//   public:
//     AppError(const string& msg) : message(msg) {}
//     const char* what() const noexcept override { return message.c_str(); }
//   };
//
// Sangat mirip! Extend dari exception, implement what() (= message di JS)

class FileException : public exception {
private:
    string message;

public:
    FileException(const string& msg) : message(msg) {}

    // what() = e.message di JavaScript
    // noexcept = garansi: method ini tidak akan throw exception
    const char* what() const noexcept override {
        return message.c_str();  // c_str() = konversi string ke char* (C-style string)
    }
};

class ValidationException : public exception {
private:
    string field;
    string reason;

public:
    ValidationException(const string& f, const string& r)
        : field(f), reason(r) {}

    const char* what() const noexcept override {
        static string msg;  // static agar tidak di-destroy saat return
        msg = "Validation error di field '" + field + "': " + reason;
        return msg.c_str();
    }
};

void section4_CustomExceptions() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: Custom Exception Classes" << endl;
    cout << "(Sama seperti class extends Error di JS/TS!)" << endl;
    cout << string(60, '=') << endl;

    cout << "\nDi TypeScript:" << endl;
    cout << "  class FileException extends Error { ... }" << endl;
    cout << "\nDi C++:" << endl;
    cout << "  class FileException : public exception { ... }" << endl;
    cout << "  // Bedanya: implement what() bukan set message" << endl;

    cout << "\n--- Demo FileException ---" << endl;
    try {
        throw FileException("Tidak bisa membuka config.json");
        // Di JS: throw new FileException("...")
    }
    catch (const FileException& e) {
        cout << "  Tertangkap: " << e.what() << endl;
        // e.what() = e.message di JS
    }

    cout << "\n--- Demo ValidationException ---" << endl;
    try {
        string email = "email_tanpa_at";
        if (email.find('@') == string::npos) {
            throw ValidationException("email", "Tidak ada @ symbol");
        }
    }
    catch (const ValidationException& e) {
        cout << "  Tertangkap: " << e.what() << endl;
    }

    cout << "\n--- Catch via base class ---" << endl;
    cout << "(Di JS: catch (e) -> kalau e instanceof FileException...)" << endl;
    try {
        throw FileException("File error umum");
    }
    catch (const exception& e) {
        cout << "  Tertangkap sebagai exception: " << e.what() << endl;
        cout << "  (Ini menangkap semua exception yang extends dari exception)" << endl;
    }
}

// ============================================================================
// SECTION 5: RAII Pattern - Pengganti `finally` di C++
// ============================================================================
//
// DI JS/TS, kamu pakai `finally` untuk cleanup:
//   try {
//     resource.open()
//   } finally {
//     resource.close()  // Pasti dijalankan walau ada exception
//   }
//
// DI C++, tidak ada `finally`!
// Gantinya pakai RAII: destructor OTOMATIS dipanggil saat keluar scope,
// BAHKAN jika keluar karena exception!
//
// Ini sebenarnya lebih elegant karena cleanup terjadi otomatis,
// tidak perlu ingat tulis finally.

class Resource {
private:
    int* buffer;
    string name;

public:
    Resource(const string& n, int size) : name(n) {
        cout << "    [ALOKASI] " << name << " (size=" << size << ")" << endl;
        buffer = new int[size];
    }

    ~Resource() {
        cout << "    [CLEANUP] " << name << " otomatis dibersihkan" << endl;
        delete[] buffer;
    }

    void doWork() {
        cout << "    [KERJA] " << name << " sedang bekerja..." << endl;
    }
};

void section5_RAIIPattern() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: RAII - Pengganti `finally` di C++" << endl;
    cout << string(60, '=') << endl;

    cout << "\nDi JS/TS kamu pakai finally:" << endl;
    cout << "  try { resource.open() }" << endl;
    cout << "  finally { resource.close() }  // selalu dijalankan" << endl;

    cout << "\nDi C++, destructor = finally otomatis:" << endl;
    cout << "  {" << endl;
    cout << "    Resource r(\"db\");  // Constructor = open" << endl;
    cout << "    r.doWork();" << endl;
    cout << "    // throw exception di sini pun..." << endl;
    cout << "  }  // Destructor dipanggil otomatis di sini = finally!" << endl;

    cout << "\n--- Demo: Exception tidak mencegah cleanup ---" << endl;
    try {
        Resource r("NetworkConn", 100);  // Dibuat
        r.doWork();

        throw runtime_error("Terjadi error!");  // Exception dilempar

        // Baris ini tidak pernah dicapai
    }
    catch (const exception& e) {
        cout << "  Exception ditangkap: " << e.what() << endl;
        cout << "  Tapi lihat: Resource sudah di-cleanup sebelum catch ini!" << endl;
    }

    cout << "\nKenapa RAII lebih baik dari finally?" << endl;
    cout << "  - Tidak perlu ingat nulis finally" << endl;
    cout << "  - Cleanup terjadi OTOMATIS bahkan jika exception tidak di-catch" << endl;
    cout << "  - Tidak bisa lupa tutup resource" << endl;
    cout << "  - Nested cleanup tidak perlu nested try/finally" << endl;
}

// ============================================================================
// SECTION 6: Exception Safety Guarantees
// ============================================================================

void section6_ExceptionGuarantees() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Exception Safety Levels" << endl;
    cout << string(60, '=') << endl;

    cout << "\nSetiap function seharusnya punya 'guarantee' kalau terjadi exception:" << endl;

    cout << "\n1. NO-THROW guarantee (paling kuat)" << endl;
    cout << "   Fungsi TIDAK PERNAH throw exception" << endl;
    cout << "   Tandai dengan: noexcept" << endl;
    cout << "   Contoh: int double_val(int x) noexcept { return x * 2; }" << endl;

    cout << "\n2. STRONG guarantee (all-or-nothing)" << endl;
    cout << "   Kalau gagal: tidak ada yang berubah (seperti database transaction)" << endl;
    cout << "   Di JS: mirip Promise.all - semua berhasil atau tidak ada yang dicommit" << endl;
    cout << "   Contoh: vector.push_back() - kalau gagal alokasi, vector tidak berubah" << endl;

    cout << "\n3. BASIC guarantee (minimum acceptable)" << endl;
    cout << "   Kalau gagal: object masih valid tapi mungkin state berubah" << endl;
    cout << "   Tidak ada memory leak, tidak ada corrupt data" << endl;
    cout << "   Contoh: partial file write sebelum error" << endl;

    cout << "\n4. NO guarantee (hindari ini!)" << endl;
    cout << "   Exception = chaos, bisa memory leak, corrupt state" << endl;
    cout << "   Jangan tulis kode seperti ini" << endl;

    cout << "\nRekomendasi: paling tidak berikan BASIC guarantee di semua kode" << endl;
}

// ============================================================================
// SECTION 7: File Operations dengan Exception Handling
// ============================================================================

void safeReadFile(const string& filename) {
    try {
        ifstream file(filename);

        if (!file.is_open()) {
            throw FileException("Tidak bisa membuka file: " + filename);
        }

        string line;
        int lineNum = 0;

        while (getline(file, line)) {
            lineNum++;
            if (line.empty()) {
                throw ValidationException(
                    "baris " + to_string(lineNum),
                    "Baris kosong tidak diijinkan"
                );
            }
        }

        cout << "  File berhasil dibaca: " << lineNum << " baris" << endl;
        file.close();
    }
    catch (const FileException& e) {
        cout << "  File error: " << e.what() << endl;
    }
    catch (const ValidationException& e) {
        cout << "  Validation error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "  Unexpected error: " << e.what() << endl;
    }
}

void section7_FileHandling() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: File Handling yang Robust" << endl;
    cout << string(60, '=') << endl;

    cout << "\nCoba baca file yang tidak ada:" << endl;
    safeReadFile("build/tidak_ada.txt");

    cout << "\nCoba baca file yang ada:" << endl;
    safeReadFile("build/output.txt");  // Dibuat oleh section 04

    cout << "\nProgram tetap jalan meskipun ada error!" << endl;
}

// ============================================================================
// SECTION 8: Best Practices
// ============================================================================

void section8_BestPractices() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 8: Exception Handling Best Practices" << endl;
    cout << string(60, '=') << endl;

    cout << "\nYANG HARUS DILAKUKAN:" << endl;
    cout << "  - Gunakan tipe exception yang spesifik (bukan hanya exception)" << endl;
    cout << "  - Catch by const reference: catch (const Error& e)" << endl;
    cout << "    (Di JS: catch (e) - tidak ada pilihan selain reference-like)" << endl;
    cout << "  - Pakai RAII untuk resource management (bukan manual try/finally)" << endl;
    cout << "  - Implement what() di custom exception" << endl;

    cout << "\nYANG JANGAN DILAKUKAN:" << endl;
    cout << "  - Catch by value: catch (Error e) -> bisa terjadi object slicing!" << endl;
    cout << "  - Catch semua dan diam: catch (...) {} -> sangat berbahaya!" << endl;
    cout << "  - Gunakan exception untuk kontrol flow normal (seperti return)" << endl;
    cout << "  - Throw pointer atau char* (pakai exception objects)" << endl;

    cout << "\nTip untuk JS/TS developer:" << endl;
    cout << "  - catch (e) di JS = catch (const exception& e) di C++" << endl;
    cout << "  - e.message di JS = e.what() di C++" << endl;
    cout << "  - finally {} di JS = destructor di C++" << endl;
    cout << "  - instanceof check = berbeda catch blocks di C++" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "EXCEPTION HANDLING - Error Management" << endl;
    cout << "(Mirip JS/TS! try/catch sama, bedanya tipe-specific catch)" << endl;
    cout << string(60, '*') << endl;

    section1_BasicTryCatch();
    section2_MultipleCatches();
    section3_ExceptionHierarchy();
    section4_CustomExceptions();
    section5_RAIIPattern();
    section6_ExceptionGuarantees();
    section7_FileHandling();
    section8_BestPractices();

    cout << "\n" << string(60, '=') << endl;
    cout << "RINGKASAN" << endl;
    cout << string(60, '=') << endl;
    cout << "\nPadanan JS/TS Exception → C++:" << endl;
    cout << "  throw new Error('msg')    → throw runtime_error('msg')" << endl;
    cout << "  throw new TypeError(...)  → throw invalid_argument(...)" << endl;
    cout << "  throw new RangeError(...) → throw out_of_range(...)" << endl;
    cout << "  catch (e) { e.message }   → catch (const exception& e) { e.what() }" << endl;
    cout << "  finally { cleanup() }     → destructor (RAII pattern)" << endl;
    cout << "  class MyErr extends Error → class MyErr : public exception" << endl;
    cout << "\nPerbedaan utama:" << endl;
    cout << "  - catch HARUS tentukan tipe di C++" << endl;
    cout << "  - Tidak ada finally, pakai destructor (lebih baik!)" << endl;
    cout << "  - noexcept = garansi function tidak throw" << endl;
    cout << "\nNext: Modern C++ features untuk kode yang lebih bersih!" << endl;
    cout << string(60, '*') << endl << endl;

    return 0;
}
