#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
using namespace std;

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
        /*
        40971
        40972
        40973
        ...
        49998
        49999
        */
    }
    else if (testNum == 2) { // Test 2: Ngẫu nhiên hoàn toàn (-1 tỷ đến 1 tỷ)
        for (int i = 0; i < n; i++) {
            long long high = rand();
            long long low = rand();
            long long combined = (high << 15) ^ low;

            // Ép dải số về khoảng [-1.000.000.000, 1.000.000.000]
            long long val = -1000000000LL + (combined % 2000000001LL);
            cout << val << "\n";
        }
        /*
        -96537713
        19397812
        ...
        -237689752
        */
    }
    else if (testNum == 3) { // Test 3: Mảng hằng trùng lặp tuyệt đối
        for (int i = 0; i < n; i++) {
            cout << 42 << "\n";
        }
        /*
        42
        42
        ...
        42
        */
    }
    else if (testNum == 4) { // Test 4: Mảng răng cưa đổi dấu tuyệt đối (-a, a, -a, a, ...)
        long long val = 2147483650LL;
        for (int i = 0; i < n; i++) {
            val -= 2;
            if (i % 2 == 0) cout << -val << "\n";
            else cout << val << "\n";
        }
        /*
        2147301706
        -2147301704
        2147301702
        ...
        2147283654
        -2147283652
        2147283650
        */
    }
    else if (testNum == 5) { // Test 5: Mảng giảm dần đều
        for (int i = 0; i < n; i++) {
            cout << 100000 - i << "\n";
        }
        /*
        9029
        9028
        9027
        ...
        3
        2
        1
        */
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

        /*
        zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
        zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
        ...
        zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
        zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
        */
    }
    else if (testNum == 2) { // Test 2: Trùng 99 ký tự đầu, xáo trộn ký tự cuối kịch trần
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            cout << prefix << (char)('a' + (rand() % 26)) << "\n";
        }
        /*
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaal
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaf
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaai
        ...
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaat
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaav

        */
    }
    else if (testNum == 3) { // Test 3: Mảng hằng chuỗi kí tự nhỏ kịch trần ('a')
        string s(100, 'a');
        for (int i = 0; i < n; i++) cout << s << "\n";
        /*
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        */
    }
    else if (testNum == 4) { // Test 4: Trùng 99 ký tự đầu, ký tự cuối tăng tuần hoàn (a -> z)
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            cout << prefix << (char)('a' + (i % 26)) << "\n";
            /*
            aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
            aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab
            aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaac
            ...
            aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaay
            aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaz
            */
        }
    }
    else if (testNum == 5) { // Test 5: Ngẫu nhiên hoàn toàn (Độ dài cố định 100)
        for (int i = 0; i < n; i++) {
            string s = "";
            for (int j = 0; j < 100; j++) {
                s += (char)('a' + (rand() % 26));
            }
            cout << s << "\n";
        }
        /*
        klhskumwyamlilqqiprlttgchclemohfejvqcwzznxzzcaqacjvletpoxdoeeybsfgdrpkmyabnofjevhfwtpyupscxfnaswogsg
        znntmacuvledbutwtbfahsuvzudkuiiitkyxmebamkmsfxhaceftcxzpsppuvkovhoqodacktztxmhermfddvzwhzphrrtdzfyul
        ...
        gllpedmapfprlxrdlugbovdjlerjsohmolobdsztaffkfzqzgropufcmtszaziirewsbzrnyjgorwyrhqoptjrkyvoqgvonavhsx
        */
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
        while (i < n) {
            char block_char = (char)('a' + (rand() % 26));
            // Khoảng [20, 50] tương đương: 20 + rand() % (50 - 20 + 1)
            int block_size = 20 + (rand() % 31);
            string s(100, block_char);
            for (int k = 0; k < block_size && i < n; k++, i++) {
                cout << s << "\n";
            }
        }

        /*
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        ...
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
        ...
        jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
        qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
        */
    }
    else if (testNum == 2) { // Test 2: Ngẫu nhiên hoàn toàn (Độ dài cố định 100)
        for (int i = 0; i < n; i++) {
            string s = "";
            for (int j = 0; j < 100; j++) {
                s += (char)('a' + (rand() % 26));
            }
            cout << s << "\n";
        }
        /*
        kinluccrbufqazbsdfkjazvfdarttpgkdqojbycabowbbkipsneeynkzrdielmnduudfoppduqfjgotyzgnqdvjnbtmysobsmnsn
        vixuoljjpcosrxfjpjlzkfjxhlzygnwohspvbzlhsjdvvxwfjwwpneshwgejkxaxsmizttxfbuofjnxsbgnmjjcwrbctemkjazry
        ...
        inyrovhcdqhafepubffkdzcgsvpbucybizjbehoipacheohogyarmppycvkdooblroimokrkkoixtlnhrjxkqnxghvtaksmotdro
        */
    }
    else if (testNum == 3) { // Test 3: Mảng hằng chuỗi kí tự nhỏ (Độ dài cố định 50)
        string s(50, 'a');
        for (int i = 0; i < n; i++) cout << s << "\n";
        /*
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        ...
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        */
    }
    else if (testNum == 4) { // Test 4: Trùng 99 ký tự đầu, ký tự cuối tăng tuần hoàn (a -> z, Độ dài 100)
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            cout << prefix << (char)('a' + (i % 26)) << "\n";
        }
        /*
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab
        ...
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaay
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaz
        */
    }
    else if (testNum == 5) { // Test 5: Trùng 99 ký tự đầu, ký tự cuối xen kẽ 'a' và 'z' (Độ dài 100)
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) cout << prefix << "a\n";
            else cout << prefix << "z\n";
        }
        /*
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaz
        ...
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaz
        */
    }
}

int main(int argc, char* argv[]) {
    srand(423);

    if (argc < 3) return 1;

    string taskType = argv[1];
    int testNum = stoi(argv[2]);

    if (taskType == "int") genInt(testNum);
    else if (taskType == "strlexi") genStrLexi(testNum);
    else if (taskType == "strlenlexi") genStrLenLexi(testNum);

    return 0;
}
