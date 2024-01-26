#ifndef MY_COURSE_HPP
#define MY_COURSE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include"professor.hpp"
#include"person.hpp"
#include"student.hpp" 
#include"semester.hpp"

//forward declaration to work the fuction with the upwards classes
class Student;
class Professor;
class Course;

class Course {
private:
    string subject_name;
    vector<Professor*> teachers; // The Professors that teach the subject
    int Ects;
    int semester;
    bool mandatory;
    vector<Student*>students;
    friend class Professor;

public:
    Course(string name, int ects, int semester, bool mandatory);
    ~Course();
    void MoveSemester(int new_semester);
    vector<Professor*>& GetTeachers();
    string GetCourseName() const;
    int GetEcts()const;
    int GetCourseSemester() const;
    bool IsMandatory() const;
    void SetSemester(int new_semester);
    friend istream& operator>>(istream& input, Course& course);
    // Function for the assignment of Subjects to Professors from Secretary
    void SetProfessor_Course( Professor* professor);
    Professor* IsProfTeaching(const Professor* target);
    void EnrollStudent(Academic_Semester* semesters,Student* student);
    const vector<Student*>& GetCourseStudents()const;
    void SetCourse(Professor* professor);
   bool IsStudentEnrolled(Student* target) const;


};
Course* FindCourseByName(string target, Academic_Semester* semesters);
#endif // MY_COURSE_HPP
