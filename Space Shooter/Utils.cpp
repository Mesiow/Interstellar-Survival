#include "Utils.h"

void save_to_file(int score)
{
	std::ifstream readFile("C:/Users/Mesio/Desktop/Visual Studio C++ Projects/SFML/Space Survival/Space Shooter/Score/file.txt");

	int s;
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> s;
		}
	}
	readFile.close();

	std::ofstream writeFile("C:/Users/Mesio/Desktop/Visual Studio C++ Projects/SFML/Space Survival/Space Shooter/Score/file.txt");

	if (writeFile.is_open())
	{
		if (s > score)
			score = s;

		writeFile << score;
	}	
	
	writeFile.close();
}

int load_score_from_file()
{
	std::ifstream file("C:/Users/Mesio/Desktop/Visual Studio C++ Projects/SFML/Space Survival/Space Shooter/Score/file.txt", std::ios::in);

	if (!file.is_open())
		std::cout << "file failed load";

	int s;
	file >> s;

	int score = s;
	file.close();

	return score;
}



int randomInt(int low, int high)
{
	std::random_device rd; //initial seed for generator
	std::default_random_engine gen(rd()); //random num gen
	std::uniform_int_distribution<int> dist(low, high); //gen random num from low to high

    int num = dist(gen);
	return num;
}

float randomFloat(float low, float high)
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_real_distribution<float> dist(low, high);

	float num = dist(gen);
	return num;
}

float vectorLength(sf::Vector2f v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

sf::Vector2f normalize(sf::Vector2f v, float length)
{
	if (length == 0)
		return sf::Vector2f(0.0f, 0.0f);
	else
		return v / length;
}
