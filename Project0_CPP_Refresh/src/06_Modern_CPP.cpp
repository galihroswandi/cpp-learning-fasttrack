/**
 * PROJECT 0 - Program 06: Modern C++ Features (C++11/C++17/C++20)
 * 
 * This program demonstrates:
 * 1. Smart pointers (unique_ptr, shared_ptr)
 * 2. Auto keyword and type deduction
 * 3. Range-based for loops
 * 4. Move semantics and rvalue references
 * 5. Lambda functions
 * 6. Variadic templates and fold expressions
 * 
 * Modern C++ makes code cleaner, safer, and more efficient
 * 
 * Compilation:
 *   g++ -std=c++17 -Wall -Wextra 06_Modern_CPP.cpp -o 06_modern
 * 
 * Run:
 *   ./06_modern
 */

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cstring>
using namespace std;

// ============================================================================
// SECTION 1: Smart Pointers
// ============================================================================

class Widget {
private:
    int id;
    
public:
    Widget(int i) : id(i) {
        cout << "    [Widget " << id << " constructed]" << endl;
    }
    
    ~Widget() {
        cout << "    [Widget " << id << " destructed]" << endl;
    }
    
    void describe() const {
        cout << "      I am Widget #" << id << endl;
    }
};

void section1_SmartPointers() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: Smart Pointers (Automatic Memory Management)" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nTraditional pointers (error-prone):" << endl;
    {
        cout << "  Widget* w = new Widget(1);" << endl;
        cout << "  delete w;  // Manual cleanup - easy to forget!" << endl;
    }
    
    cout << "\nstd::unique_ptr (exclusive ownership):" << endl;
    {
        cout << "  Creating unique_ptr:" << endl;
        unique_ptr<Widget> w1 = make_unique<Widget>(1);
        w1->describe();
        
        cout << "  Can transfer ownership (move):" << endl;
        unique_ptr<Widget> w2 = move(w1);  // w1 is now null
        w2->describe();
        
        cout << "  get() returns raw pointer:" << endl;
        Widget* raw = w2.get();
        cout << "  raw pointer: " << raw << endl;
        
        cout << "  Auto-cleanup when scope ends" << endl;
    }
    cout << "  (Destructors called automatically)" << endl;
    
    cout << "\nstd::shared_ptr (shared ownership):" << endl;
    {
        cout << "  Creating shared_ptrs:" << endl;
        shared_ptr<Widget> s1 = make_shared<Widget>(2);
        cout << "  use_count: " << s1.use_count() << endl;
        
        cout << "  Sharing ownership:" << endl;
        shared_ptr<Widget> s2 = s1;
        cout << "  use_count after copy: " << s1.use_count() << endl;
        
        cout << "  Both point to same Widget:" << endl;
        s1->describe();
        s2->describe();
        
        cout << "  When s1 goes out of scope:" << endl;
    }
    {
        cout << "  Only s2 remains, still valid" << endl;
        shared_ptr<Widget> s3 = make_shared<Widget>(3);
        s3->describe();
    }
    cout << "  (All destructed when last shared_ptr destroyed)" << endl;
    
    cout << "\nSmart pointer advantages:" << endl;
    cout << "  ✓ Automatic cleanup (no memory leaks)" << endl;
    cout << "  ✓ Exception safe (cleanup even if throw)" << endl;
    cout << "  ✓ Clear ownership semantics" << endl;
    cout << "  ✓ Cannot accidentally double-delete" << endl;
}

// ============================================================================
// SECTION 2: Auto Keyword and Type Deduction
// ============================================================================

void section2_AutoKeyword() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: Auto Keyword - Type Deduction" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nBefore C++11 (verbose):" << endl;
    cout << "  map<string, vector<int>>::iterator it = myMap.begin();" << endl;
    
    cout << "\nWith auto (clean):" << endl;
    cout << "  auto it = myMap.begin();  // Compiler deduces type" << endl;
    
    cout << "\nExamples:" << endl;
    
    auto num = 42;                              // int
    auto flt = 3.14;                            // double
    auto str = string("Hello");                 // std::string
    auto vec = vector<int>{1, 2, 3};           // std::vector<int>
    
    cout << "  auto num = 42;              // " << typeid(num).name() << endl;
    cout << "  auto flt = 3.14;            // " << typeid(flt).name() << endl;
    cout << "  auto str = string(\"...\");   // " << typeid(str).name() << endl;
    
    cout << "\nWith structured bindings (C++17):" << endl;
    {
        pair<string, int> p = {"Alice", 30};
        auto [name, age] = p;  // Decompose pair
        cout << "  auto [name, age] = pair;" << endl;
        cout << "  name = " << name << ", age = " << age << endl;
    }
    
    cout << "\nWhen to use auto:" << endl;
    cout << "  ✓ For complex types (iterators, templates)" << endl;
    cout << "  ✓ When type is obvious from context" << endl;
    cout << "  ✓ For generic code" << endl;
    cout << "  ✗ NOT for unclear types - be explicit for readability" << endl;
}

// ============================================================================
// SECTION 3: Range-Based For Loops
// ============================================================================

void section3_RangeBasedFor() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: Range-Based For Loops" << endl;
    cout << string(60, '=') << endl;
    
    vector<int> v = {10, 20, 30, 40, 50};
    
    cout << "\nOld style (C++98):" << endl;
    cout << "  for (int i = 0; i < v.size(); ++i) {" << endl;
    cout << "    cout << v[i];" << endl;
    cout << "  }" << endl;
    
    cout << "\nIterator style (C++11):" << endl;
    cout << "  for (auto it = v.begin(); it != v.end(); ++it) {" << endl;
    cout << "    cout << *it;" << endl;
    cout << "  }" << endl;
    
    cout << "\nRange-based for (C++11 - cleaner):" << endl;
    cout << "  for (int val : v) {" << endl;
    cout << "    cout << val;" << endl;
    cout << "  }" << endl;
    cout << "  Result: ";
    for (int val : v) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\nWith reference (modify elements):" << endl;
    for (auto& val : v) {
        val = val * 2;
    }
    cout << "  After doubling: ";
    for (int val : v) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\nWith const reference (read-only, efficient):" << endl;
    for (const auto& val : v) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\nWorks with any container:" << endl;
    cout << "  vector, array, string, map, set, etc." << endl;
}

// ============================================================================
// SECTION 4: Move Semantics (Rvalue References)
// ============================================================================

class MyString {
private:
    char* data;
    size_t size;
    
public:
    // Constructor
    MyString(const char* s) : size(strlen(s)) {
        data = new char[size + 1];
        strcpy(data, s);
        cout << "    [Copied: \"" << data << "\"]" << endl;
    }
    
    // Copy constructor
    MyString(const MyString& other) : size(other.size) {
        data = new char[size + 1];
        strcpy(data, other.data);
        cout << "    [Copy constructed]" << endl;
    }
    
    // Move constructor (C++11) - steal resources!
    MyString(MyString&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "    [Move constructed - EFFICIENT!]" << endl;
    }
    
    // Destructor
    ~MyString() {
        if (data) {
            cout << "    [Destructed]" << endl;
        }
        delete[] data;
    }
    
    const char* c_str() const { return data; }
};

void section4_MoveSemantics() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: Move Semantics (Rvalue References)" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nWithout move (copies data):" << endl;
    {
        cout << "  Creating temp string:" << endl;
        MyString s1 = "Hello";
    }
    
    cout << "\nWith move (steals data):" << endl;
    {
        cout << "  Moving temp string:" << endl;
        MyString s2 = MyString("World");  // Calls move constructor!
    }
    
    cout << "\nWhy move matters:" << endl;
    cout << "  - Copy: allocate new memory, copy data = SLOW" << endl;
    cout << "  - Move: steal pointer, null out source = FAST" << endl;
    cout << "  - Perfect for temporary objects" << endl;
    cout << "  - Also can use move(s1) to force move" << endl;
}

// ============================================================================
// SECTION 5: Lambda Functions
// ============================================================================

void section5_Lambdas() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: Lambda Functions (Anonymous Functions)" << endl;
    cout << string(60, '=') << endl;
    
    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    
    cout << "\nLambda syntax:" << endl;
    cout << "  [capture] (params) -> return_type { body }" << endl;
    
    cout << "\nSimple lambda:" << endl;
    auto printDouble = [](int x) { cout << x << " "; };
    cout << "  Printing doubled: ";
    for (int x : v) {
        printDouble(x * 2);
    }
    cout << endl;
    
    cout << "\nLambda with capture (using external variable):" << endl;
    int multiplier = 10;
    auto multiply = [multiplier](int x) { return x * multiplier; };
    cout << "  Multiply each by " << multiplier << ": ";
    for (int x : v) {
        cout << multiply(x) << " ";
    }
    cout << endl;
    
    cout << "\nLambda with return type:" << endl;
    auto isEven = [](int x) -> bool { return x % 2 == 0; };
    cout << "  Filter even numbers: ";
    for (int x : v) {
        if (isEven(x)) cout << x << " ";
    }
    cout << endl;
    
    cout << "\nUsing lambdas with algorithms:" << endl;
    sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    cout << "  Sorted descending: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    
    cout << "\nCapture options:" << endl;
    cout << "  []         - no capture" << endl;
    cout << "  [=]        - capture all by value" << endl;
    cout << "  [&]        - capture all by reference" << endl;
    cout << "  [x, &y]    - capture x by value, y by reference" << endl;
}

// ============================================================================
// SECTION 6: Variadic Templates & Fold Expressions (C++17)
// ============================================================================

// Template that accepts any number of arguments
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // Fold expression (C++17)
}

template<typename... Args>
void printAll(const Args&... args) {
    ((cout << args << " "), ...);  // Fold expression with comma operator
}

void section6_VariadicTemplates() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Variadic Templates & Fold Expressions (C++17)" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nVariadic templates accept variable number of arguments:" << endl;
    
    cout << "\nSum of numbers:" << endl;
    cout << "  sum(1, 2, 3) = " << sum(1, 2, 3) << endl;
    cout << "  sum(1.5, 2.5, 3.5) = " << sum(1.5, 2.5, 3.5) << endl;
    cout << "  sum(10, 20, 30, 40, 50) = " << sum(10, 20, 30, 40, 50) << endl;
    
    cout << "\nPrint different types:" << endl;
    cout << "  printAll(1, \" plus \", 2, \" equals \", 3) => ";
    printAll(1, " plus ", 2, " equals ", 3);
    cout << endl;
    
    cout << "\nFold expressions (C++17):" << endl;
    cout << "  (args + ...)  = ((arg1 + arg2) + arg3) + ..." << endl;
}

// ============================================================================
// SECTION 7: Comparing Old vs Modern C++
// ============================================================================

void section7_ComparisonOldVsModern() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: Comparison - Old C++ vs Modern C++" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\n[OLD - C++98/03]:" << endl;
    cout << "  std::vector<int> v;" << endl;
    cout << "  for (int i = 0; i < v.size(); ++i) {" << endl;
    cout << "    int* p = new int(v[i]);" << endl;
    cout << "    delete p;  // Manual cleanup" << endl;
    cout << "  }" << endl;
    cout << "  PROBLEMS: verbose, manual memory management, error-prone" << endl;
    
    cout << "\n[MODERN - C++17]:" << endl;
    cout << "  for (auto val : v) {" << endl;
    cout << "    auto p = make_unique<int>(val);" << endl;
    cout << "  }" << endl;
    cout << "  BENEFITS: clean, safe, automatic cleanup" << endl;
    
    cout << "\nModern C++ features at a glance:" << endl;
    cout << "  C++11: auto, range-for, lambdas, smart pointers, move" << endl;
    cout << "  C++14: auto return types, binary literals" << endl;
    cout << "  C++17: structured bindings, fold expressions" << endl;
    cout << "  C++20: concepts, ranges, coroutines" << endl;
}

// ============================================================================
// SECTION 8: Real-World Example - Data Processing
// ============================================================================

void section8_RealWorldExample() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 8: Real-World - Process Temperature Data" << endl;
    cout << string(60, '=') << endl;
    
    // Data with smart pointers
    auto readings = make_unique<vector<double>>();
    readings->push_back(22.5);
    readings->push_back(23.1);
    readings->push_back(21.9);
    readings->push_back(22.8);
    readings->push_back(23.5);
    
    cout << "\nTemperature readings:" << endl;
    for (const auto& temp : *readings) {
        cout << "  " << temp << "°C" << endl;
    }
    
    // Calculate statistics with modern C++
    double sum = 0;
    double minTemp = *readings->begin();
    double maxTemp = *readings->begin();
    
    for (const auto& temp : *readings) {
        sum += temp;
        if (temp < minTemp) minTemp = temp;
        if (temp > maxTemp) maxTemp = temp;
    }
    
    double avg = sum / readings->size();
    
    cout << "\nStatistics:" << endl;
    cout << "  Min: " << minTemp << "°C" << endl;
    cout << "  Max: " << maxTemp << "°C" << endl;
    cout << "  Avg: " << avg << "°C" << endl;
    
    cout << "\nAbove average: ";
    for_each(readings->begin(), readings->end(),
             [avg](double t) { if (t > avg) cout << t << " "; });
    cout << endl;
    
    cout << "\nNo manual cleanup needed!" << endl;
    cout << "  (Automatic when readings goes out of scope)" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "MODERN C++ - C++11/C++17/C++20 Features" << endl;
    cout << "Cleaner, Safer, More Efficient Code" << endl;
    cout << string(60, '*') << endl;
    
    section1_SmartPointers();
    section2_AutoKeyword();
    section3_RangeBasedFor();
    section4_MoveSemantics();
    section5_Lambdas();
    section6_VariadicTemplates();
    section7_ComparisonOldVsModern();
    section8_RealWorldExample();
    
    cout << "\n" << string(60, '=') << endl;
    cout << "SUMMARY" << endl;
    cout << string(60, '=') << endl;
    cout << "\nKey Modern C++ Features:" << endl;
    cout << "1. Smart pointers - automatic memory management" << endl;
    cout << "2. Auto - type deduction for cleaner code" << endl;
    cout << "3. Range-based for - simpler loops" << endl;
    cout << "4. Move semantics - efficient resource transfer" << endl;
    cout << "5. Lambdas - inline functions for algorithms" << endl;
    cout << "6. Variadic templates - flexible generic code" << endl;
    cout << "\nFor Qt + ECDIS Development:" << endl;
    cout << "  - Use Qt's memory management (QObject)" << endl;
    cout << "  - Use smart pointers for non-Qt data" << endl;
    cout << "  - Use lambdas for signal/slot connections" << endl;
    cout << "  - Prefer range-for for STL containers" << endl;
    cout << "\n✓ Project 0 Complete! Ready for Qt development!" << endl;
    cout << string(60, '*') << endl << endl;
    
    return 0;
}
