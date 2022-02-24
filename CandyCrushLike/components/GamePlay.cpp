#include "../headers/GamePlay.h"

#include <SFML/Window/Event.hpp>

GamePlay::GamePlay(std::shared_ptr<game::Context> &context)
        : m_context(context)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{

}
void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) {


        switch (event.type) {
            case sf::Event::Closed:
                m_context->m_window->close();
                break;

            case sf::Event::MouseButtonPressed:

                if (!eventClickLeft(event))
                    break;

                if (objectifIsFinish || coutSwap >= maxSwap) {
                    RestartGame();
                    break;
                }

                if (!IsOnGrid(event.mouseButton.x, event.mouseButton.y))
                    break;

                Cell cell = GetCell(event.mouseButton.x, event.mouseButton.y);

                if (!checkPrevCell) {
                    prevCellClick = cell;
                    changeAlphaColor(cell, 125);
                    checkPrevCell = true;
                    break;
                }

                changeAlphaColor(prevCellClick, 255);

                if (!IsAroundPrevCell(cell)) {
                    checkPrevCell = false;
                    break;
                }

                if (prevCellClick.h == cell.h && prevCellClick.l == cell.l) {
                    checkPrevCell = false;
                    break;
                }

                grille->SwapCell(prevCellClick, cell);
                checkPrevCell = false;

                bool matchIsOk = grille->CheckMatch();
                if (matchIsOk) {
                    coutSwap++;
                    while (grille->CheckMatch()) {
                        grille->DestroyCells();

                        std::map<Bonbon, int> destroy = grille->getBonbonToDestroy();
                        int i = 0;
                        for (const auto& kv : objectifs) {
                            int value = destroy.at(kv.first);
                            int maxValue = kv.second;
                            if (value > 0) {
                                addCoutObjectifs(i, value, maxValue);
                            }
                            i++;
                        }
                        grille->clearBonbonToDestroy();

                        Draw();
                        delay(0.5f);
                        ReorganizeCells();
                        RegenerateCells();

                        checkObjectifs();
                        if (objectifIsFinish)
                            break;
                    }
                }
                else {
                    grille->SwapCell(cell, prevCellClick);
                }

                break;
        }
    }
}
void GamePlay::Update(sf::Time deltaTime)
{
    TIME_PER_FRAME = deltaTime;
    if (objectifIsFinish || coutSwap >= maxSwap)
        dessinerResultat(objectifIsFinish);
}
void GamePlay::Draw()
{
    m_context->m_window->clear(sf::Color::Black);

    for (int i = 0; i < grille->getHauteur(); i++) {
        for (int j = 0; j < grille->getLargeur(); j++) {
            if (grille->getArrItem(i, j)->getName() == Bonbon::AUCUN)
                continue;

            m_context->m_window->draw(*grille->getArrItem(i, j)->getSprite());
        }
    }

    afficherObjectifs();
    m_context->m_window->display();
}
void GamePlay::Pause()
{
}
void GamePlay::Start()
{
    std::srand((unsigned int) std::time(nullptr));

    CalculParameters();

    GenerateObjectifs();

    grille = load(widthGrille, heightGrille, xFirstPoint, yFirstPoint, sizeCell, sizeSprite);

}

void GamePlay::ReorganizeCells() {
    for (int i = grille->getHauteur() - 1; i >= 0; i--) {
        for (int j = grille->getLargeur() - 1; j >= 0; j--) {
            if (grille->getArrItem(i, j)->getName() == Bonbon::AUCUN) {
                int saveHauteur = i;
                do {
                    saveHauteur--;
                } while (saveHauteur > 0 && grille->getArrItem(saveHauteur, j)->getName() == Bonbon::AUCUN);

                if (saveHauteur >= 0 && grille->getArrItem(saveHauteur, j)->getName() != Bonbon::AUCUN) {
                    grille->SwapCell(Cell(saveHauteur, j), Cell(i, j));
                    delay(0.1f);
                    Draw();
                }
            }
        }
    }
}

void GamePlay::RegenerateCells() {
    for (int h = 0; h < grille->getHauteur(); ++h) {
        for (int l = 0; l < grille->getLargeur(); ++l) {
            if (grille->getArrItem(h, l)->getName() == Bonbon::AUCUN) {
                Bonbon name = grille->getArrItem(h, l)->regenerateItem(1, 6);
                grille->getArrItem(h, l)->getSprite()->setTexture(*grille->getTexture(name));
                delay(0.1f);
                Draw();

            }
        }
    }
}


void GamePlay::RestartGame() {
    coutSwap = 0;
    objectifs.clear();
    coutObjectifs.clear();
    objectifIsFinish = false;
    checkPrevCell = false;

    GenerateObjectifs();

    grille = load(widthGrille, heightGrille, xFirstPoint, yFirstPoint, sizeCell, sizeSprite);
}

void GamePlay::CalculParameters() {
    widthMarge = (wWidth * 400) / 1920;
    heightMarge = (wHeight * 240) / 1080;

    xFirstPoint = widthMarge / 2;
    yFirstPoint = heightMarge / 2;

    CalculSizeCell();

    CalculSizeSprite();
}

void GamePlay::GenerateObjectifs() {
    int random = rand() % 2 + 1;
    Bonbon name = Bonbon::AUCUN;
    int coutBonbonNeed;
    switch (random) {
        case 1:
            coutObjectifs.reserve(1);
            maxSwap = rand() % 20 + 10;

            name = generateBonbon(1, 6);
            coutBonbonNeed = rand() % 23 + 12;

            objectifs.emplace(name, coutBonbonNeed);
            coutObjectifs.push_back(0);

            break;
        case 2:
        default:
            coutObjectifs.reserve(2);
            maxSwap = rand() % 31 + 23;

            for (int i = 0; i < 2; i++) {
                name = generateBonbonWithExcludeBonbon(1, 6, (int)name);
                coutBonbonNeed = rand() % 18 + 13;

                objectifs.emplace(name, coutBonbonNeed);
                coutObjectifs.push_back(0);
            }
            break;
    }
}

void GamePlay::CalculSizeCell() {
    int width = wWidth - widthMarge;
    int height = wHeight - heightMarge;

    double proportion = ((double)wWidth / (double)wHeight) * 75.0;
    sizeCell = (int)(proportion / (1920.0 / 1080.0));

    if (
            (sizeCell > (width / widthGrille))
            || (sizeCell > (height / heightGrille))
            ) {
        if ((width / widthGrille) > (height / heightGrille)) {
            sizeCell = height / heightGrille;
        }
        else {
            sizeCell = width / widthGrille;
        }
    }
}

void GamePlay::CalculSizeSprite() {
    int width = widthGrille / 10;
    int height = heightGrille / 10;

    sizeSprite = (((double)wWidth / (double)wHeight) * 1.5) / (1920.0 / 1080.0);

    if (width < height) {
        sizeSprite = sizeSprite / height;
    }
    else {
        sizeSprite = sizeSprite / width;
    }

    if (sizeSprite > 2) {
        sizeSprite = 2;
    }
}

Grille* GamePlay::load(int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, double sizeSprite) {

    grille = new Grille(widthGrille, heightGrille);

    loadTexture(grille);

    loadSprite(grille, widthGrille, heightGrille, xFirstPoint, yFirstPoint, sizeCell, sizeSprite);

    if (widthGrille > 2 && heightGrille > 2) {
        grille->checkIfPlayable();
    }

    return grille;
}


bool GamePlay::IsOnGrid(int xClick, int yClick) {
    xClick -= xFirstPoint;
    yClick -= yFirstPoint;

    return (
            xClick >= 0 && xClick < (sizeCell* widthGrille)
            && yClick >= 0 && yClick < (sizeCell* heightGrille)
    );
}

bool GamePlay::IsAroundPrevCell(Cell cell) {
    return (
            prevCellClick.h == cell.h + 1 && prevCellClick.l == cell.l
            || prevCellClick.h == cell.h - 1 && prevCellClick.l == cell.l
            || prevCellClick.h == cell.h && prevCellClick.l == cell.l + 1
            || prevCellClick.h == cell.h && prevCellClick.l == cell.l - 1
    );
}

Cell GamePlay::GetCell(int xClick, int yClick) {
    xClick -= xFirstPoint;
    yClick -= yFirstPoint;

    int xClickMarge = xClick % sizeCell;
    int yClickMarge = yClick % sizeCell;

    Cell cell;

    int lig = (xClick - xClickMarge) / sizeCell;
    int col = (yClick - yClickMarge) / sizeCell;
    cell.h = col;
    cell.l = lig;

    return cell;
}

void GamePlay::loadTexture(Grille* grille) {
    grille->loadTexture(Bonbon::BLUE, "asset/Blue.png");
    grille->loadTexture(Bonbon::GREEN, "asset/Green.png");
    grille->loadTexture(Bonbon::ORANGE, "asset/Orange.png");
    grille->loadTexture(Bonbon::PURPLE, "asset/Purple.png");
    grille->loadTexture(Bonbon::RED, "asset/Red.png");
    grille->loadTexture(Bonbon::YELLOW, "asset/Yellow.png");
}

void GamePlay::loadSprite(Grille* grille, int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, double sizeSprite) {
    for (int i = 0; i < grille->getHauteur(); i++) {
        for (int j = 0; j < grille->getLargeur(); j++) {

            grille->setArrItem(new Item());
            Item* item = grille->getArrItem(i, j);

            Bonbon itemName = item->regenerateItem(1, 6); // 6 Textures max
            if (i > 1) {
                if (grille->getArrItem(i - 1, j)->getName() == itemName && grille->getArrItem(i - 2, j)->getName() == itemName) {
                    itemName = generateBonbonWithExcludeBonbon(1, 6, (int)itemName);
                    item->setName(itemName);
                }
            }

            if (j > 1) {
                if (grille->getArrItem(i, j - 1)->getName() == itemName && grille->getArrItem(i, j - 2)->getName() == itemName) {
                    itemName = generateBonbonWithExcludeBonbon(1, 6, (int)itemName);
                    item->setName(itemName);
                }
            }

            item->getSprite()->setTexture(*grille->getTexture(itemName));
            UpdateSizeItem(grille->getArrItem(i, j), i, j);
        }
    }
}

void GamePlay::dessinerResultat(bool result) {
    if (!font.loadFromFile("./asset/aAbstractGroovy.ttf"))
        return;

    m_context->m_window->clear(sf::Color::Black);

    sf::Text textResult;
    textResult.setFont(font);
    textResult.setPosition((float)(wWidth / 2.5), (float)(wHeight / 2.5));
    std::string resultat = (result ? "Gagn�" : "Perdu");
    textResult.setString("Resultat : " + resultat + "\n\nClick pour recommencer");
    textResult.setCharacterSize(36);

    m_context->m_window->draw(textResult);
    m_context->m_window->display();
}

void GamePlay::afficherObjectifs() {
    if (!font.loadFromFile("./asset/aAbstractGroovy.ttf"))
        return;

    float xText = (float)((float)sizeCell * (float)grille->getLargeur() + 500.0);
    float yText = 100.0;

    sf::Text textObjectifs;
    textObjectifs.setFont(font);
    textObjectifs.setPosition(xText, yText);
    textObjectifs.setString("Objectifs");
    textObjectifs.setCharacterSize(36);

    m_context->m_window->draw(textObjectifs);

    int offsetY = 75;
    int i = 0;
    for (const auto& kv : objectifs) {

        sf::Sprite bonbonSprite;
        bonbonSprite.setTexture(*grille->getTexture(kv.first));
        bonbonSprite.setPosition(xText, yText + offsetY);

        sf::Text bonbonText;
        bonbonText.setFont(font);
        bonbonText.setPosition(xText + 75, yText + offsetY + 5);
        bonbonText.setString(std::to_string(coutObjectifs.at(i)) + "/" + std::to_string(kv.second));
        bonbonText.setCharacterSize(28);

        m_context->m_window->draw(bonbonSprite);
        m_context->m_window->draw(bonbonText);

        i++;
        offsetY += 75;
    }

    offsetY += 200;

    sf::Text textCoutSwap;
    textCoutSwap.setFont(font);
    textCoutSwap.setPosition(xText, yText + offsetY);
    textCoutSwap.setString("Coup(s) Restant(s)");
    textCoutSwap.setCharacterSize(36);

    m_context->m_window->draw(textCoutSwap);

    offsetY += 50;

    sf::Text textCoutSwapNumber;
    textCoutSwapNumber.setFont(font);
    textCoutSwapNumber.setPosition(xText, yText + offsetY);
    textCoutSwapNumber.setString(std::to_string(coutSwap) + "/" + std::to_string(maxSwap));
    textCoutSwapNumber.setCharacterSize(40);

    m_context->m_window->draw(textCoutSwapNumber);
}

void GamePlay::UpdateGrille() {
    for (int i = 0; i < grille->getHauteur(); i++) {
        for (int j = 0; j < grille->getLargeur(); j++) {

            UpdateSizeItem(grille->getArrItem(i, j), i, j);

        }
    }
}

void GamePlay::UpdateSizeItem(Item* item, int i, int j) {
    item->getSprite()->setScale((float)sizeSprite, (float)sizeSprite);

    float x = (float)(j * sizeCell + xFirstPoint);
    float y = (float)(i * sizeCell + yFirstPoint);

    item->getSprite()->setPosition(x, y);
}

void GamePlay::changeAlphaColor(Cell cell, int value) {
    sf::Color temp = grille->getArrItem(cell.h, cell.l)->getSprite()->getColor();
    temp.a = value;
    grille->getArrItem(cell.h, cell.l)->getSprite()->setColor(temp);
}

//Min et max son inclu dans le rand
Bonbon GamePlay::generateBonbon(int min, int max) {
    min -= 1;
    max -= 1;

    int random = rand() % max + min;

    return (Bonbon)random;
}

Bonbon GamePlay::generateBonbonWithExcludeBonbon(int min, int max, int valueExclude) {
    min -= 1;
    max -= 1;

    if (valueExclude > max || valueExclude < min) {
        int random = rand() % max + min;

        return (Bonbon)random;
    }

    if (valueExclude == max) {
        int random = rand() % (max - 1) + min;

        return (Bonbon)random;
    }
    else if (valueExclude == min) {
        int random = rand() % max + (min + 1);

        return (Bonbon)random;
    }
    else {
        int random1;
        if (valueExclude == 1) {
            random1 = 0;
        }
        else {
            random1 = rand() % (valueExclude - 1) + min;
        }

        int random2 = rand() % max + (valueExclude + 1);

        if (random1 > max) {
            return (Bonbon)random2;
        }

        if (random2 > max) {
            return (Bonbon)random1;
        }

        int random = rand() % 2;

        if (random == 0)
            return (Bonbon)random1;

        return (Bonbon)random2;
    }
}