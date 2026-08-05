#include <iostream>
#include <vector>
#include <map>
#include <string>

int main()
{
    // Vector -- seperti array JS tapi tipe dikunci
    std::vector<std::string> nama_kapal;
    nama_kapal.push_back("KM Nusantara");
    nama_kapal.push_back("KRI Diponegoro");
    nama_kapal.push_back("MV Oceanic");

    std::cout << "=== DAFTAR KAPAL ===" << std::endl;
    for (const std::string &nama : nama_kapal)
    {
        std::cout << "- " << nama << std::endl;
        nama_kapal.push_back("Kapal Hantu");
    }

    std::cout << "\nJumlah Kapal: " << nama_kapal.size() << std::endl;

    // Map -- seperti Object JS, key-value
    std::map<std::string, double> kecepatan_kapal;
    kecepatan_kapal["KM Nusantara"] = 14.5;
    kecepatan_kapal["KRI Diponegoro"] = 28.0;
    kecepatan_kapal["MV Oceanic"] = 21.0;

    std::cout << "\n=== KECEPATAN ===" << std::endl;
    for (const auto &entry : kecepatan_kapal)
    {
        std::cout << entry.first << ": " << entry.second << " knot" << std::endl;
    }

    std::cout << kecepatan_kapal["Kapal Hantu"] << std::endl;
    std::cout << "Ukuran map: " << kecepatan_kapal.size() << std::endl;

    if (kecepatan_kapal.count("KM Nusantara") > 0)
    {
        std::cout << "KM Nusantara ada di map " << kecepatan_kapal["KM Nusantara"] << std::endl;
    }

    return 0;
}