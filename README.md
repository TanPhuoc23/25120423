# BÁO CÁO ĐỒ ÁN SORT BENCHMARK 

* **Môn học:** Cấu trúc dữ liệu và Giải thuật
* **Lớp:** 25CTT6 
* **Giảng viên:**  Huỳnh Lâm Hải Đăng - Nguyễn Ngọc Đức - Phạm Trọng Nghĩa
* **Sinh viên thực hiện:** Trần Tấn Phước - Trần Nhất Phong - Châu Thị Thảo Vân
* **MSSV:** 25120423-25120414-25120467

---

## 1. Chiến lược thiết kế bộ sinh test case trong `test_gen.cpp`

Bộ sinh test `test_gen.cpp` tự động tạo ra 15 test case (mỗi bài gồm 5 test).  

Mục tiêu chính của bộ test không chỉ là kiểm tra tính đúng đắn của chương trình mà còn tập trung đánh vào các điểm yếu về hiệu năng của những thuật toán sắp xếp phổ biến hiện nay. Cụ thể, bộ test được thiết kế dựa trên đặc điểm hoạt động của bốn nhóm thuật toán thường có tốc độ nhanh và được sử dụng nhiều nhất trong các bài toán sắp xếp:

- **Quick Sort**
- **Merge Sort**
- **Heap Sort**
- **Radix Sort**

Đây đều là những thuật toán có độ phức tạp tốt trong điều kiện thông thường, tuy nhiên mỗi thuật toán vẫn tồn tại các trường hợp dữ liệu đặc biệt có thể làm hiệu năng giảm mạnh. Bộ test sẽ cố tình tạo ra những cấu trúc dữ liệu như:

- Mảng đã có thứ tự sẵn
- Mảng đảo ngược hoàn toàn
- Dữ liệu trùng lặp số lượng lớn
- Chuỗi có tiền tố giống nhau rất dài
- Dữ liệu phân bố lệch hoặc chia nhánh không đều
- Các mẫu dữ liệu gây tăng số lần truy cập bộ nhớ và đệ quy

Thông qua đó, chương trình của đối phương dễ rơi vào các tình huống:

- Cây đệ quy bị lệch sâu
- Số phép so sánh tăng mạnh
- Phân hoạch mất cân bằng
- Tăng số lần copy chuỗi và truy cập RAM
- CPU xử lý nhánh điều kiện kém hiệu quả
- Tốn thêm nhiều hằng số thời gian dù độ phức tạp lý thuyết không đổi

Kết quả là thời gian chạy có thể tăng lên đáng kể, dễ dẫn tới lỗi **TLE (Time Limit Exceeded)** hoặc làm lộ rõ điểm yếu trong cách cài đặt thuật toán.

Dưới đây là phân tích chi tiết cơ chế hoạt động và mục tiêu của từng test case trong bộ dữ liệu:

---

### BÀI A: SẮP XẾP SỐ NGUYÊN (`int`)
*Quy mô cố định: N = 100,000 dòng.*

* **Test 1 (Mảng tăng dần đều):**
  * **Thuật toán mục tiêu:** QuickSort thông thường (chọn pivot ở đầu hoặc cuối mảng).
  * **Cơ chế tăng thời gian:** Khi mảng đã được sắp tăng sẵn, pivot luôn rơi vào phần tử nhỏ nhất hoặc lớn nhất. Điều này làm mảng bị chia cực lệch: một bên gần như rỗng, bên còn lại chứa hầu hết phần tử. Cây đệ quy bị kéo dài thành gần N tầng, khiến số phép so sánh tăng từ `O(n log n)` lên gần `O(n²)`.

* **Test 2 (Mảng ngẫu nhiên hoàn toàn):**
  * **Thuật toán mục tiêu:** Bộ test chuẩn để đo hiệu năng trung bình trong điều kiện bình thường.

* **Test 3 (Mảng hằng trùng lặp tuyệt đối):**
  * **Thuật toán mục tiêu:** QuickSort dùng phân hoạch Lomuto cơ bản.
  * **Cơ chế tăng thời gian:** Khi toàn bộ phần tử đều bằng nhau (`42`), thuật toán vẫn phải quét và chia mảng liên tục dù dữ liệu không thay đổi gì. Các nhánh đệ quy vẫn bị kéo dài gần N tầng, làm chi phí tăng mạnh lên gần `O(n²)`.

* **Test 4 (Mảng răng cưa đổi dấu đan xen):**
  * **Thuật toán mục tiêu:** Cơ chế dự đoán rẽ nhánh của CPU.
  * **Cơ chế tăng thời gian:** Dữ liệu được tạo theo dạng:
    `-a, a, -a, a, -a, a...`
    
    Dấu âm dương thay đổi liên tục khiến CPU khó đoán kết quả của các phép so sánh điều kiện. Điều này làm chương trình phải xử lý nhiều nhánh hơn bình thường, khiến tốc độ thực tế giảm đi.

* **Test 5 (Mảng giảm dần đều):**
  * **Thuật toán mục tiêu:** Heap Sort.
  * **Cơ chế tăng thời gian:** Khi dữ liệu đảo ngược hoàn toàn, quá trình `Heapify` thường phải đổi chỗ phần tử từ gốc xuống tận cuối cây. Việc truy cập dữ liệu liên tục ở các vị trí xa nhau trong mảng làm bộ nhớ đệm hoạt động kém hiệu quả và khiến thời gian xử lý tăng lên.

---

### BÀI B: SẮP XẾP TỪ ĐIỂN CHUỖI (`strlexi`)
*Quy mô cố định: N = 100,000 dòng, độ dài mỗi chuỗi cố định = 100 ký tự.*

* **Test 1 (Mảng hằng chuỗi ký tự lớn):**
  * **Thuật toán mục tiêu:** Radix Sort hoặc các thuật toán so sánh chuỗi trực tiếp.
  * **Cơ chế tăng thời gian:** Tất cả chuỗi đều gồm 100 ký tự `'z'`. Khi so sánh hai chuỗi, chương trình phải kiểm tra gần như toàn bộ 100 ký tự mới biết chúng bằng nhau, gây tốn thời gian xử lý và truy cập bộ nhớ.

* **Test 2 (Bẫy trùng 99 ký tự đầu ngẫu nhiên):**
  * **Thuật toán mục tiêu:** MSD Radix Sort.
  * **Cơ chế tăng thời gian:** Các chuỗi giống nhau ở 99 ký tự đầu và chỉ khác ký tự cuối cùng. Vì vậy thuật toán phải đi sâu gần hết chiều dài chuỗi mới phân loại được dữ liệu, làm tăng số lần đệ quy và thao tác trên bộ nhớ.

* **Test 3 (Mảng hằng chuỗi ký tự nhỏ):**
  * **Thuật toán mục tiêu:** QuickSort chuỗi thông thường.
  * **Cơ chế tăng thời gian:** Toàn bộ chuỗi đều là `'a'`. Các phép so sánh chuỗi phải lặp đi lặp lại qua nhiều ký tự dù kết quả cuối cùng vẫn giống nhau, làm chi phí xử lý tăng mạnh.

* **Test 4 (Bẫy trùng tiền tố dài tăng tuần hoàn):**
  * **Thuật toán mục tiêu:** MSD Radix Sort và các bước `Insertion Sort` xử lý mảng nhỏ.
  * **Cơ chế tăng thời gian:** Chuỗi trùng nhau ở 99 ký tự đầu, ký tự cuối thay đổi tuần hoàn từ `'a'` đến `'z'`. Điều này khiến thuật toán phải đệ quy rất sâu mới tách được dữ liệu, đồng thời tạo nhiều lời gọi hàm và vùng nhớ tạm không cần thiết.

* **Test 5 (Mảng chuỗi ngẫu nhiên hoàn toàn):**
  * **Thuật toán mục tiêu:** Bộ test chuẩn để đánh giá khả năng quản lý bộ nhớ và đối tượng `std::string` ở quy mô lớn.

---

### BÀI C: SẮP XẾP ĐỘ DÀI + TỪ ĐIỂN (`strlenlexi`)
*Quy mô cố định: N = 10,000 dòng. Tất cả test dài 100 ký tự, trừ Test 3 dài 50 ký tự.*

* **Test 1 (Mảng hằng theo khối lặp):**
  * **Thuật toán mục tiêu:** Bucket Sort theo độ dài và MSD Radix Sort.
  * **Cơ chế tăng thời gian:** Tất cả chuỗi đều dài 100 nên việc phân loại theo độ dài không còn tác dụng. Ngoài ra, nhiều dòng giống hệt nhau được lặp thành từng khối lớn, khiến thuật toán phải xử lý lặp lại rất nhiều dữ liệu tương tự nhau.

* **Test 2 (Mảng chuỗi ngẫu nhiên hoàn toàn):**
  * **Thuật toán mục tiêu:** Bộ test chuẩn để đo chi phí của phép so sánh kép: so độ dài trước rồi mới so từ điển.

* **Test 3 (Mảng hằng chuỗi ký tự nhỏ ngắn):**
  * **Thuật toán mục tiêu:** Các thuật toán so sánh chuỗi phức tạp.
  * **Cơ chế tăng thời gian:** Mọi chuỗi đều giống nhau và có độ dài 50. Thuật toán vẫn phải kiểm tra cả độ dài lẫn nội dung chuỗi nhiều lần dù dữ liệu không có khác biệt.

* **Test 4 (Bẫy trùng tiền tố dài tuần hoàn):**
  * **Thuật toán mục tiêu:** LSD Radix Sort (quét từ phải sang trái).
  * **Cơ chế tăng thời gian:** Vì chuỗi dài 100 ký tự và giống nhau gần như toàn bộ, thuật toán phải quét đủ cả 100 lượt. Mỗi lượt lại cần sao chép dữ liệu giữa các mảng tạm, làm tăng mạnh số thao tác trên RAM và khiến chương trình chậm đi đáng kể.

* **Test 5 (Bẫy tiền tố xen kẽ nhị phân):**
  * **Thuật toán mục tiêu:** QuickSort 3 nhánh và các thuật toán phân hoạch chuỗi.
  * **Cơ chế tăng thời gian:** Chuỗi trùng 99 ký tự đầu, ký tự cuối chỉ xen kẽ giữa `'a'` và `'z'`. Điều này làm dữ liệu bị chia không đều, khiến thuật toán phải thực hiện nhiều phép so sánh sâu mới tách được các nhóm phần tử.
## 2. Quá trình tối ưu và kết quả qua 2 lần chạy

### Lần chạy thứ 1

Ở vòng đầu tiên, nhóm ưu tiên lựa chọn các thuật toán có tốc độ trung bình cao nhằm đạt thời gian thực thi tốt nhất trên bộ dữ liệu thông thường.

| Bài toán | Thuật toán sử dụng | Thời gian |
|----------|-------------------|------------|
| A (`int`) | QuickSort | 46 ms |
| B (`strlexi`) | MSD Radix Sort + Insertion Sort | 125 ms |
| C (`strlenlexi`) | LSD Radix Sort | 93 ms |

#### Bài A (`int`)

Nhóm sử dụng QuickSort do đây là thuật toán có hiệu năng trung bình rất tốt và chi phí bộ nhớ thấp. Trên các bộ dữ liệu ngẫu nhiên hoặc phân bố tương đối đều, QuickSort đạt tốc độ cao nhất trong số các thuật toán đã thử nghiệm.

Kết quả thực tế cho thấy thời gian chỉ khoảng **46 ms**, là bài có tốc độ tốt nhất trong lần chạy đầu.

#### Bài B (`strlexi`)

Đối với bài toán sắp xếp chuỗi từ điển, nhóm sử dụng MSD Radix Sort kết hợp Insertion Sort cho các đoạn dữ liệu nhỏ.

Giải pháp này tận dụng việc phân loại trực tiếp theo ký tự thay vì so sánh toàn bộ chuỗi, giúp giảm đáng kể số phép so sánh trên dữ liệu ngẫu nhiên. Tuy nhiên khi gặp các chuỗi có tiền tố dài giống nhau, Insertion Sort bắt đầu trở thành điểm nghẽn do phải thực hiện nhiều phép so sánh chuỗi sâu.

#### Bài C (`strlenlexi`)

Nhóm lựa chọn LSD Radix Sort vì dữ liệu chủ yếu là chuỗi có độ dài giới hạn. Thuật toán hoạt động ổn định và cho thời gian thực thi khá tốt ở vòng đầu với kết quả **93 ms**.

Tuy nhiên cách tiếp cận này yêu cầu quét qua toàn bộ chiều dài chuỗi ở mỗi lần xử lý, khiến chi phí tăng mạnh khi gặp các bộ test có tiền tố dài hoặc số lượng chuỗi lớn.

---

### Đánh giá sau vòng 1

Kết quả vòng đầu cho thấy các thuật toán được lựa chọn đều có hiệu năng cao trong điều kiện bình thường. Tuy nhiên phần lớn các thuật toán vẫn tồn tại những trường hợp dữ liệu đặc biệt có thể làm giảm hiệu năng đáng kể.

Sau khi công bố bộ test đối kháng giữa các nhóm, nhóm nhận thấy nhiều test được thiết kế nhằm khai thác trực tiếp các điểm yếu của QuickSort và Radix Sort, đặc biệt là:

- Dữ liệu đã có thứ tự sẵn.
- Dữ liệu trùng lặp số lượng lớn.
- Chuỗi có tiền tố dài giống nhau.
- Các trường hợp gây mất cân bằng phân hoạch hoặc tăng chi phí đệ quy.

Điều này buộc nhóm phải thay đổi chiến lược tối ưu ở vòng thứ hai.

---

### Lần chạy thứ 2

Sau khi phân tích các bộ test đối kháng, nhóm tập trung vào mục tiêu quan trọng nhất: đảm bảo hiệu năng ổn định trong trường hợp xấu thay vì chỉ tối ưu cho dữ liệu trung bình.

| Bài toán | Thuật toán tối ưu | Thời gian |
|----------|------------------|------------|
| A (`int`) | Heap Sort gián tiếp | 78 ms |
| B (`strlexi`) | MSD Radix Sort gián tiếp | 78 ms |
| C (`strlenlexi`) | Indirect QuickSort 3-Way + Insertion Sort | 187 ms |

#### Bài A (`int`)

QuickSort được thay thế bằng Heap Sort.

Mặc dù thời gian trung bình không còn nhanh bằng QuickSort trên dữ liệu đẹp, Heap Sort có ưu điểm lớn là luôn duy trì độ phức tạp `O(n log n)` bất kể dữ liệu đầu vào.

Nhóm đồng thời áp dụng:

- Sắp xếp gián tiếp thông qua mảng chỉ số.
- Mảng tĩnh toàn cục thay cho cấu trúc cấp phát động.

Nhờ đó chương trình không còn bị ảnh hưởng bởi các bộ test gây mất cân bằng phân hoạch.

#### Bài B (`strlexi`)

Thuật toán MSD Radix Sort tiếp tục được giữ lại do vẫn phù hợp với bài toán chuỗi.

Tuy nhiên nhóm thay đổi cách tổ chức dữ liệu:

- Giữ nguyên toàn bộ chuỗi trên RAM.
- Chỉ thao tác trên mảng chỉ số.
- Đưa các cấu trúc phụ trợ sang bộ nhớ tĩnh.
- Loại bỏ Insertion Sort ở các nhánh nhỏ.

Những thay đổi này giúp giảm mạnh chi phí dịch chuyển chuỗi và tránh được các bộ test có tiền tố dài giống nhau.

Kết quả thời gian giảm từ **125 ms xuống còn 78 ms**.

#### Bài C (`strlenlexi`)

Đây là bài chịu ảnh hưởng nhiều nhất từ bộ test đối kháng.

LSD Radix Sort ở vòng đầu phải quét toàn bộ chiều dài chuỗi trong mọi trường hợp, dẫn đến lượng thao tác rất lớn khi dữ liệu có chiều dài tối đa.

Nhóm chuyển sang QuickSort 3 nhánh kết hợp sắp xếp gián tiếp.

Ưu điểm của hướng tiếp cận mới:

- Ngắt so sánh ngay khi phát hiện ký tự khác nhau đầu tiên.
- Gom các phần tử bằng nhau chỉ trong một lần phân hoạch.
- Giảm đáng kể số lần sao chép chuỗi.
- Kết hợp Insertion Sort trên các đoạn nhỏ để giảm chi phí đệ quy.

Nhờ đó chương trình vượt qua toàn bộ bộ test đối kháng mà không gặp lỗi TLE.

---

### Kết luận

Qua hai vòng contest, nhóm nhận thấy rằng một thuật toán có tốc độ rất cao trên dữ liệu thông thường chưa chắc là lựa chọn tối ưu khi xuất hiện các bộ test đối kháng.

Các cải tiến ở vòng 2 tập trung vào ba hướng chính:

- Đảm bảo độ phức tạp ổn định trong trường hợp xấu.
- Giảm tối đa số lần dịch chuyển dữ liệu trên RAM.
- Hạn chế chi phí đệ quy và so sánh chuỗi sâu.

Nhờ các thay đổi này, toàn bộ chương trình có thể vượt qua các bộ test đối kháng với độ ổn định và độ tin cậy cao hơn đáng kể so với phiên bản ban đầu.
