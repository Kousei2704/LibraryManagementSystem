 

MỤC LỤC

I.	Giới thiệu dự án
II.	Tổng quan dự án
III. Chi tiết các Class và chức năng
IV.	Các thuật toán quan trọng
V.	Hướng dẫn sử dụng
VI.	Kết luận
VII. Tài liệu tham khảo



I. Giới thiệu dự án
Quản lý thư viện là một bài toán điển hình trong lập trình ứng dụng, yêu cầu sự kết hợp nhuần nhuyễn giữa việc tổ chức dữ liệu và logic nghiệp vụ. Với mục tiêu xây dựng một phần mềm có tính ứng dụng cao và giao diện thân thiện, em/nhóm em đã chọn đề tài "Hệ thống quản lý thư viện" cho bài tập lớn môn Ngôn ngữ lập trình.
Sử dụng ngôn ngữ C++ – một ngôn ngữ mạnh mẽ về hiệu năng và hỗ trợ tốt mô hình lập trình hướng đối tượng (OOP) – chương trình được thiết kế để giải quyết các vấn đề thực tế như: quản lý kho sách, theo dõi lịch sử mượn trả và tìm kiếm thông tin nhanh chóng. Báo cáo này ghi lại quá trình thực hiện dự án, các kiến thức C++ nâng cao đã áp dụng cũng như những bài học kinh nghiệm rút ra trong quá trình phát triển phần mềm.


II. Tổng quan dự án 
 
"Hệ thống Quản lý Thư viện" (Library Management System)

Dự án này được xây dựng theo hướng lập trình hướng đối tượng (OOP), sử dụng File I/O để lưu trữ dữ liệu và thao tác trên giao diện dòng lệnh (Console).
Chương trình là một hệ thống quản lý thư viện hoàn chỉnh cho phép hai vai trò tương tác:
•	Admin (Quản trị viên): Quản lý kho sách (thêm, sửa, xóa, tìm kiếm).
•	User (Người dùng/Độc giả): Đăng ký, đăng nhập, tìm sách, mượn và trả sách.
Dữ liệu của sách và người dùng được lưu trữ bền vững trong các file .txt, đảm bảo thông tin không bị mất khi tắt chương trình.

III. Các Class và chức năng

A. Class Book (Đối tượng Sách)
•	Vai trò: Đại diện cho một cuốn sách cụ thể.
•	Thuộc tính:
o	id, title, author: Thông tin định danh sách.
o	quantity: Số lượng sách hiện có trong kho.
•	Chức năng chính:
o	Lưu trữ và cung cấp thông tin sách (Getter/Setter).
o	checkAvailable(): Kiểm tra xem sách còn trong kho để mượn không.
o	updateQuantity(): Tăng/giảm số lượng sách khi có người mượn hoặc trả.
B. Class Library (Quản lý Thư viện - Đóng vai trò Admin)
•	Vai trò: Quản lý danh sách tất cả các cuốn sách (vector<Book> bookList).
•	Chức năng chính:
o	Quản lý sách: Thêm sách mới (addBook), xóa sách (removeBook).
o	Tìm kiếm: Tìm sách linh hoạt theo Tên, ID, hoặc Tác giả (sử dụng hàm checkForSubstr để tìm kiếm gần đúng).
o	Hiển thị: In ra danh sách toàn bộ sách, có sắp xếp theo tên (displayAllBooks).
o	File I/O: Đọc/Ghi dữ liệu kho sách vào file library.txt.
o	Quản lý User: Có chức năng xóa người dùng khỏi hệ thống.
C. Class User (Người dùng)
•	Vai trò: Thực hiện các hành động mượn/trả và lưu trữ lịch sử mượn sách của riêng người đó.
•	Thuộc tính:
o	name, user_id: Định danh người dùng.
o	borrowed_books: Một danh sách (vector) chứa các cuốn sách mà người này đang mượn.
•	Chức năng chính:
o	borrowBook(): Xử lý logic mượn (Kiểm tra xem đã mượn cuốn đó chưa, kho còn sách không). Nếu thành công, giảm số lượng trong kho và thêm vào danh sách đã mượn.
o	returnBook(): Xử lý logic trả, xóa sách khỏi danh sách đã mượn.
o	Lưu trữ riêng biệt: Mỗi User có một file riêng (ví dụ: User_123.txt) để lưu danh sách sách họ đang mượn.
________________________________________

Các hàm hỗ trợ và Luồng dữ liệu (Main Flow)
Ngoài 3 class trên, code còn có các hàm xử lý logic bên ngoài:
•	Hệ thống File:
o	library.txt: Lưu toàn bộ đầu sách.
o	users.txt: Lưu danh sách tài khoản người dùng (ID | Tên).
o	User_[ID].txt: Lưu sách đang mượn của từng user cụ thể.
•	Hàm tiện ích:
o	checkForSubstr: Giúp tìm kiếm từ khóa (ví dụ tìm "Harry" sẽ ra "Harry Potter").
o	compareBooksByTitle: Giúp sắp xếp sách theo bảng chữ cái.
•	Hàm Main: Điều hướng chương trình theo 3 nhánh:
1.	Menu Admin: Gọi các chức năng của class Library.
2.	Menu User: Đăng nhập, load dữ liệu cá nhân, sau đó gọi các chức năng của class User.
3.	Đăng ký: Tạo user mới và lưu vào users.txt.


IV. Các thuật toán quan trọng

1. Thuật toán Tìm kiếm Tuyến tính (Linear Search)
•	Cơ chế: Duyệt qua từng phần tử trong danh sách (vector) từ đầu đến cuối để tìm phần tử thỏa mãn điều kiện.
•	Vị trí trong code:
o	Library::searchBookByTitle/Author/ID: Duyệt qua bookList để tìm sách.
o	User::borrowBook: Duyệt qua borrowed_books để kiểm tra xem user đã mượn sách này chưa.
o	loginUser: Duyệt qua danh sách users để tìm tài khoản khớp ID.
o	Library::removeBook: Tìm vị trí sách cần xóa.
•	Độ phức tạp: $O(N)$ (với N là số lượng sách hoặc người dùng). Nếu dữ liệu lớn, nó sẽ chậm, nhưng với bài tập lớn này thì hoàn toàn chấp nhận được.

2. Thuật toán Sắp xếp (Sorting)
•	Cơ chế: Sử dụng hàm có sẵn std::sort của thư viện <algorithm>, kết hợp với hàm so sánh tùy biến compareBooksByTitle.
•	Vị trí trong code:
o	Hàm Library::displayAllBooks: sort(sortedList.begin(), sortedList.end(), compareBooksByTitle);
•	Chi tiết: std::sort trong C++ thường được cài đặt bằng thuật toán IntroSort (kết hợp giữa QuickSort, HeapSort và InsertionSort).
•	Độ phức tạp: $O(N \log N)$ (nhanh hơn nhiều so với Bubble Sort hay Selection Sort).




3. Thuật toán Xử lý chuỗi & Khớp mẫu (String Matching & Parsing)
•	Cơ chế Tìm kiếm chuỗi con (Substring Search):
o	Trong hàm checkForSubstr: Sử dụng a.find(b) để kiểm tra xem từ khóa tìm kiếm có nằm trong tên sách không (ví dụ: gõ "Harry" vẫn tìm ra "Harry Potter").
•	Cơ chế Phân tích cú pháp (Parsing Algorithm):
o	Trong các hàm loadFromFile: Bạn dùng thuật toán "trượt" để tìm vị trí các ký tự phân cách |.
o	Logic: Tìm vị trí | thứ nhất -> cắt chuỗi -> tìm | thứ 2 từ vị trí cũ -> cắt chuỗi...
o	Điều này giúp chuyển đổi một dòng văn bản thô (ví dụ: B01|Lap trinh C|Admin|10) thành các thuộc tính của Object.

4. Thuật toán Quản lý Mảng động (Vector Operations)
•	Thao tác Xóa (Erase - Shift):
o	Khi bạn gọi bookList.erase(...) trong hàm removeBook hoặc returnBook.
o	Logic: Sau khi xóa một phần tử ở giữa, thuật toán của vector sẽ dịch chuyển (shift) tất cả các phần tử phía sau lên trước một nấc để lấp đầy khoảng trống.
o	Độ phức tạp: $O(N)$ (trong trường hợp xấu nhất là xóa phần tử đầu tiên).


V. Hướng dẫn sử dụng:

1. Main Menu ( Giao diện chính )
Khi khởi động chương trình, bạn sẽ thấy 4 lựa chọn:
•	1. Dang nhap Admin: Dành cho thủ thư để quản lý sách.
•	2. Dang nhap User: Dành cho độc giả đã có tài khoản.
•	3. Dang ky User: Dành cho người dùng mới chưa có tài khoản.
•	4. Thoat: Lưu toàn bộ dữ liệu và tắt chương trình.

 

________________________________________

2. Admin (Quản trị viên)
 

Chọn phím 1 từ menu chính để truy cập quyền của Admin
•	Thêm sách mới (Chọn 1):
o	Nhập ID (Ví dụ: B001). Lưu ý: ID nên viết liền, không dấu.
o	Nhập Tên sách (Ví dụ: Doraemon Tap 1).
o	Nhập Tác giả (Ví dụ: Fujiko F Fujiko).
o	Nhập Số lượng (Ví dụ: 5).
o	Hệ thống sẽ thêm sách vào kho.
•	Xóa sách (Chọn 2): Nhập đúng ID của sách cần xóa.
•	Tìm kiếm (Chọn 3, 4, 5): Bạn có thể tìm theo tên, tác giả hoặc ID. Hệ thống có hỗ trợ tìm gần đúng (ví dụ gõ "Dora" sẽ ra "Doraemon").
•	Xem tất cả các sách trong thư viện (Chọn 6)
•	Xóa người dùng (Chọn 7): Nếu một sinh viên ra trường hoặc mất thẻ, nhập ID người dùng (UID) để xóa họ và lịch sử mượn của họ khỏi hệ thống.
•	Thoát & Lưu (Chọn 8): Sau khi thêm/sửa/xóa, bạn bắt buộc phải chọn mục 8 để chương trình ghi dữ liệu vào file library.txt. Nếu tắt ngang cửa sổ console, dữ liệu mới sẽ bị mất.

________________________________________

3. Hướng dẫn cho User (Độc giả)

Bước 1: Đăng ký tài khoản (Lần đầu tiên)
Từ màn hình chính, chọn 3.
•	Nhập ID: Tự chọn một mã định danh (Ví dụ: 202415010). ID này không được trùng với người khác.
•	Nhập Tên: Tên hiển thị của bạn (Ví dụ: Nguyen Van A).
•	-> Sau khi đăng ký xong, hệ thống sẽ quay lại màn hình chính.
 


Bước 2: Đăng nhập
Từ màn hình chính, chọn 2.
•	Nhập ID bạn vừa đăng ký (Ví dụ: 202415010).
•	Nếu đúng ID, bạn sẽ vào menu User.
 

Bước 3: Các thao tác mượn/trả
•	Xem sách (Chọn 4): Xem toàn bộ sách có trong thư viện để chọn sách muốn mượn. Hãy nhớ ID sách.
•	Mượn sách (Chọn 6):
o	Nhập ID sách cần mượn (Ví dụ: B001).
o	Điều kiện thành công: Sách đó phải còn số lượng > 0 và bạn chưa mượn cuốn đó trước đây.
•	Trả sách (Chọn 7):
o	Nhập ID sách muốn trả.
o	Hệ thống sẽ xóa sách khỏi danh sách mượn của bạn và cộng thêm 1 vào số lượng trong kho Admin.
•	Xem sách đang mượn (Chọn 5): Kiểm tra lại xem mình đang giữ những cuốn nào.
•	Đăng xuất (Chọn 8): Lưu dữ liệu cá nhân của bạn và quay lại màn hình chính.


VI. Kết luận
1. Tổng quan sản phẩm:
Xây dựng thành công hệ thống quản lý thư viện trên nền tảng Console, giải quyết bài toán quản lý sách với quy trình khép kín: Admin quản lý kho (Thêm/Sửa/Xóa) và User thao tác mượn/trả. Hệ thống đảm bảo tính bền vững của dữ liệu thông qua cơ chế lưu trữ File (.txt), không bị mất thông tin khi tắt ứng dụng.
2. Kỹ thuật cốt lõi: 
Dự án áp dụng triệt để các kiến thức nền tảng của C++:
•	OOP (Hướng đối tượng): Thiết kế chuẩn mô hình với 3 Class chính (Book, Library, User) đảm bảo tính đóng gói và tái sử dụng mã nguồn.
•	Cấu trúc dữ liệu: Sử dụng std::vector để quản lý mảng động và con trỏ để thao tác dữ liệu trực tiếp, tối ưu bộ nhớ.
•	Thuật toán: Vận dụng linh hoạt tìm kiếm tuyến tính (Linear Search), sắp xếp (Sort) và kỹ thuật xử lý chuỗi (String Parsing) để đọc/ghi file.
3. Đánh giá & Hướng phát triển: 
Hệ thống hoạt động ổn định, logic cập nhật số lượng tồn kho chính xác. Tuy nhiên, giao diện dòng lệnh còn hạn chế về trải nghiệm người dùng và chưa có bảo mật cao. Hướng phát triển tiếp theo là nâng cấp lên giao diện đồ họa (GUI) và tích hợp Cơ sở dữ liệu (SQL) để xử lý lượng dữ liệu lớn hơn.

VII. Tài liệu tham khảo
TusharKukra/LMS-Library-Management-System
https://github.com/ashutoshsuman99/Library-Management-System.git
https://github.com/abdulsamie10/Library-Management-System.git



--------------------End--------------------
