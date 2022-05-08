// mini_proj.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include"mot.h"
#include "dictionnaire.h"
#include"grille.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;


int main()
{
	int nbtotmots = nbMotsFichier("liste_finale.txt"); //renvoie le nombre de mots contenus dans le dictionnaire. Ici 323578
	Mot* tabMotsDico = motsFichiers("liste_finale.txt", nbtotmots); //stocke le contenu du fichier txt dans un vecteur
	Dictionnaire dicoMotFr(tabMotsDico, nbtotmots); //définit le dictionnaire contenant l'ensemble des mots considérés comme valides
	//22740
	Mot mot_a_deviner = dicoMotFr.genereMot();
	cout << "le joueur doit deviner le mot : " << mot_a_deviner.getContenu() << endl;

	Mot m1("moyen");
	Mot m2("mones");
	m1.lettresCommunes(m2);
	
	// grille du jeu
	int taille_grille = mot_a_deviner.getTaille();
	cout << "taille grille : " << taille_grille;
	vector <int>tab(6,taille_grille);

	for (int i = 0; i < (int)tab.size(); i++) {
		tab[i] = 0;
	}

	// compte le nombre de cases vide
	int nbleft = 9;	sf::RenderWindow window(sf::VideoMode(taille_grille*100, 600), "jeu de motus"); //taille de la fenêtre



	// boucle principale
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			// demande de fermeture de la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();

			// appui sur le bouton gauche
			if ((event.type == sf::Event::MouseButtonPressed)
				&& (event.mouseButton.button == sf::Mouse::Left)) {
				// si on a plus de place, on vide le tableau
				if (nbleft == 0) {
					for (size_t i = 0; i < 3; i++)
						for (size_t j = 0; j < 3; j++)
							tab[i] = 0;
					nbleft = 9;
				}
				// sinon, on place notre jeton
				else {
					// position de la souris dans par rapport à la fenêtre
					sf::Vector2i localposition = sf::Mouse::getPosition(window);

					// position de la souris dans le tableau
					localposition /= 100;

					// affichage console des coordonées
					cout << localposition.x << " " << localposition.y << std::endl;

					// si on tombe sur une case vide
					if (tab[localposition.x]== 0) {
						//On remplit la case par la lettre que le joueur rentre au clavier
						// on met a jour le nombre de cases vides
						nbleft--;
					}
				}
			}
		}

		// on efface la fenêtre (en blanc)
		window.clear(sf::Color::White);

		// on affiche la grille
		afficherGrille(window, taille_grille);


		// mise à jour de la fenêtre
		window.display();
	}

	return 0;
}
