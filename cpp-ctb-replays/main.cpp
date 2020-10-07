#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>

using namespace std;

//Variables
bool rubbish;

float x = 0.0f;
float y = 0.0f;
float x2 = 0.0f;
float y2 = 0.0f;

float word;
float word2;

float sleeptime1 = 0.0f;
float sleeptime2 = 0.0f;


//Creating A Window
sf::RenderWindow window(sf::VideoMode(1536, 900), "CTB KNOCKOUTS POG", sf::Style::Titlebar | sf::Style::Close);

//Creating "Catch Things/Textures"
sf::RectangleShape player(sf::Vector2f(128.0f, 128.0f));
sf::RectangleShape player2(sf::Vector2f(128.0f, 128.0f));
sf::Texture player1Texture;
sf::Texture player2Texture;

int main()
{
	//Setting FPS limit to 1000
	window.setFramerateLimit(1000);

	//Coloring/Texturing Cursors/Hitcircles
	player.setFillColor(sf::Color::White);
	player2.setFillColor(sf::Color::White);
	player1Texture.loadFromFile("redguy.png");
	player2Texture.loadFromFile("yellowguy.png");
	player.setTexture(&player1Texture);
	player2.setTexture(&player2Texture);

	//Reading text files with info
	fstream filered;
	filered.open("catchthing1.txt");

	fstream filered2;
	filered2.open("catchthing2.txt");

	//Creating Exit Event
	sf::Event ev;

	//Creating Clocks
	sf::Clock clockc1;
	sf::Clock clockc2;

	cout << "Everything is ready, start? (type anything to proceed):";
	cin >> rubbish;

	//Main Loop
	while (window.isOpen())
	{

		//Close on ESC
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}
		}

		//Catch Thing 1 - Position Finder
		sf::Time elapsedc1 = clockc1.getElapsedTime();

		if (elapsedc1.asMilliseconds() >= sleeptime1) {
			filered >> word;
			sleeptime1 = word;
			filered >> word;
			x = (word + 128) * 2;
			y = 772;
			filered >> word;
			filered >> word;
			player.setPosition(x, y);
			clockc1.restart();
		}

		//Catch Thing 2 - Position Finder
		sf::Time elapsedc2 = clockc2.getElapsedTime();

		if (elapsedc2.asMilliseconds() >= sleeptime2)
		{
			filered2 >> word2;
			sleeptime2 = word2;
			filered2 >> word2;
			x2 = (word2 + 128) * 2;
			y2 = 772;
			filered2 >> word2;
			filered2 >> word2;
			player2.setPosition(x2, y2);
			clockc2.restart();
		}

		//Render
		window.clear();
		window.draw(player2);
		window.draw(player);
		window.display(); //Display drawn stuff

	}

	return 0;
}