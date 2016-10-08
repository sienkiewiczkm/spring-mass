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

const Time Timechart::cMinimumInbetweenTime = seconds(0.05f);

Timechart::Timechart()
{
}

void Timechart::addRecord(sf::Time eventTime, float value)
{
	assert(_records.empty() || _records.back().EventTime <= eventTime);

	if (!_records.empty())
	{
		if ((eventTime - _records.back().EventTime) < cMinimumInbetweenTime)
		{
			return;
		}
	}

	_records.push_back(TimechartRecord(eventTime, value));
}

void Timechart::deleteOldRecords(sf::Time thresholdTime)
{
	while (!_records.empty() && _records.front().EventTime < thresholdTime)
	{
		_records.pop_front();
	}
}

const std::list<TimechartRecord>& sm::Timechart::getRecords()
{
	return _records;
}

TimechartsView::TimechartsView() :
	_chartColor(sf::Color::Green),
	_minimum(-1.5f),
	_maximum(+4.0f)
{
	_timespanCovered = seconds(30.0f);
}

void TimechartsView::setViewport(sf::FloatRect viewport)
{
	_viewport = viewport;
}

void TimechartsView::setColor(sf::Color color)
{
	_chartColor = color;
}

void TimechartsView::registerTimechart(
	std::shared_ptr<Timechart> timechart, 
	sf::Color assignedColor
)
{
	TimechartInfo info;
	info.Timechart = timechart;
	info.AssignedColor = assignedColor;
	_records.push_back(info);
}

void TimechartsView::setRange(float minimum, float maximum)
{
	_minimum = minimum;
	_maximum = maximum;
}

void TimechartsView::draw(RenderWindow &window, Time currentTime)
{
	Time boundaryTime = currentTime - _timespanCovered;
	deleteOldRecords(boundaryTime);

	RectangleShape background(Vector2f(_viewport.width-1, _viewport.height-1));
	background.setFillColor(Color(110, 110, 110));
	background.setPosition(Vector2f(_viewport.left+1, _viewport.top+1));
	background.setOutlineColor(Color::White);
	background.setOutlineThickness(1.0f);

	window.draw(background);
	drawZeroLine(window);

	for (auto &timechart : _records)
	{
		drawTimechart(
			window,
			timechart.Timechart,
			timechart.AssignedColor,
			boundaryTime
		);
	}
}

void TimechartsView::deleteOldRecords(Time thresholdTime)
{
	for (auto &timechart : _records)
	{
		timechart.Timechart->deleteOldRecords(thresholdTime);
	}
}

void TimechartsView::drawTimechart(
	sf::RenderWindow &window, 
	std::shared_ptr<Timechart> timechart,
	sf::Color color,
	Time boundaryTime
)
{
	vector<Vertex> vertices;
	float timespanSeconds = _timespanCovered.asSeconds();
	auto records = timechart->getRecords();

	for (auto it = records.begin(); it != records.end(); ++it)
	{
		Time elapsedFromBoundary = it->EventTime - boundaryTime;
		float elapsedSec = elapsedFromBoundary.asSeconds();
		float widthPercent = elapsedSec / timespanSeconds;

		float heightPercent = 1.0f - 
			((it->Value - _minimum) / (_maximum - _minimum));

		Vertex vertex;
		vertex.position = Vector2f(
			_viewport.left + _viewport.width * widthPercent,
			_viewport.top + _viewport.height * heightPercent
		);

		vertex.color = color;
		vertices.push_back(vertex);
	}

	if (!vertices.empty())
	{
		window.draw(&vertices[0], vertices.size(), PrimitiveType::LinesStrip);
	}
}

void TimechartsView::drawZeroLine(sf::RenderWindow & window)
{
	vector<Vertex> zeroLine;
	float zeroHeightPercent = (-_minimum) / (_maximum - _minimum);
	float zeroHeight = _viewport.top 
		+ _viewport.height * (1.0f - zeroHeightPercent);

	zeroLine.push_back(
		Vertex(
			Vector2f(_viewport.left, zeroHeight),
			Color::Black
		)
	);

	zeroLine.push_back(
		Vertex(
			Vector2f(_viewport.left + _viewport.width, zeroHeight),
			Color::Black
		)
	);

	window.draw(&zeroLine[0], zeroLine.size(), PrimitiveType::LinesStrip);
}
