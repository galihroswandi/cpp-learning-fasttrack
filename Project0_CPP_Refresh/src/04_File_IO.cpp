/**
 * PROJECT 0 - Program 04: File I/O
 * 
 * This program demonstrates:
 * 1. Reading text files (ifstream)
 * 2. Writing text files (ofstream)
 * 3. Binary file operations
 * 4. File positioning (seek, tell)
 * 5. Structured data in files
 * 6. Error handling for file operations
 * 
 * Compilation:
 *   g++ -std=c++17 -Wall -Wextra 04_File_IO.cpp -o 04_fileio
 * 
 * Run:
 *   ./04_fileio
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// ============================================================================
// SECTION 1: Writing Text Files
// ============================================================================

void section1_WritingTextFiles() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: Writing Text Files (ofstream)" << endl;
    cout << string(60, '=') << endl;
    
    // Create/open file for writing
    ofstream outfile("build/output.txt");
    
    // Check if file opened successfully
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file for writing" << endl;
        return;
    }
    
    cout << "Writing to file: build/output.txt" << endl;
    
    // Write to file (same syntax as cout)
    outfile << "Line 1: Hello from C++ File I/O" << endl;
    outfile << "Line 2: This is a test file" << endl;
    outfile << "Line 3: Numbers: " << 42 << " and " << 3.14 << endl;
    
    // File is automatically closed when outfile goes out of scope
    // (RAII - Resource Acquisition Is Initialization)
    outfile.close();
    
    cout << "File written successfully!" << endl;
}

// ============================================================================
// SECTION 2: Reading Text Files
// ============================================================================

void section2_ReadingTextFiles() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: Reading Text Files (ifstream)" << endl;
    cout << string(60, '=') << endl;
    
    ifstream infile("build/output.txt");
    
    if (!infile.is_open()) {
        cerr << "Error: Could not open file for reading" << endl;
        return;
    }
    
    cout << "Reading from file: build/output.txt\n" << endl;
    
    // Method 1: Read line by line
    cout << "[Method 1] Read line-by-line:" << endl;
    string line;
    int lineNum = 0;
    while (getline(infile, line)) {
        lineNum++;
        cout << "  Line " << lineNum << ": " << line << endl;
    }
    
    infile.close();
}

// ============================================================================
// SECTION 3: Reading Structured Data
// ============================================================================

void section3_StructuredData() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: Reading Structured Data (CSV-like)" << endl;
    cout << string(60, '=') << endl;
    
    // Create a CSV file first
    ofstream csvfile("build/data.csv");
    csvfile << "Name,Age,Score\n";
    csvfile << "Alice,30,95\n";
    csvfile << "Bob,25,87\n";
    csvfile << "Charlie,35,92\n";
    csvfile.close();
    
    cout << "Created CSV file: build/data.csv\n" << endl;
    
    // Read and parse CSV
    ifstream infile("build/data.csv");
    string line;
    vector<vector<string>> data;
    
    cout << "[Reading CSV data]" << endl;
    while (getline(infile, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;
        
        while (getline(ss, cell, ',')) {  // Split by comma
            row.push_back(cell);
        }
        data.push_back(row);
    }
    infile.close();
    
    // Print parsed data
    cout << "\nParsed data:" << endl;
    for (size_t i = 0; i < data.size(); i++) {
        cout << "  Row " << i << ": ";
        for (const auto& cell : data[i]) {
            cout << "[" << cell << "] ";
        }
        cout << endl;
    }
    
    // Process as records (skip header)
    cout << "\nProcessed records:" << endl;
    for (size_t i = 1; i < data.size(); i++) {
        string name = data[i][0];
        int age = stoi(data[i][1]);
        int score = stoi(data[i][2]);
        
        cout << "  " << setw(10) << name 
             << " Age: " << age 
             << " Score: " << score << endl;
    }
}

// ============================================================================
// SECTION 4: Binary File Operations
// ============================================================================

struct Point {
    float x, y, z;
};

void section4_BinaryFiles() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: Binary File Operations" << endl;
    cout << string(60, '=') << endl;
    
    // Write binary data
    cout << "\nWriting binary data..." << endl;
    ofstream binout("build/data.bin", ios::binary);
    
    vector<Point> points = {
        {1.0f, 2.0f, 3.0f},
        {4.0f, 5.0f, 6.0f},
        {7.0f, 8.0f, 9.0f}
    };
    
    // Write number of points
    int count = points.size();
    binout.write(reinterpret_cast<char*>(&count), sizeof(count));
    
    // Write each point
    for (const auto& p : points) {
        binout.write(reinterpret_cast<const char*>(&p.x), sizeof(p.x));
        binout.write(reinterpret_cast<const char*>(&p.y), sizeof(p.y));
        binout.write(reinterpret_cast<const char*>(&p.z), sizeof(p.z));
    }
    binout.close();
    
    cout << "Written " << count << " points to binary file" << endl;
    
    // Read binary data
    cout << "\nReading binary data..." << endl;
    ifstream binin("build/data.bin", ios::binary);
    
    int numPoints;
    binin.read(reinterpret_cast<char*>(&numPoints), sizeof(numPoints));
    cout << "Number of points: " << numPoints << endl;
    
    vector<Point> readPoints;
    for (int i = 0; i < numPoints; i++) {
        Point p;
        binin.read(reinterpret_cast<char*>(&p.x), sizeof(p.x));
        binin.read(reinterpret_cast<char*>(&p.y), sizeof(p.y));
        binin.read(reinterpret_cast<char*>(&p.z), sizeof(p.z));
        readPoints.push_back(p);
    }
    binin.close();
    
    cout << "\nRead points:" << endl;
    for (size_t i = 0; i < readPoints.size(); i++) {
        const auto& p = readPoints[i];
        cout << "  Point " << i << ": (" << p.x << ", " 
             << p.y << ", " << p.z << ")" << endl;
    }
    
    cout << "\nBinary files advantages:" << endl;
    cout << "  - More compact than text" << endl;
    cout << "  - Preserves exact data representation" << endl;
    cout << "  - Faster I/O for large datasets" << endl;
    cout << "  - Essential for ECDIS S-57 files" << endl;
}

// ============================================================================
// SECTION 5: File Positioning
// ============================================================================

void section5_FilePositioning() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: File Positioning (seek, tell)" << endl;
    cout << string(60, '=') << endl;
    
    // Create test file
    ofstream testfile("build/position.txt");
    testfile << "0123456789";  // 10 chars
    testfile.close();
    
    ifstream infile("build/position.txt");
    
    cout << "File content: '0123456789' (10 characters)" << endl;
    
    // Read first 5 characters
    cout << "\nRead first 5 characters:" << endl;
    char buffer[6];
    infile.read(buffer, 5);
    buffer[5] = '\0';
    cout << "  Result: '" << buffer << "'" << endl;
    
    // Get current position
    cout << "\nFile position (tellg): " << infile.tellg() << endl;
    
    // Seek to position 0
    cout << "\nSeek to position 0" << endl;
    infile.seekg(0);
    cout << "  Current position: " << infile.tellg() << endl;
    
    // Read again
    infile.read(buffer, 3);
    buffer[3] = '\0';
    cout << "  Read 3 chars: '" << buffer << "'" << endl;
    
    // Seek to end
    cout << "\nSeek to end:" << endl;
    infile.seekg(0, ios::end);
    cout << "  Current position: " << infile.tellg() << " (file size)" << endl;
    
    // Seek backwards from end
    cout << "\nSeek 2 positions back from end:" << endl;
    infile.seekg(-2, ios::end);
    cout << "  Current position: " << infile.tellg() << endl;
    infile.read(buffer, 2);
    buffer[2] = '\0';
    cout << "  Read: '" << buffer << "'" << endl;
    
    infile.close();
    
    cout << "\nFile seeking modes:" << endl;
    cout << "  - ios::beg: from beginning" << endl;
    cout << "  - ios::cur: from current position" << endl;
    cout << "  - ios::end: from end" << endl;
}

// ============================================================================
// SECTION 6: Error Handling
// ============================================================================

void section6_ErrorHandling() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Error Handling" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nFile stream state flags:" << endl;
    
    ifstream goodfile("build/output.txt");
    cout << "  goodfile.good(): " << goodfile.good() << endl;
    cout << "  goodfile.is_open(): " << goodfile.is_open() << endl;
    goodfile.close();
    
    cout << "\nTrying to open non-existent file:" << endl;
    ifstream badfile("nonexistent.txt");
    cout << "  badfile.is_open(): " << badfile.is_open() << endl;
    cout << "  badfile.fail(): " << badfile.fail() << endl;
    cout << "  badfile.eof(): " << badfile.eof() << endl;
    
    cout << "\nBest practice:" << endl;
    cout << "  if (!file.is_open()) {" << endl;
    cout << "    cerr << \"Error opening file\" << endl;" << endl;
    cout << "    return;" << endl;
    cout << "  }" << endl;
}

// ============================================================================
// SECTION 7: Real-World Example - Data Logger
// ============================================================================

struct Measurement {
    double temperature;
    double humidity;
    double pressure;
    int timestamp;
    
    Measurement(double t, double h, double p, int ts) 
        : temperature(t), humidity(h), pressure(p), timestamp(ts) {}
};

void section7_DataLogger() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 7: Real-World - Data Logger" << endl;
    cout << string(60, '=') << endl;
    
    // Simulate sensor measurements
    vector<Measurement> measurements = {
        Measurement(22.5, 45.0, 1013.25, 1000),
        Measurement(23.1, 46.2, 1013.20, 2000),
        Measurement(21.9, 44.8, 1013.30, 3000),
        Measurement(22.8, 47.1, 1013.15, 4000),
    };
    
    // Write to CSV log
    cout << "\nWriting sensor log..." << endl;
    ofstream logfile("build/sensor_log.csv");
    logfile << "Timestamp,Temperature,Humidity,Pressure\n";
    
    for (const auto& m : measurements) {
        logfile << m.timestamp << ","
                << fixed << setprecision(1) << m.temperature << ","
                << m.humidity << ","
                << m.pressure << "\n";
    }
    logfile.close();
    
    // Read back and process
    cout << "Reading and processing log..." << endl;
    ifstream readlog("build/sensor_log.csv");
    
    string header;
    getline(readlog, header);
    
    double tempSum = 0, tempMin = 999, tempMax = -999;
    int count = 0;
    
    string line;
    while (getline(readlog, line)) {
        stringstream ss(line);
        int ts;
        double temp, hum, pres;
        char comma;
        
        ss >> ts >> comma >> temp >> comma >> hum >> comma >> pres;
        
        tempSum += temp;
        if (temp < tempMin) tempMin = temp;
        if (temp > tempMax) tempMax = temp;
        count++;
    }
    readlog.close();
    
    cout << "\nTemperature statistics:" << endl;
    cout << "  Min: " << fixed << setprecision(1) << tempMin << "°C" << endl;
    cout << "  Max: " << tempMax << "°C" << endl;
    cout << "  Avg: " << (tempSum / count) << "°C" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "FILE I/O - Reading and Writing Files" << endl;
    cout << string(60, '*') << endl;
    
    section1_WritingTextFiles();
    section2_ReadingTextFiles();
    section3_StructuredData();
    section4_BinaryFiles();
    section5_FilePositioning();
    section6_ErrorHandling();
    section7_DataLogger();
    
    cout << "\n" << string(60, '=') << endl;
    cout << "SUMMARY" << endl;
    cout << string(60, '=') << endl;
    cout << "\nKey Takeaways:" << endl;
    cout << "1. Text files: Use ifstream/ofstream with getline" << endl;
    cout << "2. Binary files: Use read/write with reinterpret_cast" << endl;
    cout << "3. Seek/tell: Navigate within files" << endl;
    cout << "4. Always check if file opened successfully" << endl;
    cout << "5. Parse CSV: Use stringstream and getline" << endl;
    cout << "\nFor ECDIS S-57 files:" << endl;
    cout << "  - Use binary file reading (S-57 is binary format)" << endl;
    cout << "  - Use seek to navigate through records" << endl;
    cout << "  - Parse structured data efficiently" << endl;
    cout << "\nNext: Learn Exception Handling for robust code!" << endl;
    cout << string(60, '*') << endl << endl;
    
    return 0;
}
