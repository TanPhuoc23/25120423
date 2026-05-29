#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std;

// Dùng seed cố định 423 giống hệt file gốc của bạn để đảm bảo dữ liệu sinh ra đồng nhất
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
    else if (testNum == 2) { // Test 2: Ngẫu nhiên hoàn toàn (Phân bố đều)
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
    else if (testNum == 4) { // Test 4: Mảng răng cưa biến thiên khối lớn - khối nhỏ
        uniform_int_distribution<long long> high_dist(500000000LL, 1000000000LL);
        uniform_int_distribution<long long> low_dist(-1000000000LL, -500000000LL);
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) cout << high_dist(rng) << "\n";
            else cout << low_dist(rng) << "\n";
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

    if (testNum == 1) { // Test 1: Mảng hằng chuỗi kí tự lớn kịch trần
        string s(100, 'z');
        for (int i = 0; i < n; i++) cout << s << "\n";
    } 
    else if (testNum == 2) { // Test 2: Ngẫu nhiên hoàn toàn (Độ dài 100)
        for (int i = 0; i < n; i++) {
            string s = "";
            for (int j = 0; j < 100; j++) s += (char)('a' + uniform_int_distribution<int>(0, 25)(rng));
            cout << s << "\n";
        }
    } 
    else if (testNum == 3) { // Test 3: Mảng hằng chuỗi kí tự nhỏ kịch trần
        string s(100, 'a');
        for (int i = 0; i < n; i++) cout << s << "\n";
    } 
    else if (testNum == 4) { // Test 4: Bẫy trùng tiền tố dài (99 kí tự đầu giống nhau)
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            cout << prefix << (char)('a' + (i % 26)) << "\n";
        }
    } 
    else if (testNum == 5) { // Test 5: Chuỗi răng cưa biến thiên ký tự tuần hoàn
        for (int i = 0; i < n; i++) {
            string s = "";
            char base_char = (char)('z' - (i % 26));
            for (int j = 0; j < 100; j++) s += (char)(max('a', base_char - (j % 3)));
            cout << s << "\n";
        }
    }
}

// ==========================================
// BÀI C: SẮP XẾP ĐỘ DÀI + TỪ ĐIỂN (STRLENLEXI)
// ==========================================
void genStrLenLexi(int testNum) {
    int n = 10000; // Giữ nguyên quy mô 10,000 dòng theo đúng file thực tế của bạn
    cout << n << "\n";

    if (testNum == 1) { // Test 1: Ngẫu nhiên biến thiên cả độ dài (10 đến 100)
        for (int i = 0; i < n; i++) {
            int len = uniform_int_distribution<int>(10, 100)(rng);
            string s = "";
            for (int j = 0; j < len; j++) s += (char)('a' + uniform_int_distribution<int>(0, 25)(rng));
            cout << s << "\n";
        }
    } 
    else if (testNum == 2) { // Test 2: Độ dài bằng nhau (100) nhưng từ điển ngẫu nhiên
        for (int i = 0; i < n; i++) {
            string s = "";
            for (int j = 0; j < 100; j++) s += (char)('a' + uniform_int_distribution<int>(0, 25)(rng));
            cout << s << "\n";
        }
    } 
    else if (testNum == 3) { // Test 3: Mảng hằng chuỗi kí tự nhỏ kịch trần (Độ dài 50)
        string s(50, 'a');
        for (int i = 0; i < n; i++) cout << s << "\n";
    } 
    else if (testNum == 4) { // Test 4: Bẫy trùng tiền tố dài (99 kí tự đầu giống nhau)
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            cout << prefix << (char)('a' + (i % 26)) << "\n";
        }
    } 
    else if (testNum == 5) { // Test 5: Chuỗi răng cưa biến thiên ký tự tuần hoàn
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
