// Ch7 Programs.cpp : Exam Grader

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int num_questions = 20;

//Function to read answers from a file into an array
void getAnswers(const string& filename, char answers[]) 
{
    ifstream file(filename);
    if (!file) 
    {
        cerr << "Error opening file: " << filename << endl;//error message if file couldn't open
        exit(1);
    }
    for (int i = 0; i < num_questions; i++)//loop to store answers into array 
    {
        file >> answers[i];
    }
    file.close();
}

//Function to grade the exam
int gradeExam(const char correct[], const char student[], int missed[], int& numMissed) 
{
    numMissed = 0;//starts with no missed question
    for (int i = 0; i < num_questions; i++)//loops through each question index 
    {
        if (student[i] != correct[i])//checks if the students answer is different from the correct answer 
        {
            missed[numMissed] = i;//store index of missed question
            numMissed++;//counts how many were wrong
        }
    }
    return num_questions - numMissed;//return number of correct answers
}

//output
void writeReport(const char correct[], const char student[], const int missed[], int numMissed) 
{
    cout << "\n" << endl;
    cout << string(54, '=') << endl;
    //cout << center << setw(54) << "Exam Grading report" << endl;
    cout << "\t\tExam Grading Report" << endl;
    cout << string(54, '=') << endl;
   

    //Header row
    cout << left << setw(20) << "Missed Question" << setw(20) << "Correct Answer" << setw(20) << "Student Answer" << endl;
    cout << string(54, '-') << endl;

    
    for (int i = 0; i < numMissed; i++)//loops through each missed question 
    {
        int q = missed[i];//gets the index of missed questions
        cout << left << setw(20) << (q + 1) << setw(20) << correct[q] << setw(20) << student[q] << endl;//note q+1, array starts at 0, exam starts at 1
    }

    cout << "\nTotal missed: " << numMissed << endl;

    double percentage = ((num_questions - numMissed) / (double)num_questions) * 100.0;
    cout << fixed << setprecision(2);
    cout << "Percentage correct: " << percentage << "%" << endl;

    if (percentage >= 70.0)
        cout << "Result: PASS" << endl;
    else
        cout << "Result: FAIL" << endl;
}

int main() 
{
    char correct[num_questions];
    char student[num_questions];
    int missed[num_questions];
    int numMissed;

    //Read answers from files
    getAnswers("CorrectAnswers.txt", correct);
    getAnswers("StudentAnswers.txt", student);

    //Grade exam
    gradeExam(correct, student, missed, numMissed);

    //Display results
    writeReport(correct, student, missed, numMissed);

    return 0;
}