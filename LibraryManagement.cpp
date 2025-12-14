#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

class Book {
private:
	int id;
	string title;
	string author;
	int quantity;
public:
	Book(): id(0), title(""), author(""), quantity(0) {}
	Book(int id, string t, string a, int q) : id(id), title(t), author(a), quantity(q) {}
	
	int getId() const { return id; }
	void setId(int id) {this->id = id;}
	
	string getTitle() const { return title; }
	void setTitle(string title) {this->title = title;}
	
	string getAuthor() const { return author; }
	void setAuthor(string author) {this->author = author;}
	
	int getQuantity() const { return quantity; }
	void setQuantity(int quantity) {this->quantity = quantity;}
	
	void displayInfo() const {
		cout << "Book ID: " << id
		 	<< " - Title: " << title
		 	<< " - Author: " << author
		 	<< " - Quantity left: " << quantity << endl;
	}
};

class BorrowableBook : public Book {
private:
	string borrowDate;
	bool isBorrowed;
public:
	BorrowableBook(): Book(), borrowDate(""), isBorrowed(false) {}
	BorrowableBook(int id, string t, string a, int q, string bd) : Book(id, t, a, q), borrowDate(bd) {}
	BorrowableBook(int id, string t) : Book(id, t, "Unknown", 1), borrowDate(""), isBorrowed(false) {}

	void borrowBook() {
		int q = getQuantity();
		if (q<=0) {
			cout <<"Khong co sach de muon." << endl;
			return;
		}
		setQuantity(q - 1);
		cout << "Muon thanh cong!" << endl; 	
	}
		 
	void returnBook() {
		int q = getQuantity();
		if (q<=0) {
			cout << "Khong co sach de tra." << endl;
			return;
		}
		setQuantity(q + 1);
		cout <<"Tra sach thanh cong." << endl;
	}
};

class LibraryManagement {
private:
	vector<BorrowableBook> books;
public:
	LibraryManagement(BorrowableBook book) {
		books.push_back(book);
	}
	//1.Them sach
	void addBooks(BorrowableBook book) {
		books.push_back(book);
		cout <<"Da them sach:" << book.getTitle() << endl;
	}
	//2.Xem sach
	void viewBooks(BorrowableBook book) {
		cout <<"Thong tin sach duoc yeu cau:" << book.getTitle() << endl;
		book.displayInfo();
	}
	//3.Xem tat ca sach
	void viewAllBooks() {
        cout << "\n--- Danh sach tat ca sach trong thu vien ---" << endl;
        for (const auto& book : books) {
            book.displayInfo();
        }
    }
    //4.Tim sach
    void searchBook(string title) {
    	bool found
    	cout <<"\n--- Ket qua tim kiem " << title << "---" << endl;
    	for (const auto& book : books) {
    		if (book.getTitle() == title) {
    			book.displayInfo();
    			found = true;
			}
		}
		if (!found) cout <<"Khong tim thay sach nay." << endl;
	}
	//5.Muon sach
	void issueFunc(string id) {
		for (auto&book : books) {
			if (book.getId() == id) {
				if (!book.isBorrowed) {
					book.isBorrowed = true;
					cout <<"Muon thanh cong sach ID:" << id << endl;
				} else {
					cout <<"Sach ID " << id << "Da duoc muon boi nguoi khac." << endl;
				}
				return;
				}
			}
			cout <<"Khong tim thay ID sach:" << id << endl;
	}
	//6.Tra sach
	void returnFunc(string id) {
		for (auto&book : books) {
			if (book.getId() == id) {
				if (!book.isBorrowed) {
					book.isBorrowed = false;
					cout <<"Tra thanh cong sach ID:" << id << endl;
			} else {
				cout <<"Sach ID" << id << "Dach nay hien tai chua duoc muon." << endl;
			}
			return;
			}
		}
		cout <<"Khong tim thay ID sach:" << id << endl;
	}
	//7.Luu du lieu ra file
	void savetoFile() {
		ofstream outFile("library_data.txt");
		if (outFile.is_open()) {
			for (const auto&book : books) {
				outFile << book.id << "," << book.title << "," << book.isBorrowed << endl;	
			}
			outFile.close();
			cout <<"Da luu du lieu vao file library_data.txt" << endl;
	} else {
		    cout <<"Loi mo file de ghi" << endl;
		}
	}
	//8.Doc du lieu tu file
	void loadfromFile() {
		ifstream inFile("library_data.txt");
		if (inFile.is_open()) {
			books.clear();
			string line;
			while (getline(inFile,line)) {
				size_t pos1 = line.find(',');
				size_t pos2 = line.find_last_of(',');
				
				if (pos1 != string::npos && pos2 != string::npos) {
					string id = line.substr(0,pos1);
					string title = line.substr(pos1 + 1, pos2 - pos1 -1 );
					bool status = (line.substr(pos2 + 1) == "1");
					
					Borrowable Book b(id, title);
					b.isBorrowed = status;
					book.push.back(b);
				}
			}
			inFile.close();
			cout <<"Da load du lieu tu file" << endl;
	} else {
		    cout <<"Khong tim thay file du lieu hoac loi file mo!" << endl;
		}
	}
	
};

//Ham main de kiem tra
int main() {
//1.Tao sach
    BorrowableBook b1(001, "Lap trinh C++");
    BorrowableBook b2(002, "Cau truc du lieu");
    BorrowableBook b3(003, "Giai tich 1");

//2.Khoi tao LibraryManagement voi cuon sach thu 1
    LibraryManagement lib(b1);

//3.Them sach khac
    lib.addBooks(b2);
    lib.addBooks(b3);

//4.Hien thi danh sach
    lib.viewAllBooks();
    
//5.Tim kiem
    lib.searchBook("Cau truc du lieu");

//6.Muon sach
    lib.issueFunc(002);
    lib.issueFunc(002);

//7.Tra sach
    lib.returnFunc(002);

//8.Luu file
    lib.saveToFile();

    return 0;
}
