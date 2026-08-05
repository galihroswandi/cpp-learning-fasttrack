#include <iostream>
#include <string>

class Vessel
{
protected:
    std::string nama;
    double latitude, longitude;

public:
    Vessel(std::string n, double lat, double lon) : nama(n), latitude(lat), longitude(lon)
    {
        std::cout << "[Vessel] Dibuat: " << nama << std::endl;
    }

    virtual ~Vessel()
    {
        std::cout << "[Vessel] Dihapus: " << nama << std::endl;
    }

    virtual void tampilkan()
    {
        std::cout << "Kapal :" << nama << std::endl;
        std::cout << "Posisi: " << latitude << ", " << longitude << std::endl;
    }
};

class CargoShip : public Vessel
{
private:
    double muatan_ton;

public:
    CargoShip(std::string n, double lat, double lon, double muatan) : Vessel(n, lat, lon), muatan_ton(muatan)
    {
        std::cout << "[CargoShip] Dibuat: " << nama << std::endl;
    }

    ~CargoShip()
    {
        std::cout << "[CargoShip] Dihapus: " << nama << std::endl;
    }

    void tampilkan() override
    {
        Vessel::tampilkan();
        std::cout << "Muatan: " << muatan_ton << std::endl;
    }
};

class Tanker : public Vessel
{
private:
    std::string jenis_muatan;
    double kapasitas_liter;

public:
    Tanker(std::string n, double lat, double lon, std::string jenis, double kap_liter) : Vessel(n, lat, lon), jenis_muatan(jenis), kapasitas_liter(kap_liter)
    {
        std::cout << "[Tanker] Dibuat: " << nama << std::endl;
    }

    ~Tanker()
    {
        std::cout << "[Tanker] Dihapus: " << nama << std::endl;
    }

    void tampilkan() override
    {
        Vessel::tampilkan();
        std::cout << "Jenis Muatan: " << jenis_muatan << std::endl;
        std::cout << "Kapasitas: " << kapasitas_liter << " liter" << std::endl;
    }
};

class PassengerShip : public Vessel
{
private:
    int jumlah_penumpang;
    std::string rute;

public:
    PassengerShip(std::string n, double lat, double lon, int penumpang, std::string rt) : Vessel(n, lat, lon), jumlah_penumpang(penumpang), rute(rt)
    {
        std::cout << "[PassengerShip] Dibuat: " << nama << std::endl;
    }

    ~PassengerShip()
    {
        std::cout << "[PassengerShip] Dihapus: " << nama << std::endl;
    }

    void tampilkan() override
    {
        Vessel::tampilkan();
        std::cout << "Penumpang: " << jumlah_penumpang << std::endl;
        std::cout << "Rute: " << rute << std::endl;
    }
};

int main()
{
    Vessel *armada[3];
    armada[0] = new CargoShip("Cargo A", 1.234, 103.456, 5000);
    armada[1] = new Tanker("Evergreen", 2.345, 104.567, "Minyak", 100000);
    armada[2] = new PassengerShip("Ferry B", 3.456, 105.678, 200, "Jakarta - Bandung");

    std::cout << "\n--- Informasi Armada ---\n"
              << std::endl;
    for (int i = 0; i < 3; i++)
    {
        armada[i]->tampilkan();
        std::cout << "-----------------------------" << std::endl;
    }

    std::cout << "\n--- Menghapus Armada ---\n"
              << std::endl;
    for (int i = 0; i < 3; i++)
    {
        delete armada[i];
    }

    return 0;
}