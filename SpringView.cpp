#include "SpringView.h"
#include <algorithm>

using namespace sm;
using namespace sf;
using namespace std;

const float SpringView::cBaseThickness = 16.0f;
const float SpringView::cSpringThickness = 8.0f;

SpringView::SpringView() :
	_massRadius(50.0),
	_massOutlineThickness(2.0),
	_massBaseDistance(50.0),
	_springMinimumLength(0.0f),
	_springMaximumLength(1.0),
	_springLength(0.5f)
{
}

SpringView::~SpringView()
{
}

void SpringView::setViewport(const FloatRect &viewport)
{
	_viewport = viewport;
}

void SpringView::setMassBaseDistance(float distance)
{
	_massBaseDistance = distance;
}

void SpringView::setSpringMaximumLength(float maximumLength)
{
	_springMaximumLength = maximumLength;
}

void SpringView::setSpringMinimumLength(float minimumLength)
{
	_springMinimumLength = minimumLength;
}

void SpringView::setSpringLength(float springLength)
{
	_springLength = springLength;
}

void SpringView::draw(RenderWindow &window) 
{
	drawSpring(window);
	drawBase(window);
	drawMass(window);
}

void SpringView::drawMass(RenderWindow & window)
{
	float springLength = getSpringLengthInPx();

	CircleShape mass(_massRadius);
	mass.setPosition(Vector2f(
		_viewport.left + _viewport.width / 2.0f - _massRadius,
		_viewport.top + _viewport.height - springLength - _massRadius
	));

	mass.setFillColor(Color::Red);
	mass.setOutlineThickness(_massOutlineThickness);
	mass.setOutlineColor(Color::Black);
	window.draw(mass);
}

void SpringView::drawSpring(RenderWindow &window)
{
	float springLength = getSpringLengthInPx();

	RectangleShape spring(Vector2f(cSpringThickness, springLength));
	spring.setPosition(Vector2f(
		(_viewport.width - cSpringThickness) / 2.0f,
		_viewport.height - springLength
	));
	
	spring.setFillColor(Color::Blue);
	window.draw(spring);
}

void SpringView::drawBase(RenderWindow & window)
{
	RectangleShape base(Vector2f(_viewport.width, cBaseThickness));
	base.setPosition(Vector2f(
		_viewport.left,
		_viewport.top + _viewport.height - cBaseThickness
	));

	base.setFillColor(Color::Green);
	window.draw(base);
}

float SpringView::getSpringLengthInPx()
{
	float springMaximumPixels = _viewport.height - cBaseThickness
		- _massRadius - _massOutlineThickness;

	return springMaximumPixels * (_springLength / _springMaximumLength);
}
