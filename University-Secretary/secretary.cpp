//An Implementation for the Secreatry Data base by using Vector
#include"secretary.hpp"
#include"person.hpp"
#include<iostream>
#include<cstring>

//Constructor of a Secretary
Secretary::Secretary(){
    cout<<"------------UNIVERSITY DATA BASE REMOTE ACCESS-------------(Constructor of Secretary)"<<endl;
}

//Destructor of a Secretary
Secretary::~Secretary(){
    cout<<"-----------DATA BASE REMOTE ACCESSED HAS BEEN LOST--------------(Destructor of Secretary)"<<endl;
    this->database.clear();      

}
//Copy Constructor of a Secretary
Secretary::Secretary(const Secretary& original) {
    for (const Person& person : original.database) {
        this->database.push_back(person); // Using push_back to add a copy of each person
    }
}


// the ADD operand to add a person in the database vector of the SECRETARY
void Secretary::operator+(const Person& person){
    (this->database).push_back(person);
}

//Another version of ADD operand
void Secretary::operator+=(const Person& person) {
            this->database.push_back(person);
}

//operand<<
ostream& operator<<(ostream& output, const Secretary& base){
        for (const Person& person : base.database) {
            output<<person;
        }
        return output;     
}

//operand >>
istream& operator>>(istream& input, Secretary& base) {
    while (true) {
        Person person;
        input >> person; // Calls the operator>> for Person to read the data
        (base.database).push_back(person);  // Using the copy constructor

        // Check new membership
        cout <<endl<< "You are a member of University. For new Enroll press Y and any other key for exit: ";
        char check;
        input >> check;
        check=toupper(check);
        if(check=='Y')continue;
        else break;
    }

    return input;
}

//Checks if a Person is in the Secretary Vector
bool Secretary::FindPerson(string Id)const{
    cout<<"-------------UNIVERSITY MEMBERSHIPS-------------------";
    string targetId=Id;
    for(const Person& person : this->database ){
        if(person.Get_Id()==targetId){
            cout<<endl;
            cout<<"Your Person is : "<<endl;
            cout<<person;
            return true;
        }
    }
    cout<<"University Member not Found...."<<endl;
    return false;
}

 void Secretary::operator=(const Secretary& newdatabase) { //Assignment Operator Overload
            this->database = newdatabase.database; //Move new University to original University
        }