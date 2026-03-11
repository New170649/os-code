#include <iostream>
#include <bitset>

using namespace std;

const int TOTAL = 16;

class DiskManager
{
    bitset<TOTAL> freeBlocks;

public:
    DiskManager() { freeBlocks.set(); }

    int allocate()
    {
        for (int i = 0; i < TOTAL; i++)
        {
            if (freeBlocks[i])
            {
                freeBlocks[i] = 0;
                return i;
            }
        }
        return -1;
    }

    int allocateContiguous(int n)
    {
        int count = 0, start = -1;
        for (int i = 0; i < TOTAL; i++)
        {
            if (freeBlocks[i])
            {
                if (count == 0)
                    start = i;
                if (++count == n)
                {
                    for (int j = start; j < start + n; j++)
                        freeBlocks[j] = 0;
                    return start;
                }
            }
            else
            {
                count = 0;
                start = -1;
            }
        }
        return -1;
    }
};

int main()
{
    DiskManager dm;
    cout << "Allocated 3 blocks at: " << dm.allocateContiguous(3) << endl;
    return 0;
}