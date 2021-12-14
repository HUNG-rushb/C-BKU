// Fig. 3.17: fig03_16.cpp
// Create and manipulate a GradeBook object; illustrate validation.
#include <iostream>
#include "GradeBook.h" // include definition of class GradeBook
using namespace std;

// function main begins program execution
int main()
{
     // create two GradeBook objects;
     // initial course name of gradeBook1 is too long
     string course;
     string instructor;

     getline(cin, course);
     getline(cin, instructor);

     GradeBook gradeBook1(course, instructor);
     GradeBook gradeBook2("CS102 C++ Data Structures", "Nguyen Thi Duyen Bang");

     // display each GradeBook's courseName
     cout << "gradeBook1's initial course name is: "
          << gradeBook1.getCourseName()
          << "\ngradeBook2's initial course name is: "
          << gradeBook2.getCourseName() << endl;

     // modify myGradeBook's courseName (with a valid-length string)
     gradeBook1.setCourseName("CS101 C++ Programming");

     // display each GradeBook's courseName
     cout << "\ngradeBook1's course name is: "
          << gradeBook1.getCourseName()
          << "\ngradeBook2's course name is: "
          << gradeBook2.getCourseName() << endl;

    gradeBook1.displayMessage();
    gradeBook2.displayMessage();
} // end main
