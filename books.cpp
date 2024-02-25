//
//  books.cpp
//  Project 2
//
//  Created by Lawrence Degoma on 11/25/23.
//

#include "books.hpp"
#include <iostream>
using namespace std;


// Book class implementation
// Constructors
Book::Book(){}
Book::Book(int code, string title, int available, int rented){
    this->code = code;
    this->title = title;
    this->available = available;
    this->rented = rented;
}

// Getters
int Book::getCode(){return code;}
string Book::getTitle(){return title;}
int Book::getAvailable(){return available;}
int Book::getRented(){return rented;}

// Setters
void Book::setCode(int code){this->code = code;}
void Book::setTitle(string title){this->title = title;}
void Book::setAvailable(int available){this->available = available;}
void Book::setRented(int rented){this->rented = rented;}



// ChildrenBook class implementation
// Constructors
ChildrenBook::ChildrenBook(){}
ChildrenBook::ChildrenBook(int code, string title, int age, int available, int rented) : Book(code, title, available, rented){
    this->age = age;
}

// Getter
int ChildrenBook::getAge(){return age;}

// Setter
void ChildrenBook::setAge(int age){this->age = age;}



// ComputerBook class implementation
// Constructors
ComputerBook::ComputerBook(){}
ComputerBook::ComputerBook(int code, string title, string publisher, int available, int rented) : Book(code, title, available, rented){
    this->publisher = publisher;
}

// Getter
string ComputerBook::getPublisher(){return publisher;}

// Setter
void ComputerBook::setPublisher(string publisher){this->publisher = publisher;}




// Novel class implementation
// Constructos
Novel::Novel(){}
Novel::Novel(int code, string title, int publish_date, int available, int rented) : Book(code, title, available, rented){
    this->publish_date = publish_date;
}

// Getter
int Novel::getPublish_date(){return publish_date;}

// Setter
void Novel::setPublish_date(int publish_date){
    this->publish_date = publish_date;
}
