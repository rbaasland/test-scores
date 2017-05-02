/*
 * File: testScore.cpp
 * Author: Ronald Baasland
 *
 * Created on: December 1, 2010
 * Modified on: December 6, 2010
 *
 * This program reads students' names and their test scores from a data file and
 * and then outputs students' names and the test scores and the relevant grade
 * according to the alphabetical order of their last names. It also finds the
 * highest test score, and displays it.
 */

#include <iostream> //For input and output to the console
#include <fstream> //for input and output to a file
#include <iomanip> //for manipulating output
using namespace std;

//Student class declaration
class Student
{
private:
    string lname, fname; //Private data members for last name and first name
    int score; //Private data member to hold students score
    char grade; //Private data member to hold students letter grade
public:
    void setName(string ln, string fn); // Sets lastname, and first name
    void setScore(int sc); //Member function to set score
    void setGrade(int sc); // Member function to set letter grade
    string getLastName(); //Member function to return last name
    string getFirstName(); //Member function to return first name
    char getGrade(); // Member Funcion to return letter grade
    int getScore(); //Member Function to return score
    bool operator<(Student rhs); //Overloaded function for <
    bool operator=(Student rhs); //Overloaded function for =
    bool operator>(Student rhs); //Overloaded function for >
};

//Function protocols
void displayConsole(Student* s, int num);
void displayFile(Student * s, int num);
void findHighest(Student*, int numOfStudents);
void sortNames(Student* s, int num);

int main()
{
    ifstream infile; //Input stream to input from file
    ofstream outfile; // output stream to output to a file
    infile.open("grade.dat");
    outfile.open("prog3.out");
    int numOfStudents = 0; //numOfStudents is number of students in file

    if (infile)
    {
        infile >> numOfStudents; //Inputs the first line from the file which 
    }                            // contains the number of students
    Student* stdPtr; //Creates a pointer for an instance of the Student class
    stdPtr = new Student[numOfStudents]; // Points stdPtr to a new dynamic
                                         //instance of student

    if (infile) //If there is data in the file
    {
        for (int s = 0; s < numOfStudents; s++)
        {
            string ln, fn;
            int sc = 0;
            infile >> fn >> ln >> sc; //Inputs firstname, lastname, and score 
            //Assigns inputted data to the Student class for each student
            stdPtr[s].setName(ln,fn);
            stdPtr[s].setScore(sc);
            stdPtr[s].setGrade(sc);
        }
    }

    sortNames(stdPtr, numOfStudents); // Function call to sort the students 

    displayConsole(stdPtr, numOfStudents); //Function call to output to console
    displayFile(stdPtr, numOfStudents); //Function call to output to file

    infile.close(); // Closes grade.dat
    outfile.close(); //Closes prog3.out

    return 0;
}

//member function setScore
void Student::setScore(int sc)
{
    score = sc; // sets score to sc
}

//Member function setName
void Student::setName(string ln, string fn)
{
    lname = ln; // Sets lname to ln
    fname = fn; // Sets fname to fn
}

//member function setGrade, sets letter grade according to score
void Student::setGrade(int sc)
{
    if (sc >= 90 && sc<= 100)
        grade = 'A';
    else if (sc >= 80 && sc<= 89)
        grade = 'B';
    else if (sc >= 70 && sc<= 79)
        grade = 'C';
    else if (sc >= 60 && sc<= 69)
        grade = 'D';
    else if (sc >= 0 && sc <= 59)
        grade = 'F';
    else
        grade = 'I';
}

//Member function to return last name
string Student::getLastName()
{
    return lname;
}

//Member function to return first name
string Student::getFirstName()
{
    return fname;
}

//Member function to return letter grade
char Student::getGrade()
{
    return grade;
}

//Member function to return score
int Student::getScore()
{
    return score;
}

//member function to overload the < operator
bool Student::operator <(Student rhs)
{
    if (lname < rhs.lname)
    {
        return true;
    }
    else if (lname == rhs.lname)
    {
        if (fname < rhs.fname)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

//Member function to overload the > operator
bool Student::operator >(Student rhs)
{
    if (lname > rhs.lname)
    {
        return true;
    }
    else if (lname == rhs.lname)
    {
        if (fname > rhs.fname)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

//member function to overload the = operator
bool Student::operator=(Student rhs)
{
    lname = rhs.lname;
    fname = rhs.fname;
    grade = rhs.grade;
    score = rhs.score;
}

void displayConsole(Student* s, int num)
{
    int nameWidth; //Variable to help align data into columns
    //Header for output
    cout << "--------------------------------------------" << endl;
    cout << "Student Name" << setw(12) << "Score" << setw(10) << "Grade" << endl;
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < num; i++)
    {
        nameWidth = s[i].getLastName().size() + s[i].getFirstName().size();//used to make columns
        nameWidth = 20 - nameWidth;
        cout << s[i].getLastName() << ", " << s[i].getFirstName() << setw(nameWidth) << s[i].getScore() << setw(10) << s[i].getGrade();

        //Finds out if grade is invalid
        if (s[i].getGrade() == 'I')
        {
            cout << " Invalid Test Score!" << endl;
        }
        else
        {
            cout << endl;
        }

        nameWidth = 0;
    }
    cout << "--------------------------------------------" << endl << endl;
    findHighest(s,num); // Function call to find highest grade
}

void displayFile(Student* s, int numOfStudents)
{
    ofstream outfile;
    outfile.open("prog3.out");
    int nameWidth;
    outfile << "--------------------------------------------" << endl;
    outfile << "Student Name" << setw(12) << "Score" << setw(10) << "Grade" << endl;
    outfile << "--------------------------------------------" << endl;
    for (int i = 0; i < numOfStudents; i++)
    {
        nameWidth = s[i].getLastName().size() + s[i].getFirstName().size();
        nameWidth = 20 - nameWidth;
        outfile << s[i].getLastName() << ", " << s[i].getFirstName() << setw(nameWidth) << s[i].getScore() << setw(10) << s[i].getGrade();
        if (s[i].getGrade() == 'I')
        {
            outfile << " Invalid Test Score!" << endl;
        }
        else
        {
            outfile << endl;
        }

        nameWidth = 0;
    }
    outfile << "--------------------------------------------" << endl << endl;

    Student* stdPtr2; // Student class pointer
    stdPtr2 = new Student[6]; //Makes a new instance of Student for stdPtr2 to point at
    int highest = s[0].getScore(); //Sets the first element in s to highest

    /*
     * This for loop evaluates the students last names, and then places them in
     * alphabetical order. If they have the same last name, then it will sort
     * the names by first name.
     */
    for (int i = 0; i < numOfStudents; i++)
    {
        if (s[i].getScore() >= highest && s[i].getScore() <= 100)
        {
            highest = s[i].getScore();
            stdPtr2[0].operator =(s[i]);
        }

    }
    int num = 0;
    //This for loop looks for multiple people with the same high score
    for (int i = 0; i < numOfStudents; i++)
    {
        if (s[i].getScore() == highest)
        {
            stdPtr2[num].operator =(s[i]);
            num++;
        }

    }

    outfile << "The students with the highest grades are:" << endl << endl;

    for (int i = 0; i < num; i++)
    {
        nameWidth = stdPtr2[i].getLastName().size() + stdPtr2[i].getFirstName().size();;
        nameWidth = 20 - nameWidth;
        outfile << stdPtr2[i].getLastName() << ", " << stdPtr2[i].getFirstName() << setw(nameWidth) << stdPtr2[i].getScore() << setw(10) << stdPtr2[i].getGrade() << endl;
        nameWidth = 0;
    }
    cout << endl;
}

void findHighest(Student* s, int numOfStudents)
{
    ofstream outfile;
    outfile.open("prog3.out");
    Student* stdPtr2;
    stdPtr2 = new Student[6];
    int highest = s[0].getScore();

    for (int i = 0; i < numOfStudents; i++)
    {
        if (s[i].getScore() >= highest && s[i].getScore() <= 100)
        {
            highest = s[i].getScore();
            stdPtr2[0].operator =(s[i]);
        }

    }
    int num = 0;
    for (int i = 0; i < numOfStudents; i++)
    {
        if (s[i].getScore() == highest)
        {
            stdPtr2[num].operator =(s[i]);
            num++;
        }

    }

    cout << "The students with the highest grades are:" << endl << endl;
    int nameWidth;
    for (int i = 0; i < num; i++)
    {
        nameWidth = stdPtr2[i].getLastName().size() + stdPtr2[i].getFirstName().size();
        nameWidth = 20 - nameWidth;

        cout << stdPtr2[i].getLastName() << ", " << stdPtr2[i].getFirstName() << setw(nameWidth) << stdPtr2[i].getScore() << setw(10) << stdPtr2[i].getGrade() << endl;
        nameWidth = 0;
    }
    cout << endl;
}

//This function sorts elements in student class according to last name
void sortNames(Student* s, int num)
{
    bool swap;
    Student temp;
    int bottom = num - 1;

    do
    {
        swap = false;
        for (int count = 0; count < bottom; count++)
        {
            if (s[count].operator >(s[count + 1])) //Overloaded operator to see if last name falls before
            {
                temp = s[count];
                s[count] = s[count + 1];
                s[count + 1] = temp;
                swap =true;
            }
        }
        bottom--;
    } while (swap!= false);
}