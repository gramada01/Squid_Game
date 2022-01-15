#include "Application.h"
#include <sstream>
#include <string>
#include <time.h>

Application::Application(int nrSup):nrSuper{nrSup}
{
   //srand(1732);
   srand (time(NULL));
}

Application::~Application()
{

}

void Application::Eliminate(int i)
{
    int m = players[i].get_superv();

    prize = prize + players[i].get_debt();

    supervisors[m].set_compensation(supervisors[m].get_compensation()+players[i].get_debt());

    for(size_t j=0;j<supervisors[m].playerz.size();j++)
    {
        if(supervisors[m].playerz[j]==i)
        {
            supervisors[m].playerz.erase(supervisors[m].playerz.begin()+j);
            break;
        }
    }
    players.erase(players.begin()+i);
}

void Application::ShowPlayers()
{

    for(size_t i=0;i<players.size();++i)
    {
        cout<<i+1<<") ";
        cout<<players[i].get_surname()<<" "<<players[i].get_name()<<", city: "<<players[i].get_city();
        cout<<", weight: "<<players[i].get_weight()<<", debt: "<<players[i].get_debt()<<", player number: "<<players[i].get_playerNumber()<<endl;
        cout<<"Supervisor: "<<players[i].get_superv()+1<<endl;
    }
}

void Application::ShowSupervisors()
{
    for(size_t i=0;i<supervisors.size();++i)
    {
        cout<<i+1<<") ";
        cout<<supervisors[i].get_surname()<<" "<<supervisors[i].get_name()<<", city: "<<supervisors[i].get_city();
        cout<<", debt: "<<supervisors[i].get_debt()<<", mask: "<<supervisors[i].get_maskType()<<endl;
        cout<<"Players : ";
        for(size_t j=0;j<supervisors[i].playerz.size();++j)
            cout<<supervisors[i].playerz[j]+1<<" ";
        cout<<endl;
    }
}

void Application::PeopleGeneration(string fileName)
{
    Reading(fileName);

    SupervisorCreation();

    for(int i=0;i<99;++i)
        players[i].set_playerNumber(i+1);

    PlayerAssociation();

    Mask();

}

void Application::Reading(string fileName)
{
    ifstream read(fileName);
    string word, line;

    //First i read all data (of the 108 people) and save it as if they were all players
    while(getline(read, line))
    {
        players.push_back(Player());
        stringstream ss(line);

        getline(ss,word,',');

        getline(ss,word,',');
        players.back().set_surname(word);

        getline(ss,word,',');
        players.back().set_name(word);

        getline(ss,word,',');
        players.back().set_city(word);
    }
    for(size_t i=0;i<players.size();++i)
    {
        players[i].set_weight(rand_weight());
        players[i].set_debt(rand_debt());
    }
}

void Application::SupervisorCreation()
{
    //taking random people from the players pool and making them supervisors
    while(nrSuper>0)
    {
        supervisors.push_back(Supervisor());
        int size_players = players.size();
        int sup = rand()%size_players + 0;
        supervisors.back().set_surname(players[sup].get_surname());
        supervisors.back().set_name(players[sup].get_name());
        supervisors.back().set_city(players[sup].get_city());
        supervisors.back().set_debt(players[sup].get_debt());

        players.erase(players.begin()+sup);

        nrSuper--;
    }
}

void Application::PlayerAssociation()
{
    //Associating players with supervisors
    vector<int> play; //remembering which players are not associated
    for(int i=0;i<99;i++)
    {
        play.push_back(i);
    }

    int super = 0; //the supervisor currently "in use"
    int index = 99;
    while(index>0)
    {
        if(supervisors[super].playerz.size()==11)
        {
            super++;
            continue;
        }
        int size_players = play.size();
        int m = rand()%size_players + 0;
        int nr = play[m];

        players[nr].set_superv(super);
        supervisors[super].playerz.push_back(nr);
        play.erase(play.begin()+m);
        index--;
    }
}

void Application::Mask()
{
    //grouping the supervisors by mask type
    vector<int> mask;
    for(size_t i=0;i<supervisors.size();++i)
        mask.push_back(i);

    //rectangle mask
    int cond = 3;
    while(cond>0)
    {
        int mask_size = mask.size();
        int m = rand()%mask_size + 0;
        int nr = mask[m];
        supervisors[nr].set_maskType("rectangle");
        mask.erase(mask.begin()+m);
        cond--;
    }

    //triangle mask
    cond = 3;
    while(cond>0)
    {
        int mask_size = mask.size();
        int m = rand()%mask_size + 0;
        int nr = mask[m];
        supervisors[nr].set_maskType("triangle");
        mask.erase(mask.begin()+m);
        cond--;
    }

    //circle mask
    for(size_t i=0;i<mask.size();++i)
    {
        supervisors[mask[i]].set_maskType("circle");
    }
}

void Application::RedGreen()
{
    for(size_t i=0;i<players.size();++i)
    {
        if(players[i].get_playerNumber()%2==0)
        {
            Eliminate(i);
        }
    }
}

void Application::TugOfWar()
{
    vector<int> ppl;
    for(size_t i=0;i<players.size();++i)
    {
        ppl.push_back(i);
    }

    vector<int> team1;
    vector<int> team2;
    vector<int> team3;
    vector<int> team4;

    int team_size = players.size();
    team_size = team_size/4;
    int cond = team_size;

    //team1
    while(cond>0)
    {
        int ppl_size = ppl.size();
        int m = rand()%ppl_size + 0;
        int nr = ppl[m];
        team1.push_back(players[nr].get_playerNumber());
        ppl.erase(ppl.begin()+m);

        cond--;
    }

    cond = team_size;
    //team2
    while(cond>0)
    {
        int ppl_size = ppl.size();
        int m = rand()%ppl_size + 0;
        int nr = ppl[m];
        team2.push_back(players[nr].get_playerNumber());
        ppl.erase(ppl.begin()+m);

        cond--;
    }

    cond = team_size;
    //team3
    while(cond>0)
    {
        int ppl_size = ppl.size();
        int m = rand()%ppl_size + 0;
        int nr = ppl[m];
        team3.push_back(players[nr].get_playerNumber());
        ppl.erase(ppl.begin()+m);

        cond--;
    }

    cond = team_size;
    //team4
    while(cond>0)
    {
        int ppl_size = ppl.size();
        int m = rand()%ppl_size + 0;
        int nr = ppl[m];
        team4.push_back(players[nr].get_playerNumber());
        ppl.erase(ppl.begin()+m);

        cond--;
    }

    int weight1 = TeamWeight(team1);
    int weight2 = TeamWeight(team2);
    int weight3 = TeamWeight(team3);
    int weight4 = TeamWeight(team4);

    int battle1;
    int battle2;

    battle1 = TugBattle(team1, team2, weight1, weight2);
    battle2 = TugBattle(team3, team4, weight3, weight4);


    //This part of the code makes the remaining 2 teams fight each other as well

    /*if(battle1==1 and battle2==1)
        battle1 = TugBattle(team1, team3, weight1, weight3);
    else
        if(battle1==1 and battle2==2)
            battle1 = TugBattle(team1, team4, weight1, weight4);
        else
            if(battle1==2 and battle2==1)
                battle1 = TugBattle(team2, team3, weight2, weight3);
            else
                if(battle1==2 and battle2==2)
                    battle1 = TugBattle(team2, team4, weight2, weight4);

*/

}

int Application::TeamWeight(vector<int> team)
{
    int weight = 0;
    for(size_t i=0;i<team.size();++i)
    {
        weight = weight + players[SearchByNumber(team[i])].get_weight();
    }

    return weight;
}

int Application::TugBattle(vector<int> team1, vector<int> team2, int weight1, int weight2)
{
    int cond;
    if(weight1<weight2)
    {
        for(size_t i=0;i<team1.size();++i)
        {
            Eliminate(SearchByNumber(team1[i]));
            cond = 2;
        }
    }
    else
        for(size_t i=0;i<team2.size();++i)
        {
            Eliminate(SearchByNumber(team2[i]));
            cond = 1;
        }
    if(cond==2)
        return 2;
    return 1;
}

int Application::SearchByNumber(int i)
{
    size_t j;
    for(j=0;j<players.size();++j)
    {
        if(players[j].get_playerNumber()==i)
            break;
    }
    return players[j].get_playerNumber();
}

void Application::Marbles()
{
    vector<int> ppl;
    for(size_t i=0;i<players.size();++i)
    {
        ppl.push_back(players[i].get_playerNumber());
    }

    int team_size = players.size();
    int cond = team_size/2;

    int player1;
    int player2;

    while(cond>0)
    {
        int ppl_size = ppl.size();
        int m = rand()%ppl_size + 0;
        int nr = ppl[m];
        player1 = nr;
        ppl.erase(ppl.begin()+m);

        ppl_size = ppl.size();
        int n = rand()%ppl_size + 0;
        nr = ppl[n];
        player2 = nr;
        ppl.erase(ppl.begin()+n);

        int nr1 = random();
        int nr2 = random();
        if(nr1>nr2)
            Eliminate(SearchByNumber(player1));
        else
            Eliminate(SearchByNumber(player2));


        cond--;
    }
}

void Application::Genken()
{
    vector<int> ppl;
    for(size_t i=0;i<players.size();++i)
    {
        ppl.push_back(players[i].get_playerNumber());
    }
    int player1;
    int player2;

    //1 = rock, 2 = paper, 3 = scissors
    int symbol1;
    int symbol2;
    int index;


    //Example of surviving players: 1 3 5 7 9
    //This code makes players "fight": 9 vs 7 and 5 vs 3
    //And so on

    /*while(ppl.size()>1)
    {
        int m = ppl.size();
        int cond = m/2;
        while(cond>0)
        {
            int n = ppl.size();
            index = n - 1;
            player1 = ppl[index];
            player2 = ppl[index-1];
            while(true)
            {
                symbol1 = rand_genken();
                symbol2 = rand_genken();
                if(symbol1==symbol2)
                    continue;
                if((symbol1==1 and symbol2==3)or(symbol1==2 and symbol2==1)or(symbol1==3 and symbol2==2))
                {
                    ppl.erase(ppl.begin()+index-1);
                    Eliminate(SearchByNumber(player2));
                    break;
                }
                else
                {
                    ppl.erase(ppl.begin()+index);
                    Eliminate(SearchByNumber(player1));
                    break;
                }
            }
            index = index - 2;
            cond--;
        }
    }*/

    //Example of surviving players: 1 3 5 7 9
    //This code makes players "fight": 9 vs 7
    //After the results: either 9 vs 5 or 7 vs 5
    //And so on

    while(players.size()>1)
    {
        int m = players.size()-1;
        index = m;
        player1 = ppl[index];
        player2 = ppl[index-1];
        while(true)
        {
            symbol1 = rand_genken();
            symbol2 = rand_genken();
            if(symbol1==symbol2)
                continue;
            if((symbol1==1 and symbol2==3)or(symbol1==2 and symbol2==1)or(symbol1==3 and symbol2==2))
            {
                ppl.erase(ppl.begin()+index-1);
                Eliminate(SearchByNumber(player2));
                break;
            }
            else
            {
                ppl.erase(ppl.begin()+index);
                Eliminate(SearchByNumber(player1));
                break;
            }
        }
    }
}

void Application::ShowResult()
{
    cout<<"Winner :"<<endl;
    cout<<players.front().get_surname()<<" "<<players.front().get_name();
    cout<<", prize won: "<<prize<<", money left after paying debt : "<<prize-players.front().get_debt();
    cout<<endl<<endl;
    cout<<"Supervisors: "<<endl;


    //rewarding the supervisor related to the winner
    supervisors[players.front().get_superv()].set_compensation(supervisors[players.front().get_superv()].get_compensation()+players.front().get_debt());

    vector<int> money;
    vector<int> index;
    int i, j, temp;
    bool swapped;

    for(i=0;i<9;i++)
    {
        money.push_back(supervisors[i].get_compensation());
        index.push_back(i);
    }



    for (i=0;i<8;i++)
   {
     swapped = false;
     for(j=0;j<9-i-1;j++)
     {
        if (money[j] > money[j+1])
        {
            temp = money[j];
            money[j] = money[j+1];
            money[j+1] = temp;

            temp = index[j];
            index[j] = index[j+1];
            index[j+1] = temp;

            swapped = true;
        }
     }
     if (swapped == false)
        break;
   }

    for(i=8;i>=0;i--)
    {
        cout<<supervisors[index[i]].get_surname()<<" "<<supervisors[index[i]].get_name();
        cout<<", money won: "<<supervisors[index[i]].get_compensation()<<", money after paying debt : "<<supervisors[index[i]].get_compensation()-supervisors[index[i]].get_debt();
        cout<<endl;
    }

    cout<<endl<<endl;
    int teamTriangle=0;
    int teamRectangle=0;
    int teamCircle=0;

    for(i=0;i<9;i++)
    {
        if(supervisors[i].get_maskType()=="rectangle")
            teamRectangle = teamRectangle + supervisors[i].get_compensation();
        if(supervisors[i].get_maskType()=="triangle")
            teamTriangle = teamTriangle + supervisors[i].get_compensation();
        if(supervisors[i].get_maskType()=="circle")
            teamCircle = teamCircle + supervisors[i].get_compensation();
    }

    if(teamCircle>teamRectangle and teamCircle>teamTriangle)
    {
        cout<<"The supervisor team that has the most money is: Circle Masks, with the amount of "<<teamCircle;
    }
    if(teamRectangle>teamCircle and teamRectangle>teamTriangle)
    {
        cout<<"The supervisor team that has the most money is: Rectangle Masks, with the amount of "<<teamRectangle;
    }
    if(teamTriangle>teamCircle and teamTriangle>teamRectangle)
    {
        cout<<"The supervisor team that has the most money is: Triangle Masks, with the amount of "<<teamTriangle;
    }



}
