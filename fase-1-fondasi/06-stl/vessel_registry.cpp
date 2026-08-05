#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>

void daftarKapal(std::map<int, std::string> &vessel_data, std::map<int, double> &vessel_kecepatan, std::vector<std::string> &log, int mmsi, const std::string &nama, double speed);
void updateKecepatan(std::map<int, double> &vessel_kecepatan, std::vector<std::string> &log, int mmsi, double speed);
void tampilkanSemua(std::map<int, std::string> &vessel_data, std::map<int, double> &vessel_kecepatan);
void tampilkanLog(std::vector<std::string> &log);

int main()
{
    std::vector<std::string> log;
    std::map<int, std::string> vessel_data;
    std::map<int, double> vessel_kecepatan;

    daftarKapal(vessel_data, vessel_kecepatan, log, 12, "KM Nusantara", 14.5);
    daftarKapal(vessel_data, vessel_kecepatan, log, 90, "KRI Diponegoro", 28.0);
    daftarKapal(vessel_data, vessel_kecepatan, log, 80, "MV Oceanic", 21.0);

    updateKecepatan(vessel_kecepatan, log, 12, 15.0);
    updateKecepatan(vessel_kecepatan, log, 999, 10.0);

    tampilkanSemua(vessel_data, vessel_kecepatan);
    tampilkanLog(log);

    return 0;
}

void daftarKapal(std::map<int, std::string> &vessel_data, std::map<int, double> &vessel_kecepatan, std::vector<std::string> &log, int mmsi, const std::string &nama, double speed)
{
    vessel_data[mmsi] = nama;
    vessel_kecepatan[mmsi] = speed;
    log.push_back("[DAFTAR] " + nama + " (MMSI: " + std::to_string(mmsi) + ")");
}

void updateKecepatan(std::map<int, double> &vessel_kecepatan, std::vector<std::string> &log, int mmsi, double speed)
{
    if (vessel_kecepatan.count(mmsi) > 0)
    {
        vessel_kecepatan[mmsi] = speed;
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << vessel_kecepatan[mmsi];

        log.push_back("[UPDATE] MMSI: " + std::to_string(mmsi) + " kecepatan diubah menjadi " + oss.str() + " knot");
    }
    else
    {
        log.push_back("[ERROR] MMSI: " + std::to_string(mmsi) + " tidak ditemukan untuk update kecepatan");
    }
}

void tampilkanSemua(std::map<int, std::string> &vessel_data, std::map<int, double> &vessel_kecepatan)
{
    std::cout << "=== DAFTAR KAPAL ===" << std::endl;
    for (const auto &entry : vessel_data)
    {
        int mmsi = entry.first;
        std::string nama = entry.second;
        double speed = vessel_kecepatan[mmsi];

        std::cout << "MMSI: " << mmsi << ", Nama: " << nama << ", Kecepatan: " << std::fixed << std::setprecision(1) << speed << " knot" << std::endl;
    }
}

void tampilkanLog(std::vector<std::string> &log)
{
    std::cout << "=== LOG AKTIVITAS ===" << std::endl;
    for (const std::string &entry : log)
    {
        std::cout << std::fixed << std::setprecision(1) << entry << std::endl;
    }
}