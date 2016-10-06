#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <list>

namespace sm
{
	struct TimechartRecord
	{
		TimechartRecord();
		TimechartRecord(sf::Time eventTime, float value);

		sf::Time EventTime;
		float Value;
	};

	class Timechart
	{
	public:
		Timechart();

		void setViewport(sf::FloatRect viewport);
		void addRecord(sf::Time eventTime, float value);
		void draw(sf::RenderWindow &window, sf::Time currentTime);

	private:
		void deleteOldRecords(sf::Time currentTime);

		std::list<TimechartRecord> _records;
		sf::FloatRect _viewport;
		sf::Color _chartColor;
		sf::Time _timespanCovered;
	};
}