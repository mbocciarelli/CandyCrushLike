#pragma once
#include <iostream>

#include "Grille.h"
#include "../SFML/Graphics.hpp"
#include "../SFML/Graphics/Sprite.hpp"

#include "memory"
#include "StateMan.h"
#include "AssetMan.h"

enum AssetID
{
    MAIN_FONT = 0,
    BLUE,
    GREEN,
    ORANGE,
    PURPLE,
    RED,
    YELLOW,
};

namespace game{
    struct Context {
        std::unique_ptr<Engine::AssetMan> m_assets;
        std::unique_ptr<Engine::StateMan> m_states;
        std::unique_ptr<sf::RenderWindow> m_window;

        Context() {
            m_assets = make_unique<Engine::AssetMan>();
            m_states = make_unique<Engine::StateMan>();
            m_window = make_unique<sf::RenderWindow>();
        }
    };
}

class Game {
private :
    //State
    std::shared_ptr<game::Context> m_context;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

	/*
		Param�tres
	*/
	int wWidth = 1920;
	int wHeight = 1080;

public :
	Game();

	void StartGame();
};
