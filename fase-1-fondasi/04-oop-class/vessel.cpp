#include <iostream>
#include <string>
#include <iomanip>

class Vessel
{
private:
    std::string nama;
    double latitude;
    double longitude;
    double kecepatan;

public:
    Vessel(std::string n, double lat, double lon)
    {
        nama = n;
        latitude = lat;
        longitude = lon;
        kecepatan = 0.0;
        std::cout << "[+] Vessel dibuat: " << nama << std::endl;
    }

    ~Vessel()
    {
        std::cout << "[-] Vessel dihapus: " << nama << std::endl;
    }

    void setKecepatan(double k)
    {
        kecepatan = k;
    }

    void tampilkan()
    {
        std::cout << "Kapal   : " << nama << std::endl;
        std::cout << std::fixed << std::setprecision(4) << "Posisi  : " << latitude << ", " << longitude << std::endl;
        std::cout << std::fixed << std::setprecision(2) << "Speed   : " << kecepatan << " knot" << std::endl;
    }

    double getLatitude()
    {
        return latitude;
    }
};

int main()
{
    {
        Vessel kapal("KM Nusantara", -6.2088, 106.8456);
        kapal.setKecepatan(14.5);
        kapal.tampilkan();

        double latitude = kapal.getLatitude();
        std::cout << std::fixed << std::setprecision(4) << "Latitude kapal: " << latitude << std::endl;
    }

    {
        Vessel kapal2("KM Pelni", -7.2575, 112.7521);
        kapal2.tampilkan();
    }

    std::cout << "Setelah block selesai" << std::endl;

    return 0;
}