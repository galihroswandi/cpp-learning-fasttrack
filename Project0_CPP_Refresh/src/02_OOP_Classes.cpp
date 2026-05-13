/**
 * PROJECT 0 - Program 02: Object-Oriented Programming (OOP)
 *
 * Topik:
 * 1. Class definition dan member variables
 * 2. Constructors dan destructors
 * 3. Access modifiers (public, private, protected)
 * 4. Inheritance (is-a relationship)
 * 5. Virtual functions dan polymorphism
 * 6. Abstract classes (pure virtual)
 * 7. Method overriding
 *
 * Build: cd build && cmake .. && make 02_oop
 * Run:   ./build/bin/02_oop
 */

/**
 * ============================================================
 * UNTUK DEVELOPER JS/TS - BACA DULU!
 * ============================================================
 *
 * Kabar baiknya: OOP di C++ mirip dengan class di TypeScript!
 * Kamu sudah tahu konsep dasarnya.
 *
 * Yang SAMA dengan TS:
 *   - class, extends, implements
 *   - public / private / protected
 *   - constructor, method
 *   - Inheritance dan override
 *
 * Yang BERBEDA dari TS:
 *   1. `virtual` keyword - dibutuhkan agar method bisa di-override saat
 *      diakses via pointer ke base class. Di TS ini otomatis.
 *   2. Destructor (~ClassName) - cleanup saat object dihapus. Tidak ada di TS.
 *   3. Abstract class pakai `= 0` bukan interface. Di TS ada interface.
 *   4. `override` keyword SANGAT dianjurkan (di C++ tidak wajib tapi DO IT!)
 *
 * Analogi:
 *   TypeScript:                   C++:
 *   abstract class Shape {        class Shape {
 *     abstract area(): number;    public:
 *   }                               virtual double calculateArea() = 0;
 *                                 };
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

// ============================================================================
// BASE CLASS: Shape (Abstract)
// ============================================================================
//
// Seperti abstract class di TypeScript:
//   abstract class Shape {
//     protected name: string;
//     abstract calculateArea(): number;
//     describe(): void { ... }
//   }
//
// Di C++:
//   - `protected` = accessible di class ini dan turunannya (sama dengan TS)
//   - `virtual double calculateArea() = 0` = abstract method (HARUS diimplementasi)
//   - `virtual ~Shape()` = WAJIB ada di base class agar destructor bekerja benar!

class Shape {
protected:  // Sama dengan `protected` di TypeScript
    string name;

public:
    // Constructor - sama seperti constructor() di TS
    Shape(const string& n) : name(n) {
        cout << "  [CONSTRUCT] " << name << " dibuat" << endl;
    }

    // Virtual destructor - WAJIB ada di C++ base class!
    // Di TS tidak ada destructor, tapi di C++ ini penting untuk cleanup memory
    virtual ~Shape() {
        cout << "  [DESTRUCT] " << name << " dihapus" << endl;
    }

    // Pure virtual = abstract method di TS
    // `= 0` artinya "HARUS diimplementasi oleh derived class"
    // Kalau tidak diimplementasi -> compiler error (bagus!)
    virtual double calculateArea() = 0;

    // Virtual function WITH implementasi = method yang bisa di-override di TS
    // Derived class boleh override, boleh tidak
    virtual void describe() {
        cout << "  Saya adalah " << name << endl;
    }

    // Non-virtual = method yang TIDAK bisa di-override (berbeda perilakunya dari TS)
    void printInfo() {
        cout << "  Shape: " << name << endl;
        describe();
        cout << "  Area: " << fixed << setprecision(2) << calculateArea() << endl;
    }

    string getName() const { return name; }
};

// ============================================================================
// DERIVED CLASSES
// ============================================================================
//
// Di TypeScript: class Circle extends Shape { ... }
// Di C++:        class Circle : public Shape { ... }
//
// `public Shape` = "Circle adalah Shape" (IS-A relationship)
// Sama persis dengan `extends` di TS!

class Circle : public Shape {  // `public` = IS-A (extends di TS)
private:
    double radius;

public:
    // Panggil base class constructor: `: Shape("Circle")`
    // Sama seperti: `super("Circle")` di TypeScript constructor!
    Circle(double r) : Shape("Circle"), radius(r) {
        cout << "    [Circle] radius=" << r << endl;
    }

    // `override` = sama seperti `override` di TypeScript (C++11+)
    // Selalu pakai override! Compiler akan error kalau method namenya salah ketik
    double calculateArea() override {
        return M_PI * radius * radius;
    }

    void describe() override {
        cout << "  Saya Circle dengan radius " << radius << endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) {
        cout << "    [Rectangle] width=" << w << ", height=" << h << endl;
    }

    double calculateArea() override {
        return width * height;
    }

    void describe() override {
        cout << "  Saya Rectangle " << width << "x" << height << endl;
    }
};

class Triangle : public Shape {
private:
    double base, height;

public:
    Triangle(double b, double h) : Shape("Triangle"), base(b), height(h) {
        cout << "    [Triangle] base=" << b << ", height=" << h << endl;
    }

    double calculateArea() override {
        return 0.5 * base * height;
    }

    void describe() override {
        cout << "  Saya Triangle base=" << base << ", height=" << height << endl;
    }
};

// ============================================================================
// SECTION 1: Class Basics - Encapsulation
// ============================================================================

void section1_ClassBasics() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: Class Basics - Encapsulation" << endl;
    cout << string(60, '=') << endl;

    cout << "\nClass menggabungkan DATA (attributes) dan PERILAKU (methods):" << endl;
    cout << "\n  // TypeScript / JavaScript:       // C++:" << endl;
    cout << "  class Shape {                    class Shape {" << endl;
    cout << "    protected name: string;        protected: string name;" << endl;
    cout << "    abstract area(): number;       public:    virtual double calculateArea() = 0;" << endl;
    cout << "  }                                };" << endl;

    cout << "\nAccess modifiers (SAMA dengan TypeScript):" << endl;
    cout << "  - public:    accessible dari mana saja" << endl;
    cout << "  - private:   hanya accessible di dalam class ini" << endl;
    cout << "  - protected: accessible di class ini DAN derived classes" << endl;
}

// ============================================================================
// SECTION 2: Constructors dan Destructors
// ============================================================================
//
// Constructor di C++ = constructor() di TypeScript, SAMA!
// Tapi ada tambahan: DESTRUCTOR (~ClassName)
//
// Destructor tidak ada di JS/TS karena GC yang handle cleanup.
// Di C++, destructor dipanggil saat object dihapus/keluar scope.

void section2_Constructors() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: Constructors dan Destructors" << endl;
    cout << string(60, '=') << endl;

    cout << "\nConstructors dipanggil OTOMATIS saat object dibuat." << endl;
    cout << "Destructors dipanggil OTOMATIS saat object dihapus/keluar scope." << endl;
    cout << "\n--- Membuat shapes ---" << endl;

    {
        Circle c1(5.0);
        Rectangle r1(4.0, 6.0);
        Triangle t1(3.0, 8.0);

        cout << "\nSemua shape dibuat. Sekarang keluar dari scope..." << endl;
    }
    // Destructor otomatis dipanggil saat {} berakhir

    cout << "\nSemua shape otomatis dihapus (destructor dipanggil)!" << endl;
    cout << "Ini mirip seperti GC di JS, tapi lebih predictable." << endl;
}

// ============================================================================
// SECTION 3: Virtual Functions dan Polymorphism
// ============================================================================
//
// Polymorphism = "banyak bentuk"
// Memanggil method yang sama tapi hasilnya berbeda berdasarkan tipe objek
//
// Di TypeScript ini terjadi OTOMATIS:
//   const shape: Shape = new Circle(5);
//   shape.area(); // otomatis pakai Circle.area()
//
// Di C++, kamu butuh `virtual` keyword di base class untuk ini.
// TANPA virtual -> base class method yang dipanggil (BUG!)
// DENGAN virtual -> method dari tipe SEBENARNYA yang dipanggil (benar!)

void section3_Polymorphism() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: Virtual Functions dan Polymorphism" << endl;
    cout << string(60, '=') << endl;

    cout << "\nPolymorphism = panggil method yang sama, hasil berbeda per tipe" << endl;
    cout << "Di C++, BUTUH `virtual` keyword agar ini bekerja!" << endl;

    // Shape* = pointer ke base class, tapi actual object bisa derived class
    // Sama seperti: const s: Shape = new Circle(5); di TypeScript
    Shape* s1 = new Circle(5.0);
    Shape* s2 = new Rectangle(4.0, 6.0);
    Shape* s3 = new Triangle(3.0, 8.0);

    cout << "\n--- Polymorphic call: shape->calculateArea() ---" << endl;
    cout << "Semua bertipe Shape*, tapi method yang benar tetap dipanggil:" << endl;

    Shape* shapes[] = {s1, s2, s3};
    for (int i = 0; i < 3; i++) {
        cout << "\n  Shape[" << i+1 << "]: " << shapes[i]->getName() << endl;
        cout << "  Area = " << fixed << setprecision(2)
             << shapes[i]->calculateArea() << endl;
    }

    cout << "\nKenapa butuh `virtual` di C++ tapi tidak di TS?" << endl;
    cout << "  - TS: semua method virtual by default" << endl;
    cout << "  - C++: default = non-virtual (lebih efisien), virtual = opt-in" << endl;
    cout << "  - Tanpa virtual di C++: Shape::calculateArea() selalu dipanggil -> BUG!" << endl;

    delete s1;
    delete s2;
    delete s3;
}

// ============================================================================
// SECTION 4: Polymorphism Praktis - Container dengan Berbagai Tipe
// ============================================================================
//
// Di JS/TS, array bisa campur tipe (duck typing):
//   const shapes = [new Circle(), new Rectangle()]; // OK di JS
//
// Di C++, array/vector harus tipe sama.
// Tapi bisa pakai vector<Shape*> - vector of BASE CLASS POINTER!
// Ini memungkinkan menyimpan berbagai tipe yang punya base class sama.

void section4_PracticalPolymorphism() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: Polymorphism Praktis" << endl;
    cout << string(60, '=') << endl;

    cout << "\nMenyimpan berbagai tipe shape dalam SATU vector:" << endl;
    cout << "(Seperti array berisi berbagai tipe di JS, tapi dengan base class)" << endl;

    vector<Shape*> shapes;
    shapes.push_back(new Circle(3.0));
    shapes.push_back(new Rectangle(4.0, 5.0));
    shapes.push_back(new Triangle(6.0, 7.0));
    shapes.push_back(new Circle(2.5));

    cout << "\n--- Iterasi shapes ---" << endl;
    double totalArea = 0;
    for (size_t i = 0; i < shapes.size(); i++) {
        cout << "\n[Shape " << i+1 << "]" << endl;
        shapes[i]->printInfo();
        totalArea += shapes[i]->calculateArea();
    }

    cout << "\n--- Ringkasan ---" << endl;
    cout << "Total shapes: " << shapes.size() << endl;
    cout << "Total area: " << fixed << setprecision(2) << totalArea << endl;

    cout << "\nKenapa ini powerful?" << endl;
    cout << "  - Tidak perlu tahu tipe exact setiap shape" << endl;
    cout << "  - Tinggal panggil calculateArea() - yang benar otomatis dipanggil" << endl;
    cout << "  - Mau tambah shape baru? Cukup buat class baru, kode ini tidak perlu diubah!" << endl;

    for (auto shape : shapes) delete shape;
    shapes.clear();
}

// ============================================================================
// SECTION 5: Method Overriding
// ============================================================================

void section5_MethodOverriding() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: Method Overriding (Sama dengan TS Override)" << endl;
    cout << string(60, '=') << endl;

    cout << "\nBase class punya default describe()," << endl;
    cout << "Derived class bisa override dengan perilaku custom-nya:" << endl;

    cout << "\n--- Via base class pointer ---" << endl;
    Shape* generic = new Rectangle(2.0, 3.0);
    generic->describe();  // Memanggil Rectangle::describe() - bukan Shape::describe()
    delete generic;

    cout << "\n--- Via concrete types ---" << endl;
    Circle c(4.0);
    c.describe();

    Rectangle r(5.0, 6.0);
    r.describe();

    Triangle t(7.0, 8.0);
    t.describe();

    cout << "\nTip: Selalu pakai `override` keyword!" << endl;
    cout << "  C++: void describe() override { ... }" << endl;
    cout << "  TS:  override describe(): void { ... }" << endl;
    cout << "  Kalau ada typo di nama method -> compiler error (ditangkap lebih awal!)" << endl;
}

// ============================================================================
// SECTION 6: Virtual Destructors - PENTING!
// ============================================================================
//
// Ini tidak ada padanannya di JS/TS.
// Tapi sangat penting di C++!
//
// Masalah: kalau kamu delete Shape* yang sebenarnya Circle*:
//   - TANPA virtual destructor -> hanya Shape::~Shape() dipanggil
//   - Circle::~Circle() TIDAK dipanggil -> memory leak!
//   - DENGAN virtual destructor -> Circle::~Circle() dipanggil DULU, lalu Shape::~Shape()
//
// RULE: Kalau class punya virtual method -> SELALU tambahkan virtual destructor!

void section6_VirtualDestructors() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Virtual Destructors (Penting!)" << endl;
    cout << string(60, '=') << endl;

    cout << "\nTANPA virtual destructor:" << endl;
    cout << "  Shape* s = new Circle(5);" << endl;
    cout << "  delete s;  // Hanya Shape destructor dipanggil -> Circle memory leak!" << endl;

    cout << "\nDENGAN virtual destructor (seperti di kode kita):" << endl;
    cout << "  Shape* s = new Circle(5);" << endl;
    cout << "  delete s;  // Circle destructor DULU, lalu Shape destructor" << endl;

    cout << "\n--- Demo ---" << endl;
    {
        Shape* ptr = new Circle(5.0);
        cout << "delete via base class pointer:" << endl;
        delete ptr;  // Dengan virtual destructor, urutan cleanup benar
    }

    cout << "\nRule: Jika ada virtual method -> SELALU tambah virtual destructor!" << endl;
}

// ============================================================================
// SECTION 7: Inheritance Hierarchy
// ============================================================================

void section7_InheritanceVisual() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: Inheritance Hierarchy" << endl;
    cout << string(60, '=') << endl;

    cout << "\nHierarki class di program ini:" << endl;
    cout << "\n           [Shape] <- abstract base class" << endl;
    cout << "              |         (seperti abstract class di TS)" << endl;
    cout << "         +----+----+" << endl;
    cout << "         |         |" << endl;
    cout << "     [Circle] [Rectangle] [Triangle]" << endl;

    cout << "\nSetiap derived class:" << endl;
    cout << "  - INHERIT: name, destructor, printInfo(), describe()" << endl;
    cout << "  - WAJIB IMPLEMENT: calculateArea() (pure virtual / abstract)" << endl;
    cout << "  - BOLEH OVERRIDE: describe() (virtual dengan implementasi)" << endl;

    cout << "\nIS-A relationship (sama dengan extends di TS):" << endl;
    cout << "  - Circle IS-A Shape    -> bisa dipakai sebagai Shape*" << endl;
    cout << "  - Rectangle IS-A Shape -> bisa dipakai sebagai Shape*" << endl;
    cout << "  - Triangle IS-A Shape  -> bisa dipakai sebagai Shape*" << endl;
}

// ============================================================================
// SECTION 8: SOLID Principles
// ============================================================================

void section8_OOPPrinciples() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 8: SOLID Principles (berlaku untuk TS juga!)" << endl;
    cout << string(60, '=') << endl;

    cout << "\nS - Single Responsibility" << endl;
    cout << "  Circle hanya bertanggung jawab untuk kalkulasi circle" << endl;

    cout << "\nO - Open/Closed" << endl;
    cout << "  Bisa tambah Triangle TANPA ubah code Circle atau Rectangle" << endl;

    cout << "\nL - Liskov Substitution" << endl;
    cout << "  Shape* bisa diganti dengan Circle*, Rectangle*, dll tanpa masalah" << endl;

    cout << "\nI - Interface Segregation" << endl;
    cout << "  Shape hanya expose method yang diperlukan" << endl;

    cout << "\nD - Dependency Inversion" << endl;
    cout << "  Depend on abstraction (Shape), bukan concrete class (Circle)" << endl;

    cout << "\nSemua prinsip ini SAMA berlakunya di TypeScript!" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "OBJECT-ORIENTED PROGRAMMING (OOP)" << endl;
    cout << "Classes, Inheritance, Polymorphism" << endl;
    cout << "(Mirip TypeScript! Tapi ada beberapa perbedaan penting)" << endl;
    cout << string(60, '*') << endl;

    section1_ClassBasics();
    section2_Constructors();
    section3_Polymorphism();
    section4_PracticalPolymorphism();
    section5_MethodOverriding();
    section6_VirtualDestructors();
    section7_InheritanceVisual();
    section8_OOPPrinciples();

    cout << "\n" << string(60, '=') << endl;
    cout << "RINGKASAN" << endl;
    cout << string(60, '=') << endl;
    cout << "\nKey Takeaways:" << endl;
    cout << "1. Class di C++ mirip class TS: constructor, method, extends" << endl;
    cout << "2. `virtual` keyword wajib untuk polymorphism (beda dengan TS)" << endl;
    cout << "3. `= 0` = pure virtual = abstract method di TS" << endl;
    cout << "4. `override` keyword sangat dianjurkan (sama seperti TS)" << endl;
    cout << "5. SELALU tambah virtual destructor di base class!" << endl;
    cout << "\nBedanya dengan TypeScript:" << endl;
    cout << "  TS: method otomatis virtual, ada interface, ada GC" << endl;
    cout << "  C++: method default non-virtual, pakai = 0 untuk abstract, manual destructor" << endl;
    cout << "\nNext: STL containers untuk data management!" << endl;
    cout << string(60, '*') << endl << endl;

    return 0;
}
