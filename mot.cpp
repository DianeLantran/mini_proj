#include "mot.h"
#include "dictionnaire.h"
#include <iostream>
#include <fstream> //ouvre un fichier
#include <string> 
#include <vector>
#include <corecrt_wstring.h>
#include "utils.h" //definit la fonction random_at_most
#include <sstream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
using namespace std;

Mot::Mot(string contenu) {
	contenu_ = contenu;
	longueur_ = contenu_.size();
	valide_ = false;
}
string Mot::getContenu() const {
	return(contenu_);
}
void Mot::setContenu(string nouveauContenu) {
	contenu_ = nouveauContenu;
	longueur_ = nouveauContenu.size();
}
void Mot::setValide(bool b) {
	valide_ = b;
}
bool Mot::estValide() {
	return(valide_);
}
int Mot::getTaille() const {
	return(longueur_);
}


Mot* motsFichiers(string fichier_txt, int nbMots) {
	ifstream fichier_mots(fichier_txt); //le fichier .txt contenant les mots du dictionnaire
	Mot * tabMots = new Mot[nbMots];
	Mot mot;
	string contenu = mot.getContenu();

	 //On lit le fichier .txt ligne par ligne
	for (int i = 0; i < nbMots; i++) {
		getline(fichier_mots, contenu); //la i eme ligne est lue, stockée dans "contenu" puis supprimée
		//cout << i << "eme mot : " << contenu << endl;
		mot.setContenu(contenu);
		mot.setValide(true); //l'appartenance au dictionnaire definit le mot comme valide
		tabMots[i] = mot;
	}
	// ferme le fichier txt
	fichier_mots.close();
	return(tabMots);
}

int nbMotsFichier(string fichier_txt) {
	int i = 0;
	ifstream fichier_mots(fichier_txt);
	string ligne;
	while (getline(fichier_mots, ligne)) {
		i += 1;
	}
	return(i);
	}
//string& Mot::operator[](int i) {
//	string& lettre = contenu_[i];
//	return(&contenu_[i]);
//}
vector <int> Mot::lettresCommunes(Mot mot) {
	vector <int> lettresCommunesBienPlacees = {}; //stocke les indices du mot proposés qui correspondent aux lettres bien placées
	vector <int> lettresCommunesMalPlacees = {}; //stocke les indices du mot proposés qui correspondent aux lettres mal placées
	int nbBienPlacees = 0;
	int nbMalPlacees = 0;
	string proposition = mot.getContenu();
	string reference = contenu_;
	if (proposition.size() != longueur_) {
		cout << "ERREUR : les mots a comparer n'ont pas la meme taille" << endl;
		abort();
	}
	else {
		for (int i = 0; i < longueur_; i++) {
			if (reference[i] == proposition[i]) {
				nbBienPlacees += 1;
				lettresCommunesBienPlacees.resize(nbBienPlacees);
				cout << proposition[i] << " est bien placee" << endl;
				lettresCommunesBienPlacees.push_back(i);
			}
			else {
				for (int j = 0; j < longueur_; j++) {
					if (reference[j] == proposition[i]) {
						nbMalPlacees += 1;
						lettresCommunesMalPlacees.resize(nbMalPlacees);
						cout << proposition[i] << " est mal placee" << endl;
						lettresCommunesMalPlacees.push_back(i);
					}
				}
			}
		}
	}
	return(lettresCommunesBienPlacees, lettresCommunesMalPlacees);
}