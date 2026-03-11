#include <iostream>
#include <string>

using namespace std;

class StorageDevice
{
public:
    virtual string getInterface() = 0;
    virtual double getBandwidth() = 0;
    void read(int lba)
    {
        cout << getInterface() << " Reading LBA " << lba << " at " << getBandwidth() << " MB/s" << endl;
    }
};

class NVMeDrive : public StorageDevice
{
public:
    string getInterface() override { return "NVMe"; }
    double getBandwidth() override { return 7000.0; }
};

class USBDrive : public StorageDevice
{
public:
    string getInterface() override { return "USB 3.0"; }
    double getBandwidth() override { return 480.0; }
};

int main()
{
    StorageDevice *d = new NVMeDrive();
    d->read(200);
    delete d;
    return 0;
}