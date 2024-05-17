#include <bits/stdc++.h>
using namespace std;

/*
Architecture:-
                         -------------LMS----------------
                        /                                \     
                (has a)/                                  \  (has a)            
            UserManagement                          BookManagement
                |                                           \
                | (has user to manage)                       \ (has a)
              User       /   \                             Book & Bookdetails
                        /     \   (is a)--->inheritence     
                   Librarian  Member  


-->Librarian has Members to manage

--> Members has BookDetails to Seach approprite book and borrowing it.

*/

// Book class definition
map<pair<string, int>, vector<string>> Bookdatabase;   //{name,id}--->booknames


class Book {   //contains book
public:
    int identificationno;
    string ISBN;
    string title;
    string subject;
    string publisher;
    string language;
    string author;

    Book(int identificationno, string ISBN, string title, string subject, string publisher, string language, string author)
        : identificationno(identificationno), ISBN(ISBN), title(title), subject(subject), publisher(publisher), language(language), author(author) {}

    string getTitle() { return title; }
    string getISBN() { return ISBN; }
    string getSubject() { return subject; }
    string getPublisher() { return publisher; }
    string getLanguage() { return language; }
};

// BookDetails class definition
class BookDetails {
public:
    string barcode;
    string status;
    int price;
    bool available;
    int rack;

    BookDetails(string barcode, string status, int price, bool available, int rack )
        : barcode(barcode), status(status), price(price), available(available), rack(rack)  {}

    bool isAvailable() { return available; }
    void setAvailable(bool status) { available = status; }

    string getBarcode() { return barcode; }
    string getStatus() { return status; }
    void setStatus(string& s) { status = s; }
};

// User class definition
class User {
public:
    string email;
    int id;
    string name;
    string barcode;
    string password;

    User() {}
    User(string email, int id, string name, string barcode, string password)
        : email(email), id(id), name(name), barcode(barcode), password(password) {}

    string getname() { return name; }  //get username
    int getId() { return id; }      //get userid
};

// UserManagementSystem class definition
class UserManagementSystem {
private:
    vector<User> users;    //to store all the users 

public:
    void addUser(User& user) {  //to add user
        users.push_back(user);
    }

    void removeUser(int id) {   //to remove user
        users.erase(remove_if(users.begin(), users.end(), [id](User& u) { return u.getId() == id; }), users.end());
    }

    User getUserById(int id) {   //to getuser by their id
        for (auto& user : users) {
            if (user.getId() == id) {
                return user;
            }
        }
        throw runtime_error("User not found");
    }

    vector<User> getAllUsers() {  // to get details of all the users
        return users;
    }
};

// Member class definition
class Member : public User {

public:
   
    Member(string email, int id, string name, string barcode, string password)
        : User(email, id, name, barcode, password) {}

    string getbarcode() {   //to get barcode of member
        return barcode;
    }

    string getemail() {  // to get email of member
        return email;
    }

    int getid() {
        return id;
    }

    void borrowabook(string Bookname, string myName, int myId) {
        if (Bookdatabase[{myName,id}].size() >= 5) {
            cout << "You Can't check out the book";
        } else {
            Bookdatabase[{myName,myId}].push_back(Bookname);
            string statusname = "Borrowed";
            cout << "Book has been Borrowed" << endl;
        }
    }
 
};

// BookManagement class definition
class BookManagement {
private:
    Book b1; 
    vector<Book> books;
    unordered_map<int, vector<BookDetails>> bookDetails;

public:
    void addBook(Book& book) {
        books.push_back(book);
    }

    void addBookDetails(BookDetails& bookDetail) {
        bookDetails[bookDetail.b.identificationno].push_back(bookDetail);
    }

    vector<Book> searchByTitle( string& title) {
        vector<Book> result;
        for (auto& book : books) {
            if (book.title == title) {
                result.push_back(book);
            }
        }
        return result;
    }

    vector<Book> searchByAuthor( string& author) {
        vector<Book> result;
        for (auto& book : books) {
            if (book.author == author) {
                result.push_back(book);
            }
        }
        return result;
    }

    vector<Book> searchBySubject( string& subject) {
        vector<Book> result;
        for (auto& book : books) {
            if (book.subject == subject) {
                result.push_back(book);
            }
        }
        return result;
    }
};

// Librarian class definition
class Librarian : public User {
public:
    set<Member> TotalMember;

    Librarian(string email, int id, string name, string barcode, string password)
        : User(email, id, name, barcode, password) {}

    void addamember(Member& m) {
        TotalMember.insert(m);
    }

    void deleteamember(Member& b) {
        TotalMember.erase(m);
    }
};

// LMS class definition
class LMS {
private:
    UserManagementSystem userManagement;
    BookManagement bookManagement;

public:
    LMS() {}

    UserManagementSystem& getUserManagementSystem() { //returns a reference to the UserManagement object 
        return userManagement;
    }

    BookManagement& getBookManagement() { //returns a reference to the BookManagement object
        return bookManagement;
    }
};

// Main function
int main() {

    lms.getUserManagementSystem.addUser();
    lms.getBookManagement().addBook(b);
    cout<<lms.getBookManagement.getName()<<endl;

    return 0;
}
