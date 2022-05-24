/*
  Partie du programme qui sert pour la pi�ce d'�checs
  de type � Cavalier �.

  file   Knight.cpp
  author L�gar� et Ozirska
  date   6 mai 2022
  Cr�� le 12 avril 2022
*/

#include "Knight.h"

pieceEchiquier::Cavalier::Cavalier(int x, int y, bool isWhite)
{
	_name = "Cavalier";

	_pCoordinates[0] = x;
	_pCoordinates[1] = y;

	_isWhite = isWhite;

	if (_isWhite) {
		_name += " blanc";
		_icon = QIcon("icons/knight_w.png");
	}
	else { _name += " noir"; _icon = QIcon("icons/knight_b.png"); }
}

bool pieceEchiquier::Cavalier::isMoveValid(Piece* piece, int xToGo, int yToGo)
{
	bool firstCondition = (abs(piece->getXCoordinate() - xToGo) == 2 && abs(piece->getYCoordinate() - yToGo) == 1);
	bool secondCondition = (abs(piece->getXCoordinate() - xToGo) == 1 && abs(piece->getYCoordinate() - yToGo) == 2);
	if ( firstCondition || secondCondition) {
		return true;
	}
	return false;
}
