/*
  Sert � g�rer chacun des carr�es qui composeront
  l'�chiquier du jeu. 

  file   Square.h
  author L�gar� et Ozirska
  date   6 mai 2022
  Cr�� le 12 avril 2022
*/

#pragma once

#include "Piece.h"

#include <qpushbutton.h>
#include <iostream>
#include <string>

class Square 
{
public:
	Square(int positionX, int positionY, Piece* piece = nullptr);
	void setSquareGui(QPushButton* squareGUI);
	QPushButton* getSquareButton();

	void setCoordinates(int& xPosition, int& yPosition);
	void setPiece(Piece* piece);
	void showCoordinates();

	Piece* getPiece();
	int getXCoordinate();
	int getYCoordinate();

private:
	QPushButton* _squareButton;
	int _coordinates[2];
	Piece* _piece;
};
