# pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class Mot {
	int longueur_;
	bool valide_;
	string contenu_;
public :
	Mot(string contenu ="");
	string getContenu() const;
	void setContenu(string nouveauContenu);
	int getTaille() const;
	void setValide(bool);
	bool estValide();
	vector <int> lettresCommunes(Mot mot);
};


Mot* motsFichiers(string fichiertxt, int nbMots);
int nbMotsFichier(string fichier_txt);

