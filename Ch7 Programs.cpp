// Ch7 Programs.cpp : World Series Champs


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Function to get teams from file, reads each line (team name) and stores in a vector 
vector<string> getTeam(const string& filename)
{
    vector<string> teams;//holds the team names read from the file
    ifstream file(filename);//opens file
    if (!file)//if file failes to open
    {
        cerr << "Error opening " << filename << endl;
        return teams;
    }

    string line;
    while (getline(file, line))//reads file line by line 
    {
        teams.push_back(line);//adds line to vecto
    }
    return teams;
}

//Function to get winners from file similar to getTeam
vector<string> findWinner(const string& filename)
{
    vector<string> winners;
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error opening " << filename << endl;
        return winners;
    }

    string line;
    while (getline(file, line))
    {
        winners.push_back(line);
    }
    return winners;
}

//Function to display teams without modifing the vector.
void displayTeams(const vector<string>& teams)
{
    cout << "Teams that have won the World Series:\n\n";
    for (const auto& team : teams)
    {
        cout << team << endl;
    }
}

//Function to count how many times the "team" entered has won
int countWins(const string& team, const vector<string>& winners)
{
    return count(winners.begin(), winners.end(), team);//.begin stats the vector, .end ends the vector, and team is the value to look for
}

int main()
{
    vector<string> teams = getTeam("Teams.txt");
    vector<string> winners = findWinner("WorldSeriesWinners.txt");

    if (teams.empty() || winners.empty())
    {
        return 1;//Exit if files couldn't be loaded
    }

    displayTeams(teams);//prints the list of team names
    string teamName;//stores the team name entered by the user

    while (true)
    {
        cout << "\nEnter the name of a team (or type 'quit' to exit): ";

        getline(cin, teamName);

        if (teamName == "quit" || teamName == "QUIT" || teamName == "Quit")
        {
            cout << "Exiting Program. \n";
            break;
        }

        //Validate input, checks to see if the entered team name is in the list
        if (find(teams.begin(), teams.end(), teamName) == teams.end())
        {
            cout << "That team is not in the list. Please try again.\n";
            continue;
        }
        
            int wins = countWins(teamName, winners);//calls function to ount how many times the team is on the winning list
            cout << "\nThe " << teamName << " have won the World Series " << wins << " times between 1903 and 2012.\n";  
    }
    return 0;
}