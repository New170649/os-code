#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Q4 (c) Hamming Distance implementation
int hammingDistance(vector<int> &a, vector<int> &b)
{
    if (a.size() != b.size())
        throw invalid_argument("Vectors must be same length");

    int dist = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            dist++;
    }
    return dist;
}

int main()
{
    vector<int> a = {1, 0, 1, 1};
    vector<int> b = {1, 0, 0, 1};
    try
    {
        cout << "Hamming Distance: " << hammingDistance(a, b) << endl;
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}