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
        
    }

    std::vector<Card> dealCards(int numCards)
    {        
    }    
};





int main()
{
    
}

