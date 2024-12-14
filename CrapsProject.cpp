// CrapsProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string> 
using namespace std;

enum Spot { FILLED, UNFILLED };

class Dice {
public:
	int roll() {
		return (rand() % (6 - 1 + 1)) + 1;
	}
};


class Positions {
public:
	bool contains(int value) {
		for (int i = 0; i < 5; i++)
		{
			if (positions[i] == value) {
				return true;
			}
		}
		return false;
	}

	void setPositionAt(int index, int value) {
		positions[index] = value;
	}

	void clear() {
		for (int i = 0; i < 5; i++)
		{
			setPositionAt(i, 0);
		}
	}

private:
	int positions[5] = { 0,0,0,0,0 };
};





class PlayerSpot {
public:
	PlayerSpot() {
		status = UNFILLED;
		loseAmmount = 0;
		winAmmount = 0;
		betAmount = 0;
		initialDiceRoll = 0;
		name = "";
	}

	void clear() {
		status = UNFILLED;
		loseAmmount = 0;
		winAmmount = 0;
		betAmount = 0;
		initialDiceRoll = 0;
		name = "";
	}


	Spot getSpotStatus() {
		return status;
	}
	void setSpotStatus(Spot definedStatus) {
		status = definedStatus;
	}
	double getBetAmount() {
		return betAmount;
	}
	void setBetAmount(double dollars) {
		betAmount = dollars;
	}
	void setInitialDiceRoll(int roll) {
		initialDiceRoll = roll;
	}
	int getInitialDiceRoll() {
		return initialDiceRoll;
	}
	void setwinAmmount(double dollars) {
		winAmmount = dollars;
	}
	double getwinAmmount() {
		return winAmmount;

	}
	void setloseAmmount(double dollars) {
		loseAmmount = dollars;
	}
	double getloseAmmount() {
		return loseAmmount;
	}
	void setPlayerName(string playerName) {
		name = playerName;
	}
	string getPlayerName() {
		return name;
	}



private:
	Spot status;
	double loseAmmount;
	double winAmmount;
	double 	betAmount;
	int initialDiceRoll;
	int currentBetDiceRoll;
	int numberOfPlayers;
	string name;
};



int main()
{
	srand(time(0));
	int numberOfPlayers;
	double betAmountInput;

	Dice diceOne{};
	Dice diceTwo{};

	PlayerSpot playerSpot1, playerSpot2, playerSpot3, playerSpot4, playerSpot5;
	PlayerSpot playerSpots[5] = { playerSpot1, playerSpot2, playerSpot3, playerSpot4, playerSpot5 };

	Positions playerPositions{};




	while (true)
	{
		cout << "--> Welcome back!\n";
		cout << "Enter number of players: \n";
		cin >> numberOfPlayers;
		system("cls");
		if (numberOfPlayers >= 2 && numberOfPlayers <= 5) {

			//Get player bets
			for (int i = 0; i < numberOfPlayers; ++i) {
				if (playerSpots[i].getSpotStatus() == UNFILLED) {

					playerSpots[i].setSpotStatus(FILLED);
					cout << "Player " << i + 1 << " how much are you betting? \n";
					cin >> betAmountInput;
					playerSpots[i].setBetAmount(betAmountInput);
					playerSpots[i].setPlayerName("Player " + to_string(i + 1));
				}
			}


			//Get player positions
			for (int i = 0; i < numberOfPlayers; i++)
			{
				int orderRoll = diceOne.roll() + diceTwo.roll();
				while (playerPositions.contains(orderRoll)) {
					orderRoll = diceOne.roll() + diceTwo.roll();
				}
				playerPositions.setPositionAt(i, orderRoll);
				playerSpots[i].setInitialDiceRoll(orderRoll);
			}

			//Show inicial player positions
			cout << "\n\n--> Initial Players positions\n";
			for (int i = 0; i < numberOfPlayers; i++)
			{
				cout << playerSpots[i].getPlayerName() << " has rolled initialy: " << playerSpots[i].getInitialDiceRoll() << "\n";
			}


			//Order player positions              
			for (int i = 0; i < numberOfPlayers; i++)
			{
				for (int j = 0; j < numberOfPlayers; j++)
				{
					if (playerSpots[j].getInitialDiceRoll() < playerSpots[i].getInitialDiceRoll()) {
						PlayerSpot temp = playerSpots[i];
						playerSpots[i] = playerSpots[j];
						playerSpots[j] = temp;
					}
				}
			}
			cout << "\n\n--> Ordered Players positions\n";
			for (int i = 0; i < numberOfPlayers; i++)
			{
				cout << playerSpots[i].getPlayerName() << " has rolled initialy: " << playerSpots[i].getInitialDiceRoll() << "\n";
			}

			bool continuePlaying = true;
			int lastRoll = 0;

			//Play craps
			cout << "\n--> Game Starts\n";
			while (continuePlaying)
			{
				for (int i = 0; i < numberOfPlayers; i++)
				{
					int currentBetRoll = diceOne.roll() + diceTwo.roll();
					cout << playerSpots[i].getPlayerName() << " rolls: " << currentBetRoll << "\n";

					if (i == 0 && (currentBetRoll == 7 || currentBetRoll == 11)) {
						double totalPayment = playerSpots[i].getBetAmount() * (numberOfPlayers - 1);
						playerSpots[i].setwinAmmount(totalPayment);

						for (int j = 1; j < numberOfPlayers; j++)
						{
							playerSpots[j].setloseAmmount(playerSpots[i].getBetAmount());

						}
						cout << playerSpots[i].getPlayerName() << " wins = )\n ";
						continuePlaying = false;
						break;
					}

					if (i == 0 && (currentBetRoll == 2 || currentBetRoll == 3 || currentBetRoll == 12)) {
						double totalLost = 0;

						for (int j = 1; j < numberOfPlayers; j++)
						{
							totalLost += playerSpots[j].getBetAmount();
							playerSpots[j].setwinAmmount(playerSpots[j].getBetAmount());
						}
						cout << playerSpots[i].getPlayerName() << " loses = (\n";
						playerSpots[i].setloseAmmount(totalLost);


						continuePlaying = false;
						break;
					}


					if (lastRoll == currentBetRoll) {
						double totalPayment = playerSpots[i].getBetAmount() * (numberOfPlayers - 1);
						playerSpots[i].setwinAmmount(totalPayment);
						cout << playerSpots[i].getPlayerName() << " wins =)\n";

						for (int j = 0; j < numberOfPlayers; j++)
						{
							if (j != i) {
								playerSpots[j].setloseAmmount(playerSpots[i].getBetAmount());
							}
						}
						continuePlaying = false;
						break;
					}

					if (i != 0 && currentBetRoll == 7) {
						double totalLost = 0;
						cout << playerSpots[i].getPlayerName() << " lost =(\n";

						for (int j = 0; j < numberOfPlayers; j++)
						{
							if (j != i) {
								totalLost += playerSpots[j].getBetAmount();
								playerSpots[j].setwinAmmount(playerSpots[j].getBetAmount());
							}
						}
						playerSpots[i].setloseAmmount(totalLost);
						continuePlaying = false;
						break;
					}
					lastRoll = currentBetRoll;
				}
			}

			//Show win and lose ammounts
			cout << "\n--> Final score and debts\n";
			for (int i = 0; i < numberOfPlayers; i++)
			{
				cout << playerSpots[i].getPlayerName() << " win ammount: " << playerSpots[i].getwinAmmount() << "\n";
				cout << playerSpots[i].getPlayerName() << " lose ammount: " << playerSpots[i].getloseAmmount() << "\n\n";
			}
			cout << "Thanks for playing, see you soon!\n\n";

			playerPositions.clear();

			for (int i = 0; i < numberOfPlayers; i++)
			{
				playerSpots[i].clear();
			}
		}
		else {
			cout << "\nInvalid number of players \nPlayers must be between 2 and 5\n\n";
		}

	}
	return 0;
}
