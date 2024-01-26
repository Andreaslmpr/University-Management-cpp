#ifndef MY_PERSON_HPP
#define MY_PERSON_HPP  //for avoiding multiple compilation


#include<iostream>
#include<ostream>
#include<vector>
#include<string>
using namespace std;

class Secretary; // forward declaration

class Person{
protected:
    string name;
    string surname;
    string id;
    int age;
    friend class Secretary;
    
public:
    static int ConstructorCalls;
    Person(string name,string surname,string id ,int age);//constructor initialization list
    Person();//default
    ~Person(); //destructor
    Person(const Person &other);//copy constructor
    //Accessors
    int Get_Age()const;
    string Get_Name()const;
    string Get_Surname()const;
    string Get_Id()const;

    static int Get_ConstructorCalls();//Counter Constructor Calls

    friend istream& operator>>(istream& input, Person& person);
    friend ostream& operator<<(ostream& output, const Person& person);
    friend ostream& operator<<(ostream& output, const vector<Person>& base);
    friend istream& operator>>(istream& input, vector<Person>& base);
    bool isValidName(const string& name);

};

bool isValidName(const string& name);


#endif //PERSON_HPP