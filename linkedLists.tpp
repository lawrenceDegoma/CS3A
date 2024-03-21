//
//  linkedLists.cpp
//  Project 2
//
//  Created by Lawrence Degoma on 12/4/23.
//

#include <stdio.h>
#include "person.hpp"
#include "books.hpp"
#include <iostream>
using namespace std;

template<typename T>
class node{
private:
    T* m_data;
    node* m_link;
public:
    node(){
        m_data = 0;
        m_link = NULL;
    }
    node(T* data){
        this->data = data;
        this->link = NULL;
    }
    
    void setData(T* data){m_data = data;}
    void setLink(node* link){m_link = link;}
    T* getData(){return m_data;}
    class node* getLink(){return m_link;}
};

using nodePerson = node<Person>;
using nodeBook = node<Book>;

typedef class node<Person>* personNodePtr;
typedef class node<Book>* bookNodePtr;
