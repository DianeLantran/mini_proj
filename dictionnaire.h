#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "mot.h"
using namespace std;

class Dictionnaire {
	int longueurDic_;
	Mot* tabMotsDic_; //pointeur qui pointe vers le tableau contenant l'ensemble des mots valides
public:
	Dictionnaire(Mot* tabMotsDic = new Mot[0], int longueurDic = 0);
	~Dictionnaire();
	Mot genereMot();
	Mot& operator[](int i);
	int getLongueurDic() const;
};

