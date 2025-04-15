# BÀI TẬP 3 

## CHUYÊN ĐỀ TỔ CHỨC DỮ LIỆU 

**KÌ 2 2024-2025, HỆ ĐÀO TẠO TỪ XA**

---oOo---

**Lưu ý**: Bài tập này nộp file Word (.doc) hoặc file PDF (.pdf). Những câu yêu cầu viết code thì viết bằng ngôn ngữ C/C++ và trình bày kết quả chạy thử.

### 1. (3 đ) Cấu trúc một nút của cây tìm kiếm nhị phân (Binary Search Tree) các số nguyên được khai báo như sau:
```cpp
struct NODE 
{ 
}; 
int key; 
NODE *left, *right;
```
Giả sử các nút trong cây có khóa (key) phân biệt.

a) Viết hàm `NODE* search(NODE *root, int k)` để tìm nút mang khóa `k` trong cây có nút gốc trỏ bởi `root` bằng kĩ thuật **lặp** và hàm `searchRec` bằng kĩ thuật **đệ qui**.

b) Viết hàm `NODE* max(NODE *root)` để tìm nút mang khóa lớn nhất trong cây bằng kĩ thuật **lặp** và hàm `maxRec` bằng kĩ thuật **đệ qui**.

c) Viết hàm `void sort(NODE *root)` để xuất ra các khóa trong cây theo thứ tự **tăng dần**.

d) Cây được gọi là **cân bằng trọng lượng hệ số 𝛼 (𝛼 ≥ 1)** nếu tại mọi nút `r` trong cây, số lượng nút của cây con trái và cây con phải của `r` lệch nhau không quá `𝛼` lần; trong đó nút rỗng (con trỏ NULL) cũng được tính là 1 nút.

Viết hàm `int balanced(NODE *root, double alpha)` để kiểm tra cây có cân bằng trọng lượng hệ số 𝛼 hay không.

---

### 2. (2 đ) Cây biểu thức số học

a) Vẽ cây biểu thức số học của biểu thức `1 – (2 – 3) * (4 + 5)!`

b) Duyệt trước cây (a) để in ra biểu thức dạng **tiền tố**

c) Duyệt sau cây (a) để in ra biểu thức dạng **hậu tố**

---

### 3. (5 đ) Cài đặt chương trình xử lý biểu thức số học trên số nguyên với các phép toán: cộng (+), trừ (-), nhân (*), chia nguyên (/), chia dư (%), đối (-) và giai thừa (!).

a) Cho nhập và phân tích biểu thức.  

b) Tính giá trị của biểu thức. 

c) Xuất biểu thức dạng **tiền tố**, **hậu tố** và **trung tố**. (Đối chiếu kết quả làm tay ở Câu 2).

Mở rộng biểu thức số học, ta cho phép biểu thức có thể gồm các toán hạng là **biến**, trong đó biến là một **chữ cái**. Ví dụ, `a + 20 * b` là biểu thức có chứa các biến `a`, `b`.  

Ta gọi **lệnh** là chuỗi có dạng:

`<var-1> = <exp-1> ; … ; <var-n> = <exp-n> ; <exp>`

Trong đó `<var-1>, …, <var-n>` là các biến và `<exp-1>, …, <exp-n>` là các biểu thức mô tả việc tính các biểu thức và “gán” giá trị cho các biến tương ứng. Giá trị của lệnh là **giá trị của biểu thức cuối cùng `<exp>`**. 

Ví dụ lệnh:

`a = 1 ; b = 10 * a ; a + 20 * b`

có giá trị là **201**.

Viết chương trình cho nhập lệnh và tính giá trị của lệnh (hoặc thông báo nếu chuỗi không đúng **“cú pháp”** hoặc **“ngữ nghĩa”**).

---HẾT---