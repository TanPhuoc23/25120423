#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std;

void genInt(int testNum) {
    int n = 100000;
    cout << n << "\n";
    mt19937 rng(423);

    if (testNum == 1) {
        for (int i = 0; i < n; i++) {
            cout << -50000 + i << "\n";
        }
    } 
    else if (testNum == 2) {
        uniform_int_distribution<long long> dist(-1000000000LL, 1000000000LL);
        for (int i = 0; i < n; i++) {
            cout << dist(rng) << "\n";
        }
    } 
    else if (testNum == 3) {
        for (int i = 0; i < n; i++) {
            cout << 42 << "\n";
        }
    } 
    else if (testNum == 4) {
        uniform_int_distribution<long long> high_dist(500000000LL, 1000000000LL);
        uniform_int_distribution<long long> low_dist(-1000000000LL, -500000000LL);
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) cout << high_dist(rng) << "\n";
            else cout << low_dist(rng) << "\n";
        }
    } 
    else if (testNum == 5) {
        for (int i = 0; i < n; i++) {
            cout << 100000 - i << "\n";
        }
    }
}

void genStrLexi(int testNum) {
    int n = 100000;
    cout << n << "\n";
    mt19937 rng(423);

    if (testNum == 1) {
        string s(100, 'z');
        for (int i = 0; i < n; i++) cout << s << "\n";
    } 
    else if (testNum == 2) {
        for (int i = 0; i < n; i++) {
            string s = "";
            for (int j = 0; j < 100; j++) s += (char)('a' + uniform_int_distribution<int>(0, 25)(rng));
            cout << s << "\n";
        }
    } 
    else if (testNum == 3) {
        string s(100, 'a');
        for (int i = 0; i < n; i++) cout << s << "\n";
    } 
    else if (testNum == 4) {
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            cout << prefix << (char)('a' + (i % 26)) << "\n";
        }
    } 
    else if (testNum == 5) {
        for (int i = 0; i < n; i++) {
            string s = "";
            char base_char = (char)('z' - (i % 26));
            for (int j = 0; j < 100; j++) s += (char)(max('a', base_char - (j % 3)));
            cout << s << "\n";
        }
    }
}

void genStrLenLexi(int testNum) {
    int n = 10000;
    cout << n << "\n";
    mt19937 rng(423);

    if (testNum == 1) {
        for (int i = 0; i < n; i++) {
            int len = uniform_int_distribution<int>(10, 100)(rng);
            string s = "";
            for (int j = 0; j < len; j++) s += (char)('a' + uniform_int_distribution<int>(0, 25)(rng));
            cout << s << "\n";
        }
    } 
    else if (testNum == 2) {
        for (int i = 0; i < n; i++) {
            string s = "";
            for (int j = 0; j < 100; j++) s += (char)('a' + uniform_int_distribution<int>(0, 25)(rng));
            cout << s << "\n";
        }
    } 
    else if (testNum == 3) {
        string s(50, 'a');
        for (int i = 0; i < n; i++) cout << s << "\n";
    } 
    else if (testNum == 4) {
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            cout << prefix << (char)('a' + (i % 26)) << "\n";
        }
    } 
    else if (testNum == 5) {
        for (int i = 0; i < n; i++) {
            string s = "";
            char base_char = (char)('z' - (i % 26));
            for (int j = 0; j < 100; j++) s += (char)(max('a', base_char - (j % 3)));
            cout << s << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    string taskType = argv[1];
    int testNum = stoi(argv[2]);

    if (taskType == "int") genInt(testNum);
    else if (taskType == "strlexi") genStrLexi(testNum);
    else if (taskType == "strlenlexi") genStrLenLexi(testNum);

    return 0;
}