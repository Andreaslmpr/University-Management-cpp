#include"handleprofessorfile.hpp"

void readProfessorsfile(Academic_Semester* semesters, int size) {
    ifstream professorfile("professors.txt");
    if (!professorfile.is_open()) {
        cout << "-Error: Unable to open professors.txt" << endl;
        exit(-1);
    }


    for (int i = 0; i < size; ++i) {
        semesters[i].ClearProfessors();
    }
    
    string line, firstname, lastname, age, id;

    while (getline(professorfile, line)) {
        stringstream ss(line);
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        getline(ss, age, ',');
        getline(ss, id, ',');

        // Create a new professor for each line of the file
        Professor* newProfessor = new Professor(firstname, lastname, id, stoi(age));
        // Add the professor to the current semester
        cout << "-Professor " << newProfessor->Get_Name() <<" "<<newProfessor->Get_Surname()<< " created" << endl;
        AddToAllProfessors(*newProfessor);//To add not only in the semester Vector but also in the AllProfessor
   }

    professorfile.close();
}


void appendProfessorsfile(Academic_Semester* semesters, int size) {
    ofstream addprofessorsfile("professors.txt", ios::app);
    if (addprofessorsfile.fail()) {
        cout << "-Error: Unable to open professors.txt for appending" << endl;
        exit(-1);
    }

    string firstname, lastname, age, id;
    cout << "-Adding new professor.\n" << "Enter name: ";
    cin >> firstname;
    cout << "\n-Enter surname: ";
    cin >> lastname;
    cout << "\n-Enter professors's ID: ";
    cin >> id;
    cout << "\n-Enter age: ";
    cin >> age;
    addprofessorsfile << firstname << ',' << lastname << ',' << id << ',' << age ;
    // Create a new professor for each line of the file
        Professor* newProfessor = new Professor(firstname, lastname, id, stoi(age));
        // Add the professor to the current semester
        cout << "-Professor " << newProfessor->Get_Name() <<" "<<newProfessor->Get_Surname()<< " created" << endl;
        AddToAllProfessors(*newProfessor);//To add not only in the semester Vector but also in the AllProfessor
    addprofessorsfile.close();
}


void deleteProfessorfile(){
     string deleteProfessorID;
    cout << "-Enter professor's ID you wish to delete: ";
    cin >> deleteProfessorID;

    ifstream professorfile("professors.txt");
    if (!professorfile.is_open()) {
        cout << "-Error: Unable to open professors.txt for reading" << endl;
        exit(-1);
    }

    ofstream tempProfessorFile("temp_professors.txt");
    if (tempProfessorFile.fail()) {
        cout << "-Error: Unable to open temp_professors.txt for writing" << endl;
        return exit(-1);
    }

    bool professorFound = false;
    string professorLine;
    string line,firstname,lastname,age,id;

    while (getline(professorfile, professorLine)) {
        // Parse each line and check if the ID matches
        stringstream ss(professorLine);
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        getline(ss, age, ',');
        getline(ss, id, ',');

        if (id == deleteProfessorID) {
            // Found the Professor to delete
            professorFound = true;
            Professor::RemoveProfessorByID(deleteProfessorID);
            cout << "-Professor with ID " << deleteProfessorID << " found and deleted." << endl;
        } else {
            // Write the non-matching professor to the temporary file
            tempProfessorFile << professorLine << endl;
        }
    }

    professorfile.close();
    tempProfessorFile.close();

    if (!professorFound) {
        cout << "-Professor with ID " << deleteProfessorID << " not found." << endl;
    }

    // Remove the original file and rename the temporary file
    remove("professors.txt");
    rename("temp_professors.txt", "professors.txt");
}

void modifyProfessorfile(Academic_Semester* semesters,int size){
    string modifyProfessorID;
    cout << "-Enter professor's ID you wish to modify: ";
    cin >> modifyProfessorID;

    ifstream professorfile("professors.txt");
    if (!professorfile.is_open()) {
        cout << "-Error: Unable to open professors.txt for reading" << endl;
        exit(-1);
    }

    ofstream tempProfessorFile("temp_professors.txt");
    if (tempProfessorFile.fail()) {
        cout << "-Error: Unable to open temp_professors.txt for writing" << endl;
        exit(-1) ;
    }

    bool professorFound = false;
    string professorLine;
    string line,firstname,lastname,age,id;

    while (getline(professorfile, professorLine)) {
        // Parse each line and check if the ID matches
        stringstream ss(professorLine);
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        getline(ss, age, ',');
        getline(ss, id, ',');

        if (id == modifyProfessorID) {
            // Found the Professor to delete
            professorFound = true;
            cout << "-Enter 'N' to modify professor's name, 'L' to modify professor's last name,"
                     "'A' to modify professor's age, 'I' to modify professor's ID\n";
            char userinput;
            cin >> userinput;
            userinput=toupper(userinput);
            switch (userinput){
                case 'N':
                    cout << "-Enter professor's new name";
                    cin >> firstname;
                    break;
                case 'L':
                    cout << "-Enter professor's last name";
                    cin >> lastname;
                    break;
                case 'A':
                    cout << "-Enter professor's new age";
                    cin >> age;
                    break;
                case 'I':
                    cout << "-Enter professor's new ID";
                    cin >> id;
                    break;
                default:
                    cout << "-Wrong input!";
                    break;
            }
            tempProfessorFile << firstname << ',' << lastname << ',' << age << ',' << id << endl;
        } 
        else {
            // Write the non-matching professor to the temporary file
            tempProfessorFile << professorLine << endl;
        }
    }

    professorfile.close();
    tempProfessorFile.close();

    if (!professorFound) {
        cout << "-Professor with ID " << modifyProfessorID << " not found." << endl;
    }

    // Remove the original file and rename the temporary file
    remove("professors.txt");
    rename("temp_professors.txt", "professors.txt");
    readProfessorsfile( semesters, size);
}