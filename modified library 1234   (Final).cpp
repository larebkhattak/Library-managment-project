#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include <conio.h>
using namespace std;
// Structure to represent a book
struct Book {
    string title;
    string author;
    int id;
    Book* next;
    Book(string t, string a, int i) : title(t), author(a), id(i), next(nullptr) {}
};
// Structure to represent a student
struct Student {
    string name;
    int studentId;
    string book;
    time_t issueTime;
    time_t returnTime;
    Student* next;
    Student(string n, int id, string b) : name(n), studentId(id), book(b), next(nullptr) {
        time(&issueTime);
        returnTime = 0;
    }
};
class Library {
private:
    string libraryName;
    Book* bookList;
    Student* studentList;

public:
    Library(string name) : libraryName(name), bookList(nullptr), studentList(nullptr) {
        // Store some initial books
        addBook("Crime and Punishment:\n", "Mark Twain\n", 9);
        addBook("The Three Musketeers\n", "Alexandre Dumas\n", 8);
        addBook("Treasure Island by Robert\n", "Louis Stevenson\n", 7);
        addBook("King Solomon's Mines\n", "H. Rider Haggard and A. C. Michael\n", 6);
        addBook("Journey to the Center of the Earth\n", "Jules Verne\n", 5);
        addBook("The Count of Monte Cristo\n", "Alexandre Dumas\n", 4);
        addBook("Tarzan of the Apes\n", "Edgar Rice Burroughs\n", 3);
        addBook("Heart of Darkness\n", "Joseph Conrad\n", 2);
        addBook("The Jungle Book\n", "Rudyard Kipling\n", 1);
    }
    // Add a new book to the library
    void addBook(string title, string author, int id) {
        if (id <= 0) {
            cout << "Invalid book ID. Please enter a valid book ID." << endl;
            return;
        }
        // Check if the book ID already exists
        Book* currentBook = bookList;
        while (currentBook) {
            if (currentBook->id == id) {
                cout << "Book with ID " << id << " already exists in the " << libraryName << " library." << endl;
                return;
            }
            currentBook = currentBook->next;
        }
        Book* newBook = new Book(title, author, id);
        newBook->next = bookList;
        bookList = newBook;
    }
    // Display the list of available books
    void displayBooks() {
        Book* current = bookList;
        if (!current) {
            cout << "The library is empty." << endl;
            return;
        }
        while (current) {
            cout << "Book ID: " << current->id << "\n Title: " << current->title << " Author: " << current->author << endl;
            current = current->next;
        }
    }
    // Issue a book to a student
    // One student can issue a single book
    void issueBook(string studentName, int studentId, int bookId) {
        Book* currentBook = bookList;
        Student* currentStudent = studentList;
        while (currentStudent) {
            if (currentStudent->studentId == studentId && currentStudent->returnTime == 0) {
                cout << "You already have a book (" << currentStudent->book << ") issued. Please return it before issuing another book." << endl;
                return;
            }
            currentStudent = currentStudent->next;
        }
        while (currentBook) {
            if (currentBook->id == bookId) {
                currentStudent = new Student(studentName, studentId, currentBook->title);
                currentStudent->next = studentList;
                studentList = currentStudent;
                cout << "Book issued successfully!" << endl;
                return;
            }
            currentBook = currentBook->next;
        }
       cout << "Invalid book ID. Please enter a valid book ID." << endl;
    }
    // Return a book from a student
    void returnBook(int studentId) {
        Student* currentStudent = studentList;

        while (currentStudent) {
            if (currentStudent->studentId == studentId && currentStudent->returnTime == 0) {
                cout << "You have returned the book (" << currentStudent->book << "). Thank you!" << endl;
                time(&currentStudent->returnTime);
                return;
            }
            currentStudent = currentStudent->next;
        }
        cout << "You have no book issued, or the book is already returned." << endl;
    }
    // Delete a book from the library
    void deleteBook(int bookId) {
        if (bookId <= 0) {
            cout << "Invalid book ID. Please enter a validbook ID." << endl;
            return;
        }
        Book* currentBook = bookList;
        Book* prevBook = nullptr;
        bool found = false;
        while (currentBook) {
            if (currentBook->id == bookId) {
                found = true;
                if (prevBook) {
                    prevBook->next = currentBook->next;
                } else {
                    bookList = currentBook->next;
                }
                delete currentBook;
                cout << "Book with ID " << bookId << " deleted from the " << libraryName << " library." << endl;
                break; // Exit the loop once the book is found and deleted
            }
            prevBook = currentBook;
            currentBook = currentBook->next;
        }
        if (!found) {
            cout << "Book with ID " << bookId << " not found in the " << libraryName << " library." << endl;
        }
    }
    // Get the list of students
    Student* getStudentList() {
        return studentList;
    }
};
int main() {
    string libraryName;
    Library library(""); // Specify the library name
    int choice;
    bool welcomeMessageDisplayed = false;
    // username --->>> DSA.....
    // password----->>> 1234
    string adminUsername = "DSA";
    string adminPassword = "1234";
    bool adminLoggedIn = false;
    bool studentLoggedIn = false;

    do {
        if (!welcomeMessageDisplayed) {
            cout << libraryName << "\n ==================================================\n";
            cout << libraryName << "\n ================== WELCOME TO ==================== \n";
            cout << libraryName << "\n ----------- Library Management System ------------ \n";
            cout << libraryName << "\n =================================================== \n \n";
            welcomeMessageDisplayed = true;
        }

        cout << "1. Admin" << endl;
        cout << "2. Student" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
            case 1: {
                string username, password;
                if (!adminLoggedIn) {
                    cout << "Enter Username: ";
                    cin >> username;
                    cout << "Enter Password: ";
                    password = "";
                    char ch;
                    while ((ch = _getch()) != '\r') { // Use _getch() to hide password input
                        cout << '*';
                        password += ch;
                    }
                    if (username == adminUsername && password == adminPassword) {
                        adminLoggedIn = true;
                        cout << "Login successful!" << endl;
                    } else {
                        cout << "Login failed. Please enter valid credentials." << endl;
                        break;
                    }
                }

                int adminChoice;
                do {
                    cout << "\nAdmin Menu: \n";
                    cout << "1. Add a Book" << endl;
                    cout << "2. Delete a Book" << endl;
                    cout << "3. Display Books" << endl;
                    cout << "4. Student Details" << endl;
                    cout << "0. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cout << "\n";
                    cin >> adminChoice;
                    cout << "\n";

                    switch (adminChoice) {
                       case 1: {
    string title, author;
    int id;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);

    // Prompt the user to enter a valid author name without digits
    while (true) {
        cout << "Enter author: ";
        getline(cin, author);

        // Check if the author's name contains any digits
        bool containsDigits = false;
        for (char c : author) {
            if (isdigit(c)) {
                containsDigits = true;
                break;
            }
        }
        // If author name contains digits, prompt the user to enter again
        if (containsDigits) {
            cout << "Invalid author name. Please enter a valid author name without digits." << endl;
        } else {
            // Author name is valid, break out of the loop
            break;
        }
    }
    cout << "Enter book ID: ";
    while (!(cin >> id) || id <= 0) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Invalid book ID. Please enter a valid book ID: ";
    }
    library.addBook(title, author, id);
    break;
}
                        case 2: {
                            int bookId;
                            cout << "Enter book ID to delete: ";
                            while (!(cin >> bookId) || bookId <= 0) {
                                cin.clear();
                                while (cin.get() != '\n');
                                cout << "Invalid book ID. Please enter a valid book ID: ";
                            }
                            library.deleteBook(bookId);
                            break;
                        }
                        case 3: {
                            library.displayBooks();
                            break;
                        }
                        case 4: {
                            cout << "Student Details:" << endl;
                            Student* currentStudent = library.getStudentList();
                            if (!currentStudent) {
                                cout << "No student records available." << endl;
                            } else {
                                while (currentStudent) {
                                    if (currentStudent->returnTime == 0) {
                                        cout << "Student ID: " << currentStudent->studentId << " issued book: " << currentStudent->book << endl;
                                    } else {
                                        cout << "Student ID: " << currentStudent->studentId << " returned book: " << currentStudent->book << endl;
                                    }
                                    currentStudent = currentStudent->next;
                                }
                            }
                            break;
                        }
                        case 0:
                            adminLoggedIn = false;
                            break;
                        default:
                            cout << "Invalid choice. Please enter a valid option." << endl;
                            break;
                    }
                } while (adminChoice != 0);
                break;
            }

            case 2: {
                int studentChoice;
                do {
                    cout << "\nStudent Menu: \n";
                    cout << "1. Display Books" << endl;
                    cout << "2. Issue a Book" << endl;
                    cout << "3. Return a Book" << endl;
                    cout << "0. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> studentChoice;
                    cout << "\n";

                    switch (studentChoice) {
                        case 1: {
                            library.displayBooks();
                            break;
                        }
                        case 2: {
                            string studentName;
                            int studentId, bookId;
                            cout << "Enter your Name: ";
                            cin.ignore();
                            getline(cin, studentName);
                            cout << "Enter your student ID: ";
                            while (!(cin >> studentId) || studentId <= 0) {
                                cin.clear();
                                while (cin.get() != '\n');
                                cout << "Invalid student ID. Please enter a valid student ID : ";
                            }
                            cout << "Enter the book ID you want to issue: ";
                            while (!(cin >> bookId) || bookId <= 0) {
                                cin.clear();
                                while (cin.get() != '\n');
                                cout << "Invalid book ID. Please enter a valid book ID: ";
                            }
                            library.issueBook(studentName, studentId, bookId);
                            break;
                        }
                        case 3: {
                            int studentId;
                            cout << "Enter your student ID: ";
                            while (!(cin >> studentId) || studentId <= 0) {
                                cin.clear();
                                while (cin.get() != '\n');
                                cout << "Invalid student ID. Please enter a valid student ID: ";
                            }
                            library.returnBook(studentId);
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Invalid choice. Please enter a valid option." << endl;
                            break;
                    }
                } while (studentChoice != 0);
                break;
            }

            case 0:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 0);

    return 0;
}

