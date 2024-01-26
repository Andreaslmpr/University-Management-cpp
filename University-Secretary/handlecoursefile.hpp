#ifndef MY_HANDLE_COURSE_FILE_HPP
#define MY_HANDLE_COURSE_FILE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "person.hpp"
#include "secretary.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "course.hpp"
#include "semester.hpp"

//forward declaration to work the fuction with the upwards classes
class Student;
class Professor;
class Course;
class Academic_Semester;

void readCoursesfile(Academic_Semester* semesters, int size);
void appendCoursesfile(Academic_Semester* semesters, int size);
void deleteCoursesfile(Academic_Semester* semesters,int size);
void modifyCoursesfile(Academic_Semester* semesters,int size);
//usage of API 
void underlinetext(const std::string& text);

#endif //MY_HANDLE_COURSE_FILE_HPP