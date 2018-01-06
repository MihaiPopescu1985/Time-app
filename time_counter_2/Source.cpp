#include <vector>
#include <SFML/Graphics.hpp>
#include "DataBase.h"

#define MOUSE_X ((float)sf::Mouse::getPosition(window).x)
#define MOUSE_Y ((float)sf::Mouse::getPosition(window).y)

#pragma warning(suppress : 4996)

int main()
{
	sf::RenderWindow window(sf::VideoMode(1030, 600), "Time manager", 4);

	sf::Image icon;
	icon.loadFromFile("50x43.png");

	window.setIcon(50, 43, icon.getPixelsPtr());
	window.setVerticalSyncEnabled(true);

	sf::Event event;

	sf::Font font;
	font.loadFromFile("arial.ttf");

	DataBase DB(&window, &event, &font);


	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				DB.SaveBeforeExit();
		}
		window.clear(sf::Color(164, 164, 164, 255));

		DB.Process(MOUSE_X, MOUSE_Y);
		DB.Display();

		window.display();
	}
	return 0;
}