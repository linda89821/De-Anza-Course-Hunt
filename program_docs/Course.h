// Specification file for the Course class

#ifndef COURSE_H
#define COURSE_H

  
#include<string>

using std::string;
using std::ostream;

class Course; // Forward Declaration

// Function Prototypes for Overloaded Stream Operators
ostream &operator << (ostream &, const Course &);

class Course
{
    private:
        string crn;
        string title;
        string prof;
        string time;
        string sec;


    public:
        //constructors
        Course();
        Course(string, string);
        Course(string, string, string, string);
        Course(string, string, string, string, string);

        //setters
        void setCRN(string c){ crn = c;}
        void setTitle(string ttl){ title = ttl;}
        void setProf(string p){ prof = p;}
        void setTime(string tim){ time = tim;}
        void setSec(string s){ sec = s;}

        //getters
        string getCRN() const {return crn;}
        string getTitle() const {return title;}
        string getProf() const {return prof;}
        string getTime() const {return time;}
        string getSec() const {return sec;}
    

        //other functions if any
        void display()const;
    
        // overloaded operators
    bool operator<(const Course &rval) const {return rval.getTitle() > title;}
    bool operator>(const Course &rval) const {return rval.getTitle() < title;}
    bool operator==(const Course &rval) const {
		if (crn == "" || rval.getCRN() == "")
			return title == rval.getTitle();
		return (title == rval.getTitle()) && (rval.getCRN() == crn);
	}
    bool operator!=(const Course &rval) const { return rval.getCRN() != crn; }
      
        // Friends
        friend ostream &operator << (ostream &, const Course &);
};

#endif
