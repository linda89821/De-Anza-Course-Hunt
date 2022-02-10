// CIS 22C Team 2 project
// Computer Science 2020 spring courses
// De Anza Community College Database


#include "BinarySearchTree.h"  // BST ADT
#include "HashTable.h"
#include "StackADT.h"
#include "Course.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>


using namespace std;


void hDisplay(Course &);
void vDisplay(Course &);
void iDisplay(Course &, int);
void buildList(const string &, BinarySearchTree<Course> &list, HashTable<Course> &hash);
void searchCRNManager(const HashTable<Course> &hash, BinarySearchTree<Course> &list);
void searchTitleManager(const HashTable<Course> &hash, BinarySearchTree<Course> &list);
int countNumLines(string filename);
void capitalize (string &s);
int keyToIndex(const Course& key, int size);
void undoDelete(Stack<Course> &stack, HashTable<Course> &hash, BinarySearchTree<Course> &list);
void displayWelcomeMessage();
void displayMenuMessage();
void displayFarewell();
void addNewCourse(HashTable<Course> &hash, BinarySearchTree<Course> &list);
void deleteManager(HashTable<Course> &hash, BinarySearchTree<Course> &list, Stack<Course> &stack);
void statistics(HashTable<Course> &hash);
void writeToFile(string filename,BinarySearchTree<Course> &bst, HashTable<Course> &hash);
void displayAllCourse(BinarySearchTree<Course> &bst, HashTable<Course> &hash);

int main()
{
    string filename = "Course.txt";
    string outfile = "Result.txt";
    string course, crn, title, prof, time, sec;
	BinarySearchTree<Course> bst;
    HashTable<Course> hash;
    Stack<Course> stack;
    
    cout << "\n Reading text file Course.txt" << endl << endl;
    displayWelcomeMessage();
    buildList(filename, bst, hash);
    char choice;
    
	// Display the menu.
	displayMenuMessage();

    do
    {
		cout << "\nEnter your choice: ";
        cin  >> choice;
        switch (choice)
        {
            case '1':
            {
                addNewCourse(hash, bst);
                break;
            }
            case '2':
            {
                deleteManager(hash, bst, stack);
                break;
            }
                
            case '3':
            {
                searchCRNManager(hash, bst);
                break;
            }
            
            case '4':
            {
                searchTitleManager(hash, bst);
                break;
            }
                
            case '5':
            {
                displayAllCourse(bst, hash);
                break;
            }
             
            /**hidden option, print indent tree*/
            case '6':
            {
                cout << "Your choice is the \"display the tree\": \n\n";
                bst.printTree(iDisplay);
                break;
            }
            
            /**To show the menu again*/
            case '7':
            case 'H':
            case 'h':
            {
                displayMenuMessage();
                break;
            }
                
            /**To undo the delete*/
            case '8':
            {
                undoDelete(stack, hash, bst);
                break;
            }
            
            /**Statistics*/
            case '9':
            {
                statistics(hash);
                break;
            }
            
            /**Hidden option: display the names of the team member*/
            case 'D':
            case 'd':
            {
                cout << "Your choice is the \"Hidden option\": \n\n";
                cout << " Team members' name:\n"
                << " Chih-Lin, Wang\n"
                << " Zijun, Ye\n"
                << " Yonglin, Liang\n"
                << " Shi-Chih, Han\n";
                break;
            }
                
        } // end switch
    
    }while (toupper(choice) != 'Q');

    //writing data to the output file
    cout <<"writing to file.....";
    writeToFile(outfile, bst, hash);
    
    //print the farewell
    displayFarewell();
    
    return 0;

}


/*****************************************************************************
 This function reads data about colleges from a file and inserts them
 into a sorted linked list. The list is sorted in ascending order by code
 *****************************************************************************/

void buildList(const string &filename, BinarySearchTree<Course> &list, HashTable<Course> &hash)
{
    ifstream fin(filename);
    int numLines = countNumLines(filename);
    hash.reHash(numLines * 2, keyToIndex);

    string crn;
    string sec, title, time, name;
    string line;
    while(fin >> crn)
    {
        fin >> sec;
        fin.ignore();
        getline(fin, title, ';');
        capitalize(title);
        getline(fin, time, ';');
        getline(fin, name, '\n');
        // create a Course object for bst and initialize it with data from file
        Course bCourse(crn, title);
        list.insert(bCourse);
        Course aCourse(crn, title, name, time, sec);
        hash.insert(aCourse, keyToIndex);
    }

    fin.close();
}

/*****************************************************************************
 Search CRN manager: search the list until the user enters Q to quit searching
 Input Parameter: list, hash
 *****************************************************************************/

void searchCRNManager(const HashTable<Course> &hash, BinarySearchTree<Course> &list)
{
    string targetCode = "";
    Course aCourse;
    Course bCourse;

    cout << "Your choice is the \"Search and display course by CRN\": \n\n";
    cout << "\n Search\n";
    cout <<   "=======\n";
    

    while(toupper(targetCode[0]) != 'Q')
    {
        cout << "\nEnter a course CRN (or Q to stop searching) \n";
        
        if(toupper(targetCode[0]) != 'Q')
        {
            Course target;

            bool test_crn = true;
            while (test_crn) {
                test_crn = false;
                cout << "CRN: ";
                cin >> targetCode;
                for (int i = 0; i < targetCode.length(); i++) {
                    if (!isdigit(targetCode[i]))
                    {
                        cout << "Please enter a valid CRN number" << endl;
                        test_crn = true;
                        break;
                    }
                }
            }
             
            target.setCRN(targetCode);
            if(hash.search(aCourse, target, keyToIndex) != -1)
            {
                aCourse.display();
            }
            else
                cout << "Course \"" << targetCode << "\" was not found in this list." << endl;
        }
    }
    cout << "___________________END SEARCH SECTION _____\n";
}


/*****************************************************************************
 Search Title manager: search the list until the user enters Q to quit searching
 Input Parameter: list, hash
 *****************************************************************************/
void searchTitleManager(const HashTable<Course> &hash, BinarySearchTree<Course> &list)
{
    string targetCode = "";
    Course aCourse;

    cout << "Your choice is the \"Search course by Title\": \n\n";
    cout << "\n Search\n";
    cout <<   "=======\n";

    while(toupper(targetCode[0]) != 'Q')
    {
        if(targetCode == "")
            cin.ignore();
        cout << "\nEnter a course title (or Q to stop searching) :" << endl;
        getline(cin, targetCode, '\n');
        cout << endl;
        if(toupper(targetCode[0]) != 'Q')
        {
            Course target;
            capitalize(targetCode);
			vector<Course> matchCourses;
            target.setTitle(targetCode);
			cout << target.getTitle() << endl;
            list.search(target, matchCourses);
			if (!matchCourses.empty())
			{
				for (auto& target : matchCourses) {
					if (hash.search(aCourse, target, keyToIndex) != -1) {
						aCourse.display();
					}
				}
			}
            else
                cout << "Course \"" << targetCode << "\" was not found in this list." << endl;
        }
    }
    cout << "___________________END SEARCH SECTION _____\n";
}

/*****************************************************************************
hDisplay : display the course list
Input Parameter: list
*****************************************************************************/
void hDisplay (Course &item)
{
     cout << item.getCRN();
       cout << "  " << left << setw(5) << item.getSec();
       cout << left << setw(25) << item.getTime();
       cout << left << setw(74) << item.getTitle();
       cout << left << setw(37) << item.getProf();
       cout << endl;
}


/*****************************************************************************
iDisplay : one item per line, including the level number
Input Parameter: Course item, level
*****************************************************************************/
void iDisplay(Course &item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item.getCRN() << "  " << item.getTitle() << endl;
    
}

/*****************************************************************************
countNumLines : calculate the number of lines in the input file
Input Parameter: filename
*****************************************************************************/
int countNumLines(string filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "Error opening the input file: \"" << filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    int count = 0;
    string line;
    while (!fin.eof())
    {
        getline(fin, line, '\n');
        count++;
    }

    fin.close();
    return count;
}

/*****************************************************************************
keyToIndex : hash function take the key and return the index to hash table
Input Parameter: stack, &hash, &list
*****************************************************************************/
int keyToIndex(const Course& key, int size) {
    int k = stoi(key.getCRN());
    return k % size;
}

/*****************************************************************************
undoDelete : undo the delete part
Input Parameter: stack, &hash, &list
*****************************************************************************/
void undoDelete(Stack<Course> &stack, HashTable<Course> &hash, BinarySearchTree<Course> &list)
{
    Course sCourse;
    Course bCourse("", "");
    Course hCourse("", "", "" , "", "");
    cout << "Your choice is the \"Undo Delete\": \n\n";
    cout << "Undo delete:\n";
    while(! stack.isEmpty())
    {
        stack.pop(sCourse);
        bCourse.setCRN(sCourse.getCRN());
        bCourse.setTitle(sCourse.getTitle());
        hCourse.setCRN(sCourse.getCRN());
        hCourse.setTitle(sCourse.getTitle());
        hCourse.setProf(sCourse.getProf());
        hCourse.setSec(sCourse.getSec());
        hCourse.setTime(sCourse.getTime());
        list.insert(bCourse);
        hash.insert(hCourse, keyToIndex);
        cout << sCourse.getCRN() << endl;
    }
}

/*****************************************************************************
capitalize : capitalize the string
Input Parameter: string
*****************************************************************************/
void capitalize (string &s)
{
    bool cap = true;

    for(unsigned int i = 0; i <= s.length(); i++)
    {
        if (isalpha(s[i]) && cap == true)
        {
            s[i] = toupper(s[i]);
            cap = false;
        }
        else if (isspace(s[i]))
        {
            cap = true;
        }
    }
}

/*****************************************************************************
addNewCourse : adding the new course into hash and bst
Input Parameter: hash and bst
*****************************************************************************/
void addNewCourse(HashTable<Course> &hash, BinarySearchTree<Course> &list)
{
    string crn, time, sec, prof, course;
    Course tCourse(crn, course, prof, time, sec);
    Course target;
    cout << "Your choice is the \"Add new course\": \n\n";
    bool test_crn = false;
    while (!test_crn)
    {
        test_crn = true;
        cout << "CRN: ";
        cin >> crn;
        for (int i = 0; i < crn.length(); i++)
        {
            if (!isdigit(crn[i]))
            {
                cout << "Please enter a valid CRN number" << endl;
                test_crn = false;
                break;
            }
        }
        if (test_crn == true) {
         target.setCRN(crn);
         if (hash.search(tCourse, target, keyToIndex) != -1)
         {
          cout << "Replicate CRN. CRN should be a unique number." << endl;
          test_crn = false;
         }
        }
    }
    cin.ignore();
    cout << "Course: ";
    getline(cin, course);
    capitalize(course);
    cout << "Time: ";
    cin >> time;
    cout << "Section: ";
    cin >> sec;
    cin.ignore();
    cout << "Professor: ";
    getline(cin, prof);
    Course aCourse(crn, course, prof, time, sec);
    Course bCourse(crn, course);
    list.insert(bCourse);
    hash.insert(aCourse, keyToIndex);
}


/*****************************************************************************
deleteManager: delete the course in the hash and bst
Input Parameter: hash, bst, and stack
*****************************************************************************/
void deleteManager(HashTable<Course> &hash, BinarySearchTree<Course> &list, Stack<Course> &stack)
{
    string crn, time, sec, prof, course;
    Course tCourse(crn, course, prof, time, sec);
    Course target;
    cout << "Your choice is the \"Delete course\": \n\n";
    bool test_crn = true;
    while (test_crn) {
        test_crn = false;
        cout << "Delete CRN: ";
        cin >> crn;
        for (int i = 0; i < crn.length(); i++) {
            if (!isdigit(crn[i]))
            {
                cout << "Please enter a valid CRN number" << endl;
                test_crn = true;
                break;
            }
        }
    }
    Course aCourse(crn, "");
    Course bCourse;
    if (hash.search(bCourse, aCourse, keyToIndex) != -1) {
        Course cCourse("", "");
        Course dCourse;
        if (list.remove(bCourse, cCourse) && hash.remove(dCourse, bCourse, keyToIndex))
        {
            cout << crn << " has been deleted" << endl;
            Course sCourse(cCourse.getCRN(), cCourse.getTitle(), bCourse.getProf(), bCourse.getTime(), bCourse.getSec());
            stack.push(sCourse);
        }
    }
    else
        cout << crn << " has not found" << endl;
}


/*****************************************************************************
statistics : display the statistics in the hash table
Input Parameter: hash
*****************************************************************************/
void statistics(HashTable<Course> &hash)
{
    cout << " Loading factor: " << hash.getLoadFactor() << endl
    << " Collision count: " << hash.getTotalCollision() << endl
    << " Longest collision path: " << hash.getLongestCollisions() << endl;
}

/*****************************************************************************
displayMenuMessage : display the menu
Input Parameter: none
*****************************************************************************/
void displayMenuMessage()
{
	cout << "\n==================================================="
		<< "\n||  De Anza CIS 2020 spring courses information  ||\n"
		<< "||-----------------------------------------------||\n"
		<< "||  1. Add new course                            ||\n"
		<< "||  2. Delete course                             ||\n"
		<< "||  3. Search course by CRN                      ||\n"
		<< "||  4. Search course by Title                    ||\n"
		<< "||  5. Display all course                        ||\n"
		<< "||  6. Hidden print option                       ||\n"
		<< "||  7. Enter an option (H - for help)            ||\n"
		<< "||  8. Undo delete                               ||\n"
		<< "||  9. Statistics                                ||\n"
		<< "||  D. Hidden option                             ||\n"
		<< "||  Q. End program                               ||\n"
		<< "===================================================\n";
}

/*****************************************************************************
displayWelcomeMessage : display the welcome message
Input Parameter: none
*****************************************************************************/
void displayWelcomeMessage()
{
    cout << "========Welcome to CIS course schedule program=============" << endl;
    cout << "This program can help you to add, delete, search courses OvO" << endl;
}

/*****************************************************************************
displayFarewell : display the farewell message
Input Parameter: none
*****************************************************************************/
void displayFarewell()
{
    cout << "This is the end of the program QAQ" << endl
    << "See you next time! OuO" << endl;
    cout << "~Wish you to open this program again~ o(≥V≤)o" << endl;
}

/*****************************************************************************
writeToFile : write data to file.
Input Parameter: file name, bst, hash.
*****************************************************************************/
void writeToFile(string filename,BinarySearchTree<Course> &bst, HashTable<Course> &hash)
{
    ofstream outFile;
    
    outFile.open(filename.c_str());
    vector<Course> aCourse;
    bst.printAll(aCourse);
    for (int i = 0; i < aCourse.size(); i++) {
        Course target, dCourse;
        target.setCRN(aCourse[i].getCRN());
        if (hash.search(dCourse, target, keyToIndex) != -1)
        {
            outFile << dCourse;
        }
    }
    
    outFile.close();
}

/*****************************************************************************
displayAllCourse :  display all the Course in input file
Input Parameter: bst , hash.
*****************************************************************************/
void displayAllCourse(BinarySearchTree<Course> &bst, HashTable<Course> &hash)
{
    cout << "Your choice is the \"Display all course\": \n\n";
    cout << "==============================================="
    << "===================================================="
    << "================================\n";
    cout << left << setw(7) << "CRN";
    cout << left << setw(10) << "Sec";
    cout << left << setw(37) << "Time";
    cout << left << setw(57) << "Title" << " ";
    cout << "Professor" << endl;
    cout << "-----------------------------------------------"
    << "----------------------------------------------------"
    << "--------------------------------\n";
    vector<Course> aCourse;
    bst.printAll(aCourse);
    for (int i = 0; i < aCourse.size(); i++) {
        Course target, dCourse;
        target.setCRN(aCourse[i].getCRN());
        if (hash.search(dCourse, target, keyToIndex) != -1)
        {
            hDisplay(dCourse);
        }
    }
}
