#pragma once

#include "historique.h"
#include <string>
#include <vector>

using namespace std;

class Menu;
//dérivée de la classe menu, permet de définir les options du menu principal
class OptionMenu
{
    string nom_;
    string description_;
public:
    OptionMenu(const string& nom, const string& description); //initialise une option dans un menu
    string getNom() const { return nom_; } //retourne le nom de l'option
    string getDescription() const { return description_; } //retourne la description de l'option
};

//la classe Menu permet de definir le menu principal du jeu, il contient certaines options, un titre et un historique qu'il met à jour au fil des parties
class Menu
{
    string titre_;
    vector<OptionMenu> listeOptions_;
    Historique historique_;
public:
    Menu(const string& titre, Historique H); //initialise le menu
    void setTitre(const string& titre); //donne un titre au menu
    void ajouterOption(const string& nom, const string& description); //ajoute une option au menu
    void afficherMenu(sf::RenderWindow& window); //affiche le menu dans une fenetre SFML
    int demanderChoix(sf::RenderWindow& window); //attend que le joueur clique sur une option du menu et retourne cette option
    void executer(); //execute le menu
    virtual void executerOption(const string& nom, bool& fin); //execute l'option choisie
    bool quitter(); //lance la fonction qui permet de quitter l'application
    virtual void aide(); //explique comment fonctionne le menu
    virtual void jouer(); //explique comment fnctionne l'application
    void historique(); //ouvre l'historique du jeu
};