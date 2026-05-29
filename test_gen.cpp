#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std;

// Dùng seed cố định 423 đồng bộ với file gốc của nhóm
mt19937 rng(423);

// ==========================================
// BÀI A: SẮP XẾP SỐ NGUYÊN (INT)
// ==========================================
void genInt(int testNum) {
    int n = 100000;
    cout << n << "\n";

    if (testNum == 1) { // Test 1: Mảng tăng dần đều
        for (int i = 0; i < n; i++) {
            cout << -50000 + i << "\n";
        }
    } 
    else if (testNum == 2) { // Test 2: Ngẫu nhiên hoàn toàn
        uniform_int_distribution<long long> dist(-1000000000LL, 1000000000LL);
        for (int i = 0; i < n; i++) {
            cout << dist(rng) << "\n";
        }
    } 
    else if (testNum == 3) { // Test 3: Mảng hằng trùng lặp tuyệt đối
        for (int i = 0; i < n; i++) {
            cout << 42 << "\n";
        }
    } 
    else if (testNum == 4) { // Test 4: Mảng răng cưa đổi dấu tuyệt đối (-a, a, -a, a, ...)
        uniform_int_distribution<long long> dist(500000000LL, 1000000000LL);

        long long val = dist(rng);

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) cout << -val << "\n";
            else cout << val << "\n";
        }
    } 
    else if (testNum == 5) { // Test 5: Mảng giảm dần đều
        for (int i = 0; i < n; i++) {
            cout << 100000 - i << "\n";
        }
    }
}

// ==========================================
// BÀI B: SẮP XẾP TỪ ĐIỂN CHUỖI (STRLEXI)
// ==========================================
void genStrLexi(int testNum) {
    int n = 100000;
    cout << n << "\n";

    if (testNum == 1) { // Test 1: Mảng hằng chuỗi kí tự lớn kịch trần ('z')
        string s(100, 'z');
        for (int i = 0; i < n; i++) cout << s << "\n";
    } 
    else if (testNum == 2) { // Test 2: Trùng 99 ký tự đầu, xáo trộn ký tự cuối kịch trần
        string prefix(99, 'a');
        uniform_int_distribution<int> char_dist(0, 25);
        for (int i = 0; i < n; i++) {
            cout << prefix << (char)('a' + char_dist(rng)) << "\n";
        }
    } 
    else if (testNum == 3) { // Test 3: Mảng hằng chuỗi kí tự nhỏ kịch trần ('a')
        string s(100, 'a');
        for (int i = 0; i < n; i++) cout << s << "\n";
    } 
    else if (testNum == 4) { // Test 4: Trùng 99 ký tự đầu, ký tự cuối tăng tuần hoàn (a -> z)
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            cout << prefix << (char)('a' + (i % 26)) << "\n";
        }
    } 
    else if (testNum == 5) { // Test 5: Ngẫu nhiên hoàn toàn (Độ dài cố định 100)
        for (int i = 0; i < n; i++) {
            string s = "";
            for (int j = 0; j < 100; j++) s += (char)('a' + uniform_int_distribution<int>(0, 25)(rng));
            cout << s << "\n";
        }
    }
}

// ==========================================
// BÀI C: SẮP XẾP ĐỘ DÀI + TỪ ĐIỂN (STRLENLEXI)
// ==========================================
void genStrLenLexi(int testNum) {
    int n = 10000; 
    cout << n << "\n";

    if (testNum == 1) { // Test 1: Chuỗi hằng nội tại theo dòng, lặp khối vài chục dòng (Độ dài 100)
        int i = 0;
        uniform_int_distribution<int> char_dist(0, 25);
        while (i < n) {
            char block_char = (char)('a' + char_dist(rng));
            int block_size = uniform_int_distribution<int>(20, 50)(rng); // Mỗi khối dài vài chục dòng
            string s(100, block_char);
            for (int k = 0; k < block_size && i < n; k++, i++) {
                cout << s << "\n";
            }
        }
    } 
    else if (testNum == 2) { // Test 2: Ngẫu nhiên hoàn toàn (Độ dài cố định 100)
        for (int i = 0; i < n; i++) {
            string s = "";
            for (int j = 0; j < 100; j++) s += (char)('a' + uniform_int_distribution<int>(0, 25)(rng));
            cout << s << "\n";
        }
    } 
    else if (testNum == 3) { // Test 3: Mảng hằng chuỗi kí tự nhỏ (Độ dài cố định 50)
        string s(50, 'a');
        for (int i = 0; i < n; i++) cout << s << "\n";
    } 
    else if (testNum == 4) { // Test 4: Trùng 99 ký tự đầu, ký tự cuối tăng tuần hoàn (a -> z, Độ dài 100)
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            cout << prefix << (char)('a' + (i % 26)) << "\n";
        }
    } 
    else if (testNum == 5) { // Test 5: Trùng 99 ký tự đầu, ký tự cuối xen kẽ 'a' và 'z' (Độ dài 100)
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) cout << prefix << "a\n";
            else cout << prefix << "z\n";
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
