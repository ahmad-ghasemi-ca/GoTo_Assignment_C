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
#include <string>
#include "IGame.h"
#include "IGameHandler.h"


//needed classes:
//  enum class Suit
//	enum class Value
//	struct Card
//	class Deck
//	class Player
//	class Game
//  class Gamehandler
//  class Messages


class Messages
{
public:
	std::string gameHandlerUndealtCardsPerSuit = "Undealt cards count per suit are:";
	std::string gameHandlerRemainingCards = "Remaing cards count are:";
	std::string gameHandlerListPlayersSorted = "list of players sorted by their hand value";
	std::string gameHandlerNewGameCreated = "A new game created with players and decks: ";
	std::string gameHandlerListCardsplayer = "list of cards for player ";
	std::string gameHandlerInvalidParamforGameCreation = "Invalid parameters for creating a game.";
	std::string gameHandlerGameDeleted = "Game ended!";

	std::string gameGetCradsErrorNoPlayer = "Get number of Cards Error: player with this number does not exist: ";
	std::string gameDealErrorPlayerDoesNotExist = "Deal to player Error: The player does not exist in the game";
	std::string gameRemoveErrorPlayerDoseNotExist = "Remove player Error: This player does not exist in the game";
	std::string gameRemovePlayerSuccess = "The player with this number were removed: ";
	std::string gameCardsDealtSuccess = "This numbers of crads were dealt to player: ";
	std::string gameShuffleGameDeckSuccess = "The shoe was shuffled!";
	std::string gameShuffleGameDeckFailed = "Shuffle Error: There is not enough cards to shuffle";
	std::string getPlayerListSortedByTotalValueFailed = "Player cards list Error: There is no player to get the hand";

	std::string line = "----------";
};

enum class Suit { Hearts = 1, Spades, Clubs, Diamonds };
enum class Value {
	Ace = 1, Two, Three, Four, Five, Six, Seven,
	Eight, Nine, Ten, Jack, Queen, King
};


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
		for (int i = 1; i < 5; ++i)
		{
			for (int j = 1; j < 14; ++j)
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
			totalValue += static_cast<int>(card.value); //Assumption: ace has value 1
		}
		return totalValue;
	}

	// Get the player's hand
	const std::vector<Card>& getHand() const
	{
		return hand;
	}
};


class Game: public IGame
{
private:
	std::vector<Player> players;
	std::vector<Card> shoe;
	Messages message;

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
		Deck generatedDeck = createDeck();

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
	void removePlayer(int playerNumberToRemove) //Assumption: We need to remove a specific player in a seat (has a number)
	{
		int indexToRemove = playerNumberToRemove - 1;
		if (indexToRemove >= 0 && indexToRemove < static_cast<int>(players.size()))
		{
			players.erase(players.begin() + indexToRemove);
			std::cout << message.line << std::endl;
			std::cout << message.gameRemovePlayerSuccess << playerNumberToRemove << std::endl;
		}
		else
		{
			std::cout << message.line << std::endl;
			std::cout << message.gameRemoveErrorPlayerDoseNotExist << std::endl;
		}
	}


	// Deals cards to a player from the shoe
	void dealCardsToPlayer(int playerNumber, int numCards)
	{
		int playerIndex = playerNumber - 1;
		if (playerIndex >= 0 && playerIndex < static_cast<int>(players.size()))
		{
			std::vector<Card> dealtCards;
			size_t shoeSize = shoe.size();
			for (size_t i = shoeSize - 1; i > shoeSize - 1 - numCards && !shoe.empty(); i--) //does not deal if shoe is empty.
			{
				dealtCards.push_back(shoe.back());
				shoe.pop_back();
			}
			players.at(playerIndex).addCards(dealtCards);
			std::cout << message.line << std::endl;
			std::cout << message.gameCardsDealtSuccess << numCards << " , " << playerNumber << std::endl;
		}
		else
		{
			std::cout << message.line << std::endl;
			std::cout << message.gameDealErrorPlayerDoesNotExist << std::endl;
		}
	}

	const std::vector<Card> getListOfCardsPlayer(int playerNumber)
	{
		int playerIndex = playerNumber-1;
		std::vector<Card> playerHand;
		if (playerIndex < players.size() && playerIndex>=0)
		{
			playerHand = players.at(playerIndex).getHand();
		}
		else
		{
			std::cout << message.line << std::endl;
			std::cout << message.gameGetCradsErrorNoPlayer << playerNumber << std::endl;
		}

		return playerHand;
	}

	void shuffleGameDeck()
	{
		// random number generator
		std::random_device rd;
		std::mt19937 g(rd());

		// Simple random swapping algorithm
		if (shoe.size() > 1)
		{
			for (size_t i = shoe.size() - 1; i > 0; --i)
			{
				std::uniform_int_distribution<int> distribution(0, i);
				int j = distribution(g);

				// Swap cards[i] and cards[j]
				std::swap(shoe.at(i), shoe.at(j));
			}
			std::cout << message.line << std::endl;
			std::cout << message.gameShuffleGameDeckSuccess << std::endl;
		}
		else
		{
			std::cout << message.line << std::endl;
			std::cout << message.gameShuffleGameDeckFailed << std::endl;
		}
	}

	// Get the list of players with the total added value of all the cards each player holds
	std::vector<std::pair<int, int>> getPlayerListSortedByTotalValue()
	{
		std::vector<std::pair<int, int>> playerValues;

		if (players.size() > 0)
		{
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
		}
		else
		{
			std::cout << message.line << std::endl;
			std::cout << message.getPlayerListSortedByTotalValueFailed << std::endl;
		}

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


class GameHandler: public IGameHandler
{
private:
	Game* game;
	Messages message;

public:
	GameHandler()
	{
		game = new Game();
	}

	Game* createGame(int playerNum, int Decks)
	{
		if (Decks <= 0 || playerNum <= 0)
		{
			std::cerr << message.gameHandlerInvalidParamforGameCreation << std::endl;
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

		std::cout << message.gameHandlerNewGameCreated << playerNum << "," << Decks << std::endl;

		game->shuffleGameDeck();

		return game;
	}

	// Generates and displays a report on the status of the game
	void displayReport(int playerNumber)
	{
		//int playerIndex = playerNumber - 1;
		auto list = game->getListOfCardsPlayer(playerNumber);
		std::cout << message.line << std::endl;
		std::cout << message.gameHandlerListCardsplayer << playerNumber << " is:" << std::endl;
		for (auto& card : list)
		{
			std::cout << "Suit: " << static_cast<int>(card.suit) << "  Value: " << static_cast<int>(card.value) << std::endl;
		}

		auto list2 = game->getPlayerListSortedByTotalValue();
		std::cout << message.line << std::endl;
		std::cout << message.gameHandlerListPlayersSorted << std::endl;
		for (auto& elem : list2)
		{
			std::cout << "Player " << elem.first + 1 << ", Value: " << elem.second << std::endl;
		}

		auto list3 = game->getRemainingCardCount();
		std::cout << message.line << std::endl;
		std::cout << message.gameHandlerRemainingCards << std::endl;
		for (auto& elem : list3)
		{
			std::cout << "suit: " << static_cast<int>(elem.first.first) << " value: " << static_cast<int>(elem.first.second)
				<< ", count: " << elem.second << std::endl;
		}

		auto list4 = game->getUndealtCountPerSuit();
		std::cout << message.line << std::endl;
		std::cout << message.gameHandlerUndealtCardsPerSuit << std::endl;
		for (auto& elem : list4)
		{
			std::cout << "Suit: " << static_cast<int>(elem.first) << " count: " << elem.second << std::endl;
		}

		std::cout << "----end-----" << std::endl;
	}

	void deleteGame()
	{
		delete game;
		game = nullptr;
		std::cout << std::endl;
		std::cout << message.gameHandlerGameDeleted << std::endl;
	}

	~GameHandler()
	{
		if (game != nullptr)
		{
			delete game;
		}
	}
};



int main()
{
	GameHandler gamehandler;
	auto game = gamehandler.createGame(1, 1); //Creates a game with given number of players and decks and shuffles the shoe.
	game->removePlayer(1);

	game->shuffleGameDeck(); // On demand shuffle of the shoe.

	game->dealCardsToPlayer(1, 5); //Deals the given player the given number of cards
	game->dealCardsToPlayer(2, 5);
	game->dealCardsToPlayer(3, 5);
	game->dealCardsToPlayer(4, 5);

	gamehandler.displayReport(1); // displays status of the game and especially cards on the hand of the given player.
	gamehandler.deleteGame();
}

