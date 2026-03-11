#include <iostream>
#include <vector>
#include <string>

using namespace std;

void writeRAID5(string blockA, string blockB)
{
    string parity = "";
    for (int i = 0; i < blockA.size(); i++)
        parity += char(blockA[i] ^ blockB[i]);
    cout << "Stripe 0: Disk0=" << blockA << ", Disk1=" << blockB << ", Disk2=" << parity << " (P)" << endl;
}

int main()
{
    writeRAID5("DATA1", "DATA2");
    return 0;
}