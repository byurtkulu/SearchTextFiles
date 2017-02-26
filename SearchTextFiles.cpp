//
//  SearchTextFiles.cpp
//
//  Created by Bahadır Yurtkulu on 6.02.2017.
//  Copyright © 2017 Bahadir. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "strutils.h"

using namespace std;


//---------------------------------------------------------------------------------------

/* 
   Take one line from the text file and search the contents of the vectors one by one in this line.
   if found replace the ';' with ' ' and print out the line.
*/

void printOutEnrolledStudents (ifstream& studentList, const vector<string> studentIDs) {
    unsigned long found = 0;
    string line;

    while (getline(studentList, line)) {
        for (int i = 0; i < studentIDs.size(); i++) {
            found = line.find(studentIDs[i]);
            if (found != string::npos) {
                for (int k = 0; k < line.length(); k++) {
                    if (line[k] == ';') {
                        line[k] = ' ';
                    }
                }
                cout << line << '\n';
            }
        }
    }
    
}

//---------------------------------------------------------------------------------------


/*
    take given searchingStr which is 'course ID' and searh it line by line in the given file.
    if found, write the left hand side number, which is student id, into the vector.
*/
void FindEnrolledStuID (string searchingStr, ifstream& listFile, vector<string>&  EnrolledStudentID) {
    
    string line; // !!!! search after semicolon !!!!
    string stuID;
    unsigned long foundSemicolon;
    string sublineAfterSemi;
    while (getline(listFile, line)) {
        stuID = "";
        foundSemicolon = line.find(";");
        if (foundSemicolon != string::npos) {
            sublineAfterSemi = line.substr(foundSemicolon + 1);
            if (sublineAfterSemi == searchingStr) {
                stuID = line.substr(0, foundSemicolon);
                EnrolledStudentID.push_back(stuID);
            }
        }
    }
    
}


//---------------------------------------------------------------------------------------

/*
    Course name is given. Find course ID by searching the file line by line.
    If found, assign that to the id variable and return it.
*/
string FindCourseID(string searchingStr, ifstream& listFile) {
    string line;
    string temp = "";
    string id = "null";
    unsigned long foundSemicolon;
    string sublineAfterSemi;
    
    while (getline(listFile, line)) {
        ToLower(line);
        foundSemicolon = line.find(";");
        if (foundSemicolon != string::npos) {
            sublineAfterSemi = line.substr(foundSemicolon + 1);
            if (sublineAfterSemi == searchingStr) {
                id = line.substr(0, foundSemicolon);
            }
        }
    }
    if (id == "null") {
        cout << "No course found!" << '\n';
    }
    return id;
}


//========================================================================================

int main() {
    /*
     This program helps user to find out the students who are enrolled in to given the courses.
     Run it, then type the course name. Program will give you the students ids and names */
    
    /*====================================
     ============= OPEN FILES ============
     ====================================*/
    
    ifstream studentListFile;
    studentListFile.open("student.txt");
    
    if (studentListFile.fail()){
        cout << "Could not open student.txt" << '\n';
    }
    
    ifstream enrollmentListFile;
    enrollmentListFile.open("enrollment.txt");
    
    if (enrollmentListFile.fail()){
        cout << "Could not open the enrollment.txt" << '\n';
    }
    
    ifstream courseListFile;
    courseListFile.open("course.txt");
    
    if (courseListFile.fail()){
        cout << "Could not open the course.txt" << '\n';
    }
    
    /*=====================================
     ====== TAKE INPUT FROM THE USER ======
     =======   CALL THE FUNCTIONS   =======
     ======================================
     */
    cout << "Please enter the course name to see the students who are enrolled in: ";
    string courseName;
    cin >> courseName;
    string courseID;
    vector <string> EnrolledStudentsID;
    
    /*
     this vector is to store the student ids. 
     It is to be used later in FindEnrolledStuID and printOutEnrolledStudents funtions
     to provide necessery data.
    */
    
    
    courseID = FindCourseID(courseName, courseListFile);
    // finds the course ID.
    

    
    FindEnrolledStuID(courseID, enrollmentListFile, EnrolledStudentsID);
    // find ID of students who are enrolled the given course.

    
    printOutEnrolledStudents(studentListFile, EnrolledStudentsID);
    // print out the students' ID and names who are enrolled the given course.
    
    
    
    
    
    
    /*==================================
     ============ CLOSE FILES ==========
     ==================================*/
    
    studentListFile.close();
    enrollmentListFile.close();
    courseListFile.close();
    
    return 0;
}

