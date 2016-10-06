#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <list>

namespace sm
{
	struct StatechartRecord
	{
		float XAxisValue;
		float YAxisValue;

		StatechartRecord();
		StatechartRecord(float xAxisValue, float yAxisValue);
	};

	class Statechart
	{
	public:
		Statechart();
		
		void setViewport(sf::FloatRect viewport);
		void setColor(sf::Color color);
		void addRecord(StatechartRecord record);
		void draw(sf::RenderWindow &window);

	private:
		static const int cNumMaxRecords;
		static const int cOutlineThickness;

		sf::FloatRect _viewport;
		sf::Color _color;
		std::list<StatechartRecord> _records;
	};
}