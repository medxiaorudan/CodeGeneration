#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

void display(vector<pair<int, time_t>> &v) {
    for (auto &p : v) {
        cout << p.first << " " << ctime(&p.second) << endl;
    }
}

int main() {
    vector<pair<int, time_t>> v;
    while (true) {
        int n;
        cin >> n;
        if (!cin) {
            break;
        }
        v.push_back(make_pair(n, time(nullptr)));
    }
    sort(v.begin(), v.end());
    display(v);
}