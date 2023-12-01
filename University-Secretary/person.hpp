#ifndef MY_PERSON_HPP
#define MY_PERSON_HPP  //for avoiding multiple compilation


#include<iostream>
#include<ostream>
#include<vector>
#include<string>
using namespace std;

class Secretary; // forward declaration

class Person{
private:
    string name;
    string surname;
    string id;
    int age;
    char role;
    friend class Secretary;
    
public:
    static int ConstructorCalls;
    Person();//constructor
    ~Person(); //destructor
    Person(const Person &other);//copy constructor
    //Accessors
    int Get_Age()const;
    string Get_Name()const;
    string Get_Surname()const;
    char Get_Role()const;
    string Get_Id()const;

    static int Get_ConstructorCalls();//Counter Constructor Calls

    friend istream& operator>>(istream& input, Person& person);
    friend ostream& operator<<(ostream& output, const Person& person);
    friend ostream& operator<<(ostream& output, const vector<Person>& base);
    friend istream& operator>>(istream& input, vector<Person>& base);


};


#endif //PERSON_HPP