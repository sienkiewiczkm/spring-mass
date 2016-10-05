#pragma once

#include <SFML/Window.hpp>

namespace sm {
	class SpringApplication {
	public:
		SpringApplication();
		~SpringApplication();

		void run();

	private:
		sf::Window _window;
	};
}