/**
 * PROJECT 0 - Program 03: STL Containers and Algorithms
 * 
 * This program demonstrates:
 * 1. std::vector - dynamic arrays
 * 2. std::string - strings with powerful methods
 * 3. std::map - key-value data structure (like dictionaries)
 * 4. Iterators - traversing containers
 * 5. Algorithms - common operations (sort, find, transform)
 * 6. Real-world example: Parsing and processing data
 * 
 * STL = Standard Template Library
 * - Provides ready-made, efficient data structures
 * - Heavily used in modern C++ code
 * - Essential for interview and production code
 * 
 * Compilation:
 *   g++ -std=c++17 -Wall -Wextra 03_STL_Containers.cpp -o 03_stl
 * 
 * Run:
 *   ./03_stl
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

// ============================================================================
// SECTION 1: std::vector - Dynamic Arrays
// ============================================================================

void section1_Vector() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: std::vector - Dynamic Arrays" << endl;
    cout << string(60, '=') << endl;
    
    // Vector basics
    vector<int> v;  // Empty vector
    
    cout << "\nAdding elements with push_back():" << endl;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    
    cout << "Vector: ";
    for (int val : v) {  // Range-based for loop (C++11)
        cout << val << " ";
    }
    cout << endl;
    
    cout << "  size() = " << v.size() << " elements" << endl;
    cout << "  capacity() = " << v.capacity() << " (allocated space)" << endl;
    cout << "  v[0] = " << v[0] << endl;
    cout << "  v.front() = " << v.front() << endl;
    cout << "  v.back() = " << v.back() << endl;
    
    // Vector operations
    cout << "\nCommon operations:" << endl;
    v.pop_back();  // Remove last element
    cout << "After pop_back(): ";
    for (int val : v) cout << val << " ";
    cout << endl;
    
    v.insert(v.begin() + 1, 15);  // Insert 15 at position 1
    cout << "After insert(1, 15): ";
    for (int val : v) cout << val << " ";
    cout << endl;
    
    v.erase(v.begin() + 2);  // Erase element at position 2
    cout << "After erase(2): ";
    for (int val : v) cout << val << " ";
    cout << endl;
    
    cout << "\nVector advantages:" << endl;
    cout << "  - Dynamic size (grows as needed)" << endl;
    cout << "  - Fast random access: v[i] is O(1)" << endl;
    cout << "  - Efficient storage" << endl;
    cout << "  - Better than raw C arrays in modern code" << endl;
}

// ============================================================================
// SECTION 2: std::string - Text Manipulation
// ============================================================================

void section2_String() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: std::string - Powerful Text Handling" << endl;
    cout << string(60, '=') << endl;
    
    // String creation
    string s1 = "Hello";
    string s2 = "World";
    
    cout << "\nString basics:" << endl;
    cout << "  s1 = \"" << s1 << "\"" << endl;
    cout << "  s2 = \"" << s2 << "\"" << endl;
    cout << "  s1.length() = " << s1.length() << endl;
    cout << "  s1[0] = '" << s1[0] << "'" << endl;
    
    // String operations
    cout << "\nString operations:" << endl;
    
    string s3 = s1 + " " + s2;  // Concatenation
    cout << "  Concatenation: \"" << s3 << "\"" << endl;
    
    string s4 = s1;
    transform(s4.begin(), s4.end(), s4.begin(), ::toupper);
    cout << "  To uppercase: \"" << s4 << "\"" << endl;
    
    size_t pos = s3.find("World");
    cout << "  Position of 'World': " << pos << endl;
    
    string s5 = s3.substr(0, 5);  // Extract substring
    cout << "  Substring [0:5]: \"" << s5 << "\"" << endl;
    
    string s6 = "42";
    int val = stoi(s6);  // String to integer
    cout << "  Convert \"42\" to int: " << val << endl;
    
    string s7 = to_string(123);  // Integer to string
    cout << "  Convert 123 to string: \"" << s7 << "\"" << endl;
    
    cout << "\nWhy strings > char arrays:" << endl;
    cout << "  - Automatic memory management" << endl;
    cout << "  - Safe concatenation and manipulation" << endl;
    cout << "  - Rich built-in methods" << endl;
    cout << "  - No buffer overflows" << endl;
}

// ============================================================================
// SECTION 3: Iterators - Traversing Containers
// ============================================================================

void section3_Iterators() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: Iterators - Generalized Pointers" << endl;
    cout << string(60, '=') << endl;
    
    vector<int> v = {10, 20, 30, 40, 50};
    
    cout << "\nIterators are like pointers to container elements" << endl;
    cout << "They let us traverse any container in a generic way" << endl;
    
    // Using iterators
    cout << "\nTraversal with iterator:" << endl;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << "  *it = " << *it << endl;
    }
    
    cout << "\nRange-based for (more modern, cleaner):" << endl;
    for (int val : v) {
        cout << "  val = " << val << endl;
    }
    
    cout << "\nIterator operations:" << endl;
    auto it = v.begin();
    cout << "  v.begin() = " << *it << endl;
    
    ++it;  // Move to next element
    cout << "  After ++it: " << *it << endl;
    
    it += 2;  // Move forward by 2
    cout << "  After it += 2: " << *it << endl;
    
    --it;  // Move to previous
    cout << "  After --it: " << *it << endl;
    
    cout << "\nIterator types:" << endl;
    cout << "  - Forward: can move forward only" << endl;
    cout << "  - Bidirectional: can move forward/backward (list)" << endl;
    cout << "  - Random access: ++ and += both work (vector)" << endl;
    cout << "  - Input/Output: for reading/writing streams" << endl;
}

// ============================================================================
// SECTION 4: std::map - Key-Value Pairs
// ============================================================================

void section4_Map() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: std::map - Dictionary/Hash Map" << endl;
    cout << string(60, '=') << endl;
    
    // Map creation
    map<string, int> ages;  // Key: string (name), Value: int (age)
    
    cout << "\nAdding key-value pairs:" << endl;
    ages["Alice"] = 30;
    ages["Bob"] = 25;
    ages["Charlie"] = 35;
    
    cout << "  ages[\"Alice\"] = " << ages["Alice"] << endl;
    cout << "  ages[\"Bob\"] = " << ages["Bob"] << endl;
    
    cout << "\nIterating through map:" << endl;
    for (auto& p : ages) {  // p is pair<const string, int>
        cout << "  " << p.first << ": " << p.second << " years old" << endl;
    }
    
    cout << "\nMap operations:" << endl;
    cout << "  size() = " << ages.size() << endl;
    
    // Check if key exists
    if (ages.find("Alice") != ages.end()) {
        cout << "  Alice is in the map" << endl;
    }
    
    // Erase a key
    ages.erase("Bob");
    cout << "  After erase(\"Bob\"): size = " << ages.size() << endl;
    
    cout << "\nWhy use map:" << endl;
    cout << "  - Fast lookup: O(log n)" << endl;
    cout << "  - Keys must be unique" << endl;
    cout << "  - Automatically sorted by key" << endl;
    cout << "  - Alternative: unordered_map for O(1) average lookup" << endl;
}

// ============================================================================
// SECTION 5: Algorithms
// ============================================================================

void section5_Algorithms() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: STL Algorithms" << endl;
    cout << string(60, '=') << endl;
    
    vector<int> v = {30, 10, 40, 20, 50, 5, 15};
    
    cout << "\nOriginal vector: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    
    // Sort
    cout << "\nAfter sort():" << endl;
    sort(v.begin(), v.end());
    for (int x : v) cout << x << " ";
    cout << endl;
    
    // Find
    cout << "\nFind specific element:" << endl;
    auto it = find(v.begin(), v.end(), 20);
    if (it != v.end()) {
        cout << "  Found 20 at position: " << (it - v.begin()) << endl;
    }
    
    // Count
    cout << "\nCount elements:" << endl;
    int count20 = std::count(v.begin(), v.end(), 20);
    cout << "  Count of 20: " << count20 << endl;
    
    // Transform (modify each element)
    cout << "\nTransform (multiply each by 2):" << endl;
    vector<int> doubled;
    transform(v.begin(), v.end(), back_inserter(doubled),
              [](int x) { return x * 2; });  // Lambda function
    for (int x : doubled) cout << x << " ";
    cout << endl;
    
    // Reverse
    cout << "\nReverse:" << endl;
    reverse(v.begin(), v.end());
    for (int x : v) cout << x << " ";
    cout << endl;
    
    cout << "\nCommon algorithms:" << endl;
    cout << "  - sort, stable_sort" << endl;
    cout << "  - find, find_if, count, count_if" << endl;
    cout << "  - transform, copy, copy_if" << endl;
    cout << "  - reverse, rotate, unique" << endl;
    cout << "  - min_element, max_element, accumulate" << endl;
}

// ============================================================================
// SECTION 6: Real-World Example - Data Parsing
// ============================================================================

struct Student {
    string name;
    int id;
    double gpa;
    
    // Constructor
    Student(const string& n, int i, double g) 
        : name(n), id(i), gpa(g) {}
};

void section6_RealWorldExample() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Real-World - Student Record System" << endl;
    cout << string(60, '=') << endl;
    
    // Create records
    vector<Student> students;
    students.emplace_back("Alice", 101, 3.8);
    students.emplace_back("Bob", 102, 3.5);
    students.emplace_back("Charlie", 103, 3.9);
    students.emplace_back("Diana", 104, 3.7);
    students.emplace_back("Eve", 105, 3.6);
    
    cout << "\nStudent records:" << endl;
    for (const auto& s : students) {
        cout << "  " << setw(10) << s.name 
             << " ID: " << s.id 
             << " GPA: " << fixed << setprecision(2) << s.gpa << endl;
    }
    
    // Sort by GPA (descending)
    cout << "\nSorted by GPA (highest first):" << endl;
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.gpa > b.gpa;  // Descending
         });
    
    for (const auto& s : students) {
        cout << "  " << setw(10) << s.name 
             << " ID: " << s.id 
             << " GPA: " << fixed << setprecision(2) << s.gpa << endl;
    }
    
    // Find high achievers (GPA > 3.7)
    cout << "\nHigh achievers (GPA > 3.7):" << endl;
    for (const auto& s : students) {
        if (s.gpa > 3.7) {
            cout << "  " << s.name << " (" << fixed << setprecision(2) 
                 << s.gpa << ")" << endl;
        }
    }
    
    // Calculate average GPA
    cout << "\nStatistics:" << endl;
    double totalGPA = 0;
    for (const auto& s : students) {
        totalGPA += s.gpa;
    }
    double avgGPA = totalGPA / students.size();
    cout << "  Average GPA: " << fixed << setprecision(2) << avgGPA << endl;
    
    // Create map for quick lookup by ID
    cout << "\nQuick lookup by ID:" << endl;
    map<int, Student*> byId;
    for (auto& s : students) {
        byId[s.id] = &s;
    }
    
    int searchId = 103;
    if (byId.find(searchId) != byId.end()) {
        cout << "  ID " << searchId << " is " << byId[searchId]->name << endl;
    }
}

// ============================================================================
// SECTION 7: Lambda Functions (Modern C++)
// ============================================================================

void section7_Lambdas() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: Lambda Functions (Anonymous Functions)" << endl;
    cout << string(60, '=') << endl;
    
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "\nLambdas are small, inline functions:" << endl;
    cout << "  [capture] (parameters) { body }" << endl;
    
    // Example 1: Simple lambda
    cout << "\nFilter numbers > 5:" << endl;
    for (int x : v) {
        if (x > 5) {  // Inline condition
            cout << x << " ";
        }
    }
    cout << endl;
    
    // More elegantly with find_if and lambda
    cout << "\nUsing find_if with lambda:" << endl;
    auto it = find_if(v.begin(), v.end(), 
                     [](int x) { return x > 5; });  // Lambda!
    cout << "  First element > 5: " << *it << endl;
    
    // Example 2: Lambda with capture
    cout << "\nLambda with capture variable:" << endl;
    int threshold = 6;
    auto above_threshold = [threshold](int x) { 
        return x > threshold; 
    };
    
    for (int x : v) {
        if (above_threshold(x)) {
            cout << x << " ";
        }
    }
    cout << endl;
    
    // Example 3: Transform with lambda
    cout << "\nTransform with lambda:" << endl;
    vector<int> squared;
    transform(v.begin(), v.end(), back_inserter(squared),
              [](int x) { return x * x; });
    for (int x : squared) cout << x << " ";
    cout << endl;
    
    cout << "\nWhen to use lambdas:" << endl;
    cout << "  - Short inline functions" << endl;
    cout << "  - Algorithm predicates (sort, find, etc.)" << endl;
    cout << "  - Callbacks and event handlers (very common in Qt!)" << endl;
}

// ============================================================================
// SECTION 8: Common Mistakes
// ============================================================================

void section8_CommonMistakes() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 8: Common STL Mistakes" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\n[MISTAKE 1] Accessing out-of-bounds" << endl;
    vector<int> v = {1, 2, 3};
    cout << "  v[5] = undefined behavior (should check v.size())" << endl;
    cout << "  FIX: Use v.at(5) which throws exception if out of bounds" << endl;
    
    cout << "\n[MISTAKE 2] Invalidating iterators" << endl;
    cout << "  for (auto it = v.begin(); it != v.end(); ++it) {" << endl;
    cout << "    v.erase(it);  // THIS INVALIDATES it!" << endl;
    cout << "  }" << endl;
    
    cout << "\n[MISTAKE 3] Comparing map keys" << endl;
    cout << "  Maps are automatically sorted by key" << endl;
    cout << "  If you insert out of order, retrieval is still O(log n)" << endl;
    
    cout << "\n[MISTAKE 4] Not clearing vectors before reuse" << endl;
    vector<int> myVec = {1, 2, 3};
    myVec.clear();  // Good practice
    myVec.push_back(4);
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "STL - STANDARD TEMPLATE LIBRARY" << endl;
    cout << "Containers, Iterators, Algorithms" << endl;
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
    cout << "SUMMARY" << endl;
    cout << string(60, '=') << endl;
    cout << "\nKey Takeaways:" << endl;
    cout << "1. vector = dynamic arrays (most common)" << endl;
    cout << "2. string = text with powerful methods" << endl;
    cout << "3. map = sorted key-value dictionary" << endl;
    cout << "4. Iterators = generalized pointers" << endl;
    cout << "5. Algorithms = functions operating on containers" << endl;
    cout << "6. Lambdas = inline anonymous functions" << endl;
    cout << "\nSTL containers and algorithms are:" << endl;
    cout << "  - Well-optimized (battle-tested)" << endl;
    cout << "  - Generic (work with any type)" << endl;
    cout << "  - Safe (bounds checking available)" << endl;
    cout << "\nNext: Learn File I/O for data persistence!" << endl;
    cout << string(60, '*') << endl << endl;
    
    return 0;
}
