
#pragma once

#include <vector>
#include <unordered_map>

enum class Suit;
enum class Value;

struct Card;


class IGame
{
public:
    virtual ~IGame() = default;

    virtual void addDeckToShoe() = 0;
    virtual void addPlayer() = 0;
    virtual void removePlayer(int playerNumberToRemove) = 0;
    virtual void dealCardsToPlayer(int playerNumber, int numCards) = 0;
    virtual const std::vector<Card> getListOfCardsPlayer(int playerNumber) = 0;
    virtual void shuffleGameDeck() = 0;
    virtual std::vector<std::pair<int, int>> getPlayerListSortedByTotalValue() = 0;
    virtual std::unordered_map<Suit, int> getUndealtCountPerSuit() const = 0;
    virtual std::vector<std::pair<std::pair<Suit, Value>, int>> getRemainingCardCount() const = 0;
};





