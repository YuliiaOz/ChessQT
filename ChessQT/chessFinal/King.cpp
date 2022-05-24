/*
  Partie du programme qui sert pour la pièce d'échecs
  de type « Roi ».

  file   King.cpp
  author Légaré et Ozirska
  date   6 mai 2022
  Créé le 12 avril 2022
*/

#include "King.h"

using namespace pieceEchiquier;

int Roi::_nKing = 0;

 pieceEchiquier::Roi::Roi(int x, int y, bool isWhite)
{
	_name = "Roi";

	_pCoordinates[0] = x;
	_pCoordinates[1] = y;

	_isWhite = isWhite;

	if (_isWhite) {
		_name += " blanc";
		_icon = QIcon("icons/king_w.png");
	}
	else {
		_name += " noir"; 
		_icon = QIcon("icons/king_b.png"); 
	}

	if (_nKing == (2)) {
		throw _nKing;
	}
	else { 
		_nKing++; 
	}
}

 bool pieceEchiquier::Roi::isMoveValid(Piece* piece, int xToGo, int yToGo)
{
	bool firstPossibleMove = (abs(piece->getXCoordinate() - xToGo) == 1 && abs(piece->getYCoordinate() - yToGo) == 1);
	bool secondPossibleMove = (abs(piece->getXCoordinate() - xToGo) == 0 && abs(piece->getYCoordinate() - yToGo) == 1);
	bool thirdPossibleMove = (abs(piece->getXCoordinate() - xToGo) == 1 && abs(piece->getYCoordinate() - yToGo) == 0);
	if (firstPossibleMove || secondPossibleMove || thirdPossibleMove) {
		return true;
	}
	return false;
}

 int pieceEchiquier::Roi::getNKing() { return _nKing; }
