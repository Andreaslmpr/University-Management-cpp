#include"course.hpp"


using namespace std;

//forward declaration to work the fuction with the upwards classes
class Student;
class Professor;
class Course;


Course::Course(string name, int semester,int ects, bool mandatory)
    : subject_name(name), Ects(ects), semester(semester), mandatory(mandatory) {
    this->teachers.clear();
    cout << "Course Created" << endl;
}

Course::~Course() {
    // Vector manages their memory automatically, no need to delete individual elements
    students.clear();
    teachers.clear();

    cout << "Course Destructed" << endl;
}

void Course::MoveSemester(int new_semester) {
    cout << "Course Moved from " << GetCourseSemester() << " Semester to";
    SetSemester(new_semester);
    cout << GetCourseSemester() << " Semester" << endl;
}

string Course::GetCourseName() const {
    return subject_name;
}

vector<Professor*>& Course::GetTeachers() {
    return this->teachers;
}


int Course::GetEcts() const {
    return Ects;
}

int Course::GetCourseSemester() const {
    return semester;
}

bool Course::IsMandatory() const {
    return mandatory;
}

void Course::SetSemester(int new_semester) {
    semester = new_semester;
}

istream& operator>>(istream& input, Course& course) {
    cout << endl << "------------------------UNIVERSITY DATA BASE---------------------------(input stream course)" << endl;
    cout << "-Enter Course's Name";
    input >> course.subject_name;
    cout << "-Enter Course's ECTS";
    input >> course.Ects;
    cout << "-Enter which semester the Course is included";
    input >> course.semester;
    cout << "-Enter 'T' if the Course is mandatory or any other key otherwise";
    char check;
    input >> check;
    check = toupper(check);
    if (check != 'T') {
        course.mandatory = false;
    }
    cout << "-Enter the Professors that the Course will be Assigned to " << endl;
    while (1) {
        // Creating a new professor and checking for memory allocation
        Professor* professor = new Professor();
        input >> *professor;  // executed function in Class Professor

        // Checks for copies of the Professor in the Vector
        bool professorExists = false;
        for (const Professor* target : course.GetTeachers()) {
            if (target->Get_Name() == professor->Get_Name()) {
                cout << "Already Assigned Subject" << endl;
                professorExists = true;
                break;
            }
        }
        if (!professorExists) {
            course.GetTeachers().push_back(professor);
        }

        cout << "-To Add Another Professor for this Course press T, Otherwise press any other key..." << endl;
        cin >> check;
        check = toupper(check);
        if (check != 'T') {
            break;
        }
    }
    return input;
}

void Course::SetCourse(Professor* professor){
    if (professor != nullptr) 
        teachers.push_back(professor);
    
}
Course* FindCourseByName(string target, Academic_Semester* semesters) {
    for (int i = 0; i < 8; ++i) {
        Academic_Semester& semester = semesters[i];
        for (Course* course : semester.GetCourses()) {
            if (course->GetCourseName() == target) {
                return course;  // Return the pointer to the course if found
            }
        }
    }
    return nullptr;  // Return nullptr if the course is not found in any semester
}

void Course::SetProfessor_Course( Professor* professor) {
    cout << "----------WELCOME TO PROFESSOR ACADEMIC ASSIGNMENT----------" << endl;
    cout << endl << "-To Proceed to a Professor's Assignment PRESS Y. Otherwise PRESS any other Key." << endl;
    char check;
    cin >> check;
    check = toupper(check);
    while (check == 'Y') {
        GetTeachers().push_back(professor);
        cout << "-Do you Want Add Another Professor Assignment, press Y . Otherwise any Other Key. " << endl;
        cin >> check;
        check = toupper(check);
    }
}

  Professor* Course::IsProfTeaching(const Professor* target){
    for ( Professor* prof : this->teachers) {
        if (prof->Get_Id() == target->Get_Id())
            return prof;
    }
    return nullptr;
}
const vector<Student*>& Course::GetCourseStudents()const{
    return students;
}
void Course::EnrollStudent(Academic_Semester* semesters, Student* student) {
        if (!IsStudentEnrolled(student)) {  // Note the negation here
            cout << "-Student " << student->Get_Surname() << " is eligible to enroll in this Course " << this->GetCourseName() << endl;
            char userinput;
            cout << "-Do you want to enroll in the Course " << this->GetCourseName() << "? Enter 'Y' for yes or any other key to exit." << endl;
            cin >> userinput;
            userinput = toupper(userinput);
            if (!this->GetCourseName().empty() && userinput == 'Y') {
                this->students.push_back(student);
                cout << "-" << student->Get_Name() << " " << student->Get_Surname() << " successfully enrolled in Course " << this->GetCourseName() << endl;

                semesters[this->GetCourseSemester()-1].AddStudent(student);
            } else {
                cout << "-" << student->Get_Name() << " " << student->Get_Surname() << " chose not to enroll in Course " << this->GetCourseName() << endl;
            }
        } else {
            cout << "-Student " << student->Get_Surname() << " is already enrolled in Course " << this->GetCourseName() << endl;
        }
    //} else {
        //cout << "-Student " << student->Get_Surname() << " is not eligible to enroll in this Course " << this->GetCourseName() << endl;
    //}
}

bool Course::IsStudentEnrolled(Student* target) const {
    // Check if the target student's ID is already in the students vector
    return find_if(students.begin(), students.end(), [target](const Student* student) {
        return student->Get_Id() == target->Get_Id();
    }) != students.end();
}





