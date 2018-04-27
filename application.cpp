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
std::vector<Obstacle *> obstacles;

Application::Application(int width, int height, bool vS, std::string title) {
	m_clickableArea = new Zone(width, height);
	m_maxFrames = 10;
	editingOverlayPh = false;
	editingOverlayFo = false;
	editingOverlayA = false;
	editingOverlayB = false;
	appRun = false;
	state = Menu;
	windowWidth = width;
	windowHeight = height;
	m_window.create(sf::VideoMode(width, height), title);

	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60);

	m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	m_view.setSize((float)width, (float)height);
	m_view.setCenter(width / 2.f, height / 2.f);
	//m_view.move(width * 2 - width / 2, height * 2 - height / 2);

	//m_grid = new Grid(width * 4, height * 4);
	m_grid = new Grid(width, height);

	m_font.loadFromFile("arial.ttf");

	m_overlay = new Overlay(&m_font, &width, &height);
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

	//std::cout << Grid::GetSize().x << " " << Grid::GetSize().y << std::endl;
	
	for (int i = 0; i < 0; i++) {
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

	//buttons for incrementing the colony size 
	buttonList.push_back(Button(sf::Vector2f((windowWidth / 2.f) + 75, (windowHeight / 2.f) - 70), sf::Vector2f(25, 50), sf::Color(100, 100, 100, 255)));
	
	buttonLabels.push_back(sf::Text());
	buttonLabels.at(3).setFont(m_font);
	buttonLabels.at(3).setString(">");
	buttonLabels.at(3).setCharacterSize(18);
	buttonLabels.at(3).setFillColor(sf::Color::White);
	buttonLabels.at(3).setPosition(sf::Vector2f(buttonList.at(3).getPosition().x + 10, buttonList.at(3).getPosition().y + 15));

	buttonList.push_back(Button(sf::Vector2f((windowWidth / 2.f) - 100, (windowHeight / 2.f) - 70), sf::Vector2f(25, 50), sf::Color(100, 100, 100, 255)));

	buttonLabels.push_back(sf::Text());
	buttonLabels.at(4).setFont(m_font);
	buttonLabels.at(4).setString("<");
	buttonLabels.at(4).setCharacterSize(18);
	buttonLabels.at(4).setFillColor(sf::Color::White);
	buttonLabels.at(4).setPosition(sf::Vector2f(buttonList.at(4).getPosition().x + 10, buttonList.at(4).getPosition().y + 15));


	colonySize.setFont(m_font);
	colonySize.setString(std::to_string(Config::ColonySize));
	colonySize.setCharacterSize(18);
	colonySize.setFillColor(sf::Color::White);
	colonySize.setPosition(sf::Vector2f(buttonList.at(3).getPosition().x - 90, buttonList.at(3).getPosition().y + 15));
}

int num_frames;
void Application::run() {
	setup();	
	num_frames = 0;

	Timer timer;
	double start = 0, elapsed = 0;

	//phero.detach();
	while (m_window.isOpen()) {		
		elapsed = timer.elapsed();
		m_window.clear(sf::Color::Black);

		while (elapsed - start < 1 / 60.f || num_frames < Config::MaxFrames) {
			//std::cout << num_frames << std::endl;
			m_window.setView(m_view);
			update();
			m_window.setView(m_window.getDefaultView());
			elapsed = timer.elapsed();
		}
		
		if (num_frames > Config::MaxFrames - 1)
			num_frames = 0;

		start = elapsed;
		
		if (state == Pause) {

			m_window.setView(m_view);
				m_window.draw(*m_colony);

				m_window.draw(m_bg);
				if (smell_toggle) {
					for (size_t i = 0; i < m_smells.size(); ++i)
						m_window.draw(m_smells.at(i));
				}
				for (size_t i = 0; i < food.size(); ++i)
					m_window.draw(*food[i]);

				for (size_t i = 0; i < obstacles.size(); ++i)
					m_window.draw(*obstacles[i]);
			m_window.setView(m_window.getDefaultView());
			m_window.draw(m_paused);
		
		}
		if (state == Run) {
			//since the movement speed of the ants is tied to fps, this is the only way to slow them without seriously changing how the updates work
			//skipping an update means they stay still, set SimSpeed to 2 to halve it, could probably improve this with floats but I'm lazy
			//std::cout << (int)time.elapsed() % Config::SimSpeed << std::endl;
			
			m_window.setView(m_view);
			
			//elapsed = clock.restart();
			//std::cout << frame.asSeconds() << " " << elapsed.asSeconds() << " " << (frame - elapsed).asSeconds() << "\n";
			//if (elapsed > frame) {
			//	phero.join();

			//	continue;
			//}
				//m_window.draw(*m_clickableArea);
				//m_window.setView(m_view);
				m_window.draw(m_bg);
				if (smell_toggle) {
					for (size_t i = 0; i < m_smells.size(); ++i)
						m_window.draw(m_smells.at(i));
				}

				for (size_t i = 0; i < food.size(); ++i)
					m_window.draw(*food[i]);

				for (size_t j = 0; j < obstacles.size(); j++) {
					m_window.draw(*obstacles[j]);
				}

		
					m_window.draw(*m_colony);
			
	

			m_window.setView(m_window.getDefaultView());
				if (toggle) {
					m_window.draw(*m_overlay);
					m_window.draw(m_overlay->overlayAntCount);
					m_window.draw(m_overlay->overlayFoodCount);
					m_window.draw(m_overlay->simSpeed);
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
					if (!editingOverlayA) {
						m_window.draw(m_overlay->alpha);
					}
					else {
						m_window.draw(m_tempOverlayLabel);
					}
					if (!editingOverlayB) {
						m_window.draw(m_overlay->beta);
					}
					else {
						m_window.draw(m_tempOverlayLabel);
					}
					m_window.draw(*m_overlay->ovButton);
					m_window.draw(m_overlay->buttonLabel);
					m_window.draw(*m_overlay->loadDefaults);
					m_window.draw(m_overlay->defaultsLabel);
				}
			

		}
		if (state == Menu) {
			//std::cout << num_frames << std::endl;
			m_window.draw(m_bg);
			m_window.draw(m_logo);
			if (!appRun) {
				m_window.draw(colonySize);
			}
			
			for (size_t i = 0; i < buttonList.size(); i++) {
				if ((i == 4 || i == 3) && appRun) {
				
				}
				else {
					m_window.draw(buttonList.at(i));
					m_window.draw(buttonLabels.at(i));
				}
			}
		}

		
		m_window.draw(m_label);
		m_window.display();
		m_label.setString("FPS: " + std::to_string(fps.elapsed()));
	}

	
}
sf::String temp;
std::string::size_type si;
void Application::update() {
	//std::cout << num_frames << std::endl;
	sf::Event event;
	sf::Vector2i winc = sf::Vector2i(m_window.getSize().x / 2, m_window.getSize().y / 2);
	m_overlay->checkTextHover((sf::Vector2f) sf::Mouse::getPosition(m_window));

	if (state == Pause) {
		m_colony->passFrames(num_frames);
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
				state = Run;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
				m_view.move(0, -1);
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
				m_view.move(0, 1);
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
				m_view.move(-1, 0);
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
				m_view.move(1, 0);
			if (event.type == sf::Event::MouseWheelMoved)
				m_view.zoom(1 - 0.05f * event.mouseWheel.delta);
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				state = Menu;
			}
		}
	}

	if (state == Run) {
		m_colony->update(num_frames);
		//std::thread phero(&Grid::update);
		//phero.join();
		m_overlay->updateStats(m_colony->getAntCount(), food.size());
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				m_window.close();

			if (event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
				m_window.setView(sf::View(visibleArea));
			}
			if (!editingOverlayPh && !editingOverlayFo) {
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
					toggle = !toggle;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
					smell_toggle = !smell_toggle;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
					if (Config::MaxFrames == 10) {
						Config::MaxFrames = 20;
					}
					else {
						Config::MaxFrames = 10;
					}
				}	
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
				if (event.type == sf::Event::MouseWheelMoved) {
					m_view.zoom(1 - 0.05f * event.mouseWheel.delta);
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
					std::cout << num_frames << std::endl;
					state = Menu;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
					state = Pause;
				}
				if (m_clickableArea->update(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))) == 1) {
					//add food
					Food* newFood = new Food(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
					food.push_back(newFood);
					int r = newFood->getRadius();
					int i = newFood->getPosition().y;
					int j = newFood->getPosition().x;
					sf::VertexArray va(sf::Quads);

					va.append({ sf::Vector2f(j - r + 0.f, i - r + 0.f), sf::Color(255, 255, 0, 100) });
					va.append({ sf::Vector2f(j + r + 1.f, i - r + 0.f), sf::Color(255, 255, 0, 100) });
					va.append({ sf::Vector2f(j + r + 1.f, i + r + 1.f), sf::Color(255, 255, 0, 100) });
					va.append({ sf::Vector2f(j - r + 0.f, i + r + 1.f), sf::Color(255, 255, 0, 100) });

					m_smells.push_back(va);
					//delete newFood;
				}
				if (m_clickableArea->update(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))) == 0) {
					//add food
					Obstacle* newObs = new Obstacle(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
					obstacles.push_back(newObs);
					//delete newFood;
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
			if (m_overlay->editMode == 3 && toggle) {
				editingOverlayA = true;
				m_tempOverlayLabel.setPosition(m_overlay->alpha.getPosition());
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
						m_overlay->updateFieldA(std::to_string(Config::AlphaParam));
						m_overlay->editMode = 0;
					}
					else {
						Config::AlphaParam = std::stof(temp.toAnsiString(), &si);
						m_overlay->updateFieldA(std::to_string(Config::AlphaParam));
						m_overlay->editMode = 0;
					}
					std::cout << "Alpha: " << Config::AlphaParam;
					//Config::writeConfig();
					m_tempOverlayLabel.setString("");
					temp = "";
					editingOverlayA = false;
				}
			}
			if (m_overlay->editMode == 4 && toggle) {
				editingOverlayB = true;
				m_tempOverlayLabel.setPosition(m_overlay->beta.getPosition());
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
						m_overlay->updateFieldB(std::to_string(Config::BetaParam));
						m_overlay->editMode = 0;
					}
					else {
						Config::BetaParam = std::stof(temp.toAnsiString(), &si);
						m_overlay->updateFieldB(std::to_string(Config::BetaParam));
						m_overlay->editMode = 0;
					}
					std::cout << "Beta: " << Config::BetaParam;
					//Config::writeConfig();
					m_tempOverlayLabel.setString("");
					temp = "";
					editingOverlayB = false;
				}
			}
			if (m_overlay->ovButton->update((sf::Vector2f) sf::Mouse::getPosition(m_window))) {
				Config::writeConfig();
			}			
			if (m_overlay->loadDefaults->update((sf::Vector2f) sf::Mouse::getPosition(m_window))) {
				Config::loadDefaultValues();
				m_overlay->updateFieldPh(std::to_string(Config::PheremoneDecay));
				m_overlay->updateFieldFo(std::to_string(Config::FoodSmellRadius));
				m_overlay->updateFieldA(std::to_string(Config::AlphaParam));
				m_overlay->updateFieldB(std::to_string(Config::BetaParam));
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
					appRun = true;
					m_colony->generate(Config::ColonySize);
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
					obstacles.clear();
					smell_toggle = false;
					pheromone_toggle = false;
					toggle = false;
					
					m_smells.clear();
					Config::loadConfig();
					Config::loadDefaultColonySize();
					m_overlay->updateFieldPh(std::to_string(Config::PheremoneDecay));
					m_overlay->updateFieldFo(std::to_string(Config::FoodSmellRadius));
					appRun = false;
					setup();
				}
			}
			if (i == 2) {
				if (buttonList.at(i).update((sf::Vector2f) sf::Mouse::getPosition(m_window))) {
					m_window.close();
				}
			}
			if (i == 3 && !appRun) {
				if (buttonList.at(i).update((sf::Vector2f) sf::Mouse::getPosition(m_window))) {
					if (num_frames == Config::MaxFrames) {
						Config::ColonySize++;
						colonySize.setString(std::to_string(Config::ColonySize));
					}
				}
			}
			if (i == 4 && !appRun) {
				if (buttonList.at(i).update((sf::Vector2f) sf::Mouse::getPosition(m_window))) {
					if ((num_frames == Config::MaxFrames) && Config::ColonySize > 1) {
						Config::ColonySize--;
						colonySize.setString(std::to_string(Config::ColonySize));
					}
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
	num_frames++;
	
}

