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
    cout<<"-----------DATA BASE REMOTE ACCESS HAS BEEN LOST--------------(Destructor of Secretary)"<<endl;
    for (Person* person : database) {
        delete person; // Deallocate memory for each Person
    }
    database.clear();      

}
//Copy Constructor of a Secretary
Secretary::Secretary(const Secretary& original) {
     for (const Person* person : original.database) {
        this->database.push_back(new Person(*person)); // Using copy constructor to create a new Person
    }
}


// the ADD operand to add a person in the database vector of the SECRETARY
//this type* const indicates that the pointer will be constant and cannot point out somewhere else

void Secretary::operator+(Person* const person){  
    this->database.push_back(person);
}

    // Another version of ADD operand
void Secretary::operator+=( Person* const person) {
    this->database.push_back(person);
}

void Secretary::AddPerson(Person* const person) { //Adds person to the vector function
        *this+=person;
    }

// Operand <<
ostream& operator<<(ostream& output, const Secretary& base) {
    for (const Person* person : base.database) {
        output << *person; // Using operator<< to print each person
    }
    return output;
}

// Operand >>
istream& operator>>(istream& input, Secretary& base) {
    while (true) {
        Person* person = new Person();  // Allocate memory for a new Person
        if(!person){
           cout<<"Error in Memory Allocatrion"<<endl;
           exit(0);
        }

        input >> *person; // Calls the operator>> for Person to read the data
        base.database.push_back(person);

        // Check new membership
        cout <<endl << "You are a member of University. For new Enroll press Y and any other key for exit: ";
        char check;
        input >> check;
        check =toupper(check);
        if (check == 'Y') continue;
        else break;
    }

    return input;
}

// Checks if a Person is in the Secretary Vector
void Secretary::FindPerson(string Id) const {
    std::cout << "-------------UNIVERSITY MEMBERSHIPS-------------------";
    std::string targetId = Id;
    for (const Person* person : this->database) {
        if (person->Get_Id() == targetId) {
            cout <<endl;
            cout << "Your Person is : " <<endl;
            cout << *person; // Using operator<< to print the person
            return;
            
        }
         
        }
        
        cout << "University Member not Found...." <<endl;

   
}

// Assignment Operator Overload
void Secretary::operator=(const Secretary& newdatabase) {
    // Clear existing data
    for (Person* person : database) {
        delete person; // Deallocate memory for each Person
    }
    database.clear();

    // Copy new data
    for (const Person* person : newdatabase.database) {
        this->database.push_back(new Person(*person)); // Using copy constructor to create a new Person
        if(!person){
           cout<<"Error in Memory Allocatrion"<<endl;
           exit(0);
        }
    }
}


