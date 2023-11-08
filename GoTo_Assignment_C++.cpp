// GoTo_Assignment_C++.cpp 
//below is theimplementation of the described system in C++.
//Please note that C++ does not have native support for HTTPand REST API.
//To demonstrate the core functionality, I'll provide a simple set of classes and methods without focusing on the RESTful aspects.

#include <iostream>
#include <vector>
#include <ctime>

//needed classes:
//  enum class Suit
//	enum class Value
//	struct Card
//	class Deck
//	class Player
//	class Game

enum class Suit { Hearts, Spades, Clubs, Diamonds };
enum class Value { Ace, Two, Three, Four, Five, Six, Seven,
                    Eight, Nine, Ten, Jack, Queen, King };


struct Card {
    Suit suit;
    Value value;
};


class Deck
{
private:
    std::vector<Card> cards;

public:
    Deck()
    {  
        initialize();
    }
    
	void initialize()
	{
		cards.clear();
		for (int i = 0; i < 4; ++i)
        {
			for (int j = 0; j < 13; ++j)
            {
				cards.push_back({ static_cast<Suit>(i), static_cast<Value>(j) });
			}
		}
	}

    void shuffle()
    {
       //implement 
    }

	std::vector<Card> dealCards(int numCards)
	{
		std::vector<Card> hand;
		for (int i = 0; i < numCards && !cards.empty(); ++i) {
			hand.push_back(cards.back());
			cards.pop_back();
		}
		return hand;
	}
};


class Player {
private:
    std::vector<Card> hand;

public:
    // Add cards to the player's hand
    void addCards(const std::vector<Card>& newCards)
    {       
    }

    // Get the total value of the player's hand
    int getTotalValue() const
    {        
    }

    // Get the player's hand
    const std::vector<Card>& getHand() const
    {        
    }
};


class Game {
private:
    std::vector<Deck> decks;
    std::vector<Player> players;

public:
    // Add a deck to the game
    void addDeck()
    {
        decks.emplace_back();
    }

    // Add a player to the game
    void addPlayer()
    {  
        players.emplace_back();
    }

    // Deal cards to a player from the game deck
    void dealCardsToPlayer()
    {        
    }

    // Get the list of players with the total added value of all the cards each player holds
    void getPlayerListSortedByTotalValue()
    {
        // Implementation
    }
};



int main()
{
    
}

