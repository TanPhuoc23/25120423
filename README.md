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

Để tối đa hóa thời gian chạy code từ các nhóm khác trong lớp, bộ sinh test `test_gen.cpp` của nhóm được cấu hình để tự động tạo ra đúng 15 bộ test case đối kháng (chia đều cho 3 bài toán, mỗi bài 5 test). 

Mục tiêu của bộ test này là bắt bài cơ chế vận hành của CPU, RAM và Giải thuật để ép code của đối phương chạm ngưỡng thời gian chạy tồi nhất, dễ dính lỗi **TLE (Quá thời gian)** hoặc nghẽn hằng số phần cứng.

Dưới đây là phân tích chi tiết cho bộ test:

---

### Dạng 1: Mảng tăng dần/giảm dần 
* **Áp dụng cho:** Test 1 của bài `int` và Test 1 của bài `strlexi`.
* **Thuật toán mục tiêu:** QuickSort thông thường sử dụng phân hoạch Lomuto hoặc Hoare truyền thống (luôn chọn phần tử chốt pivot cố định ở biên trái hoặc biên phải).
* **Lý do chọn mục tiêu này:** QuickSort là giải thuật phổ biến nhất được các bạn sinh viên cài đặt nhờ hằng số thời gian nhỏ và chạy rất nhanh ở điều kiện dữ liệu ngẫu nhiên.
* **Tại sao test này làm tăng thời gian chạy:** Khi mảng đã được tăng dần đều (`int`) hoặc là một mảng hằng chứa toàn ký tự lớn nhất `'z'` (`strlexi`), việc chọn pivot ở biên sẽ luôn bốc trúng phần tử tồi nhất mảng (nhỏ nhất hoặc lớn nhất). Lúc này, mảng con thay vì được chia đôi cân đối thì lại bị lệch hẳn: một bên chứa 0 phần tử, bên còn lại giữ nguyên $N-1$ phần tử. Cây đệ quy thẳng tuột thành một đường thẳng đứng dài $N$ tầng. Số phép so sánh tăng vọt từ $O(n \log n)$ thành $O(n^2)$, ép code đối phương dính TLE ngay lập tức.

---

### Dạng 2: Dữ liệu ngẫu nhiên / Vô hiệu hóa bộ lọc độ dài
* **Áp dụng cho:** Test 2 bài `int`, Test 2 bài `strlexi`, Test 1 và Test 2 bài `strlenlexi`.
* **Thuật toán mục tiêu:** Các thuật toán phân loại thô dựa trên bộ lọc độ dài chuỗi (như Bucket Sort theo độ dài).
* **Lý do chọn mục tiêu này:** Nhiều nhóm giải quyết Bài C (`strlenlexi`) bằng cách lọc gom nhóm các chuỗi có cùng độ dài vào từng mảng riêng biệt rồi mới dùng Radix Sort, QuickSort hoặc MergeSort để xử lý nội bộ nhằm tăng tốc.
* **Tại sao test này làm tăng thời gian chạy:**
  * Ở điều kiện thường (Test 2 bài `int`, Test 2 bài `strlexi`, Test 1 bài `strlenlexi`), đây là bộ test nền tảng để đánh giá xem code đối thủ quản lý vùng nhớ con trỏ ổn định hay không khi quy mô mảng lên tới $10^5$ dòng.
  * Riêng ở Bài C, **Test 2** ép toàn bộ $10.000$ chuỗi đều có **độ dài bằng 100 ký tự tuyệt đối**. Việc này làm bẻ gãy hoàn toàn bộ lọc độ dài của đối thủ. Toàn bộ lượng dữ liệu khổng lồ bị dồn ứ cục bộ vào đúng một nhóm duy nhất, ép giải thuật của đối phương phải gánh trọn phần so sánh từ điển nặng nề ở phía sau mà không được lợi thế sắp xếp theo độ dài chuỗi.

---

### Dạng 3: Mảng hằng trùng lặp toàn bộ
* **Áp dụng cho:** Test 3 bài `int`, Test 3 bài `strlexi`, Test 3 bài `strlenlexi`.
* **Thuật toán mục tiêu:** QuickSort phân hoạch Lomuto cơ bản và các giải thuật sao chép nội dung chuỗi nặng (MergeSort).
* **Lý do chọn mục tiêu này:** Merge Sort và QuickSort thông thường rất ít khi kiểm tra điều kiện mảng trùng lặp trước khi thực hiện chia đệ quy.
* **Tại sao test này làm tăng thời gian chạy:**
  * Với QuickSort dùng phân hoạch Lomuto, giải thuật không có cơ chế dừng lại khi gặp phần tử bằng chốt. Gặp mảng chứa toàn số `42`, vòng lặp phân hoạch vẫn chạy qua toàn bộ mảng một cách mù quáng nhưng cây đệ quy vẫn bị lệch $N$ tầng, đẩy tốc độ lên $O(n^2)$.
  * Với các bài chuỗi (`strlexi`, `strlenlexi`), việc các chuỗi giống hệt nhau bắt buộc các hàm so sánh cặp của đối thủ phải lướt qua đủ 100 ký tự mới đưa ra được kết quả. Việc so sánh lặp đi lặp lại nội dung chuỗi thô nặng nề trực tiếp trên RAM làm nghẽn băng thông xử lý của hệ thống.

---

### Dạng 4: Bẫy trùng tiền tố dài 
* **Áp dụng cho:** Test 4 bài `int`, Test 4 bài `strlexi`, Test 4 bài `strlenlexi`.
* **Thuật toán mục tiêu:** MSD Radix Sort (Sắp xếp từ trái qua phải) và các hàm `Insertion Sort` dọn dẹp mảng con nhỏ.
* **Lý do chọn mục tiêu này:** Radix Sort là vua tốc độ tuyến tính được nhiều nhóm chọn để xử lý bài toán chuỗi nhằm đạt tốc độ tuyệt đối.
* **Tại sao test này làm tăng thời gian chạy:**
  * **Đối với bài `int` (Test 4):** Việc sinh số đan xen khối lớn và khối nhỏ luân phiên liên tục làm phá sản hoàn toàn các giải thuật dò đoán nhánh của CPU, ép máy tính phải thực hiện tối đa số phép so sánh ở mọi tầng phân chia.
  * **Đối với bài chuỗi (Test 4 ở bài B và C):** Nhóm sinh ra hàng vạn chuỗi dài tối đa 100 ký tự, nhưng có **99 ký tự đầu giống hệt nhau**, chỉ khác đúng ký tự thứ 100 ở cuối. Khi quét từ trái qua phải, MSD Radix Sort thấy ký tự giống nhau nên liên tục bẻ nhánh đệ quy sâu vô tận xuống các tầng dưới. Việc ép CPU sinh hàng vạn khung bộ nhớ (Stack Frame) trống không những làm chậm tốc độ chạy thực tế mà còn rất dễ kích hoạt lỗi **Stack Overflow**.

---

### Dạng 5: Phá vỡ bộ nhớ đệm (Cache Miss)
* **Áp dụng cho:** Test 5 bài `int`, Test 5 bài `strlexi`, Test 5 bài `strlenlexi`.
* **Thuật toán mục tiêu muốn "triệt hạ":** Heap Sort và cơ chế quản lý bộ nhớ đệm phần cứng (Cache Locality).
* **Lý do chọn giải thuật này:** Các thuật toán giữ độ phức tạp ổn định như Heap Sort thường dựa vào cấu trúc mảng phẳng để quản lý cây nhị phân.
* **Tại sao bộ test này làm tăng thời gian chạy:**
  * **Đối với bài `int` (Test 5):** Mảng giảm dần đều từ `100000` về `1` ép hàm `Heapify` mỗi lần trích xuất phần tử lớn nhất đều phải hoán đổi và chạy xuyên hết chiều sâu của cây nhị phân (từ gốc xuống ngọn). Do cây Heap lưu trên mảng phẳng, việc ép CPU liên tục nhảy cách quãng các ô nhớ nằm rất xa nhau ($2i+1$ và $2i+2$) làm phá sản cơ chế lưu bộ nhớ đệm. CPU dính lỗi **Cache Miss kịch trần**, phải mất thời gian lội ngược ra RAM để tìm dữ liệu, khiến tốc độ xử lý bị kéo tụt thảm hại.
  * **Đối với bài chuỗi (Test 5 ở bài B và C):** Việc biến thiên ký tự tuần hoàn tạo ra một cấu trúc mảng răng cưa chuỗi cực kỳ phức tạp. Phép toán này ép các hàm so sánh cặp trực tiếp chuỗi phải duyệt sâu vào nội dung để phân loại, đồng thời làm phân tán các con trỏ vùng nhớ động của `std::string` trên RAM, triệt hạ hoàn toàn tốc độ xử lý của đối thủ.
---
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
