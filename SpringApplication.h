#pragma once

#include "SpringView.h"
#include "Timechart.h"
#include "Statechart.h"
#include "MassSpringSimulation.h"
#include "ITimeFunction.h"

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
		static const sf::Time cMaximumTimeDelta;

		void setup();
		void setupSimulation();

		void update();
		void updateControlsPositions();

		void draw();
		
		sf::Clock _clock;
		sf::Time _totalElapsedTime;
		sf::Time _deltaTime;
		sf::Time _leftoverTime;

		sf::RenderWindow _window;
		sf::View _view;
		SpringView _springView;
		
		TimechartsView _topLeftTimechart;
		TimechartsView _topRightTimechart;
		TimechartsView _bottomLeftTimechart;
		TimechartsView _bottomRightTimechart;

		Statechart _statechart;

		std::shared_ptr<MassSpringSimulation> _simulation;

		std::shared_ptr<Timechart> _positionTimechart;
		std::shared_ptr<Timechart> _velocityTimechart;
		std::shared_ptr<Timechart> _accelerationTimechart;

		std::shared_ptr<Timechart> _resilienceForceTimechart;
		std::shared_ptr<Timechart> _attenuationForceTimechart;
		std::shared_ptr<Timechart> _externalForceTimechart;

		std::shared_ptr<Timechart> _massBalanceTimechart;

		float _mass;
		float _resilience;
		float _initialPosition;
		float _initialVelocity;
		float _attenuationFactor;
		float _step;

		std::shared_ptr<ITimeFunction> _massBalanceFunction;
		std::shared_ptr<ITimeFunction> _externalForceFunction;
	};
}