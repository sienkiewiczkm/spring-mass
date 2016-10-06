#include "SpringApplication.h"

using namespace sm;

SpringApplication::SpringApplication()
{
}

SpringApplication::~SpringApplication()
{
}

void SpringApplication::run()
{
	_window.create(sf::VideoMode(800, 600), "Mass on Spring Simulation");

	_clock.restart();
	_springView.setViewport(sf::Rect<float>(0, 0, 400, 500));
	while (_window.isOpen())
	{
		sf::Event windowEvent;
		if (_window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed)
			{
				_window.close();
			}
		}
		
		float springLength = 0.5f*
			(1.0f + sinf(_clock.getElapsedTime().asSeconds()));
		_springView.setSpringLength(springLength);

		_window.clear(sf::Color::White);
		_springView.draw(_window);
		_window.display();
	}
}
