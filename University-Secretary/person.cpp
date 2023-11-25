
#include "person.hpp"
#include "secretary.hpp" // Include Secretary for friend declaration
#include <iostream>

int Person::ConstructorCalls = 0; //Initialization

// An accessor to Constructor Calls
int Person::Get_ConstructorCalls(){
    return ConstructorCalls;
}

//Constructor
Person::Person(){               //Initialize personal Info as NULL strings//
    ConstructorCalls++;
    name="";
    surname="";
    id="";
    role='\0';
    age=0;
}

//Accessors

int Person::Get_Age()const{
    return this->age;
}

string Person::Get_Name()const{
    return this->name;
}

string Person::Get_Surname()const{
    return this->surname;
}

string Person::Get_Id()const{
    return this->id;
}

char Person::Get_Role()const{
    return this->role;
}

//Copy Constructor
Person::Person(const Person &other) {
  this->name = other.name;
  this->surname=other.surname;
  this->age = other.age;
  this->id =other.id;
  this->role=other.role;
}

Person::~Person(){
    ConstructorCalls--;
}


ostream& operator<<(ostream& output, const Person& person){
    output<<endl;
    output<<"------------------------------------------"<<endl;
    if(person.role=='S'||person.role=='s')
    output<<"-------Student's Personal Info---------"<<endl;
    else output<<"----Teacher's Personal Info----"<<endl;
    output<<"-Name: ";
    output <<person.name<<endl;
    output<<"-Surname: ";
    output<<person.surname<<endl;
    output<<"-Age: ";
    output<<person.age<<endl;
    output<<"-ID: ";
    output<<person.id<<endl;  
    return output;
}

istream& operator>>(istream& input, Person& person){
    cout<<endl<<"------------------------UNIVERSITY DATA BASE---------------------------(input stream person)"<<endl;
    cout<<"Insert S for Student Enroll or T for Teacher Register:";

    input >>person.role;
    person.role=toupper(person.role);
    while(person.role!='S'&&  person.role!='T'){
        cout<<"-Invalid User Input-"<<endl;
        cout<<"Please, Insert S for Student Enroll or T for Teacher Register ";
        input>>person.role; 
    }

    cout<<"-Insert the Name of the Person: ";
    if(!person.name.empty()) (person.name).clear(); //already existing name
    input>>person.name;

    cout<<"-Insert the Surname: ";
     if(!person.surname.empty()) (person.surname).clear(); //already existing name
    input>>person.surname;

    cout<<"-Insert Age:  ";
    input>>person.age;

    cout<<"-Insert the University ID: ";
     if(!person.id.empty()) (person.id).clear(); //already existing name
    input>>person.id;

    return input;

}
