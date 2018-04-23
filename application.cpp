#include "application.h"
#include "button.h"
#include <cstdlib>
#include <thread>
#include <functional>
#include <vector>
#include <iostream>

static bool toggle = false;
static bool smell_toggle = false;
static bool pheromone_toggle = false;
int windowWidth, windowHeight;

std::vector<Button> buttonList;
std::vector<sf::Text> buttonLabels;

std::vector<Food*> food;
std::vector<sf::VertexArray> m_smells;

Application::Application(int width, int height, bool vS, std::string title) {
	editingOverlayPh = false;
	editingOverlayFo = false;
	state = Menu;
	windowWidth = width;
	windowHeight = height;
	m_window.create(sf::VideoMode(width, height), title);

	m_window.setVerticalSyncEnabled(vS);
	m_window.setFramerateLimit(60);

	m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	m_view.setSize((float)width, (float)height);
	m_view.setCenter(width / 2.f, height / 2.f);
	//m_view.move(width * 2 - width / 2, height * 2 - height / 2);

	//m_grid = new Grid(width * 4, height * 4);
	m_grid = new Grid(width, height);

	m_font.loadFromFile("arial.ttf");

	m_overlay = new Overlay(&m_font);
	m_overlay->setPosition(1000, 0);
	m_overlay->setSize(sf::Vector2f(280, 720));
	m_overlay->setUpText();
	m_tempOverlayLabel.setFont(m_font);
	m_tempOverlayLabel.setString("");
	m_tempOverlayLabel.setCharacterSize(18);
	m_tempOverlayLabel.setFillColor(sf::Color::White);

	m_bg.setSize(sf::Vector2f((float)m_window.getSize().x, (float)m_window.getSize().y));
	//m_bg.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	m_bg.setFillColor(sf::Color(110, 50, 110, 50));
	m_bg.setPosition(sf::Vector2f(0, 0));

	m_label.setFont(m_font);
	m_label.setString("FPS: " + std::to_string(fps.elapsed()));
	m_label.setCharacterSize(18);
	m_label.setFillColor(sf::Color::White);

	m_paused.setFont(m_font);
	m_paused.setString("Paused");
	m_paused.setCharacterSize(18);
	m_paused.setFillColor(sf::Color::White);
	m_paused.setOrigin(sf::Vector2f(m_paused.getLocalBounds().width/2,0));
	m_paused.setPosition(sf::Vector2f(width / 2, 0));

	m_logoTexture.loadFromFile("logoTexture.png");
	m_logoTexture.setSmooth(true);
	m_logo.setTexture(&m_logoTexture);
	m_logo.setSize(sf::Vector2f(height / 4.f, height / 4.f));
	m_logo.setPosition(sf::Vector2f((width / 2.f) - height / 8.f, height / 8.f));
}

Application::~Application() {
	m_window.close();
}

void Application::setup() {
	m_colony = new Colony(sf::Vector2f(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f));
	m_colony->generate(5);

	std::cout << Grid::GetSize().x << " " << Grid::GetSize().y << std::endl;
	
	for (int i = 0; i < 100; i++) {
		food.push_back(new Food(sf::Vector2f((float)(rand() % m_window.getSize().x + 1), (float)(rand() % m_window.getSize().y + 1))));
	}

	auto k = Grid::Food.begin();
	while (k != Grid::Food.end()) {
		int r = ((Food*)((*k).first->food))->getRadius();
		int i = (*k).second.x;
		int j = (*k).second.y;
		sf::VertexArray va(sf::Quads);

		va.append({ sf::Vector2f(j - r + 1.f, i - r + 1.f), sf::Color(255, 255, 0, 100) });
		va.append({ sf::Vector2f(j + r + 0.f, i - r + 1.f), sf::Color(255, 255, 0, 100) });
		va.append({ sf::Vector2f(j + r + 0.f, i + r + 0.f), sf::Color(255, 255, 0, 100) });
		va.append({ sf::Vector2f(j - r + 1.f, i + r + 0.f), sf::Color(255, 255, 0, 100) });

		m_smells.push_back(va);

		++k;
	}

	buttonList.push_back(Button(sf::Vector2f((windowWidth / 2.f) - 100, windowHeight / 2.f), sf::Vector2f(200, 50), sf::Color(100, 100, 100, 255)));

	buttonLabels.push_back(sf::Text());
	buttonLabels.at(0).setFont(m_font);
	buttonLabels.at(0).setString("Start");
	buttonLabels.at(0).setCharacterSize(18);
	buttonLabels.at(0).setFillColor(sf::Color::White);
	buttonLabels.at(0).setPosition(sf::Vector2f(buttonList.at(0).getPosition().x + 80, buttonList.at(0).getPosition().y + 10));

	buttonList.push_back(Button(sf::Vector2f((windowWidth / 2.f) - 100, (windowHeight / 2.f) + 70), sf::Vector2f(200, 50), sf::Color(100, 100, 100, 255)));

	buttonLabels.push_back(sf::Text());
	buttonLabels.at(1).setFont(m_font);
	buttonLabels.at(1).setString("Reset");
	buttonLabels.at(1).setCharacterSize(18);
	buttonLabels.at(1).setFillColor(sf::Color::White);
	buttonLabels.at(1).setPosition(sf::Vector2f(buttonList.at(1).getPosition().x + 78, buttonList.at(1).getPosition().y + 10));

	buttonList.push_back(Button(sf::Vector2f((windowWidth / 2.f) - 100, (windowHeight / 2.f) + 140), sf::Vector2f(200, 50), sf::Color(100, 100, 100, 255)));

	buttonLabels.push_back(sf::Text());
	buttonLabels.at(2).setFont(m_font);
	buttonLabels.at(2).setString("Exit");
	buttonLabels.at(2).setCharacterSize(18);
	buttonLabels.at(2).setFillColor(sf::Color::White);
	buttonLabels.at(2).setPosition(sf::Vector2f(buttonList.at(2).getPosition().x + 85, buttonList.at(2).getPosition().y + 10));
}

void Application::run() {
	setup();
	
	sf::Clock clock;
	sf::Time frame = sf::milliseconds(60);
	sf::Time elapsed = frame;
	int num_frames = 0;
	//phero.detach();

	while (m_window.isOpen()) {
		if (num_frames > 10)
			num_frames = 0;
		//std::cout << (elapsed - frame).asMilliseconds() << " " << frame.asMilliseconds() <<"\n";
		
		//do {
			//elapsed = clock.getElapsedTime();

			//std::cout << "->" << (elapsed - frame).asMilliseconds() << " " << frame.asMilliseconds() << "\n";

		update();
		//} while ((elapsed - frame).asMilliseconds() < num_frames * frame.asMilliseconds());

		//elapsed = clock.restart();
		
		m_window.clear(sf::Color::Black);
		if (state == Pause) {
			m_window.setView(m_view);
			m_window.draw(m_bg);
			if (smell_toggle) {
				for (size_t i = 0; i < m_smells.size(); ++i)
					m_window.draw(m_smells.at(i));
			}
			for (size_t i = 0; i < food.size(); ++i)
				m_window.draw(*food[i]);

			m_window.draw(*m_colony);
			m_window.setView(m_window.getDefaultView());
			m_window.draw(m_paused);
		
		}
		if (state == Run) {
			m_colony->update(num_frames);
			
			//std::thread phero(&Grid::update);
			//phero.join();

			m_overlay->updateStats(m_colony->getAntCount(), food.size());
			m_window.setView(m_view);

			//elapsed = clock.restart();
			//std::cout << frame.asSeconds() << " " << elapsed.asSeconds() << " " << (frame - elapsed).asSeconds() << "\n";
			//if (elapsed > frame) {
			//	phero.join();

			//	continue;
			//}

			m_window.draw(m_bg);

			if (smell_toggle) {
				for (size_t i = 0; i < m_smells.size(); ++i)
					m_window.draw(m_smells.at(i));
			}
			
			for (size_t i = 0; i < food.size(); ++i)
				m_window.draw(*food[i]);

			m_window.draw(*m_colony);

			
			if (pheromone_toggle) {	
				/*auto v = Grid::Pheromones;
				for (size_t i = 0; i < v.size(); i++) {
					if (v[i].second.size() == 0)
						continue;
				
					m_window.draw(&v[i].second[0], 4, sf::Quads);
				}*/
			}
			
			m_window.setView(m_window.getDefaultView());
			if (toggle) {
				m_window.draw(*m_overlay);
				m_window.draw(m_overlay->overlayAntCount);
				m_window.draw(m_overlay->overlayFoodCount);
				m_window.draw(m_overlay->div1);
				if (!editingOverlayPh) {
					m_window.draw(m_overlay->pheremoneDecay);
				}
				else {
					m_window.draw(m_tempOverlayLabel);
				}
				if (!editingOverlayFo) {
					m_window.draw(m_overlay->foodSmellRadius);
				}
				else {
					m_window.draw(m_tempOverlayLabel);
				}
				m_window.draw(*m_overlay->ovButton);
				m_window.draw(m_overlay->buttonLabel);
			}

			
		}
		if (state == Menu) {
			m_window.clear(sf::Color::Black);
			m_window.draw(m_bg);
			m_window.draw(m_logo);
			
			for (size_t i = 0; i < buttonList.size(); i++) {
				m_window.draw(buttonList.at(i));
				m_window.draw(buttonLabels.at(i));
			}
		}

		m_window.draw(m_label);
		m_window.display();

		num_frames++;
	}
}
sf::String temp;
std::string::size_type si;
void Application::update() {
	sf::Event event;
	sf::Vector2i winc = sf::Vector2i(m_window.getSize().x / 2, m_window.getSize().y / 2);
	m_overlay->checkTextHover((sf::Vector2f) sf::Mouse::getPosition(m_window));

	if (state == Pause) {
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
				state = Run;
			}
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

	if (state == Run) {
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				m_window.close();

			if (event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
				m_window.setView(sf::View(visibleArea));
			}
			if (!editingOverlayPh) {
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
					toggle = !toggle;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
					smell_toggle = !smell_toggle;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
					pheromone_toggle = !pheromone_toggle;
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
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
					state = Pause;
				}
			}
			if (m_overlay->editMode == 1 && toggle) {
				editingOverlayPh = true;
				m_tempOverlayLabel.setPosition(m_overlay->pheremoneDecay.getPosition());
				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode == '\b') {
						if (temp.getSize() != 0) {
							temp.erase(temp.getSize() - 1, 1);
							m_tempOverlayLabel.setString(temp);
						}
					}
					else {
						temp += event.text.unicode;
						std::cout << temp.toAnsiString();
						m_tempOverlayLabel.setString(temp);
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
					if (!Config::isFloatNumber(temp) || std::stof(temp.toAnsiString(), &si) < 0) {
						m_overlay->updateFieldPh(std::to_string(Config::PheremoneDecay));
						m_overlay->editMode = 0;
					}
					else {
						Config::PheremoneDecay = std::stof(temp.toAnsiString(), &si);
						m_overlay->updateFieldPh(std::to_string(Config::PheremoneDecay));
						m_overlay->editMode = 0;
					}
					std::cout << "Current decay: " << Config::PheremoneDecay;
					//Config::writeConfig();
					m_tempOverlayLabel.setString("");
					temp = "";
					editingOverlayPh = false;
				}
			}
			if (m_overlay->editMode == 2 && toggle) {
				editingOverlayFo = true;
				m_tempOverlayLabel.setPosition(m_overlay->foodSmellRadius.getPosition());
				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode == '\b') {
						if (temp.getSize() != 0) {
							temp.erase(temp.getSize() - 1, 1);
							m_tempOverlayLabel.setString(temp);
						}
					}
					else {
						temp += event.text.unicode;
						std::cout << temp.toAnsiString();
						m_tempOverlayLabel.setString(temp);
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
					if (!Config::isFloatNumber(temp) || std::stof(temp.toAnsiString(), &si) < 0) {
						m_overlay->updateFieldFo(std::to_string(Config::FoodSmellRadius));
						m_overlay->editMode = 0;
					}
					else {
						Config::FoodSmellRadius = std::stof(temp.toAnsiString(), &si);
						m_overlay->updateFieldFo(std::to_string(Config::FoodSmellRadius));
						m_overlay->editMode = 0;
					}
					std::cout << "Food radius: " << Config::FoodSmellRadius;
					//Config::writeConfig();
					m_tempOverlayLabel.setString("");
					temp = "";
					editingOverlayFo = false;
				}
			}
			if (m_overlay->ovButton->update((sf::Vector2f) sf::Mouse::getPosition(m_window))) {
				Config::writeConfig();
			}
		}
	} else if (state == Menu) {
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
				m_window.setView(sf::View(visibleArea));
			}
		}

		for (size_t i = 0; i < buttonList.size(); i++) {
			if (i == 0) {
				if (buttonList.at(i).update((sf::Vector2f) sf::Mouse::getPosition(m_window))) {
					state = Run;

					buttonLabels.at(i).setPosition(sf::Vector2f(buttonList.at(i).getPosition().x + 70, buttonList.at(i).getPosition().y + 10));
					buttonLabels.at(i).setString("Resume");
				}
			}
			if (i == 1) {
				if (buttonList.at(i).update((sf::Vector2f) sf::Mouse::getPosition(m_window))) {
					buttonList.clear();
					buttonLabels.clear();

					m_colony->clean();
					delete m_colony;
					
					m_grid->clear();
					food.clear();
					smell_toggle = false;
					pheromone_toggle = false;
					toggle = false;
					
					m_smells.clear();
					Config::loadConfig();
					m_overlay->updateFieldPh(std::to_string(Config::PheremoneDecay));
					m_overlay->updateFieldFo(std::to_string(Config::FoodSmellRadius));
					setup();
				}
			}
			if (i == 2) {
				if (buttonList.at(i).update((sf::Vector2f) sf::Mouse::getPosition(m_window))) {
					m_window.close();
				}
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		sf::Vector2i mp = sf::Mouse::getPosition(m_window);

		if (mp.x < winc.x)
			m_view.move(-15, 0);
		else
			m_view.move(15, 0);

		if (mp.y < winc.y)
			m_view.move(0, -15);
		else
			m_view.move(0, 15);
	}

	m_label.setString("FPS: " + std::to_string(fps.elapsed()));
}
