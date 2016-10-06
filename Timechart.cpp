#include "Timechart.h"

#include <cassert>
#include <vector>

using namespace sm;
using namespace sf;
using namespace std;

TimechartRecord::TimechartRecord() :
	EventTime(Time::Zero),
	Value(0.0f)
{
}

TimechartRecord::TimechartRecord(Time eventTime, float value) :
	EventTime(eventTime),
	Value(value)
{ 
}

Timechart::Timechart()
{
	_timespanCovered = seconds(30.0f);
}

void Timechart::setViewport(sf::FloatRect viewport)
{
	_viewport = viewport;
}

void Timechart::addRecord(Time eventTime, float value)
{
	assert(_records.empty() || _records.back().EventTime <= eventTime);
	_records.push_back(TimechartRecord(eventTime, value));
}

void Timechart::draw(RenderWindow &window, Time currentTime)
{
	deleteOldRecords(currentTime);
	
	vector<Vertex> vertices;
	Time boundaryTime = currentTime - _timespanCovered;
	float timespanSeconds = _timespanCovered.asSeconds();

	for (auto it = _records.begin(); it != _records.end(); ++it)
	{
		Time elapsedFromBoundary = it->EventTime - boundaryTime;
		float elapsedSec = elapsedFromBoundary.asSeconds();
		float widthPercent = elapsedSec / timespanSeconds;
		float heightPercent = 1.0f - it->Value;

		Vertex vertex;
		vertex.position = Vector2f(
			_viewport.left + _viewport.width * widthPercent,
			_viewport.top + _viewport.height * heightPercent
		);

		vertex.color = Color::Green;
		vertices.push_back(vertex);
	}

	RectangleShape background(Vector2f(_viewport.width, _viewport.height));
	background.setPosition(Vector2f(_viewport.left, _viewport.top));
	background.setFillColor(Color::Black);

	window.draw(background);
	
	if (!vertices.empty())
	{
		window.draw(&vertices[0], vertices.size(), PrimitiveType::LinesStrip);
	}
}

void Timechart::deleteOldRecords(Time currentTime)
{
	Time boundaryTime = currentTime - _timespanCovered;
	while (!_records.empty() && _records.front().EventTime < boundaryTime)
	{
		_records.pop_front();
	}
}