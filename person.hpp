//
//  person.hpp
//  Project 2
//
//  Created by Lawrence Degoma on 11/25/23.
//

#ifndef person_hpp
#define person_hpp

#include <stdio.h>
#include <iostream>
using namespace std;


class Person{
public:
    // Constructors:
    Person();
    Person(int, string, int);
    
    // Method Declarations:
    // Other classes will follow this format
    int getId();
    string getName();
    int getCount();
    
    void setId(int);
    void setName(string);
    void setCount(int);
    
    // Virtual Functions:
    virtual int getCode(int) = 0;
    virtual int getStudentCode(int) = 0;
    virtual void setStudentCode(int, int) = 0;
    virtual void setTeacherCode(int, int) = 0;
private:
    int id;
    string name;
    int count;
};


class Student : public Person{
public:
    Student();
    Student(int, string, int, int*);
    
    void setStudentCode(int, int) override;
    int getStudentCode(int) override;
    
    virtual int getCode(int){return 0;}
    virtual void setTeacherCode(int, int){}
private:
    int code[2];
};


class Teacher : public Person{
public:
    Teacher();
    Teacher(int, string, int, int*);
    
    void setTeacherCode(int, int) override;
    int getCode(int) override;
    
    virtual int getStudentCode(int){return 0;}
    virtual void setStudentCode(int, int){}
private:
    int code[3];
};
#endif /* person_hpp */
