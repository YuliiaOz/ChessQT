/*
  Sert à gérer chacun des carrées qui composeront
  l'échiquier du jeu.

  file   Square.cpp
  author Légaré et Ozirska
  date   6 mai 2022
  Créé le 12 avril 2022
*/

#include "Square.h"

Square::Square(int positionX, int positionY, Piece* piece)
{
	QPushButton* square = new QPushButton; 
	QSize size;

	size.setWidth(70);
	size.setHeight(70);
	square->setIconSize(size);
	square->setFixedSize(100, 100);
	setSquareGui(square);
	setCoordinates(positionX, positionY);

	_squareButton = square;
	_piece = piece;
}

void Square::setSquareGui(QPushButton* squareGUI) { _squareButton = squareGUI; }

QPushButton* Square::getSquareButton() { return _squareButton; }

void Square::setCoordinates(int& xPosition, int& yPosition) { _coordinates[0] = xPosition, _coordinates[1] = yPosition; }

void Square::setPiece(Piece* piece) { _piece = piece; }

void Square::showCoordinates() { std::cout << _coordinates[0] << " " << _coordinates[1] << std::endl; }

Piece* Square::getPiece() { return _piece; }

int Square::getXCoordinate() { return _coordinates[0]; }

int Square::getYCoordinate() { return _coordinates[1]; }
