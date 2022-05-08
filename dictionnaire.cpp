#include "dictionnaire.h"
#include "mot.h"
#include <iostream>
#include <fstream> //ouvre un fichier
#include <string> 
#include <vector>
//#include <corecrt_wstring.h>
#include "utils.h" //definit la fonction random_at_most
#include <sstream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
using namespace std;


Dictionnaire::Dictionnaire(Mot* p, int longueurDic) {
	tabMotsDic_ = p;
	longueurDic_ = longueurDic;
	for (int i = 0; i < longueurDic; i++) {
		tabMotsDic_[i] = p[i];
	}
}
Dictionnaire::~Dictionnaire() {
	delete[] tabMotsDic_;
}
int Dictionnaire::getLongueurDic() const {
	return(longueurDic_);
}


Mot& Dictionnaire::operator[](int i) {
	if (i < 0 || i >= longueurDic_) {
		cout << "ERREUR : dépassement d'indice : i = " << i << endl;
		abort(); //sortie
	}
	return(tabMotsDic_[i]);
}

Mot Dictionnaire::genereMot() {
	if (longueurDic_ == 0) {
		cout << "ERREUR : division par zero" << endl;
		abort(); //sortie
	}
	srand((unsigned)time(NULL));
	int indice = rand() % longueurDic_;
	cout << "indice du mot à deviner : " << indice << endl;
	Mot mot = tabMotsDic_[indice];
	cout << "mot à deviner : " << mot.getContenu() << endl;
	return(mot);
}