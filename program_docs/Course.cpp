 // Implementation file for the Course class

 #include <iostream>
 #include <iomanip>
 #include <string>   
 #include <vector>

 #include "Course.h"

 using namespace std;

 //**************************************************
 // Constructor
 //**************************************************
 Course::Course()
 {
     crn = "";
     title = "";
     prof = "";
     time = "";
     sec = "";
 }

 //**************************************************
 // Overloaded Constructor for bst
 //**************************************************
 Course::Course(string c, string ttl)
 {
     crn = c;
     title = ttl;
 }


 //**************************************************
 // Overloaded Constructor for stack and hash
 //**************************************************
 Course::Course(string c, string ttl, string p, string t, string s)
 {
     crn = c;
     title = ttl;
     prof = p;
     time = t;
     sec = s;
 }


 //**************************************************
 // Display function
 //**************************************************
 void Course::display() const
 {
     cout << "CRN: " << crn << endl
     << "Sec: " << sec << endl
     << "Title: " << title << endl
     << "Time: " << time << endl
     << "Name: " << prof << endl << endl;
 }

 //**************************************************
// ostream function
//**************************************************
 ostream& operator << (ostream& os, const Course& c)
 {
	 os << c.crn << " "
		 << c.sec << " "
		 << c.title << ";"
		 << c.time << ";"
		 << c.prof << endl;
	 return os;
 }

