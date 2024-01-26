#ifndef MY_HANDLESTUDENTFILE_HPP
#define MY_HANDLESTUDENTFILE_HPP

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

void readStudentsfile(Academic_Semester* semesters, int size);
void appendStudentsfile(Academic_Semester* semesters,int size);
void deleteStudentfile(Academic_Semester* semesters,int size);
void modifyStudentfile(Academic_Semester* semesters,int size);
void CreatePassedStudentsfile(Academic_Semester* semesters,int size);
void deleteFile(const string& filename);

#endif //MY_HANDLESTUDENTFILE_HPP