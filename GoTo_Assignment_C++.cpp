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
#include <utility>
#include <map>
#include <memory>





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

public:
    Deck()
    {  
        initialize();
    }	

    std::vector<Card>& getCards()
    {
        return cards;
    }
};


class Player
{
private:
    std::vector<Card> hand;

public:
    // Add cards to the player's hand
    void addCards(const std::vector<Card>& newCards)
    { 
        hand.insert(hand.end(), newCards.begin(), newCards.end());  
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
class Game
{
private:
    std::vector<Player> players;
    std::vector<Card> shoe;

    //Create Deck
    Deck createDeck()
    {
        Deck generatedDeck;
        return generatedDeck;
    }

public:    

    // Add a deck to the game and add to the shoe
    void addDeckToShoe()
    {
        Deck generatedDeck= createDeck();

        std::vector<Card> generatedCards = generatedDeck.getCards();
        for (auto& card : generatedCards)
        {
            shoe.push_back(card);
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
        if (indexToRemove >= 0 && indexToRemove < static_cast<int>(players.size()))
        {
            players.erase(players.begin() + indexToRemove);
        }
    }


    // Deals cards to a player from the shoe
    void dealCardsToPlayer(int playerIndex, int numCards)  
    {
        if (playerIndex >= 0 && playerIndex < static_cast<int>(players.size()))
        {
            std::vector<Card> dealtCards;
            for (size_t i = shoe.size()-1; i > shoe.size()-1-numCards && !shoe.empty(); i--) //does not deal if shoe is empty.
            {
                dealtCards.push_back(shoe.back());
                shoe.pop_back();
            }
            players.at(playerIndex).addCards(dealtCards);
        }
    }

    const std::vector<Card> getListOfCardsPlayer(int playerIndex)
    {
        std::vector<Card> playerHand= players.at(playerIndex).getHand();
        return playerHand;
    }

    void shuffleGameDeck()
    {
        // random number generator
        std::random_device rd;
        std::mt19937 g(rd());

        // Simple random swapping algorithm
        for (size_t i = shoe.size() - 1; i > 0; --i)
        {
            std::uniform_int_distribution<int> distribution(0, i);
            int j = distribution(g);

            // Swap cards[i] and cards[j]
            std::swap(shoe.at(i), shoe.at(j));
        }
    }
    
    // Get the list of players with the total added value of all the cards each player holds
    std::vector<std::pair<int, int>> getPlayerListSortedByTotalValue()
    {        
        std::vector<std::pair<int, int>> playerValues;

        // Calculate and store total values for each player
        for (size_t i = 0; i < players.size(); ++i)
        {
            playerValues.emplace_back(i, players.at(i).getTotalValue());
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
        for (const auto& card : shoe)
		{
			undealtCount[card.suit]++;
		}
        return undealtCount;
    }
    

    std::vector<std::pair<std::pair<Suit, Value>, int>> getRemainingCardCount() const
    {
        // Initialize a map to store the count of remaining cards per suit and value
        std::map<std::pair<Suit, Value>, int> cardCount;

        // Count remaining cards per suit and value
        for (const auto& card : shoe)
        {
            cardCount[{card.suit, card.value}]++;
        }

        // Copy elements to a vector for sorting
        std::vector<std::pair<std::pair<Suit, Value>, int>> cardVector(cardCount.begin(), cardCount.end());

        // Define a custom comparator for sorting by suit and face value
        auto comparator = [](const auto& a, const auto& b) {
            if (a.first.first == b.first.first) {
                return static_cast<int>(a.first.second) > static_cast<int>(b.first.second);
            }
            return static_cast<int>(a.first.first) > static_cast<int>(b.first.first);
        };

        // Sort based on Suit name and Value
        std::sort(cardVector.begin(), cardVector.end(), comparator);

        return cardVector;
    }


};


class GameHandler
{
private:
    std::shared_ptr<Game> game;

public:
    GameHandler()
    {
        game = std::make_shared<Game>();
    }    

    std::shared_ptr<Game> createGame(int playerNum, int Decks)
    {
        if (Decks <= 0 || playerNum <= 0)
        {
            std::cerr << "Invalid parameters for creating a game." << std::endl;
            return nullptr;
        }
        for (int i = 0; i < Decks; i++)
        {
            game->addDeckToShoe();
        }

        for (int i = 0; i < playerNum; i++)
        {
            game->addPlayer();
        }
        
        std::cout << "A new game created with " << playerNum << " players and " << Decks << " decks." << std::endl;

        game->shuffleGameDeck();
        std::cout << "The shoe containing " << Decks << " decks was shuffled and is ready to be dealt." << std::endl;

        return game;
    }

    void displayReport(int playerIndex)
    {
        auto list=game->getListOfCardsPlayer(playerIndex);
        std::cout << "-----------" << std::endl;
        std::cout << "list of cards for player " << playerIndex << " is:" << std::endl;
        for (auto& card: list)
        {
            std::cout << "Suit: " <<static_cast<int>(card.suit) << "  Value: " << static_cast<int>(card.value) << std::endl;
        }

    }
};



int main()
{
    GameHandler gamehandler;
    auto game = gamehandler.createGame(3,1);
    game->dealCardsToPlayer(0, 3);
    game->dealCardsToPlayer(1, 3);
    game->dealCardsToPlayer(1, 3);

    gamehandler.displayReport(0);
    std::cout << "end"<< std::endl;
    
}

