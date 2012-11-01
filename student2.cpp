#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>


using namespace std;

int main(void)
{
    //array variables to store student records max students is 1000
    char fname[1000][30];
    char lname[1000][30];
    float t1[1000];
    float t2[1000];
    float fe[1000];
    float score[1000];
    char grade[1000];
    //temporary variables to do the bubble sort
    char tempfname[30];
    char templname[30];
    float tempt1;
    float tempt2;
    float tempfe;
    float tempscore;
    char tempgrade;

    std::ifstream input("students.txt");
    int length = 0;
    //Read File into arrays
    while(input >> fname[length] >> lname[length] >> t1[length] >> t2[length] >> fe[length])
        length++;
    //Calculate score and letter grade
    for(int ndx = 0; ndx < length; ndx++)
    {
        if(t1[ndx] < t2[ndx])
        {
            score[ndx] = (t1[ndx] * .25) + (t2[ndx] * .35) + (fe[ndx] * .4);
        }
        else
        {
            score[ndx] = (t1[ndx] * .35) + (t2[ndx] * .25) + (fe[ndx] * .4);
        }
        if(score[ndx] > 90)
        {
            grade[ndx] = 'A';
        }
        else if(score[ndx] > 80)
        {
            grade[ndx] = 'B';
        }
        else if(score[ndx] > 70)
        {
            grade[ndx] = 'C';
        }
        else if(score[ndx] > 60)
        {
            grade[ndx] = 'D';
        }
        else
        {
            grade[ndx] = 'F';
        }
    }
    //Bubblesort
    int flag = 1;
    for(int ndx1 = 1; (ndx1 <= length) && flag; ndx1++)
    {
        flag = 0;
        for(int ndx2 = 0; ndx2 < (length - 1); ndx2++)
        {
            if(score[ndx2 + 1] < score[ndx2])
            {
                strcpy(tempfname, fname[ndx2]);
                strcpy(templname, lname[ndx2]);
                tempt1 = t1[ndx2];
                tempt2 = t2[ndx2];
                tempfe = fe[ndx2];
                tempscore = score[ndx2];
                tempgrade = grade[ndx2];

                strcpy(fname[ndx2], fname[ndx2+1]);
                strcpy(lname[ndx2], lname[ndx2+1]);
                t1[ndx2] = t1[ndx2+1];
                t2[ndx2] = t2[ndx2+1];
                fe[ndx2] = fe[ndx2+1];
                score[ndx2] = score[ndx2+1];
                grade[ndx2] = grade[ndx2+1];

                strcpy(fname[ndx2+1], tempfname);
                strcpy(lname[ndx2+1], templname);
                t1[ndx2+1] = tempt1;
                t2[ndx2+1] = tempt2;
                fe[ndx2+1] = tempfe;
                score[ndx2+1] = tempscore;
                grade[ndx2+1] = tempgrade;
                flag = 1;
            }
        }
    }
    //Write out to a file
    std::ofstream output("calcstudents.txt");
    for(int ndx = 0; ndx < length; ndx++)
    {
        output <<
        fname[ndx] <<
        "\t" <<
        lname[ndx] <<
        "\t" <<
        score[ndx] <<
        "\t" <<
        grade[ndx];
    }

    return 0;
}