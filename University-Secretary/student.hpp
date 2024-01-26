#ifndef MY_STUDENT_HPP
#define MY_STUDENT_HPP

#include <iostream>
#include <vector>
#include <string>
#include "person.hpp" 
#include"course.hpp"
#include"professor.hpp"
#include"semester.hpp" 



//forward declaration to work the fuction with the upwards classes
class Student;
class Professor;
class Course;
class Academic_Semester;

struct Grade {
    float points;
    string lesson;
};

class Student : public Person {
private:
    int mysemester;
    vector<Grade*> grades;


public:
    Student(string name, string surname,int age, int mysemester,string id );
    ~Student();
    int GetMySemester() const;
    vector<Grade*> GetGrades() const;
    string GetSubject(const Grade* grade) const;
    string Get_Name();
    void SetGrade(float points, string new_lesson);
    bool PassedCourse(const Course& course_name);
    int GetPoints(const Grade* grade)const;
    bool HasPassedCourse(string coursename);
    int Get_CourseGrade(string coursename);
    bool CheckifStudenthasNOcourses();
};
Student* findStudentById(const string& studentId, Academic_Semester* semesters);

#endif // MY_STUDENT_HPP
