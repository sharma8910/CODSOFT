#include <iostream>
#include <vector>
#include <string>
 #include <ctime>
using namespace std;

class Book {
public:
    string title;
    string author;
    string ISBN;
    bool available;

    Book(string t, string a, string i) {
        title = t;
        author = a;
        ISBN = i;
        available = true;
    }
};

class Borrower {
public:
    string name;
    int  id;

    Borrower(string n, int i) {
        name = n;
        id = i;
    }
};

class Transaction {
public:
    string borrowerID;
    string ISBN;
    time_t checkoutDate;
    time_t returnDate;
    bool returned;

    Transaction(string b, string i) {
        borrowerID = b;
        ISBN = i;
        time(&checkoutDate);
        returned = false;
    }
};

class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;

public:
    void addBook(Book b) {
        books.push_back(b);
    }

    void addBorrower(Borrower br) {
        borrowers.push_back(br);
    }

    void searchBook(string search) {
        bool found = false;
        for (auto &b : books) {
            if (b.title == search || b.author == search || b.ISBN == search) {
                cout << "Found: " << b.title << " by " << b.author
                     << " -> ISBN: " << b.ISBN
                     << " ->Available: " << (b.available ? "Yes" : "No") << endl;
                found = true;
            }
        }
        if (!found) cout << "No book found.\n";
    }

    void checkoutBook(string borrowerID, string isbn) {
        for (auto &b : books) {
            if (b.ISBN == isbn && b.available) {
                b.available = false;
                transactions.push_back(Transaction(borrowerID, isbn));
                cout << "Book checked out successfully!\n";
                return;
            }
        }
        cout << "Book not available or ISBN not found!\n";
    }

    void returnBook(string isbn) {
        for (auto &t : transactions) {
            if (t.ISBN == isbn && !t.returned) {
                time(&t.returnDate);
                t.returned = true;

                for (auto &b : books)
                    if (b.ISBN == isbn) b.available = true;

                // fine calculation (7 days free, Rs.10/day after)
                double diff = difftime(t.returnDate, t.checkoutDate) / (60 * 60 * 24);
                if (diff > 7) {
                    int fine = (diff - 7) * 10;
                    cout << "you have to pay fine for it = Rs." << fine << endl;
                } else {
                    cout << "Book returned successfully... thank u\n";
                }
                return;
            }
        }
        cout << "No such borrowed book found!\n";
    }
};

int main() {
    Library lib;

    
    lib.addBook(Book("THE MAHABHARATA", "saint bhagrati", "12ab"));
    lib.addBook(Book("THE RAMYANA", "Guru dev", "13ab"));
    lib.addBook(Book("KARAN 'THE GOODS WARRIOR", "sonu sharma", "14ab"));

    lib.addBorrower(Borrower("sonu", 01));
    lib.addBorrower(Borrower("aditya", 02));
    lib.addBorrower(Borrower("sharma ji", 03));


    int choice;
    string search, id;

    do {
        cout << "\n <+  LIBRARY MENU +> \n";
        cout << "1. Search Book\n";
        cout << "2. Checkout Book\n";
        cout << "3. Return Book\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter title/author/ISBN: ";
            cin >> search;
            lib.searchBook(search);
            break;
        case 2:
            cout << "Enter Borrower ID: "; 
            cin >> id;
            cout << "Enter ISBN: "; 
            cin >>search;
            lib.checkoutBook(id, search);
            break;
        case 3:
            cout << "Enter ISBN: "; 
            cin >> search;
            lib.returnBook(search);
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
