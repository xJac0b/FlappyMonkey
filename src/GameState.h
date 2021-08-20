#pragma once
#include "Gameplay.h"
class GameState :
    public State
{
public:
    GameState(StateData& state_data, sf::RenderStates& state);
    ~GameState();
    void gameOver();   
    void updateSfmlEvents();
    void update(const float& dt);
    void render();
private:
    bool end;
    sf::RenderStates& state;
    std::unique_ptr<Gameplay>gameplay;
    std::unique_ptr<PauseMenu>pauseMenu;
    std::map<sf::String, sf::Texture>textures;
    std::vector<sf::Vertex>endBox;
    sf::Text endText;
    sf::RenderStates endState;
    std::vector<gui::Button>buttons; 
};

