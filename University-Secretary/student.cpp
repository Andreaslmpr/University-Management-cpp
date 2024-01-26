#include"student.hpp"

using namespace std;

//forward declaration to work the fuction with the upwards classes
class Student;
class Professor;
class Course;

    Student::Student(string name, string surname,int age, int mysemester,string id )
    :Person(name, surname, id, age), mysemester(mysemester) {
        this->grades.clear();
        cout << "Student:" << name <<" "<< surname <<" Created" << endl;
    }


    Student::~Student(){
        for(Grade* grade : this->grades)
            delete grade;
        this->grades.clear();
        cout<<"Student Destructed"<<endl;
    }

    int Student::GetMySemester()const{
        return mysemester;
    }
    int Student::GetPoints(const Grade* grade)const{
        return grade->points;
    }

    vector<Grade*>  Student::GetGrades()const{
        return this->grades;
    }

    string Student::GetSubject(const Grade* grade)const{
        return grade->lesson;
    }

    string Student::Get_Name(){
        return this->Person::Get_Name();
    }


//Set the Grade(points and lessons) of the Student
void Student::SetGrade(float points,string new_lesson){
    //check for memory allocation
    Grade* target=new Grade();
    if(!target){
        cout<<"Error in Memory Allocation"<<endl;
        exit(0);
    }
    // Check for double input of the same subject, then the final grade is the average of them
    bool found = false;
        for (Grade* target : this->grades) {
            if (target->lesson == new_lesson) {
                float new_points = (target->points + points)/2;
                target->points = new_points;
                found = true;
                break;
            }
        }

        if (!found) {
            target->points = points;
            target->lesson = new_lesson;
            this->grades.push_back(target);
        }

    cout << "Grades Has Been Successfully Assigned" << endl;
}


bool Student::PassedCourse(const Course& course_name) {
    // Check the semesters of the student and course
    if (this->mysemester < course_name.GetCourseSemester()) {
        cout << "-This Course is Not Available for this Student" << endl;
        return false;
    } else {
        for (const Grade* target : this->grades) {
            if (target->lesson == course_name.GetCourseName()) {  // Assuming that has been examined for this lesson
                if (target->points >= 5) {
                    // Above 5/10 is successful
                   // cout << "The Student Has Passed this Course with " << target->points << "/10" << endl;
                    return true;
                } else {
                   // cout << "The Student Has Failed this Course with " << target->points << "/10" << endl;
                    return false;
                }
            }
        }
    }

    // The course was not found in the student's grades
   // cout << "The Student Has Not Been Examined for this Course" << endl;
    return false;
}

    
   
bool Student::HasPassedCourse(string coursename){
    for (const Grade* target : this->grades){
        if (target->lesson == coursename){
            if(target->points>=5.0){
                return true; // student passed course with >=5
            }
            else{
                return false; //student failed
            }
        }
    }
    return false; //student doesnt have the course
}

int Student::Get_CourseGrade(string coursename){
    for (const Grade* target : this->grades){
        if (target->lesson == coursename){
            return target->points;    
        }
    }
    return -1; //course doesnt exist
}

Student* findStudentById(const string& studentId, Academic_Semester* semesters) {
    for(int i=0;i<8;i++){
        for ( Student* student :semesters[i].GetStudents() ) {
            if (student->Get_Id() == studentId) {
                return student;
            }
        }
    }
    return nullptr;  // Professor with the given ID not found
}

bool Student::CheckifStudenthasNOcourses(){
    if(grades.empty()){
        return true;
    }
    else{
        return false;
    }
}