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

const Time Timechart::cMinimumInbetweenTime = seconds(0.1f);

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
	_chartColor(sf::Color::Green)
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

void TimechartsView::draw(RenderWindow &window, Time currentTime)
{
	Time boundaryTime = currentTime - _timespanCovered;
	deleteOldRecords(boundaryTime);

	RectangleShape background(Vector2f(_viewport.width-1, _viewport.height-1));
	background.setFillColor(Color(83, 83, 83));
	background.setPosition(Vector2f(_viewport.left+1, _viewport.top+1));
	background.setOutlineColor(Color::Black);
	background.setOutlineThickness(1);

	window.draw(background);

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
		float heightPercent = 0.95f * (1.0f - (0.5f + 0.5f*it->Value)) + 0.025f;

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
