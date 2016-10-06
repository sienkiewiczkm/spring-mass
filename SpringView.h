#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace sm
{
	class SpringView
	{
	public:
		SpringView();
		~SpringView();

		sf::FloatRect getViewport() const { return _viewport; }
		void setViewport(const sf::FloatRect &viewport);
		void setMassBaseDistance(float distance);

		void setSpringMaximumLength(float maximumLength);
		void setSpringMinimumLength(float minimumLength);
		void setSpringLength(float springLength);

		void draw(sf::RenderWindow &window);

	private:
		static const float cSpringThickness;
		static const float cBaseThickness;

		void drawMass(sf::RenderWindow &window);
		void drawSpring(sf::RenderWindow &window);
		void drawBase(sf::RenderWindow &window);

		float getSpringLengthInPx();

		float _massRadius;
		float _massOutlineThickness;
		float _massBaseDistance;

		float _springMinimumLength;
		float _springMaximumLength;
		float _springLength;

		sf::FloatRect _viewport;
	};
}