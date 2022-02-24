#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>

#include "Game.h"
#include "State.h"
#include "Grille.h"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<game::Context> m_context;

    /*
        Param�tres
    */
    int wWidth = 1920;
    int wHeight = 1080;

    int widthMarge = 0;
    int heightMarge = 0;

    int widthGrille = 10;
    int heightGrille = 10;

    int xFirstPoint = 0;
    int yFirstPoint = 0;
    int sizeCell = 0;
    double sizeSprite = 0;

    sf::Time TIME_PER_FRAME;

    /*
        Text
    */

    sf::Font font;

    /*
        Click
    */

    Cell prevCellClick;
    bool checkPrevCell = false;

    /*
        Fen�tre
    */

    Grille* grille;

    //sf::RenderWindow window;

    /*
        Objectifs
    */
    bool objectifIsFinish = false;

    int coutSwap = 0;
    int maxSwap = 0;
    std::map<Bonbon, int> objectifs;
    std::vector<int> coutObjectifs;


    void afficherObjectifs();

public:
    GamePlay(std::shared_ptr<game::Context> &context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;

    void RestartGame();

    void CalculParameters();

    void GenerateObjectifs();


    void addCoutObjectifs(int place, int value, int maxValue) {
        coutObjectifs.at(place) += value;
        if(coutObjectifs.at(place) > maxValue)
            coutObjectifs.at(place) = maxValue;
    }

    void checkObjectifs() {
        int i = 0;
        objectifIsFinish = true;
        for (const auto& kv : objectifs) {
            if (kv.second != coutObjectifs.at(i)) {
                objectifIsFinish = false;
                break;
            }
            i++;
        }
    }

    bool eventClickLeft(sf::Event event) {
        return event.mouseButton.button == sf::Mouse::Left;
    }

    void delay(float timeDelay){
        sf::Clock clock;
        sf::Time lastTime;
        do {
            lastTime = clock.getElapsedTime();
        }while(lastTime.asSeconds() < timeDelay);
    }

    void RegenerateCells();

    void CalculSizeCell();

    void CalculSizeSprite();

    void ReorganizeCells();

    Grille* load(int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, double sizeSprite);

    void loadTexture(Grille* grille);

    void loadSprite(Grille* grille, int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, double sizeSprite);

    void dessinerResultat(bool result);

    Bonbon generateBonbon(int min, int max);

    Bonbon generateBonbonWithExcludeBonbon(int min, int max, int valueExclude);

    bool IsOnGrid(int xClick, int yClick);

    void UpdateGrille();

    void UpdateSizeItem(Item* item, int i, int j);

    Cell GetCell(int xClick, int yClick);

    bool IsAroundPrevCell(Cell cell);

    void changeAlphaColor(Cell cell, int value);

};