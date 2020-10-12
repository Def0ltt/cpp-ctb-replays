#include <json/json.h>
#include <json/value.h>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/Glsl.hpp>
#include <windows.h>
#include <string>


using namespace std;

// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f
sf::Color hsv(int hue, float sat, float val)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255);
	case 1: return sf::Color(q * 255, val * 255, p * 255);
	case 2: return sf::Color(p * 255, val * 255, t * 255);
	case 3: return sf::Color(p * 255, q * 255, val * 255);
	case 4: return sf::Color(t * 255, p * 255, val * 255);
	case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}

//Variables
bool rubbish;

float x[50] = { 0.0f };
float lastx[50] = { 0.0f };
float y[50] = { 772.0f };

float word[50];

float sleeptime[50] = { 0.0f };

int counter4 = 0;
int counter5 = 0;
int counter6 = 0;
int counter7 = 0;
int namesCounter = 0;
int namesPos = 0;
int actualNamePos = 0;

int button1Active[50] = { 0 };
int button2Active[50] = { 0 };

int fontSize;

string parsercode;
string playerName[50];
string playerMod[50];

//Creating A Window
sf::RenderWindow window(sf::VideoMode(1536, 900), "CTB KNOCKOUTS POG", sf::Style::Titlebar | sf::Style::Close);

//Creating "Catch Things/Textures"
sf::Texture playerTexture;
std::vector<sf::RectangleShape> player(50);
std::vector<sf::RectangleShape> playerButton1(50);
std::vector<sf::RectangleShape> playerButton2(50);

sf::Font font;
sf::Text playerNames[50];

int main()
{
	ifstream settings_file("settings.json", std::ifstream::binary);
	Json::Value settings;
	settings_file >> settings;

	int playerAmount = (settings["Settings"]["playerAmount"]).asInt();
	fontSize = 900 / playerAmount;

	const int playerss = playerAmount;

	if (settings["Settings"]["parseReplays"] == true) {
		while (counter7 <= (playerAmount - 1)) {
			ofstream ParserFile("rawrpdata/parser.js");
			parsercode = "const osuReplayParser = require('osureplayparser'); const utils = require('./node_modules/osureplayparser/utils/utils.js'); const replayPath = 'C:/Users/Danila/source/repos/cpp-ctb-replays/cpp-ctb-replays/rawrpdata/replays/";
			parsercode += to_string(counter7);
			parsercode += ".osr'; const replay = osuReplayParser.parseReplay(replayPath); var replayDonee = replay.replace(/\\|/g, '\\n'); var replayDoneee = replayDonee.replace(/,/g, '\\n'); var fs = require('fs'); fs.writeFileSync('catchthings/info/catchthing";
			parsercode += to_string(counter7);
			parsercode += ".txt', replayDoneee);";
			ParserFile << parsercode;
			ParserFile.close();
			system("node rawrpdata/parser.js");
			counter7 = counter7 + 1;
			cout << "Replay " << counter7 << " Parsed! \n";
		}
	}
	cout << "All replays parsed. " << endl << playerAmount << " replays parsed!" << endl;

	//Setting FPS limit to 10000 cuzynot
	window.setFramerateLimit((settings["Settings"]["fpsLimit"]).asInt());

	//Coloring/Texturing CatchThings
	playerTexture.loadFromFile("catchthings/textures/defaultguy.png");

	int counter = 0;
	int counter2 = 0;
	int colorz = 360 / playerAmount;
	while (counter <= (playerAmount - 1)) {
		player[counter].setTexture(&playerTexture);
		player[counter].setFillColor(sf::Color(hsv(counter2, 100, 100)));
		player[counter].setSize(sf::Vector2f(128.0f,128.0f));
		playerNames[counter].setFillColor(sf::Color(hsv(counter2, 100, 100)));
		counter = counter + 1;
		counter2 = counter2 + colorz;
	}
	cout << "Player models created." << endl;

	//Reading text files with info
	int modFound[50] = { 0 };
	ifstream modfile[50];

	string modName[50];
	string modNumber[50];

	ifstream filered[50];
	int counter3 = 0;
	string updaterthing;
	while (counter3 <= (playerAmount - 1)) {
		modfile[counter3].open("catchthings/modinfo.txt");
		updaterthing = "catchthings/info/catchthing"; updaterthing += to_string(counter3); updaterthing += ".txt";
		filered[counter3].open(updaterthing);
		getline(filered[counter3], playerName[counter3]);
		getline(filered[counter3], playerMod[counter3]);
		if (playerMod[counter3] == "0") { modFound[counter3] = 1; modName[counter3] = "NM"; }
		while (modFound[counter3] == 0) {
			modfile[counter3] >> modName[counter3];
			modfile[counter3] >> modNumber[counter3];
			if (modNumber[counter3] == playerMod[counter3]) { modFound[counter3] = 1; }
		}
		playerName[counter3] += " +";
		playerName[counter3] += modName[counter3];
		playerNames[counter3].setString(playerName[counter3]);
		cout << playerName[counter3] << "'s replays opened. Total[" << counter3+1 << "]" << endl;
		counter3 = counter3 + 1;
	}
	cout << "Parsed files opened." << endl;

	//Creating Exit Event
	sf::Event ev;

	//Creating Clocks
	sf::Clock clockc[50];

	font.loadFromFile("fonts/Exo2-Light.ttf");
	namesPos = fontSize;
	if (fontSize >= 70) {
		fontSize = 70;
	}

	counter2 = 0;

	while (namesCounter <= (playerAmount - 1)) {
		playerNames[namesCounter].setCharacterSize(fontSize);
		playerNames[namesCounter].setPosition(sf::Vector2f((fontSize*2)+3+3, actualNamePos));
		playerButton1[namesCounter].setFillColor(sf::Color(hsv(counter2, 100, 100)));
		playerButton1[namesCounter].setSize(sf::Vector2f(fontSize, fontSize));
		playerButton1[namesCounter].setPosition(sf::Vector2f(0, actualNamePos));
		playerButton2[namesCounter].setFillColor(sf::Color(hsv(counter2, 100, 100)));
		playerButton2[namesCounter].setSize(sf::Vector2f(fontSize, fontSize));
		playerButton2[namesCounter].setPosition(sf::Vector2f(fontSize+3, actualNamePos));
		playerNames[namesCounter].setFont(font);
		actualNamePos = namesPos;
		namesPos = namesPos + fontSize;
		counter2 = counter2 + colorz;
		namesCounter = namesCounter + 1;
	}

	cout << "Everything is ready, starting!";

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

		//Catch Thing - Position Finder
		while (counter4 <= (playerAmount - 1)) {
			sf::Time elapsed = clockc[counter4].getElapsedTime();

			if (elapsed.asMilliseconds() >= sleeptime[counter4]) {
				filered[counter4] >> word[counter4];
				sleeptime[counter4] = word[counter4];
				filered[counter4] >> word[counter4];
				lastx[counter4] = x[counter4];
				x[counter4] = (word[counter4] + 128) * 2;
				if (x[counter4] > lastx[counter4]) { button2Active[counter4] = 1; button1Active[counter4] = 0; }
				if (x[counter4] < lastx[counter4]) { button1Active[counter4] = 1; button2Active[counter4] = 0; }
				if (x[counter4] == lastx[counter4]) { button1Active[counter4] = 0; button2Active[counter4] = 0; }
				filered[counter4] >> word[counter4];
				filered[counter4] >> word[counter4];
				y[counter4] = 772.0f;
				player[counter4].setPosition(x[counter4], y[counter4]);
				clockc[counter4].restart();
			}
			counter4 = counter4 + 1;
		}
		counter4 = 0;

		//Render
		window.clear();
		while (counter5 <= (playerAmount - 1)) {
			window.draw(playerNames[counter5]);
			window.draw(player[counter5], sf::BlendAdd);
			if (button1Active[counter5] == 1) { window.draw(playerButton1[counter5]); }
			if (button2Active[counter5] == 1) { window.draw(playerButton2[counter5]); }
			counter5 = counter5 + 1;
		}
		counter5 = 0;
		window.display(); //Display drawn stuff
	}

	return 0;
}