/*
  Programme qui g�n�re un jeu de type � �checs �.

  file   main.cpp
  author L�gar� et Ozirska
  date   4 mai 2022
  Cr�� le 12 avril 2022
*/

#pragma warning(disable:5045)
#include <QApplication>
#include <memory>

#include "Menu.h"
#include "Square.h"
#include "Board.h"
#include "Knight.h"
#include "Rook.h"
#include <iostream>

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette ent�te si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif
#pragma warning(default:5045)

// SOURCE: Les images qui ont servies pour les pi�ces de notre jeu ont �t� tir�es de 
// Wikip�dia (https://commons.wikimedia.org/wiki/Category:PNG_chess_pieces/Standard_transparent)

// Cette partie (initialiserBibliothequeCours) a �t� pris de l'exemple de la calculatrice!
void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
#ifdef BIBLIOTHEQUE_COURS_INCLUS
    bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par d�faut.

    // cdbg.setTee(&clog);  // D�commenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du d�bogueur.

    bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un r�sultat de test.
#endif
//NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main apr�s l'appel � cette fonction puisqu'il ex�cute uniquement les tests Google Test dans l'appel ci-dessus.
}

int main(int argc, char* argv[])
{
    using namespace affichage;

    QApplication a(argc, argv);
    initialiserBibliothequeCours(argc, argv);

    Board* board = new Board;
    Menu* menu = new Menu(board);

    QObject::connect(&a, SIGNAL(aboutToQuit()), menu, SLOT(quitApplication()));

    return a.exec();
}