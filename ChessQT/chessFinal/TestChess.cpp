/*
  Ce fichier contient une série de tests
  servant à vérifier le bon fonctionnement du
  programme. Une couverture du code de 100% a
  été visée pour le modèle vue dans le bus de
  vérifier que tout fonctionne comme prévu.

  file   TestChess.cpp
  author Légaré et Ozirska
  date   5 mai 2022
  Créé le 12 avril 2022
*/

// Un type de warning a été désactivé pour 
// une opération "deprecated" d'après le conseil
// de monsieur Boyer.
#pragma warning(disable:5045)
#include "Board.h"
#include "Square.h"
#include "Rook.h"
#include "King.h"
#include "Menu.h"
#include "Knight.h"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST
#pragma warning(default:5045)

TEST(Menu, simple) {
	Board* board = new Board;
	Menu* menu2 = new Menu(board);
	
	// test du board 2
	menu2->createBoard2();
	menu2->getBoard()->destroyed();
	menu2->getBoard()->getBox()->destroyed();
	menu2->getBoard()->getBox()->close();
	Roi::_nKing = Roi::_nKing - 2;
	EXPECT_EQ(Roi::_nKing, 0);
	
	// test du boutton reset
	menu2->resetPartie();
	menu2->getBoard()->getBox()->close();
	menu2->getBox()->close();
	EXPECT_EQ(Roi::_nKing, 0);
	
	// test du board 3
	menu2->createBoard3();
	menu2->getBoard()->destroyed();
	menu2->getBoard()->getBox()->destroyed();
	menu2->getBoard()->getBox()->close();
	Roi::_nKing = Roi::_nKing - 2;
	EXPECT_EQ(Roi::_nKing, 0);

	menu2->quitApplication();
}

TEST(Menu, exception) {
	Board* board = new Board;
	Menu* menu2 = new Menu(board);

	// Devrait lancer une exception
	try {
		menu2->createBoard1();
		menu2->getBoard()->destroyed();
		menu2->getBoard()->getBox()->destroyed();
		menu2->getBoard()->getBox()->close();
	}
	catch (int myNumber) {
		myNumber;
	}
	Roi::_nKing = Roi::_nKing - 2;
	EXPECT_EQ(Roi::_nKing, 0);
	
	menu2->quitApplication();
}

TEST(Board, simple) {
	Board* board = new Board;

	Cavalier* cavalier = new Cavalier(4, 4, true);
	EXPECT_EQ(cavalier->getXCoordinate(), 4);
	EXPECT_EQ(cavalier->getYCoordinate(), 4);
	EXPECT_EQ(cavalier->getColor(), true);
	board->setPiece(cavalier);

	Tour* tour = new Tour(6, 6, false);
	EXPECT_EQ(tour->getXCoordinate(), 6);
	EXPECT_EQ(tour->getYCoordinate(), 6);
	EXPECT_EQ(tour->getColor(), false);
	board->setPiece(tour);
	board->movePiece(tour, 6, 8);

	Tour* tour2 = new Tour(6, 6, true);
	EXPECT_EQ(tour2->getXCoordinate(), 6);
	EXPECT_EQ(tour2->getYCoordinate(), 6);
	EXPECT_EQ(tour2->getColor(), true);
	board->setPiece(tour2);
	tour2->isMoveValid(tour2, 7, 7);

	board->deletePiece(tour);
	board->deletePiece(cavalier);

	Roi* roi = new Roi(2, 2, false);
	EXPECT_EQ(roi->getXCoordinate(), 2);
	EXPECT_EQ(roi->getYCoordinate(), 2);
	EXPECT_EQ(roi->getColor(), false);
	board->setPiece(roi);

	EXPECT_EQ(roi->isMoveValid(roi, 2, 3), true);
	EXPECT_EQ(roi->isMoveValid(roi, 3, 3), true);
	EXPECT_EQ(roi->isMoveValid(roi, 4, 4), false);
	EXPECT_EQ(roi->isMoveValid(roi, 5, 5), false);

	board->movePiece(roi, 3, 3);
	EXPECT_EQ(roi->getXCoordinate(), 3);
	EXPECT_EQ(roi->getYCoordinate(), 3);

	board->movePiece(roi, 4, 3);
	EXPECT_EQ(roi->getXCoordinate(), 4);
	EXPECT_EQ(roi->getYCoordinate(), 3);

	EXPECT_EQ(roi->getNKing(), 1);

	Roi* roi2 = new Roi(4, 4, true);
	EXPECT_EQ(roi2->getXCoordinate(), 4);
	EXPECT_EQ(roi2->getYCoordinate(), 4);
	EXPECT_EQ(roi2->getColor(), true);
	EXPECT_EQ(roi2->getNKing(), 2);
	board->setPiece(roi2);

	board->movePiece(roi, 5, 5);
	EXPECT_EQ(roi->getXCoordinate(), 4);
	EXPECT_EQ(roi->getYCoordinate(), 3);

	Tour* tour3 = new Tour(6, 6, true);
	EXPECT_EQ(tour3->getXCoordinate(), 6);
	EXPECT_EQ(tour3->getYCoordinate(), 6);
	EXPECT_EQ(tour3->getColor(), true);
	board->setPiece(tour3);

	Tour* tour4 = new Tour(6, 7, false);
	EXPECT_EQ(tour4->getXCoordinate(), 6);
	EXPECT_EQ(tour4->getYCoordinate(), 7);
	EXPECT_EQ(tour4->getColor(), false);
	board->setPiece(tour4);

	EXPECT_EQ(board->checkColor(tour3, tour4), true);

	board->movePiece(tour4, 6, 6);
	EXPECT_EQ(tour4->getXCoordinate(), 6);
	EXPECT_EQ(tour4->getYCoordinate(), 7);

	Roi::_nKing = Roi::_nKing - 2;
	EXPECT_EQ(Roi::_nKing, 0);

	board->selectPiece();

	delete tour2;
	delete roi;
	delete roi2;
	delete tour4;
	delete tour3;

	QGroupBox* boxTest = board->getBox();
	EXPECT_EQ(board->getBox(), boxTest);

	QGridLayout* gridTest = board->getGrid();
	EXPECT_EQ(board->getGrid(), gridTest);
	board->getBox()->close();
	board->destroyed();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete board->getElementsList(i, j)->getSquareButton(); // Delete des QPushButtons* de squares
			delete board->getElementsList(i, j); // Delete des squares
		}
	}

	delete board->getButton(); // delete du bouton reset
	delete board->getGrid(); // delete du QGridLayout*
	delete board->getBox(); // delete du QBoxLayout*

	delete board;
}

#endif
