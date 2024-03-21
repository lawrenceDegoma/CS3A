//
//  books.hpp
//  Project 2
//
//  Created by Lawrence Degoma on 11/25/23.
//

#ifndef books_hpp
#define books_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

class Book{
public:
    Book();
    Book(int, string, int, int);
    
    int getCode();
    string getTitle();
    int getAvailable();
    int getRented();
    
    void setCode(int);
    void setTitle(string);
    void setAvailable(int);
    void setRented(int);
    
    virtual int getAge() = 0;
    virtual string getPublisher() = 0;
    virtual int getPublish_date() = 0;
    
private:
    int code;
    string title;
    int available;
    int rented;
};


class ChildrenBook : public Book{
public:
    ChildrenBook();
    ChildrenBook(int, string, int, int, int);
    
    void setAge(int);
    int getAge() override;
    
    virtual string getPublisher(){return 0;}
    virtual int getPublish_date(){return 0;}
private:
    int age;
};

class ComputerBook : public Book{
public:
    ComputerBook();
    ComputerBook(int, string, string, int, int);
    string getPublisher() override;
    void setPublisher(string);
    
    virtual int getAge(){return 0;}
    virtual int getPublish_date(){return 0;}
private:
    string publisher;
};


class Novel : public Book{
public:
    Novel();
    Novel(int, string, int, int, int);
    int getPublish_date() override;
    void setPublish_date(int);
    
    virtual int getAge(){return 0;}
    virtual string getPublisher(){return 0;}
private:
    int publish_date;
};

#endif /* books_hpp */
