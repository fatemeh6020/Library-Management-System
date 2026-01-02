//Fatemeh_Q_term3_Computer_Engineering
//Project name = Library Management System
#include <iostream>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    int year;
    string status;
};

const int MAX_BOOKS = 100;
const int MAX_HISTORY = 5;

class Stack {	
private:
    string history[MAX_HISTORY];
    int top = -1;
public:
    void push(const string& operation) {
        if (top < MAX_HISTORY - 1) {//checking if the stack is not full
            history[++top] = operation;// adding operations to the stack
        } else {//if the  stack is full,the operation removes the oldest and adds the newest
            for (int i = 1; i < MAX_HISTORY; ++i) {
                history[i - 1] = history[i];//moving operations
            }
            history[MAX_HISTORY - 1] = operation;//add new operations to the last position
        }
    }
    string pop() {
        if (top == -1) {//if the stack was empty
            return "";// it would be nothing
        }
        return history[top--];//top - 1 mishe
    }
    bool isEmpty() {
        return top == -1;// means stack is empty
    }
    void show() {
        for (int i = top; i >= 0; --i) {
            cout << history[i] << endl;// printing operations
        }
    }
};

class Library {
private:
    Book books[MAX_BOOKS]; //array of books
    int bookCount = 0; // the num of books in the array
    Stack history; // for save the last 5 operationa

public:
    void addBook(int id, const string& title, const string& author, int year) {
        if (bookCount < MAX_BOOKS) {//if we have extra space for books
            books[bookCount] = {id, title, author, year, "available"};//creating a new book
            bookCount++;
            history.push("Add book: " + title);//add the operations to the history
            cout << "Book with title " << title << " added.\n";
        } else {
            cout << "Library is full!\n";
        }
    }
    void removeBook(int id) {
        for (int i = 0; i < bookCount; ++i) {//browse all books
            if (books[i].id == id) {//if user code == book code it has
                history.push("Remove book: " + books[i].title);//add the operations to the history
                cout << "Book with title " << books[i].title << " removed.\n";
                books[i] = books[bookCount - 1];//deleted book == last book
                bookCount--;
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
    }
    void searchBook(int id) {
        for (int i = 0; i < bookCount; ++i) {//browse all books
            if (books[i].id == id) {//if user code == book code it has
                cout << "Book found: " <<"ID: " << books[i].id << endl;
                cout << "Title: " << books[i].title << endl;
                cout << "Author: " << books[i].author << endl;
                cout << "Year: " << books[i].year << endl;
                cout << "Status:= " << books[i].status << endl;
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
    }
    void sortBooksById() {
        for (int i = 0; i < bookCount - 1; ++i) {//bookCount - 1 = last one,doesn't need to be sorted
            for (int j = i + 1; j < bookCount; ++j) {
                if (books[i].id > books[j].id) { // if the book code > next book code
                    swap(books[i], books[j]); // the two books are swapped
                }
            }
        }
        history.push("Sort books by ID");//add the operations to the history
        cout << "Books sorted by ID.\n";
        for (int i = 0; i < bookCount; ++i) {
        	cout << "\nID: " << books[i].id << "  Title: " << books[i].title << "  Year: " << books[i].year;
		}
    }
    void sortBooksByYear() {
        for (int i = 0; i < bookCount - 1; ++i) {
            for (int j = i + 1; j < bookCount; ++j) {
                if (books[i].year > books[j].year) {//if the book code > next book code
                    swap(books[i], books[j]);//if the book code > next book code
                }
            }
        }
        history.push("Sort books by publication year");//add the operations to the history
        cout << "Books sorted by publication year.\n";
        for (int i = 0; i < bookCount; ++i) {
        	cout << "\nYear: " << books[i].year << "  Title: " << books[i].title << "  ID: " << books[i].id;
		}
    }
    void requestLoan(int id) {
        for (int i = 0; i < bookCount; ++i) {//browse all books
            if (books[i].id == id) {//if the book is found
                if (books[i].status == "available") {//no one borrowed
                    books[i].status = "loaned out";//change of status
                    history.push("Loan book: " + books[i].title);//add the operations to the history
                    cout << "Book " << books[i].title << " loaned out.\n";
                } else {//if borrowing
                    cout << "Book " << books[i].title << " has already been loaned out.\n";
                }
                return;
            }
        }//if not found
        cout << "Book with ID " << id << " not found.\n";
    }
    void returnBook(int id) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].id == id) {//if the book is found
                if (books[i].status == "loaned out") {//if borrowed
                    books[i].status = "available";//change of status
                    history.push("Return book: " + books[i].title);//add the operations to the history
                    cout << "Book " << books[i].title << " returned.\n";
                } else {//if isn't borrowed
                    cout << "Book " << books[i].title << " has not been loaned out.\n";
                }
                return;
            }
        }//if not found
        cout << "Book with ID " << id << " not found.\n";
    }
    void showLastOperations() {//operations history
        cout << "\nLast 5 operations:\n";
        history.show();//print them
    }
};

int main() {
    Library library;
    int choice, id, year;
    string title, author;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add book\n";
        cout << "2. Remove book\n";
        cout << "3. Search book\n";
        cout << "4. Sort books by ID\n";
        cout << "5. Sort books by publication year\n";
        cout << "6. Request loan\n";
        cout << "7. Return book\n";
        cout << "8. Show last 5 operations\n";
        cout << "9. Exit\n";
        cout << "Please enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Book ID: ";
                cin >> id;
                cout << "Book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Author name: ";
                getline(cin, author);
                cout << "Publication year: ";
                cin >> year;
                library.addBook(id, title, author, year);
                break;
            case 2:
                cout << "Book ID to remove: ";
                cin >> id;
                library.removeBook(id);
                break;
            case 3:
                cout << "Book ID to search: ";
                cin >> id;
                library.searchBook(id);
                break;
            case 4:
                library.sortBooksById();
                break;
            case 5:
                library.sortBooksByYear();
                break;
            case 6:
                cout << "Book ID for loan request: ";
                cin >> id;
                library.requestLoan(id);
                break;
            case 7:
                cout << "Book ID to return: ";
                cin >> id;
                library.returnBook(id);
                break;
            case 8:
                library.showLastOperations();
                break;
            case 9:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}