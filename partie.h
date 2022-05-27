#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "mot.h"
#include "dictionnaire.h"
#include "grille.h"

using namespace std;
// La classe partie permet de définir une partie dans le jeu
// Une partie contient des propositions de mots. Ces propositions sont contenues dans le vecteur propositions_
//Une partie dépend aussi du mot à deviner.
// Une partie a 2 statuts : enCours_ (ou terminée) et gagnee_ (ou perdue)
//Dès que la partie n'est plus enCours_, elle est ajoutée à l'historique
class Partie {
	int nbPropositions_;
	Mot aDeviner_;
	vector <Mot> propositions_;
	bool enCours_;
	bool gagnee_;
public:
	Partie(Mot aDeviner = Mot(""), vector <Mot> propositions = {}, bool enCours = true, bool gagnee = false); //initialise une partie. Par défaut elle est en cours, sans proposition, et perdue. Le mot à deviner est le mot vide
	Mot getMotaDeviner() const; //retourne le mot à deviner
	vector <Mot> getPropositions() const; //retourne les propositions faites au cours de la partie
	int getNbPropositions() const; //retourne le nombre de propositions faites au cours de la partie
	bool getEstGagnee() const; //renvoie le statut de la partie : 1 si gagnée et 0 si perdue
	void ajouteProposition(Mot); //ajoute un mot au vecteur des propositions
	void jouer(); //lance la partie
};