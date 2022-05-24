/*
  Sert à gérer les pièces d'échec du jeu en
  général.

  file   Piece.cpp
  author Légaré et Ozirska
  date   6 mai 2022
  Créé le 12 avril 2022
*/

#include "Piece.h"

Piece::Piece(int x, int y, bool isWhite)
{
	_pCoordinates[0] = x;
	_pCoordinates[1] = y;

	_isWhite = isWhite;
}

Piece::~Piece() {}
QIcon Piece::getQIcon() { return _icon; }
QString Piece::getName() { return _name; }

int Piece::getXCoordinate() { return _pCoordinates[0]; }
int Piece::getYCoordinate() { return _pCoordinates[1]; }
void Piece::setXCordinates(int newCoordinates) { _pCoordinates[0] = newCoordinates; }
void Piece::setYCordinates(int newCoordinates) { _pCoordinates[1] = newCoordinates; }
bool Piece::getColor() { return _isWhite; }
void Piece::showCoordinates() { std::cout << _pCoordinates[0] << " " << _pCoordinates[1] << std::endl; }
