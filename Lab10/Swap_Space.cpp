#include <iostream>
#include <map>

using namespace std;

class SwapManager
{
    int swapSize, usedSwap;
    map<int, int> swapTable;

public:
    SwapManager(int s) : swapSize(s), usedSwap(0) {}

    bool swapOut(int pid, int size)
    {
        if (usedSwap + size <= swapSize)
        {
            swapTable[pid] = size;
            usedSwap += size;
            return true;
        }
        return false;
    }

    void swapIn(int pid)
    {
        if (swapTable.count(pid))
        {
            usedSwap -= swapTable[pid];
            swapTable.erase(pid);
        }
    }

    void printStatus()
    {
        cout << "Swap Used: " << usedSwap << " / " << swapSize << " MB" << endl;
    }
};

int main()
{
    SwapManager sm(512);
    sm.swapOut(1, 128);
    sm.printStatus();
    return 0;
}