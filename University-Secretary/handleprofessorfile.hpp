#ifndef MY_HANDLEPROFESSORFILE_HPP
#define MY_HANDLEPROFESSORFILE_HPP

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

void readProfessorsfile(Academic_Semester* semesters,int size);
void appendProfessorsfile(Academic_Semester* semesters,int size);
void deleteProfessorfile();
void modifyProfessorfile(Academic_Semester* semesters,int size);



#endif //MY_HANDLEPROFESSORFILE_HPP