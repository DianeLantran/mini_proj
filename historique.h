#pragma once
#include <vector>
#include "partie.h"

//la classe historique permet de définir l'historique du jeu, il contient l'ensemble des parties terminées dans un vecteur
//l'historique peut être mis à jour en ajoutant des parties dans le vecteur partiesJouees_ grace à la méthode addPartiesJouees
class Historique {
	vector <Partie> partiesJouees_;
public :
	Historique(vector <Partie> partiesJouees = {}); //initialise un historique, par défaut, l'historique est vide
	void afficher(sf::RenderWindow& window); //affiche l'historique dans une fenetre SFML
	void addPartiesJouees(Partie p); //ajoute une partie terminée à l'historiquess
};