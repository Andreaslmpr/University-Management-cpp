#ifndef MY_SECRETARY_HPP 
#define MY_SECRETARY_HPP
//To avoid multiple compilation
#include "person.hpp"
#include <iostream>
#include <vector>


class Person;       //forward declaration

class Secretary{
private:
    vector<Person> database;
public:
    Secretary();
    ~Secretary();
    Secretary(const Secretary& original);
    void operator+(const Person& person);
    void operator+=(const Person& person);
    void operator=(const Secretary& newdatabase);
    friend ostream& operator<<(ostream& output, const Secretary& base);
    friend istream& operator>>(istream& input, Secretary& base);
    bool FindPerson(string Id)const;
};

#endif