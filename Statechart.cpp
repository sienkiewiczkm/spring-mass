#include "Statechart.h"

using namespace sm;
using namespace sf;
using namespace std;

const int Statechart::cNumMaxRecords = 100000;
const float Statechart::cOutlineThickness = 1.0f;
const float Statechart::cMinimumNormDifference = 0.0005f;

StatechartRecord::StatechartRecord() :
	XAxisValue(0.0f),
	YAxisValue(0.0f)
{
}

StatechartRecord::StatechartRecord(float xAxisValue, float yAxisValue) :
	XAxisValue(xAxisValue),
	YAxisValue(yAxisValue)
{
}

Statechart::Statechart() :
	_color(Color::Green)
{
}

void Statechart::setViewport(FloatRect viewport)
{
	_viewport = viewport;
}

void Statechart::setColor(Color color)
{
	_color = color;
}

void Statechart::addRecord(StatechartRecord record)
{
	if (!_records.empty())
	{
		Vector2f lastState(_records.back().XAxisValue, _records.back().YAxisValue);
		Vector2f insertedState(record.XAxisValue, record.YAxisValue);
		auto difference = lastState - insertedState;
		auto lengthSq = difference.x * difference.x + difference.y * difference.y;
		auto length = fabs(lengthSq);
		if (length < cMinimumNormDifference)
		{
			return;
		}
	}

	_records.push_back(record);

	if (_records.size() > cNumMaxRecords)
	{
		_records.pop_front();
	}
}

void Statechart::draw(RenderWindow &window)
{
	RectangleShape background(Vector2f(
		_viewport.width - cOutlineThickness,
		_viewport.height - cOutlineThickness
	));

	background.setPosition(Vector2f(
		_viewport.left + cOutlineThickness,
		_viewport.top + cOutlineThickness
	));

	background.setOutlineColor(Color::White);
	background.setOutlineThickness(cOutlineThickness);
	background.setFillColor(Color(110, 110, 110));

	window.draw(background);

	vector<Vertex> vertices;

	float halfWidth = _viewport.width * 0.5f;
	float halfHeight = _viewport.height * 0.5f;
	float minViewportHalfSize = min(halfWidth, halfHeight);

	for (auto it = _records.begin(); it != _records.end(); ++it)
	{
		Vertex vertex;
		float xPos = _viewport.left + halfWidth 
			+ minViewportHalfSize * it->XAxisValue;
		float yPos = _viewport.top + halfHeight 
			+ minViewportHalfSize * it->YAxisValue;

		vertex.position = Vector2f(xPos, yPos);
		vertex.color = _color;
		vertices.push_back(vertex);
	}

	if (!vertices.empty())
	{
		window.draw(&vertices[0], vertices.size(), PrimitiveType::LinesStrip);
	}
}
