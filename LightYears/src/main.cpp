#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(100, 100), "Hello LightYears");
	std::cout << "Hello Worlds!" << std::endl;

	while (renderWindow.isOpen())
	{
		sf::Event windowEvent;
		while (renderWindow.pollEvent(windowEvent))
		{
			if(windowEvent.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}
		//renderWindow.clear();
		//renderWindow.display();
	}





	return 0;
}
