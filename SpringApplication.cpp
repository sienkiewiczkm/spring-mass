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
	_positionTimechart.setViewport(sf::FloatRect(400, 0, 200, 200));

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
			(1.0f + fabs(sinf(_clock.getElapsedTime().asSeconds())));

		sf::Time elapsedTime = _clock.getElapsedTime();

		_springView.setSpringLength(springLength);
		_positionTimechart.addRecord(elapsedTime, springLength);

		_window.clear(sf::Color::White);
		_springView.draw(_window);
		_positionTimechart.draw(_window, elapsedTime);
		_window.display();
	}
}
