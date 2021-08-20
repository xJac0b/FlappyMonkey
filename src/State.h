#pragma once
#include "Gui.h"
class State;
class StateData
{
public:
	StateData(sf::RenderWindow& window, std::stack<std::unique_ptr<State>>& states, sf::Event& sf_event)
		: window(window), states(states), sfEvent(sf_event)
	{};
	sf::RenderWindow& window;
	std::stack<std::unique_ptr<State>>&states;
	sf::Event& sfEvent;
};
class State
{
public:
	State(StateData& state_data);
	
	
	virtual ~State();

	virtual void updateSfmlEvents();
	virtual void updateMousePosition();
	virtual void update(const float& dt) = 0;
	virtual void render() = 0;
protected:
	StateData& stateData;
	sf::Vector2i mousePosWindow;
	sf::Font font;
	
};

