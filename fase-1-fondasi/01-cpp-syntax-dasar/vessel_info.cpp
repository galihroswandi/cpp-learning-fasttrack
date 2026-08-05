#include <iostream>
#include <string>
#include <iomanip>

int main()
{
    std::string nama_kapal = "KM Nusantara";
    int MMSI = 525012345;
    double latitude = -6.2088;
    double longitude = 106.8456;
    int heading = 45;
    float kecepatan = 12.5;
    bool berlayar = false;

    std::cout << "\n=== SHIP REPORT ===" << std::endl;
    std::cout << "Nama" << "     : " << nama_kapal << std::endl;
    std::cout << "MMSI" << "     : " << MMSI << std::endl;
    std::cout << "Lat" << "      : " << latitude << std::endl;
    std::cout << "Long" << "     : " << std::fixed << std::setprecision(4) << longitude << std::endl;
    std::cout << "Speed" << "    : " << kecepatan << " knot" << std::endl;
    std::cout << "Heading" << "  : " << std::setw(3) << std::setfill('0') << heading << " deg" << std::endl;
    std::cout << "Anchored" << " : " << std::boolalpha << !berlayar << std::endl;

    return 0;
}