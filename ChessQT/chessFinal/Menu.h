/*
  Sert à gérer le menu principal du jeu (dans lequel
  apparaissent trois options de départ).

  file   Menu.h
  author Légaré et Ozirska
  date   6 mai 2022
  Créé le 12 avril 2022
*/

#pragma once

#include <QLabel>
#include <QMessageBox>
#include <QCloseEvent>

#include "King.h"
#include "Board.h"

using namespace pieceEchiquier;
using namespace raii;
using namespace affichage;

class Menu : public QObject
{
	Q_OBJECT
public:
	Menu(Board* board);

	QPushButton* _buttonList[3];
	QLabel* _labelList[3];
	QLabel* createLabel(QString string);

signals:
	void clicked();

public slots:
	void createBoard1();
	void createBoard2();
	void createBoard3();

	void resetPartie();
	void quitApplication();

	Board* getBoard();
	QGroupBox* getBox();

private:
	Board* _board; 
	QGroupBox* _box;
};