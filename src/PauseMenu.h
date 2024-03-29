#pragma once
#include "Entity.h"
class PauseMenu
{
public:
	PauseMenu(sf::Font& font, sf::Vector2u window_size);
	~PauseMenu();

	const bool& isPaused() const;
	void pause();
	const bool isBtnClicked(short n);
	void update(const float& dt, sf::Vector2i& mouse_pos_win);
	void render(sf::RenderTarget& target);
private:
	bool paused;
	sf::Font& font;
	std::vector<gui::Button>buttons;
	std::vector<sf::Vertex>background;
	std::vector<sf::Vertex>panel;
};

