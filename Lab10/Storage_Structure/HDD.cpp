#include <iostream>

struct HDD
{
    int cylinders;
    int tracks_per_cylinder;
    int sectors_per_track;
    int bytes_per_sector;
    int rpm; // Revolutions Per Minute (e.g., 7200)

    // Calculate total capacity in bytes
    long long totalCapacity()
    {
        return (long long)cylinders * tracks_per_cylinder * sectors_per_track * bytes_per_sector;
    }

    // Calculate Average Rotational Latency (half a rotation) in milliseconds
    double rotationalLatency()
    {
        return (60.0 / rpm) / 2.0 * 1000.0;
    }
};

int main()
{
    HDD myDisk = {1024, 16, 63, 512, 7200};
    std::cout << "Capacity: " << myDisk.totalCapacity() << " bytes" << std::endl;
    std::cout << "Rotational Latency: " << myDisk.rotationalLatency() << " ms" << std::endl;
    return 0;
}