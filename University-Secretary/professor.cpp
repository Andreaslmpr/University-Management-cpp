#include "professor.hpp"

using namespace std;

//forward declaration to work the fuction with the upwards classes
class Student;
class Professor;
class Course;


// Definition of the static vector AllProfessors
 vector<Professor> Professor::AllProfessors;

Professor::Professor(string name, string surname, string id, int age) : Person(name, surname, id, age) {
    cout << "Professor Created" << endl;
}

Professor::Professor(){
    cout<<"Professor Created"<<endl;
}

// Copy constructor definition
Professor::Professor(const Professor& other) {
    // Copy other's data members to this object
    this->name = other.name;
    this->surname = other.surname;
    this->id = other.id;
    this->age = other.age;
   for (const string& target : other.subjects) {
        this->subjects.push_back(target);
   }
}

Professor::~Professor() {
    this->subjects.clear();
    //cout << "Professor Destructed" << endl;
}

// Definition of the static member function AddProfessor
void AddToAllProfessors(const Professor& professor) {
    Professor::GetAllProfessors().push_back(professor);
}
// Definition of the static member function RemoveProfessorByID
void Professor::RemoveProfessorByID(const string& professorID) {
    // Use an iterator to find the professor with the specified ID
    auto it = AllProfessors.begin();
    while (it != AllProfessors.end()) {
        if (it->Get_Id() == professorID) {
            // Erase the professor from the vector
            it = AllProfessors.erase(it);
        } else {
            ++it;
        }
    }
}

// Overloading the input stream operator
istream& operator>>(istream& input, Professor& professor) {
    cout << endl << "------------------------UNIVERSITY DATA BASE---------------------------(input stream professor)" << endl;

    cout << "-Insert the Name of the Professor: ";
    if (!professor.name.empty()) professor.name.clear(); //already existing name
    input >> professor.name;
    //Wrong Input Check
    while (!isValidName(professor.Get_Name())) {
        cout << "-Invalid User Input" << endl;
        cout << "-Insert the Name of the Professor: ";
        input >> professor.name;
    }

    cout << "-Insert the Surname: ";
    if (!professor.surname.empty()) professor.surname.clear(); //already existing name
    input >> professor.surname;
    //Wrong Input Check
    while (!isValidName(professor.Get_Surname())) {
        cout << "-Invalid User Input" << endl;
        cout << "-Insert the Surname of the Professor: ";
        input >> professor.surname;
    }

    cout << "-Insert Age:  ";
    input >> professor.age;
    while (professor.age <= 25 || professor.age >= 100) {
        cout << endl << "Invalid Age...New Input Please: ";
        input >> professor.age;
    }

    cout << "-Insert the University ID: ";
    if (!professor.id.empty()) professor.id.clear(); //already existing name
    input >> professor.id;

    cout << "-Insert how many Subjects the Professor will Teach: " << endl;
    int numSubj;
    input >> numSubj;

    // Clear existing subjects
    professor.subjects.clear();

    while (numSubj > 0){
        string subject;
        cout << "-Enter the Subject of the Professor: " << endl;
        input >> subject;
        professor.subjects.push_back(subject);
        numSubj--;
    }

    cout << "-Do you Want to Add Another Subject for The Professor , Press Y for YES , Otherwise press any other key " << endl;
    string addAnotherSubject;
    input >> addAnotherSubject;

    while (addAnotherSubject == "Y" || addAnotherSubject == "y") {
        string subj;
        cout << "-Enter Another Subject of the Professor: " << endl;
        professor.SetSubject(subj,nullptr);

        cout << "-Do you Want to Add Another Subject for The Professor , Press Y for YES , Otherwise press any other key " << endl;
        input >> addAnotherSubject;
    }

    cout << endl << "-Professor Assignments Has Been Completed..." << endl;
    return input;
}

void Professor::SetSubject(string target, Academic_Semester* semesters) {
    // Check if the subject is already assigned
    bool alreadyAssigned = false;
    for (const string& subject : this->subjects) {
        if (target == subject) {
            alreadyAssigned = true;
            cout << "Already Assigned Subject" << endl;
            break;  // Exit the loop since the subject is already assigned
        }
    }

    // If the subject is not assigned, add it to the list
    if (!alreadyAssigned) {
        this->subjects.push_back(target);
        cout << "Subject " << target << " has been assigned to Professor " << this->Get_Name() << endl;
    }
    cout<<endl;
}

void Professor::FinalGrade(const Course& target, Student& student, float pointss) {
    cout << "------------Professors Exams Final Grade-------------" << endl;

    // First check if the Student can be Assessed in this Course
    if (target.GetCourseSemester() > student.GetMySemester()) {
        cout << "Student cannot be Assessed in this Course" << endl;
        exit(0);
    }
    // So this Course is in The Semester of the Student
    // Now Set the Grade
    student.SetGrade(pointss,target.GetCourseName());
    cout << "The Student " << student.Get_Name() << " " << student.Get_Surname() << " Has a Grade "
         << pointss << "/10"
         << " in The " << target.GetCourseName() << " Course "
         << " by Professor " << this->Get_Name() << " " << this->Get_Surname()
         << endl;
}


 void Professor::ClearAllProfessors() {
    AllProfessors.clear();
}

Professor* Professor::CheckIfProfessorExistsById(string checkProfessorId) const {
    for (const Professor& professor : AllProfessors) {
        if (professor.Get_Id() == checkProfessorId) {
            return const_cast<Professor*>(&professor);
        }
    }

    cout << "- Professor Not Exists" << endl;
    return nullptr;
}


vector<Professor>& Professor::GetAllProfessors(){
    return AllProfessors;
}
// In the AddToAllProfessorss function
void AddToAllProfessors(Professor* professor) {
    if(professor==nullptr)
        cout<<"Cannot Add to Professors"<<endl;
    else
    Professor::GetAllProfessors().push_back(*professor);
}

 const Professor* findProfessorById(const string& professorId, const vector<Professor>& professors) {
    for (const Professor& professor : professors) {
        if (professor.Get_Id() == professorId) {
            return &professor;
        }
    }
    return nullptr;  // Professor with the given ID not found
}

void Professor::AssignGrade(const string& studentId, const string& courseName, int points, Academic_Semester* semester) {
    // Check if the professor is teaching the specified course
    Course* course = nullptr;
    for (Course* c : semester->GetCourses()) {
        Professor* profTeaching = c->IsProfTeaching(this);
        if (profTeaching != nullptr && c->GetCourseName() == courseName) {
            course = c;
            break;
        }
    }
    // Check if the course is found
    if (course==nullptr) {
        cout << "Professor is not teaching the course " <<courseName << endl;
        return;
    }
    // Find the student in the semester
    Student* student = nullptr;
    for (Student* s : semester->GetStudents()) {
        if (s->Get_Id() == studentId) {
            student = s;
            break;
        }
    }
    // Check if the student is found
    if (!student) {
        cout << "Student with ID " << studentId << " not found in the semester." <<endl;
    }

    // Use the FinalGrade function to assign the grade
    FinalGrade(*course, *student, points);
    cout<<"Grade for Student: "<<student->Get_Name()<<" "<<student->Get_Surname()<<" in the Course "<<course->GetCourseName()
    <<" Has Been Set"<<endl<<endl;
}

void Professor::PrintProfessorsSubjects()const {
    cout << "Courses available to grade for professor " << this->Get_Surname() << endl;
    int i = 1;
    for(auto it = subjects.cbegin(); it!=subjects.cend(); it++){ //TO C GIA CONSTANT
           cout << i << ')' << " " <<  *it <<endl; 
           i++;
    }
    
}

const vector<string>& Professor::GetProfessorsSubjects()const{
    return subjects;
}