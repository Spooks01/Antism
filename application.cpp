#include "application.h"
#include "button.h"
#include <cstdlib>
#include <thread>
#include <functional>
#include <vector>
static bool toggle = false;
int windowWidth, windowHeight;
Application::Application(int width, int height, bool vS, std::string title) {
	state = Menu;
	windowWidth = width;
	windowHeight = height;
	m_window.create(sf::VideoMode(width, height), title);

	m_window.setVerticalSyncEnabled(vS);
	m_window.setFramerateLimit(60);

	m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	m_view.setSize(width, height);
	m_view.setCenter(width / 2.f, height / 2.f);
	//m_view.move(width * 2, height * 2);

	m_grid = new Grid(width * 4, height * 4);
}

Application::~Application() {
	m_window.close();
}
std::vector<Button> buttonList;
void Application::run() {
	sf::Font font;
	font.loadFromFile("arial.ttf");
	m_label.setFont(font);
	m_label.setString("FPS: " + std::to_string(fps.elapsed()));
	m_label.setCharacterSize(18);
	m_label.setFillColor(sf::Color::White);
	buttonList.push_back(Button(sf::Vector2f(windowWidth / 2, windowHeight / 2), sf::Vector2f(200, 50)));
	Colony colony(sf::Vector2f(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f));
	colony.generate(100);
	m_overlay.setPosition(1000, 0);
	m_overlay.setSize(sf::Vector2f(280, 720));

	while (m_window.isOpen()) {
		update();
		m_window.clear(sf::Color::Black);
		if (state == Run) {
			colony.update();	
			renderAnts();
			m_window.draw(colony);
			renderHUD();
		}
		if (state == Menu) {
			m_window.clear(sf::Color::Black);
			for (int i = 0; i < buttonList.size(); i++) {
				m_window.draw(buttonList.at(i));
			}
			m_window.draw(m_label);	
		}
		m_window.display();
	}
}

void Application::update() {
	sf::Event event;
	if (state == Run) {	
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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				state = Menu;
			}
		}
	}
	else if (state == Menu) {
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				m_window.setView(sf::View(visibleArea));
			}
			for (int i = 0; i < buttonList.size(); i++) {
				if (i == 0) {
					if (buttonList.at(i).update((sf::Vector2f) sf::Mouse::getPosition(m_window))) {
						state = Run;
					}
				}
			}
		}
	}
	m_label.setString("FPS " + std::to_string(fps.elapsed()));
}

void Application::renderAnts()
{
	m_window.setView(m_view);

	
}

void Application::renderHUD() {
	m_window.setView(m_window.getDefaultView());
	if (toggle)
		m_window.draw(m_overlay);
	m_window.draw(m_label);
}