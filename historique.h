#pragma once
#include <vector>
#include "partie.h"

//la classe historique permet de d�finir l'historique du jeu, il contient l'ensemble des parties termin�es dans un vecteur
//l'historique peut �tre mis � jour en ajoutant des parties dans le vecteur partiesJouees_ grace � la m�thode addPartiesJouees
class Historique {
	vector <Partie> partiesJouees_;
public :
	Historique(vector <Partie> partiesJouees = {}); //initialise un historique, par d�faut, l'historique est vide
	void afficher(sf::RenderWindow& window); //affiche l'historique dans une fenetre SFML
	void addPartiesJouees(Partie p); //ajoute une partie termin�e � l'historiquess
};