#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "partie.h"
#include "menu.h"
sf::Font policeMenu;

using namespace std;


OptionMenu::OptionMenu(const string& nom, const string& description)
	: nom_(nom), description_(description)
{
}


Menu::Menu(const string& titre, Historique H) {
	titre_ = titre;
	historique_ = H;
}

void Menu::setTitre(const string& titre)
{
	titre_ = titre;
}

void Menu::ajouterOption(const string& nom, const string& description)
{
	listeOptions_.push_back(OptionMenu(nom, description));
}


void Menu::afficherMenu(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	if (!policeMenu.loadFromFile("calibril.ttf")) {
		std::cout << "ERREUR : police introuvable" << endl;
		abort();
	}
	sf::Text titre;
	titre.setFont(policeMenu);
	titre.setString(titre_);
	titre.setFillColor(sf::Color::Green);
	titre.setCharacterSize(100); // taille en pixels
	titre.setPosition(230, 0); // (35 + i*100 pour la i eme colonne, 60 + 100*j pour la j eme ligne)
	window.draw(titre);


	for (int i = 0; i < listeOptions_.size(); i++) {
		sf::Text option;
		option.setFont(policeMenu);
		option.setString(listeOptions_[i].getDescription());
		option.setFillColor(sf::Color::Black);
		option.setCharacterSize(40); // taille en pixels
		option.setPosition(10, 150 + 70 * i); // (35 + i*100 pour la i eme colonne, 60 + 100*j pour la j eme ligne)
		window.draw(option);
	}

	sf::Text auteurs;
	auteurs.setFont(policeMenu);
	auteurs.setString("Diane Lantran -- Clément Vorms");
	auteurs.setFillColor(sf::Color::Blue);
	auteurs.setCharacterSize(20); // taille en pixels
	auteurs.setPosition(350, 470); // (35 + i*100 pour la i eme colonne, 60 + 100*j pour la j eme ligne)
	window.draw(auteurs);
}

int Menu::demanderChoix(sf::RenderWindow& window)
{
	int choix = -1;
	sf::Event event;
	while (window.pollEvent(event))
	{
		// verifie le type de l'evenement
		switch (event.type)
		{
			// cas où l'utilisteur demande la fermeture de la fenetre
		case sf::Event::Closed:
			window.close();
			break;

		case (sf::Event::MouseButtonPressed):
			if (event.mouseButton.button == sf::Mouse::Left) {
				// position de la souris dans par rapport à la fenêtre
				sf::Vector2i localposition = sf::Mouse::getPosition(window);

				// position de la souris dans le tableau
				float x = localposition.x;
				float y = localposition.y;
				for (int i = 0; i < 6; i++) {
					if ((y < 160 + 80 * i + 30) && (y > 160 + 80 * i - 30)) {
						choix = i;
					}
				}
			}
			break;
		default:
			break;
		}
	}
	return choix;
}

void Menu::executer()
{
	bool fin = false;
	while (!fin) {
		system("cls"); //efface tout ce qui était affiché à l'écran

		sf::RenderWindow fenetreMenu(sf::VideoMode(1000, 500), "Menu principal");
		afficherMenu(fenetreMenu);
		int choix = -1;
		fenetreMenu.display();
		while (choix < 0) {
			choix = demanderChoix(fenetreMenu);
		}
		executerOption(listeOptions_[choix].getNom(), fin);
	}
}

void Menu::executerOption(const string& nom, bool& fin)
{
	fin = false;
	if (nom == "quitter") fin = quitter();
	else if (nom == "aide") aide();
	else if (nom == "jouer") jouer();
	else if (nom == "historique") historique();
	//il n'existe que 4 options dans ce jeu
	else {
		cout << "Option inexistante" << endl;
		system("pause");
	}
}

bool Menu::quitter()
{
	bool fin = false;
	sf::RenderWindow menuFenetre(sf::VideoMode(1000, 500), "Menu quitter");
	menuFenetre.clear(sf::Color::White);
	if (!policeMenu.loadFromFile("calibril.ttf")) {
		std::cout << "ERREUR : police introuvable" << endl;
		abort();
	}
	sf::Text texte1;
	texte1.setFont(policeMenu);
	texte1.setString("Voulez-vous vraiment quitter l'application ?");
	texte1.setFillColor(sf::Color::Black);
	texte1.setCharacterSize(30);
	texte1.setPosition(15, 0);
	menuFenetre.draw(texte1);

	sf::Text texte2;
	texte2.setFont(policeMenu);
	texte2.setString("Oui");
	texte2.setFillColor(sf::Color::Black);
	texte2.setCharacterSize(30);
	texte2.setPosition(70, 30);
	menuFenetre.draw(texte2);

	sf::Text texte3;
	texte3.setFont(policeMenu);
	texte3.setString("Non");
	texte3.setFillColor(sf::Color::Black);
	texte3.setCharacterSize(30);
	texte3.setPosition(170, 30);
	menuFenetre.draw(texte3);

	sf::Event eventQuitter;
	menuFenetre.display();
	bool sortie = false;

	while (sortie == false) {
		if (menuFenetre.pollEvent(eventQuitter)) {
			if ((eventQuitter.type == sf::Event::MouseButtonPressed) && (eventQuitter.mouseButton.button == sf::Mouse::Left)) {
				sf::Vector2i localposition = sf::Mouse::getPosition(menuFenetre);
				// position de la souris dans le tableau
				float x = localposition.x;
				float y = localposition.y;
				//position de Non avec une marge
				if (((y < 60) && (y > 40)) && ((x < 220) && (x > 190))) {
					fin = false;
					sortie = true;
				}
				//position de Oui avec une marge
				if (((y < 60) && (y > 40)) && ((x < 90) && (x > 60))) {
					fin = true;
					sortie = true;
				}
			}
		}
		
	}
	
	return (fin);
}

void Menu::aide()
{
	sf::RenderWindow menuFenetre(sf::VideoMode(1000, 500), "Menu aide");
	menuFenetre.clear(sf::Color::White);
	if (!policeMenu.loadFromFile("calibril.ttf")) {
		std::cout << "ERREUR : police introuvable" << endl;
		abort();
	}
	sf::Text texte1;
	texte1.setFont(policeMenu);
	texte1.setString("La liste ci-dessus vous propose les options disponibles pour ce menu.");
	texte1.setFillColor(sf::Color::Black);
	texte1.setCharacterSize(30);
	texte1.setPosition(15, 0);
	menuFenetre.draw(texte1);

	sf::Text texte2;
	texte2.setFont(policeMenu);
	texte2.setString("Vous devez entrer un numero qui correspond a votre choix et valider");
	texte2.setFillColor(sf::Color::Black);
	texte2.setCharacterSize(30);
	texte2.setPosition(15, 30);
	menuFenetre.draw(texte2);

	sf::Text texte3;
	texte3.setFont(policeMenu);
	texte3.setString("en appuyant sur la touche <Entree>.");
	texte3.setFillColor(sf::Color::Black);
	texte3.setCharacterSize(30);
	texte3.setPosition(15, 60);
	menuFenetre.draw(texte3);

	menuFenetre.display();
	sf::Event event;
	bool sortie = false;
	//il faut qu ele joueuer appuie sur une touche pour quitter le menu aide
	while (sortie == false) {
		if ((menuFenetre.pollEvent(event)) && (event.type == sf::Event::KeyPressed)) {
			sortie = true;
		}
	}
	menuFenetre.close();
}

void Menu::jouer()
{
	cout << "Chargement de la partie en cours..." << endl;
	Partie p;
	p.jouer();
	//a la fin d'une partie, celle-ci est aoutée à l'historique du jeu
	historique_.addPartiesJouees(p);
}

void Menu::historique()
{
	cout << "Chargement de l'historique en cours..." << endl;
	sf::RenderWindow menuFenetre(sf::VideoMode(1000, 500), "Menu historique");
	menuFenetre.clear(sf::Color::White);
	historique_.afficher(menuFenetre);
}