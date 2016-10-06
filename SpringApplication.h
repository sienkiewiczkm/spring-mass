#pragma once

#include "SpringView.h"
#include "Timechart.h"
#include "Statechart.h"

#include <SFML/Window.hpp>

namespace sm
{
	class SpringApplication
	{
	public:
		SpringApplication();
		~SpringApplication();

		void run();

	private:
		static const int cNumTimecharts;
		
		sf::Clock _clock;
		sf::RenderWindow _window;
		sf::View _view;
		SpringView _springView;
		Timechart _positionTimechart;
		Statechart _statechart;
	};
}