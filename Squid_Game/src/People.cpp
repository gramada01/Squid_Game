#include "People.h"

People::People()
{

}

People::~People()
{

}

Player::Player()
{

}

Player::~Player()
{

}

Supervisor::Supervisor()
{

}

Supervisor::~Supervisor()
{

}

string Player::person_type()
{
    string smth = "This is a player: ";
    smth.append(surname);
    smth.append(" ");
    smth.append(name);
    return smth;
}

string Supervisor::person_type()
{
    string smth = "This is a supervisor: ";
    smth.append(surname);
    smth.append(" ");
    smth.append(name);
    return smth;
}
