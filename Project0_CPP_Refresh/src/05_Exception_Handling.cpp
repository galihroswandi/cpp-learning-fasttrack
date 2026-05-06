/**
 * PROJECT 0 - Program 05: Exception Handling
 * 
 * This program demonstrates:
 * 1. Try-catch blocks
 * 2. Throwing exceptions
 * 3. Standard exception hierarchy
 * 4. Custom exception classes
 * 5. Exception safety guarantees
 * 6. RAII pattern for resource cleanup
 * 
 * Key concept: Gracefully handle errors without crashing
 * 
 * Compilation:
 *   g++ -std=c++17 -Wall -Wextra 05_Exception_Handling.cpp -o 05_exceptions
 * 
 * Run:
 *   ./05_exceptions
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

void section1_BasicTryCatch() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: Basic Try-Catch Blocks" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nDivision by zero without exception handling:" << endl;
    cout << "  int result = 10 / 0;  // Undefined behavior!" << endl;
    
    cout << "\nWith exception handling:" << endl;
    try {
        int dividend = 10;
        int divisor = 0;
        
        if (divisor == 0) {
            throw invalid_argument("Cannot divide by zero!");
        }
        
        int result = dividend / divisor;
        cout << "  Result: " << result << endl;
    }
    catch (const invalid_argument& e) {
        cout << "  Caught exception: " << e.what() << endl;
        cout << "  Program continues normally" << endl;
    }
    
    cout << "\nKey concept:" << endl;
    cout << "  try { } - code that might throw" << endl;
    cout << "  catch (type e) { } - handle specific exception type" << endl;
}

// ============================================================================
// SECTION 2: Multiple Catch Blocks
// ============================================================================

int safeDivide(int a, int b) {
    if (b == 0) {
        throw invalid_argument("Divisor cannot be zero");
    }
    return a / b;
}

string getString(int index) {
    if (index < 0 || index > 5) {
        throw out_of_range("Index out of range");
    }
    string arr[] = {"one", "two", "three", "four", "five"};
    return arr[index];
}

void section2_MultipleCatches() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: Multiple Catch Blocks" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nTesting division (valid):" << endl;
    try {
        int result = safeDivide(10, 2);
        cout << "  10 / 2 = " << result << endl;
    }
    catch (const invalid_argument& e) {
        cout << "  Caught: " << e.what() << endl;
    }
    
    cout << "\nTesting division (invalid):" << endl;
    try {
        int result = safeDivide(10, 0);
        cout << "  10 / 0 = " << result << endl;
    }
    catch (const invalid_argument& e) {
        cout << "  Caught: " << e.what() << endl;
    }
    
    cout << "\nTesting array access (valid):" << endl;
    try {
        string s = getString(2);
        cout << "  Index 2: " << s << endl;
    }
    catch (const out_of_range& e) {
        cout << "  Caught: " << e.what() << endl;
    }
    
    cout << "\nTesting array access (invalid):" << endl;
    try {
        string s = getString(10);
        cout << "  Index 10: " << s << endl;
    }
    catch (const out_of_range& e) {
        cout << "  Caught: " << e.what() << endl;
    }
    
    cout << "\nCatching base exception class:" << endl;
    try {
        safeDivide(5, 0);
    }
    catch (const exception& e) {
        cout << "  Caught base exception: " << e.what() << endl;
        cout << "  This catches ANY standard exception" << endl;
    }
}

// ============================================================================
// SECTION 3: Standard Exception Hierarchy
// ============================================================================

void section3_ExceptionHierarchy() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: Standard Exception Hierarchy" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nC++ Standard Exception Hierarchy:" << endl;
    cout << "\n  exception" << endl;
    cout << "    ├─ logic_error" << endl;
    cout << "    │  ├─ invalid_argument" << endl;
    cout << "    │  ├─ out_of_range" << endl;
    cout << "    │  └─ length_error" << endl;
    cout << "    │" << endl;
    cout << "    └─ runtime_error" << endl;
    cout << "       ├─ range_error" << endl;
    cout << "       ├─ overflow_error" << endl;
    cout << "       └─ underflow_error" << endl;
    
    cout << "\nCommon exceptions:" << endl;
    cout << "  invalid_argument - parameter is invalid" << endl;
    cout << "  out_of_range - index/value out of valid range" << endl;
    cout << "  runtime_error - unexpected runtime situation" << endl;
    cout << "  logic_error - logic/design error" << endl;
}

// ============================================================================
// SECTION 4: Custom Exception Classes
// ============================================================================

class FileException : public exception {
private:
    string message;
    
public:
    FileException(const string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
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
        static string msg;
        msg = "Validation error in field '" + field + "': " + reason;
        return msg.c_str();
    }
};

void section4_CustomExceptions() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: Custom Exception Classes" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nCustom exceptions allow domain-specific error handling:" << endl;
    
    // Example 1: File exception
    cout << "\n[FileException]" << endl;
    try {
        throw FileException("Could not open configuration file");
    }
    catch (const FileException& e) {
        cout << "  Caught FileException: " << e.what() << endl;
    }
    
    // Example 2: Validation exception
    cout << "\n[ValidationException]" << endl;
    try {
        string email = "invalid_email";
        if (email.find('@') == string::npos) {
            throw ValidationException("email", "Missing @ symbol");
        }
    }
    catch (const ValidationException& e) {
        cout << "  Caught ValidationException: " << e.what() << endl;
    }
    
    // Example 3: Hierarchy
    cout << "\n[Exception Hierarchy]" << endl;
    cout << "Catching base exception catches all derived:" << endl;
    try {
        throw FileException("General file error");
    }
    catch (const exception& e) {
        cout << "  Caught as exception: " << e.what() << endl;
    }
}

// ============================================================================
// SECTION 5: Exception Safety - RAII Pattern
// ============================================================================

class Resource {
private:
    int* buffer;
    
public:
    Resource(int size) {
        cout << "    [Allocating buffer of size " << size << "]" << endl;
        buffer = new int[size];
    }
    
    ~Resource() {
        cout << "    [Freeing buffer]" << endl;
        delete[] buffer;
    }
    
    void doSomething() {
        cout << "    [Using resource]" << endl;
    }
};

void section5_RAIIPattern() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: RAII - Resource Acquisition Is Initialization" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nRAII principle:" << endl;
    cout << "  - Resource allocated in constructor" << endl;
    cout << "  - Resource freed in destructor" << endl;
    cout << "  - Automatic cleanup even if exception occurs" << endl;
    
    cout << "\nExample - Resource with exception:" << endl;
    try {
        {
            Resource r(100);  // Constructor runs
            r.doSomething();
            
            // Exception thrown
            throw runtime_error("Oops!");
            
            // Destructor still runs! (cleanup happens)
        }
    }
    catch (const exception& e) {
        cout << "  Exception caught: " << e.what() << endl;
        cout << "  But resource was cleaned up automatically!" << endl;
    }
}

// ============================================================================
// SECTION 6: Exception Safety Guarantees
// ============================================================================

void section6_ExceptionGuarantees() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Exception Safety Guarantees" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nException safety levels:" << endl;
    
    cout << "\n1. No-throw guarantee" << endl;
    cout << "   - Function never throws" << endl;
    cout << "   - Example: int doubleValue(int x) { return x * 2; }" << endl;
    
    cout << "\n2. Strong guarantee" << endl;
    cout << "   - Either succeeds completely or has no effect" << endl;
    cout << "   - 'All or nothing' - like database transactions" << endl;
    cout << "   - Example: vector.push_back() with potential reallocation" << endl;
    
    cout << "\n3. Basic guarantee" << endl;
    cout << "   - If exception thrown, object remains valid" << endl;
    cout << "   - But may be in different state" << endl;
    cout << "   - Example: partial file write before error" << endl;
    
    cout << "\n4. No guarantee (Bad!)" << endl;
    cout << "   - Anything could happen on exception" << endl;
    cout << "   - Don't write code like this" << endl;
}

// ============================================================================
// SECTION 7: File Operations with Exception Handling
// ============================================================================

void safeReadFile(const string& filename) {
    try {
        ifstream file(filename);
        
        if (!file.is_open()) {
            throw FileException("Cannot open file: " + filename);
        }
        
        string line;
        int lineNum = 0;
        
        while (getline(file, line)) {
            lineNum++;
            if (line.empty()) {
                throw ValidationException("line", "Empty line at " + to_string(lineNum));
            }
        }
        
        file.close();
    }
    catch (const FileException& e) {
        cout << "    File error: " << e.what() << endl;
    }
    catch (const ValidationException& e) {
        cout << "    Validation error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "    Unexpected error: " << e.what() << endl;
    }
}

void section7_FileHandling() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: Robust File Handling" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nAttempting to read non-existent file:" << endl;
    safeReadFile("build/nonexistent.txt");
    
    cout << "\nApplication continues despite error!" << endl;
}

// ============================================================================
// SECTION 8: Best Practices
// ============================================================================

void section8_BestPractices() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 8: Exception Handling Best Practices" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\n✓ DO:" << endl;
    cout << "  - Use specific exception types" << endl;
    cout << "  - Catch by const reference" << endl;
    cout << "  - Use RAII for resource management" << endl;
    cout << "  - Document exception guarantees" << endl;
    cout << "  - Cleanup properly before re-throwing" << endl;
    
    cout << "\n✗ DON'T:" << endl;
    cout << "  - Catch by value (can cause slicing)" << endl;
    cout << "  - Catch all exceptions (...) silently" << endl;
    cout << "  - Use exceptions for normal control flow" << endl;
    cout << "  - Throw pointers or char*" << endl;
    cout << "  - Write code that can't meet some guarantee" << endl;
    
    cout << "\n  catch (...) { }  // Catches everything - dangerous!" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "EXCEPTION HANDLING - Robust Error Management" << endl;
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
    cout << "SUMMARY" << endl;
    cout << string(60, '=') << endl;
    cout << "\nKey Takeaways:" << endl;
    cout << "1. Use try-catch to handle errors gracefully" << endl;
    cout << "2. Catch specific exceptions, then general" << endl;
    cout << "3. Always catch by const reference" << endl;
    cout << "4. RAII ensures cleanup even on exception" << endl;
    cout << "5. Provide exception safety guarantees" << endl;
    cout << "\nFor ECDIS Development:" << endl;
    cout << "  - Validate all input files" << endl;
    cout << "  - Use exceptions for real errors" << endl;
    cout << "  - Don't let parse errors crash the app" << endl;
    cout << "  - Log errors for debugging" << endl;
    cout << "\nNext: Learn Modern C++ Features for cleaner code!" << endl;
    cout << string(60, '*') << endl << endl;
    
    return 0;
}
