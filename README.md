# BÁO CÁO ĐỒ ÁN SORT BENCHMARK 

* **Môn học:** Cấu trúc dữ liệu và Giải thuật
* **Lớp:** 25CTT6 
* **Giảng viên:**  Huỳnh Lâm Hải Đăng
* **Giảng viên:**  Nguyễn Ngọc Đức
* **Giảng viên:**  Phạm Trọng Nghĩa
* **Sinh viên thực hiện:** Trần Tấn Phước - Trần Nhất Phong - Châu Thị Thảo Vân
* **MSSV:** [25120423-25120414-25120467]

---

## 1. Phân tích thực nghiệm và Quá trình tối ưu qua 2 vòng Contest


### Lần chạy thứ 1:
* **Bài A (Sắp xếp số nguyên - `int`):** Cài đặt bằng **QuickSort thông thường** đạt tốc độ tối ưu **46 ms** do dữ liệu vòng đầu phân bố đều, không xuất hiện các trường hợp biến dạng phân hoạch.
* **Bài B (Sắp xếp từ điển - `strlexi`):** Cài đặt bằng **Radix Sort** kết hợp với **Insertion Sort** đạt thời gian chạy hệ thống là **125 ms**.
* **Bài C (Sắp xếp độ dài + từ điển - `strlenlexi`):** Cài đặt bằng **Radix Sort** đạt thời gian chạy hệ thống là **93 ms**.

### Lần chạy thứ 2:

#### Thống kê kết quả cài đặt tối ưu nhất ở lần 2:
| Bài toán | Thuật toán tối ưu nhất lần 2 | Thời gian chạy | Phương thức tối ưu hóa cốt lõi |
| :--- | :--- | :--- | :--- |
| **Bài A (`int`)** | **Heap Sort gián tiếp** | **78 ms** | Chuyển sang Heap Sort để cố định độ phức tạp ở mức $O(n \log n)$ trong mọi kịch bản dữ liệu, kết hợp loại bỏ chi phí dịch chuyển vùng nhớ bằng mảng chỉ số tĩnh. |
| **Bài B (`strlexi`)** | **Radix Sort cải tiến** | **78 ms** | Phân loại ký tự theo tầng thay vì so sánh cặp, triệt tiêu hằng số so sánh chuỗi cực lớn khi gặp các chuỗi có độ dài kịch trần 100 ký tự. |
| **Bài C (`strlenlexi`)** | **Indirect QuickSort 3-Way + Insertion Sort** | **187 ms** | Áp dụng phân hoạch 3 nhánh Dijkstra để cô lập chuỗi trùng lặp trong $O(n)$, ngắt đệ quy sớm bằng Insertion Sort ở đoạn mảng nhỏ ($< 16$ phần tử) và sắp xếp gián tiếp qua mảng chỉ số số nguyên. |

---

## 2. Chiến lược thiết kế bộ sinh test case trong `test_gen.cpp`

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
## 3. Phân tích giải thuật tối ưu lần chạy 2. Cách tối ưu so với lần 1 

# Bài A : Int
Ở lần chạy đầu tiên, nhóm sử dụng **QuickSort thông thường** đạt hiệu năng tốt ở điều kiện thường. Tuy nhiên, khi đối mặt với các bộ test hack chứa mảng hằng hoặc dữ liệu răng cưa (Zig-zag) ở Vòng 2, QuickSort bị mất cân bằng phân hoạch nghiêm trọng đẩy độ phức tạp lên $O(n^2)$ và dính lỗi TLE. Nhóm đã chuyển dịch sang **Heap Sort đệ quy** để cố định thời gian chạy luôn ở mức $O(n \log n)$ trong mọi kịch bản dữ liệu và đạt mốc thời gian **78 ms**.
#### 1. Tình huống thực tế và lý do đổi thuật toán
* **Ở Lần chạy 1:** Bản đầu tiên dùng **QuickSort** chạy rất nhanh vì dữ liệu phân bố đều.
* **Ở Lần chạy 2:** Khi bị các nhóm khác (có nhóm em) nộp test hack (như mảng gồm các số giống hệt nhau hoặc mảng xếp răng cưa), QuickSort bị mất cân bằng khi chia đôi mảng. Tốc độ của nó bị tụt thảm hại và dính lỗi quá thời gian (TLE).
* **Giải pháp ở Lần 2:** Chuyển sang dùng **Heap Sort đệ quy**. Thuật toán này có ưu điểm là giữ nguyên tốc độ ổn định trong mọi trường hợp (bất kể dữ liệu có bị trùng lặp hay răng cưa) và đạt mốc thời gian **78 ms**.

#### 2. Các bước cải tiến từ bản Heap Sort gốc để chạy nhanh hơn nữa

Từ code Heap Sort cơ bản, nhóm đã thực hiện 2 cải tiến nhỏ để tối ưu hóa bộ nhớ và tăng tốc cho CPU:

* **Sắp xếp gián tiếp qua mảng chỉ số (Indirect Sorting):**
  * *Nhược điểm bản cũ:* Mỗi lần đổi chỗ các phần tử trên cây Heap, code phải gọi hàm `swap` để bê nguyên giá trị số nguyên ở ô nhớ này đặt sang ô nhớ khác trên RAM. Việc này làm tốn thời gian ghi dữ liệu của máy tính.
  * *Cải tiến mới:* Tạo một mảng số nguyên phụ tên là `p` để lưu vị trí (0, 1, 2, 3...). Mảng dữ liệu số gốc `arr` được giữ đứng yên 100% trên RAM. Khi cần so sánh hay đổi chỗ, code chỉ việc hoán đổi các con số chỉ vị trí trên mảng `p`. Máy tính di chuyển các con số chỉ số này nhanh hơn nhiều so với việc di chuyển dữ liệu thô, giúp tiết kiệm thời gian.
* **Tạo bộ nhớ tĩnh ngay từ đầu (Global Static Allocation):**
  * *Nhược điểm bản cũ:* Dữ liệu truyền vào được lưu bằng `vector<int> a(n)`. Bản chất của `vector` là bộ nhớ động, tức là khi bật chương trình lên, máy tính mới bắt đầu đi tìm và cấp phát các ô nhớ trống trên RAM. Việc này tạo ra một khoảng trễ (Overhead) không đáng có.
  * *Cải tiến mới:* Thay `vector` bằng mảng tĩnh thuần C (`int arr[100005]`) khai báo nằm ngoài các hàm. Bộ nhớ này sẽ được máy tính chuẩn bị sẵn sàng ngay từ khi dịch code xong. Khi chạy, CPU chỉ việc lao vào đọc dữ liệu một đường thẳng băng, giúp code chạy mượt mà và an toàn trước mọi bộ test khó.# Bài B : Strlexi
 
# Bài B : Strlexi
Bản cài đặt Bài B ở lần 2 đã chứng minh sự vượt trội về mặt giải thuật khi ép xung thời gian chạy từ **125 ms** ở lần 1 xuống **78 ms** ở lần 2. Quá trình cải tiến và tối ưu hóa cấu trúc mã nguồn từ phiên bản đầu lên phiên bản thứ hai được triển khai dựa trên ba chiến thuật cốt lõi sau:

1. **Chuyển dịch từ Sắp xếp trực tiếp sang Sắp xếp gián tiếp (Indirect Sorting):**
   * *Hạn chế ở lần 1:* Bản cài đặt đầu tiên truyền vào hàm một `vector<string>& a`. Tại bước rẽ nhánh phân loại dữ liệu, giải thuật thực hiện dịch chuyển trực tiếp nội dung các chuỗi thô thông qua cơ chế `move(a[i])` sang mảng tạm rồi gán ngược lại. Mặc dù đã tối ưu bằng toán tử dịch chuyển con trỏ, CPU vẫn phải liên tục quản lý, cấp phát lại các cấu trúc vùng nhớ động (Dynamic memory block) nặng nề của đối tượng `std::string` trên RAM khi quy mô mảng lên tới $10^5$ dòng.
   * *Cải tiến ở lần 2:* Giải thuật giữ mảng chuỗi gốc `a` đứng yên 100% trên bộ nhớ trong suốt quá trình chạy. Nhóm thiết lập một mảng số nguyên phụ `int p[100005]` để lưu trữ chỉ số vị trí (index) ban đầu của chuỗi. Mọi thao tác hoán đổi, phân loại và trích xuất ký tự đều tác động gián tiếp thông qua mảng `p`. Do chi phí di chuyển dữ liệu kiểu số nguyên (`int`) trên thanh ghi CPU thấp hơn hàng trăm lần so với đối tượng chuỗi, điểm nghẽn về hằng số thời gian dịch chuyển bộ nhớ đã được giải phóng hoàn toàn.

2. **Khử chi phí cấp phát bộ nhớ động của Stack (Global Static Allocation):**
   * *Hạn chế ở lần 1:* Bản cũ thực hiện khởi tạo động các mảng đếm tần suất `vector<int> cnt` và mảng vị trí `vector<int> pos` ngay bên trong hàm đệ quy `msd`. Do đặc thù của MSD Radix Sort là phân rã và gọi đệ quy sâu thành hàng ngàn nhánh nhỏ, việc CPU phải liên tục cấp phát (allocate) và giải phóng (deallocate) các vector này trên Stack Frame ở mỗi tầng gọi hàm đã tạo ra một chi phí hao tổn hệ thống (Overhead) cực kỳ lớn.
   * *Cải tiến ở lần 2:* Đưa hai mảng phụ trợ kích thước lớn (`p` và `aux`) ra ngoài phạm vi toàn cục dưới dạng bộ nhớ tĩnh (`global static array`). Bên trong hàm đệ quy lúc này chỉ khai báo duy nhất một mảng đếm tần suất cấu trúc thuần C kích thước siêu nhỏ cố định: `int count[28] = {0};`. Cấu trúc này triệt tiêu hoàn toàn gánh nặng tạo/hủy mảng của Stack Frame, CPU chỉ việc tái sử dụng vùng nhớ tĩnh có sẵn để quét tuyến tính, tối ưu hóa tối đa tốc độ vòng lặp.

3. **Loại bỏ hoàn toàn Insertion Sort tại các nhánh mảng nhỏ (Bẻ gãy bẫy chuỗi trùng tiền tố):**
   * *Hạn chế ở lần 1:* Bản cũ tích hợp một ngưỡng `CUTOFF = 32` để chuyển sang `insertion_sort` khi đoạn con nhỏ đi nhằm tiết kiệm chi phí đệ quy. Tuy nhiên, hàm `insertion_sort` này lại thực hiện so sánh cặp trực tiếp giữa các chuỗi (`a[j] > key`). Khi đối phương nộp bộ test "hack" chứa các chuỗi có tiền tố giống nhau hoàn toàn (ví dụ giống nhau 99 ký tự đầu), hàm này buộc CPU phải duyệt lặp đi lặp lại sâu từ đầu đến cuối nội dung chuỗi, làm phá sản hoàn toàn lợi thế tuyến tính của Radix Sort.
   * *Cải tiến ở lần 2:* Nhóm quyết định xóa bỏ hoàn toàn tầng gộp `CUTOFF`, cho phép MSD đệ quy tự nhiên đến tận cùng (`l >= r`). Vì bản chất MSD phân loại độc lập theo từng vị trí ký tự `d` tại thời điểm xét, khi gặp bẫy tiền tố dài, nó chỉ lướt qua ký tự tại vị trí `d` đó đúng một lần trong vòng lặp $O(n)$ của tầng đệ quy tương ứng chứ không thực hiện so sánh cặp lại từ đầu chuỗi. Cải tiến này giúp giải thuật đạt trạng thái "miễn nhiễm" trước các bộ test bẫy chuỗi trùng tiền tố dài.
## Bài C : Strlenlexi

Bài C là bài toán có độ phức tạp cao nhất khi tiêu chí sắp xếp phải phối hợp cả độ dài chuỗi lẫn thứ tự từ điển, đồng thời phải chịu áp lực lớn từ các bộ test case phối hợp cực đoan ở vòng đối kháng. Việc thay đổi từ thuật toán LSD Radix Sort phân nhóm ở lần 1 sang QuickSort 3 nhánh gián tiếp ở lần 2 mang lại sự nâng cấp vượt bậc về hiệu năng, khắc phục hoàn toàn lỗi chạy quá thời gian (TLE) và vượt qua toàn bộ hệ thống test với thời gian tối ưu **187 ms**.

Quá trình thay đổi tư duy và tối ưu hóa cấu trúc mã nguồn được phân tích qua ba điểm cốt lõi sau:

1. **Khắc phục triệt để lỗi quá tải thời gian (TLE) ở Test 50:**
   * *Hạn chế ở lần 1:* Bản cài đặt đầu tiên sử dụng **LSD Radix Sort** chạy vòng lặp quét ký tự từ phải qua trái theo chiều dài chuỗi `maxLen`. Khi gặp bộ test đối kháng chứa lượng chuỗi lớn có độ dài kịch trần 100 ký tự (như Test 50), vòng lặp bắt buộc phải chạy đủ 100 lần. Tại mỗi vòng, code lại ép CPU phải sao chép dữ liệu chuỗi thô qua lại giữa mảng gốc và mảng tạm `tmp`. Việc phải thực hiện hàng triệu lượt copy chuỗi nặng nề trên RAM đã đốt cháy tài nguyên thời gian của hệ thống, dẫn đến lỗi TLE.
   * *Cải tiến ở lần 2:* Nhóm chuyển sang giải thuật **QuickSort 3 nhánh kết hợp so sánh trực tiếp**. Hàm so sánh `compareString` mới sẽ quét từ trái qua phải và ngắt lệnh (return) ngay lập tức khi tìm thấy ký tự khác biệt đầu tiên. Nhờ vậy, code không bị ép phải chạy qua đủ 100 ký tự một cách mù quáng, giảm thiểu tối đa số phép tính toán của CPU.

2. **Triệt tiêu gánh nặng sao chép chuỗi nhờ Sắp xếp gián tiếp (Indirect Sorting):**
   * *Hạn chế ở lần 1:* Ở bản cũ, việc gán đổi dữ liệu chuỗi thô diễn ra liên tục ở mọi tầng quét ký tự, làm phình to hằng số thời gian thực thi trên RAM.
   * *Cải tiến ở lần 2:* Toàn bộ mảng chuỗi gốc được giữ cố định trên bộ nhớ trong suốt quá trình chạy. Nhóm sử dụng mảng chỉ số tĩnh toàn cục `int p[100005]`, mọi phép so sánh và hoán đổi vị trí (`swap`) chỉ thực hiện trên mảng số nguyên `p` này. Việc thay thế thao tác dịch chuyển chuỗi bằng dịch chuyển số nguyên thuần túy trên thanh ghi giúp giải phóng hoàn toàn gánh nặng cho bộ nhớ RAM, giúp code chạy cực kỳ nhẹ nhàng.

3. **Hóa giải bẫy dữ liệu trùng lặp nhờ Phân hoạch 3 nhánh Dijkstra:**
   * *Hạn chế ở lần 1:* Thuật toán LSD Radix Sort phân nhóm ở lần 1 không có khả năng tự tối ưu hoặc ngắt sớm khi gặp các cụm dữ liệu có cấu trúc trùng lặp lớn, dẫn đến việc lãng phí thời gian quét qua các ô nhớ trống.
   * *Cải tiến ở lần 2:* Nhóm áp dụng giải thuật **QuickSort 3 nhánh của Dijkstra** phối hợp cùng bộ sinh số ngẫu nhiên để chọn phần tử chốt (pivot), chia mảng thành 3 vùng độc lập (`< pivot`, `== pivot`, `> pivot`). Khi đối mặt với dữ liệu chứa lượng chuỗi giống nhau lớn, giải thuật gom sạch và cô lập vùng bằng nhau này chỉ trong đúng một lần duyệt tuyến tính $O(n)$ rồi ngắt hoàn toàn đệ quy vào đó. Đồng thời, hệ thống tự động chuyển sang dùng `insertionSort` trên mảng chỉ số khi đoạn con nhỏ hơn 16 phần tử, tận dụng tối đa cơ chế bộ nhớ đệm (Cache Locality) của phần cứng để đạt tốc độ tối đa.
