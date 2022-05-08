#include "grille.h"

void afficherGrille(sf::RenderWindow& window, int tailleGrille) {
	std::vector<sf::RectangleShape> lines;
	int nb_lignes_h = 5;
	int nb_lignes_v = tailleGrille - 1;

	for (int i = 0; i < nb_lignes_h; i++) {
		//lignes horizontales
		lines.push_back(sf::RectangleShape(sf::Vector2f(tailleGrille * 100, 6))); // 6 = largeur de la ligne
	}
	for (int i = 0; i < nb_lignes_v; i++) {
		//lignes verticales
		lines.push_back(sf::RectangleShape(sf::Vector2f(6, 600))); // 6 : largeur de la ligne
	}
	for (int i = 0; i < nb_lignes_h; i++) {
		//positionnement
		lines[i].setPosition(0, 97 + 100 * i);
	}
	
	for (int i = nb_lignes_h; i < nb_lignes_v + nb_lignes_h; i++) {		//vertical
		lines[i].setPosition(97 + 100 * (i-nb_lignes_h), 0);
	}

	// met les lignes en noir
	for (size_t i = 0; i < lines.size(); i++)
		lines[i].setFillColor(sf::Color::Black);

	// affichage
	for (size_t i = 0; i < lines.size(); i++)
		window.draw(lines[i]);
}