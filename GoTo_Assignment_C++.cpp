// GoTo_Assignment_C++.cpp 
//below is the implementation of the described system in C++.
//Please note that C++ does not have native support for HTTPand REST API.
//To demonstrate the core functionality, I'll provide a simple set of classes and methods without focusing on the RESTful aspects.

#include <iostream>
#include <vector>
#include <ctime>
#include <random>

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


struct Card
{
    Suit suit;
    Value value;
};


class Deck
{
private:
    std::vector<Card> cards;  //contains 52 cards

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

    std::vector<Card> getCards()
    {
        return cards;
    }
};


class Player {
private:
    std::vector<Card> hand;

public:
    // Add cards to the player's hand
    void addCards(const std::vector<Card>& newCards)
    { 
        hand.insert(hand.end(), newCards.begin(), newCards.end());  //ToDo: double check if insertion is correct
    }

    // Get the total value of the player's hand
    int getTotalValue() const
    {
		int totalValue = 0;
		for (const auto& card : hand)
		{
			totalValue += static_cast<int>(card.value) + 1; //Assumption: ace has 1 value
		}
		return totalValue;
    }

    // Get the player's hand
    const std::vector<Card>& getHand() const
    {   
        return hand;
    }
};


//Define Game
class Game {
private:
    std::vector<Deck> decks;  //Todo check if it is useless
    std::vector<Player> players;
    std::vector<Card> wholeShoe;

public:

    //Create Deck
    Deck createDeck()
    {
        Deck generatedDeck;
        return generatedDeck;
    }

    // Add a deck to the game and add to the shoe
    void addDeck()
    {
        Deck generatedDeck= createDeck();
        decks.push_back(generatedDeck);  //Todo check if it is useless

        std::vector<Card> generatedCards = generatedDeck.getCards();
        for (auto card : generatedCards)
        {
            wholeShoe.push_back(card);
        }
    }

    // Add a player to the game
    void addPlayer()
    {  
        players.emplace_back();
    }

    // Deal cards to a player from the shoe
    void dealCardsToPlayer(int playerIndex, int numCards)
    {
        if (playerIndex >= 0 && playerIndex < players.size())
        {
            std::vector<Card> dealtCards;
            for (size_t i = wholeShoe.size()-1; i > wholeShoe.size()-numCards; i--)
            {
                dealtCards.push_back(wholeShoe.back());
                wholeShoe.pop_back();
            }
            players[playerIndex].addCards(dealtCards);
        }
    }

    void shuffleGameDeck()
    {
        // random number generator
        std::random_device rd;
        std::mt19937 g(rd());

        // Simple random swapping algorithm
        for (int i = static_cast<int>(wholeShoe.size()) - 1; i > 0; --i)
        {
            std::uniform_int_distribution<int> distribution(0, i);
            int j = distribution(g);

            // Swap cards[i] and cards[j]
            std::swap(wholeShoe[i], wholeShoe[j]);
        }
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

