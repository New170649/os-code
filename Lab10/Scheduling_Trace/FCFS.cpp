#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int fcfs(int head, vector<int> requests)
{
    int totalMovement = 0;
    for (int req : requests)
    {
        totalMovement += abs(req - head);
        head = req;
    }
    return totalMovement;
}

int main()
{
    vector<int> req = {98, 183, 37, 122, 14, 124, 65, 67};
    int initialHead = 53;
    cout << "FCFS Total Head Movement: " << fcfs(initialHead, req) << " cylinders" << endl;
    // Expected Output: 640
    return 0;
}