#include "SpringApplication.h"

using namespace sm;
using namespace sf;
using namespace std;

const int SpringApplication::cNumTimecharts = 4;
const Time SpringApplication::cMaximumTimeDelta = seconds(1.0 / 30.0);

SpringApplication::SpringApplication()
{
	_positionTimechart = make_shared<Timechart>();
	_speedTimechart = make_shared<Timechart>();
}

SpringApplication::~SpringApplication()
{
}

void SpringApplication::run()
{
	_window.create(sf::VideoMode(1680, 1050), "Mass on Spring Simulation");
	_view = _window.getDefaultView();

	_clock.restart();

	_topLeftTimechart.registerTimechart(_positionTimechart, Color::Green);
	_topLeftTimechart.registerTimechart(_speedTimechart, Color::Red);
	_topRightTimechart.registerTimechart(_speedTimechart, Color::Red);
	_bottomLeftTimechart.registerTimechart(_speedTimechart, Color::Red);
	_bottomRightTimechart.registerTimechart(_speedTimechart, Color::Red);

	Time totalElapsedTime = Time::Zero;
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

		sf::Time elapsedTime = _clock.getElapsedTime();
		_clock.restart();

		if (elapsedTime > cMaximumTimeDelta)
		{
			elapsedTime = cMaximumTimeDelta;
		}

		totalElapsedTime += elapsedTime;
		
		updateControlsPositions();
		
		float springLength = fabs(sinf(totalElapsedTime.asSeconds()));

		_springView.setSpringLength(springLength);
		_positionTimechart->addRecord(totalElapsedTime, springLength);
		_speedTimechart->addRecord(totalElapsedTime, -springLength);

		float multipler = 1.0f / (1.0f+ totalElapsedTime.asSeconds());
		float timeSin = sinf(totalElapsedTime.asSeconds());
		float timeCos = cosf(totalElapsedTime.asSeconds());
		_statechart.addRecord(StatechartRecord(multipler*timeSin, multipler*timeCos));

		_window.clear(sf::Color::White);
		_springView.draw(_window);
		_topLeftTimechart.draw(_window, totalElapsedTime);
		_topRightTimechart.draw(_window, totalElapsedTime);
		_bottomLeftTimechart.draw(_window, totalElapsedTime);
		_bottomRightTimechart.draw(_window, totalElapsedTime);
		_statechart.draw(_window);
		_window.display();
	}
}

void SpringApplication::updateControlsPositions()
{
	auto windowSize = _window.getSize();

	float simulationWidth = 0.33f*windowSize.x;

	float timechartPixelsWidth = (windowSize.x - simulationWidth) / 2.0f;
	float timechartPixelsHeight = (0.50f / (cNumTimecharts / 2))*windowSize.y;

	float statechartWidth = windowSize.x - simulationWidth;
	float statechartHeight = 0.50f * windowSize.y;

	_springView.setViewport(FloatRect(
		0, 0, simulationWidth, windowSize.y
	));

	_topLeftTimechart.setViewport(FloatRect(
		simulationWidth, 0,
		timechartPixelsWidth, timechartPixelsHeight
	));

	_topRightTimechart.setViewport(FloatRect(
		simulationWidth+timechartPixelsWidth, 0,
		timechartPixelsWidth, timechartPixelsHeight
	));

	_bottomLeftTimechart.setViewport(FloatRect(
		simulationWidth, timechartPixelsHeight,
		timechartPixelsWidth, timechartPixelsHeight
	));

	_bottomRightTimechart.setViewport(FloatRect(
		simulationWidth+timechartPixelsWidth, timechartPixelsHeight,
		timechartPixelsWidth, timechartPixelsHeight
	));

	_statechart.setViewport(FloatRect(
		simulationWidth, 2.0f * timechartPixelsHeight,
		statechartWidth, statechartHeight
	));
}
