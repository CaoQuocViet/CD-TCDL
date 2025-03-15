1. (2 đ). Số tổ hợp.
Số cách chọn ra một tập con gồm 𝑘 phần tử từ tập có 𝑛 phần tử được gọi là số tổ hợp chọn 𝑘 từ 𝑛 (0 ≤ 𝑘 ≤ 𝑛), kí hiệu 𝐶𝑛𝑘. Người ta chứng minh được

𝐶𝑛𝑘 = 𝑛! / (𝑘!(𝑛 − 𝑘)!)

trong đó 𝑛! = 1 × 2 ×…×𝑛 là giai thừa của 𝑛.

a) Viết hàm tính 𝐶𝑛𝑘 bằng công thức trên.

b) Nhận xét rằng 𝑛! lớn rất nhanh khi 𝑛 tăng, chẳng hạn 20! = 243290200817664000, nên công thức trên không dùng được khi 𝑛 không nhỏ. Tìm cách viết hàm tính 𝐶𝑛𝑘 mà không dùng giai thừa.

c) Nhận xét rằng tích các số nguyên có giá trị lớn so với các thừa số, chẳng hạn 106 × 106 = 1012. Tìm cách viết hàm tính 𝐶𝑛𝑘 mà không dùng phép nhân/chia. Gợi ý: tam giác Pascal. So sánh các giải pháp ở trên.


3. 5.1 Viết hàm double round(double x, int pos) để tìm giá trị làm tròn của số thực x đến chữ số ở hàng pos sau dấu chấm thập phân với qui ước hàng đơn vị có pos là 0, hàng ngay sau dấu chấm (hàng phần 10) có pos là 1, … Ví dụ: round(25.649, 0) sẽ trả về 26.0, round(25.649, 1) sẽ trả về 25.6, round(25.649, 2) sẽ trả về 25.65, … Bạn có làm được cho trường hợp pos < 0 không? Ví dụ: round(25.649, -1) sẽ trả về 30.0, round(25.649, -2) sẽ trả về 0.0, …


4. 1.6 Hãy xem lại phần Mở rộng 4.1. Cho một mẫu dữ liệu, ta gọi trung vị (median) của mẫu là giá trị “ở giữa” hay giá trị “chia đôi dữ liệu” của mẫu. Tương tự giá trị trung bình, trung vị là một con số phản ánh trung tâm của số liệu. Hãy tham khảo tài liệu để hiểu rõ khái niệm trung vị và viết hàm tính giá trị này của một mẫu dữ liệu (prototype tương tự hàm mean hay var của Mã 4.1.4).

MỞ RỘNG 4.1 – Trung bình và phương sai của một mẫu dữ liệu số
Một mẫu dữ liệu (số) cỡ n là một danh sách gồm n số thực x1, x2, …, xn. Ta gọi giá trị 𝑥= ∑ 𝑥𝑖 (i=1 đến n) là trung bình của mẫu, giá trị 𝑆2 = ∑ (𝑥𝑖 − 𝑥)² / n là phương sai của mẫu và 𝑆 = √𝑆2 là độ lệch chuẩn của mẫu. Các giá trị này cho ta một hình dung đơn giản về mẫu dữ liệu. Giá trị trung bình cho biết giá trị trung tâm (hay trọng tâm) mà các số liệu của mẫu xoay quanh đó còn độ lệch chuẩn (hay phương sai) cho thấy mức độ phân tán (hay xa cách) của các số liệu so với giá trị trung tâm. Độ lệch chuẩn (hay phương sai) càng nhỏ cho thấy các số liệu của mẫu càng bu gần giá trị trung tâm, cũng có nghĩa là chúng bu gần nhau. Ngược lại, độ lệch chuẩn lớn cho thấy một hình ảnh tản mác, xa cách nhau của các số liệu. Đây hiển nhiên là các giá trị quan trọng trong Thống kê. Tuy nhiên ở đây ta đơn giản sẽ là tìm cách tính chúng. 

Như đã nói cách xử lý offline thường dễ dàng: ta dùng mảng số thực (kiểu double) để chứa (toàn bộ) các số liệu của mẫu (kèm với một biến nguyên n cho biết chiều dài mảng và cũng là cỡ mẫu) rồi mới tính trung bình và phương sai của mẫu, chẳng hạn, bằng 2 hàm sau.

Mã 4.1.4 – Các hàm tính trung bình và phương sai mẫu:

double mean(double x[], int n) 
{ 
    double S = 0; 
    for(int i = 0; i < n; i++) 
        S = S + x[i]; 
    return S/n; 
}

double var(double x[], int n) 
{ 
    double m = mean(x, n); 
    double S = 0; 
    for(int i = 0; i < n; i++) 
        S = S + (x[i] - m)*(x[i] - m); 
    return S/n; 
}

Hàm mean tính trung bình của mẫu số liệu để trong mảng số thực x với tham số n cho biết cỡ mẫu. Hàm này cài đặt nguyên si công thức tính giá trị trung bình ở trên. Cũng lưu ý là ta thường kí hiệu các số liệu mẫu là x1, x2, …, xn nhưng vì chỉ số mảng trong C bắt đầu từ 0 nên chúng sẽ là x[0], x[1], …, x[n-1]. Tương tự, hàm var tính phương sai của mẫu theo công thức đã cho. Lưu ý là ta phải tính giá trị trung bình trước và chỉ cần tính một lần như Dòng 12 cho thấy. Bạn hãy ráp vào chương trình, cho nhập mẫu số liệu vào mảng rồi dùng các hàm trên để tính trung bình và phương sai của mẫu số liệu đã nhập. Để tính độ lệch chuẩn, ta tính căn của phương sai.


4. 2.8 Một phần tử của mảng hai chiều các số được gọi là “điểm yên ngựa” nếu phần tử đó là nhỏ nhất trong dòng và lớn nhất trong cột. Tìm tất cả các điểm yên ngựa của một mảng. 
Mảng là công cụ vô giá của C!

