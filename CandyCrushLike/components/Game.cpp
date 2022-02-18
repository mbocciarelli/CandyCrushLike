//
// Created by Daniel Chiquet on 12/11/2021.
//

#include "../headers/Game.h"
#include "../headers/MainMenu.h"

Game::Game(): m_context(std::make_shared<Context>()) {
    //m_context->m_window->create(sf::VideoMode(wWidth, wHeight), "SFML works!", sf::Style::Close | sf::Style::Titlebar);
    m_context->m_window->create(sf::VideoMode(wWidth, wHeight), "SFML works!", sf::Style::Close | sf::Style::Titlebar);
    m_context->m_states->Add(make_unique<MainMenu>(m_context));
}


void Game::StartGame() {
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen()) {
        timeSinceLastFrame += clock.restart();

        while(timeSinceLastFrame > TIME_PER_FRAME) {
            timeSinceLastFrame -= TIME_PER_FRAME;
            m_context->m_states->ProcessStateChange();
            m_context->m_states->GetCurrent()->ProcessInput();
            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
            m_context->m_states->GetCurrent()->Draw();
        }
    }
}
