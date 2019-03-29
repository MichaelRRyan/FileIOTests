/// <summary>
/// Testing projecto for File IO
/// @Author Michael Rainsford Ryan
/// @Date 28/03/19
/// Time 20:36
/// </summary>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void addPlayer();
void readPlayerData();
void reSortScores();

int main()
{
	int input = -1;
	while (input != 0)
	{
		input = -1;
		std::cout << std::endl << "0) Exit.\n1) Save a player to file.\n2) Display player data.\n3) Re-sort data.\nEnter a number: ";
		std::cin >> input;

		if (input == 1)
		{
			addPlayer();
		}
		else if (input == 2)
		{
			readPlayerData();
		}
		else if (input == 3)
		{
			reSortScores();
		}
	}

	system("Pause");
	return EXIT_SUCCESS;
}

void addPlayer()
{
	// Get user input
	std::string name;
	std::cin.ignore();
	std::cout << "Enter your name: ";
	std::getline(std::cin, name);

	int score = 0;
	std::cout << "Enter your score: ";
	std::cin >> score;

	int charNum = 0;
	std::cout << "Enter your character number: ";
	std::cin >> charNum;

	// Save to file
	std::ofstream outputFile;
	outputFile.open("PlayerData.txt", std::ios_base::app);

	if (outputFile.is_open())
	{
		outputFile << name << ",";
		outputFile << score << ",";
		outputFile << charNum << ",";
		outputFile << std::endl;

		outputFile.close();
		std::cout << "File write success!" << std::endl;
	}
	else
	{
		std::cout << "Error opening file." << std::endl;
	}
}

void readPlayerData()
{
	std::ifstream inputFile;
	inputFile.open("PlayerData.txt");

	if (inputFile.is_open())
	{
		std::string line;
		std::string inputName;
		std::string inputScore;
		std::string inputCharNum;
		int playerNum = 1;

		while (!inputFile.eof())
		{
			std::getline(inputFile, line);

			int len = line.length();
			for (int i = 0, data = 0; i < len; i++)
			{
				if (line[i] == ',')
				{
					data++;
					if (data > 2)
						break;
					continue;
				}
				if (data == 0)
				{
					inputName += line[i];
				}
				else if (data == 1)
				{
					inputScore += line[i];
				}
				else if (data == 2)
				{
					inputCharNum += line[i];
				} // End if else
			} // End for

			if (len > 0)
			{
				std::cout << "Player " << playerNum << ":\n" << "Name: " << inputName << "\nScore: " << inputScore << "\nCharacter Number: " << inputCharNum << std::endl;
				playerNum++;
				inputName = "";
				inputScore = "";
				inputCharNum = "";
			}
			else
			{
				break;
			}
			
		} // End while

		inputFile.close();
		std::cout << "Read File Success!" << std::endl;
	} // End if
	else
	{
		std::cout << "Error opening file." << std::endl;
	}
}

void reSortScores()
{
	const int MAX_PLAYERS = 5;
	std::string names[MAX_PLAYERS];
	int scores[MAX_PLAYERS];
	std::string charNums[MAX_PLAYERS];

	std::ifstream inputFile;
	inputFile.open("PlayerData.txt");

	if (inputFile.is_open())
	{
		std::string line;
		std::string item;
		int i = 0;

		while (std::getline(inputFile, line))
		{
			std::stringstream line_ss(line);

			int dataType = 0;
			while (std::getline(line_ss, item, ','))
			{
				if (dataType == 0)
				{
					names[i] = item;
				}
				else if (dataType == 1)
				{
					if (item == "")
					{
						scores[i] = 0;
					}
					else
					{
						scores[i] = std::stoi(item);
					}
				}
				else if (dataType == 2)
				{
					charNums[i] = item;
				} // End if else

				dataType++;
			} // End while

			std::cout << "Player " << i + 1 << ":\n" << "Name: " << names[i] << "\nScore: " << scores[i] << "\nCharacter Number: " << charNums[i] << std::endl;
			i++;
			if (i >= MAX_PLAYERS)
			{
				break;
			}
		} // End while

		inputFile.close();
		std::cout << "Read File Success!" << std::endl;
	} // End if
	else
	{
		std::cout << "Error opening file." << std::endl;
	}


	std::string tempString;
	int tempInt = 0;

	for (int i = 1; i < MAX_PLAYERS; i++) // Loop down the array
	{
		for (int j = i; j > 0; j--)
		{
			if (scores[j] > scores[j - 1])
			{
				tempString = names[j - 1];
				names[j - 1] = names[j];
				names[j] = tempString;
				tempInt = scores[j - 1];
				scores[j - 1] = scores[j];
				scores[j] = tempInt;
				tempString = charNums[j - 1];
				charNums[j - 1] = charNums[j];
				charNums[j] = tempString;
			}
			else
			{
				break;
			}
		}
	}


	// Write to the file
	// Save to file
	std::ofstream outputFile;
	outputFile.open("PlayerData.txt");

	if (outputFile.is_open())
	{
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			outputFile << names[i] << ",";
			outputFile << scores[i] << ",";
			outputFile << charNums[i] << ",";
			outputFile << std::endl;
		}

		outputFile.close();
		std::cout << "File write success!" << std::endl;
	}
	else
	{
		std::cout << "Error opening file." << std::endl;
	}


}