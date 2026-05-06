/**
 * PROJECT 0 - Program 02: Object-Oriented Programming (OOP)
 * 
 * This program demonstrates:
 * 1. Class definition and member variables
 * 2. Constructors and destructors
 * 3. Access modifiers (public, private, protected)
 * 4. Inheritance (is-a relationship)
 * 5. Virtual functions and polymorphism
 * 6. Abstract classes (pure virtual)
 * 7. Method overriding
 * 
 * Concept: Shape hierarchy - Shape is base class
 *          Derived classes: Circle, Rectangle, Triangle
 * 
 * Compilation:
 *   g++ -std=c++17 -Wall -Wextra 02_OOP_Classes.cpp -o 02_oop
 * 
 * Run:
 *   ./02_oop
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

// ============================================================================
// SECTION 1: Base Class - Shape (Abstract)
// ============================================================================

/**
 * Base class: Shape
 * 
 * This is an ABSTRACT base class that defines the interface for all shapes.
 * It has one pure virtual function: calculateArea()
 * 
 * Key concepts:
 * - virtual: allows derived classes to override
 * - = 0: pure virtual (must be implemented by derived classes)
 * - virtual destructor: important for polymorphic classes
 */
class Shape {
protected:  // Protected = accessible to derived classes, not outside
    string name;
    
public:
    // Constructor
    Shape(const string& n) : name(n) {
        cout << "[CONSTRUCT] " << name << " shape created" << endl;
    }
    
    // Virtual destructor - important!
    virtual ~Shape() {
        cout << "[DESTRUCT] " << name << " shape destroyed" << endl;
    }
    
    // Pure virtual function - MUST be implemented by derived classes
    virtual double calculateArea() = 0;  // = 0 means "pure virtual"
    
    // Virtual function - can be overridden, but has default implementation
    virtual void describe() {
        cout << "  I am a " << name << " shape" << endl;
    }
    
    // Non-virtual function - all shapes use same implementation
    void printInfo() {
        cout << "Shape: " << name << endl;
        describe();
        cout << "  Area: " << fixed << setprecision(2) << calculateArea() << endl;
    }
    
    // Getter
    string getName() const { return name; }
};

// ============================================================================
// SECTION 2: Derived Classes
// ============================================================================

/**
 * Circle class - derived from Shape
 * 
 * Demonstrates:
 * - Inheriting from base class
 * - Adding new member variables (radius)
 * - Overriding pure virtual method (calculateArea)
 * - Calling base class constructor
 */
class Circle : public Shape {  // "public" means "is-a" relationship (vs "private")
private:
    double radius;
    
public:
    // Constructor - calls base class constructor with : Shape(name)
    Circle(double r) : Shape("Circle"), radius(r) {
        cout << "  [Circle specific] radius=" << r << endl;
    }
    
    // Override: Must implement the pure virtual function
    double calculateArea() override {  // override keyword helps catch mistakes
        return M_PI * radius * radius;
    }
    
    // Optional: Override describe() for custom behavior
    void describe() override {
        cout << "  I am a " << name << " with radius " << radius << endl;
    }
};

/**
 * Rectangle class - derived from Shape
 */
class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) {
        cout << "  [Rectangle specific] width=" << w << ", height=" << h << endl;
    }
    
    double calculateArea() override {
        return width * height;
    }
    
    void describe() override {
        cout << "  I am a " << name << " with width=" << width 
             << " and height=" << height << endl;
    }
};

/**
 * Triangle class - derived from Shape
 */
class Triangle : public Shape {
private:
    double base, height;
    
public:
    Triangle(double b, double h) : Shape("Triangle"), base(b), height(h) {
        cout << "  [Triangle specific] base=" << b << ", height=" << h << endl;
    }
    
    double calculateArea() override {
        return 0.5 * base * height;
    }
    
    void describe() override {
        cout << "  I am a " << name << " with base=" << base 
             << " and height=" << height << endl;
    }
};

// ============================================================================
// SECTION 1: Basic Class Concepts
// ============================================================================

void section1_ClassBasics() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: Class Basics - Encapsulation" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nA class groups data (attributes) and behavior (methods) together:" << endl;
    cout << "\nclass Shape {" << endl;
    cout << "  protected: string name;        // data - only derived classes see" << endl;
    cout << "  public: double calculateArea(); // method - everyone can call" << endl;
    cout << "}" << endl;
    
    cout << "\nAccess modifiers:" << endl;
    cout << "  - public: accessible from anywhere" << endl;
    cout << "  - private: only accessible inside this class" << endl;
    cout << "  - protected: accessible in this class and derived classes" << endl;
}

// ============================================================================
// SECTION 2: Constructors and Initialization
// ============================================================================

void section2_Constructors() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: Constructors and Initialization" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nConstructors run automatically when object is created:" << endl;
    cout << "\n--- Creating shapes ---" << endl;
    
    Circle c1(5.0);
    Rectangle r1(4.0, 6.0);
    Triangle t1(3.0, 8.0);
    
    cout << "\n--- All shapes created successfully ---" << endl;
}

// ============================================================================
// SECTION 3: Virtual Functions and Polymorphism
// ============================================================================

void section3_Polymorphism() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: Virtual Functions and Polymorphism" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nPolymorphism = 'many forms'" << endl;
    cout << "Same function call, different behavior based on actual type" << endl;
    
    // Create shapes with POINTERS to base class
    Shape* s1 = new Circle(5.0);
    Shape* s2 = new Rectangle(4.0, 6.0);
    Shape* s3 = new Triangle(3.0, 8.0);
    
    cout << "\n--- Polymorphic call: s->calculateArea() ---" << endl;
    cout << "Even though all are Shape*, correct method is called:" << endl;
    
    Shape* shapes[] = {s1, s2, s3};
    for (int i = 0; i < 3; i++) {
        cout << "\nShape " << i+1 << ": " << shapes[i]->getName() << endl;
        cout << "  Area = " << fixed << setprecision(2) 
             << shapes[i]->calculateArea() << endl;
    }
    
    cout << "\nWHY is this called polymorphism?" << endl;
    cout << "  - s1 points to a Shape, but it's actually a Circle" << endl;
    cout << "  - When we call s1->calculateArea(), it calls Circle's method" << endl;
    cout << "  - This is determined at RUNTIME (dynamic dispatch)" << endl;
    
    // Clean up
    delete s1;
    delete s2;
    delete s3;
}

// ============================================================================
// SECTION 4: Using Polymorphism Practically
// ============================================================================

void section4_PracticalPolymorphism() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: Practical Use of Polymorphism" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nWe can store different shape types in ONE container:" << endl;
    
    // Create a vector of Shape pointers
    vector<Shape*> shapes;
    
    shapes.push_back(new Circle(3.0));
    shapes.push_back(new Rectangle(4.0, 5.0));
    shapes.push_back(new Triangle(6.0, 7.0));
    shapes.push_back(new Circle(2.5));
    
    cout << "\n--- Iterating through different shapes ---" << endl;
    double totalArea = 0;
    for (int i = 0; i < shapes.size(); i++) {
        cout << "\n[Shape " << i+1 << "]" << endl;
        shapes[i]->printInfo();
        totalArea += shapes[i]->calculateArea();
    }
    
    cout << "\n--- Summary ---" << endl;
    cout << "Total number of shapes: " << shapes.size() << endl;
    cout << "Total area: " << fixed << setprecision(2) << totalArea << endl;
    
    cout << "\nWhy is this powerful?" << endl;
    cout << "  - We DON'T need to know what type each shape is" << endl;
    cout << "  - We just call shapes[i]->calculateArea()" << endl;
    cout << "  - The correct method is called automatically" << endl;
    cout << "  - Easy to add new shape types without changing this code!" << endl;
    
    // Clean up
    for (auto shape : shapes) {
        delete shape;
    }
    shapes.clear();
}

// ============================================================================
// SECTION 5: Method Overriding - Different Implementations
// ============================================================================

void section5_MethodOverriding() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: Method Overriding" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nBase class has default describe() method" << endl;
    cout << "Derived classes override it with custom behavior:" << endl;
    
    cout << "\n--- Base class default (should not happen) ---" << endl;
    Shape* generic = new Rectangle(2.0, 3.0);
    generic->describe();
    delete generic;
    
    cout << "\n--- Derived class overrides ---" << endl;
    Circle c(4.0);
    c.describe();
    
    Rectangle r(5.0, 6.0);
    r.describe();
    
    Triangle t(7.0, 8.0);
    t.describe();
}

// ============================================================================
// SECTION 6: Virtual Destructors (Important!)
// ============================================================================

void section6_VirtualDestructors() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Virtual Destructors (Critical Concept)" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nWithout virtual destructor: MEMORY LEAK!" << endl;
    cout << "\nExample:" << endl;
    cout << "  Shape* s = new Circle(5.0);" << endl;
    cout << "  delete s;  // Calls Shape::destructor, NOT Circle::destructor!" << endl;
    cout << "\nWith virtual destructor: Correct cleanup" << endl;
    cout << "  Shape* s = new Circle(5.0);" << endl;
    cout << "  delete s;  // Calls Circle::destructor, then Shape::destructor" << endl;
    
    cout << "\n--- Demonstration ---" << endl;
    {
        Shape* ptr = new Circle(5.0);
        cout << "Deleting through base class pointer..." << endl;
        delete ptr;  // Both destructors called in correct order
    }
}

// ============================================================================
// SECTION 7: Inheritance Hierarchy Visualization
// ============================================================================

void section7_InheritanceVisual() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: Inheritance Hierarchy" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nClass hierarchy for this program:" << endl;
    cout << "\n           [Shape] (abstract base)" << endl;
    cout << "              |" << endl;
    cout << "         +----+----+----+" << endl;
    cout << "         |    |    |" << endl;
    cout << "     [Circle] [Rectangle] [Triangle]" << endl;
    
    cout << "\nEach derived class:" << endl;
    cout << "  - INHERITS: name, destructor, printInfo(), describe()" << endl;
    cout << "  - MUST IMPLEMENT: calculateArea() (pure virtual)" << endl;
    cout << "  - MAY OVERRIDE: describe() (optional)" << endl;
    
    cout << "\nKey relationships:" << endl;
    cout << "  - Circle IS-A Shape" << endl;
    cout << "  - Rectangle IS-A Shape" << endl;
    cout << "  - Triangle IS-A Shape" << endl;
    cout << "  - Therefore: Can use Circle* as Shape*" << endl;
}

// ============================================================================
// SECTION 8: Common OOP Principles
// ============================================================================

void section8_OOPPrinciples() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 8: OOP Principles (SOLID)" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nS - Single Responsibility" << endl;
    cout << "  Circle is responsible ONLY for circle calculations" << endl;
    
    cout << "\nO - Open/Closed" << endl;
    cout << "  Can add new shapes (Triangle) WITHOUT modifying existing code" << endl;
    
    cout << "\nL - Liskov Substitution" << endl;
    cout << "  Any Shape* can be used where expected, works correctly" << endl;
    
    cout << "\nI - Interface Segregation" << endl;
    cout << "  Shape interface only exposes necessary methods" << endl;
    
    cout << "\nD - Dependency Inversion" << endl;
    cout << "  Depend on Shape (abstraction), not concrete Circle/Rectangle" << endl;
}

// ============================================================================
// SECTION 9: Common OOP Mistakes
// ============================================================================

void section9_CommonMistakes() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 9: Common OOP Mistakes" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\n[MISTAKE 1] Forgetting virtual destructor in base class" << endl;
    cout << "  Result: Derived class destructor NOT called, memory leak" << endl;
    
    cout << "\n[MISTAKE 2] Not using 'override' keyword" << endl;
    cout << "  Typo in method name = silent bug, not override" << endl;
    cout << "  FIX: Use override keyword, compiler catches typos" << endl;
    
    cout << "\n[MISTAKE 3] Mixing public/private inheritance" << endl;
    cout << "  class Circle : private Shape {...}  // Don't do this!" << endl;
    cout << "  Result: Circle is NOT a Shape (private inheritance)" << endl;
    
    cout << "\n[MISTAKE 4] Pure virtual but no implementation in derived" << endl;
    cout << "  Result: Compiler error (good!)" << endl;
    
    cout << "\n[MISTAKE 5] Using delete on derived pointer created as base" << endl;
    cout << "  Shape* s = new Circle(5);" << endl;
    cout << "  delete s;  // Works IF Shape has virtual destructor" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "OBJECT-ORIENTED PROGRAMMING (OOP)" << endl;
    cout << "Classes, Inheritance, Polymorphism" << endl;
    cout << string(60, '*') << endl;
    
    section1_ClassBasics();
    section2_Constructors();
    section3_Polymorphism();
    section4_PracticalPolymorphism();
    section5_MethodOverriding();
    section6_VirtualDestructors();
    section7_InheritanceVisual();
    section8_OOPPrinciples();
    section9_CommonMistakes();
    
    cout << "\n" << string(60, '=') << endl;
    cout << "SUMMARY" << endl;
    cout << string(60, '=') << endl;
    cout << "\nKey Takeaways:" << endl;
    cout << "1. Classes encapsulate data + behavior" << endl;
    cout << "2. Inheritance allows code reuse (is-a relationships)" << endl;
    cout << "3. Virtual functions enable polymorphism" << endl;
    cout << "4. Polymorphism = same interface, different behavior" << endl;
    cout << "5. ALWAYS use virtual destructors in base classes" << endl;
    cout << "6. Use 'override' keyword to catch typos" << endl;
    cout << "\nNext: Learn STL containers for data management!" << endl;
    cout << string(60, '*') << endl << endl;
    
    return 0;
}
