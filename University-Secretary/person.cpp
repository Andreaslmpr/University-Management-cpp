
#include "person.hpp"
#include "secretary.hpp" // Include Secretary for friend declaration
#include <iostream>
#include<cctype>

int Person::ConstructorCalls = 0; //Initialization

// An accessor to Constructor Calls
int Person::Get_ConstructorCalls(){
    return ConstructorCalls;
}

// Constructor
Person::Person(string name,string surname,string id ,int age ):name(name),surname(surname),id(id),age(age){
    ++ConstructorCalls;
    
}


Person::Person() : name(""), surname(""), id(""), age('0') {
   ++ConstructorCalls;
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


//Copy Constructor
Person::Person(const Person &other) {
  this->name = other.name;
  this->surname=other.surname;
  this->age = other.age;
  this->id =other.id;
}

Person::~Person(){
    ConstructorCalls--;
}

bool isValidName(const string& name){
    // Check each character in the name
    for (char ch : name) {
        // Check if the character is an alphabetical character or a space
        if (!isalpha(ch) && ch != ' ') {
            cout << "Invalid characters in the name: " << ch <<endl;
            return false;
        }
    }

    // Name is valid
    return true;
}


ostream& operator<<(ostream& output, const Person& person){
    output<<endl;
    output<<"------------------------------------------"<<endl;
    //if(person.role=='S'||person.role=='s') 
    //output<<"-------Student's Personal Info---------"<<endl;
    //else output<<"----Teacher's Personal Info----"<<endl;
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

    cout<<"-Insert the Name of the Person: ";
    if(!person.name.empty()) (person.name).clear(); //already existing name
    input>>person.name;
    //Wrong Input Check
    while(!isValidName(person.name)){
        cout<<"-Invalid User Input"<<endl;
        cout<<"-Insert the Name of the Person: ";
        input>>person.name;
    }
  

    cout<<"-Insert the Surname: ";
     if(!person.surname.empty()) (person.surname).clear(); //already existing name
    input>>person.surname;
     //Wrong Input Check
    while(!isValidName(person.surname)){
        cout<<"-Invalid User Input"<<endl;
        cout<<"-Insert the Surname of the Person: ";
        input>>person.surname;
    }

    cout<<"-Insert Age:  ";
    input>>person.age;
    while(person.age<=18 || person.age>=100){
        cout<<endl<<"Invalid Age...New Input Please: ";
        input>>person.age;
    }

    cout<<"-Insert the University ID: ";
     if(!person.id.empty()) (person.id).clear(); //already existing name
    input>>person.id;

    return input;

}


