#include "SpringApplication.h"

using namespace sm;

SpringApplication::SpringApplication() {
}

SpringApplication::~SpringApplication() {
}

void SpringApplication::run() {
	_window.create(sf::VideoMode(800, 600), "Mass on Spring Simulation");

	while (_window.isOpen()) {
		sf::Event windowEvent;
		if (_window.pollEvent(windowEvent)) {
			if (windowEvent.type == sf::Event::Closed) {
				_window.close();
			}
		}
	}
}
