/*
  Partie du programme qui sert pour la pièce d'échecs
  de type « Tour ».

  file   Tour.cpp
  author Légaré et Ozirska
  date   6 mai 2022
  Créé le 12 avril 2022
*/

#include "Rook.h"

pieceEchiquier::Tour::Tour(int x, int y, bool isWhite)
{
	_name = "Tour";

	_pCoordinates[0] = x;
	_pCoordinates[1] = y;

	_isWhite = isWhite;

	if (_isWhite) {
		_name += " blanc";
		_icon = QIcon("icons/tower_w.png");
	}
	else { _name += " noir"; _icon = QIcon("icons/tower_b.png"); }
}

bool pieceEchiquier::Tour::isMoveValid(Piece* piece, int xToGo, int yToGo)
{
	if ((xToGo - piece->getXCoordinate() == 0) || (yToGo - piece->getYCoordinate() == 0)) {
		return true;
	}
	return false;
}
