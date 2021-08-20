#include "pch.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::Font& font, sf::Vector2u window_size) : font(font), paused(false)
{
	//Init background
	this->background.resize(4, sf::Vertex());
	gui::setVertexShape(this->background, { 0.f, 0.f, static_cast<float>(window_size.x), static_cast<float>(window_size.y) });
	for (auto& i : this->background)
		i.color = sf::Color(50, 50, 50, 150);
	//Init panel
	this->panel.resize(4, sf::Vertex());
	gui::setVertexShape(this->panel, { gui::p2pX(35.f, window_size), 0.f,
		gui::p2pX(30.f, window_size), static_cast<float>(window_size.y) });
	for (auto& i : this->panel)
		i.color = sf::Color(10, 10, 10, 200);
	//Init Buttons
	this->buttons.push_back(gui::Button(sf::FloatRect(gui::p2pX(35.f, window_size), gui::p2pY(35.f, window_size),
		gui::p2pX(30.f, window_size), gui::p2pY(7.f, window_size)), "Resume", this->font, gui::calcCharSize(window_size, 40)));
	this->buttons.push_back(gui::Button(sf::FloatRect(gui::p2pX(35.f, window_size), gui::p2pY(50.f, window_size),
		gui::p2pX(30.f, window_size), gui::p2pY(7.f, window_size)), "Restart", this->font, gui::calcCharSize(window_size, 40)));
	this->buttons.push_back(gui::Button(sf::FloatRect(gui::p2pX(35.f, window_size), gui::p2pY(65.f, window_size),
		gui::p2pX(30.f, window_size), gui::p2pY(7.f, window_size)), "Quit", this->font, gui::calcCharSize(window_size, 40)));
}

PauseMenu::~PauseMenu()
{
}

const bool& PauseMenu::isPaused() const
{
	return this->paused;
}

void PauseMenu::pause()
{
	this->paused = !this->paused;
}

const bool PauseMenu::isBtnClicked(short n)
{
	if (this->buttons[n].clicked)
	{
		this->buttons[n].clicked = false;
		return true;
	}
	return false;
		
}

void PauseMenu::update(const float& dt, sf::Vector2i& mouse_pos_win)
{
	for (auto& i : this->buttons)
		i.update(mouse_pos_win);
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(&this->background[0], 4, sf::Quads);
	target.draw(&this->panel[0], 4, sf::Quads);
	for (auto& i : this->buttons)
		i.render(target);
}
