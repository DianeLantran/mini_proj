#include "grille.h"
#include "mot.h"
#include "dictionnaire.h"
#include <string>
#include <vector>
sf::Font police;

using namespace std;

Grille::Grille(int nb_casesH, int nb_casesV) {
	nb_caseH_ = nb_casesH;
	nb_caseV_ = nb_casesV;
}

Grille::~Grille() {
}

void Grille::afficherGrille(sf::RenderWindow& window) {
	//la grille contient toujours 6 lignes, sa taille ne d�pend que de son nombre de colonne
	int tailleGrille = nb_caseH_;
	vector<sf::RectangleShape> lines;
	int nb_lignes_h = nb_caseV_+1;
	int nb_lignes_v = tailleGrille;

	//definition des lignes horizontales
	for (int i = 0; i < nb_lignes_h; i++) {
		//lignes horizontales
		lines.push_back(sf::RectangleShape(sf::Vector2f(tailleGrille * 100, nb_caseV_)));
	}
	//definition des lignes verticales
	for (int i = 0; i < nb_lignes_v; i++) {
		//lignes verticales
		lines.push_back(sf::RectangleShape(sf::Vector2f(6, nb_caseV_*100))); // 6 : largeur de la ligne
	}
	//positionnement des lignes horizontales
	for (int i = 0; i < nb_lignes_h; i++) {
		lines[i].setPosition(0,50 + 100 * i); //marge de 50 pour les messages affich�s en haut de la grille et cases carr�es de cot� 97
	}
	//positionnement des lignes verticales
	for (int i = nb_lignes_h; i < nb_lignes_v + nb_lignes_h; i++) {
		lines[i].setPosition(97 + 100 * (i - nb_lignes_h), 50); //marge de 50 pour les messages affich�s en haut de la grille et cases carr�es de cot� 97
	}

	// met les lignes en noir
	for (size_t i = 0; i < lines.size(); i++)
		lines[i].setFillColor(sf::Color::Black);

	// affichage des lignes
	for (size_t i = 0; i < lines.size(); i++)
		window.draw(lines[i]);
}
int Grille::getNbCasesV() {
	return(nb_caseV_);
}
int Grille::getNbCasesH() {
	return(nb_caseH_);
}

void Grille::afficherLettres(string motEntre, vector <Mot> propositions, sf::RenderWindow& window) {
	//verifie que la police � utilis�e est correctement import�e
	if (!police.loadFromFile("calibril.ttf")) {
		cout << "ERREUR : police introuvable" << endl;
		abort();
	}
	int nbPropositions = propositions.size();
	int tailleMotEntre = motEntre.size();
	//affichage de chacune des lettres du mot entr� une � une
	for (int i = 0; i < tailleMotEntre; i++) {
		char lettreMaj = toupper(motEntre[i]); //permet de mettre les lettres en majuscules
		sf::Text lettre;
		lettre.setFont(police);
		lettre.setString(lettreMaj);
		lettre.setFillColor(sf::Color::Black);
		lettre.setCharacterSize(55); // taille en pixels
		lettre.setPosition(35 + 100 * i, 60 + 100 * nbPropositions); // (35 + i*100 pour la i eme colonne, 60 + 100*j pour la j eme ligne)
		window.draw(lettre);
	}
	
}

void Grille::afficherMots(vector <Mot> propositions, Mot aDeviner, sf::RenderWindow& window) {
	//verifie que la police � utilis�e est correctement import�e
	if (!police.loadFromFile("calibril.ttf")) {
		cout << "ERREUR : police introuvable" << endl;
		abort();
	}

	//comme la fen�tre est r�initialis�e � chaque nouvelle proposition, il faut r�afficher chaque ancienne proposition � chaque fois
	for (int j = 0; j < propositions.size(); j++) {
		string contenu = propositions[j].getContenu();
		for (int i = 0; i < contenu.size(); i++) {
			//affichage des lettres de la i eme proposition unes � unes
			char lettreMaj = toupper(contenu[i]);
			sf::Text lettre;
			lettre.setFont(police);
			lettre.setString(lettreMaj);
			lettre.setFillColor(sf::Color::Black);
			lettre.setCharacterSize(55); // taille en pixels
			lettre.setPosition(35 + 100 * i, 60 + 100 * j); // (35 + i*100 pour la i eme colonne, 60 + 100*j pour la j eme ligne)

			//pour colorier correctement les lettres suivant leur rapport avec le mot � deviner, on verifie leur appartenance aux vecteurs suivants :
			vector <int> indice_communesBienPlacees = aDeviner.lettresBienPlacees(propositions[j]);
			vector <int> indice_communesMalPlacees = aDeviner.lettresMalPlacees(propositions[j]);

			//si la j eme lettre de la i eme proposition est identique avec la j eme lettre du mot a deviner, elle apparait avec un fond vert
			if (estInclu(i, indice_communesBienPlacees)) {
				sf::RectangleShape carreVert(sf::Vector2f(96, 96));
				carreVert.setPosition(1.5+100 * i, 53+ 100 * j);
				carreVert.setFillColor(sf::Color::Green);
				window.draw(carreVert);
			}
			// si la j eme lettre de la i eme propositon est contenue dans le mot a deviner, elle apparait entour�e pas un rond jaune
			else if (estInclu(i, indice_communesMalPlacees)) { //cas o
				sf::CircleShape rondJaune(47);
				rondJaune.setPosition(100 * i +3, 56 +100 * j);
				rondJaune.setFillColor(sf::Color::Yellow);
				window.draw(rondJaune);
			}
			//chaque lettre est dessin�e dans la fen�tre de la grille
			window.draw(lettre);
		}
	}
	
}

void Grille::afficherMessage(string message, sf::RenderWindow& window) {
	int nbLettres = message.size();
	int taillePolice = nb_caseH_ * 100 / 40; //la taille de la police du message s'adapte � la taille de la fen�tre
	int positionCentreeSurGrille = (nb_caseH_ * 100 / 2) - taillePolice * nbLettres / 5; //on centre le message sur la fen�tre
	sf::Text message_sf;
	message_sf.setFont(police);
	message_sf.setString(message);
	message_sf.setFillColor(sf::Color::Black);
	message_sf.setCharacterSize(taillePolice); // taille en pixels
	message_sf.setPosition(positionCentreeSurGrille, 12);
	window.draw(message_sf);
}