#include "application.h"

#include <cstdlib>

static bool toggle = false;

Application::Application(int width, int height, std::string title) {
	m_window.create(sf::VideoMode(width, height), title);

	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60);

	m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	m_view.setSize(1280, 720);
	m_view.setCenter(640, 360);
}


Application::~Application() {
	m_window.close();
}

void Application::run() {
	Ant ant[50];
	for (int i = 0; i < 50; i++) {
		ant[i].setPosition(rand() % 1280 + 1, rand() % 720 + 1);
		m_ants.push_back(ant[i]);
	}

	sf::Font font;
	font.loadFromFile("arial.ttf");

	m_label.setFont(font);
	m_label.setString("FPS: " + std::to_string(fps.elapsed()));
	m_label.setCharacterSize(18);
	m_label.setFillColor(sf::Color::White);

	while (m_window.isOpen()) {
		update();

		render();
	}
}

void Application::update()
{
	sf::Event event;

	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();

		if (event.type == sf::Event::Resized) {
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			m_window.setView(sf::View(visibleArea));
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
			toggle = !toggle;
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
			m_view.move(0, -100);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			m_view.move(0, 100);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
			m_view.move(-100, 0);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
			m_view.move(100, 0);
		if (event.type == sf::Event::MouseWheelMoved)
			m_view.zoom(1 - 0.05f * event.mouseWheel.delta);
	}

	m_label.setString("FPS: " + std::to_string(fps.elapsed()));
}

void Application::render()
{
	m_window.clear(sf::Color::Black);
	m_window.setView(m_view);

	for (int i = 0; i < m_ants.size(); i++) {
		m_window.draw(m_ants[i]);
	}

	if (toggle)
		m_window.draw(m_overlay);
	m_window.draw(m_label);

	m_window.display();
}
