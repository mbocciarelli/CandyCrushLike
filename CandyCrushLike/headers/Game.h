//
// Created by Daniel Chiquet on 12/11/2021.
//
#ifndef HELLOSFML_SFML_TEST_H
#define HELLOSFML_SFML_TEST_H

#include <iostream>

#include "Grille.h"
#include "../SFML/Graphics.hpp"
#include "../headers/Grille.h"
#include "../SFML/Graphics/Sprite.hpp"

class Game {
private : 
	/*
		Paramétres
	*/
	int wWidth = 1920;
	int wHeight = 1080;

	int widthMarge;
	int heightMarge;

	int widthGrille = 10;
	int heightGrille = 10;

	int xFirstPoint;
	int yFirstPoint;
	int sizeCell;
	float sizeSprite;

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
		Fenêtre
	*/

	Grille* grille;

	sf::RenderWindow window;

	/*
		Objectifs
	*/

	int coutSwap = 0;
	int maxSwap;
	std::map<Bonbon, int> objectifs;
	std::vector<int> coutObjectifs;

	void afficherObjectifs();

public :
	Game() {
		window.create(sf::VideoMode(wWidth, wHeight), "SFML works!", sf::Style::Close | sf::Style::Titlebar);
	}

	void StartGame();

	void CalculParameters();

	void GenerateObjectifs();

	void addCoutObjectifs(int place, int value, int maxValue) {
		coutObjectifs.at(place) += value;
		if (coutObjectifs.at(place) > maxValue)
			coutObjectifs.at(place) = maxValue;
	}

	void CalculSizeCell();

	void CalculSizeSprite();

	Grille* load(int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, float sizeSprite);

	void loadTexture(Grille* grille);

	void loadSprite(Grille* grille, int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, float sizeSprite);

	void dessinerJeu(Grille* grille);

	Bonbon generateBonbon(int min, int max);

	Bonbon generateBonbonWithExcludeBonbon(int min, int max, int valueExclude);

	bool eventClickLeft(sf::Event event);

	void checkMouseEvent();

	bool IsOnGrid(int xClick, int yClick);

	void UpdateGrille();

	void UpdateSizeItem(Item* item, int i, int j);

	Cell GetCell(int xClick, int yClick);

	bool IsAroundPrevCell(Cell cell);

	void changeAlphaColor(Cell cell, int value);
};

#endif //HELLOSFML_SFML_TEST_H