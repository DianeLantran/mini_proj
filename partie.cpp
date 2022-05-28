#include "dictionnaire.h"
#include "mot.h"
#include "partie.h"
#include <iostream>
#include <string> 
#include <vector>
#include "utils.h" //definit la fonction random_at_most
#include <sstream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
using namespace std;


Partie::Partie(Mot aDeviner, vector <Mot> propositions, bool enCours, bool gagnee) {
	nbPropositions_ = propositions.size();
	aDeviner_ = aDeviner;
	propositions_ = propositions;
	enCours_ = enCours;
	gagnee_ = gagnee;
}

Mot Partie::getMotaDeviner() const {
	return(aDeviner_);
}

vector <Mot> Partie::getPropositions() const {
	return(propositions_);
}

int Partie::getNbPropositions() const {
	return(nbPropositions_);
}

bool Partie::getEstGagnee() const {
	return(gagnee_);
}

void Partie::ajouteProposition(Mot nouvelleProposition) {
	propositions_.push_back(nouvelleProposition);
}

void Partie::jouer() {

	// preparation du dictionnaire
	int nbtotmots = nbMotsFichier("liste_finale.txt"); //renvoie le nombre de mots contenus dans le dictionnaire. Ici 323578
	Mot* tabMotsDico = motsFichiers("liste_finale.txt", nbtotmots); //stocke le contenu du fichier txt dans un vecteur
	Dictionnaire dicoMotFr(tabMotsDico, nbtotmots); //d�finit le dictionnaire contenant l'ensemble des mots consid�r�s comme valides

	//creation de la structure de la grille
	aDeviner_ = dicoMotFr.genereMot();
	cout << "le joueur doit deviner le mot : " << aDeviner_.getContenu() << endl;
	int taille_grille = aDeviner_.getTaille();
	Grille grille(taille_grille, 6); //on veut 6 essais possibles avant de perdre
	sf::RenderWindow window(sf::VideoMode(taille_grille * 100, grille.getNbCasesV() * 100 + 50+300), "jeu de motus"); //taille de la fen�tre avec une marge de 50 pour mettre les messages d'erreur

	//on stocke le contenu du mot entr� dans la variable proposition
	Mot proposition;
	string contenuproposition;

	sf::Event event;
	while (window.isOpen() && enCours_)
	{
		// on reinitialise la fen�tre et on met � jour son contenu
		window.clear(sf::Color::White);
		grille.afficherGrille(window);
		grille.afficherMots(propositions_, aDeviner_, window);

		while (window.pollEvent(event))
		{
			// differents cas suivant le type de l'evenement
			switch (event.type)
			{
				// cas o� l'utilisteur demande la fermeture de la fenetre
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::TextEntered:
				//touche effacer
				if ((event.text.unicode == 8) && (contenuproposition.size() != 0)) {
					contenuproposition.pop_back();
				}

				//lettre en majuscule, lettre en minuscule ou tiret du 6
				if ((contenuproposition.size() < taille_grille) && (nbPropositions_ < 6)) {
					if (((event.text.unicode > 96) && (event.text.unicode < 123)) || ((event.text.unicode > 40) && (event.text.unicode < 91)) || (event.text.unicode == 45)) {
						contenuproposition.push_back(event.text.unicode);
					}
				}
				break;

			//si on entre du texte de la bonne taille, contenu dans le dictionnaire et qu'on appuie sur la touche entr�e, il est stock� dans "proposition" et la liste des propositions est actualis�e
			case sf::Event::KeyPressed:
				if ((event.key.code == sf::Keyboard::Enter) && (contenuproposition.size() == taille_grille)) {
					proposition.setContenu(contenuproposition);
					if (dicoMotFr.contient(proposition)) { //verification du fait que le mot est contenu dans le dictionnaire
						propositions_.push_back(proposition);
						nbPropositions_ += 1;

						//cas o� le mot � deviner est entr�
						if (contenuproposition == aDeviner_.getContenu()) {
							grille.afficherMots(propositions_, aDeviner_, window); //on affiche le mot ici car la sortie de boucle ne permettrait pas de l'afficher autrement
							string message = "Felicitations, vous remportez la partie ! Fermez la grille pour revenir au menu principal.";
							grille.afficherMessage(message, window);
							//la partie est gagn�e et la partie est termin�e
							gagnee_ = true;
							enCours_ = false;
						}
						//si le nombre de propositions exc�de 6, la partie est perdue donc finie
						else if (nbPropositions_ >= 6) {
							enCours_ = false;
						}
						// si la partie n'est ni gagn�e, ni perdue, le contenu de la proposition est r�initialis�
						contenuproposition = "";
					}

					//si le mot entr� n'est pas valide
					else {
						bool sortie = false;
						// on affiche un message informant le joueur que sa proposition n'est pas retenue jusqu'� ce que le joueur presse une nouvelle touche
						grille.afficherMessage("Le mot entr� n'est pas valide, v�rifiez l'othographe.", window);
						window.display();
						while (sortie == false) {
							if ((window.pollEvent(event)) && (event.type == sf::Event::KeyPressed)) {
								sortie = true;
							}
						}
						contenuproposition = "";
					}
				}
				break;
			default:
				break;
			}
		}

		// plus aucun evenement detect�
		if (contenuproposition != "") { //si des lettres ont �t� tapp�es, elles sont affich�es
			grille.afficherLettres(contenuproposition, propositions_, window);
		}

		//cas o� le joueur a perdu la partie
		else if ((nbPropositions_ >= 6)&&(gagnee_ == false)) {
			grille.afficherMots(propositions_, aDeviner_, window);
			string message = "Perdu ! Le mot � deviner �tait : " + aDeviner_.getContenu();
			grille.afficherMessage(message, window);
			enCours_ = false;
		}

		// mise � jour de la fen�tre
		window.display();
	}
	//au sortir de cette boucle, le mot a �t� trouv� ou le nombre de proposition max est atteint
	//on laisse la grille affich�e jusqu'� ce que l'utilisateur appuie sur fermer

	while (window.isOpen()) {

		// demande de fermeture de la fen�tre
		window.pollEvent(event);
		if (event.type == sf::Event::Closed)
			window.close();
	}
}