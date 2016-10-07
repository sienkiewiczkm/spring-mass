#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <memory>
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

		void addRecord(sf::Time eventTime, float value);
		void deleteOldRecords(sf::Time thresholdTime);
		const std::list<TimechartRecord>& getRecords();

	private:
		static const sf::Time cMinimumInbetweenTime;

		std::list<TimechartRecord> _records;
	};

	class TimechartsView
	{
	public:
		TimechartsView();

		void setViewport(sf::FloatRect viewport);
		void setColor(sf::Color color);
		void registerTimechart(
			std::shared_ptr<Timechart> timechart,
			sf::Color assignedColor
		);

		void draw(sf::RenderWindow &window, sf::Time currentTime);

	private:
		struct TimechartInfo
		{
			std::shared_ptr<Timechart> Timechart;
			sf::Color AssignedColor;
		};

		void deleteOldRecords(sf::Time thresholdTime);
		void drawTimechart(
			sf::RenderWindow &window,
			std::shared_ptr<Timechart> timechart,
			sf::Color color,
			sf::Time boundaryTime
		);

		std::list<TimechartInfo> _records;
		sf::FloatRect _viewport;
		sf::Color _chartColor;
		sf::Time _timespanCovered;
	};
}