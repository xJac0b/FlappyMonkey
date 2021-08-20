#pragma once
#include "Pipe.h"
class Gameplay
{
public: 
	Gameplay(sf::Vector2u v, std::map<sf::String, sf::Texture>& textures, sf::Font& font, sf::RenderStates& state);
	~Gameplay();
	
	const unsigned int getPoints() const;
	const bool& gameOver() const;

	void pauseMusic();
	void updatePipes();
	void update(const float& dt);
	void render(sf::RenderTarget& target);
private:
	bool start;
	std::vector<sf::Vertex>keys;
	sf::RenderStates keysState;
	bool end, fall;
	unsigned pipe, points;
	float xPipe;
	std::map<sf::String, sf::Texture>& textures;
	sf::RenderStates state;
	std::vector<sf::Vertex>background;
	std::unique_ptr<sf::View> view;
	sf::Vector2u v;
	std::unique_ptr<Monkey>monkey;
	std::deque<std::unique_ptr<Pipe>>pipes;
	sf::Font& font;
	sf::Text pointsText;
	sf::Music music;

};

