#include <iostream>
#include <string>

class Vessel
{
protected:
    std::string nama;
    double latitude;
    double longitude;

public:
    Vessel(std::string n, double lat, double lon)
        : nama(n), latitude(lat), longitude(lon)
    {
        std::cout << "[Vessel] Dibuat: " << nama << std::endl;
    }

    virtual ~Vessel()
    {
        std::cout << "[Vessel] Dihapus: " << nama << std::endl;
    }

    virtual void tampilkan()
    {
        std::cout << "Kapal: " << nama << " | Pos: " << latitude << ", " << longitude << std::endl;
    }
};

class Warship : public Vessel
{
private:
    int jumlah_meriam;

public:
    Warship(std::string n, double lat, double lon, int meriam)
        : Vessel(n, lat, lon), jumlah_meriam(meriam)
    {
        std::cout << "[Warship] Dibuat: " << nama << std::endl;
    }

    ~Warship()
    {
        std::cout << "[Warship] Dihapus: " << nama << std::endl;
    }

    void tampilkan() override
    {
        Vessel::tampilkan();
        std::cout << "Meriam: " << jumlah_meriam << std::endl;
    }
};

class CivilianVessel : public Vessel
{
private:
    int jumlah_penumpang;

public:
    CivilianVessel(std::string n, double lat, double lon, int penump)
        : Vessel(n, lat, lon), jumlah_penumpang(penump)
    {
        std::cout << "[CivilianVessel] Dibuat: " << nama << std::endl;
    }

    ~CivilianVessel()
    {
        std::cout << "[CivilianVessel] Dihapus: " << nama << std::endl;
    }

    void tampilkan() override
    {
        Vessel::tampilkan();
        std::cout << "Penumpang: " << jumlah_penumpang << std::endl;
    }
};

int main()
{
    Vessel *v1 = new Vessel("KM Nusantara", -6.2088, 106.8456);
    Vessel *v2 = new Warship("KRI Diponegoro", -8.1234, 114.5678, 76);
    Vessel *v3 = new CivilianVessel("MV Oceanic", -7.5678, 110.1234, 300);

    std::cout << "\n--- v1->tampilkan() ---" << std::endl;
    v1->tampilkan();

    std::cout << "\n--- v2->tampilkan() ---" << std::endl;
    v2->tampilkan();

    std::cout << "\n--- v3->tampilkan() ---" << std::endl;
    v3->tampilkan();

    std::cout << "\n"
              << std::endl;

    delete v1;
    delete v2;
    delete v3;
}