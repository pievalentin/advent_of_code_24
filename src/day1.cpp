#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <tuple>
#include <unordered_map>
#include <optional>

using namespace std;

const string filePath = "./data/input_1.csv";

optional<tuple<vector<int>, vector<int>>> read_list()
{
    ifstream inputFile;

    inputFile.open(filePath);
    if (!inputFile.is_open())
    {
        cout << "Error opening file: " << strerror(errno) << endl;
        return {};
    }

    // Using vector instead of arrays because vectors are dynamic arrays that can change size,
    // provide many useful member functions, and handle memory management automatically.
    vector<int> l1;
    vector<int> l2;

    string line;
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        // Split the line by comma using getline() with stringstream

        string item1, item2;
        if (getline(ss, item1, ',') && getline(ss, item2, ','))
        {
            l1.push_back(stoi(item1));
            l2.push_back(stoi(item2));
        }
    }

    inputFile.close();
    return tuple(l1, l2);
}

int distance()
{
    auto lists = read_list();
    if (!lists)
    {
        return -1;
    }
    auto &[l1, l2] = *lists;
    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());

    int result;

    cout << (l1.size() != l2.size() ? "not matching" : "");
    cout << endl;

    for (u_long i = 0; i < l1.size(); i++)
    {
        result = result + abs(l1.at(i) - l2.at(i));
    }

    return result;
}

int similarity()
{
    unordered_map<int, int> counter;
    int result = 0;
    auto lists = read_list();
    if (!lists)
    {
        return -1;
    }
    auto &[l1, l2] = *lists;

    for (auto &el : l2)
    {
        counter[el]++;
    }

    for (auto &el : l1)
    {
        result += el * counter[el];
    }

    return result;
}

int main()
{
    cout << distance() << endl;
    cout << similarity() << endl;

    return 0;
}
