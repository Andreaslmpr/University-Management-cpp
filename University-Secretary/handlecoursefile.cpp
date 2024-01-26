#include"handlecoursefile.hpp"

void readCoursesfile(Academic_Semester* semesters, int size){
    ifstream coursefile("courses.txt");
    if (!coursefile.is_open()) {
        cout << "Error: Unable to open courses.txt" << endl;
        exit(-1);
    }

   for (int i = 0; i < size; ++i) {
        semesters[i].ClearCourses();
    }

    string  line, lessonname, semesterStr, ects, mandatory;
    bool finalmandatory;

    while (getline(coursefile, line)) {
        stringstream ss(line);
        getline(ss, lessonname, ',');
        getline(ss, semesterStr, ',');
        getline(ss, ects, ',');
        getline(ss, mandatory, ',');

        if (mandatory == "True" || mandatory == "true") {
            finalmandatory = true;
        } else if (mandatory == "False" || mandatory == "false") {
            finalmandatory = false;
        }

        for (int i = 0; i < 8; i++) {
            if (stoi(semesterStr) - 1 == i) {
                Course* course= new Course(lessonname, stoi(semesterStr), stoi(ects), finalmandatory);
                semesters[i].AddCourse(course);
            }
        }
    }

    coursefile.close();
}

void appendCoursesfile(Academic_Semester* semesters, int size){
    ofstream addcoursesfile("courses.txt", ios::app);

    if(addcoursesfile.fail()){
        cout << "Error: Unable to open courses.txt for appending" << endl;
        exit(-1);
    }

    string  line, lessonname, semester, ects, mandatory;
    bool finalmandatory;

    cout << "Adding new course.\n" << "Enter course name: " ;
    cin >> lessonname;
    cout << "\nEnter course's semester: ";
    cin >> semester;
    cout << "\nEnter course's ECTS: ";
    cin >> ects;
    cout << "\nEnter True if course is mandatory or False if not: ";
    cin >> mandatory;
    addcoursesfile <<endl<< lessonname << ',' << semester << ',' << ects << ',' << mandatory << endl;

    if (mandatory == "True" || mandatory == "true") {
            finalmandatory = true;
    } 
    else if (mandatory == "False" || mandatory == "false") {
            finalmandatory = false;
    }
    for (int i = 0; i < 8; i++) {
        if (stoi(semester) - 1 == i) {
            semesters[i].AddCourse(new Course(lessonname, stoi(semester), stoi(ects), finalmandatory));
        }
    }

    addcoursesfile.close();
}

void deleteCoursesfile(Academic_Semester* semesters, int size) {
    string courseToDelete;
    cout << "Enter the name of the course you want to delete: ";
    cin >> courseToDelete;

    for (int i = 0; i < 8; i++) {
        vector<Course*>& coursesInSemester = const_cast<vector<Course*>&>(semesters[i].GetCourses());
        auto it = coursesInSemester.begin();

        while (it != coursesInSemester.end()) {
            if ((*it)->GetCourseName() == courseToDelete) {
                cout << "Course " << courseToDelete << " found in Semester " << (i + 1) << " and deleted." << endl;
                delete *it;  // Delete the Course object
                it = coursesInSemester.erase(it);
                break;
            } else {
                ++it;
            }
        }
    }

    // Write the updated courses back to the file
    ofstream coursefileOut("courses.txt");
    if (!coursefileOut.is_open()) {
        cout << "Error: Unable to open courses.txt for writing" << endl;
        exit(-1);
    }

    for (int i = 0; i < 8; i++) {
        const vector<Course*>& coursesInSemester = semesters[i].GetCourses();
        for (const Course* coursePtr : coursesInSemester) {
            coursefileOut << coursePtr->GetCourseName() << ',' << coursePtr->GetCourseSemester() << ','
                           << coursePtr->GetEcts() << ',' << (coursePtr->IsMandatory() ? "True" : "False") << '\n';
        }
    }

    coursefileOut.close();
}


void modifyCoursesfile(Academic_Semester* semesters,int size){
    string modifyCourseName;
    cout << "Enter course's name you wish to modify: ";
    cin >> modifyCourseName;

    ifstream coursefile("courses.txt");
    if (!coursefile.is_open()) {
        cout << "Error: Unable to open courses.txt for reading" << endl;
        exit(-1);
    }

    ofstream tempCourseFile("temp_courses.txt");
    if (tempCourseFile.fail()) {
        cout << "Error: Unable to open temp_courses.txt for writing" << endl;
        exit(-1);
    }

    bool courseFound = false;
    string courseLine;
    string lessonname, semesterStr, ects, mandatory;

    while (getline(coursefile, courseLine)) {
        // Parse each line and check if the name matches
        stringstream ss(courseLine);
        getline(ss, lessonname, ',');
        getline(ss, semesterStr, ',');
        getline(ss, ects, ',');
        getline(ss, mandatory, ',');
        if(modifyCourseName==lessonname){
            courseFound=true;
            cout << "Enter 'N' to modify course's name, 'S' to modify course's semester,"
                     "'E' to modify courses's ECTS, 'M' to modify student's mandate\n";
            char userinput;
            cin >> userinput;
            userinput=toupper(userinput);
            switch (userinput){
                case 'N':
                    cout << "Enter course's new name: ";
                    cin >> lessonname;
                    break;
                case 'S':
                    cout << "Enter course's new semester: ";
                    cin >> semesterStr;
                    break;
                case 'E':
                    cout << "Enter course's new ECTS: ";
                    cin >> ects;
                    break;
                case 'M':
                    cout << "Enter course's new mandate: ";
                    cin >> mandatory;
                    break;
                default:
                    cout << "Wrong input! Exiting modification: ";
                    break;
            }
            tempCourseFile << lessonname << ',' << semesterStr << ',' << ects << ',' << mandatory << endl;
        }
        else{
            tempCourseFile << courseLine << endl;
        }
    }

    coursefile.close();
    tempCourseFile.close();

    if (!courseFound) {
        cout << "Course with name " << modifyCourseName << " not found." << endl;
    }

    // Remove the original file and rename the temporary file
    remove("courses.txt");
    rename("temp_courses.txt", "courses.txt");
    readCoursesfile(semesters,size);
}

void underlinetext(const std::string& text) {
    // Print the text
    cout << text ;
    cout<<endl;
    // Print the underline
    for (size_t i = 0; i < text.length(); ++i) {
        cout << '-';
    }
    
}