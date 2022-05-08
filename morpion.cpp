#include <sfml/graphics.hpp>
#include <iostream>
#include <vector>

// affichage de la grille
void drawgrid(sf::RenderWindow &window) {
	std::vector<sf::RectangleShape> lines;

	// lignes verticales
	lines.push_back(sf::RectangleShape(sf::Vector2f(6, 300)));
	lines.push_back(sf::RectangleShape(sf::Vector2f(6, 300)));
	// lignes horizontalesH
	lines.push_back(sf::RectangleShape(sf::Vector2f(300, 6)));
	lines.push_back(sf::RectangleShape(sf::Vector2f(300, 6)));

	// positionnement des lignes
	lines[0].setPosition(97, 0);
	lines[1].setPosition(197, 0);
	lines[2].setPosition(0, 97);
	lines[3].setPosition(0, 197);

	// lignes de couleurs noires
	for (size_t i = 0; i < lines.size(); i++)
		lines[i].setFillColor(sf::Color::Black);

	// affichage
	for (size_t i = 0; i < lines.size(); i++)
		window.draw(lines[i]);
}

// affichage d'une croix
void drawcross(sf::RenderWindow &window, size_t i, size_t j) {

	// deux lignes tourn�es de 45�
	sf::RectangleShape r1(sf::Vector2f(4, 80));
	sf::RectangleShape r2(sf::Vector2f(4, 80));

	// par d�faut, l'origine est en haut � droite du rectangle
	// on met l'origine au milieu pour simplifier les calculs
	r1.setOrigin(2, 40);
	r2.setOrigin(2, 40);


	// positionnement
	r1.setPosition(i * 100 + 50, j * 100 + 50);
	r2.setPosition(i * 100 + 50, j * 100 + 50);

	// rotation
	r1.rotate(45);
	r2.rotate(-45);

	// coueleur bleu
	r1.setFillColor(sf::Color::Blue);
	r2.setFillColor(sf::Color::Blue);

	// affichage
	window.draw(r1);
	window.draw(r2);
}

// affichage d'un cercle
void drawcircle(sf::RenderWindow &window, size_t i, size_t j) {
	// rayon = 30px
	sf::CircleShape c(30);

	// contour rouge d'une �paisseur de 4px
	c.setOutlineColor(sf::Color::Red);
	c.setOutlineThickness(4);

	c.setOrigin(30, 30);
	c.setPosition(i * 100 + 50, j * 100 + 50);

	window.draw(c);
}


int main()
{

	// cr�ation de la fen�tre
	sf::RenderWindow window(sf::VideoMode(300, 300), "jeu de morpion");

	// tableau de jeu
	int tab[3][3];

	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			tab[i][j] = 0;

	// indique le tour du joueur rouge
	bool redturn = true;

	// compte le nombre de cases vide
	int nbleft = 9;


	// boucle principale
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			// demande de fermeture de la fen�tre
			if (event.type == sf::Event::Closed)
				window.close();
			
			// appui sur le bouton gauche
			if ( (event.type == sf::Event::MouseButtonPressed)
				&& (event.mouseButton.button == sf::Mouse::Left) ) {
				// si on a plus de place, on vide le tableau
				if (nbleft == 0) {
					for (size_t i = 0; i < 3; i++)
						for (size_t j = 0; j < 3; j++)
							tab[i][j] = 0;
					nbleft = 9;
				}
				// sinon, on place notre jeton
				else {
					// position de la souris dans par rapport � la fen�tre
					sf::Vector2i localposition = sf::Mouse::getPosition(window);

					// position de la souris dans le tableau
					localposition /= 100;

					// affichage console des coordon�es
					std::cout << localposition.x << " " << localposition.y << std::endl;

					// si on tombe sur une case vide
					if (tab[localposition.x][localposition.y] == 0) {
						// on remplie en fonction du tour du joueur (1 pour rouge, 2 pour bleu)
						tab[localposition.x][localposition.y] = redturn ? 1 : 2;
						// on change de joueur
						redturn = !redturn;
						// on met a jour le nombre de cases vides
						nbleft--;
					}
				}
			}
			
		}

		// on efface la fen�tre (en blanc)
		window.clear(sf::Color::White);

		// on affiche la grille
		drawgrid(window);

		// parcours du tableau
		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 3; j++) {

				// affichage du jeton
				if (tab[i][j] == 1) 
					drawcircle(window, i, j);
				else if (tab[i][j] == 2) 
					drawcross(window, i, j);
			}
		}
				
		// mise � jour de la fen�tre
		window.display();
	}

	return 0;
}
