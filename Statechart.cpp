#include "Statechart.h"

using namespace sm;
using namespace sf;
using namespace std;

const int Statechart::cNumMaxRecords = 100000;
const int Statechart::cOutlineThickness = 1;

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

	background.setOutlineColor(Color::Black);
	background.setOutlineThickness(cOutlineThickness);
	background.setFillColor(Color(83, 83, 83));

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
