#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "mot.h"
#include "dictionnaire.h"
#include "grille.h"

using namespace std;
// La classe partie permet de d�finir une partie dans le jeu
// Une partie contient des propositions de mots. Ces propositions sont contenues dans le vecteur propositions_
//Une partie d�pend aussi du mot � deviner.
// Une partie a 2 statuts : enCours_ (ou termin�e) et gagnee_ (ou perdue)
//D�s que la partie n'est plus enCours_, elle est ajout�e � l'historique
class Partie {
	int nbPropositions_;
	Mot aDeviner_;
	vector <Mot> propositions_;
	bool enCours_;
	bool gagnee_;
public:
	Partie(Mot aDeviner = Mot(""), vector <Mot> propositions = {}, bool enCours = true, bool gagnee = false); //initialise une partie. Par d�faut elle est en cours, sans proposition, et perdue. Le mot � deviner est le mot vide
	Mot getMotaDeviner() const; //retourne le mot � deviner
	vector <Mot> getPropositions() const; //retourne les propositions faites au cours de la partie
	int getNbPropositions() const; //retourne le nombre de propositions faites au cours de la partie
	bool getEstGagnee() const; //renvoie le statut de la partie : 1 si gagn�e et 0 si perdue
	void ajouteProposition(Mot); //ajoute un mot au vecteur des propositions
	void jouer(); //lance la partie
};