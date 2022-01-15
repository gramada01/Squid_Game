#ifndef APPLICATION_H
#define APPLICATION_H
#include <fstream>
#include <iostream>
#include "People.h"
#include "Rand.h"

using namespace std;

class Application
{
    private:
        int nrSuper; //number of supervisors
        int prize = 0;

    public:

        vector<Player> players;
        vector<Supervisor> supervisors;


        //Expects csv file with columns: index, surname, name, city
        Application(int nrSup);
        ~Application();
        void Eliminate(int i); //i is the number to help find the player in the vector of players
        void ShowPlayers();
        void ShowSupervisors();
        void PeopleGeneration(string fileName);
        void Reading(string fileName);
        void SupervisorCreation();
        void PlayerAssociation();
        void Mask();
        void RedGreen();
        void TugOfWar();
        int TeamWeight(vector<int> team);
        int TugBattle(vector<int> team1, vector<int> team2, int weight1, int weight2);
        int SearchByNumber(int i);
        void Marbles();
        void Genken(); //Rock, Paper, Scissors
        void ShowResult();
};

#endif // APPLICATION_H
