// Lawrence Degoma
// Professor Ji Lee
// Project 2
// 12-14-23


// iostream library + class header files
#include <iostream>
#include "person.cpp"
#include "books.cpp"
#include "linkedLists.tpp"

// other c++ libraries: files, strings, ctime (for one of the exception handling), and algorithm for substring replacement
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <iomanip>
using namespace std;


// Function declarations:
// Linked list builders
personNodePtr createPersonList(ifstream&, personNodePtr&);
bookNodePtr createBookList(ifstream&, bookNodePtr&, bookNodePtr&);

// Other functions: error prompt, create objects for person or book, print info
void error();
template<class T>
void processPerson(ifstream&, personNodePtr&, personNodePtr&, int, int, T);
void processBook(ifstream&, bookNodePtr&, bookNodePtr&, int);
void printBook(bookNodePtr);
void findBookSubFunc(bookNodePtr*, int, int, const string&);
void findBook(bookNodePtr*, personNodePtr*);
void menu(bookNodePtr*, personNodePtr*);
void checkId(personNodePtr*, personNodePtr&, int, int, bool&);
void checkBook(bookNodePtr*, bookNodePtr&, int, int, bool&);
void rent(bookNodePtr*, personNodePtr*);
void returnBook(bookNodePtr*, personNodePtr*);
void showInfo(bookNodePtr*, personNodePtr*);




int main(){
    // prompt user to input book and names files
    string book, personFile;
    cout << "Enter book file: ";
    cin >> book;
    cout << "Enter person file: ";
    cin >> personFile;
    
    // infileOne will be for book.txt, infileTwo will be for person.txt
    ifstream infileOne, infileTwo;
    try{
        infileOne.open(book);
        if (infileOne.fail())
            throw book;
        infileTwo.open(personFile);
        if (infileTwo.fail())
            throw personFile;
    }
    // first exception handling
    catch(string fail){
        cout << fail << " not found. Try again? (Y/N) ";
        error();
    }
    
    // create linked lists for people
    personNodePtr teacher = NULL;
    personNodePtr student = createPersonList(infileTwo, teacher);
    personNodePtr person[2] = {teacher, student};
    
    
    // created linked lists for books
    bookNodePtr children_book = NULL;
    bookNodePtr computer_book = NULL;
    bookNodePtr novel = createBookList(infileOne, children_book, computer_book);
    bookNodePtr books[3] = {children_book, computer_book, novel};
    
    // open menu
    menu(books, person);
    return 0;
}




// This function prompts the user to try again after an error
void error(){
    char ans;
    cin >> ans;
    switch(ans){
        case('y'):
        case('Y'):{
            cout << endl;
            main();
        }
        case('n'):
        case('N'):{
            exit(1);
        }
        default:{
            cout << "Choice not valid. Exiting..." << endl;
            exit(1);
        }
    }
}


// This function organizes the data that will be assigned to either the student or teacher sub class
// After processing, the new node will be placed in ascending order of ID
template<class T>
void processPerson(ifstream& infile, personNodePtr& head, personNodePtr& ptr, int limit, int id, T){
    string name;
    int count, code[limit];
    // Exception handling to check if a person in the person txt file has more books already than they're allowed
    try{
        infile >> name >> count;
        if (count > limit)
            throw name;
    }
    catch (string name){
        cout << "Error! " << name << " has too many books!\n"
        << "Try again? (Y/N): ";
        error();
    }
    if (count == 0){
        string dummy;
        getline(infile, dummy);
    }
    else{
        for (int i=0; i<count; i++)
            infile >> code[i];
    }
    // Create linked list in order of ascending ID number
    Person* p = new T(id, name, count, code);
    ptr->setData(p);
    if (head == NULL || ptr->getData()->getId() < head->getData()->getId()){
        ptr->setLink(head);
        head = ptr;
    }
    else{
        personNodePtr temp = head;
        while (temp->getLink() && temp->getLink()->getData()->getId() < ptr->getData()->getId())
            temp = temp->getLink();
        ptr->setLink(temp->getLink());
        temp->setLink(ptr);
    }
}


personNodePtr createPersonList(ifstream& infile, personNodePtr& teacher){
    personNodePtr studentHead = NULL;
    while (!infile.eof()){
        int id = 0;
        infile >> id;
        personNodePtr ptr = new nodePerson;
        // create separate linked lists for teachers and students. Any other id gets thrown as an error
        try{
            if (id >= 1 && id <= 100){
                processPerson(infile, teacher, ptr, 3, id, Teacher());
            }
            else if (id >= 101 && id <= 300){
                processPerson(infile, studentHead, ptr, 2, id, Student());
            }
            else
                throw id;
        }
        catch(int fail){
            cout << "Error: unrecognized id: " << fail << "...\n";
            cout << "Try again with different files? (Y/N): ";
            error();
        }
    }
    return studentHead;
}


// This function does the same things as the createPersonList function but for the books
bookNodePtr createBookList(ifstream& infile, bookNodePtr& children_book, bookNodePtr& computer_book){
    bookNodePtr novel = NULL;
    while (!infile.eof()){
        int code = 0;
        infile >> code;
        bookNodePtr ptr = new nodeBook;
        // Distinguish the infile code as one of the three categories
        // Anything else gets thrown as an error
        try{
            if (code >= 1001 && code <= 2000){
                processBook(infile, children_book, ptr, code);
            }
            else if (code >= 2001 && code <= 3000){
                processBook(infile, computer_book, ptr, code);
            }
            else if (code >= 3001 && code <= 4000){
                bookNodePtr ptr = new nodeBook;
                processBook(infile, novel, ptr, code);
            }
            else
                throw code;
        }
        catch(int code){
            cout << "Error: unrecognized code: " << code << "...\n";
            cout << "Try again with different files? (Y/N): ";
            error();
        }
    }
    return novel;
}


// This function is similar in implementation to the processPerson function above
void processBook(ifstream& infile, bookNodePtr& head, bookNodePtr& ptr, int code){
    string title, publisher;
    int available=0, rented=0, age=0, publish_date=0;
    infile >> title;
    // Immediately get rid of the underscores in the ttle
    replace(title.begin(), title.end(), '_', ' ');
    if (code >= 1000 && code <= 2000){
        try{
            infile >> age >> available >> rented;
            if (available < 0)
                throw available;
            if (rented < 0)
                throw rented;
        }
        catch(int num){
            cout << "Error: invalid " << num << " books recorded.\n";
            cout << "Try again?: (Y/N)";
            error();
        }
    }
    else if (code >= 2001 && code <= 3000){
        try{
            infile >> publisher >> available >> rented;
            replace(publisher.begin(), publisher.end(), '-', ' ');
            if (available < 0)
                throw available;
            if (rented < 0)
                throw rented;
        }
        catch(int num){
            cout << "Error: invalid " << num << " books recorded.\n";
            cout << "Try again?: (Y/N)";
            error();
        }
    }
    else{
        try{
            infile >> publish_date >> available >> rented;
            if (available < 0)
                throw available;
            if (rented < 0)
                throw rented;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            // The line of code below checks to see if the publish date of the book is within current date
            if (publish_date > 1900 + ltm->tm_year || publish_date < 0)
                throw "fail";
        }
        catch(int num){
            cout << "Error: invalid " << num << " books recorded.\n";
            cout << "Try again?: (Y/N)";
            error();
        }
        catch(string fail){
            cout << "Error: invalid year (" << publish_date << ")\n";
            cout << "Try again?: (Y/N)";
        }
    }

    Book* b;
    if (code >= 1001 && code <= 2000)
        b = new ChildrenBook(code, title, age, available, rented);
    else if (code >= 2001 && code <= 3000)
        b = new ComputerBook(code, title, publisher, available, rented);
    else
        b = new Novel(code, title, publish_date, available, rented);

    ptr->setData(b);
    if (head == NULL || ptr->getData()->getCode() < head->getData()->getCode()){
        ptr->setLink(head);
        head = ptr;
    }
    else{
        bookNodePtr temp = head;
        while (temp->getLink() && temp->getLink()->getData()->getCode() < ptr->getData()->getCode())
            temp = temp->getLink();
        ptr->setLink(temp->getLink());
        temp->setLink(ptr);
    }
}


void printBook(bookNodePtr x){
    for (bookNodePtr ptr = x; ptr != nullptr; ptr = ptr->getLink()) {
        cout << std::setw(10) << std::left << ptr->getData()->getCode() << setw(30) << ptr->getData()->getTitle();

        if (ptr->getData()->getCode() >= 1000 && ptr->getData()->getCode() <= 2000) {
            cout << std::setw(5) << left << ptr->getData()->getAge();
        } else if (ptr->getData()->getCode() >= 2001 && ptr->getData()->getCode() <= 3000) {
            cout << setw(17) << left << ptr->getData()->getPublisher();
        } else {
            cout << setw(15) << left << ptr->getData()->getPublish_date();
        }

        cout << setw(10) << left << ptr->getData()->getAvailable() <<setw(7) << right
                  << ptr->getData()->getRented() << endl << endl;
    }
}


// This is a suplemental function to the findBook function for menu option 1
// All exception handling shuld be covered before this function is called
void findBookSubFunc(bookNodePtr* library, int index, int code, const string& title){
    bool found = false;
    
    for (bookNodePtr ptr = library[index]; ptr!=NULL; ptr=ptr->getLink()){
        if (code == ptr->getData()->getCode() && title == ptr->getData()->getTitle()){
            found = true;
            cout << title << "(" << code << ") exists.\n";

            if (index == 0)
                cout << "category : Children's book\n Age : " << ptr->getData()->getAge() << endl;
            else if (index == 1)
                cout << "category : Computer book\n Publisher : " << ptr->getData()->getPublisher() << endl;
            else if (index == 2)
                cout << "category : Novel\n Publish Date :  " << ptr->getData()->getPublish_date() << endl;
            cout << ptr->getData()->getAvailable() << " available, " << ptr->getData()->getRented() << " rented." << endl;
            break;
        }
        if (code == ptr->getData()->getCode() && title != ptr->getData()->getTitle())
            throw title;
        if (ptr->getData()->getCode() > code){
            throw code;
            break;
        }
    }

    if (!found)
        throw code;
}


void findBook(bookNodePtr* library, personNodePtr* people){
    int code;
    std::string title;
    cout << "Enter code  :  ";
    cin >> code;

    cout << "Enter title :  ";
    cin >> title;
    replace(title.begin(), title.end(), '_', ' ');
    
    cout << endl << endl;


    // bool found = false;
    try{
        if (code>=1001 && code<=2000){
            findBookSubFunc(library, 0, code, title);
        }
        else if (code>=2001 && code <= 3000){
            findBookSubFunc(library, 1, code, title);
        }
        else if (code >= 3001 && code <= 4000){
            findBookSubFunc(library, 2, code, title);
        }
        else
            throw code;
    }
    catch (int code){
        cout << "Error: code not recognized. Please try again" << endl << endl;
        menu(library, people);
    }
    catch (const string& title){
        cout << "Error: code does not match registered book name\n"
        << "You entered code, '" << code << "' and title '" << title << "'\n"
        << "Please try again. " << endl << endl;
        menu(library, people);
    }
    cout << endl;
}


void rent(bookNodePtr* library, personNodePtr* people){
    int id;
    cout << "Enter your id    : ";
    cin >> id;
    string title;
    bookNodePtr bookPtr = NULL;
    personNodePtr personPtr = NULL;
    cout << "Enter book title : ";
    cin >> title;
    replace(title.begin(), title.end(), '_', ' ');

    // Check if id and title are registered in the system
    // This part checks for the person's id
    bool foundId = false;
    if (id >= 1 && id <= 100)
        checkId(people, personPtr, 0, id, foundId);
    if (id >= 101 && id <= 300)
        checkId(people, personPtr, 1, id, foundId);
    try{
        if (foundId == false)
            throw foundId;
    }
    catch (bool found){
        cout << "Error, id: " << id << " not found. Returning to menu.\n" << endl;
        menu(library, people);
    }


    // This one checks for the book code
    bool foundBook = false;
    for (bookNodePtr ptr=library[0]; ptr!=NULL; ptr = ptr->getLink()){
        if (title == ptr->getData()->getTitle()){
            foundBook = true;
            bookPtr = ptr;
            break;
        }
    }
    for (bookNodePtr ptr=library[1]; ptr!=NULL; ptr = ptr->getLink()){
        if (title == ptr->getData()->getTitle()){
            foundBook = true;
            bookPtr = ptr;
            break;
        }
    }
    for (bookNodePtr ptr=library[2]; ptr!=NULL; ptr = ptr->getLink()){
        if (title == ptr->getData()->getTitle()){
            foundBook = true;
            bookPtr = ptr;
            break;
        }
    }
    try{
        if (foundBook == false)
            throw foundBook;
    }
    catch(bool foundBook){
        cout << "Error, book title: '" << title << "' (" << bookPtr->getData()->getCode() << ")not found. Returning to menu.\n" << endl;
        menu(library, people);
    }



    if (id >= 1 && id <= 100){
        for (personNodePtr ptr=people[0]; ptr!=NULL; ptr=ptr->getLink()){
            if (id == ptr->getData()->getId()){
                cout << "You are " << ptr->getData()->getName() << ". ";
                if (ptr->getData()->getCount() == 1)
                    cout << "You rented " << ptr->getData()->getCount() << " book." << endl;
                else
                    cout << "You rented " << ptr->getData()->getCount() << " books." << endl;
                cout << "Do you want to rent '" << title << "' (y/n)? ";
                char ans;
                cin >> ans;
                switch(ans){
                    case 'y':
                    case 'Y':{
                        if (bookPtr->getData()->getAvailable() == 0){
                            cout << "***** Rent failed. Book is unavailable! Please try again!\n" << endl;
                            menu(library, people);
                        }
                        else if (ptr->getData()->getCount() == 3){
                            cout << "***** Rent failed. Check your info!" << endl;
                            menu(library, people);
                        }
                        else{
                            ptr->getData()->setTeacherCode(bookPtr->getData()->getCode(), 3-(3-ptr->getData()->getCount()));
                            cout << "***** Rent succeed. Check your info!\n";
                            ptr->getData()->setCount(ptr->getData()->getCount()+1);
                            bookPtr->getData()->setAvailable(bookPtr->getData()->getAvailable()-1);
                            bookPtr->getData()->setRented(bookPtr->getData()->getRented()+1);
                            menu(library, people);
                        }
                    }
                    case 'n':
                    case 'N':{
                        cout << "Understood, returning to menu..." << endl;
                        menu(library, people);
                    }
                    default:{
                        cout << "Invalid choice, returning to menu..." << endl;
                        menu(library, people);
                    }
                }
                break;
            }
        }
    }
    else if (id >= 101 && id <= 300){
        for (personNodePtr ptr=people[1]; ptr!=NULL; ptr=ptr->getLink()){
            if (id == ptr->getData()->getId()){
                cout << "You are " << ptr->getData()->getName() << ". ";
                if (ptr->getData()->getCount() == 1)
                    cout << "You rented " << ptr->getData()->getCount() << " book." << endl;
                else
                    cout << "You rented " << ptr->getData()->getCount() << " books." << endl;
                cout << "Do you want to rent '" << title << "' (y/n)? ";
                char ans;
                cin >> ans;
                switch(ans){
                    case 'y':
                    case 'Y':{
                        if (bookPtr->getData()->getAvailable() == 0){
                            cout << "***** Rent failed. Book is unavailable! Please try again!\n" << endl;
                            menu(library, people);
                        }
                        else if (ptr->getData()->getCount() == 2){
                            cout << "***** Rent failed. Check your info!" << endl;
                            menu(library, people);
                        }
                        else{
                            ptr->getData()->setStudentCode(bookPtr->getData()->getCode(), 1-(1-ptr->getData()->getCount()));
                            cout << "***** Rent succeed. Check your info!\n";
                            ptr->getData()->setCount(ptr->getData()->getCount()+1);
                            bookPtr->getData()->setAvailable(bookPtr->getData()->getAvailable()-1);
                            bookPtr->getData()->setRented(bookPtr->getData()->getRented()+1);
                            menu(library, people);
                        }
                    }
                    case 'n':
                    case 'N':{
                        cout << "Understood, returning to menu..." << endl;
                        menu(library, people);
                    }
                    default:{
                        cout << "Invalid choice, returning to menu..." << endl;
                        menu(library, people);
                    }
                }
                break;
            }
        }
    }
}


// sub function checks student/teacher id
// manipulates bool value
void checkId(personNodePtr* people, personNodePtr& personPtr, int index, int id, bool& found){
    for (personNodePtr ptr=people[index]; ptr!=NULL; ptr=ptr->getLink()){
        if (id == ptr->getData()->getId()){
            found = true;
            personPtr = ptr;
            break;
        }
        if (ptr->getData()->getId() > id)
            break;
    }
}


// sub function checks book code
// manipulates bool value
void checkBook(bookNodePtr* library, bookNodePtr& bookPtr, int index, int code, bool& found){
    for (bookNodePtr ptr=library[index]; ptr!=NULL; ptr = ptr->getLink()){
        if (code == ptr->getData()->getCode()){
            found = true;
            bookPtr = ptr;
            break;
        }
        if (ptr->getData()->getCode() > code)
            break;
    }
}


// Menu option 3: Return book
// Uses params of library arrary and people array
void returnBook(bookNodePtr* library, personNodePtr* people){
    int id, code=0;
    cout << "Enter your id    : ";
    cin >> id;
    bookNodePtr bookPtr = NULL;
    personNodePtr personPtr = NULL;
    cout << "Enter book code : ";
    cin >> code;

    // Check if id and title are registered in the system
    bool foundId = false;
    if (id >= 1 && id <= 100)
        checkId(people, personPtr, 0, id, foundId);
    else if (id >= 101 && id <= 300)
        checkId(people, personPtr, 1, id, foundId);

    // Exception handling to see if the person id is recognized
    try{
        if (foundId == false)
            throw foundId;
    }
    catch (bool found){
        cout << "Error, id: " << id << " not found. Returning to menu.\n" << endl;
        menu(library, people);
    }


    // Check if book exists
    bool foundBook = false;
    if (code >= 1001 && code <= 2000)
        checkBook(library, bookPtr, 0, code, foundBook);
    else if (code >= 2001 && code <= 3000)
        checkBook(library, bookPtr, 1, code, foundBook);
    else if (code >= 3001 && code <= 4000)
        checkBook(library, bookPtr, 2, code, foundBook);

    // Exception handling for an unrecognized book
    try{
        if (foundBook == false)
            throw foundBook;
    }
    catch(bool foundBook){
        cout << "Error, book title: " << bookPtr->getData()->getTitle() << " not found. Returning to menu.\n" << endl;
        menu(library, people);
    }

    // Exception handling for a person not having rented any books
    try{
        if (personPtr->getData()->getCount() == 0)
            throw personPtr->getData()->getCount();
    }
    catch (int count){
        cout << "Error, id: " << personPtr->getData()->getId() << " does not have any books rented.\n"
        << "returning to menu...\n" << endl;
        menu(library, people);
    }

    // Check if the person rented the book
    try{
        bool rented = false;
        if (personPtr->getData()->getId() >= 1 && personPtr->getData()->getId() <= 100){
            for (int i=0; i<personPtr->getData()->getCount(); i++){
                if (bookPtr->getData()->getCode() == personPtr->getData()->getCode(i)){
                    rented = true;
                    break;
                }
            }
        }
        else if (personPtr->getData()->getId() >= 101 && personPtr->getData()->getId() <= 300){
            for (int i=0; i<personPtr->getData()->getCount(); i++){
                if (bookPtr->getData()->getCode() == personPtr->getData()->getStudentCode(i)){
                    rented = true;
                    break;
                }
            }
        }
        if (rented == false)
            throw rented;
    }
    catch(bool rented){
        cout << "Id: " << personPtr->getData()->getId() << " name: " << personPtr->getData()->getName() << " has not rented book code: " << code << ".\n"
        << "Returning to menu...\n" << endl;
        menu(library, people);
    }

    char ans;
    cout << "Do you want to return '" << bookPtr->getData()->getTitle() << "' (y/n)? ";
    cin >> ans;
    switch(ans){
        case 'n':
        case 'N':{
            cout << "Understood, returning to menu...\n" << endl;
            menu(library, people);
        }
        case 'y':
        case 'Y':{
            break;
        }
        default:{
            cout << "Option not recognized. Returning to menu...\n" << endl;
            menu(library, people);
        }
    }

    if (personPtr->getData()->getId() >= 1 && personPtr->getData()->getId() <= 100){
        for (int i=0; i<personPtr->getData()->getCount(); i++){
            if (bookPtr->getData()->getCode() == personPtr->getData()->getCode(i)){
                personPtr->getData()->setTeacherCode('\0', i);
                personPtr->getData()->setCount(personPtr->getData()->getCount() - 1);
                bookPtr->getData()->setAvailable(bookPtr->getData()->getAvailable() + 1);
                bookPtr->getData()->setRented(bookPtr->getData()->getRented() - 1);
            }
        }
    }
    else if (personPtr->getData()->getId() >= 101 && personPtr->getData()->getId() <= 300){
        for (int i=0; i<personPtr->getData()->getCount(); i++){
            if (bookPtr->getData()->getCode() == personPtr->getData()->getStudentCode(i)){
                personPtr->getData()->setStudentCode('\0', i);
                personPtr->getData()->setCount(personPtr->getData()->getCount() - 1);
                bookPtr->getData()->setAvailable(bookPtr->getData()->getAvailable() + 1);
                bookPtr->getData()->setRented(bookPtr->getData()->getRented() - 1);
            }
        }
    }

    cout << "***** Return succeed. Check your info!\n" << endl;
    menu(library, people);
}


void showInfo(bookNodePtr* library, personNodePtr* people){
    int id;
    string name;
    cout << "Enter your id    : ";
    cin >> id;
    cout << "Enter your name  : ";
    cin >> name;

    personNodePtr personPtr = NULL;
    bool match = false;
    bool foundId = false;
    try{
        if (id >= 1 && id <= 100){
            for (personNodePtr ptr = people[0]; ptr!=NULL; ptr = ptr->getLink()){
                if (id == ptr->getData()->getId()){
                    foundId = true;
                    if (name == ptr->getData()->getName()){
                        match = true;
                        personPtr = ptr;
                    }
                }
            }
        }
        else if (id >= 101 && id <= 300){
            for (personNodePtr ptr = people[1]; ptr!=NULL; ptr = ptr->getLink()){
                if (id == ptr->getData()->getId()){
                    foundId = true;
                    if (name == ptr->getData()->getName()){
                        match = true;
                        personPtr = ptr;
                    }
                }
            }
        }
        if (match == false)
            throw match;
        if (foundId == false)
            throw id;
    }
    catch (bool match){
        cout << "Error, name and id do not match. Please try again.\n" << endl;
        menu(library, people);
    }
    catch (int id){
        cout << "Error, id not found. Please try again.\n" << endl;
        menu(library, people);
    }

    if (personPtr->getData()->getCount() == 1)
        cout << "You rented " << personPtr->getData()->getCount() << " book.\n";
    else
        cout << "You rented " << personPtr->getData()->getCount() << " books.\n";
    if (personPtr->getData()->getId() >= 1 && personPtr->getData()->getId() <= 100){
        for (int i=0; i < personPtr->getData()->getCount(); i++){
            if (personPtr->getData()->getCode(i) >= 1001 && personPtr->getData()->getCode(i) <= 2000){
                for (bookNodePtr ptr = library[0]; ptr!=NULL; ptr=ptr->getLink()){
                    if (personPtr->getData()->getCode(i) == ptr->getData()->getCode()){
                        cout << "* " << ptr->getData()->getTitle() << "(" << ptr->getData()->getCode() << ")" << " - age " << ptr->getData()->getAge() << endl;
                    }
                }
            }
            else if (personPtr->getData()->getCode(i) >= 1001 && personPtr->getData()->getCode(i) <= 2000){
                for (bookNodePtr ptr = library[1]; ptr!=NULL; ptr=ptr->getLink()){
                    if (personPtr->getData()->getCode(i) == ptr->getData()->getCode()){
                        cout << "* " << ptr->getData()->getTitle() << "(" << ptr->getData()->getCode() << ")" << " - publisher " << ptr->getData()->getPublisher() << endl;
                    }
                }

            }
            else if (personPtr->getData()->getCode(i) >= 1001 && personPtr->getData()->getCode(i) <= 2000){
                for (bookNodePtr ptr = library[2]; ptr!=NULL; ptr=ptr->getLink()){
                    if (personPtr->getData()->getCode(i) == ptr->getData()->getCode()){
                        cout << "* " << ptr->getData()->getTitle() << "(" << ptr->getData()->getCode() << ")" << " - publish date " << ptr->getData()->getPublish_date() << endl;
                    }
                }
            }
        }
        menu(library, people);
    }
    else if (personPtr->getData()->getId() >= 101 && personPtr->getData()->getId() <= 300){
        for (int i=0; i < personPtr->getData()->getCount(); i++){
            if (personPtr->getData()->getStudentCode(i) >= 1001 && personPtr->getData()->getStudentCode(i) <= 2000){
                for (bookNodePtr ptr = library[0]; ptr!=NULL; ptr=ptr->getLink()){
                    if (personPtr->getData()->getStudentCode(i) == ptr->getData()->getCode()){
                        cout << "* " << ptr->getData()->getTitle() << "(" << ptr->getData()->getCode() << ")" << " - age " << ptr->getData()->getAge() << endl;
                    }
                }
            }
            else if (personPtr->getData()->getStudentCode(i) >= 2001 && personPtr->getData()->getStudentCode(i) <= 3000){
                for (bookNodePtr ptr = library[1]; ptr!=NULL; ptr=ptr->getLink()){
                    if (personPtr->getData()->getStudentCode(i) == ptr->getData()->getCode()){
                        cout << "* " << ptr->getData()->getTitle() << "(" << ptr->getData()->getCode() << ")" << " - publisher " << ptr->getData()->getPublisher() << endl;
                    }
                }

            }
            else if (personPtr->getData()->getStudentCode(i) >= 3001 && personPtr->getData()->getStudentCode(i) <= 4000){
                for (bookNodePtr ptr = library[2]; ptr!=NULL; ptr=ptr->getLink()){
                    if (personPtr->getData()->getStudentCode(i) == ptr->getData()->getCode()){
                        cout << "* " << ptr->getData()->getTitle() << "(" << ptr->getData()->getCode() << ")" << " - publish date " << ptr->getData()->getPublish_date() << endl;
                    }
                }
            }
        }
    }
    menu(library, people);
}


// This is the menu function that all the previous functions will be calling when they need to return to a screen
void menu(bookNodePtr* library, personNodePtr* people){
    int choice;
    cout << "=========================================" << endl;
    cout << "                   Menu" << endl;
    cout << "=========================================" << endl;
    cout << setw(3) << "1." << setw(3) << "Search a book" << endl;
    cout << setw(3) << "2." << setw(3) << "Rent a book" << endl;
    cout << setw(3) << "3." << setw(3) << "Return a book" << endl;
    cout << setw(3) << "4." << setw(3) << "Show my information" << endl;
    cout << setw(3) << "5." << setw(3) << "Show all books" << endl;
    cout << setw(3) << "6." << setw(3) << "Exit" << endl;
    cout << setw(3) << "Select (1~6): ";
    cin >> choice;
    cout << endl << endl;

    switch (choice){
        case 1:{
            findBook(library, people);
            menu(library, people);
        }
        case 2:{
            rent(library, people);
            break;
        }
        case 3:{
            returnBook(library, people);
            break;
        }
        case 4:{
            showInfo(library, people);
            break;
        }
        case 5:{
            for (int i=0; i<=65; i++)
                cout << "=";
            cout << endl;
            for (int i=0; i<=23; i++)
                cout << " ";
            cout << "Children Books" << endl;
            for (int i=0; i<=65; i++)
                cout << "=";
            cout << endl;
            cout << setw(10) << left << "code" << setw(30) << "title" << setw(5) << left << "age" << 
            setw(10) << left << "available"  << setw(7) << right << "rented" << endl;
            for (int i=0; i<=65; i++)
                cout << "-";
            cout << endl;
            printBook(library[0]);
            
            for (int i=0; i<=70; i++)
                cout << "=";
            cout << endl;
            for (int i=0; i<26; i++)
                cout << " ";
            cout << "Computer Books" << endl;
            for (int i=0; i<=70; i++)
                cout << "=";
            cout << endl;
            cout << setw(10) << left << "code" << setw(25) << "title" << setw(17) << left << "publisher" <<
            setw(10) << left << "available"  << setw(7) << right << "rented" << endl;
            for (int i=0; i<=70; i++)
                cout << "-";
            cout << endl;
            printBook(library[1]);
            
            for (int i=0; i<=65; i++)
                cout << "=";
            cout << endl;
            for (int i=0; i<=29; i++)
                cout << " ";
            cout << "novels" << endl;
            for (int i=0; i<=65; i++)
                cout << "=";
            cout << endl;
            cout << setw(10) << left << "code" << setw(20) << "title" << setw(15) << left << "publish date" <<
            setw(10) << left << "available"  << setw(7) << right << "rented" << endl;
            for (int i=0; i<=65; i++)
                cout << "-";
            cout << endl;
            printBook(library[2]);
            menu(library, people);
        }
        case 6:{
            // Little extra with allowing the user to reset the entire program with other txt files
            char ans;
            cout << "Try again with different files? (Y/N): ";
            cin >> ans;
            if (ans == 'y' || ans == 'Y'){
                cout << endl << endl << endl << endl;
                main();
            }
            else if (ans == 'n' || ans == 'N'){
                cout << "Have a nice day." << endl;
                exit(0);
            }
            else{
                cout << "Invalid choice. Program ending" << endl << "Have a nice day" << endl;
                exit (0);
            }
            cout << "Exiting..." << endl;
            break;
        }
        default:{
            cout << "Invalid choice, exiting..." << endl;
            break;
        }
    }
}
