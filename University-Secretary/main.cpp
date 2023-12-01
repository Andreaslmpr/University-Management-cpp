#include<iostream>
#include"person.hpp"
#include "secretary.hpp"
using namespace std;

//Main demonstration of the usage of Secretary and Person


int main() {
    cout << "--------------WELCOME TO THE DEPARTMENT OF INFORMATICS AND TELECOMS OF ATHENS---------------"<<endl<<endl;
    char check;
    cout << "Do you want to enroll persons in the University?(Press Y to continue or any other key to terminate program)\n";
    cin >> check;
    check=toupper(check);
   
        Secretary secretary;
        // Input Secretary information
            cin >> secretary;

        // Display Secretary and University information
        cout << ".............................."<<endl;
        cout <<endl<< "Secretary Information:"<<endl;
        cout << secretary;
        cout << ".............................."<<endl;

       cout<<endl<<"Constructor Calls are: "<<Person::Get_ConstructorCalls();

        // Search for a person by ID
        do {
            cout << ".............................."<<endl;;
            string searchID;
            cout << "Enter the ID to search for a person: ";
            cin >> searchID;
            secretary.FindPerson(searchID);       
            cout << "To find another Person insert Y or any other key to terminate the program: ";
            cin >> check;
            check = toupper(check);
        } while (check == 'Y');


//Print by copy constructor
//NOTE :
//BECAUSE IS CALLED BY COPY CONSTRUCTOR WE MANAGED IT(BY DEFAULT)TO NOT COUNT AS NEW PERSONS!!!!
        cout<<endl<<"Now will be another print of the copy constructor in a new Secretary database"<<endl;
        Secretary copy(secretary);
        cout<<copy;

        cout << "Demo Main terminated successfully!\n";
    return 0;
    }