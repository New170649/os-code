#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct NVMRequest
{
    string type; // "read" or "write"
    int lba;
};

// Q3 (b) Priority NVM Processing (Reads over Writes)
void processNVM(queue<NVMRequest> &q)
{
    queue<NVMRequest> reads, writes;
    while (!q.empty())
    {
        NVMRequest r = q.front();
        q.pop();
        if (r.type == "read")
            reads.push(r);
        else
            writes.push(r);
    }

    while (!reads.empty())
    {
        auto r = reads.front();
        reads.pop();
        cout << "READ  LBA " << r.lba << " -> ~0.05ms" << endl;
    }
    while (!writes.empty())
    {
        auto r = writes.front();
        writes.pop();
        cout << "WRITE LBA " << r.lba << " -> ~0.15ms" << endl;
    }
}

// Q3 (c) Wear Leveling Simulation
const int NUM_BLOCKS = 8;
int writeCount[NUM_BLOCKS] = {0};

int wearLevelWrite(int logicalBlock)
{
    int physBlock = 0;
    int minWrites = writeCount[0];
    for (int i = 1; i < NUM_BLOCKS; i++)
    {
        if (writeCount[i] < minWrites)
        {
            minWrites = writeCount[i];
            physBlock = i;
        }
    }
    writeCount[physBlock]++;
    cout << "Logical " << logicalBlock << " -> Physical " << physBlock << " (Writes: " << writeCount[physBlock] << ")" << endl;
    return physBlock;
}

int main()
{
    queue<NVMRequest> q;
    q.push({"write", 101});
    q.push({"read", 102});
    q.push({"write", 103});

    cout << "--- NVM Processing ---" << endl;
    processNVM(q);

    cout << "\n--- Wear Leveling Test ---" << endl;
    for (int i = 0; i < 5; i++)
        wearLevelWrite(i);

    return 0;
}