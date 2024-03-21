//
//  person.cpp
//  Project 2
//
//  Created by Lawrence Degoma on 11/25/23.
//

#include "person.hpp"
#include <iostream>
using namespace std;


// Person class implementation
Person::Person(){}
Person::Person(int id, string name, int count){
    this->id = id;
    this->name = name;
    this->count = count;
}

// Getters
int Person::getId(){return id;}
string Person::getName(){return name;}
int Person::getCount(){return count;}
// Setters

void Person::setId(int id){this->id = id;}
void Person::setName(string name){this->name = name;}
void Person::setCount(int count){this->count = count;}


// Student child-class implementation
Student::Student(){}
Student::Student(int id, string name, int count, int* code) : Person(id, name, count){
    for (int i=0; i<count; i++)
        this->code[i] = code[i];
}

// Getter
int Student::getStudentCode(int i){return code[i];}

// Setter
// * need to add exception handling
void Student::setStudentCode(int code, int replaceIndex){
    this->code[replaceIndex] = code;
}


// Teacher child-class implementation
Teacher::Teacher(){}
Teacher::Teacher(int id, string name, int count, int* code) : Person(id, name, count){
    for (int i=0; i<count; i++)
        this->code[i] = code[i];
}
// Getter
int Teacher::getCode(int i){return code[i];}
// Setter
// * need to add exception handling to both
void Teacher::setTeacherCode(int code, int replaceIndex){
    this->code[replaceIndex] = code;
}
