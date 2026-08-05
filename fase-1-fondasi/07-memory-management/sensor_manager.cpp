#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Sensor
{
public:
    std::string tipe;
    double nilai;

    Sensor(std::string tipe) : tipe(tipe)
    {
        std::cout << "[+] Sensor Dibuat : " << tipe << std::endl;
    }

    void baca()
    {
        nilai = (std::rand() % 100);
    }
};

class SensorManager
{
protected:
    std::vector<std::unique_ptr<Sensor>> sensors;

public:
    void tambahSensor(std::string tipe)
    {
        sensors.push_back(std::make_unique<Sensor>(tipe));
    }

    void bacaSemua()
    {
        std::cout << std::string(4, '=') << " DAFTAR SENSOR " << std::string(4, '=') << std::endl;
        for (const std::unique_ptr<Sensor> &sensor : sensors)
        {
            sensor->baca();
            std::cout << "Jenis Sensor : " << sensor->tipe << std::endl;
            std::cout << "Nilai        : " << sensor->nilai << std::endl;
            std::cout << std::string(25, '-') << std::endl;
        }
    }

    Sensor *getSensor(int index)
    {
        return sensors[index].get();
    }
};

int main()
{
    std::unique_ptr<SensorManager> manager = std::make_unique<SensorManager>();
    manager->tambahSensor("GPS");
    manager->tambahSensor("Radar");
    manager->tambahSensor("Gyro");

    manager->bacaSemua();
    std::cout << manager->getSensor(0)->tipe << std::endl;

    return 0;
}