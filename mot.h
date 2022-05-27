# pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;
//defini ce qu'est un mot : un objet d'une certaine longueur contenant un string, ce string est considéré comme valide ou non suivant son appartenance au dictionnaire
class Mot {
	int longueur_;
	bool valide_;
	string contenu_;
public :
	Mot(string contenu =""); //initialise le mot
	string getContenu() const; //retourne le contenu du mot
	void setContenu(string nouveauContenu); //donne un contenu au mot
	int getTaille() const; //retourne la taille du mot
	void setValide(bool); //fixe la validité ou non du mot
	bool estValide(); //retourne la validité du mot
	vector <int> lettresBienPlacees(Mot mot); //renvoie un vecteur contenant les indices des lettres du mot qui sont bien placée par rapport au mot à deviner
	vector <int> lettresMalPlacees(Mot mot); //renvoie un vecteur contenant les indices des lettres du mot qui sont contenue dans le mot à deviner mais mal placées
};


int nbMotsFichier(string fichier_txt); //renvoie le nombre de mots contenus dans un fichier txt
Mot* motsFichiers(string fichiertxt, int nbMots); //retourne un tableau contenant des pointeurs sur tous les mots contenu dans le fichier txt passé en paramètres
bool estInclu(int, vector <int>); //retourne un booléen indiquant si un entier est inclu dans un tableau d'entier.
//cette fonction est utilisée pour déterminer l'appartenance de l'indice d'une lettre aux vecteurs renvoyés par lettresBienPlacees et lettresMalPlacees

