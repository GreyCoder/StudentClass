/*Author:  Israel Cabello
  Course:  EE 3420
  Homework: 4
  Description:  This is a Program to perform the functions as described
                 in Homework 4*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>


using namespace std;
/*Class to use as an entry for a Student Record*/
class student{
    public:
        char FirstName[30];
        char LastName[30];
        float Test1;
        float Test2;
        float FinalExam;
        float CourseScore;
        char LetterGrade;

        /*constructor*/
        student();
        student(char FN[30], char LN[30], float T1, float T2, float FE);

        /*destructor*/
        ~student();
        /*copy constructor*/
        student(const student& p);
        /*comparison operators for class*/
        friend bool operator==(student &s1, student &s2);
        friend bool operator!=(student &s1, student &s2);
        friend bool operator>(student &s1, student &s2);
        friend bool operator<(student &s1, student &s2);
        friend bool operator>=(student &s1, student &s2);
        friend bool operator<=(student &s1, student &s2);
        /*calculate*/
        void calculate();

};

/*Default constructor that takes no input*/
student::student()
{
    char temp[] = "";
    strcpy(FirstName, temp);
    strcpy(LastName,temp);
    Test1 = 0;
    Test2 = 0;
    FinalExam = 0;
    CourseScore = 0;
    LetterGrade = 'F';

}

/*constructor that takes in FirstName, LastName, Test1, Test2 and FinalExam.
    It automatically calculates the CourseScore and LetterGrade*/
student::student(char FN[30], char LN[30], float T1, float T2, float FE)
{
    float min, max;
    strcpy(FirstName, FN);
    strcpy(LastName,LN);
    Test1 = T1;
    Test2 = T2;
    FinalExam = FE;
    if(Test1 > Test2)
        CourseScore = (Test1 * .35) + (Test2 * .25) + (FinalExam * .4);
    else
        CourseScore = (Test2 * .35) + (Test1 * .25) + (FinalExam * .4);
    if(CourseScore >= 90)
        LetterGrade = 'A';
    else if(CourseScore >= 80)
        LetterGrade = 'B';
    else if(CourseScore >= 70)
        LetterGrade = 'C';
    else if(CourseScore >= 60)
        LetterGrade = 'D';
    else
        LetterGrade = 'F';

}

/*method to recalculate a student score*/
void student::calculate()
{
    if(Test1 > Test2)
        CourseScore = (Test1 * .35) + (Test2 * .25) + (FinalExam * .4);
    else
        CourseScore = (Test2 * .35) + (Test1 * .25) + (FinalExam * .4);
    if(CourseScore >= 90)
        LetterGrade = 'A';
    else if(CourseScore >= 80)
        LetterGrade = 'B';
    else if(CourseScore >= 70)
        LetterGrade = 'C';
    else if(CourseScore >= 60)
        LetterGrade = 'D';
    else
        LetterGrade = 'F';
}

/*Destructor for student class*/
student::~student()
{
    char Null[] = "\0";
    strcpy(FirstName, Null);
    strcpy(LastName, Null);
    Test1 = 0;
    Test2 = 0;
    FinalExam = 0;
    CourseScore = 0;
    LetterGrade = '\0';
}

/*Copy Constructor for student class*/
student::student(const student& p)
{
    strcpy(FirstName, p.FirstName);
    strcpy(LastName, p.LastName);
    Test1 = p.Test1;
    Test2 = p.Test2;
    FinalExam = p.FinalExam;
    CourseScore = p.CourseScore;
    LetterGrade = p.LetterGrade;
}

/*Overloaded Operators for student class*/
bool operator==(student &s1, student &s2)
{
    return (
            !(strcmp(s1.FirstName, s2.FirstName)) &&
            !(strcmp(s1.LastName, s2.LastName)) &&
            s1.Test1 == s2.Test1 &&
            s1.Test2 == s2.Test2 &&
            s1.FinalExam == s2.FinalExam &&
            s1.CourseScore == s2.CourseScore &&
            s1.LetterGrade == s2.LetterGrade
            );
}

bool operator!=(student &s1, student &s2)
{
    return !(s1 == s2);
}

bool operator>(student &s1, student &s2)
{
    return (s1.CourseScore > s2.CourseScore);

}

bool operator<(student &s1, student &s2)
{
    return (s1.CourseScore < s2.CourseScore);

}

bool operator>=(student &s1, student &s2)
{
    return   (s1.CourseScore >= s2.CourseScore);


}

bool operator<=(student &s1, student &s2)
{
    return (s1.CourseScore <= s2.CourseScore);

}

/*The follwing function will populate a vector of student from a file
    Input: vector<student>*/
void getStudents(vector<student> &v1)
{
    char FirstName[30], LastName[30];
    float Test1, Test2, FinalExam;
    student temp;
    std::ifstream infile("students.txt");
    while(infile >> FirstName >> LastName >> Test1 >> Test2 >> FinalExam)
    {
        strcpy(temp.FirstName, FirstName);
        strcpy(temp.LastName, LastName);
        temp.Test1 = Test1;
        temp.Test2 = Test2;
        temp.FinalExam = FinalExam;
        temp.calculate();
        v1.push_back(temp);
    }
}

/*The follwing function will sort the student records
    Input: vector<student>*/
void sortStudents(vector<student> &v1)
{
    student temp;
    int i, j, flag =1;
    int numLength = v1.size();
    for(i = 1; (i <= numLength) && flag; i++)
    {
        flag = 0;
        for (j=0; j < (numLength -1); j++)
        {
            if (v1.at(j+1) < v1.at(j))      // ascending order
            {
                temp = v1.at(j);             // swap elements
                v1.at(j) = v1.at(j+1);
                v1.at(j+1) = temp;
                flag = 1;               // indicates that a swap occurred.
            }
        }
    }
}

/*The follwing function will output the Student Record to a file
    Input: vector<student>*/
void outputStudents(vector<student> &v1)
{
    std::ofstream outfile("studentsoutput.txt");
    for(int i = 0; i < v1.size(); i++)
    {
        outfile << v1.at(i).FirstName << "    " <<
        v1.at(i).LastName << "    " <<
        v1.at(i).CourseScore << "    " <<
        v1.at(i).LetterGrade << endl;

    }
}

int main(void)
{
    vector<student> Students;
    getStudents(Students);
    sortStudents(Students);
    outputStudents(Students);
    Students.clear();
    return 0;
}