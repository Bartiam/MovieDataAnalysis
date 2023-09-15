#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "nlohmann/json.hpp"

struct Movie
{
	short Release;
	std::string name;
	std::string country;
	std::string screenwriter;
	std::string regisseur;
	std::string producer;
	std::string studio;
	std::map <std::string, std::string> actors;
};

void reading_jsone_file(std::ifstream& readJsoneFile, nlohmann::json& dict)
{
	readJsoneFile.open("..//infoAboutMovie.json");
	if (!readJsoneFile.is_open())
		std::cerr << "Error! The file was not open. " << std::endl;
	else
	{
		readJsoneFile >> dict;
		readJsoneFile.close();
	}
}

void convertation_jsone_in_vector(const nlohmann::json& dict, std::vector<Movie>& movies)
{
	for (auto& temp : dict.items())
	{
		Movie movie;
		movie.name = temp.key();
		movie.Release = temp.value()["Release"];
		movie.country = temp.value()["Country"];
		movie.screenwriter = temp.value()["Screenwriter"];
		movie.regisseur = temp.value()["Regisseur"];
		movie.producer = temp.value()["Producer"];
		movie.studio = temp.value()["Studio"];
		movie.actors = temp.value()["Actors"];
		movies.emplace_back(movie);
	}
}

void find_actor(const std::vector<Movie>& movies,const std::string& nameActor)
{
	std::string firstName, secondName;
	for (int i = 0; i < movies.size(); ++i)
	{
		for (const auto& nameAndNickname : movies[i].actors)
		{
			std::stringstream stream(nameAndNickname.second);
			stream >> firstName >> secondName;
			if (firstName == nameActor || secondName == nameActor ||
				nameAndNickname.second == nameActor)
			{
				std::cout << "The movie: " << movies[i].name << "\nRole: " <<
					nameAndNickname.first << "\nActor: " << nameAndNickname.second << std::endl;
			}
		}
	}
}

int main()
{
	std::vector<Movie> movies;
	std::string nameActor;
	std::ifstream readJsoneFile;
	nlohmann::json dict;

	reading_jsone_file(readJsoneFile, dict);
	convertation_jsone_in_vector(dict, movies);

	std::cout << "A program for finding information about an actor: " << std::endl;
	while (nameActor != "Exit" || nameActor != "exit")
	{
		std::cout << "Command:\nName of the actor\nExit" << std::endl;
		std::cout << "Enter the name of the actor: ";
		std::getline(std::cin, nameActor);

		if (nameActor == "Exit" || nameActor == "exit")
			return 0;

		system("cls");

		find_actor(movies, nameActor);
	}
}