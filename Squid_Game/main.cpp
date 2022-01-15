#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "Application.h"

using namespace std;

int main()
{
    Application app(9);

    app.PeopleGeneration("People.csv");
    app.ShowPlayers();
    cout<<endl<<endl;
    app.ShowSupervisors();
    cout<<endl<<endl<<endl;

    app.RedGreen();
    cout<<"Red Light Green Light surviving players:"<<endl<<endl;
    app.ShowPlayers();
    cout<<endl<<endl;
    app.ShowSupervisors();
    cout<<endl;

    app.TugOfWar();
    cout<<"Tug of War surviving players:"<<endl<<endl;
    app.ShowPlayers();
    cout<<endl<<endl;

    app.Marbles();
    cout<<"Marbles surviving players:"<<endl<<endl;
    app.ShowPlayers();
    cout<<endl<<endl;

    app.Genken();
    cout<<"Genken(Rock, Paper, Scissors) surviving player:"<<endl<<endl;
    app.ShowPlayers();

    cout<<endl<<endl;
    app.ShowResult();
    cout<<endl<<endl;

    return 0;
}
