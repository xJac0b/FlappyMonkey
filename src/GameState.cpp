#include "pch.h"
#include "GameState.h"

GameState::GameState(StateData& state_data, sf::RenderStates& state) : State(state_data), state(state), end(0)
{
	this->textures["MONKEY"].loadFromFile("Resources/Images/Monkey.png");
	this->textures["PIPE1"].loadFromFile("Resources/Images/pipe1.png");
	this->textures["PIPE2"].loadFromFile("Resources/Images/pipe2.png");
	this->textures["KEYS"].loadFromFile("Resources/Images/keys.png");
	//init gameplay
	this->gameplay = std::make_unique<Gameplay>(this->stateData.window.getSize(), this->textures, this->font, this->state);
	//init pause menu
	this->pauseMenu = std::make_unique<PauseMenu>(this->font, this->stateData.window.getSize());
	//Init endText
	this->endText.setOutlineThickness(2.f);
	this->endText.setOutlineColor(sf::Color::Black);
	this->endText.setFont(this->font);
	this->endText.setCharacterSize(gui::calcCharSize(this->stateData.window.getSize(),30U));
	this->endText.setPosition(200.f, 200.f);
	//Init endbox
	this->endBox.resize(4, sf::Vertex());
	gui::setVertexShape(this->endBox, {0.f, gui::p2pY(30.f, this->stateData.window.getSize()),
	static_cast<float>(this->stateData.window.getSize().x),gui::p2pY(30.f, this->stateData.window.getSize()) });
	//Init buttons
	this->buttons.push_back(gui::Button(sf::FloatRect(
		gui::p2pX(35.f, this->stateData.window.getSize()), gui::p2pY(44.f, this->stateData.window.getSize()),
		gui::p2pX(15.5f, this->stateData.window.getSize()), gui::p2pY(10.f, this->stateData.window.getSize())), "PLAY AGAIN",
		this->font, gui::calcCharSize(this->stateData.window.getSize(), 50)));
	
	this->buttons.push_back(gui::Button(sf::FloatRect(
		gui::p2pX(55.f, this->stateData.window.getSize()), gui::p2pY(44.f, this->stateData.window.getSize()),
		gui::p2pX(7.f, this->stateData.window.getSize()), gui::p2pY(10.f, this->stateData.window.getSize())), "QUIT",
		this->font, gui::calcCharSize(this->stateData.window.getSize(), 50)));
}

GameState::~GameState()
{
}

void GameState::gameOver()
{
	this->end = true;
	for (auto& i : this->endBox)
		i.color = sf::Color(100, 100, 100, 100);
	std::stringstream ss;
	ss << "Your score : " << this->gameplay->getPoints()/2.f;
	
	this->endText.setString(ss.str());
	this->endText.setPosition(this->stateData.window.getSize().x / 2.f - this->endText.getGlobalBounds().width / 2.f,
		gui::p2pY(31.5f, this->stateData.window.getSize()));
}

void GameState::updateSfmlEvents()
{
	if (this->stateData.sfEvent.type == sf::Event::KeyPressed)
	{
		if (this->stateData.sfEvent.key.code == sf::Keyboard::Escape)
		{
			this->pauseMenu->pause();
			this->gameplay->pauseMusic();
		}
	}
		
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateSfmlEvents();
	if (this->end)
	{
		for (auto& i : this->buttons)
			i.update(this->mousePosWindow);
		if (this->buttons[0].clicked)
		{
			this->gameplay = std::make_unique<Gameplay>(this->stateData.window.getSize(), this->textures, this->font, this->state);
			this->end = false;
			this->buttons[0].clicked = false;
		}
		if (this->buttons[1].clicked)
		{
			this->stateData.states.pop();
		}
	}
	else
	{
		if (this->pauseMenu->isPaused())
		{
			this->pauseMenu->update(dt, this->mousePosWindow);

			if (this->pauseMenu->isBtnClicked(0))
			{
				this->pauseMenu->pause();
				this->gameplay->pauseMusic();
			}			
			else if (this->pauseMenu->isBtnClicked(1))
			{
				this->gameplay = std::make_unique<Gameplay>(this->stateData.window.getSize(), this->textures, this->font, this->state);
				this->pauseMenu->pause();
			}	
			else if (this->pauseMenu->isBtnClicked(2))
				this->stateData.states.pop();
		}
		else
		{
			this->gameplay->update(dt);
			if (this->gameplay->gameOver())
				this->gameOver();
		}
	}
	
}

void GameState::render()
{
	this->gameplay->render(this->stateData.window);
	if (this->end)
	{
		this->stateData.window.draw(&this->endBox[0], 4, sf::Quads);
		this->stateData.window.draw(this->endText);
		for (auto& i : this->buttons)
			i.render(this->stateData.window);
	}
	else if (this->pauseMenu->isPaused())
		this->pauseMenu->render(this->stateData.window);

}