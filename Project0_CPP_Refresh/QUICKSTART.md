# Project 0: Quick Start Guide

## Setup & Compilation

### Option 1: Using CMake (Recommended)
```bash
cd /home/galih/Documents/Explore/belajar-cpp/Project0_CPP_Refresh
mkdir -p build
cd build
cmake ..
make
```

### Option 2: Manual g++ Compilation
```bash
cd /home/galih/Documents/Explore/belajar-cpp/Project0_CPP_Refresh

# Compile each program
g++ -std=c++17 -Wall -Wextra src/01_Memory_Management.cpp -o build/01_memory
g++ -std=c++17 -Wall -Wextra src/02_OOP_Classes.cpp -o build/02_oop
g++ -std=c++17 -Wall -Wextra src/03_STL_Containers.cpp -o build/03_stl
g++ -std=c++17 -Wall -Wextra src/04_File_IO.cpp -o build/04_fileio
g++ -std=c++17 -Wall -Wextra src/05_Exception_Handling.cpp -o build/05_exceptions
g++ -std=c++17 -Wall -Wextra src/06_Modern_CPP.cpp -o build/06_modern
```

## Running Programs

### From CMake build
```bash
cd build
./bin/01_memory
./bin/02_oop
./bin/03_stl
./bin/04_fileio
./bin/05_exceptions
./bin/06_modern
```

### From manual compilation
```bash
./build/01_memory
./build/02_oop
./build/03_stl
./build/04_fileio
./build/05_exceptions
./build/06_modern
```

## Learning Path

Follow this order for best understanding:

1. **01_Memory_Management** (15 min)
   - Understand stack vs heap
   - Learn pointers and references
   - Know when memory leaks happen
   
2. **02_OOP_Classes** (20 min)
   - Understand class hierarchy
   - Learn inheritance and polymorphism
   - See virtual functions in action
   
3. **03_STL_Containers** (20 min)
   - Practice with vector, map, string
   - Learn iterators
   - Use algorithms
   
4. **04_File_IO** (15 min)
   - Read/write text and binary files
   - Parse CSV-like data
   - Understand seeking in files
   
5. **05_Exception_Handling** (10 min)
   - Try-catch blocks
   - Custom exceptions
   - RAII pattern
   
6. **06_Modern_CPP** (20 min)
   - Smart pointers
   - Auto keyword
   - Lambdas
   - Move semantics

**Total: ~100 minutes of learning**

## Tips for Learning

1. **Read all output carefully** - Each program explains concepts thoroughly
2. **Run programs one by one** - Don't skip any
3. **Modify and experiment** - Change values, add prints, test edge cases
4. **Take notes** - Write down key concepts you learn
5. **Relate to Web Dev** - Connect C++ concepts to JavaScript/Web knowledge

## Common Compilation Issues

### "command not found: g++"
```bash
# Install compiler
sudo apt install -y build-essential
```

### "command not found: cmake"
```bash
# Install cmake
sudo apt install -y cmake
```

### Permission denied
```bash
# Make executable
chmod +x build/01_memory
./build/01_memory
```

## What to Look For in Output

Each program demonstrates:
- **CLEAR EXPLANATION** of the concept
- **VISUAL DIAGRAMS** (in ASCII art)
- **CODE EXAMPLES** with side-by-side comparisons
- **REAL-WORLD APPLICATIONS** 
- **COMMON MISTAKES** and how to avoid them

## Next After Project 0

Once you've completed all 6 programs and understand the concepts:
- Move to **Project 1: Qt Basics**
- Then **Project 2: Graphics & Drawing**
- Then **Project 3: S-57 Parser**
- Finally **Project 4: Full ECDIS Integration**

---

**Ready to start? Run your first program:**
```bash
cd /home/galih/Documents/Explore/belajar-cpp/Project0_CPP_Refresh/build
./01_memory
```

The journey to mastering C++ begins! 🚀
