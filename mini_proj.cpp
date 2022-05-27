// mini_proj.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include"mot.h"
#include "dictionnaire.h"
#include"grille.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "partie.h"
#include "menu.h"
#include "historique.h"
#include <string>

//#include <random>
using namespace std;


int main()
{
	Historique H; //initialisation de l'historique
	//affichage du menu et initialisation des options
	Menu Menu("Jeu de Motus", H);
	Menu.ajouterOption("jouer", "Lancer une partie");
	Menu.ajouterOption("historique", "Historique du jeu");
	Menu.ajouterOption("quitter", "Quitter le jeu");
	Menu.ajouterOption("aide", "Aide");
	Menu.executer();
	return 0;
}
