
#include "semester.hpp"
#include"handlecoursefile.hpp"
#include "student.hpp"  
#include "professor.hpp" 
#include "course.hpp"

using namespace std;
//forward declaration to work the fuction with the upwards classes
class Student;
class Professor;
class Course;


Academic_Semester::Academic_Semester(){}
Academic_Semester::Academic_Semester(int number) : number(number) {
    this->listcourse.clear();
    this->listprof.clear();
    this->liststud.clear();
}
 
 void Academic_Semester::ClearStudents() {
    // Check if the vector is already empty
    if (!liststud.empty()) {
        // Delete each Student object
        for (Student* student : liststud) {
            delete student;
        }

        // Clear the vector
        liststud.clear();
    }
}

 void Academic_Semester::ClearProfessors() {
    // Check if the vector is already empty
    if (!listprof.empty()) {
        // Delete each Student object
        for (Professor* professor : listprof) {
            delete professor;
        }

        // Clear the vector
        listprof.clear();
    }
}

 void Academic_Semester::ClearCourses() {
    // Check if the vector is already empty
    if (!listcourse.empty()) {
        // Delete each Student object
        for (Course* course : listcourse) {
            delete course;
        }

        // Clear the vector
        listcourse.clear();
        
    }
}

int Academic_Semester::GetNumber() const {
    return this->number;
}

void Academic_Semester::PrintListCourse()const{
    for(auto it = listcourse.cbegin(); it!=listcourse.cend(); it++){ //TO C GIA CONSTANT
       cout << *it <<endl; 
    }
}

bool Academic_Semester::CheckIfCourseExists(string checkcourse)const{
    for(auto it = listcourse.cbegin(); it!=listcourse.cend(); it++){
        if((*it)->GetCourseName()==checkcourse){
            return true;
        }
    }
    return false;
}

const vector<Course*>& Academic_Semester::GetCourses() const {
    return listcourse;
}

Academic_Semester::~Academic_Semester() {
    // No need to delete vectors, they will handle memory automatically
    liststud.clear();
    listcourse.clear();
    listprof.clear();
}



bool Academic_Semester::FindSemester(const Academic_Semester* Semester, const Course* lesson) const {
    int target = lesson->GetCourseSemester();  // Fix function logic
    if (target != Semester->GetNumber()) {
        cout << "The Course is Not in this Semester" << endl;
        return false;
    } else
        return true;
}

void Academic_Semester::UpdateCourses(const vector<Course>& updatedCourses) {
    // Clear the existing vector of pointers
    for (Course* coursePtr : listcourse) {
        delete coursePtr;  // Delete each Course object
    }
    listcourse.clear();

    // Populate the vector of pointers with new Course objects
    for (const auto& course : updatedCourses) {
        listcourse.push_back(new Course(course));
        // Note: This assumes that the Course class has a copy constructor.
    }
}



// Setter for the student vector
void Academic_Semester::AddStudent(Student* student) {
    if(student!=nullptr){
        this->liststud.push_back(student);
        cout << "Student " << student->Get_Name() << " also added to a subject in semester "
         << this->GetNumber()<< endl;
    }
    else cout<<"Invalid Student..."<<endl;
}

// Setter for the professor vector
void Academic_Semester::AddProfessor(Professor* professor) {
    if(professor!=nullptr){
        this->listprof.push_back(professor);
        cout << "-Professor " << professor->Get_Name() <<" "<<professor->Get_Surname()<<" added to Semester " 
        << this->GetNumber() << endl;
    }
    else cout<<"Invalid Professor..."<<endl;
}

// Setter for the course vector
void Academic_Semester::AddCourse(Course* course) {
    this->listcourse.push_back(course);
    cout << "Course " << course->GetCourseName() << " added to Semester " << this->GetNumber() << endl;
}



const vector<Student*>& Academic_Semester::GetStudents() const {
    return liststud;
}

// To graduate, a student must pass 32 lessons and have 240 ECTS points
bool Graduate(Academic_Semester* semesters[], Student* student) {
    // Check for nullptr to avoid potential issues
    
    if (student == nullptr || semesters == nullptr) {
        cout << "Error in Semesters or Student's Status" << endl;
        return false;
    }

    // Check if the student has completed at least 8 semesters
    if (student->GetMySemester() < 8) {
        cout << "-" << student->Get_Name() << " " << student->Get_Surname()
             << " is not eligible for graduation. Incomplete Study Duration." << endl;
        return false;
    }

    

    if(student->CheckifStudenthasNOcourses()){
        cout << "-Student has not enrolled in any courses and is not eligible for graduation. Incomplete Study Duration."<< endl;
        return false;
    }

    int passedCounter = 0;
    int totalEcts = 0;

    // Iterate through each semester the student has completed
    for (int i = 0; i < 8 ;i++) {

        // Iterate through courses in the semester
        for (const Course* course : semesters[i]->GetCourses()) {
            
            // Iterate through grades in the semester for each student
            for (const Grade* grade : student->GetGrades()) {
                
                // Check if the lesson names match and points are greater than or equal to 5
                if (grade->lesson == course->GetCourseName() && grade->points >= 5) {
                    cout << "Student " << student->Get_Name() << " passed the course " << course->GetCourseName()
                         << " in semester " << semesters[i]->GetNumber() << endl;
                    totalEcts += course->GetEcts();
                    passedCounter++;
                }
            }
        }
    }

    // Last check
    return (passedCounter >= 32 && totalEcts >= 240);
}




 Course* Academic_Semester::GetCourse(string name){
    for( Course* target : this->GetCourses()){
        if(target->GetCourseName()==name){
            return target;
        }
        else continue;
    }
   // cout<<"Course Not Found"<<endl;
    return nullptr;
}


// Print detailed grades for a student
void PrintDetailedGrades(Academic_Semester* semesters, Student* student) {
    // Check if the student has completed at least 4 years (8 semesters)
    underlinetext("Detailed Grades for Student");
    cout<< student->Get_Name() <<" "<< student->Get_Surname() <<":" << endl;

    for (int semesterIndex = 0; semesterIndex < student->GetMySemester(); semesterIndex++) {
        Academic_Semester* currentSemester = &semesters[semesterIndex];

        // Iterate through the grades of the student
        for (const Grade* grade : student->GetGrades()) {
            // Get the course associated with the grade
            const Course* course = currentSemester->GetCourse(student->GetSubject(grade));

            // Check if the course is valid
            if (course != nullptr) {
                // Check if the student passed the course (points >= 5)
                cout << "Course: " << student->GetSubject(grade) << "  Points: " << student->GetPoints(grade) << " /10";

                if (course->IsMandatory()) {
                    cout << " Mandatory";
                } else {
                    cout << " Not Mandatory";
                }

                if (student->GetPoints(grade) >= 5) {
                    underlinetext(" Passed");
                } else {
                    underlinetext(" Not Passed");
                }
            } else {
                // Handle the case where the course is not found
               // cout << "Course not found for grade." << endl;
            }
        }
    }
    cout<<endl;
    underlinetext( "End of Detailed Grades.");
    cout<<endl;
}


void Academic_Semester::PrintListCoursewithnumber(int& index)const{
    for(auto it = listcourse.cbegin(); it!=listcourse.cend(); it++){ //TO C GIA CONSTANT
       cout << index << ')' << (*it)->GetCourseName() <<endl;
       index++; 
    }
}