#include "dictionnaire.h"
#include "mot.h"
#include <iostream>
#include <fstream> //ouvre un fichier
#include <string> 
#include <random>
#include <vector>
#include <sstream>
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
		//si i est trop grand ou négatif, il est impossible d'acceder au i eme mot du dictionnaire
		cout << "ERREUR : dépassement d'indice : i = " << i << endl;
		abort(); //sortie
	}
	return(tabMotsDic_[i]);
}

bool Dictionnaire::contient(Mot mot) {
	string contenuAChercher = mot.getContenu();
	for (int i = 0; i < longueurDic_; i++) {
		if (tabMotsDic_[i].getContenu() == contenuAChercher) {
			return true;
		}
	}
	return false;
}

Mot Dictionnaire::genereMot() {
	std::srand(std::time(NULL));
	if (longueurDic_ == 0) {
		cout << "ERREUR : division par zero" << endl;
		abort(); //sortie
	}
	//genere un indice compris entre 0 et la taille du dictionnaire. L'indice est généré suivant une loi uniforme
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned long long> dis(0, longueurDic_);

	int indice = dis(gen);
	cout << "indice du mot à deviner : " << indice << endl;
	Mot mot = tabMotsDic_[indice];
	cout << "mot à deviner : " << mot.getContenu() << endl;
	return(mot);
}