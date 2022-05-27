#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "mot.h"
using namespace std;

//la classe dictionnaire permet de définir l'ensemble des mots considérés comme valides par le jeu
class Dictionnaire {
	int longueurDic_; //la longueur du dictionnaire
	Mot* tabMotsDic_; //pointeur qui pointe vers le tableau contenant l'ensemble des mots valides
public:
	Dictionnaire(Mot* tabMotsDic = new Mot[0], int longueurDic = 0); //initialise le dictionnaire. Par défaut il est vide
	~Dictionnaire(); //destructeur du dictionnaire
	Mot genereMot(); //génère aléatoirement un mot dans le dictionnaire suivant une loi uniforme
	Mot& operator[](int i); //renvoie le i eme mot du dictionnaire grace à dictionnaire[i]
	int getLongueurDic() const; //retourne la longueur du dictionnaire
	bool contient(Mot); //renvoie 1 si le mot est contenu dans le dictionnaire, 0 sinon
};

