#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <cstdlib> // Thu vien cho atoi neu can, hoac NULL
using namespace std;

// Khai bao truoc
class Book;
class Library;
class User;
bool compareBooksByTitle(const Book &a, const Book &b);
void saveUsers(const vector<User>& users);

// Tim kiem = match ki tu
bool checkForSubstr(const string& a, const string& b) {
    return a.find(b) != string::npos;
}

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

    bool checkAvailable() const {
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
    void setUID(string user_id) { this->user_id = user_id; }
    string getName() const { return name; }
    void setName(string name) { this->name = name; }

    bool borrowBook(Book& b) {
        // Thay auto bang for thuong
        for (size_t i = 0; i < borrowed_books.size(); i++) {
            if (borrowed_books[i].getID() == b.getID()) {
                return false;
            }
        }
        if (b.checkAvailable() == true) {
            borrowed_books.push_back(Book(b.getID(), b.getTitle(), b.getAuthor(), 1));
            b.updateQuantity(-1);
            return true;
        } else {
            return false;
        }
    }

    bool returnBook(string bookID) {
        for (size_t i = 0; i < borrowed_books.size(); i++) {
            if (borrowed_books[i].getID() == bookID) {
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
    
    void userMenu(User& user, Library& lib);

    string createUserFile() const {
        return "User_" + user_id + ".txt";
    }

    void writeToFile(const string &filename) {
        ofstream out(filename.c_str());
        // Thay auto bang for thuong
        for (size_t i = 0; i < borrowed_books.size(); i++) {
            out << borrowed_books[i].getID() << '|'
                << borrowed_books[i].getTitle() << '|'
                << borrowed_books[i].getAuthor() << '|'
                << borrowed_books[i].getQuantity() << '\n';
        }
        out.close();
    }

    void loadFromFile(const string& filename) {
        borrowed_books.clear();
        ifstream f(filename.c_str());
        if (!f.is_open()) return;
        string line;
        while (getline(f, line)) {
            string id, title, author;
            int quantity;
            int p1 = line.find('|');
            int p2 = line.find('|', p1 + 1);
            int p3 = line.find('|', p2 + 1);
            if (p1 == string::npos || p2 == string::npos || p3 == string::npos) continue; // Kiem tra loi dong trong
            
            id = line.substr(0,p1);
            title = line.substr(p1+1, p2-p1-1);
            author = line.substr(p2+1, p3-p2-1);
            quantity = atoi(line.substr(p3+1).c_str()); // Dung atoi thay cho stoi cho an toan
            borrowed_books.push_back(Book(id,title,author,quantity));
        }
        f.close();
    }
};  

class Library {
public:
    vector<Book> bookList;

    void addBook(const Book& b) {
        bool found = false;
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList[i].getID() == b.getID()) {
                cout << "Da co sach voi ID tren. Cap nhat thong tin...\n";
                bookList[i].setTitle(b.getTitle());
                bookList[i].setAuthor(b.getAuthor());
                bookList[i].setQuantity(b.getQuantity());
                found = true;
                break;
            }
        }
        if (!found) {
            bookList.push_back(b);
            cout << "Them sach thanh cong!\n";
        }
    }

    void removeBook(const string &id) {
        bool found = false;
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList[i].getID() == id) {
                bookList.erase(bookList.begin() + i);
                cout << "Da xoa sach khoi thu vien.\n";
                found = true;
                break; 
            }
        }
        if (!found) cout << "Khong tim thay sach!\n";
    }
    
    // Ham tim va tra ve sach = pointer
    Book* getBookRefByID(string id) {
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList[i].getID() == id) {
                return &bookList[i];
            }
        }
        return NULL; // Thay nullptr bang NULL
    }

    // Tim kiem sach = ten
    void searchBookByTitle(const string& title) {
        bool found = false;
        // Thay auto bang for thuong
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList[i].getTitle() == title || checkForSubstr(bookList[i].getTitle(), title)) {
                bookList[i].displayBook();
                found = true;
            }
        }
        if (!found) {
            cout << "Khong tim thay sach!" << '\n';
            return;
        }
    }
    
    // Tim kiem sach = ID
    void searchBookByID(const string& id) {
        bool found = false;
        // Thay auto bang for thuong
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList[i].getID() == id || checkForSubstr(bookList[i].getID(), id)) {
                bookList[i].displayBook();
                found = true;
            }
        }
        if (!found) {
            cout << "Khong tim thay sach!" << '\n';
            return;
        }
    }

    // Tim kiem sach = ten tac gia
    void searchBookByAuthor(const string& author) {
        bool found = false;
        // Thay auto bang for thuong
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList[i].getAuthor() == author || checkForSubstr(bookList[i].getAuthor(), author)) {
                bookList[i].displayBook();
                found = true;
            }
        }
        if (!found) {
            cout << "Khong tim thay sach!" << '\n';
            return;
        }
    }
    
    // Hien thi tat ca sach trong thu vien
    void displayAllBooks() {
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
        do {
            cout << "\n===== BAN DA DANG NHAP VOI TU CACH ADMIN =====\n";
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

            string id, uid, title, author;
            int quantity;
            bool userFound = false;

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
                lib.displayAllBooks();
                break;
            case 7:
                cout << "Nhap ID nguoi dung can xoa: "; getline(cin, uid);
                for (size_t i = 0; i < users.size(); i++) {
                    if (users[i].getUID() == uid) {
                        string filename = users[i].createUserFile();
                        remove(filename.c_str());
                        users.erase(users.begin() + i);
                        saveUsers(users);
                        cout << "Da xoa nguoi dung.\n";
                        userFound = true;
                        break;
                    }
                }
                if (!userFound) cout << "Khong tim thay nguoi dung.\n";
                break;
            case 8:
                lib.writeToFile("library.txt");
                for (size_t i = 0; i < users.size(); i++) {
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
        // Thay auto bang for thuong
        for (size_t i = 0; i < bookList.size(); i++) {
            out << bookList[i].getID() << '|'
                << bookList[i].getTitle() << '|'
                << bookList[i].getAuthor() << '|'
                << bookList[i].getQuantity() << '\n';
        }
        out.close();
    }

    void loadFromFile(const string& filename) {
        bookList.clear();
        ifstream f(filename.c_str());
        if (!f.is_open()) return;
        string line;
        while (getline(f, line)) {
            string id, title, author;
            int quantity;
            int p1 = line.find('|');
            int p2 = line.find('|', p1 + 1);
            int p3 = line.find('|', p2 + 1);
            if (p1 == string::npos || p2 == string::npos || p3 == string::npos) continue;

            id = line.substr(0,p1);
            title = line.substr(p1+1, p2-p1-1);
            author = line.substr(p2+1, p3-p2-1);
            quantity = atoi(line.substr(p3+1).c_str()); // Dung atoi cho chac chan
            bookList.push_back(Book(id,title,author,quantity));
        }
        f.close();
    }
};

void User::userMenu(User& u, Library& lib) {
    int choice;
    string title, id, author;
        
    do {
        cout << "\n===== BAN DA DANG NHAP VOI TU CACH USER =====\n";
        cout << "1. Tim sach theo ten" << '\n';
        cout << "2. Tim sach theo tac gia" << '\n';
        cout << "3. Tim sach theo ID" << '\n';
        cout << "4. Xem tat ca sach trong thu vien" << '\n';
        cout << "5. Xem tat ca sach dang muon" << '\n';
        cout << "6. Muon sach" << '\n';
        cout << "7. Tra sach" << '\n';
        cout << "8. Dang xuat" << '\n';
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
            lib.displayAllBooks();
            break;
        case 5:
            u.displayBorrowedBooks();
            break; // QUAN TRONG: Them break o day de khong bi troi xuong case 6
        case 6:
            cout << "Nhap ID sach de muon: ";
            getline(cin, id);
            b = lib.getBookRefByID(id);
            if (b && u.borrowBook(*b)) {
                cout << "Muon sach thanh cong!";
                b->displayBook();
            }
            else cout << "Khong tim thay sach hoac ban da muon sach nay roi.";
            break;
        case 7:
            cout << "Nhap ID sach de tra: ";
            getline(cin, id);
            b = lib.getBookRefByID(id);
            if (b && u.returnBook(id)) {
                b->updateQuantity(1);
            }
            break;
        case 8:
            u.writeToFile(u.createUserFile());
            return;
        default:
            cout << "Ban chua chon thao tac. Vui long thu lai!";
            break;
        }
    } while (choice != 7);
}

vector<User> users;

int loginUser(const vector<User>& users, const string& uid) {
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUID() == uid)
            return i;
    }
    return -1;
}  

void loadUsers(vector<User>& users) {
    users.clear();
    ifstream f("users.txt");
    if (!f.is_open()) return;

    string line;
    while (getline(f, line)) {
        int p = line.find('|');
        if (p == string::npos) continue;
        string uid = line.substr(0, p);
        string name = line.substr(p + 1);
        users.push_back(User(name, uid));
    }
    f.close();
}

void saveUsers(const vector<User>& users) {
    ofstream out("users.txt");
    // Thay auto bang for thuong
    for (size_t i = 0; i < users.size(); i++) {
        out << users[i].getUID() << '|' << users[i].getName() << '\n';
    }
    out.close();
}

void registerUser(vector<User>& users) {
    string uid, name;
    cout << "Nhap ID cua ban: ";
    getline(cin, uid);

    // Thay auto bang for thuong
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUID() == uid) {
            cout << "ID da ton tai!\n";
            return;
        }
    }

    cout << "Nhap ten: ";
    getline(cin, name);

    users.push_back(User(name, uid));
    saveUsers(users);   
    cout << "Dang ky thanh cong!\n";
}

int main() {
    Library lib;
    int choice;
    string uid;
    int idx;
    lib.loadFromFile("library.txt");
    loadUsers(users);
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
            if (idx != -1) {
                users[idx].loadFromFile(users[idx].createUserFile());
                users[idx].userMenu(users[idx], lib);
            } else {
                cout << "Sai ID\n";
            }
            break;
        case 3:
            registerUser(users);
            break;
        case 4:
            lib.writeToFile("library.txt");
            saveUsers(users);
            for (size_t i = 0; i < users.size(); i++) {
                users[i].writeToFile(users[i].createUserFile());
            }
            break;  
        }
    } while (choice != 4);
    return 0;
}
