#include "historique.h"
#include <iostream>
using namespace std;

sf::Font policeHistorique;

Historique::Historique(vector <Partie> partiesJouees) {
	partiesJouees_ = partiesJouees;
}
void Historique::afficher(sf::RenderWindow& window) {
	//verifie si la police a bien �t� import�e, sinon renvoie un message d'erreur
	if (!policeHistorique.loadFromFile("calibril.ttf")) {
		std::cout << "ERREUR : police introuvable" << endl;
		abort();
	}
	//configure le titre du menu historique
	sf::Text titre;
	titre.setFont(policeHistorique);
	titre.setString("Historique des parties jou�es");
	titre.setFillColor(sf::Color::Green);
	titre.setCharacterSize(70);
	titre.setPosition(90, 0);
	window.draw(titre);

	//si aucune partie n'a �t� jou�e, l'historique invite le joueur � jouer
	if (partiesJouees_.size() == 0) {
		sf::Text pasJoue;
		pasJoue.setFont(policeHistorique);
		pasJoue.setString("Aucune partie jou�e. Revenuez au menu principal et choisissez lancer une partie !");
		pasJoue.setFillColor(sf::Color::Black);
		pasJoue.setCharacterSize(30);
		pasJoue.setPosition(10, 150);
		window.draw(pasJoue);
	}
	//pour chaque partie jou�e, l'historique affiche son numero le mot � deviner dans cette partie et si la partie � �t� gagn�e (dans ce cas en combien de coups) ou perdue
	for (int i = 0; i < partiesJouees_.size(); i++) {
		string texte = "Partie " + to_string(i+1);
		texte += " : ";
		if (partiesJouees_[i].getEstGagnee()) {
			texte += "Le mot � deviner �tait : ";
			texte += partiesJouees_[i].getMotaDeviner().getContenu();
			texte += ", gagn�e en ";
			texte += to_string(partiesJouees_[i].getNbPropositions());
			texte += " essais.";
		}
		else {
			texte += "perdu...";
		}

		sf::Text partie;
		partie.setFont(policeHistorique);
		partie.setString(texte);
		partie.setFillColor(sf::Color::Black);
		float taille = 0;
		//si beaucoup de parties ont �t� jou�e, la taille de la police est diminu�e afin d'afficher un maximum de partie
		if (partiesJouees_.size() > 13) {
			taille = 30 - partiesJouees_.size()/2;
		}
		else {
			taille = 30;
		}
		partie.setCharacterSize(taille);
		partie.setPosition(20, 100 + taille * i);
		window.draw(partie);
	}
	window.display();
	bool sortie = false;
	sf::Event sortieHistorique;
	//pour sortir du menu Historique, le joueur doit appuyer sur n'importe quelle touche
	while (sortie == false) {
		if (window.pollEvent(sortieHistorique)) {
			if (sortieHistorique.type == sf::Event::KeyPressed) {
				sortie = true;
			}
		}
	}

}

void Historique::addPartiesJouees(Partie p) {
	partiesJouees_.push_back(p);
}