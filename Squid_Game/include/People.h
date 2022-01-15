#ifndef PEOPLE_H
#define PEOPLE_H
#include <string>
#include <vector>
using namespace std;


class People
{
    protected:
        string name;
        string surname;
        string city;
        int debt;
        int weight;

    private:

    public:
        People();
        ~People();

        virtual string person_type() = 0;

        void set_name(string name)
        {
            this->name = name;
        }
        string get_name()
        {
            return name;
        }
        void set_surname(string surname)
        {
            this->surname = surname;
        }
        string get_surname()
        {
            return surname;
        }
        void set_city(string city)
        {
            this->city = city;
        }
        string get_city()
        {
            return city;
        }
        void set_debt(int debt)
        {
            this->debt = debt;
        }
        int get_debt()
        {
            return debt;
        }
        void set_weight(int weight)
        {
            this->weight = weight;
        }
        int get_weight()
        {
            return weight;
        }


};

class Player:public People
{
    private:
        int playerNumber;
        int superv; //this will keep track of which supervisor is in charge of the player

    public:
        Player();
        ~Player();

        string person_type();

        void set_playerNumber(int playerNumber)
        {
            this->playerNumber = playerNumber;
        }
        int get_playerNumber()
        {
            return playerNumber;
        }
        void set_superv(int superv)
        {
            this->superv = superv;
        }
        int get_superv()
        {
            return superv;
        }
};

class Supervisor:public People
{
    private:
        string maskType;
        int compensation = 0;

    public:
        Supervisor();
        ~Supervisor();

        vector<int> playerz; //this will keep track of the players they are in charge with

        string person_type();

        void set_maskType(string maskType)
        {
            this->maskType = maskType;
        }
        string get_maskType()
        {
            return maskType;
        }
        void set_compensation(int compensation)
        {
            this->compensation = compensation;
        }
        int get_compensation()
        {
            return  compensation;
        }
};



#endif // PEOPLE_H
