#include "SpringApplication.h"

using namespace sm;
using namespace sf;

SpringApplication::SpringApplication()
{
}

SpringApplication::~SpringApplication()
{
}

void SpringApplication::run()
{
	_window.create(sf::VideoMode(800, 600), "Mass on Spring Simulation");
	_view = _window.getDefaultView();

	_clock.restart();

	while (_window.isOpen())
	{
		sf::Event windowEvent;
		if (_window.pollEvent(windowEvent))
		{
			if (windowEvent.type == Event::Closed)
			{
				_window.close();
			}

			if (windowEvent.type == Event::Resized)
			{
				auto windowSize = _window.getSize();
				_view = View(FloatRect(0.0f, 0.0f, windowSize.x, windowSize.y));
				_window.setView(_view);
			}
		}
		
		float springLength = 0.5f*
			(1.0f + fabs(sinf(_clock.getElapsedTime().asSeconds())));

		sf::Time elapsedTime = _clock.getElapsedTime();

		_springView.setSpringLength(springLength);
		_positionTimechart.addRecord(elapsedTime, springLength);

		auto windowSize = _window.getSize();
		float simulationWidth = 0.33f*windowSize.x;

		int cNumOfTimecharts = 3;
		float timechartPixelsHeight = (1.0f / cNumOfTimecharts)*windowSize.y;

		_springView.setViewport(FloatRect(
			0, 0, simulationWidth, windowSize.y
		));

		_positionTimechart.setViewport(FloatRect(
			simulationWidth, 0, 
			windowSize.x - simulationWidth, timechartPixelsHeight
		));

		_window.clear(sf::Color::White);
		_springView.draw(_window);
		_positionTimechart.draw(_window, elapsedTime);
		_window.display();
	}
}
