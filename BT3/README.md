## Bài tập 1: Cây Tìm Kiếm Nhị Phân (Binary Search Tree)

### Mô tả cài đặt

Cây tìm kiếm nhị phân được cài đặt với cấu trúc nút:

```cpp
struct NODE {
    int key;
    char data; // Trường dữ liệu mẫu, có thể mở rộng
    NODE* left, * right;
};
```

### Các file trong project

- **BST.h**: Header file chứa khai báo cấu trúc và các hàm
- **Search.cpp**: Cài đặt các hàm tìm kiếm (lặp và đệ quy)
- **Max.cpp**: Cài đặt các hàm tìm khóa lớn nhất (lặp và đệ quy)
- **Sort.cpp**: Cài đặt hàm sắp xếp các khóa tăng dần
- **Balance.cpp**: Cài đặt hàm kiểm tra cân bằng trọng lượng hệ số α
- **Utility.cpp**: Các hàm tiện ích (tạo nút, chèn nút, giải phóng cây)
- **TestCases.h/cpp**: Các hàm kiểm thử
- **BinarySearchTree.cpp**: File chương trình chính

### Cấu trúc dữ liệu với ba loại cây thử nghiệm

1. **Cây cân bằng** - Cấu trúc:
   ```
               50(A)
             /       \
         30(B)       70(C)
        /     \     /     \
     20(D)  40(E) 60(F)  80(G)
   ```

2. **Cây lệch phải** - Cấu trúc:
   ```
        10(A)
          \
          20(B)
            \
            30(C)
              \
              40(D)
                \
                50(E)
   ```

3. **Cây phức tạp** - Cấu trúc:
   ```
                                50(A)
                       /                     \
                 25(B)                         75(C)
              /        \                   /         \
         15(D)          35(E)         65(F)          85(G)
        /     \        /     \       /     \        /     \
   10(H)     20(I)  30(J)  40(K)  60(L)  70(M)   80(N)   90(O)
   ```

### Độ hoàn thiện theo yêu cầu

#### a) Hàm `search` và `searchRec`

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt đầy đủ hai hàm tìm kiếm sử dụng kỹ thuật lặp và đệ quy
- **Cài đặt**:
  - Hàm `search` sử dụng vòng lặp while để duyệt cây, so sánh khóa cần tìm với khóa tại mỗi nút và di chuyển xuống nút con phù hợp
  - Hàm `searchRec` sử dụng đệ quy, kiểm tra nút hiện tại và gọi đệ quy với nút con trái hoặc phải tùy thuộc vào giá trị khóa cần tìm
- **Độ phức tạp**: O(h) với h là chiều cao của cây
- **Test case**: 
  - Tìm các khóa có trong cây (khóa 50, 30, 70, 20, 40, 60, 80)
  - Tìm khóa không có trong cây (khóa 100)
  - Thử nghiệm trên cả 3 loại cây: cân bằng, lệch phải, phức tạp
- **Output mẫu**:
  ```
  === Kiem tra chuc nang tim kiem ===
  Tim khoa 50 bang phuong phap lap: Tim thay, data = A
  Tim khoa 50 bang de quy: Tim thay, data = A
  Tim khoa 30 bang phuong phap lap: Tim thay, data = B
  Tim khoa 30 bang de quy: Tim thay, data = B
  ...
  Tim khoa 100 bang phuong phap lap: Khong tim thay
  Tim khoa 100 bang de quy: Khong tim thay
  ```

**Bổ sung theo yêu cầu đề bài**: Cài đặt hàm tìm kiếm các node con trực tiếp của node gốc:

- **Hàm `searchChildren`**: Tìm node con trực tiếp của root có khóa k
- **Cài đặt**: Kiểm tra nút con trái và nút con phải của root, trả về nút nếu tìm thấy khóa k
- **Độ phức tạp**: O(1) - chỉ kiểm tra tối đa 2 nút con
- **Test case**: 
  - Tìm node con trái của root
  - Tìm node con phải của root
- **Output mẫu**:
  ```
  === Kiem tra chuc nang tim kiem cac node con truc tiep cua node root ===
  Tim node con trai (key=30): Tim thay, data = B
  Tim node con phai (key=70): Tim thay, data = C
  ```

#### b) Hàm `max` và `maxRec`

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt đầy đủ hai hàm tìm khóa lớn nhất sử dụng kỹ thuật lặp và đệ quy
- **Cài đặt**:
  - Hàm `max` dùng vòng lặp while để liên tục di chuyển sang nút con phải đến khi không thể di chuyển tiếp
  - Hàm `maxRec` dùng đệ quy để tìm nút có khóa lớn nhất (nút ngoài cùng bên phải)
- **Độ phức tạp**: O(h) với h là chiều cao của cây
- **Test case**:
  - Tìm khóa lớn nhất trong cây cân bằng (80 với data = G)
  - Tìm khóa lớn nhất trong cây lệch phải (50 với data = E)
  - Tìm khóa lớn nhất trong cây phức tạp (90 với data = O)
- **Output mẫu**:
  ```
  === Kiem tra chuc nang tim gia tri lon nhat ===
  Khoa lon nhat (lap): 80, data = G
  Khoa lon nhat (de quy): 80, data = G
  ```

#### c) Hàm `sort`

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt hàm xuất các khóa theo thứ tự tăng dần (sử dụng kỹ thuật duyệt cây inorder)
- **Cài đặt**: Sử dụng thuật toán duyệt cây theo thứ tự inorder (trái-gốc-phải)
- **Độ phức tạp**: O(n) với n là số nút trong cây
- **Test case**:
  - Sắp xếp cây cân bằng (20 30 40 50 60 70 80)
  - Sắp xếp cây lệch phải (10 20 30 40 50)
  - Sắp xếp cây phức tạp (10 15 20 25 30 35 40 50 60 65 70 75 80 85 90)
- **Output mẫu**:
  ```
  === Kiem tra chuc nang sap xep ===
  Cac khoa theo thu tu tang dan: 20 30 40 50 60 70 80
  ```

#### d) Hàm `balanced`

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt hàm kiểm tra cây có cân bằng trọng lượng hệ số α hay không
- **Cài đặt**: 
  - Tính số nút của cây con trái và cây con phải tại mỗi nút
  - Kiểm tra xem tỷ lệ giữa số nút của cây con lớn hơn và cây con nhỏ hơn có vượt quá α không
  - Áp dụng đệ quy kiểm tra mọi nút trong cây
- **Độ phức tạp**: O(n²) trong trường hợp xấu nhất (do đếm nút ở mỗi cấp)
- **Test case**:
  - Kiểm tra cây cân bằng với α = 1.0, 1.5, 2.0, 3.0, 4.1, 5.2
  - Kiểm tra cây lệch phải với α = 1.0, 1.5, 2.0, 3.0, 4.1, 5.2
  - Kiểm tra cây phức tạp với α = 1.0, 1.5, 2.0, 3.0, 4.1, 5.2
- **Output mẫu**:
  ```
  === Kiem tra chuc nang can bang ===
  Cay can bang voi he so alpha = 1.0
  Cay can bang voi he so alpha = 1.5
  Cay can bang voi he so alpha = 2.0
  Cay can bang voi he so alpha = 3.0
  Cay can bang voi he so alpha = 4.1
  Cay can bang voi he so alpha = 5.2
  ```
  ```
  === Kiem tra chuc nang can bang ===
  Cay khong can bang voi he so alpha = 1.0
  Cay khong can bang voi he so alpha = 1.5
  Cay khong can bang voi he so alpha = 2.0
  Cay khong can bang voi he so alpha = 3.0
  Cay can bang voi he so alpha = 4.1
  Cay can bang voi he so alpha = 5.2
  ```

### Các hàm phụ trợ bổ sung

- **createNode**: Tạo một nút mới với khóa và dữ liệu
- **insertNode**: Chèn một nút mới vào cây (đảm bảo không có khóa trùng)
- **countNodes**: Đếm số nút trong cây
- **displayInOrder**: Hiển thị các nút theo thứ tự inorder
- **freeTree**: Giải phóng bộ nhớ cây

### Kết quả đạt được

- Đã cài đặt đầy đủ các hàm theo yêu cầu đề bài
- Cải tiến tối ưu thuật toán với độ phức tạp phù hợp
- Xử lý các trường hợp đặc biệt như cây rỗng
- Kiểm thử thành công với ba loại cây khác nhau
- Bổ sung các hàm hỗ trợ để thuận tiện cho việc sử dụng và kiểm thử

![Ảnh demo terminal](./img/bai1.png)

---

## Bài tập 3: Xử lý biểu thức số học (Expression Evaluator)

### Mô tả cài đặt

Cài đặt hệ thống xử lý biểu thức số học với các phép toán: cộng (+), trừ (-), nhân (*), chia nguyên (/), chia dư (%), đối (-) và giai thừa (!). Hệ thống được thiết kế để:
1. Phân tích cú pháp biểu thức
2. Tính giá trị biểu thức
3. Chuyển đổi biểu thức giữa các dạng tiền tố, trung tố và hậu tố
4. Xử lý biến và lệnh gán

### Cấu trúc project

#### Các file chính:

- **ExpressionEvaluator.h**: Header file chính với khai báo lớp và hàm
- **TokenParser.cpp**: Phân tích cú pháp và tách token
- **ExpressionTree.cpp**: Xây dựng và đánh giá cây biểu thức
- **VariableProcessor.cpp**: Xử lý biến và đánh giá biểu thức
- **TestCases.cpp/h**: Bộ kiểm thử
- **ExpressionEvaluator.cpp**: File chương trình chính

#### Các lớp và cấu trúc dữ liệu chính:

- **Token**: Biểu diễn một token trong biểu thức, với các loại:
  ```cpp
  enum TokenType { NUMBER, VARIABLE, OPERATOR, LEFT_PAREN, RIGHT_PAREN, ASSIGNMENT, SEMICOLON };
  
  struct Token {
      TokenType type;
      std::string value;
  };
  ```
  
- **ExpressionNode**: Lớp cơ sở cho các nút trong cây biểu thức
  ```cpp
  enum NodeType { VALUE_NODE, VARIABLE_NODE, OPERATOR_NODE };
  
  class ExpressionNode {
  public:
      NodeType type;
      ExpressionNode(NodeType t) : type(t) {}
      virtual int evaluate(std::map<char, int>& variables) = 0;
      virtual std::string toString() = 0;
      virtual ~ExpressionNode() {}
  };
  ```

- **ValueNode**: Nút biểu diễn giá trị số
- **VariableNode**: Nút biểu diễn biến
- **OperatorNode**: Nút biểu diễn toán tử

### Các chức năng chính theo yêu cầu đề bài

#### a) Cho nhập và phân tích biểu thức

- **Mức độ hoàn thiện**: 100%
- **Cài đặt**:
  - Hàm `tokenize`: Phân tích biểu thức thành các token (số, biến, toán tử, dấu ngoặc)
  - Hàm `validateSyntax`: Kiểm tra cú pháp hợp lệ của biểu thức
  - Xử lý khoảng trắng, dấu ngoặc, toán tử đơn ngôi (đối dấu, giai thừa)
- **Test case**: 
  ```
  3 + 5
  10 - 4
  4 * 7
  20 / 4
  17 % 5
  -7
  -(3 + 4)
  5!
  (3 + 2)!
  ```
- **Output mẫu**:
  ```
  Bieu thuc dang tien to: + 3 5
  Bieu thuc dang trung to: (3 + 5)
  Bieu thuc dang hau to: 3 5 +
  Ket qua: 8
  ```

#### b) Tính giá trị của biểu thức

- **Mức độ hoàn thiện**: 100%
- **Cài đặt**:
  - Hàm `buildExpressionTree`: Xây dựng cây biểu thức từ các token dạng hậu tố
  - Hàm `evaluate`: Đánh giá giá trị của cây biểu thức
  - Xử lý đúng độ ưu tiên các toán tử, dấu ngoặc và toán tử đơn ngôi
- **Test case**:
  - Các phép toán cơ bản (cộng, trừ, nhân, chia, chia dư)
  - Toán tử đơn ngôi (đối dấu, giai thừa)
  - Biểu thức phức tạp với nhiều toán tử và dấu ngoặc lồng nhau
- **Output mẫu**:
  ```
  Bieu thuc dang tien to: + - 10 * 3 2 5
  Bieu thuc dang trung to: ((10 - (3 * 2)) + 5)
  Bieu thuc dang hau to: 10 3 2 * - 5 +
  Ket qua: 9
  ```

#### c) Xuất biểu thức dạng tiền tố, hậu tố và trung tố

- **Mức độ hoàn thiện**: 100%
- **Cài đặt**:
  - Hàm `toPrefix`: Chuyển cây biểu thức sang dạng tiền tố
  - Hàm `toInfix`: Chuyển cây biểu thức sang dạng trung tố
  - Hàm `toPostfix`: Chuyển cây biểu thức sang dạng hậu tố
  - Hàm `infixToPostfix`: Chuyển dãy token trung tố sang hậu tố (thuật toán Shunting Yard)
- **Test case**:
  ```
  3 + 4 * 2
  (a + b) * 5
  1 - (2 - 3) * (4 + 5)!
  ```
- **Output mẫu**:
  ```
  Bieu thuc dang tien to: + 3 * 4 2
  Bieu thuc dang trung to: (3 + (4 * 2))
  Bieu thuc dang hau to: 3 4 2 * +
  Ket qua: 11
  ```

#### Phần mở rộng: Xử lý biểu thức có biến và lệnh gán

- **Mức độ hoàn thiện**: 100%
- **Cài đặt**:
  - Hàm `processCommand`: Xử lý lệnh dạng `<var-1> = <exp-1> ; … ; <var-n> = <exp-n> ; <exp>`
  - Sử dụng map để lưu trữ biến và giá trị
  - Xử lý biến trong biểu thức thông qua `VariableNode`
  - Hỗ trợ chuỗi nhiều lệnh phân cách bởi dấu chấm phẩy
- **Test case**:
  ```
  a = 5
  a = 5; a + 3
  a = 1; b = 10 * a; a + 20 * b
  a = b = 5; a * b
  ```
- **Output mẫu**:
  ```
  Gan bien don gian:
  a = 5
  Ket qua: 5

  Su dung bien da gan:
  a = 5; a + 3
  Ket qua: 8

  Nhieu bien va phep toan:
  a = 1; b = 10 * a; a + 20 * b
  Ket qua: 201

  Phep gan long nhau:
  a = b = 5; a * b
  Ket qua: 25
  ```

### Xử lý ngoại lệ

Dưới đây là bảng tóm tắt các ngoại lệ được xử lý:

| STT | Ngoại lệ | Test case | Output |
|-----|----------|-----------|--------|
| 1 | Chia cho 0 | `5 / 0` | `Loi: chia cho 0` |
| 2 | Dấu ngoặc không khớp | `(3 + 4 * (2 - 1` | `Loi: Dau ngoac khong khop` |
| 3 | Toán tử không hợp lệ | `3 @ 5` | `Loi: Ky tu khong hop le: @` |
| 4 | Giai thừa của số âm | `(-3)!` | `Loi: Khong the tinh giai thua cua     so am` |
| 5 | Thiếu toán hạng | `3 + * 5` | `Loi: Bieu thuc khong hop le: thieu toan hang cho toan tu nhi phan` |
| 6 | Thiếu toán tử | `3 5` | `Loi: Bieu thuc khong hop le` |
| 7 | Biến chưa định nghĩa | `a + 5` | `Loi: Bien chua duoc gan gia tri: a` |
| 8 | Hai toán tử liên tiếp | `2 ++ 3` | `Loi: Bieu thuc khong hop le` |
| 9 | Hai toán hạng liên tiếp | `2 3` | `Loi: Bieu thuc khong hop le` |
| 10 | Toán tử ! đặt không đúng | `!5` | `Loi: Bieu thuc khong hop le` |

### Bộ kiểm thử toàn diện

Bộ kiểm thử được triển khai đầy đủ, bao gồm:

1. **Kiểm thử các phép toán cơ bản**
   - Phép cộng và trừ
   - Phép nhân và chia
   - Phép chia lấy dư
   - Phép đối dấu
   - Phép giai thừa

2. **Kiểm thử biểu thức phức tạp**
   - Nhiều phép toán và độ ưu tiên
   - Dấu ngoặc lồng nhau
   - Kết hợp nhiều phép toán

3. **Kiểm thử chuyển đổi ký pháp**
   - Chuyển đổi giữa các dạng tiền tố, trung tố, hậu tố

4. **Kiểm thử gán biến**
   - Gán biến đơn giản
   - Sử dụng biến đã gán
   - Nhiều biến và phép toán
   - Phép gán lồng nhau

5. **Kiểm thử xử lý ngoại lệ**
   - Các lỗi cú pháp và ngữ nghĩa

6. **Kiểm thử lệnh đầy đủ**
   - Ví dụ từ đề bài: `a = 1; b = 10 * a; a + 20 * b` (kết quả 201)
   - Ví dụ với nhiều biến: `a = 5; b = a * 2; c = b - a; c * 3` (kết quả 15)
   - Ví dụ với giai thừa: `a = 3!; b = 2 * a; a + b` (kết quả 18)
   - Ví dụ với biểu thức ngoặc: `a = 2; b = 3; c = (a + b) * 2; c - a` (kết quả 8)
   - Ví dụ gán lại biến: `a = 10; a = a + 5; a * 2` (kết quả 30)
   - Ví dụ giai thừa phức tạp: `a = 2; b = 3; c = (a + b)!; c % 10` (kết quả 0)
   - Ví dụ phép toán kết hợp: `x = 5; y = 3; z = x * y + (x - y); z / 2` (kết quả 8)
   - Ví dụ chuỗi gán liên tiếp: `a = 1; a = a + 1; a = a * 2; a = a - 1; a` (kết quả 3)
   - Ví dụ nhiều phép toán: `a = 10; b = 3; c = a % b; d = a / b; c + d * 2` (kết quả 7)
   - Ví dụ biểu thức lồng nhau: `a = 2 * (3 + 1); b = a / 2; c = b!; c - a` (kết quả 16)
   - Ví dụ giá trị âm: `a = -5; b = -a; c = a * b; -c` (kết quả 25)
   - Ví dụ biểu thức phức tạp: `a = 10; b = 20; c = 5; (a + b) * c - b / c` (kết quả 146)
   - Ví dụ tất cả phép toán: `a = 4; b = 3; c = 2; a * b / c + a - b % c` (kết quả 9)

### Chức năng xử lý biểu thức và lệnh

Phần xử lý lệnh (`processCommand`) có các đặc điểm:

1. **Xử lý đúng cú pháp lệnh**: Hỗ trợ chuỗi lệnh có dạng `<var-1> = <exp-1> ; … ; <var-n> = <exp-n> ; <exp>` theo đúng yêu cầu
2. **Lưu trữ biến**: Sử dụng `map` để lưu trữ giá trị biến
3. **Tính giá trị biểu thức**: Đánh giá biểu thức cuối cùng hoặc giá trị sau mỗi lệnh gán
4. **Xử lý biến trong biểu thức**: Đảm bảo tất cả biến đều có giá trị trước khi sử dụng
5. **Chuỗi nhiều câu lệnh**: Hỗ trợ thực thi nhiều câu lệnh gán liên tiếp và tính toán biểu thức cuối cùng
6. **Kiểm tra lỗi**: Phát hiện lỗi cú pháp, ngữ nghĩa trong chuỗi lệnh

Các test case đầy đủ đã được cài đặt và kiểm thử, thể hiện khả năng xử lý lệnh phức tạp bao gồm nhiều phép gán, sử dụng lại biến đã định nghĩa, và tính toán biểu thức cuối cùng chính xác.

### Kết quả đạt được

- Đã cài đặt đầy đủ tất cả các chức năng yêu cầu trong đề bài
- Xử lý thành công các biểu thức phức tạp với nhiều loại toán tử
- Chuyển đổi chính xác giữa các dạng biểu thức (tiền tố, trung tố, hậu tố)
- Xử lý biến và lệnh gán đúng theo yêu cầu của đề bài
- Phát hiện và xử lý các ngoại lệ cú pháp và ngữ nghĩa
- Xử lý đúng các phép toán đơn ngôi và độ ưu tiên toán tử
- Triển khai bộ kiểm thử toàn diện để đảm bảo tính đúng đắn

![Ảnh demo terminal](./img/bai3.png)

Cả hai bài tập đều được thực hiện đầy đủ theo yêu cầu với cách tiếp cận tổng quát và xử lý chi tiết các trường hợp ngoại lệ. Các cấu trúc dữ liệu và thuật toán được tối ưu hóa, mã nguồn được tổ chức thành các module rõ ràng, dễ bảo trì và test case đầy đủ. 
Với bài tập 3, tất cả ngoại lệ đều được xử lý kỹ lưỡng, có test case kiểm thử và báo lỗi rõ ràng giúp người dùng dễ dàng hiểu và khắc phục lỗi.

---

**Ghi chú**: Các mã nguồn được viết bằng C++ và tương thích tốt với visual studio 2022.