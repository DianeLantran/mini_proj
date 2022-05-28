#pragma once
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "mot.h"
using namespace std;
//la classe grille permet de définir la grille contenant les propositions du joueur lorsqu'il tente de trouver le mot à deviner
//la classe permet de dessiner la grille, les lettres qu'elle contient et la couleur avec laquelle les lettres exactes ou mal placées sont affichées
class Grille {
	int nb_caseH_;
	int nb_caseV_;
public:
	Grille(int nb_caseH = 0, int nb_caseV = 0); //initialise la grille
	~Grille(); //détruit la grille
	void afficherGrille(sf::RenderWindow& window); //affiche la grille dans une fenetre SFML
	void afficherAlphabet(sf::RenderWindow& window); //affiche l'alphabet en bas de la grille
	void afficherLettres(string motEntre, vector <Mot> propositions, sf::RenderWindow& window); //récupère les lettres entrées sous forme d'un mot et l'affiche
	void afficherMots(vector <Mot> propositions, Mot aDeviner, sf::RenderWindow& window); //affiche une proposition et colorie les lettres suivant leur rapport au mot à deviner
	int getNbCasesV(); //retourne le nombre de cases dans une colonne de la grille
	int getNbCasesH(); //retourne le nombre de cases dans une ligne de la grille
	void afficherMessage(string message, sf::RenderWindow& window); //affiche un message en haut de la grille
};

