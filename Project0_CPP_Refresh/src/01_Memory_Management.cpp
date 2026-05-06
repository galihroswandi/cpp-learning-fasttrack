/**
 * PROJECT 0 - Program 01: Memory Management Fundamentals
 * 
 * This program demonstrates:
 * 1. Stack vs Heap allocation
 * 2. Pointers and dereferencing
 * 3. References
 * 4. Dynamic memory with new/delete
 * 5. Common memory management mistakes
 * 6. Memory leak detection concepts
 * 
 * Compilation:
 *   g++ -std=c++17 -Wall -Wextra 01_Memory_Management.cpp -o 01_memory
 * 
 * Run:
 *   ./01_memory
 */

#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================================
// SECTION 1: Stack vs Heap - Basics
// ============================================================================

void section1_StackVsHeap() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: Stack vs Heap Allocation" << endl;
    cout << string(60, '=') << endl;
    
    // STACK ALLOCATION - Automatic, fast, limited scope
    int stackVar = 42;
    double stackArray[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    
    cout << "\n[STACK] stackVar = " << stackVar << endl;
    cout << "[STACK] Address of stackVar: " << &stackVar << endl;
    cout << "[STACK] stackArray[0] = " << stackArray[0] << endl;
    
    // HEAP ALLOCATION - Manual, flexible, need to delete
    int* heapVar = new int(42);               // Create int on heap
    double* heapArray = new double[5]{1.1, 2.2, 3.3, 4.4, 5.5};  // Create array on heap
    
    cout << "\n[HEAP] *heapVar = " << *heapVar << endl;
    cout << "[HEAP] Address (heapVar pointer) = " << heapVar << endl;
    cout << "[HEAP] Address of heapVar itself = " << &heapVar << endl;
    cout << "[HEAP] heapArray[0] = " << heapArray[0] << endl;
    
    // IMPORTANT: Delete heap memory
    delete heapVar;              // Delete single value
    delete[] heapArray;          // Delete array (note the [])
    
    // heapVar and heapArray now point to freed memory (dangling pointers)
    // NEVER access them after delete!
}

// ============================================================================
// SECTION 2: Pointers - Understanding Address & Dereference
// ============================================================================

void section2_PointersBasics() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: Pointers - & (address-of) and * (dereference)" << endl;
    cout << string(60, '=') << endl;
    
    int x = 100;
    int* ptr = &x;  // ptr HOLDS the address of x
    
    cout << "\nVariable x:" << endl;
    cout << "  x value: " << x << endl;
    cout << "  address of x: " << &x << endl;
    
    cout << "\nPointer ptr = &x:" << endl;
    cout << "  ptr value (address): " << ptr << endl;
    cout << "  *ptr (what ptr points to): " << *ptr << endl;
    cout << "  address of ptr itself: " << &ptr << endl;
    
    // Modifying through pointer
    *ptr = 200;  // This modifies x
    cout << "\nAfter *ptr = 200:" << endl;
    cout << "  x = " << x << " (changed through pointer!)" << endl;
    cout << "  *ptr = " << *ptr << endl;
    
    // Multiple pointers to same variable
    int* ptr2 = &x;
    cout << "\nMultiple pointers to same variable:" << endl;
    cout << "  ptr and ptr2 both point to x" << endl;
    cout << "  *ptr = " << *ptr << ", *ptr2 = " << *ptr2 << endl;
    
    *ptr2 = 500;
    cout << "  After *ptr2 = 500:" << endl;
    cout << "  x = " << x << " (all pointers see the change)" << endl;
}

// ============================================================================
// SECTION 3: References - Safer Alternative to Pointers
// ============================================================================

void section3_References() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: References - Safe Aliases" << endl;
    cout << string(60, '=') << endl;
    
    int original = 42;
    int& ref = original;  // ref is an ALIAS to original
    
    cout << "\nReference ref = original:" << endl;
    cout << "  original = " << original << endl;
    cout << "  ref = " << ref << endl;
    
    // Unlike pointers, references can't be reassigned
    int other = 99;
    // ref = other;  // This does NOT make ref point to 'other'
                     // Instead, it assigns 99 to original!
    ref = other;  // Actually: original = 99
    
    cout << "\nAfter ref = other (where other = 99):" << endl;
    cout << "  original = " << original << " (ref changes original)" << endl;
    cout << "  ref = " << ref << endl;
    cout << "  other = " << other << endl;
    
    cout << "\nKey differences - Pointers vs References:" << endl;
    cout << "  Pointers: Can be null, can be reassigned, need * to access" << endl;
    cout << "  References: Can't be null, can't be reassigned, transparent access" << endl;
}

// ============================================================================
// SECTION 4: Pointer Arithmetic & Array Access
// ============================================================================

void section4_PointerArithmetic() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: Pointer Arithmetic" << endl;
    cout << string(60, '=') << endl;
    
    int arr[5] = {10, 20, 30, 40, 50};
    int* ptr = arr;  // Array name decays to pointer to first element
    
    cout << "\nArray arr[5] = {10, 20, 30, 40, 50}" << endl;
    cout << "int* ptr = arr;" << endl;
    
    cout << "\nPointer arithmetic:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  ptr[" << i << "] = " << ptr[i];
        cout << " (or *(ptr+" << i << ") = " << *(ptr + i) << ")" << endl;
    }
    
    cout << "\nMemory addresses:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  &arr[" << i << "] = " << &arr[i] << endl;
    }
    
    cout << "\nNote: Pointer arithmetic in bytes, but scaled by type size:" << endl;
    cout << "  ptr + 1 moves sizeof(int) bytes forward" << endl;
}

// ============================================================================
// SECTION 5: Functions with Pointers and References
// ============================================================================

// Function that takes pointer - can modify original variable
void incrementByPointer(int* ptr, int amount) {
    *ptr += amount;  // Modify what pointer points to
}

// Function that takes reference - can modify, cleaner syntax
void incrementByReference(int& ref, int amount) {
    ref += amount;   // Direct modification, no * needed
}

// Function that takes value - CANNOT modify original
void incrementByValue(int val, int amount) {
    val += amount;   // Only modifies local copy
}

void section5_FunctionParameters() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: Function Parameters - Pointer vs Reference vs Value" << endl;
    cout << string(60, '=') << endl;
    
    int x = 100;
    int y = 100;
    int z = 100;
    
    cout << "\nOriginal values: x=100, y=100, z=100" << endl;
    
    incrementByPointer(&x, 50);    // Pass address
    incrementByReference(y, 50);   // Pass reference
    incrementByValue(z, 50);       // Pass copy
    
    cout << "\nAfter increment by 50:" << endl;
    cout << "  x (by pointer) = " << x << " (MODIFIED)" << endl;
    cout << "  y (by reference) = " << y << " (MODIFIED)" << endl;
    cout << "  z (by value) = " << z << " (NOT modified - only local copy)" << endl;
    
    cout << "\nWhen to use:" << endl;
    cout << "  - Pointer: Legacy code, need null-check possibility, optional output" << endl;
    cout << "  - Reference: Modern code, cleaner syntax, guaranteed non-null" << endl;
    cout << "  - Value: When function shouldn't modify original, small types" << endl;
}

// ============================================================================
// SECTION 6: Dynamic Arrays - More Complex Heap Usage
// ============================================================================

void section6_DynamicArrays() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Dynamic Arrays on Heap" << endl;
    cout << string(60, '=') << endl;
    
    int n = 5;
    
    // Create dynamic array on heap
    int* arr = new int[n];
    
    // Initialize it
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;  // 10, 20, 30, 40, 50
    }
    
    cout << "\nDynamic array (size=" << n << "): ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Important: Use delete[] for arrays (not delete)
    delete[] arr;
    
    cout << "\nCRITICAL: Always delete[] arrays created with new[]" << endl;
    cout << "If you use delete (without []), it's undefined behavior!" << endl;
}

// ============================================================================
// SECTION 7: Common Memory Mistakes (and how to spot them)
// ============================================================================

void section7_MemoryMistakes() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: Common Memory Mistakes" << endl;
    cout << string(60, '=') << endl;
    
    // MISTAKE 1: Memory leak - allocate but never delete
    cout << "\n[MISTAKE 1] Memory Leak:" << endl;
    {
        int* leaked = new int(42);
        // Forgot to delete - memory lost!
        // In real code, this would accumulate and exhaust memory
        cout << "  int* leaked = new int(42);" << endl;
        cout << "  // Forgot delete - memory leaked!" << endl;
        cout << "  (We'll clean it up to not actually leak in this demo)" << endl;
        delete leaked;  // Clean up for demo
    }
    
    // MISTAKE 2: Dangling pointer - use after delete
    cout << "\n[MISTAKE 2] Dangling Pointer:" << endl;
    {
        int* ptr = new int(42);
        cout << "  int* ptr = new int(42);" << endl;
        cout << "  delete ptr;  // ptr now dangling!" << endl;
        cout << "  std::cout << *ptr;  // UNDEFINED BEHAVIOR - may crash!" << endl;
        delete ptr;
        // We don't actually dereference here to avoid crash in demo
    }
    
    // MISTAKE 3: Double delete - delete same pointer twice
    cout << "\n[MISTAKE 3] Double Delete:" << endl;
    {
        int* ptr = new int(42);
        cout << "  int* ptr = new int(42);" << endl;
        cout << "  delete ptr;" << endl;
        cout << "  delete ptr;  // CRASH - deleting already freed memory!" << endl;
        delete ptr;
        // Don't demonstrate actual crash
    }
    
    // MISTAKE 4: Wrong delete for array
    cout << "\n[MISTAKE 4] delete vs delete[] mismatch:" << endl;
    {
        int* arr = new int[5];
        cout << "  int* arr = new int[5];" << endl;
        cout << "  delete arr;  // WRONG! Should be delete[]" << endl;
        cout << "  (undefined behavior, may leak or crash)" << endl;
        delete[] arr;  // Correct way
    }
    
    cout << "\nPREVENTION with Modern C++:" << endl;
    cout << "  Use smart pointers (std::unique_ptr, std::shared_ptr)" << endl;
    cout << "  They auto-delete when going out of scope" << endl;
}

// ============================================================================
// SECTION 8: Smart Pointers (Modern C++ Solution)
// ============================================================================

#include <memory>

void section8_SmartPointers() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 8: Smart Pointers - Modern C++ (C++11+)" << endl;
    cout << string(60, '=') << endl;
    
    // std::unique_ptr - Exclusive ownership
    cout << "\nstd::unique_ptr (exclusive ownership):" << endl;
    {
        std::unique_ptr<int> uptr(new int(42));  // or: std::make_unique<int>(42)
        cout << "  Created: std::unique_ptr<int> uptr(new int(42))" << endl;
        cout << "  Value: " << *uptr << endl;
        cout << "  Address: " << uptr.get() << endl;
        // Automatically deletes when uptr goes out of scope
    }
    cout << "  (Auto-deleted when out of scope - no manual delete!)" << endl;
    
    // std::shared_ptr - Shared ownership
    cout << "\nstd::shared_ptr (shared ownership):" << endl;
    {
        std::shared_ptr<int> sptr1(new int(99));
        std::shared_ptr<int> sptr2 = sptr1;  // Both share ownership
        
        cout << "  sptr1 and sptr2 both point to same int(99)" << endl;
        cout << "  sptr1 use_count: " << sptr1.use_count() << endl;  // Should be 2
        cout << "  *sptr1 = " << *sptr1 << ", *sptr2 = " << *sptr2 << endl;
        // Auto-deletes only when last shared_ptr is destroyed
    }
    cout << "  (Auto-deleted when all shared_ptrs are destroyed)" << endl;
    
    cout << "\nAdvantages of smart pointers:" << endl;
    cout << "  ✓ No manual delete needed" << endl;
    cout << "  ✓ Exception safe (deletes even if exception thrown)" << endl;
    cout << "  ✓ Harder to make memory mistakes" << endl;
    cout << "  ✓ Clear ownership semantics" << endl;
}

// ============================================================================
// MAIN - Run all sections
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "C++ MEMORY MANAGEMENT FUNDAMENTALS" << endl;
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
    cout << "SUMMARY" << endl;
    cout << string(60, '=') << endl;
    cout << "\nKey Takeaways:" << endl;
    cout << "1. Stack: automatic, fast, limited scope" << endl;
    cout << "2. Heap: flexible, manual management, potential for errors" << endl;
    cout << "3. Pointers: hold addresses, flexible but error-prone" << endl;
    cout << "4. References: safer aliases, modern C++ preference" << endl;
    cout << "5. Smart pointers: automatic memory management, use in modern code" << endl;
    cout << "\nNext: Learn OOP with classes and inheritance!" << endl;
    cout << string(60, '*') << endl << endl;
    
    return 0;
}
