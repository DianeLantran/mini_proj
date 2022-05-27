# pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;
//defini ce qu'est un mot : un objet d'une certaine longueur contenant un string, ce string est consid�r� comme valide ou non suivant son appartenance au dictionnaire
class Mot {
	int longueur_;
	bool valide_;
	string contenu_;
public :
	Mot(string contenu =""); //initialise le mot
	string getContenu() const; //retourne le contenu du mot
	void setContenu(string nouveauContenu); //donne un contenu au mot
	int getTaille() const; //retourne la taille du mot
	void setValide(bool); //fixe la validit� ou non du mot
	bool estValide(); //retourne la validit� du mot
	vector <int> lettresBienPlacees(Mot mot); //renvoie un vecteur contenant les indices des lettres du mot qui sont bien plac�e par rapport au mot � deviner
	vector <int> lettresMalPlacees(Mot mot); //renvoie un vecteur contenant les indices des lettres du mot qui sont contenue dans le mot � deviner mais mal plac�es
};


int nbMotsFichier(string fichier_txt); //renvoie le nombre de mots contenus dans un fichier txt
Mot* motsFichiers(string fichiertxt, int nbMots); //retourne un tableau contenant des pointeurs sur tous les mots contenu dans le fichier txt pass� en param�tres
bool estInclu(int, vector <int>); //retourne un bool�en indiquant si un entier est inclu dans un tableau d'entier.
//cette fonction est utilis�e pour d�terminer l'appartenance de l'indice d'une lettre aux vecteurs renvoy�s par lettresBienPlacees et lettresMalPlacees

