#include"handlestudentfile.hpp"
#include<cstdio>


void readStudentsfile(Academic_Semester* semesters, int size) {
    ifstream studentfile("students.txt");
    if (!studentfile.is_open()) {
        cout << "Error: Unable to open students.txt" << endl;
        exit(-1);
    }

    for (int i = 0; i < size; ++i) {
        semesters[i].ClearStudents();
    }

    string firstname, lastname, age, id, semester;
    string line;

    while (getline(studentfile, line)) {
        stringstream ss(line);
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        getline(ss, age, ',');
        getline(ss, semester, ',');
        getline(ss, id, ',');

        int semesterIndex = stoi(semester) - 1;
        if (semesterIndex >= 0 && semesterIndex <= size) {
            // Create a new Student object on the heap and add it to the  semester
            Student* student = new Student(firstname, lastname,stoi(age),stoi(semester), id );
            semesters[semesterIndex].AddStudent(student);
        } else {
            // Handle the case where the semester index is out of bounds
            cout << "Invalid semester index: " << semesterIndex << endl;
        }
    }

    studentfile.close();
}



void appendStudentsfile(Academic_Semester* semesters,int size){
    ofstream addstudentsfile("students.txt", ios::app);
    if (addstudentsfile.fail()) {
        cout << "Error: Unable to open students.txt for appending" << endl;
        exit(-1);
    }

    string firstname, lastname, age, id, semester;
    string line;
    cout << "-Adding new student.\n" << "Enter name: ";
    cin >> firstname;
    cout << "\n-Enter surname: ";
    cin >> lastname;
    cout << "\n-Enter age: ";
    cin >> age;
    cout << "\n-Enter student's ID: ";
    cin >> id;
    cout << "\n-Enter the semester in which the student is currently in: ";
    cin >> semester;
    addstudentsfile <<endl<< firstname << ',' << lastname << ',' << age << ',' << semester<< ',' <<  id << endl;

    for (int i = 0; i < size; i++) {
        if (stoi(semester) - 1 == i) {
            Student* student=new Student(firstname, lastname, stoi(age), stoi(semester),id );
            semesters[i].AddStudent(student);
        }
    }

    addstudentsfile.close();
    readStudentsfile(semesters,8);
}

void deleteStudentfile(Academic_Semester* semesters,int size){
    string deleteStudentID;
    cout << "-Enter student's ID you wish to delete: ";
    cin >> deleteStudentID;

    ifstream studentfile("students.txt");
    if (!studentfile.is_open()) {
        cout << "-Error: Unable to open students.txt for reading" << endl;
        exit(-1);
    }

    ofstream tempFile("temp_students.txt");
    if (tempFile.fail()) {
        cout << "-Error: Unable to open temp_students.txt for writing" << endl;
        exit(-1);
    }

    bool found = false;
    string line;
    string firstname, lastname, age, id, semester;

    while (getline(studentfile, line)) {
        // Parse each line and check if the ID matches
        stringstream ss(line);
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        getline(ss, age, ',');
        getline(ss, semester, ',');
        getline(ss, id, ',');

        if (id == deleteStudentID) {
            // Found the student to delete
            found = true;
            cout << "-Student with ID " << deleteStudentID << " found and deleted." << endl;
        } else {
            // Write the non-matching student to the temporary file
            tempFile << line << endl;
        }
    }

    studentfile.close();
    tempFile.close();

    if (!found) {
        cout << "-Student with ID " << deleteStudentID << " not found." << endl;
    }

    // Remove the original file and rename the temporary file
    remove("students.txt");
    rename("temp_students.txt", "students.txt");
    readStudentsfile(semesters,8);
}

void modifyStudentfile(Academic_Semester* semesters,int size){
    string modifyStudentID;
    cout << "-Enter student's ID you wish to modify: ";
    cin >> modifyStudentID;

    ifstream studentfile("students.txt");
    if (!studentfile.is_open()) {
        cout << "-Error: Unable to open students.txt for reading" << endl;
        exit(-1);
    }

    ofstream tempStudentFile("temp_students.txt");
    if (tempStudentFile.fail()) {
        cout << "-Error: Unable to open temp_students.txt for writing" << endl;
        exit(-1);
    }

    bool studentFound = false;
    string studentLine;
    string line,firstname,lastname,age,id,semester;


    while (getline(studentfile, studentLine)) {
        // Parse each line and check if the ID matches
        stringstream ss(studentLine);
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        getline(ss, age, ',');
        getline(ss, semester, ',');
        getline(ss, id, ',');
        if(modifyStudentID==id){
            studentFound=true;
            cout << "-Enter 'N' to modify student's name, 'L' to modify student's last name,"
                     "'A' to modify student's age, 'I' to modify student's ID , 'S' to modify "
                      "student's semester.\n";
            char userinput;
            cin >> userinput;
            userinput=toupper(userinput);
            switch (userinput){
                case 'N':
                    cout << "-Enter student's new name: ";
                    cin >> firstname;
                    break;
                case 'L':
                    cout << "-Enter student's new last name: ";
                    cin >> lastname;
                    break;
                case 'A':
                    cout << "Enter student's new age: ";
                    cin >> age;
                    break;
                case 'I':
                    cout << "-Enter student's new ID: ";
                    cin >> id;
                    break;
                case 'S':
                    cout << "-Enter student's new semester: ";
                    cin >> semester;
                    break;
                default:
                    cout << "-Invalid input!";
                    break;
            }
            tempStudentFile << firstname << ',' << lastname << ',' << age << ',' << semester << ',' << id << endl;
        }
        else{
            tempStudentFile << studentLine << endl;
        }
    }

    studentfile.close();
    tempStudentFile.close();

    if (!studentFound) {
        cout << "-Student with ID " <<modifyStudentID << " not found." << endl;
    }

    // Remove the original file and rename the temporary file
    remove("students.txt");
    rename("temp_students.txt", "students.txt");
    readStudentsfile(semesters,size);
}

void CreatePassedStudentsfile(Academic_Semester* semesters,int size){
    ofstream passedStudentsFile("passed_students.txt");
    if (passedStudentsFile.fail()) {
        cout << "Error: Unable to open passed_students.txt for writing" << endl;
        exit(-1);
    }

    int semesternumber;
    do{
    cout << "Enter which semester's courses would you like to view(1-8)\n";
    cin >> semesternumber;
    if(semesternumber<1 || semesternumber>8){
        cout << "Invalid input please try again!\n";
    }
    }while(semesternumber<1 || semesternumber>8);

    // Display courses for selection
    
    int courseIndex = 1; // Initialize index for each semester
    cout << "Courses for Semester " << (semesternumber) << ":" << endl;
    semesters[semesternumber-1].PrintListCoursewithnumber(courseIndex);
    cout << endl; // Add a newline for better readability between semesters
                
    cout << "Please enter the course name to view the list of students who have successfully passed the course: ";
    string coursename;
    getline(std::cin >> std::ws, coursename);
    if(semesters[semesternumber-1].CheckIfCourseExists(coursename)){
        passedStudentsFile << "Students who passed the course \"" << coursename << "\" in Semester " << semesternumber << ":\n";
        for (const auto& student : semesters[semesternumber-1].GetStudents()) {
            if (student->HasPassedCourse(coursename)) {
                passedStudentsFile << student->Get_Name() << " " << student->Get_Surname() << " with ID " << student->Get_Id() << ": " << student->Get_CourseGrade(coursename) << endl;
            }
        }
        cout << "File with students who passed " << coursename << " succesfully created as passedStudentsFile.txt !\n";
    }
    else{
        cout << "Course not found in the selected semester.\n";
    }
    
    passedStudentsFile.close();
}

void deleteFile(const std::string& filename) {
    if (remove(filename.c_str()) == 0) {
        cout << "File deleted successfully: " << filename <<endl;
        
    } else {
        cerr << "Error deleting file: " << filename <<endl;
        
    }
}