#include "SpringApplication.h"

using namespace sm;
using namespace sf;
using namespace std;

const int SpringApplication::cNumTimecharts = 4;
const Time SpringApplication::cMaximumTimeDelta = seconds(1.0f / 30.0f);

SpringApplication::SpringApplication() :
	_totalElapsedTime(Time::Zero)
{
	_positionTimechart = make_shared<Timechart>();
	_velocityTimechart = make_shared<Timechart>();
	_accelerationTimechart = make_shared<Timechart>();
}

SpringApplication::~SpringApplication()
{
}

void SpringApplication::run()
{
	_window.create(sf::VideoMode(1680, 1050), "Mass on Spring Simulation");
	_view = _window.getDefaultView();

	setup();

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

		_totalElapsedTime += elapsedTime;
		
		update();
		draw();
	}
}

void SpringApplication::setup()
{
	_clock.restart();

	_topLeftTimechart.registerTimechart(_positionTimechart, Color::Green);
	_topLeftTimechart.registerTimechart(_velocityTimechart, Color::Red);
	_topLeftTimechart.registerTimechart(_accelerationTimechart, Color::Blue);

	_topRightTimechart.registerTimechart(_velocityTimechart, Color::Red);
	_bottomLeftTimechart.registerTimechart(_velocityTimechart, Color::Red);
	_bottomRightTimechart.registerTimechart(_velocityTimechart, Color::Red);

	setupSimulation();
}

void SpringApplication::setupSimulation()
{
	_simulation = make_shared<MassSpringSimulation>(
		1.0f, 1.0f, 0.8f, 0.5f, 0.8f, 0.01f
	);
}

void SpringApplication::update()
{
	updateControlsPositions();

	_simulation->step();

	float position = _simulation->getPosition();
	float velocity = _simulation->getVelocity();

	_springView.setSpringLength(position);

	_positionTimechart->addRecord(_totalElapsedTime, -position);
	_velocityTimechart->addRecord(_totalElapsedTime, velocity);

	_accelerationTimechart->addRecord(
		_totalElapsedTime, 
		_simulation->getAcceleration()
	);

	_statechart.addRecord(StatechartRecord(position, velocity));
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

void SpringApplication::draw()
{
	_window.clear(sf::Color::White);
	_springView.draw(_window);
	_topLeftTimechart.draw(_window, _totalElapsedTime);
	_topRightTimechart.draw(_window, _totalElapsedTime);
	_bottomLeftTimechart.draw(_window, _totalElapsedTime);
	_bottomRightTimechart.draw(_window, _totalElapsedTime);
	_statechart.draw(_window);
	_window.display();
}
