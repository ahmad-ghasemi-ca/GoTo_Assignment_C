#pragma once

#include "IGame.h" 

class IGameHandler
{
public:
    virtual ~IGameHandler() = default;

    virtual IGame* createGame(int playerNum, int Decks) = 0;
    virtual void deleteGame() = 0;
    virtual void displayReport(int playerNumber) = 0;
};