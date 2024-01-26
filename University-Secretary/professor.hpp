#ifndef MY_PROFESSOR_HPP
#define MY_PROFESSOR_HPP

#include <iostream>
#include <vector>
#include <string>
#include "person.hpp"
#include "course.hpp"
#include "student.hpp"
#include"semester.hpp"

//forward declaration to work the fuction with the upwards classes
class Student;
class Professor;
class Course;
class Academic_Semester;

class Professor : public Person {
private:
    static vector<Professor> AllProfessors;
    vector<string> subjects;

public:
    Professor(string name,string surname,string id, int age);
    Professor();//default constructor for Memory allocation usage
    Professor(const Professor& other); //Copy Constructor
    ~Professor();
    static void AddProfessor( Professor* professor);
    static void RemoveProfessorByID(const string& professorID);
    friend istream& operator>>(istream& input, Professor& professor);
    void SetSubject(string target,Academic_Semester* semesters); 
    void FinalGrade(const Course& target, Student& student, float pointss);
    static void ClearAllProfessors();
    Professor* CheckIfProfessorExistsById(string checkProfessorId)const;
    static vector<Professor>& GetAllProfessors();
    friend void AddToAllProfessors(const Professor& professor);
    const Professor* findProfessorById(const string& professorId, const vector<Professor>& professors);
    void AssignGrade(const string& studentId, const string& courseName, int points, Academic_Semester* semester);
    void PrintProfessorsSubjects()const;
    const vector<string>& GetProfessorsSubjects()const;
    
    

};
#endif // MY_PROFESSOR_HPP