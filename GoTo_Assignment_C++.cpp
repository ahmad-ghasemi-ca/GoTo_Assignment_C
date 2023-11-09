// GoTo_Assignment_C++.cpp 
//below is the implementation of the described system in C++.
//Please note that C++ does not have native support for REST API.
//To demonstrate the core functionality, I'll provide a simple set of classes and methods without focusing on the RESTful aspects.

// I add various comments inside the code to convey my thought knowing the facts that most of them are not needed in real code

#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <unordered_map>


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
			totalValue += static_cast<int>(card.value) + 1; //Assumption: ace has value 1
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
    std::vector<Deck> decks;  //Todo: check if it is useless
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
        decks.push_back(generatedDeck);  //Todo: check if it is useless

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

    // Remove a player to the game
    void removePlayer(int indexToRemove) //Assumption: We need to remove a specific player in a seat (has a number)
    {
        if (indexToRemove >= 0 && indexToRemove < players.size())
        {
            players.erase(players.begin() + indexToRemove);
        }
    }


    // Deal cards to a player from the shoe
    void dealCardsToPlayer(int playerIndex, int numCards)  //ToDo: check the condition of 53 cards
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
    std::vector<std::pair<int, int>> getPlayerListSortedByTotalValue()
    {        
        std::vector<std::pair<int, int>> playerValues;

        // Calculate and store total values for each player
        for (int i = 0; i < players.size(); ++i)
        {
            playerValues.emplace_back(i, players[i].getTotalValue());
        }

        // Sort the vector of pairs based on total values in descending order
		std::sort(playerValues.begin(), playerValues.end(), [](const auto& a, const auto& b)
			{
				return b.second < a.second; // Sorting in descending order
			});
        return playerValues;
    }

    //Get undealt cards per suit 
    std::unordered_map<Suit, int> getUndealtCountPerSuit() const
    {
        // Initialize a map to store the count of undealt cards per suit
        std::unordered_map<Suit, int> undealtCount;

        // Count undealt cards per suit
        for (const auto& card : wholeShoe)
		{
			undealtCount[card.suit]++;
		}
        return undealtCount;
    }

    //Calculate the count of each remaining card sorted by suit and value
    std::unordered_map<std::pair<Suit, Value>, int> getRemainingCardCount() const
    {
        // Initialize a map to store the count of remaining cards per suit and value
        std::unordered_map<std::pair<Suit, Value>, int> cardCount;

        // Count remaining cards per suit and value
        for (const auto& card : wholeShoe)
        {            
                cardCount[{card.suit, card.value}]++;            
        }

        // Define a custom comparator for sorting by suit and face value
        auto comparator = [](const auto& a, const auto& b) {
            if (a.first == b.first) {
                return static_cast<int>(a.second) > static_cast<int>(b.second);
            }
            return static_cast<int>(a.first) > static_cast<int>(b.first);  
        };

        // Sort based on Suit name and Value
        std::sort(cardCount.begin(), cardCount.end(), comparator);
        return cardCount;
    }
};



int main()
{
    
}

