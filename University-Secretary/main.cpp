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
    if(check == 'Y'){
        Secretary secretary;
        // Input Secretary information
        cin >> secretary;
        // Input information for multiple persons
        cout<<endl<<"Insertion of a Single Person was Demonstrated , Following up for multiple in a While Loop"<<endl;
        while(check == 'Y'){
            Person person;
            cin >> person;
            secretary+=person;
            cout << "Press Y to add another person or any other key to exit enrollment: ";
            cin >> check;
            check = toupper(check); 
        }
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
            cout << "Press F to find another Person or any other key to terminate the program: ";
            cin >> check;
            check = toupper(check);
        } while (check == 'F');
    }
        cout << "Program terminated successfully!\n";
    return 0;
}