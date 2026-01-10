#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Khai bao truoc class Book de dung trong ham so sanh
class Book;
class Library;
class User;
bool compareBooksByTitle(const Book &a, const Book &b);

class Book {
private:
    string id;
    string title;
    string author;
    int quantity;
public:
    Book(): id(""), title(""), author(""), quantity(0) {}
    Book(string id_, string title_, string author_, int quantity_): id(id_), title(title_), author(author_), quantity(quantity_) {}
    
    string getID() const { return id; }
    void setID(string id) { this->id = id; }
    string getTitle() const { return title; }
    void setTitle(string title) { this->title = title; }
    string getAuthor() const { return author; }
    void setAuthor(string author) { this->author = author; }
    int getQuantity() const { return quantity; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    
    void displayBook() const {
        cout << left << setw(10) << id
            << left << setw(30) << title
            << left << setw(20) << author
            << right << setw(10) << quantity << '\n';
    }

    bool checkAvailable() {
        return quantity > 0;
    }

    void updateQuantity(int q) {
        quantity += q;
    }
};

bool compareBooksByTitle(const Book &a, const Book &b) {
    return a.getTitle() < b.getTitle();
}

class User {
private:
    string name;
    string user_id;
    vector<Book> borrowed_books;
public:
    User(): name(""), user_id("") {}
    User(string name_, string uid_): name(name_), user_id(uid_) {}

    string getUID() const { return user_id; }
    string getName() const { return name; }

    void borrowBook(Book& b) {
        if (b.checkAvailable()) {
            borrowed_books.push_back(b);
            b.updateQuantity(-1);
            cout << "Nguoi dung " << name << " (ID: " << user_id << ") da muon sach:\n ";
            b.displayBook();
        } else {
            cout << "Sach:\n";
            b.displayBook();
            cout << " -> Hien tai khong the cho muon (het hang).\n";
        }
    }

    bool returnBook(string bookId) {
        for (size_t i = 0; i < borrowed_books.size(); i++) {
            if (borrowed_books[i].getID() == bookId) {
                borrowed_books.erase(borrowed_books.begin() + i);
                cout << "Da tra sach thanh cong!\n";
                return true;
            } 
        }
        cout << "Ban khong muon cuon sach nay.\n";
        return false;
    }

    void displayBorrowedBooks() {
        if (borrowed_books.empty()) {
            cout << "Khong co sach nao dang muon." << '\n';
            return;
        }
        cout << "--- Sach dang muon ---\n";
        for (size_t i = 0; i < borrowed_books.size(); i++) {
            cout << "- " << borrowed_books[i].getTitle() << " (ID: " << borrowed_books[i].getID() << ")\n";
        }
    }
	
    string createUserFile() const {
        return "User_" + user_id + ".txt";
    }
	
	void userMenu(User& user, Library& lib);

    void writeToFile(const string &filename) {
        ofstream out(filename.c_str());
        for (size_t i = 0; i < borrowed_books.size(); i++) {
            out << borrowed_books[i].getID() << '|' 
                << borrowed_books[i].getTitle() << '|' 
                << borrowed_books[i].getAuthor() << '|' << 1 << '\n';
        }
        out.close();
    }
};

void addUser(vector<User>& users) {
    string uid, name;
    cout << "Nhap ID: ";
    getline(cin, uid);

    for (size_t i = 0; i < users.size(); i++) {
    	if (users[i].getUID() == uid) {
        	cout << "ID da ton tai!\n";
        	return;
    	}
	}

    cout << "Nhap ten: ";
    getline(cin, name);
    users.push_back(User(name, uid));
    cout << "Dang ky thanh cong!\n";
}

int loginUser(const vector<User>& users, const string& uid) {
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUID() == uid)
            return i;
    }
    return -1;
}

class Library {
public:
    vector<Book> bookList;

    void addBook(const Book& book) {
        bool found = false;
        for(size_t i = 0; i < bookList.size(); i++) {
            if(bookList[i].getID() == book.getID()) {
                cout << "ID da ton tai. Cap nhat thong tin sach cu.\n";
                bookList[i].setTitle(book.getTitle());
                bookList[i].setAuthor(book.getAuthor());
                bookList[i].setQuantity(book.getQuantity());
                found = true;
                break;
            }
        }
        
        if(!found) {
            bookList.push_back(book);
            cout << "Them sach thanh cong!\n";
        }
    }

    void removeBook(const string &id) {
        bool found = false;
        for(int i = (int)bookList.size() - 1; i >= 0; i--) {
            if(bookList[i].getID() == id) {
                bookList.erase(bookList.begin() + i);
                cout << "Da xoa sach khoi thu vien.\n";
                found = true;
                break; 
            }
        }
        if (!found) cout << "Khong tim thay sach!\n";
    }
    
    // Ham tim va tra ve sach = pointer, tra ve con tro NULL neu khong tim thay sach
    Book* getBookRefByID(const string& id) {
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList[i].getID() == id) return &bookList[i];
        }
        return NULL;
    }

    void searchBookByTitle(const string& title) {
        bool found = false;
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList[i].getTitle() == title) {
                bookList[i].displayBook();
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay sach!\n";
    }
    
    void searchBookByID(const string& id) {
        bool found = false;
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList[i].getID() == id) {
                bookList[i].displayBook();
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay sach!\n	";
    }

    void searchBookByAuthor(const string& author) {
        bool found = false;
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList[i].getAuthor() == author) {
                bookList[i].displayBook();
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay sach!\n";
    }
    
    void displayBooks() {
        if (bookList.empty()) {
            cout << "Thu vien khong co sach.\n";
            return;
        }
        
        vector<Book> sortedList = bookList;
        sort(sortedList.begin(), sortedList.end(), compareBooksByTitle);
        
        cout << left << setw(10) << "ID"
                << left << setw(30) << "Ten sach"
                << left << setw(20) << "Tac gia"
                << right << setw(10) << "So luong" << '\n';
        cout << string(70, '-') << '\n';
        
        for (size_t i = 0; i < sortedList.size(); i++) {
            sortedList[i].displayBook();
        }
    }
    
    void libraryMenu(Library& lib, vector<User>& users) {
    	int choice;
    	string id;
    	
    	do {
    		cout << "\n     BAN DA DANG NHAP VOI TU CACH ADMIN     \n";
        	cout << "1. Them sach" << '\n';
        	cout << "2. Xoa sach khoi thu vien" << '\n';
        	cout << "3. Tim sach theo ten" << '\n';
        	cout << "4. Tim sach theo tac gia" << '\n';
        	cout << "5. Tim sach theo ID" << '\n';
        	cout << "6. Xem tat ca sach trong thu vien" << '\n';
        	cout << "7. Xoa nguoi dung" << '\n';
        	cout << "8. Thoat chuong trinh" << '\n';
        	cout << "Chon thao tac: ";
        	if (!(cin >> choice)) {
            	cin.clear();
            	cin.ignore(1000, '\n');
            	choice = 0;
        	}
        	cin.ignore();

        	string id, uid, title, author, name;
        	int quantity;
        	Book* bookPtr = NULL;
        	bool userFound = false;
        	int userIndex = -1;

        	switch (choice) {
        	case 1:
            	cout << "Nhap ID sach: "; getline(cin, id);
            	cout << "Nhap ten sach: "; getline(cin, title);
            	cout << "Nhap ten tac gia: "; getline(cin, author);
            	cout << "Nhap so luong sach: "; cin >> quantity;
            	lib.addBook(Book(id, title, author, quantity));
            	break;
        	case 2:
            	cout << "Dien ID sach can xoa: "; getline(cin, id);
            	lib.removeBook(id);
            	break;
        	case 3:
            	cout << "Dien ten sach: "; getline(cin, title);
            	lib.searchBookByTitle(title);
            	break;
        	case 4:
            	cout << "Dien ten tac gia: "; getline(cin, author);
            	lib.searchBookByAuthor(author);
            	break;
        	case 5:
            	cout << "Dien ID sach: "; getline(cin, id);
            	lib.searchBookByID(id);
            	break;
        	case 6:
            	lib.displayBooks();
            	break;
        	case 7: // Xoa nguoi dung
            	cout << "Nhap ID nguoi dung can xoa: "; getline(cin, uid);
            	for (size_t i = 0; i < users.size(); i++) {
                	if (users[i].getUID() == uid) {
                    	users.erase(users.begin() + i);
                    	cout << "Da xoa nguoi dung.\n";
                    	userFound = true;
                    	break;
                	}
            	}
            	if (!userFound) cout << "Khong tim thay nguoi dung.\n";
            	break;
        	case 8:
            	lib.writeToFile("library.txt");
            	for(size_t i=0; i < users.size(); i++) {
                	users[i].writeToFile(users[i].createUserFile());
            	}
            	cout << "Da luu du lieu va thoat.\n";
            	break;
        	default:
            	cout << "Ban chua chon thao tac, hay thu lai.\n";
            	break;
        	}
    	} while (choice != 8);
	}

    void writeToFile(const string &filename) {
        ofstream out(filename.c_str());
        for (size_t i = 0; i < bookList.size(); i++) {
            out << bookList[i].getID() << '|' 
                << bookList[i].getTitle() << '|' 
                << bookList[i].getAuthor() << '|' 
                << bookList[i].getQuantity() << '\n';
        }
        out.close();
    }

    void loadFromFile(const string& filename) {
        ifstream f(filename.c_str());
        if (!f.is_open()) return;
        string line;
        while (getline(f, line)) {
            if (line.empty()) continue;
            string id, title, author;
            int quantity;
            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);
            if (p1 != string::npos && p2 != string::npos && p3 != string::npos) {
                id = line.substr(0,p1);
                title = line.substr(p1+1, p2-p1-1);
                author = line.substr(p2+1, p3-p2-1);
                // Dung atoi (string to int) thay vi stoi de tranh loi C++11
                quantity = atoi(line.substr(p3+1).c_str());
                bookList.push_back(Book(id,title,author,quantity));
            }
        }
        f.close();
    }
};

void User::userMenu(User& user, Library& lib) {
	int choice;
	string title, id, author;
		
	do {
		cout << "\n     BAN DA DANG NHAP VOI TU CACH USER     \n";
        cout << "1. Tim sach theo ten" << '\n';
        cout << "2. Tim sach theo tac gia" << '\n';
        cout << "3. Tim sach theo ID" << '\n';
        cout << "4. Xem tat ca sach trong thu vien" << '\n';
        cout << "5. Muon sach" << '\n';
        cout << "6. Tra sach" << '\n';
        cout << "7. Dang xuat" << '\n';
        cout << "Chon thao tac: ";
        cin >> choice;
        cin.ignore();

        Book* b;
        switch(choice) {
        case 1:
        	cout << "Nhap ten sach: ";
        	getline(cin, title);
        	lib.searchBookByTitle(title);
        	break;
       	case 2:
        	cout << "Nhap ten tac gia: ";
        	getline(cin, author);
        	lib.searchBookByAuthor(author);
        	break;
        case 3:
        	cout << "Nhap ID sach: ";
        	getline(cin, id);
        	lib.searchBookByID(id);
        	break;
        case 4:
        	lib.displayBooks();
        	break;
        case 5:
        	cout << "Nhap ID sach: ";
        	getline(cin, id);
        	b = lib.getBookRefByID(id);
        	if (b) user.borrowBook(*b);
        	else cout << "Khong tim thay sach.";
        	break;
        case 6:
            cout << "Nhap ID sach: ";
            getline(cin, id);
            b = lib.getBookRefByID(id);
            if (b && user.returnBook(id)) {
                b->updateQuantity(1);
            }
            break;
        case 7:
            return;
        default:
            cout << "Ban chua chon thao tac. Vui long thu lai!";
            break;
        }
	} while (choice != 7);
}
	
vector<User> users;

int main() {
	Library lib;
	int choice;
	string uid;
	int idx;
    do {
    	cout << "\n===== MAIN MENU =====\n";
    	cout << "1. Dang nhap Admin\n";
    	cout << "2. Dang nhap User\n";
    	cout << "3. Dang ky User\n";
    	cout << "4. Thoat\n";
    	cin >> choice;
    	cin.ignore();

    	switch (choice) {
    	case 1:
        	lib.libraryMenu(lib, users);
        	break;
    	case 2:
        	cout << "Nhap ID: ";
        	getline(cin, uid);
        	idx = loginUser(users, uid);
        	if (idx != -1)
            	users[idx].userMenu(users[idx], lib);
        	else
            	cout << "Sai ID!\n";
        	break;
    	case 3:
        	addUser(users);
        	break;
    	}
	} while (choice != 4);
	return 0;
}
