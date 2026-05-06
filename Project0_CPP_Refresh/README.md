# Project 0: C++ Refresh - Complete Fundamentals

## 📚 Tujuan Pembelajaran

Anda akan refresh/reinforce konsep-konsep C++ yang essential sebelum masuk ke Qt development. Project ini terdiri dari **6 program pembelajaran** yang progressive, mulai dari mudah hingga advanced.

**Duration**: 1-2 hari  
**Prerequisites**: Familiar dengan basic syntax C++ (sudah pernah menulis if/for/function)  
**Outcome**: Solid understanding of C++ memory management, OOP, STL, dan modern C++ features

---

## 📋 Materi yang Akan Dipelajari

### 1. **Memory Management** (Program 01)
- **Stack vs Heap**: Perbedaan memory allocation strategies
- **Pointers**: Address-of operator (`&`), dereference operator (`*`)
- **References**: Alias to existing variables (safer than pointers)
- **Dynamic Memory**: `new` dan `delete` operators
- **Memory Leaks**: Apa itu, bagaimana menghindari

**Why Important for Qt?**  
Qt extensively uses dynamic memory. Understanding how memory works akan membantu debugging memory-related issues.

---

### 2. **Object-Oriented Programming** (Program 02)
- **Classes & Objects**: Encapsulation, attributes, methods
- **Constructors & Destructors**: Initialization dan cleanup
- **Inheritance**: Code reuse, is-a relationship
- **Polymorphism**: Virtual functions, method overriding
- **Access Modifiers**: `public`, `private`, `protected`

**Why Important for Qt?**  
Qt framework dibangun dengan heavy OOP design. Setiap Qt widget adalah class hierarchy. Memahami inheritance/polymorphism adalah KEY untuk extend Qt components.

---

### 3. **Standard Template Library (STL)** (Program 03)
- **Containers**: `std::vector`, `std::map`, `std::string`
- **Iterators**: Cara traverse containers
- **Algorithms**: Common operations (sort, find, transform)
- **String Operations**: Powerful string manipulation

**Why Important for Qt?**  
Data handling dalam ECDIS parser membutuhkan containers. STL containers lebih efficient daripada raw arrays.

---

### 4. **File I/O** (Program 04)
- **Reading Files**: `std::ifstream`
- **Writing Files**: `std::ofstream`
- **Binary vs Text**: Perbedaan file modes
- **Seeking & Positioning**: Navigate dalam file

**Why Important for Qt?**  
S-57 files adalah binary format. Kemampuan membaca/parse binary files adalah foundation dari Project 3.

---

### 5. **Exception Handling** (Program 05)
- **Try-Catch Blocks**: Error handling gracefully
- **Throwing Exceptions**: Bagaimana mengomunikasikan errors
- **Standard Exceptions**: `std::exception` dan derived classes
- **RAII Pattern**: Resource Acquisition Is Initialization

**Why Important for Qt?**  
Production code HARUS robust. Exception handling membuat aplikasi tidak crash pada invalid data.

---

### 6. **Modern C++ Features** (Program 06)
- **Smart Pointers**: `std::unique_ptr`, `std::shared_ptr` (automatic memory management)
- **Auto Keyword**: Type deduction
- **Range-Based For Loop**: Clean iteration
- **Move Semantics**: Efficient resource transfer (C++11)
- **Lambda Functions**: Anonymous functions, functional programming

**Why Important for Qt?**  
Modern C++ code lebih clean, lebih safe, lebih efficient. Qt 6 (yang terbaru) menggunakan modern C++ features extensively.

---

## 🚀 Struktur Program

### Program 01: Memory Management
```
01_Memory_Management.cpp
├─ Stack allocation basics
├─ Heap allocation dengan new/delete
├─ Pointer arithmetic & dereferencing
├─ References vs pointers
├─ Dynamic arrays
└─ Memory leak detection tips
```

### Program 02: OOP - Shape Hierarchy
```
02_OOP_Classes.cpp
├─ Base class: Shape
├─ Derived classes: Circle, Rectangle, Triangle
├─ Virtual functions (polymorphism)
├─ Constructor/destructor chaining
├─ Inheritance best practices
└─ Pure virtual classes (abstract)
```

### Program 03: STL Containers & Algorithms
```
03_STL_Containers.cpp
├─ Vector: dynamic arrays
├─ String: powerful text manipulation
├─ Map: key-value data structure
├─ Iterators
├─ Algorithms (sort, find, transform)
└─ Real-world: Parsing CSV-like data
```

### Program 04: File I/O
```
04_File_IO.cpp
├─ Text file reading/writing
├─ Binary file operations
├─ File positioning (seek/tell)
├─ Structured data in files
└─ Error handling
```

### Program 05: Exception Handling
```
05_Exception_Handling.cpp
├─ Try-catch blocks
├─ Custom exception classes
├─ Resource cleanup with RAII
├─ Standard exception hierarchy
└─ Exception safety guarantees
```

### Program 06: Modern C++ Features
```
06_Modern_CPP.cpp
├─ Smart pointers (unique_ptr, shared_ptr)
├─ Auto type deduction
├─ Range-based for loops
├─ Move semantics
└─ Lambda functions
```

---

## 🎓 Konsep-Konsep Kunci yang Harus Dipahami

### Memory Model
```
┌─────────────────────────────────┐
│          MEMORY LAYOUT          │
├─────────────────────────────────┤
│  CODE SEGMENT                   │ (Program instructions)
├─────────────────────────────────┤
│  STATIC DATA                    │ (Global variables)
├─────────────────────────────────┤
│  HEAP                           │ (Dynamic allocation - grows up)
│  ▲                              │
│  │ (allocate)                   │
├─────────────────────────────────┤
│                                 │
│  ↓ (deallocate)                │
│  STACK                          │ (Local variables - grows down)
└─────────────────────────────────┘

KEY CONCEPT:
- Stack: Automatic cleanup when scope ends (safe but limited)
- Heap: Manual cleanup with delete (flexible but manual)
- Stack allocation = FAST, predictable
- Heap allocation = FLEXIBLE, but need care
```

### Pointer Visualization
```
int x = 42;
int* ptr = &x;          // ptr HOLDS ADDRESS of x

Memory:
┌────────────────────┐
│ Address | Value    │
├────────────────────┤
│ 0x1000  | 42       │ ← x (variable)
│ 0x1004  | 0x1000   │ ← ptr (holds address)
└────────────────────┘

Operations:
&x          → 0x1000 (address-of)
*ptr        → 42     (dereference)
ptr->field  → access member through pointer
```

### Class Hierarchy (Polymorphism)
```
         ┌─────────┐
         │ Shape   │ (Base class)
         │ ─────── │
         │ + area()│ (virtual)
         └────┬────┘
              │ inherits
        ┌─────┼─────┐
        │     │     │
    ┌─────┐ ┌──────┐ ┌───────────┐
    │Circle│ │Rect  │ │ Triangle  │
    └─────┘ └──────┘ └───────────┘
    
At runtime:
Shape* s = new Circle(5);
s->area();  // Calls Circle::area(), NOT Shape::area()
            // This is POLYMORPHISM
```

---

## 🔧 Cara Compile & Run

### Option 1: Manual compilation dengan g++
```bash
cd /home/galih/Documents/Explore/belajar-cpp/Project0_CPP_Refresh

# Compile individual program
g++ -std=c++17 -Wall -Wextra src/01_Memory_Management.cpp -o build/01_memory
g++ -std=c++17 -Wall -Wextra src/02_OOP_Classes.cpp -o build/02_oop
# ... etc

# Run
./build/01_memory
./build/02_oop
```

### Option 2: Using CMake (recommended)
```bash
cd /home/galih/Documents/Explore/belajar-cpp/Project0_CPP_Refresh
mkdir -p build
cd build
cmake ..
make
./01_memory
./02_oop
```

---

## 📊 Program Output Breakdown

Setiap program akan menunjukkan:
1. **Konsep demonstrasi** - output yang menunjukkan bagaimana concept bekerja
2. **Side-by-side comparison** - contoh DO vs DONT
3. **Real-world simulation** - praktis use case mirip ECDIS parser

---

## ✅ Checklist - Anda Sudah Siap Lanjut ke Project 1 Jika:

- [ ] Mengerti perbedaan stack vs heap allocation
- [ ] Bisa membaca & mengerti pointer syntax (`*`, `&`, `->`)
- [ ] Mengerti konsep inheritance dan virtual functions
- [ ] Familiar dengan `std::vector`, `std::map`, `std::string`
- [ ] Bisa membaca/menulis file dengan ifstream/ofstream
- [ ] Tahu bagaimana exception handling bekerja
- [ ] Familiar dengan smart pointers dan auto keyword

---

## 🧪 Latihan Wajib (Qt-Oriented, 60–120 menit total)

Tujuan latihan ini bukan “tambah fitur besar”, tapi memaksa kamu memahami pola yang nanti kepakai di Qt: **ownership/lifetime**, **data structure**, dan **error handling yang rapi**.

### Program 01 — Memory Management
- **Latihan**:
  - Ubah `section1_StackVsHeap()` agar setelah `delete` kamu set pointer ke `nullptr`, lalu buat helper kecil `safeDelete(T*& p)` untuk single object dan `safeDeleteArray(T*& p)` untuk array.
  - Tambah 1 contoh “optional output” function yang menerima pointer nullable (mis. `bool tryGetValue(int* out)`), lalu bandingkan dengan versi reference.
- **Checkpoint**:
  - Kamu bisa menjelaskan “dangling pointer” dan kenapa `nullptr` penting untuk menghindari use-after-free.

### Program 02 — OOP Classes
- **Latihan**:
  - Tambahkan 1 method virtual baru di base class (mis. `name()`), override di semua derived class.
  - Buat `std::vector<std::unique_ptr<Shape>>` (bukan raw pointer) untuk menyimpan shapes.
- **Checkpoint**:
  - Kamu paham polymorphism + RAII; tidak ada `new/delete` manual.

### Program 03 — STL Containers
- **Latihan**:
  - Tambah satu fungsi `filter` + `transform` memakai `<algorithm>` (mis. filter angka > X lalu transform jadi string).
  - Buat representasi sederhana “feature list” dengan `struct Feature { id, type, name, vertices... }` lalu simpan di `std::vector`.
- **Checkpoint**:
  - Kamu bisa membedakan kapan pakai `vector` vs `map`, dan bisa iterasi dengan range-for + iterator.

### Program 04 — File I/O
- **Latihan**:
  - Tambah validasi: kalau file gagal dibuka atau header tidak cocok, tampilkan error yang jelas dan return.
  - Tambahkan opsi “print ringkasan” (jumlah record/bytes) tanpa print semua detail.
- **Checkpoint**:
  - Kamu nyaman dengan pattern: open → validate → read loop → handle error.

### Program 05 — Exception Handling
- **Latihan**:
  - Buat 1 custom exception yang membawa context (mis. path file / record index).
  - Tunjukkan 1 contoh RAII untuk resource non-memory (mis. file wrapper/guard kecil).
- **Checkpoint**:
  - Kamu paham bedanya “return error code” vs “throw exception”, dan kapan lebih cocok.

### Program 06 — Modern C++
- **Latihan**:
  - Refactor semua `unique_ptr<int> uptr(new int(...))` menjadi `std::make_unique<int>(...)`.
  - Tambah 1 contoh move semantics: return `std::vector<int>` dari function dan amati performa/log (konseptual).
- **Checkpoint**:
  - Kamu bisa menjelaskan ownership `unique_ptr` dan kenapa move itu “transfer kepemilikan”.

---

## 🎯 Tips Pembelajaran Effective

1. **Baca code dengan cermat** - Setiap baris dicomment
2. **Modify dan experiment** - Change values, add prints, observe behavior
3. **Relate to web development** - Gunakan background Anda sebagai reference point
4. **Take notes** - Catat konsep yang baru atau confusing
5. **Run all programs** - Jangan hanya baca, jalankan dan lihat output
6. **Debug dengan print** - Use `std::cout` untuk understand flow

---

## 🤔 Analogi dengan Web Development (untuk mempermudah)

| C++ Concept | Web Dev Analogy | Example |
|---|---|---|
| **Pointer** | DOM node reference | `document.getElementById('id')` returns reference |
| **Memory allocation** | Creating objects | `new Object()` in JavaScript |
| **Destructor** | Cleanup/garbage collection | Component unmount in React |
| **Inheritance** | CSS selector inheritance | Child inherits parent styles |
| **Polymorphism** | Event handlers overriding | Override parent event handler |
| **STL vector** | JavaScript array | `let arr = []` |
| **STL map** | JavaScript object/dictionary | `let obj = {}` |
| **Exception** | Try-catch in JS | `try { } catch(e) { }` |

---

## 📖 Further Reading & Resources

1. **C++ Reference**: https://en.cppreference.com
2. **Modern C++ Best Practices**: https://github.com/isocpp/cppcoreguidelines
3. **Memory Management**: https://en.cppreference.com/w/cpp/memory
4. **Qt Integration**: Setelah ini, konsep ini akan diterapkan di Qt classes

---

## 🚨 Common Mistakes (Akan Dijelaskan di Code)

1. ❌ Forgetting to delete memory → Memory leak
2. ❌ Using deleted pointer → Dangling pointer (crash)
3. ❌ Not using virtual keyword → Slicing problem
4. ❌ Forgetting destructors → Resource leak
5. ❌ Raw pointers in modern code → Should use smart pointers
6. ❌ Not catching exceptions → Program crash on error

---

## 📝 Next Steps

1. ✅ Read this README completely
2. ✅ Compile & run all 6 programs
3. ✅ Modify programs (add features, change values)
4. ✅ Answer self-assessment questions at bottom
5. 🚀 **Move to Project 1: Qt Basics**

---

## 🎬 Self-Assessment Questions

Setelah belajar Project 0, jawab pertanyaan ini untuk self-check:

1. **Memory**: What's the difference between `int x = 5;` (stack) vs `int* x = new int(5);` (heap)? When should you use each?

2. **Pointers**: If `int x = 42;` and `int* ptr = &x;`, what's the value of `*ptr`? Draw the memory diagram.

3. **OOP**: Design a class hierarchy for Vehicle → Car, Motorcycle, Truck. Which methods should be virtual?

4. **STL**: How would you store student records (name, ID, GPA) using STL containers? `vector<T>` or `map<K,V>`?

5. **File I/O**: Write pseudocode to read a CSV file and store data in a `std::vector<std::map<std::string, std::string>>`.

6. **Modern C++**: What's the advantage of `std::unique_ptr` over `new`/`delete`?

(Answers provided in the source code or discussion)

---

**Ready to start? Run the programs and let's begin! 🚀**
