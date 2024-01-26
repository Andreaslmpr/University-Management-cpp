#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include<limits>
#include <time.h>
#include<cstdio>
#include "person.hpp"
#include "secretary.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "course.hpp"
#include "semester.hpp"
#include "handlecoursefile.hpp"
#include "handleprofessorfile.hpp"
#include "handlestudentfile.hpp"

using namespace std;



int main() {
    Academic_Semester* semesters = new Academic_Semester[8];

    for (int i = 1; i <= 8; ++i) {
        // Explicitly call the parameterized constructor
        new (&semesters[i - 1]) Academic_Semester(i);
    }
cout<<endl;
    underlinetext("List of Student in DI University 2023-2024:\n");
    cout<<endl;
    readStudentsfile(semesters, 8);
    cout<<endl;
    underlinetext("Courses in DI University 2023-2024:\n ");
    cout<<endl;
    readCoursesfile(semesters, 8);
    cout<<endl;
    underlinetext("List of Professors in DI University 2023-2024:\n ");
    cout<<endl;
    readProfessorsfile(semesters, 8);
    cout<<endl;

    cout << "----------WELCOME TO THE DIT UNIVERSITY OF ATHENS----------\n";
    bool exitprogram = false;

    do {
        int cases;
        underlinetext("OPTION LIST:");
        cout << endl<<"-Press '1' to enter professor modification.\n"
             << "-Press '2' to enter student modification.\n"
             << "-Press '3' to enter course modification.\n"
             << "-Press '4' to assign Professors to courses.\n"
             << "-Press '5' to enroll a student in a course.\n"
             << "-Press '6' to make Professor assign Grades\n"
             << "-Press '7' to record and save students who passed a specific course in a semester.\n"
             << "-Press '8' to print a professor's semester statistics for all of their courses.\n"
             << "-Press '9' to print detailed grades for the current semester and all years for a student.\n";
             underlinetext( "-Press '10' to print the list of students eligible for graduation.");
             cout<< "\nPress any other key to exit the program\n";
             
        cin >> cases;
        cout<<endl;
        switch (cases) {
            case 1:
                char fileinput;
                cout << "-Press 'A' to add new professor\n"
                     << "-Press 'M' to modify professor's information\n"
                     << "-Press 'D' to delete professor\n"
                     << "-Press any other key to exit professor modification\n";
                cin >> fileinput;
                fileinput = toupper(fileinput);

                switch (fileinput) {
                    case 'A':
                        appendProfessorsfile(semesters, 8);
                        break;
                    case 'M':
                        modifyProfessorfile(semesters, 8);
                        break;
                    case 'D':
                        deleteProfessorfile();
                        break;
                    default:
                        cout << "Exiting professor modification\n";
                        break;
                }
                cout<<endl;
                break;

            case 2: {
                char fileinput;
                cout << "-Press 'A' to add new student\n"
                     << "-Press 'M' to modify students's information\n"
                     << "-Press 'D' to delete student\n"
                     << "-Press any other key to exit student modification\n";
                cin >> fileinput;
                fileinput = toupper(fileinput);

                switch (fileinput) {
                    case 'A':
                        appendStudentsfile(semesters, 8);
                        break;
                    case 'M':
                        modifyStudentfile(semesters, 8);
                        break;
                    case 'D':
                        deleteStudentfile(semesters, 8);
                        break;
                    default:
                        cout << "Exiting student modification\n";
                        break;
                }
                cout<<endl;
                break;
            }
            case 3: {
                char fileinput;
                cout << "-Press 'A' to add new course\n"
                     << "-Press 'M' to modify course's information\n"
                     << "-Press 'D' to delete course\n"
                     << "-Press any other key to exit course modification\n";
                cin >> fileinput;
                fileinput = toupper(fileinput);

                switch (fileinput) {
                    case 'A':
                        appendCoursesfile(semesters, 8);
                        break;
                    case 'M':
                        modifyCoursesfile(semesters, 8);
                        break;
                    case 'D':
                        deleteCoursesfile(semesters, 8);
                        break;
                    default:
                        cout << "Exiting course modification\n";
                        break;
                }
                cout<<endl;
                break;
                cout<<endl;
            }
          
            case 4: {
                underlinetext("-The List of Professors at DIT University:\n" );
                cout<<endl;

                int i = 1;
                const vector<Professor>& professors = Professor::GetAllProfessors();

                for (const Professor& professor : professors) {
                    cout << i << ") " << professor.Get_Name() << " " << professor.Get_Surname() << endl;
                    i++;
                }

                cout << "-Select Professor's index to Assign a Course: " << endl;

                int userinput;
                cin >> userinput;
        
                // Check for the right Index Option
                while (true) {
                    if (userinput < 1 || static_cast<size_t>(userinput) > professors.size()) {
                        cout << "Invalid Input, Please Try again...." << endl;
                        cout << "-Select Professor's index to Assign a Course: " << endl;
                        cin >> userinput;
                    } else {
                        break;
                    }
                }

                // Display courses for selection
                for (int j = 0; j < 8; j++) {
                    int courseIndex = 1; // Initialize index for each semester
                    cout << "Courses for Semester " << (j + 1) << ":" << endl;
                    semesters[j].PrintListCoursewithnumber(courseIndex);
                    cout << endl; // Add a newline for better readability between semesters
                }

                string newuserinput;
                bool found = false;

                do{
                    cout << "Enter Course's name to assign to Professor " << professors[userinput - 1].Get_Surname() << ": ";
                    getline(std::cin >> ws, newuserinput);
                    

                    // Check if the entered course exists in any semester
                    for (int j = 0; j < 8; j++) {
                        if (semesters[j].CheckIfCourseExists(newuserinput)) {
                            found = true;
                            break;  // Exit the loop once the course is found in any semester
                        }
                    }

                if (!found) {
                    cout << "Invalid Input, Please Try again...." << endl;
                } else {
                    break; // Exit the loop if the course is found
                }
            } while (found == false);
        
            // Assign the course to the selected professor
            Professor& selectedProfessor = Professor::GetAllProfessors()[userinput - 1];
            Course* selectedCourse = FindCourseByName(newuserinput, semesters);
        
            if (selectedCourse != nullptr) {
                selectedCourse->SetCourse(&selectedProfessor);
                selectedProfessor.SetSubject(newuserinput, semesters);
            } else {
                cout << "Course not found." << endl;
            }
        
            break;
            }
            

        case 5:{
            char exitenrollment='y';
            string userinput;
            bool found=false;
            char tryagain;
            Student* student = nullptr;
            
                do{
                    tryagain='Y';
                    underlinetext( "-Enter Student's ID you want to enroll to courses: ");
                    cout<<endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');//To clear the buffer
                    getline(cin,userinput);
                    

                    student = findStudentById(userinput, semesters);
                    if (student==nullptr){
                        cout << "Student with ID " << userinput << " doesnt't exist."
                            << "Do you want to try again?Press 'Y' to try again or any other key to exit student's course enrollment.";
                        cin >> tryagain;
                        tryagain=toupper(tryagain);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else{
                        found=true;
                    }
                }
                while(found==false && tryagain=='Y');

                if(tryagain!='Y'){
                    break;
                }
            while(true){
                cout << "-Courses available for student " << student->Get_Name() << " " << student->Get_Surname()
                     << " with ID:" << " " << student->Get_Id() << endl;

                // Display courses for selection
                for (int j = 0; j < student->GetMySemester(); j++) {
                    int courseIndex = 1; // Initialize index for each semester
                    cout << "Courses for Semester " << (j + 1) << ":" << endl;
                    semesters[j].PrintListCoursewithnumber(courseIndex);
                    cout << endl; // Add a newline for better readability between semesters
                }

                found=false;
                Course* course;
                while(exitenrollment=='Y'){
                    cout<<"------------------"<<endl;
                        cout << "Enter Course's name to assign to student " << student->Get_Surname() << ": ";
                        getline(std::cin >> std::ws, userinput);

                        // Check if the entered course exists in any semester
                        for (int j = 0; j < student->GetMySemester(); j++) {
                            if (semesters[j].CheckIfCourseExists(userinput)) {
                                course = semesters[j].GetCourse(userinput);                   
                                found = true;
                                break;  // Exit the loop once the course is found in any semester
                            }
                        }

                    if (!found) {
                        cout << "Invalid Input, Please Try again...." << endl;
                    }
                    else{
                        break;
                    }
                }
                course->EnrollStudent(semesters,student);
                cout << "Do you want to enroll another course to this student?"
                     << "Press 'Y' to continue or any other key to exit enrollment" << endl;
                
                cin >> exitenrollment;
                exitenrollment=toupper(exitenrollment);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(exitenrollment!='Y')
                    break; 
                else continue;
            }
            break;
        }

            case 6: {
                char userinput;
                while(true){
                    cout <<"Press 'R' to insert grades randomly(faster,for time reasons) or 'M' to manually assign grades\n";
                    cin >> userinput;
                    userinput=toupper(userinput);
                    if(userinput!='M' && userinput!='R'){
                        cout << "Invalid input please try again." << endl;
                    }
                    else{
                        break;
                    }
                }
                if(userinput=='M'){
 // Display professors for selection
                    int professorIndex = 1;
                    int selectedProfessorIndex;
                    const vector<Professor>& professors = Professor::GetAllProfessors();
                    cout << "-Select professor's index which is assigning grades: " << endl;

                    for (const Professor& professor : professors) {
                        cout << professorIndex << ") " << professor.Get_Name() << " " << professor.Get_Surname() << endl;
                        professorIndex++;
                    }

                    cout << "Enter Professor's index: ";
                    cin >> selectedProfessorIndex;

                    while (selectedProfessorIndex < 1 || selectedProfessorIndex > professorIndex - 1) {
                        cout << "Invalid Input, Please Try again...." << endl;
                        cout << "Enter Professor's index: ";
                        cin >> selectedProfessorIndex;
                    }


                    const Professor& selectedProfessor=Professor::GetAllProfessors()[selectedProfessorIndex - 1];
                    const vector<string>& selectedSubjects=selectedProfessor.GetProfessorsSubjects();
                    if(selectedSubjects.empty()){
                        cout << "Professor " << selectedProfessor.Get_Surname() << " has not been assigned to any courses" << endl;
                        break;
                    }
                    int courseindex;
                    while(true){
                        selectedProfessor.PrintProfessorsSubjects();
                        cout << "-Select courses's index to assign grades: " << endl;
                        cin >> courseindex;
                        //cast to can compare with the size of a vector
                        if (courseindex < 1 || static_cast<long unsigned int>(courseindex) > selectedSubjects.size()){
                            cout << "Invalid course index. Please enter a valid index." << endl;
                        }
                        else{
                            break;
                        }
                    }

                    string subject = selectedSubjects[courseindex-1];
                    int subjectsemester;
                    Course* course;
                    for(int i=0;i<8;i++){
                        for (Course* c : semesters[i].GetCourses()){
                            //cout << c->GetCourseName() << endl; THEMA DEN PRINTAREI TO NAME KAI DE MPAINEI POTE STH APO KATW SUNTHIKI!
                            if (c->GetCourseName() == subject) {
                                course = c;
                                subjectsemester=i;
                                break;
                            }
                        }
                    }
                    Academic_Semester& targetSemester = semesters[subjectsemester];
                    for (Student* student : targetSemester.GetStudents()) {
                        if(course->IsStudentEnrolled(student)){
                            while(true){
                                cout << "Enter grade for student " << student->Get_Name()
                                     << " " << student->Get_Surname() << ": ";
                                float grade;
                                cin >> grade;
                                if(grade<0.0 || grade>10.0){
                                    cout << "\nInvalid grade please try again." <<endl;
                                }
                                else{
                                    Professor::GetAllProfessors()[selectedProfessorIndex - 1].AssignGrade(student->Get_Id(),course->GetCourseName(),grade, &targetSemester);
                                    break;
                                }
                            }     
                        }
                    }
                }
                else{
                    srand(time(NULL));
                    // Display professors for selection
                    int professorIndex = 1;
                    int selectedProfessorIndex;
                    const vector<Professor>& professors = Professor::GetAllProfessors();
                    cout << "-Select professor's index which is assigning grades: " << endl;

                    for (const Professor& professor : professors) {
                        cout << professorIndex << ") " << professor.Get_Name() << " " << professor.Get_Surname() << endl;
                        professorIndex++;
                    }

                    cout << "Enter Professor's index: ";
                    cin >> selectedProfessorIndex;

                    while (selectedProfessorIndex < 1 || selectedProfessorIndex > professorIndex - 1) {
                        cout << "Invalid Input, Please Try again...." << endl;
                        cout << "Enter Professor's index: ";
                        cin >> selectedProfessorIndex;
                    }


                    const Professor& selectedProfessor=Professor::GetAllProfessors()[selectedProfessorIndex - 1];
                    const vector<string>& selectedSubjects=selectedProfessor.GetProfessorsSubjects();
                    if(selectedSubjects.empty()){
                        cout << "Professor " << selectedProfessor.Get_Surname() << " has not been assigned to any courses" << endl;
                        break;
                    }
                    int courseindex;
                    while(true){
                        selectedProfessor.PrintProfessorsSubjects();
                        cout << "-Select courses's index to assign grades: " << endl;
                        cin >> courseindex;
                        if (courseindex < 1 || static_cast<long unsigned int>( courseindex )> selectedSubjects.size()){
                            cout << "Invalid course index. Please enter a valid index." << endl;
                        }
                        else{
                            break;
                        }
                    }

                    string subject = selectedSubjects[courseindex-1];
                    int subjectsemester;
                    Course* course;
                    for(int i=0;i<8;i++){
                        for (Course* c : semesters[i].GetCourses()){
                            //cout << c->GetCourseName() << endl; THEMA DEN PRINTAREI TO NAME KAI DE MPAINEI POTE STH APO KATW SUNTHIKI!
                            if (c->GetCourseName() == subject) {
                                course = c;
                                subjectsemester=i;
                                break;
                            }
                        }
                    }
                    Academic_Semester& targetSemester = semesters[subjectsemester];
                    for (Student* student : targetSemester.GetStudents()) {
                        if(course->IsStudentEnrolled(student)){
                            while(true){
                                Professor::GetAllProfessors()[selectedProfessorIndex - 1].AssignGrade(student->Get_Id(),course->GetCourseName(),rand() % 11, &targetSemester);
                                break;
                            }     
                        }
                    }
                }
                break;
            }

            case 7: {
                CreatePassedStudentsfile(semesters, 8);
                break;
            }

            case 8: {
                string professorId;
                underlinetext("-Please Insert the Professor's ID that you want to Print Their Stats:" );
                cout<<endl;
                cin >> professorId;
                const Professor* targetProfessor = targetProfessor->CheckIfProfessorExistsById(professorId);

                if (targetProfessor != nullptr) {
                    underlinetext("-Statistics for Professor ");
                    cout<< targetProfessor->Get_Name() << " " << targetProfessor->Get_Surname()
                        << ":" << endl<<endl;
                    for (int i = 0; i < 8; i++) {
                        Academic_Semester* current_semester = &semesters[i];
                        bool professorTeachesInSemester = false;

                        for (Course* course : current_semester->GetCourses()) {
                            const Professor* foundProfessor;
                            foundProfessor = foundProfessor->CheckIfProfessorExistsById(professorId);

                            if (foundProfessor != nullptr && course->IsProfTeaching(foundProfessor)) {
                                professorTeachesInSemester = true;

                                double totalPoints = 0;
                                int passedStudents = 0;
                                int totalStudents = 0;

                                for (Student* student : current_semester->GetStudents()) {
                                    if (student->PassedCourse(*course)) {
                                        totalPoints += student->Get_CourseGrade(course->GetCourseName());
                                        passedStudents++;
                                    }

                                    totalStudents++;
                                }

                                double averageGrade = (totalStudents > 0) ? totalPoints /totalStudents : 0.0;

                                cout << "Semester: " << i + 1 << ", Course: " << course->GetCourseName() << endl;
                                cout << "   Total Students: " << totalStudents << endl;
                                cout << "   Passed Students: " << passedStudents << endl;
                                cout << "   Average Grade: " << averageGrade << endl;
                                cout << endl;
                            }
                        }

                        if (!professorTeachesInSemester) {
                            cout << "Professor does not teach any course in Semester " << i + 1 << endl;
                        }
                    }
                    cout<<"-----------------"<<endl<<endl;
                } else {
                    cout << "Professor with ID " << professorId << " does not exist." << endl;
                }
                break;
            }

            case 9: {
                 char tryagain;
                 string userinput;
                 bool found=false;
                 Student* student;
                 do{
                    tryagain='Y';
                    cout << "Enter student's ID you want to to see their detailed grades" << endl;
                    cin >> userinput;

                    student = findStudentById(userinput, semesters);
                    if (student==nullptr){
                        cout << "Student with ID " << userinput << " doesnt't exist."
                            << "Do you want to try again?Press 'Y' to try again or any other key to exit student's course enrollment.";
                        cin >> tryagain;
                        tryagain=toupper(tryagain);
                    }
                    else{
                        found=true;
                    }
                }
                while(found==false && tryagain=='Y');

                if(tryagain!='Y'){
                    break;
                }

                PrintDetailedGrades(semesters, student);
                cout<<endl;
                
                break;
            }

            case 10: {
                for (int i = 0; i < 8; i++) {
                    cout <<endl;
                    cout << "Entering semester " << i+1 << endl;
                    for (Student* target : semesters[i].GetStudents()) {
                        cout <<endl;
                        cout << "Processing student: " << target->Get_Name() << " " << target->Get_Surname() << endl;
                        cout << "Student's semester: " << target->GetMySemester() << endl;

                        if (Graduate(&semesters, target)) {
                            cout << "Student " << target->Get_Name() << " " << target->Get_Surname() << " is eligible for graduation." << endl;
                        } else {
                            cout << "Student " << target->Get_Name() << " " << target->Get_Surname() << " is not eligible for graduation." << endl;
                        }


                    }
                    cout << "Exiting semester " << i+1 << endl;


                }
                cout<<endl;

            break;
            }


            default:
                cout << "This was the demonstration of the Program, End Of Program" << endl;
                exitprogram = true;
                break;
        }
    } while(!exitprogram);

//Destructors of the program 
    for(int i=0;i<8;i++){
        for(Student* student : semesters[i].GetStudents())
            student->GetGrades().clear();

        semesters[i].ClearStudents();
        

        for(Course* course : semesters[i].GetCourses()){
            for(Professor* professor: course->GetTeachers())
            delete professor;

            for(Student* student : course->GetCourseStudents())
                delete student;
        }
        semesters[i].ClearCourses();



        semesters[i].ClearProfessors();

        
    }
   
    
    delete[] semesters;
    
    return 0;
}
