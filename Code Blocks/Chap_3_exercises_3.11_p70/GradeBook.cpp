// Fig. 3.16: GradeBook.cpp
// Implementations of the GradeBook member-function definitions.
// The setCourseName function performs validation.
#include <iostream>
#include "GradeBook.h" // include definition of class GradeBook
using namespace std;

// constructor initializes courseName with string supplied as argument
GradeBook::GradeBook(string c_name, string i_name)
{
   setCourseName(c_name); // validate and store courseName
   setInstructorName(i_name);
} // end GradeBook constructor

// function that sets the course name;
// ensures that the course name has at most 25 characters
void GradeBook::setCourseName(string name)
{
   if (name.length() <= 25) // if name has 25 or fewer characters
      courseName = name;    // store the course name in the object

   if (name.length() > 25) // if name has more than 25 characters
   {
      // set courseName to first 25 characters of parameter name
      courseName = name.substr(0, 25); // start at 0, length of 25

      cout << "Name \"" << name << "\" exceeds maximum length (25).\n"
           << "Limiting courseName to first 25 characters.\n"
           << endl;
   } // end if
} // end function setCourseName

// function to get the course name
string GradeBook::getCourseName()
{
   return courseName; // return object's courseName
} // end function getCourseName


void GradeBook::setInstructorName(string name)
{
    instructorName = name;
}

string GradeBook::getInstructorName()
{
    return instructorName;
}


// display a welcome message to the GradeBook user
void GradeBook::displayMessage()
{
   // call getCourseName to get the courseName
   cout << "Welcome to the grade book for\n"
        << getCourseName()
        << "\nThis course is presented by: "
        << getInstructorName()
        << "!" << endl;
} // end function displayMessage


