#ifndef MY_SEMESTER_HPP
#define MY_SEMESTER_HPP

#include <iostream>
#include <vector>
#include <string>
#include"student.hpp"
#include"professor.hpp"
#include"course.hpp" 


//forward declaration to work the fuction with the upwards classes
class Student;
class Professor;
class Course;

class Academic_Semester {
    int number;
    vector<Student*> liststud;
    vector<Professor*> listprof;
    vector<Course*> listcourse;

public:
    Academic_Semester();// default constructor
    Academic_Semester(int number);//initialization list
    int GetNumber() const;
    void PrintListCourse()const;
    void ClearStudents();
    bool CheckIfCourseExists(string checkcourse)const;
    const vector<Course*>& GetCourses()const;
    ~Academic_Semester();
    bool FindSemester(const Academic_Semester* Semester, const Course* lesson) const;
    void UpdateCourses(const vector<Course>& updatedCourses);
    // Setter for the student vector
    void AddStudent(Student* student);
    // Setter for the professor vector
    void AddProfessor(Professor* professor);
    // Setter for the course vector
    void AddCourse(Course* course);
    // Getters Info of Vectors
    const vector<Student*>& GetStudents() const;
    // To graduate, a student must pass 32 lessons and have 240 ECTS points
   friend bool Graduate(Academic_Semester* semesters[],Student* student) ;
    // Print detailed grades for a student
   friend void PrintDetailedGrades(Academic_Semester* semesters, Student* student) ;
   //Find the Course and returns it by reference
    Course* GetCourse(string name);
   void ClearCourses();
   void PrintListCoursewithnumber(int& index)const;
    void ClearProfessors();




    
};

#endif // MY_SEMESTER_HPP
