#include "pch.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(StateData& state_data, sf::String&& path) : State(state_data)
{
	//Init backgorund
	this->bgTexture.loadFromFile(path);
	state.texture = &this->bgTexture;
	this->background.resize(4, sf::Vertex());
	gui::setVertexShape(this->background, {0.f, 0.f, static_cast<float>(this->stateData.window.getSize().x), 
		static_cast<float>(this->stateData.window.getSize().y)});
	gui::setVertexShape(this->background, { 0.f, 0.f, 3200.f,
		2400.f }, 0);
	//init title
	this->title.setFont(this->font);
	this->title.setString("Flappy Monkey");
	this->title.setCharacterSize(gui::calcCharSize(this->stateData.window.getSize(), 20));
	this->title.setPosition(this->stateData.window.getSize().x / 2.f - this->title.getGlobalBounds().width / 2.f,
		gui::p2pY(10.f, this->stateData.window.getSize()));
	this->title.setOutlineThickness(2.f);
	this->title.setOutlineColor(sf::Color::Black);
	
	//buttons
	this->buttons.push_back(gui::Button(sf::FloatRect(
		gui::p2pX(45.f, this->stateData.window.getSize()), gui::p2pY(35.f, this->stateData.window.getSize()),
		gui::p2pX(10.f, this->stateData.window.getSize()), gui::p2pY(19.f, this->stateData.window.getSize())), "PLAY", this->font, gui::calcCharSize(this->stateData.window.getSize(), 30)));
	this->buttons.push_back(gui::Button(sf::FloatRect(
		gui::p2pX(45.f, this->stateData.window.getSize()), gui::p2pY(60.f, this->stateData.window.getSize()),
		gui::p2pX(10.f, this->stateData.window.getSize()), gui::p2pY(19.f, this->stateData.window.getSize())), "QUIT", this->font, gui::calcCharSize(this->stateData.window.getSize(), 30)));
	

}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	for (auto& i : this->buttons)
	{
		i.update(this->mousePosWindow);
	}
	if (this->buttons[0].clicked)
	{
		this->stateData.states.push(std::make_unique<GameState>(this->stateData, this->state));
		this->buttons[0].clicked = 0;
	}	
	else if (this->buttons[1].clicked)
	{
		this->stateData.states.pop();
	}
		


}

void MainMenuState::render()
{
	this->stateData.window.draw(&background[0], 4, sf::Quads, state);
	this->stateData.window.draw(this->title);
	for (auto& i : this->buttons)
	{
		i.render(this->stateData.window);
	}
}
