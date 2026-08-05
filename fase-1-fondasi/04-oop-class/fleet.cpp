#include <iostream>
#include <string>
#include <iomanip>

class Vessel
{
private:
    std::string nama;
    int mmsi;
    double latitude, longitude, kecepatan;
    bool aktif;

public:
    Vessel(std::string nama, int mmsi, double lat, double lon, double kecepatan, bool aktif)
    {
        this->nama = nama;
        this->mmsi = mmsi;
        this->latitude = lat;
        this->longitude = lon;
        this->kecepatan = kecepatan;
        this->aktif = aktif;

        std::cout << "\n[+] Vessel " << nama << " dengan MMSI " << mmsi << " berhasil dibuat." << std::endl;
    }

    ~Vessel()
    {
        std::cout << "[-] Vessel " << this->nama << " dengan MMSI " << this->mmsi << " telah dihancurkan." << std::endl;
    }

    std::string getNama()
    {
        return this->nama;
    }

    int getMMSI()
    {
        return this->mmsi;
    }

    double getLatitude()
    {
        return this->latitude;
    }

    double getLongitude()
    {
        return this->longitude;
    }

    double getKecepatan()
    {
        return this->kecepatan;
    }

    bool getAktif()
    {
        return this->aktif;
    }

    void setKecepatan(double kecepatan)
    {
        if (kecepatan < 0)
        {
            std::cout << "[-] Kecepatan tidak boleh negatif." << std::endl;
            return;
        }

        this->kecepatan = kecepatan;
    }

    void setAktif(bool aktif)
    {
        this->aktif = aktif;
    }

    void tampilkan()
    {
        std::cout << std::string(5, '=') << "VESSEL INFO" << std::string(5, '=') << std::endl;
        std::cout << "Nama      : " << this->nama << std::endl;
        std::cout << "MMSI      : " << this->mmsi << std::endl;
        std::cout << std::fixed << std::setprecision(4) << "Latitude  : " << this->latitude << std::endl;
        std::cout << std::fixed << std::setprecision(4) << "Longitude : " << this->longitude << std::endl;
        std::cout << std::fixed << std::setprecision(2) << "Kecepatan : " << this->kecepatan << " knots" << std::endl;
        std::cout << "Status    : " << (this->aktif ? "ACTIVE" : "INACTIVE") << std::endl;
    }
};

int main()
{
    {
        Vessel kapal1("Ever Given", 123, 30.0444, 31.2357, 13.5, true);
        kapal1.setKecepatan(0);
        kapal1.setAktif(false);
        kapal1.tampilkan();
    }

    {
        Vessel kapal2("Titanic", 456, 41.7325, -49.9469, 0.0, false);
        kapal2.setKecepatan(-0.5); // Invalid speed, should show error message
        kapal2.setAktif(true);
        kapal2.tampilkan();
    }

    return 0;
}