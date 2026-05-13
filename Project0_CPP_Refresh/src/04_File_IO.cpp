/**
 * PROJECT 0 - Program 04: File I/O
 *
 * Topik:
 * 1. Menulis text file (ofstream)
 * 2. Membaca text file (ifstream)
 * 3. Parsing data terstruktur (CSV)
 * 4. Binary file operations
 * 5. File positioning (seek, tell)
 * 6. Error handling untuk file operations
 *
 * Build: cd build && cmake .. && make 04_fileio
 * Run:   ./build/bin/04_fileio
 */

/**
 * ============================================================
 * UNTUK DEVELOPER JS/TS - BACA DULU!
 * ============================================================
 *
 * Kalau kamu terbiasa dengan Node.js, file I/O di C++ akan familiar.
 * Kalau pure frontend (browser JS), ini mungkin hal baru.
 *
 * Padanan Node.js fs module → C++ File I/O:
 *
 *   Node.js:                         C++:
 *   const fs = require('fs');
 *
 *   // Tulis file:
 *   fs.writeFileSync('file.txt', ...) → ofstream file("file.txt"); file << data;
 *
 *   // Baca file:
 *   fs.readFileSync('file.txt')       → ifstream file("file.txt"); getline(file, line);
 *
 * PERBEDAAN dari Node.js:
 *   1. C++ file I/O SYNCHRONOUS by default (tidak ada async/await)
 *   2. Pakai "stream" dengan operator << dan >>
 *   3. Harus cek apakah file berhasil dibuka (is_open())
 *   4. Binary mode eksplisit dengan ios::binary
 *
 * KONSEP STREAM di C++:
 *   - cout = output stream ke terminal
 *   - ofstream = output stream ke file  (o = output)
 *   - ifstream = input stream dari file (i = input)
 *   - Syntax sama: cout << "hello" === fileStream << "hello"
 * ============================================================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// ============================================================================
// SECTION 1: Menulis Text File
// ============================================================================
//
// Di Node.js: fs.writeFileSync("file.txt", "isi file")
// Di C++:     ofstream f("file.txt"); f << "isi file";
//
// Konsep RAII (Resource Acquisition Is Initialization):
// File otomatis tertutup saat ofstream object keluar dari scope.
// Mirip seperti: using (stream) { ... } di bahasa lain.
// DI JS/TS tidak ada padanannya karena tidak ada destructor.

void section1_WritingTextFiles() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 1: Menulis Text File (ofstream)" << endl;
    cout << string(60, '=') << endl;

    // Buka/buat file untuk menulis
    ofstream outfile("build/output.txt");

    // SELALU cek apakah file berhasil dibuka!
    if (!outfile.is_open()) {
        cerr << "Error: Gagal membuka file untuk menulis" << endl;
        return;
    }

    cout << "Menulis ke file: build/output.txt" << endl;

    // Tulis ke file - syntax SAMA dengan cout!
    // Di JS: stream.write("Line 1\n") atau fs.writeFileSync(...)
    outfile << "Line 1: Hello dari C++ File I/O" << endl;
    outfile << "Line 2: Ini test file" << endl;
    outfile << "Line 3: Angka: " << 42 << " dan " << 3.14 << endl;

    // File otomatis tertutup saat outfile keluar scope (RAII)
    // Tapi good practice: tutup eksplisit
    outfile.close();

    cout << "File berhasil ditulis!" << endl;
    cout << "\nTip: syntax `outfile << data` sama persis dengan `cout << data`" << endl;
    cout << "     Perbedaannya hanya destinasi: file vs terminal" << endl;
}

// ============================================================================
// SECTION 2: Membaca Text File
// ============================================================================
//
// Di Node.js: const content = fs.readFileSync("file.txt", "utf8")
//             const lines = content.split("\n")
//
// Di C++:     ifstream f("file.txt");
//             string line;
//             while (getline(f, line)) { ... }

void section2_ReadingTextFiles() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 2: Membaca Text File (ifstream)" << endl;
    cout << string(60, '=') << endl;

    ifstream infile("build/output.txt");

    if (!infile.is_open()) {
        cerr << "Error: Gagal membuka file untuk dibaca" << endl;
        return;
    }

    cout << "Membaca dari: build/output.txt\n" << endl;

    // getline(stream, string) = baca satu baris
    // Di JS: fileContent.split("\n").forEach(line => ...)
    cout << "Baca baris per baris dengan getline:" << endl;
    string line;
    int lineNum = 0;
    while (getline(infile, line)) {  // Loop sampai habis (EOF)
        lineNum++;
        cout << "  Baris " << lineNum << ": " << line << endl;
    }

    infile.close();
    cout << "\nTotal baris: " << lineNum << endl;
}

// ============================================================================
// SECTION 3: Membaca Data Terstruktur (CSV)
// ============================================================================
//
// CSV parsing adalah task umum di backend dev.
// Tidak ada padanan built-in di C++ (tidak ada JSON.parse seperti JS),
// tapi kita bisa parse manual dengan stringstream.
//
// Teknik: pakai stringstream untuk "split by delimiter"
// Di JS: line.split(",")

void section3_StructuredData() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 3: Membaca Data Terstruktur (CSV)" << endl;
    cout << "(Konsep: parse string - di JS pakai str.split(','))" << endl;
    cout << string(60, '=') << endl;

    // Buat CSV file dulu
    ofstream csvfile("build/data.csv");
    csvfile << "Name,Age,Score\n";
    csvfile << "Alice,30,95\n";
    csvfile << "Bob,25,87\n";
    csvfile << "Charlie,35,92\n";
    csvfile.close();

    cout << "CSV file dibuat: build/data.csv\n" << endl;

    // Baca dan parse CSV
    ifstream infile("build/data.csv");
    string line;
    vector<vector<string>> data;

    cout << "Parse CSV (teknik: stringstream + getline dengan delimiter ',')" << endl;
    cout << "Di JS: line.split(',') - C++ tidak punya split, jadi kita parse manual" << endl;

    while (getline(infile, line)) {
        vector<string> row;
        stringstream ss(line);    // stringstream = stream dari string
        string cell;

        // getline dengan delimiter ',' = split by comma
        // Ini padanan: line.split(',') di JS
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    infile.close();

    // Print data mentah
    cout << "\nData yang diparsing:" << endl;
    for (size_t i = 0; i < data.size(); i++) {
        cout << "  Row " << i << ": ";
        for (const auto& cell : data[i]) {
            cout << "[" << cell << "] ";
        }
        cout << endl;
    }

    // Proses sebagai records (skip header baris 0)
    cout << "\nData setelah diproses (skip header):" << endl;
    for (size_t i = 1; i < data.size(); i++) {
        string name = data[i][0];
        int age = stoi(data[i][1]);     // stoi = parseInt di JS
        int score = stoi(data[i][2]);

        cout << "  " << setw(10) << name
             << " Age: " << age
             << " Score: " << score << endl;
    }
}

// ============================================================================
// SECTION 4: Binary File Operations
// ============================================================================
//
// Binary file = baca/tulis data dalam format biner (bytes), bukan text
//
// Di Node.js: fs.writeFileSync("file.bin", Buffer.from(data))
//             fs.readFileSync("file.bin") // returns Buffer
//
// Di C++: pakai ios::binary mode dan metode write()/read()
//
// Kenapa binary? Lebih compact, lebih cepat untuk data numerik.
// SANGAT PENTING untuk format file seperti ECDIS S-57 yang kamu pelajari!
// S-57 adalah format BINARY, bukan text!

struct Point {
    float x, y, z;
};

void section4_BinaryFiles() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 4: Binary File Operations" << endl;
    cout << "(Penting untuk format S-57 yang adalah format biner!)" << endl;
    cout << string(60, '=') << endl;

    // Tulis binary data
    cout << "\nMenulis data biner (3D points)..." << endl;
    ofstream binout("build/data.bin", ios::binary);  // ios::binary = mode biner

    vector<Point> points = {
        {1.0f, 2.0f, 3.0f},
        {4.0f, 5.0f, 6.0f},
        {7.0f, 8.0f, 9.0f}
    };

    // Tulis jumlah points dulu (header sederhana)
    int count = points.size();
    // reinterpret_cast<char*> = konversi pointer ke "raw bytes"
    // Di Node.js: Buffer.writeInt32LE(count, 0)
    binout.write(reinterpret_cast<char*>(&count), sizeof(count));

    // Tulis setiap point
    for (const auto& p : points) {
        binout.write(reinterpret_cast<const char*>(&p.x), sizeof(p.x));
        binout.write(reinterpret_cast<const char*>(&p.y), sizeof(p.y));
        binout.write(reinterpret_cast<const char*>(&p.z), sizeof(p.z));
    }
    binout.close();

    cout << "Ditulis " << count << " points ke binary file" << endl;

    // Baca binary data
    cout << "\nMembaca data biner..." << endl;
    ifstream binin("build/data.bin", ios::binary);

    int numPoints;
    binin.read(reinterpret_cast<char*>(&numPoints), sizeof(numPoints));
    cout << "  Jumlah points: " << numPoints << endl;

    vector<Point> readPoints;
    for (int i = 0; i < numPoints; i++) {
        Point p;
        binin.read(reinterpret_cast<char*>(&p.x), sizeof(p.x));
        binin.read(reinterpret_cast<char*>(&p.y), sizeof(p.y));
        binin.read(reinterpret_cast<char*>(&p.z), sizeof(p.z));
        readPoints.push_back(p);
    }
    binin.close();

    cout << "\nPoints yang dibaca:" << endl;
    for (size_t i = 0; i < readPoints.size(); i++) {
        const auto& p = readPoints[i];
        cout << "  Point " << i << ": (" << p.x << ", "
             << p.y << ", " << p.z << ")" << endl;
    }

    cout << "\nKenapa binary file?" << endl;
    cout << "  - Lebih compact: float (4 bytes) vs \"1.0\" (3 bytes text, tapi 3.14159... bisa panjang)" << endl;
    cout << "  - Lebih cepat: tidak perlu konversi text <-> number" << endl;
    cout << "  - Presisi tepat: tidak ada rounding dari text representation" << endl;
    cout << "  - Format industri seperti S-57 pakai binary" << endl;
}

// ============================================================================
// SECTION 5: File Positioning - Seek dan Tell
// ============================================================================
//
// Seeking = pindah posisi baca/tulis di file
//
// Di JS/Node.js ini tidak umum dipakai (biasanya streaming),
// tapi di C++ untuk binary format ini SANGAT penting.
//
// Analoginya seperti:
//   - Rewind/fast-forward kaset
//   - Pindah ke halaman tertentu dokumen
// Berguna untuk: format binary yang punya index, jump ke record tertentu

void section5_FilePositioning() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 5: File Positioning (seek dan tell)" << endl;
    cout << "(Berguna untuk navigasi binary file seperti S-57)" << endl;
    cout << string(60, '=') << endl;

    // Buat test file
    ofstream testfile("build/position.txt");
    testfile << "0123456789";  // 10 karakter
    testfile.close();

    ifstream infile("build/position.txt");

    cout << "File content: '0123456789' (10 karakter)" << endl;

    // Baca 5 karakter pertama
    char buffer[6];
    infile.read(buffer, 5);
    buffer[5] = '\0';
    cout << "\nBaca 5 karakter: '" << buffer << "'" << endl;

    // tellg = posisi saat ini
    cout << "Posisi sekarang (tellg): " << infile.tellg() << endl;

    // seekg = pindah ke posisi tertentu
    cout << "\nSeek ke posisi 0 (mulai dari awal):" << endl;
    infile.seekg(0);  // Pindah ke awal
    cout << "  Posisi sekarang: " << infile.tellg() << endl;

    infile.read(buffer, 3);
    buffer[3] = '\0';
    cout << "  Baca 3 karakter: '" << buffer << "'" << endl;

    // Seek ke akhir
    cout << "\nSeek ke akhir file:" << endl;
    infile.seekg(0, ios::end);
    cout << "  Posisi = ukuran file: " << infile.tellg() << " bytes" << endl;

    // Seek mundur dari akhir
    cout << "\nSeek 2 posisi sebelum akhir:" << endl;
    infile.seekg(-2, ios::end);
    cout << "  Posisi: " << infile.tellg() << endl;
    infile.read(buffer, 2);
    buffer[2] = '\0';
    cout << "  Baca 2 karakter: '" << buffer << "'" << endl;

    infile.close();

    cout << "\nMode seek:" << endl;
    cout << "  infile.seekg(pos, ios::beg) - dari awal file" << endl;
    cout << "  infile.seekg(pos, ios::cur) - dari posisi sekarang" << endl;
    cout << "  infile.seekg(pos, ios::end) - dari akhir file (pos biasanya negatif)" << endl;
}

// ============================================================================
// SECTION 6: Error Handling untuk File Operations
// ============================================================================
//
// Di Node.js kamu biasanya handle dengan try/catch atau callback error.
// Di C++, pakai cek is_open() dan state flags.

void section6_ErrorHandling() {
    cout << "\n" << string(60, '=') << endl;
    cout << "SECTION 6: Error Handling File" << endl;
    cout << string(60, '=') << endl;

    cout << "\nFile stream state flags:" << endl;

    // File yang ada
    ifstream goodfile("build/output.txt");
    cout << "  File yang ada - goodfile.is_open(): " << goodfile.is_open() << " (1=true)" << endl;
    cout << "  goodfile.good(): " << goodfile.good() << " (1=true)" << endl;
    goodfile.close();

    // File yang tidak ada
    cout << "\nCoba buka file yang tidak ada:" << endl;
    ifstream badfile("tidak_ada.txt");
    cout << "  badfile.is_open(): " << badfile.is_open() << " (0=false, gagal!)" << endl;
    cout << "  badfile.fail(): " << badfile.fail() << " (1=true, error)" << endl;

    cout << "\nPola error handling yang benar:" << endl;
    cout << "  ifstream file(\"path/to/file.txt\");" << endl;
    cout << "  if (!file.is_open()) {" << endl;
    cout << "    cerr << \"Error: gagal buka file\" << endl;" << endl;
    cout << "    return;  // atau throw exception" << endl;
    cout << "  }" << endl;
    cout << "  // baru proses file..." << endl;
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
    cout << "SECTION 7: Real-World - Sensor Data Logger" << endl;
    cout << string(60, '=') << endl;

    // Data sensor simulasi
    vector<Measurement> measurements = {
        Measurement(22.5, 45.0, 1013.25, 1000),
        Measurement(23.1, 46.2, 1013.20, 2000),
        Measurement(21.9, 44.8, 1013.30, 3000),
        Measurement(22.8, 47.1, 1013.15, 4000),
    };

    // Tulis ke CSV log
    cout << "\nMenulis sensor log..." << endl;
    ofstream logfile("build/sensor_log.csv");
    logfile << "Timestamp,Temperature,Humidity,Pressure\n";

    for (const auto& m : measurements) {
        logfile << m.timestamp << ","
                << fixed << setprecision(1) << m.temperature << ","
                << m.humidity << ","
                << m.pressure << "\n";
    }
    logfile.close();

    cout << "Log disimpan ke: build/sensor_log.csv" << endl;

    // Baca kembali dan proses statistik
    cout << "\nMembaca dan menghitung statistik..." << endl;
    ifstream readlog("build/sensor_log.csv");

    string header;
    getline(readlog, header);  // Skip header

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

    cout << "\nStatistik temperatur:" << endl;
    cout << "  Min: " << fixed << setprecision(1) << tempMin << " C" << endl;
    cout << "  Max: " << tempMax << " C" << endl;
    cout << "  Avg: " << (tempSum / count) << " C" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "\n" << string(60, '*') << endl;
    cout << "FILE I/O - Baca dan Tulis File" << endl;
    cout << "(Mirip fs module di Node.js, tapi synchronous)" << endl;
    cout << string(60, '*') << endl;

    section1_WritingTextFiles();
    section2_ReadingTextFiles();
    section3_StructuredData();
    section4_BinaryFiles();
    section5_FilePositioning();
    section6_ErrorHandling();
    section7_DataLogger();

    cout << "\n" << string(60, '=') << endl;
    cout << "RINGKASAN" << endl;
    cout << string(60, '=') << endl;
    cout << "\nPadanan Node.js fs module → C++:" << endl;
    cout << "  fs.writeFileSync() → ofstream f; f << data;" << endl;
    cout << "  fs.readFileSync()  → ifstream f; getline(f, line);" << endl;
    cout << "  str.split(',')     → getline(ss, cell, ',')" << endl;
    cout << "  Buffer operations  → ios::binary + read()/write()" << endl;
    cout << "\nPola penting:" << endl;
    cout << "  1. SELALU cek is_open() setelah buka file" << endl;
    cout << "  2. Text file: getline untuk baca baris" << endl;
    cout << "  3. Binary file: read/write + reinterpret_cast" << endl;
    cout << "  4. File otomatis tertutup saat keluar scope (RAII)" << endl;
    cout << "\nUntuk ECDIS S-57 files:" << endl;
    cout << "  - Format biner -> pakai ios::binary" << endl;
    cout << "  - Punya header dengan index -> pakai seek" << endl;
    cout << "  - Baca record by record -> pakai read()" << endl;
    cout << "\nNext: Exception Handling untuk kode yang robust!" << endl;
    cout << string(60, '*') << endl << endl;

    return 0;
}
