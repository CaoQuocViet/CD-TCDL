# Báo Cáo Bài Tập 1 và 3 - Chuyên Đề Tổ Chức Dữ Liệu

## Giới thiệu

Báo cáo này mô tả việc thực hiện hai bài tập:
1. Xây dựng cấu trúc dữ liệu Cây Tìm Kiếm Nhị Phân (Binary Search Tree)
2. Xử lý biểu thức số học (Expression Evaluator)

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

### Độ hoàn thiện theo yêu cầu

#### a) Hàm `search` và `searchRec`

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt đầy đủ hai hàm tìm kiếm sử dụng kỹ thuật lặp và đệ quy
- **Cải tiến**: Xử lý trường hợp cây rỗng, tối ưu hóa thuật toán

#### b) Hàm `max` và `maxRec`

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt đầy đủ hai hàm tìm khóa lớn nhất sử dụng kỹ thuật lặp và đệ quy
- **Cải tiến**: Xử lý trường hợp cây rỗng, tối ưu hóa thuật toán

#### c) Hàm `sort`

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt hàm xuất các khóa theo thứ tự tăng dần (sử dụng kỹ thuật duyệt cây inorder)
- **Cải tiến**: Xử lý trường hợp cây rỗng

#### d) Hàm `balanced`

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt hàm kiểm tra cây có cân bằng trọng lượng hệ số α hay không
- **Cải tiến**: 
  - Xử lý đúng định nghĩa khi nút là NULL cũng tính là 1 nút
  - Kiểm tra đệ quy tất cả các nút trong cây

### Các hàm phụ trợ bổ sung

- **createNode**: Tạo một nút mới với khóa và dữ liệu
- **insertNode**: Chèn một nút mới vào cây (đảm bảo không có khóa trùng)
- **countNodes**: Đếm số nút trong cây
- **displayInOrder**: Hiển thị các nút theo thứ tự inorder
- **freeTree**: Giải phóng bộ nhớ cây

### Bộ kiểm thử

Bộ kiểm thử được triển khai với ba loại cây:
1. Cây cân bằng (mẫu)
2. Cây lệch phải
3. Cây rỗng (NULL)

Mỗi hàm chính được kiểm thử riêng biệt và tất cả chức năng đều hoạt động đúng như yêu cầu.

---

## Bài tập 3: Xử lý biểu thức số học (Expression Evaluator)

### Mô tả cài đặt

Cài đặt hệ thống xử lý biểu thức số học với các phép toán: cộng (+), trừ (-), nhân (*), chia nguyên (/), chia dư (%), đối (-) và giai thừa (!).

### Cấu trúc project

#### Các file chính:

- **ExpressionEvaluator.h**: Header file chính với khai báo lớp và hàm
- **TokenParser.cpp**: Phân tích cú pháp và tách token
- **ExpressionTree.cpp**: Xây dựng và đánh giá cây biểu thức
- **VariableProcessor.cpp**: Xử lý biến và đánh giá biểu thức
- **TestCases.cpp/h**: Bộ kiểm thử
- **ExpressionEvaluator.cpp**: File chương trình chính

#### Các lớp chính:

- **Token**: Biểu diễn một token trong biểu thức
- **ExpressionNode**: Lớp cơ sở cho các nút trong cây biểu thức
- **ValueNode**: Nút biểu diễn giá trị số
- **VariableNode**: Nút biểu diễn biến
- **OperatorNode**: Nút biểu diễn toán tử

### Độ hoàn thiện theo yêu cầu

#### a) Cho nhập và phân tích biểu thức

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt đầy đủ khả năng phân tích biểu thức thành token và xây dựng cây biểu thức
- **Xử lý ngoại lệ**: Đã xử lý tất cả ngoại lệ liên quan đến cú pháp

#### b) Tính giá trị của biểu thức

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt đầy đủ khả năng đánh giá biểu thức dựa trên cây biểu thức
- **Xử lý ngoại lệ**: Đã xử lý tất cả ngoại lệ liên quan đến ngữ nghĩa và tính toán

#### c) Xuất biểu thức dạng tiền tố, hậu tố và trung tố

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt đầy đủ các hàm `toPrefix`, `toPostfix`, và `toInfix` để chuyển đổi biểu thức
- **Xử lý đặc biệt**:
  - Xử lý đúng độ ưu tiên toán tử khi chuyển đổi
  - Xử lý đúng toán tử đơn ngôi (đối dấu, giai thừa)
  - Thêm ngoặc khi cần thiết để duy trì ngữ nghĩa biểu thức

#### Phần mở rộng: Xử lý biểu thức có biến và lệnh gán

- **Mức độ hoàn thiện**: 100%
- **Mô tả**: Cài đặt đầy đủ khả năng xử lý biến và lệnh dạng `<var-1> = <exp-1> ; … ; <var-n> = <exp-n> ; <exp>`
- **Xử lý ngoại lệ**: Đã xử lý tất cả ngoại lệ liên quan đến biến và lệnh gán

### Xử lý các ngoại lệ

Dưới đây là chi tiết việc xử lý 20 ngoại lệ được liệt kê:

| STT | Ngoại lệ | Mô tả | Cách xử lý | Test case |
|-----|----------|-------|------------|-----------|
| 1 | Ngoặc không khớp | Thiếu ngoặc đóng/mở hoặc không khớp | Đếm số ngoặc khi tokenize, kiểm tra cặp ngoặc | `(3 + 4 * (2 - 1`, `(2 + 3`, `((1+2)*3))` |
| 2 | Biểu thức rỗng/chỉ khoảng trắng | Biểu thức không có giá trị | Kiểm tra khi tokenize | `""`, `" "` |
| 3 | Hai toán tử liên tiếp | Xuất hiện hai toán tử mà không có toán hạng ở giữa | Kiểm tra quy tắc cú pháp trong validateSyntax | `2 ++ 3`, `4 ** 5`, `3 // 2` |
| 4 | Hai toán hạng liên tiếp không có toán tử | Thiếu toán tử giữa các toán hạng | Kiểm tra token liên tiếp trong validateSyntax | `2 3`, `x y` |
| 5 | Dấu ! đứng sai vị trí | Toán tử giai thừa đặt không đúng vị trí | Kiểm tra trong validateSyntax | `!5`, `!(4+1)`, `5!!`, `a!` |
| 6 | Biến chưa gán giá trị | Sử dụng biến chưa được định nghĩa | Kiểm tra trong VariableNode::evaluate | `a + 5` (khi a chưa gán) |
| 7 | Biến có tên không hợp lệ | Tên biến không tuân theo quy tắc | Chỉ cho phép biến là 1 chữ cái | `12a + 3`, `@b + 1`, `_x + 1` |
| 8 | Chia cho 0 hoặc chia dư cho 0 | Phép chia với mẫu số là 0 | Kiểm tra trước khi thực hiện phép chia | `5 / 0`, `10 % 0` |
| 9 | Thiếu toán hạng | Toán tử thiếu toán hạng cần thiết | Kiểm tra trong validateSyntax | `+ 3`, `4 -`, `*5` |
| 10 | Toán tử ở vị trí sai trong biểu thức | Toán tử đặt không đúng vị trí | Kiểm tra trong validateSyntax | `2 + * 3`, `2 + ( * 4 )` |
| 11 | Toán tử - bị lặp hoặc hiểu sai | Sử dụng dấu trừ liên tiếp | Xử lý đặc biệt unary minus | `--2`, `- - 3`, `-( - 2 )` |
| 12 | Lỗi xử lý ! với biểu thức phức tạp | Áp dụng giai thừa cho biểu thức | Xử lý đúng trong đánh giá biểu thức | `(3+2)!`, `((2+3)*4)!` |
| 13 | Thiếu dấu ; giữa các lệnh trong chuỗi gán | Thiếu dấu phân cách giữa các lệnh | Kiểm tra cú pháp khi phân tích lệnh | `a = 1 b = 2; a + b` |
| 14 | Gán sai cú pháp | Cú pháp gán không chính xác | Kiểm tra trong validateSyntax | `= 10 + 2;`, `x = ;`, `x =` |
| 15 | Dùng toán tử không hợp lệ | Sử dụng toán tử không được hỗ trợ | Kiểm tra khi tokenize | `2 $ 3`, `4 ^ 2` |
| 16 | Tên biến trùng từ khóa | Sử dụng từ khóa làm tên biến | Không áp dụng (không có từ khóa) | - |
| 17 | Lạm dụng khoảng trắng | Khoảng trắng gây hiểu sai | Bỏ qua khoảng trắng khi tokenize | `- 2`, `- ( 3 + 4 )` |
| 18 | Ngoặc đơn bao trùm không cần thiết | Sử dụng quá nhiều dấu ngoặc | Hỗ trợ xử lý | `(((((3)))))` |
| 19 | Toán tử ! áp dụng cho biến | Tính giai thừa của biến | Kiểm tra kiểu và giá trị trước khi tính | `a!` |
| 20 | Biểu thức kết thúc bằng toán tử | Biểu thức không hoàn chỉnh | Kiểm tra trong validateSyntax | `2 + 3 *`, `a +` |

### Bộ kiểm thử toàn diện

Bộ kiểm thử đã được cài đặt đầy đủ, bao gồm:

1. **Kiểm thử các phép toán cơ bản**
   - Phép cộng và trừ: `3 + 5`, `10 - 4`, `3 + 5 - 2`
   - Phép nhân và chia: `4 * 7`, `20 / 4`, `5 * 3 / 2`
   - Phép chia lấy dư: `17 % 5`
   - Phép đối dấu: `-7`, `-(3 + 4)`
   - Phép giai thừa: `5!`, `(3 + 2)!`

2. **Kiểm thử biểu thức phức tạp**
   - Nhiều phép toán và độ ưu tiên: `3 + 4 * 2`, `(3 + 4) * 2`, `10 - 3 * 2 + 5`
   - Dấu ngoặc lồng nhau: `((2 + 3) * (4 - 1))`
   - Kết hợp nhiều phép toán: `1 - (2 - 3) * (4 + 5)!`, `20 / 4 + 3 * 2!`, `-3 * 4 + 7 * 2`

3. **Kiểm thử chuyển đổi ký pháp**
   - Chuyển đổi infix, prefix, postfix: `3 + 4 * 2`, `(a + b) * 5`, `1 - (2 - 3) * (4 + 5)!`

4. **Kiểm thử gán biến**
   - Gán biến đơn giản: `a = 5`
   - Sử dụng biến đã gán: `a = 5; a + 3`
   - Nhiều biến và phép toán: `a = 1; b = 10 * a; a + 20 * b`
   - Phép gán lồng nhau: `a = b = 5; a * b`

5. **Kiểm thử xử lý ngoại lệ**
   - Chia cho 0: `5 / 0`
   - Dấu ngoặc không khớp: `(3 + 4 * (2 - 1`
   - Toán tử không hợp lệ: `3 @ 5`
   - Giai thừa của số âm: `(-3)!` 
   - Thiếu toán hạng: `3 + * 5`
   - Thiếu toán tử: `3 5`
   - Biến chưa định nghĩa: `a + 5`
   - Ngoặc lồng nhau thừa: `(((((3)))))`
   - Toán tử đặt sai vị trí: `2 + * 3`
   - Toán tử - bị lặp: `--2`, `- - 3`
   - Gán sai cú pháp: `= 10 + 2;`, `x = ;`
   - Thiếu dấu ; giữa các lệnh: `a = 1 b = 2; a + b`
   - Áp dụng giai thừa cho biến: `a!`
   - Biểu thức kết thúc bằng toán tử: `2 + 3 *`, `a +`

6. **Kiểm thử lệnh đầy đủ**
   - Ví dụ 1: `a = 1; b = 10 * a; a + 20 * b` (kết quả 201)
   - Ví dụ 2: `a = 5; b = a * 2; c = b - a; c * 3` (kết quả 15)
   - Ví dụ 3: `a = 3!; b = 2 * a; a + b` (kết quả 12)

## Kết luận

Cả hai bài tập đều được thực hiện đầy đủ theo yêu cầu với cách tiếp cận tổng quát và xử lý chi tiết các trường hợp ngoại lệ. Các cấu trúc dữ liệu và thuật toán được tối ưu hóa, mã nguồn được tổ chức thành các module rõ ràng, dễ bảo trì và test case đầy đủ.

Đặc biệt với bài tập 3, tất cả 20 ngoại lệ đều được xử lý kỹ lưỡng, có test case kiểm thử và báo lỗi rõ ràng giúp người dùng dễ dàng hiểu và khắc phục lỗi.

---

**Ghi chú**: Các mã nguồn được viết bằng C++ và có thể được biên dịch bằng bất kỳ trình biên dịch C++ hiện đại nào hỗ trợ C++11 hoặc cao hơn. 